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
 *  @(#) $Id: memory.c 599 2012-02-05 06:40:30Z ertl-hiro $
 */

/*
 *		���ꥪ�֥������ȴ����⥸�塼��
 */

#include "kernel_impl.h"
#include "task.h"
#include "memory.h"

/*
 *  ���ꥪ�֥������ȴ����⥸�塼��ν����
 */
#ifdef TOPPERS_memini
#ifndef OMIT_INITIALIZE_MEMORY

void
initialize_memory(void)
{
}

#endif /* OMIT_INITIALIZE_MEMORY */
#endif /* TOPPERS_memini */

/*
 *  ���ꥪ�֥������Ƚ�����֥�å��θ���
 */
#ifdef TOPPERS_memsearch
#ifndef OMIT_STANDARD_MEMINIB

int_t
search_meminib(const void *addr)
{
	uint_t	left, right, i;

	left = 0;
	right = tnum_meminib - 1;
	while (left < right) {
		i = (left + right + 1) / 2;
		if ((SIZE)(addr) < (SIZE)(memtop_table[i])) {
			right = i - 1;
		}
		else {
			left = i;
		}
	}
	return(left);
}

#endif /* OMIT_STANDARD_MEMINIB */
#endif /* TOPPERS_memsearch */

/*
 *  ����ؤν���߸��Υ����å�
 */
#ifdef TOPPERS_memprbw
#ifndef OMIT_PROBE_MEM_WRITE

bool_t
probe_mem_write(const void *base, SIZE size)
{
	int_t	meminib;
	ATR		mematr;
	SIZE	memsize;

	meminib = search_meminib(base);
	mematr = meminib_table[meminib].mematr;
	memsize = ((char *)((meminib + 1 < tnum_meminib) ?
					memtop_table[meminib + 1] : 0)) - ((char *) base);

	if (mematr == TA_NULL) {
		return(false);
	}
	else if (size > memsize) {
		/*
		 *  ���ꤵ�줿�����ΰ褬��ʣ���Υ��ꥪ�֥������Ȥˤޤ�����
		 *  �Ƥ�����
		 */
		return(false);
	}
	else if ((mematr & TOPPERS_USTACK) == 0U) {
		/*
		 *  ((mematr & TA_NOWRITE) != 0U)�λ��ϡ�acptn1��0�ˤ��Ƥ��뤿
		 *  �ᡤ��ԤΥ����å��Τߤ�Ԥ��Ф褤��
		 */
		return((rundom & meminib_table[meminib].acptn1) != 0U);
	}
	else {
		return(within_ustack(base, size, p_runtsk));
	}
}

#endif /* OMIT_PROBE_MEM_WRITE */
#endif /* TOPPERS_memprbw */

/*
 *  ���꤫����ɽФ����Υ����å�
 */
#ifdef TOPPERS_memprbr
#ifndef OMIT_PROBE_MEM_READ

bool_t
probe_mem_read(const void *base, SIZE size)
{
	int_t	meminib;
	ATR		mematr;
	SIZE	memsize;

	meminib = search_meminib(base);
	mematr = meminib_table[meminib].mematr;
	memsize = ((char *)((meminib + 1 < tnum_meminib) ?
					memtop_table[meminib + 1] : 0)) - ((char *) base);

	if (mematr == TA_NULL) {
		return(false);
	}
	else if (size > memsize) {
		/*
		 *  ���ꤵ�줿�����ΰ褬��ʣ���Υ��ꥪ�֥������Ȥˤޤ�����
		 *  �Ƥ�����
		 */
		return(false);
	}
	else if ((mematr & TOPPERS_USTACK) == 0U) {
		return((mematr & TA_NOREAD) == 0U
					&& (rundom & meminib_table[meminib].acptn2) != 0U);
	}
	else {
		return(within_ustack(base, size, p_runtsk));
	}
	return(true);
}

#endif /* OMIT_PROBE_MEM_READ */
#endif /* TOPPERS_memprbr */

/*
 *  �����å��ΰ�˴ޤޤ�Ƥ��뤫�Υ����å�
 */
#ifdef TOPPERS_memprbs
#ifndef OMIT_PROBE_STACK

bool_t
probe_stack(const void *base, SIZE size)
{
	return(within_ustack(base, size, p_runtsk));
}

#endif /* OMIT_PROBE_STACK */
#endif /* TOPPERS_memprbs */

/*
 *  DATA����������BSS���������ν����
 */
#ifdef TOPPERS_secini
#ifndef OMIT_INITIALIZE_SECTIONS

void
initialize_sections(void)
{
	uint_t				i;
	uint8_t				*src, *dst;
	const DATASECINIB	*p_datasecinib;
	const BSSSECINIB	*p_bsssecinib;

	for (i = 0; i < tnum_datasec; i++) {
		p_datasecinib = &(datasecinib_table[i]);
		for (src = p_datasecinib->start_idata, dst = p_datasecinib->start_data;
				(SIZE)(dst) < (SIZE)(p_datasecinib->end_data); src++, dst++) {
					
			*dst = *src;
		}
	}
	for (i = 0; i < tnum_bsssec; i++) {
		p_bsssecinib = &(bsssecinib_table[i]);
		for (dst = p_bsssecinib->start_bss;
				(SIZE)(dst) < (SIZE)(p_bsssecinib->end_bss); dst++) {
			*dst = 0U;
		}
	}
}

#endif /* OMIT_INITIALIZE_SECTIONS */
#endif /* TOPPERS_secini */
