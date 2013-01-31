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
 *  @(#) $Id: memory.h 837 2012-12-26 15:09:59Z ertl-hiro $
 */

/*
 *		���ꥪ�֥������ȴ����⥸�塼��
 */

#ifndef TOPPERS_MEMORY_H
#define TOPPERS_MEMORY_H

/*
 *  ����°���ʥ����ͥ��������Ѥ����
 *
 *  HRP2�����ͥ�Ǽºݤ˻��Ȥ��Ƥ���Τϡ�TOPPERS_USTACK�ΤߤǤ��롥��
 *  ��¾��2�Ĥϡ������ͥ���Ǥ϶��̤��ư���ɬ�פ��ʤ���
 *
 *  ����ե�����졼��������դ������Ĺ����ס����ΰ�ϡ�¾�Υ���
 *  ���֥������Ȥ����礵����礬���뤿�ᡤTOPPERS_ATTSEC�Υ���°��
 *  �Ȥ��롥
 */
#define TOPPERS_ATTSEC	0x0100	/* ATT_SEC��ATA_SEC�ޤ���ATT_MOD��ATA_MOD
								   ����Ͽ���줿���ꥪ�֥������� */
#define TOPPERS_ATTMEM	0x0200	/* ATT_MEM��ATA_MEM����Ͽ���줿���ꥪ��
								   �������� */
#define TOPPERS_USTACK	0x0400	/* �������Υ桼�������å��ΰ� */

#ifndef TOPPERS_MACRO_ONLY
#ifndef OMIT_STANDARD_MEMINIB

/*
 *  ���ꥪ�֥������Ƚ�����֥�å�
 *
 *  ̤�����ΰ��TA_NULL�ˤ��Ф��Ƥϡ����٤ƤΥ����������ĥѥ�����
 *  ��acptn1��acptn2��acptn4�ˤ�0�ˤ��롥�ޤ����꡼�ɥ���꡼��TA_RO��
 *  ���ΰ���Ф��Ƥϡ��̾����1�ʽ���ߥ��������ˤΥ����������ĥѥ�����
 *  ��acptn1�ˤ�0�ˤ��롥
 */
typedef struct memory_initialization_block {
	ATR		mematr;			/* ���ꥪ�֥�������°�� */
	ACPTN	acptn4;			/* �������Υ����������ĥѥ����� */
	ACPTN	acptn1;			/* �̾����1�Υ����������ĥѥ����󡿥�������TCB */
	ACPTN	acptn2;			/* �̾����2�Υ����������ĥѥ����� */
} MEMINIB;

/*
 *  ���ꥪ�֥������Ƚ�����֥�å��Υ���ȥ����kernel_cfg.c��
 */
extern const uint_t		tnum_meminib;

/*
 *  ���ꥪ�֥������Ȥ���Ƭ���Ϥ��ΰ��kernel_cfg.c��
 */
extern void *const		memtop_table[];

/*
 *  ���ꥪ�֥������Ƚ�����֥�å����ΰ��kernel_cfg.c��
 */
extern const MEMINIB	meminib_table[];

#endif /* OMIT_STANDARD_MEMINIB */

/*
 *  ���ꥪ�֥������ȴ����⥸�塼��ν����
 */
extern void		initialize_memory(void);

/*
 *  ���ꥪ�֥������Ƚ�����֥�å��θ���
 *
 *  ���ꥪ�֥������Ƚ�����֥�å����顤addr��ޤ���ꥪ�֥�������
 *  �򸡺��������Υ���ǥå������֤���
 */
#ifndef OMIT_STANDARD_MEMINIB

extern int_t	search_meminib(const void *addr);

#endif /* OMIT_STANDARD_MEMINIB */

/*
 *  �����ΰ褬���ꥪ�֥������Ȥ˴ޤޤ�Ƥ��뤫�Υ����å�
 *
 *  ��Ƭ���Ϥ�base�ǥ�������size�Υ����ΰ褬����Ƭ���Ϥ�mobase�ǥ���
 *  ����mosize�Υ��ꥪ�֥������Ȥ˴ޤޤ�Ƥ������true�������Ǥʤ�
 *  ����false���֤���
 */
Inline bool_t
within_memobj(const void *base, SIZE size, void *mobase, SIZE mosize)
{
	return((SIZE)(mobase) <= (SIZE)(base) && size <= mosize
			&& (SIZE)((char *)(base) - (char *)(mobase)) <= mosize - size);
}

/*
 *  �����ΰ褬�桼�������å��ΰ�˴ޤޤ�Ƥ��뤫�Υ����å�
 *
 *  ��Ƭ���Ϥ�base�ǥ�������size�Υ����ΰ褬��p_tcb�ǻ��ꤵ��륿����
 *  �Υ桼�������å��ΰ�˴ޤޤ�Ƥ������true�������Ǥʤ�����
 *  false���֤���
 */
#ifndef USE_TSKINICTXB

Inline bool_t
within_ustack(const void *base, SIZE size, TCB *p_tcb)
{
	return(within_memobj(base, size,
					p_tcb->p_tinib->ustk, p_tcb->p_tinib->ustksz));
}

#else /* USE_TSKINICTXB */

extern bool_t	within_ustack(const void *base, SIZE size, TCB *p_tcb);

#endif /* USE_TSKINICTXB */

/*
 *  ����ؤν���߸��Υ����å�
 *
 *  �¹�����ݸ�ɥᥤ��ʥ桼���ɥᥤ��ˤ������ꤷ�������ΰ�ؤν�
 *  ���߸�����äƤ��뤫������å���������߸�����äƤ������true��
 *  �����Ǥʤ�����false���֤����¹�����ݸ�ɥᥤ�󤬥����ͥ�ɥᥤ��
 *  �λ��ϡ����δؿ���Ƥ�ǤϤʤ�ʤ���
 */
extern bool_t	probe_mem_write(const void *base, SIZE size);

/*
 *  ���꤫����ɽФ����Υ����å�
 *
 *  �¹�����ݸ�ɥᥤ��ʥ桼���ɥᥤ��ˤ������ꤷ�������ΰ�ؤ���
 *  �Ф�������äƤ��뤫������å������ɽФ�������äƤ������true��
 *  �����Ǥʤ�����false���֤����¹�����ݸ�ɥᥤ�󤬥����ͥ�ɥᥤ��
 *  �λ��ϡ����δؿ���Ƥ�ǤϤʤ�ʤ���
 */
extern bool_t	probe_mem_read(const void *base, SIZE size);

/*
 *  �����å��ΰ�˴ޤޤ�Ƥ��뤫�Υ����å�
 *
 *  ���ꤷ�������ΰ褬�����������Υ����å��ΰ�˴ޤޤ�Ƥ��뤫�ɤ���
 *  ������å������ޤޤ�Ƥ������true�������Ǥʤ�����false���֤���
 */
extern bool_t	probe_stack(const void *base, SIZE size);

/*
 *  ���ꥢ���������Υ����å��Τ���Υޥ���
 */
#ifndef PROBE_MEM_WRITE
#define PROBE_MEM_WRITE(p_var, type) \
				(ALIGN_TYPE(p_var, type) && (rundom == TACP_KERNEL \
					|| probe_mem_write((void *)(p_var), sizeof(type))))
#endif /* PROBE_MEM_WRITE */

#ifndef PROBE_MEM_READ
#define PROBE_MEM_READ(p_var, type) \
				(ALIGN_TYPE(p_var, type) && (rundom == TACP_KERNEL \
					|| probe_mem_read((void *)(p_var), sizeof(type))))
#endif /* PROBE_MEM_READ */

/*
 *  �����å��ؤΥ��������������å��Τ���Υޥ���
 */
#ifndef PROBE_STACK
#define PROBE_STACK(sp, size) \
				(ALIGN_TYPE(sp, STK_T) && probe_stack(sp, size))
#endif /* PROBE_STACK */

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  data��������������֥�å�
 */
typedef struct {
	void	*start_data;		/* data������������Ƭ���� */
	void	*end_data;			/* data���������ν�λ���� */
	void	*start_idata;		/* ������ǡ����ΰ����Ƭ���� */
} DATASECINIB;

/*
 *  data���������ο��Ƚ�����֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern const uint_t	tnum_datasec;
extern const DATASECINIB	datasecinib_table[];

/*
 *  bss��������������֥�å�
 */
typedef struct {
	void	*start_bss;			/* bss������������Ƭ���� */
	void	*end_bss;			/* bss���������ν�λ���� */
} BSSSECINIB;

/*
 *  bss���������ο��Ƚ�����֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern const uint_t	tnum_bsssec;
extern const BSSSECINIB	bsssecinib_table[];

#endif /* TOPPERS_MEMORY_H */
