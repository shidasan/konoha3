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

/*
 *	MPU�ɥ饤��
 */

#include "kernel_impl.h"
#include "task.h"
#include "memory.h"
#include <sil.h>
#include "kernel_cfg.h"
#include "target_mpu.h"

void
target_mpu_initialize(void)
{
    char *shared_mem_base;
    char *shared_mem_attr;

    sil_wrw_mem((void *)(MPU_REGNO), (uint32_t)(0));
    /*
     *  �ΰ�0: ��ͭ�꡼���ΰ�
     */
    shared_mem_base = shared_meminib_table[0];
    shared_mem_attr = shared_meminib_table[1];
    sil_wrw_mem((void *)(MPU_REGBASE), (uint32_t)shared_mem_base);
    sil_wrw_mem((void *)(MPU_REGATR),  (uint32_t)shared_mem_attr);

    /*
     *  �ΰ�1: ��ͭ�꡼�ɥ饤���ΰ�
     */
    shared_mem_base = shared_meminib_table[2];
    shared_mem_attr = shared_meminib_table[3];
    sil_wrw_mem((void *)(MPU_REGBASE), (uint32_t)shared_mem_base);
    sil_wrw_mem((void *)(MPU_REGATR),  (uint32_t)shared_mem_attr);

    /*
     *  �ΰ�2: ��ͭ�꡼����ͭ�饤���ΰ�����
     */
    shared_mem_base = shared_meminib_table[4];
    shared_mem_attr = shared_meminib_table[5];
    sil_wrw_mem((void *)(MPU_REGBASE), (uint32_t)shared_mem_base);
    sil_wrw_mem((void *)(MPU_REGATR),  (uint32_t)shared_mem_attr);

    /*
     *  MPUͭ��
     *  �ø��⡼�ɤǤϥǥե���ȤΥ���ޥå�
     *  �ϥ�ɥ���Ǥ�MPU̵��
     */
    sil_wrw_mem((void *)(MPU_CR), (uint32_t)(MPU_CR_PRIVDEFENA | MPU_CR_ENABLE));
}

void
target_mpu_exc_handler(void *p_excinf)
{
    syslog(LOG_EMERG, "MPU EXCEPTION OCCURED!!");
    while(1);
}

// �������㳰�¹Գ��ϻ������å������ϥ�ɥ�
void
target_emulate_texrtn_handler(void *p_excinf)
{
    syslog(LOG_EMERG, "User stack is no space at prepare texrtn.");
    while(1);
}

// �������㳰�꥿����������å������ϥ�ɥ�
void
target_emulate_ret_tex_handler(void *p_excinf)
{
    syslog(LOG_EMERG, "User stack is no space at return texrtn.");
    while(1);
}

