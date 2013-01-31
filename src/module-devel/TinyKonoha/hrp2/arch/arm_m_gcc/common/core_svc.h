/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 *	
 *	Copyright (C) 2012 by Embedded and Real-Time Systems Laboratory
 *				Graduate School of Information Science, Nagoya Univ., JAPAN
 *	
 *	�嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *	�����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *	�ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *	(1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *		��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *		����������˴ޤޤ�Ƥ��뤳�ȡ�
 *	(2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *		�ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *		�ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *		��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *	(3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *		�ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *		�ȡ�
 *	  (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *		  �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *	  (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *		  ��𤹤뤳�ȡ�
 *	(4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *		������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *		�ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *		ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *		���դ��뤳�ȡ�
 *	
 *	�ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *	���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *	���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *	�������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *	����Ǥ�����ʤ���
 *	
 */

#ifndef TOPPERS_CORE_SVC_H
#define TOPPERS_CORE_SVC_H

#ifndef TOPPERS_MACRO_ONLY


/*
 *  �����ͥ�Υ����ӥ�������Υ��󥿥ե�����
 *
 *  ������å��쥸����
 *    r4 : �ؿ�������
 *    r0 - r3 : ������4�Ĥޤǡ�
 *    r12 : ��5����
 *    r5-r9��caller saved
 */
extern char call_svc_entry;

#define CAL_SVC_0(TYPE, FNCD) \
	register TYPE  r0 asm("r0"); \
	register FN    r4 asm("r4") = FNCD; \
    register char *entry asm("r8") = &call_svc_entry; \
	Asm ( \
        "orr r8, r8, #0x01\n\t" \
        "blx r8\n\t" \
        "nop\n\t" \
		:"=r"(r0),"+r"(r4) \
		:"r"(entry),"r"(r4)\
		:"lr","r1","r2","r3","r12","r5","r6","r9","r10" \
	); \
	return((TYPE)(r0));

#define CAL_SVC_1(TYPE, FNCD, TYPE1, PAR1) \
	register TYPE1 r0 asm("r0") = (TYPE1)(PAR1); \
	register FN    r4 asm("r4") = FNCD; \
    register char *entry asm("r8") = &call_svc_entry; \
	Asm ( \
        "orr r8, r8, #0x01\n\t" \
        "blx r8\n\t" \
        "nop\n\t" \
		:"+r"(r0),"+r"(r4) \
		:"r"(entry),"r"(r0),"r"(r4)\
		:"lr","r1","r2","r3","r12","r5","r6","r9","r10" \
	); \
	return((TYPE)(r0));

#define CAL_SVC_2(TYPE, FNCD, TYPE1, PAR1, TYPE2, PAR2) \
	register TYPE1 r0 asm("r0") = (TYPE1)(PAR1); \
	register TYPE2 r1 asm("r1") = (TYPE2)(PAR2); \
	register FN    r4 asm("r4") = FNCD; \
    register char *entry asm("r8") = &call_svc_entry; \
	Asm ( \
        "orr r8, r8, #0x01\n\t" \
        "blx r8\n\t" \
        "nop\n\t" \
		:"+r"(r0),"+r"(r1),"+r"(r4) \
		:"r"(entry),"r"(r0),"r"(r1),"r"(r4)\
		:"lr","r2","r3","r12","r5","r6","r9","r10" \
	); \
	return((TYPE)(r0));

#define CAL_SVC_3(TYPE, FNCD, TYPE1, PAR1, \
							TYPE2, PAR2, TYPE3, PAR3) \
	register TYPE1 r0 asm("r0") = (TYPE1)(PAR1); \
	register TYPE2 r1 asm("r1") = (TYPE2)(PAR2); \
	register TYPE3 r2 asm("r2") = (TYPE3)(PAR3); \
	register FN    r4 asm("r4") = FNCD; \
    register char *entry asm("r8") = &call_svc_entry; \
	Asm ( \
        "orr r8, r8, #0x01\n\t" \
        "blx r8\n\t" \
        "nop\n\t" \
		:"=r"(r0),"+r"(r1),"+r"(r2),"+r"(r4) \
		:"r"(entry),"r"(r0),"r"(r1),"r"(r2),"r"(r4)\
		:"lr","r3","r12","r5","r6","r9","r10" \
	); \
	return((TYPE)(r0));

#define CAL_SVC_4(TYPE, FNCD, TYPE1, PAR1, TYPE2, PAR2, \
								TYPE3, PAR3, TYPE4, PAR4) \
	register TYPE1 r0 asm("r0") = (TYPE1)(PAR1); \
	register TYPE2 r1 asm("r1") = (TYPE2)(PAR2); \
	register TYPE3 r2 asm("r2") = (TYPE3)(PAR3); \
	register TYPE4 r3 asm("r3") = (TYPE4)(PAR4); \
	register FN    r4 asm("r4") = FNCD; \
    register char *entry asm("r8") = &call_svc_entry; \
	Asm ( \
        "orr r8, r8, #0x01\n\t" \
        "blx r8\n\t" \
        "nop\n\t" \
		:"=r"(r0),"+r"(r1),"+r"(r2),"+r"(r3),"+r"(r4) \
		:"r"(entry),"r"(r0),"r"(r1),"r"(r2),"r"(r3),"r"(r4)\
		:"lr","r12","r5","r6","r9","r10" \
	); \
	return((TYPE)(r0));

#define CAL_SVC_5(TYPE, FNCD, TYPE1, PAR1, TYPE2, PAR2, \
						TYPE3, PAR3, TYPE4, PAR4, TYPE5, PAR5) \
	register TYPE1 r0 asm("r0") = (TYPE1)(PAR1); \
	register TYPE2 r1 asm("r1") = (TYPE2)(PAR2); \
	register TYPE3 r2 asm("r2") = (TYPE3)(PAR3); \
	register TYPE4 r3 asm("r3") = (TYPE4)(PAR4); \
	register TYPE5 r12 asm("r12") = (TYPE5)(PAR5); \
	register FN    r4 asm("r4") = FNCD; \
    register char *entry asm("r8") = &call_svc_entry; \
	Asm ( \
        "orr r8, r8, #0x01\n\t" \
        "blx r8\n\t" \
        "nop\n\t" \
		:"=r"(r0),"+r"(r1),"+r"(r2),"+r"(r3),"+r"(r12),"+r"(r4) \
		:"r"(entry),"r"(r0),"r"(r1),"r"(r2),"r"(r3),"r"(r12),"r"(r4)\
		:"lr","r5","r6","r9","r10" \
	); \
	return((TYPE)(r0));

#define CAL_SVC_0M(TYPE, FNCD) \
	register TYPE  r0 asm("r0"); \
	register FN    r4 asm("r4") = FNCD; \
    register char *entry asm("r8") = &call_svc_entry; \
	Asm ( \
        "orr r8, r8, #0x01\n\t" \
        "blx r8\n\t" \
        "nop\n\t" \
		:"=r"(r0),"+r"(r4) \
		:"r"(entry),"r"(r4)\
		:"memory","lr","r1","r2","r3","r12","r5","r6","r9","r10" \
	); \
	return((TYPE)(r0));

#define CAL_SVC_1M(TYPE, FNCD, TYPE1, PAR1) \
	register TYPE1 r0 asm("r0") = (TYPE1)(PAR1); \
	register FN    r4 asm("r4") = FNCD; \
    register char *entry asm("r8") = &call_svc_entry; \
	Asm ( \
        "orr r8, r8, #0x01\n\t" \
        "blx r8\n\t" \
        "nop\n\t" \
		:"+r"(r0),"+r"(r4) \
		:"r"(entry),"r"(r0),"r"(r4)\
		:"memory","lr","r1","r2","r3","r12","r5","r6","r9","r10" \
	); \
	return((TYPE)(r0));

#define CAL_SVC_2M(TYPE, FNCD, TYPE1, PAR1, TYPE2, PAR2) \
	register TYPE1 r0 asm("r0") = (TYPE1)(PAR1); \
	register TYPE2 r1 asm("r1") = (TYPE2)(PAR2); \
	register FN    r4 asm("r4") = FNCD; \
    register char *entry asm("r8") = &call_svc_entry; \
	Asm ( \
        "orr r8, r8, #0x01\n\t" \
        "blx r8\n\t" \
        "nop\n\t" \
		:"+r"(r0),"+r"(r1),"+r"(r4) \
		:"r"(entry),"r"(r0),"r"(r1),"r"(r4)\
		:"memory","lr","r2","r3","r12","r5","r6","r9","r10" \
	); \
	return((TYPE)(r0));

#define CAL_SVC_3M(TYPE, FNCD, TYPE1, PAR1, \
							TYPE2, PAR2, TYPE3, PAR3) \
	register TYPE1 r0 asm("r0") = (TYPE1)(PAR1); \
	register TYPE2 r1 asm("r1") = (TYPE2)(PAR2); \
	register TYPE3 r2 asm("r2") = (TYPE3)(PAR3); \
	register FN    r4 asm("r4") = FNCD; \
    register char *entry asm("r8") = &call_svc_entry; \
	Asm ( \
        "orr r8, r8, #0x01\n\t" \
        "blx r8\n\t" \
        "nop\n\t" \
		:"=r"(r0),"+r"(r1),"+r"(r2),"+r"(r4) \
		:"r"(entry),"r"(r0),"r"(r1),"r"(r2),"r"(r4)\
		:"memory","lr","r3","r12","r5","r6","r9","r10" \
	); \
	return((TYPE)(r0));

#define CAL_SVC_4M(TYPE, FNCD, TYPE1, PAR1, TYPE2, PAR2, \
								TYPE3, PAR3, TYPE4, PAR4) \
	register TYPE1 r0 asm("r0") = (TYPE1)(PAR1); \
	register TYPE2 r1 asm("r1") = (TYPE2)(PAR2); \
	register TYPE3 r2 asm("r2") = (TYPE3)(PAR3); \
	register TYPE4 r3 asm("r3") = (TYPE4)(PAR4); \
	register FN    r4 asm("r4") = FNCD; \
    register char *entry asm("r8") = &call_svc_entry; \
	Asm ( \
        "orr r8, r8, #0x01\n\t" \
        "blx r8\n\t" \
        "nop\n\t" \
		:"=r"(r0),"+r"(r1),"+r"(r2),"+r"(r3),"+r"(r4) \
		:"r"(entry),"r"(r0),"r"(r1),"r"(r2),"r"(r3),"r"(r4)\
		:"memory","lr","r12","r5","r6","r9","r10" \
	); \
	return((TYPE)(r0));

#define CAL_SVC_5M(TYPE, FNCD, TYPE1, PAR1, TYPE2, PAR2, \
						TYPE3, PAR3, TYPE4, PAR4, TYPE5, PAR5) \
	register TYPE1 r0 asm("r0") = (TYPE1)(PAR1); \
	register TYPE2 r1 asm("r1") = (TYPE2)(PAR2); \
	register TYPE3 r2 asm("r2") = (TYPE3)(PAR3); \
	register TYPE4 r3 asm("r3") = (TYPE4)(PAR4); \
	register TYPE5 r12 asm("r12") = (TYPE5)(PAR5); \
	register FN    r4 asm("r4") = FNCD; \
    register char *entry asm("r8") = &call_svc_entry; \
	Asm ( \
        "orr r8, r8, #0x01\n\t" \
        "blx r8\n\t" \
        "nop\n\t" \
		:"=r"(r0),"+r"(r1),"+r"(r2),"+r"(r3),"+r"(r12),"+r"(r4) \
		:"r"(entry),"r"(r0),"r"(r1),"r"(r2),"r"(r3),"r"(r12),"r"(r4)\
		:"memory","lr","r5","r6","r9","r10" \
	); \
	return((TYPE)(r0));

#ifndef TOPPERS_SVC_CALL
#include "gcc/tool_svc.h"
#endif /* TOPPERS_SVC_CALL */

Inline ER_UINT
cal_svc(FN fncd, intptr_t par1, intptr_t par2,
        intptr_t par3, intptr_t par4, intptr_t par5)
{
    if(fncd > 0){
        CAL_SVC_5M(FN, fncd, intptr_t, par1, intptr_t, par2, 
                intptr_t, par3, intptr_t, par4, intptr_t, par5);
    } else {
        return (E_RSFN);
    }
}

#endif /* TOPPERS_MACRO_ONLY */


#endif /* TOPPERS_CORE_SVC_H */

