/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
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
 *  $Id: test_tex8.c 837 2012-12-26 15:09:59Z ertl-hiro $
 */

/* 
 *		�������㳰�����˴ؤ���ƥ���(8)
 *
 * �ڥƥ��Ȥ���Ū��
 *
 *  �������㳰�����롼����Ϣ³���Ƽ¹Գ��Ϥ��줿���ˡ��������Υ�����
 *  ���ΰ�λ����̤����ä��ʤ����Ȥ��ǧ���롥�ޤ����������㳰�����롼
 *  ���󤫤�Υ꥿������ˡ��ǥ����ѥå����Ƥ����˥�������enatex��
 *  false�ˤ��Ƥ����������������������Ƥ��뤫���ǧ���롥
 *
 *  �����ͥ�ɥᥤ���°���륿�����ȡ��桼���ɥᥤ���°���륿������ξ
 *  �Ԥ��Ф��ơ�Ʊ���Υƥ��Ȥ�»ܤ��롥
 *
 * �ڹͻ���
 *
 *  �������㳰�����롼���󤫤�Υ꥿������ˡ��ǥ����ѥå����Ƥ�����
 *  ��������enatex��false�ˤ��Ƥ����������������������Ƥ��뤫�ϡ�����
 *  ��ˡ�ǳ�ǧ���롥
 *
 *  �������㳰�����롼�������ǡ��ǥ����ѥå��ػ߾��֤��ĥ������㳰��
 *  �����ľ��֤Ȥ����塤��ͥ���٥�������ư���롥���λ����Ǥϡ���ͥ��
 *  �٥������ؤ��ڤ괹���ʤ����������㳰�����롼���󤫤�꥿���󤹤�
 *  �ȡ��ǥ����ѥå��ػߤ�������졤��ͥ���٥��������ڤ괹��롥��ͥ��
 *  �٥������ϡ��оݥ��������Ф��ƥ������㳰�������׵ᤷ���塤��λ����
 *  (*)��enatex��false�ˤ����������������������Ƥ��ʤ��ȡ���ͥ���٥�
 *  ���������оݥ��������ڤ괹����ǥ����ѥå���ˤ�ꡤ�������㳰����
 *  �롼���󤬼¹Գ��Ϥ��졤�����å��ΰ�λ����̤����ä��롥������Ф�
 *  �ơ�enatex��false�ˤ����������������������Ƥ���ȡ������å��ΰ��
 *  �����̤����ä��ʤ���
 *
 *  �����ǡ��嵭��(*)�ξ����򷫤��֤��������Ƥ⡤�����å��ΰ����­����
 *  ���ʤ����Ȥ��ǧ���롥
 *
 * �ڥƥ��ȹ��ܡ�
 *
 *	(A) �����ͥ�ɥᥤ���°���륿���������������㳰�����롼�����Ϣ³
 *		���Ƽ¹Գ��Ϥ�������򷫤��֤������ˡ������å��ΰ����­����
 *		���ʤ�
 *  (B) �����ͥ�ɥᥤ���°���륿�������Ф��ơ�(*)�ξ����򷫤��֤�����
 *		��ˡ������å��ΰ����­�������ʤ�
 *	(C) �桼���ɥᥤ���°���륿���������������㳰�����롼�����Ϣ³��
 *		�Ƽ¹Գ��Ϥ�������򷫤��֤������ˡ������å��ΰ����­������
 *		�ʤ�
 *  (D) �桼���ɥᥤ���°���륿�������Ф��ơ�(*)�ξ����򷫤��֤������
 *		�ˡ������å��ΰ����­�������ʤ�
 *
 * �ڻ��ѥ꥽������
 *
 *	TASK1: �����ͥ�ɥᥤ���°����ƥ����оݤΥ�����
 *	TASK2: TASK1�˥������㳰�������׵᤹���ͥ���٥�����
 *	TASK3: �桼���ɥᥤ���°����ƥ����оݤΥ�����
 *	TASK4: TASK3�˥������㳰�������׵᤹���ͥ���٥�����
 *
 * �ڥƥ��ȥ������󥹡�
 *
 *  ���Υƥ��ȥץ�����gentest�ˤ�ä��������뤳�ȤϤ������롥
 */

#include <kernel.h>
#include <test_lib.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "test_tex8.h"

#define STASK_TEX_COUNT		((uint_t) STACK_SIZE)
#define UTASK_TEX_COUNT		((uint_t) STACK_SIZE)
//#define UTASK_TEX_COUNT		200

static uint_t	tex_start_count;

