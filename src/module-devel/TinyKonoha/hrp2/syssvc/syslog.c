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
 *  $Id: syslog.c 837 2012-12-26 15:09:59Z ertl-hiro $
 */

/*
 *		�����ƥ����ǽ
 */

#include <sil.h>
#include <kernel.h>
#undef TOPPERS_OMIT_SYSLOG
#include <t_syslog.h>
#include <t_stdlib.h>
#include <log_output.h>
#include "target_syssvc.h"
#include "syslog.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_SYSLOG_WRI_LOG_ENTER
#define LOG_SYSLOG_WRI_LOG_ENTER(prio, p_syslog)
#endif /* LOG_SYSLOG_WRI_LOG_ENTER */

#ifndef LOG_SYSLOG_WRI_LOG_LEAVE
#define LOG_SYSLOG_WRI_LOG_LEAVE(ercd)
#endif /* LOG_SYSLOG_WRI_LOG_LEAVE */

#ifndef LOG_SYSLOG_FWRI_LOG_ENTER
#define LOG_SYSLOG_FWRI_LOG_ENTER(ercd, p_syslog)
#endif /* LOG_SYSLOG_FWRI_LOG_ENTER */

#ifndef LOG_SYSLOG_FWRI_LOG_LEAVE
#define LOG_SYSLOG_FWRI_LOG_LEAVE(ercd)
#endif /* LOG_SYSLOG_FWRI_LOG_LEAVE */

#ifndef LOG_SYSLOG_REA_LOG_ENTER
#define LOG_SYSLOG_REA_LOG_ENTER(p_syslog)
#endif /* LOG_SYSLOG_REA_LOG_ENTER */

#ifndef LOG_SYSLOG_REA_LOG_LEAVE
#define LOG_SYSLOG_REA_LOG_LEAVE(ercd, p_syslog)
#endif /* LOG_SYSLOG_REA_LOG_LEAVE */

#ifndef LOG_SYSLOG_MSK_LOG_ENTER
#define LOG_SYSLOG_MSK_LOG_ENTER(logmask, lowmask)
#endif /* LOG_SYSLOG_MSK_LOG_ENTER */

#ifndef LOG_SYSLOG_MSK_LOG_LEAVE
#define LOG_SYSLOG_MSK_LOG_LEAVE(ercd)
#endif /* LOG_SYSLOG_MSK_LOG_LEAVE */

#ifndef LOG_SYSLOG_REF_LOG_ENTER
#define LOG_SYSLOG_REF_LOG_ENTER(pk_rlog)
#endif /* LOG_SYSLOG_REF_LOG_ENTER */

#ifndef LOG_SYSLOG_REF_LOG_LEAVE
#define LOG_SYSLOG_REF_LOG_LEAVE(pk_rlog)
#endif /* LOG_SYSLOG_REF_LOG_LEAVE */

/*
 *  ���ߤΥ����ƥ����
 *
 *  ���������Ф�����ˡ����ʤ��������ͥ�������ѿ��򻲾Ȥ��Ƥ�
 *  �롥
 */
extern ulong_t	_kernel_current_time;

/*
 *  ���Хåե��Ȥ���˥����������뤿��Υݥ���
 */
static SYSLOG	syslog_buffer[TCNT_SYSLOG_BUFFER];	/* ���Хåե� */
static uint_t	syslog_count;			/* ���Хåե���Υ��ο� */
static uint_t	syslog_head;			/* ��Ƭ�Υ��γ�Ǽ���� */
static uint_t	syslog_tail;			/* ���Υ��γ�Ǽ���� */
static uint_t	syslog_lost;			/* ����줿���ο� */

/*
 *  ���Ϥ��٤�������ν����١ʥӥåȥޥåס�
 */
static uint_t	syslog_logmask;			/* ���Хåե��˵�Ͽ���٤������� */
static uint_t	syslog_lowmask_not;		/* ���٥���Ϥ��٤������١�ȿž��*/

/*
 *  �����ƥ����ǽ�ν����
 */
