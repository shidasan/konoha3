/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 * 
 *  Copyright (C) 2012 by Embedded and Real-Time Systems Laboratory
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
 */

/*
 *  �����ޥɥ饤�С�STM32P207�ѡ�
 */

#include "kernel_impl.h"
#include "time_event.h"
#include <sil.h>
#include "target_timer.h"

#ifdef TOPPERS_TARGET_SUPPORT_OVRHDR

/*
 *	�����Х�󥿥��ޤν��������
 *
 *	�����ޤ��������롥
 */
void
target_ovrtimer_initialize(intptr_t exinf)
{
    /* ������� */
	sil_orw((void*)RCC_APB1ENR, APB1ENR_TIM2_EN);
    sil_wrh_mem((void *)TIMX_CR1(OVRTIMER_BASE), (CR1_OPM | CR1_DIR));
    sil_wrh_mem((void *)TIMX_PSC(OVRTIMER_BASE), (SYS_CLOCK / 1000000));
    sil_orh((void *)TIMX_EGR(OVRTIMER_BASE), EGR_UG);
    sil_andh((void *)TIMX_SR(OVRTIMER_BASE), ~SR_UIF);
    /* �����ߵ��� */
    sil_wrh_mem((void *)TIMX_DIER(OVRTIMER_BASE), DIER_UIE);
}

/*
 *	�����Х�󥿥��ޤν�λ����
 *
 *	�����ޤ�ư���λ���롥
 */
void
target_ovrtimer_terminate(intptr_t exinf)
{
    /* �����ޤ���� */
    sil_andh((void *)TIMX_CR1(OVRTIMER_BASE), ~CR1_CEN);

    /* �������׵�򥯥ꥢ */
    sil_andh((void *)TIMX_SR(OVRTIMER_BASE), ~SR_UIF);
}

/*
 *	�����Х�󥿥��ޤε�ư����
 *
 *	�����ޤ�ư���롥
 */
void
target_ovrtimer_start(OVRTIM ovrtim)
{
	CLOCK	 cyc = OVRTIMER_CLOCK(ovrtim) - 1;

    /*
     *  �����޼��������ꤷ�������ޤ�ư��򳫻Ϥ��롥
     */
    assert(cyc <= MAX_OVRTIMER_CLOCK);          /* �����޾���ͤΥ����å� */

    sil_wrw_mem((void *)TIMX_CNT(OVRTIMER_BASE), cyc);   /* �����󥿡��򥻥å� */

    /* �������׵�򥯥ꥢ */
    sil_andh((void *)TIMX_SR(OVRTIMER_BASE), ~SR_UIF);

    /* �����ޥ������� */
    sil_orh((void *)TIMX_CR1(OVRTIMER_BASE), CR1_CEN);
}

/*
 *	�����Х�󥿥��ޤ���߽���
 *
 *	�����ޤ�ư�����ߤ����롥
 */
OVRTIM
target_ovrtimer_stop(void)
{
    OVRTIM rest;

    /* �����ޤ���� */
    sil_andh((void *)TIMX_CR1(OVRTIMER_BASE), ~CR1_CEN);
    /* �������׵�򥯥ꥢ */
    sil_andh((void *)TIMX_SR(OVRTIMER_BASE), ~SR_UIF);

	rest = (OVRTIM)sil_rew_mem((void *)TIMX_CNT(OVRTIMER_BASE));

    if(rest < 0){
        return 1;
    } else {
        return (OVRTIMER_USEC(rest + 1));
    }
}

/*
 *	�����Х�󥿥��ޤλĤ���֤��ɽФ�
 */
OVRTIM
target_ovrtimer_get_current(void)
{
    OVRTIM rest;

	rest = (OVRTIM)sil_rew_mem((void *)TIMX_CNT(OVRTIMER_BASE));

    if(rest < 0){
        return 0;
    } else {
        return (OVRTIMER_USEC(rest + 1));
    }
}

/*
 *	�����Х�󥿥��޳���ߥϥ�ɥ�
 */
void
target_ovrtimer_handler(void)
{
	i_begin_int(INTNO_OVRTIMER);
	call_ovrhdr();
	i_end_int(INTNO_OVRTIMER);
}

#endif /* TOPPERS_TARGET_SUPPORT_OVRHDR */