void
task1(intptr_t exinf)
{
	ER		ercd;

	check_point(1);

	ercd = ena_tex();
	check_ercd(ercd, E_OK);

	/*
	 *  �ƥ��ȹ���(A)�Υƥ���
	 */
	tex_start_count = 0U;
	ercd = ras_tex(TASK1, 0x0001);
	check_ercd(ercd, E_OK);
	check_assert(tex_start_count == STASK_TEX_COUNT);

	check_point(2);

	/*
	 *  �ƥ��ȹ���(B)�Υƥ���
	 */
	tex_start_count = 0U;
	ercd = ras_tex(TASK1, 0x0002);
	check_ercd(ercd, E_OK);
	check_assert(tex_start_count == STASK_TEX_COUNT);

	check_point(3);

	/*
	 *  ���θ�Υƥ��Ȥ�TASK3�Ǽ»�
	 */
	ercd = act_tsk(TASK3);
	check_ercd(ercd, E_OK);

	ercd = ext_tsk();
	check_point(0);
}

void
tex_task1(TEXPTN texptn, intptr_t exinf)
{
	ER		ercd;

	/*
	 *  �����å��ΰ��;͵�����뤳�Ȥ򡤳�ĥ�����ӥ��������ȤäƳ�ǧ
	 *  ���롥
	 */
	ercd = cal_svc(TFN_EXTSVC, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);

#ifdef DEBUG_LOG
	if (tex_start_count % 50 == 0) {
		syslog_2(LOG_NOTICE, "%d: sp = %x", tex_start_count, &ercd);
	}
#endif /* DEBUG_LOG */

	tex_start_count += 1;
	if (tex_start_count < STASK_TEX_COUNT) {
		switch (texptn) {
		case 0x0001:
			ercd = ras_tex(TASK1, 0x0001);
			check_ercd(ercd, E_OK);
			break;

		case 0x0002:
			ercd = dis_dsp();
			check_ercd(ercd, E_OK);

			ercd = ena_tex();
			check_ercd(ercd, E_OK);

			ercd = act_tsk(TASK2);
			check_ercd(ercd, E_OK);
			break;
		}
	}
}

void
task2(intptr_t exinf)
{
	ER		ercd;

	ercd = ras_tex(TASK1, 0x0002);
	check_ercd(ercd, E_OK);
	
	ercd = ext_tsk();
	check_point(0);
}

void
task3(intptr_t exinf)
{
	ER		ercd;

	check_point(4);

	ercd = ena_tex();
	check_ercd(ercd, E_OK);

	/*
	 *  �ƥ��ȹ���(C)�Υƥ���
	 */
	tex_start_count = 0U;
	ercd = ras_tex(TASK3, 0x0001);
	check_ercd(ercd, E_OK);
	check_assert(tex_start_count == UTASK_TEX_COUNT);

	check_point(5);

	/*
	 *  �ƥ��ȹ���(D)�Υƥ���
	 */
	tex_start_count = 0U;
	ercd = ras_tex(TASK3, 0x0002);
	check_ercd(ercd, E_OK);
	check_assert(tex_start_count == UTASK_TEX_COUNT);

	check_finish(6);
}

void
tex_task3(TEXPTN texptn, intptr_t exinf)
{
	ER		ercd;

	/*
	 *  �����ƥॹ���å��ΰ��;͵�����뤳�Ȥ򡤳�ĥ�����ӥ��������Ȥ�
	 *  �Ƴ�ǧ���롥
	 *
	 *  �桼���������ˤ����ơ������ƥॹ���å��ΰ褬���뤳�ȤϤʤ��Ϥ�
	 *  �����������ͥ�ΥХ��ˤ�����������ǽ���Ϥ��뤿�ᡤǰ�Τ����
	 *  ǧ���Ƥ��롥�������������ƥॹ���å��ΰ褬�����Ƥ��ޤ��Х��ϡ�
	 *  ����Ǥϸ��ФǤ��ʤ����ԲĲ��ư��򤹤�ˡ�
	 */
	ercd = cal_svc(TFN_EXTSVC, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);

#ifdef DEBUG_LOG
	if (tex_start_count % 50 == 0) {
		syslog_2(LOG_NOTICE, "%d: sp = %x", tex_start_count, &ercd);
	}
#endif /* DEBUG_LOG */

	tex_start_count += 1;
	if (tex_start_count < UTASK_TEX_COUNT) {
		switch (texptn) {
		case 0x0001:
			ercd = ras_tex(TASK3, 0x0001);
			check_ercd(ercd, E_OK);
			break;

		case 0x0002:
			ercd = dis_dsp();
			check_ercd(ercd, E_OK);

			ercd = ena_tex();
			check_ercd(ercd, E_OK);

			ercd = act_tsk(TASK4);
			check_ercd(ercd, E_OK);
			break;
		}
	}
}

void
task4(intptr_t exinf)
{
	ER		ercd;

	ercd = ras_tex(TASK3, 0x0002);
	check_ercd(ercd, E_OK);
	
	ercd = ext_tsk();
	check_point(0);
}

ER_UINT
extsvc_routine(intptr_t par1, intptr_t par2, intptr_t par3,
								intptr_t par4, intptr_t par5, ID cdmid)
{
	return(E_OK);
}