void
syslog_initialize(intptr_t exinf)
{
	syslog_count = 0U;
	syslog_head = 0U;
	syslog_tail = 0U;
	syslog_lost = 0U;
	syslog_logmask = 0U;
	syslog_lowmask_not = 0U;
}     

/* 
 *  ������ν���
 *
 *  CPU��å����֤�¹ԥ���ƥ����Ȥˤ�餺ư��Ǥ���褦�˼������Ƥ��롥
 */
ER
_syslog_syslog_wri_log(uint_t prio, const SYSLOG *p_syslog)
{
	SIL_PRE_LOC;

	LOG_SYSLOG_WRI_LOG_ENTER(prio, p_syslog);
	SIL_LOC_INT();

	/*
	 *  �����������
	 */
	((SYSLOG *) p_syslog)->logtim = _kernel_current_time;

	/*
	 *  ���Хåե��˵�Ͽ
	 */
	if ((syslog_logmask & LOG_MASK(prio)) != 0U) {
		syslog_buffer[syslog_tail] = *p_syslog;
		syslog_tail++;
		if (syslog_tail >= TCNT_SYSLOG_BUFFER) {
			syslog_tail = 0U;
		}
		if (syslog_count < TCNT_SYSLOG_BUFFER) {
			syslog_count++;
		}
		else {
			syslog_head = syslog_tail;
			syslog_lost++;
		}
	}

	/*
	 *  ���٥����
	 */
	if (((~syslog_lowmask_not) & LOG_MASK(prio)) != 0U) {
		syslog_print(p_syslog, target_fput_log);
		target_fput_log('\n');
	}

	SIL_UNL_INT();
	LOG_SYSLOG_WRI_LOG_LEAVE(E_OK);
	return(E_OK);
}

/* 
 *  ������ν��ϼ��Ի��ν���
 */
ER
_syslog_syslog_fwri_log(ER ercd, const SYSLOG *p_syslog)
{
	intptr_t	args;
	SIL_PRE_LOC;

	LOG_SYSLOG_FWRI_LOG_ENTER(prio, p_syslog);
	SIL_LOC_INT();

	/*
	 *  �����������
	 */
	((SYSLOG *) p_syslog)->logtim = _kernel_current_time;

	/*
	 *  ���٥����
	 */
	args = (intptr_t)(itron_strerror(MERCD(ercd)));
	syslog_printf("syslog_wri_log failed with %s.", &args, target_fput_log);
	target_fput_log('\n');

	syslog_print(p_syslog, target_fput_log);
	target_fput_log('\n');

	/*
	 *  �����ͥ�ν�λ
	 */
	(void) ext_ker();

	/*
	 *  ����ѥ���ηٹ��к��ʤ�������뤳�ȤϤʤ��Ϥ���
	 */
	SIL_UNL_INT();
	LOG_SYSLOG_FWRI_LOG_LEAVE(E_SYS);
	return(E_SYS);
}

/*
 *  ���Хåե�������ɽФ�
 *
 *  CPU��å����֤�¹ԥ���ƥ����Ȥˤ�餺ư��Ǥ���褦�˼������Ƥ��롥
 */
ER_UINT
_syslog_syslog_rea_log(SYSLOG *p_syslog)
{
	ER_UINT	ercd;
	SIL_PRE_LOC;

	LOG_SYSLOG_REA_LOG_ENTER(p_syslog);
	SIL_LOC_INT();

	/*
	 *  ���Хåե�����μ�Ф�
	 */
	if (syslog_count > 0U) {
		*p_syslog = syslog_buffer[syslog_head];
		syslog_count--;
		syslog_head++;
		if (syslog_head >= TCNT_SYSLOG_BUFFER) {
			syslog_head = 0U;
		}
		ercd = (ER_UINT) syslog_lost;
		syslog_lost = 0U;
	}
	else {
		ercd = E_OBJ;
	}

	SIL_UNL_INT();
	LOG_SYSLOG_REA_LOG_LEAVE(ercd, p_syslog);
	return(ercd);
}

/* 
 *  ���Ϥ��٤�������ν����٤�����
 */
