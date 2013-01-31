/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2012 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 *  $Id: mem_manage.c 837 2012-12-26 15:09:59Z ertl-hiro $
 */

/*
 *		���ꥪ�֥������ȴ�����ǽ
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"
#include "memory.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_PRB_MEM_ENTER
#define LOG_PRB_MEM_ENTER(base, size, tskid, pmmode)
#endif /* LOG_PRB_MEM_ENTER */

#ifndef LOG_PRB_MEM_LEAVE
#define LOG_PRB_MEM_LEAVE(ercd)
#endif /* LOG_PRB_MEM_LEAVE */

/*
 *  ���ꥢ���������Υ����å���prb_mem�����Ρ�
 */
#ifndef OMIT_PROBE_MEMORY

Inline ER
probe_memory(const void *base, SIZE size, TCB *p_tcb, MODE pmmode)
{
	ACPTN	domptn;
	int_t	meminib;
	ATR		mematr;
	SIZE	memsize;
	ER		ercd;

	domptn = p_tcb->p_tinib->p_dominib->domptn;
	meminib = search_meminib(base);
	mematr = meminib_table[meminib].mematr;
	memsize = ((char *)((meminib + 1 < tnum_meminib) ?
					memtop_table[meminib + 1] : 0)) - ((char *) base);

	if (mematr == TA_NULL) {
		ercd = E_NOEXS;
	}
	else if (size > memsize) {
		ercd = E_OBJ;
	}
	else if (rundom != TACP_KERNEL
				&& (rundom & meminib_table[meminib].acptn4) == 0U) {
		ercd = E_OACV;
	}
	else if (domptn == TACP_KERNEL) {
		/*
		 *  �оݥ������������ͥ�ɥᥤ���°������
		 */
		ercd = E_OK;
	}
	else if ((mematr & TOPPERS_USTACK) == 0U) {
		/*
		 *  �̾�Υ��ꥪ�֥������ȡʥ������Υ桼�������å��ΰ�ʳ���
		 *  �ξ��
		 *
		 *  ���ꥪ�֥�������°����TA_NOWRITE�ξ��ˤϡ�acptn1��0U��
		 *  �ʤäƤ���Τǡ����ꥪ�֥�������°����TA_NOWRITE�ϥ�����
		 *  �����Ƥ��ʤ���
		 */
		if ((pmmode & TPM_WRITE) != 0U
					&& (domptn & meminib_table[meminib].acptn1) == 0U) {
			ercd = E_MACV;
		}
		else if ((pmmode & TPM_READ) != 0U && ((mematr & TA_NOREAD) != 0U
						|| (domptn & meminib_table[meminib].acptn2) == 0U)) {
			ercd = E_MACV;
		}
		else if ((pmmode & TPM_EXEC) != 0U && ((mematr & TA_EXEC) == 0U
						|| (domptn & meminib_table[meminib].acptn2) == 0U)) {
			ercd = E_MACV;
		}
		else {
			ercd = E_OK;
		}
	}
	else {
		/*
		 *  �������Υ桼�������å��ΰ�ξ��
		 *
		 *  �桼�������å��ΰ褬�ɽФ��ػߤ����߶ػߤˤʤäƤ��뤳��
		 *  �Ϥ������ʤ����ᡤ���ꥪ�֥�������°����TA_NOWRITE��
		 *  TA_NOREAD�ϥ����å����Ƥ��ʤ���
		 */
		if (!within_ustack(base, size, p_tcb)) {
			ercd = E_MACV;
		}
		else if ((pmmode & TPM_EXEC) != 0U && ((mematr & TA_EXEC) == 0U)) {
			ercd = E_MACV;
		}
		else {
			ercd = E_OK;
		}
	}
	return(ercd);
}

#endif /* OMIT_PROBE_MEMORY */

/*
 *  ���ꥢ���������Υ����å�
 *
 *  ���Υ����ӥ�������Ǥϡ���Ū�ʥǡ�����¤�������Ȥ��ʤ����ᡤ����ƥ�
 *  ���륻����������ɬ�פ��ʤ���
 */
#ifdef TOPPERS_prb_mem

ER
prb_mem(const void *base, SIZE size, ID tskid, MODE pmmode)
{
	ER		ercd;

	LOG_PRB_MEM_ENTER(base, size, tskid, pmmode);
	CHECK_TSKCTX();
	CHECK_TSKID_SELF(tskid);
	CHECK_PAR(size > 0U);
	CHECK_PAR((pmmode & ~(TPM_READ|TPM_WRITE|TPM_EXEC)) == 0U);
	CHECK_PAR(pmmode != 0U);

	ercd = probe_memory(base, size, get_tcb_self(tskid), pmmode);

  error_exit:
	LOG_PRB_MEM_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_prb_mem */