ER
_syslog_syslog_msk_log(uint_t logmask, uint_t lowmask)
{
	LOG_SYSLOG_MSK_LOG_ENTER(logmask, lowmask);
	syslog_logmask = logmask;
	syslog_lowmask_not = ~lowmask;
	LOG_SYSLOG_MSK_LOG_LEAVE(E_OK);
	return(E_OK);
}

/*
 *  ���Хåե��ξ��ֻ���
 */
ER
_syslog_syslog_ref_log(T_SYSLOG_RLOG *pk_rlog)
{
	SIL_PRE_LOC;

	LOG_SYSLOG_REF_LOG_ENTER(pk_rlog);
	SIL_LOC_INT();

	pk_rlog->count = syslog_count;
	pk_rlog->lost = syslog_lost;
	pk_rlog->logmask = syslog_logmask;
	pk_rlog->lowmask = ~syslog_lowmask_not;

	SIL_UNL_INT();
	LOG_SYSLOG_REF_LOG_LEAVE(pk_rlog);
	return(E_OK);
}

/*
 *  ���ꥢ���������Υ����å��Τ���Υޥ���
 */
#ifndef PROBE_MEM_WRITE
#define PROBE_MEM_WRITE(p_var, type) \
				(ALIGN_TYPE(p_var, type) && (cdmid == TDOM_KERNEL		\
						|| prb_mem((void *)(p_var), sizeof(type),		\
										 TSK_SELF, TPM_WRITE) == E_OK))
#endif /* PROBE_MEM_WRITE */

#ifndef PROBE_MEM_READ
#define PROBE_MEM_READ(p_var, type) \
				(ALIGN_TYPE(p_var, type) && (cdmid == TDOM_KERNEL		\
						|| prb_mem((void *)(p_var), sizeof(type),		\
										 TSK_SELF, TPM_READ) == E_OK))
#endif /* PROBE_MEM_READ */

/*
 *  �����ƥ����ǽ���ĥ�����ӥ�������Ȥ�����Ͽ���뤿������
 */
ER_UINT
extsvc_syslog_wri_log(intptr_t prio, intptr_t p_syslog, intptr_t par3,
							intptr_t par4, intptr_t par5, ID cdmid)
{
	ER		ercd;

	if (!PROBE_MEM_READ(p_syslog, SYSLOG)) {
		ercd = E_MACV;
	}
	else {
		ercd = _syslog_syslog_wri_log((uint_t) prio,
										(const SYSLOG *) p_syslog);
	}
	return((ER_UINT) ercd);
}

ER_UINT
extsvc_syslog_fwri_log(intptr_t ercd, intptr_t p_syslog, intptr_t par3,
							intptr_t par4, intptr_t par5, ID cdmid)
{
	return((ER_UINT) _syslog_syslog_fwri_log((ER) ercd,
										(const SYSLOG *) p_syslog));
}

ER_UINT
extsvc_syslog_rea_log(intptr_t p_syslog, intptr_t par2, intptr_t par3,
							intptr_t par4, intptr_t par5, ID cdmid)
{
	ER		ercd;

	if (!PROBE_MEM_WRITE(p_syslog, SYSLOG)) {
		ercd = E_MACV;
	}
	else {
		ercd = _syslog_syslog_rea_log((SYSLOG *) p_syslog);
	}
	return((ER_UINT) ercd);
}

ER_UINT
extsvc_syslog_msk_log(intptr_t logmask, intptr_t lowmask, intptr_t par3,
							intptr_t par4, intptr_t par5, ID cdmid)
{
	return((ER_UINT) _syslog_syslog_msk_log((uint_t) logmask,
												(uint_t) lowmask));
}

ER_UINT
extsvc_syslog_ref_log(intptr_t pk_rlog, intptr_t par2, intptr_t par3,
							intptr_t par4, intptr_t par5, ID cdmid)
{
	ER		ercd;

	if (!PROBE_MEM_WRITE(pk_rlog, T_SYSLOG_RLOG)) {
		ercd = E_MACV;
	}
	else {
		ercd = _syslog_syslog_ref_log((T_SYSLOG_RLOG *) pk_rlog);
	}
	return((ER_UINT) ercd);
}
