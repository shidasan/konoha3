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
 *  $Id: test_diswai1.c 837 2012-12-26 15:09:59Z ertl-hiro $
 */

/* 
 *		�Ԥ��ػ߾��֤˴ؤ���ƥ���(1)
 *
 * �ڥƥ��Ȥ���Ū��
 *
 *  �����ͥ�ɥᥤ��Υ�������dis_wai��idis_wai�������������Ū�˥ƥ���
 *  ���롥
 *
 * �ڥƥ��Ȥǥ��С�������ͥ�����
 *		��NGKI1321�ϡ�NGKI1322��
 *		��NGKI1330�ϡ�NGKI1331�ϡ�NGKI1332��
 *		��NGKI1333�ϡ�NGKI1334��
 *
 * �ڹͻ���
 *
 *  �����ƥॿ�������Ф��Ƥϡ��������㳰�����ޥ������֤ϡ���ĥ�����ӥ�
 *  �������¹Ԥ��Ƥ���֤��������Ƥ��롥�����ǡ��ֳ�ĥ�����ӥ�����
 *  ���¹Ԥ��Ƥ���֡פˤϡ��¹Բ�ǽ���֤乭�����Ԥ����֤ˤʤäƤ���
 *  ����ޤ�Ǥ��롥
 *
 *  �����ǡ��������㳰�����ޥ������֤Ǥ�����Υƥ��Ȥϡ�����5�Ĥξ���
 *  �Ǽ»ܤ��롥
 *  (a) ����������ĥ�����ӥ��������¹Ԥ��Ƥ����
 *  (b) ����������ĥ�����ӥ��������¹Ԥ��Ƥ���֤˥ץꥨ��ץȤ��졤
 *		�¹Բ�ǽ���֤ˤʤäƤ������
 *  ���ּ¹Բ�ǽ���֤乭�����Ԥ����֤ˤʤäƤ�����פϡ����������ץ�
 *     ����ץȤ���ơ��¹Բ�ǽ���֤ˤʤäƤ�����Τߤǥƥ��Ȥ��롥
 *
 *  �������������㳰�����ޥ������֤Ǥʤ����Υƥ��Ȥϡ�����2�Ĥξ��֤�
 *  �»ܤ��롥
 *	(c) ���������¹Գ�����
 *	(d) ���������¹Գ��ϸ�ǡ���ĥ�����ӥ��������Ƥ�Ǥ��ʤ�����
 *
 * �ڥƥ��ȹ��ܡ�
 *
 *	(A) ¾���������Ф���dis_wai�Υ��顼����
 *		(A-1) �оݥ��������ٻ߾��֡�NGKI1330��
 *		���оݥ��������������㳰�����ޥ������֤Ǥʤ���NGKI1331��
 *		(A-2) �оݥ��������¹Գ�������NGKI1331(c)��
 *		(A-3) �оݥ��������¹Գ��ϸ�ǡ���ĥ�����ӥ��������Ƥ�Ǥ���
 *			  �����֡�NGKI1331(d)��
 *		(A-4) �оݥ��������Ԥ��ػ߾��֡�NGKI1332��
 *	(B) ¾���������Ф���dis_wai�����������NGKI1333��
 *		(B-1) �оݥ���������ĥ�����ӥ��������¹Ԥ��Ƥ���֤˥ץꥨ��
 *			  �ץȤ��졤�¹Ծ��ְʳ��ξ��֤ˤʤäƤ�����֡�NGKI1333(b)��
 *		�� ���󥰥�ץ��å��Ǥϡ�(a)�ξ��֤Ϥʤ�
 *	(C) �����������Ф���dis_wai�Υ��顼����
 *		�� ���������ϵٻ߾��֤ˤʤ뤳�ȤϤʤ�
 *		�� �����������Ф��Ƥϡ�(c)�ξ��֤Ϥʤ�
 *		(C-1) ����������ĥ�����ӥ��������Ƥ�Ǥ��ʤ����֡�NGKI1331(d)��
 *		(C-2) �����������Ԥ��ػ߾��֡�NGKI1332��
 *	(D) �����������Ф���dis_wai�����������NGKI1333��
 *		(D-1) ������������ĥ�����ӥ��������¹Ԥ��Ƥ���֡�NGKI1333(a)��
 *		�� �����������Ф���dis_wai�Ǥϡ�(b)�ξ��֤Ϥʤ�
 *		(D-2) tskid��TSK_SELF����ꤷ������NGKI1334��
 *	(E) idis_wai�Υ��顼����
 *		(E-1) �оݥ��������ٻ߾��֡�NGKI1330��
 *		���оݥ��������������㳰�����ޥ������֤Ǥʤ���NGKI1331��
 *		(E-2) �оݥ��������¹Գ�������NGKI1331(c)��
 *		(E-3) �оݥ��������¹Գ��ϸ�ǡ���ĥ�����ӥ��������Ƥ�Ǥ���
 *			  �����֡�NGKI1331(d)��
 *		(E-4) �оݥ��������Ԥ��ػ߾��֡�NGKI1332��
 *	(F) idis_wai�����������NGKI1333��
 *		(F-1) �оݥ���������ĥ�����ӥ��������¹Ԥ��Ƥ���֡�NGKI1333(a)��
 *		(F-2) �оݥ���������ĥ�����ӥ��������¹Ԥ��Ƥ���֤˥ץꥨ��
 *			  �ץȤ��졤�¹Ծ��ְʳ��ξ��֤ˤʤäƤ�����֡�NGKI1333(b)��
 *	(G) ��ĥ�����ӥ��������¿�ŸƽФ�
 *		(G-1) ¿�Ť���¦�γ�ĥ�����ӥ�������ˤ��륿�������Ф���
 *			  dis_wai��ȯ��
 *		(G-2) ¿�Ťγ�¦�γ�ĥ�����ӥ�������ˤ��륿�������Ф���
 *			  dis_wai��ȯ��
 *
 * �ڻ��ѥ꥽������
 *
 *	TASK1: �ᥤ�󥿥����������������Ф��ƥ������㳰�������׵᤹��
 *	TASK2: �ᥤ�󥿥������Ф��ƥ������㳰�������׵᤹�륿����
 *	TASK3: �¹Գ������Υ�����
 *	TASK4: �ٻ߾��֤Υ�����
 *	ALM1: �ᥤ�󥿥������Ф��ƥ������㳰�������׵᤹�����߽���
 *	EXTSVC1: ��ĥ�����ӥ�������
 *	EXTSVC2: ¿�ŤǸƤӽФ���ĥ�����ӥ�������
 *
 * �ڥƥ��ȥե�������
 *
 *	�ե�����1����ñ�˥ƥ��ȤǤ�����ܤ�ƥ���
 *				(C-1),(A-1),(A-2),(E-1),(E-2),(E-3)
 *	�ե�����2��(A-3)��ƥ���
 *	�ե�����3��(B-1)��ƥ��ȡ�(A-4)(C-2)(D-2)��ƥ��Ȥ���
 *	�ե�����4��(D-1)��ƥ���
 *	�ե�����5��(F-1)��ƥ��ȡ�(E-4)��ƥ��Ȥ���
 *	�ե�����6��(F-2)��ƥ���
 *	�ե�����7��(G-1)��ƥ���
 *	�ե�����8��(G-2)��ƥ���
 *
 * �ڥƥ��ȥ������󥹡�
 *
 *  ���Υƥ��ȥץ�����gentest�ˤ�ä��������뤳�ȤϤ������롥
 */

#include <kernel.h>
#include <test_lib.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "test_diswai1.h"

volatile uint_t	test_phase;
volatile uint_t	flag1, loop_count;
volatile bool_t	flag2;
volatile bool_t	flag3;

/*
 *	�ե�����1����ñ�˥ƥ��ȤǤ�����ܤ�ƥ���
 *		(C-1)��TASK1���顤TASK1��dis_wai��ȯ��
 *		(A-1),(A-2)��TASK1���顤TASK4��TASK3��dis_wai��ȯ��
 *		(E-1),(E-2),(E-3)������߽�����ALM1�ˤ��顤TASK4��TASK3��TASK1��
 *		idis_wai��ȯ��
 */
void
task1_phase1(void)
{
	T_RTSK	rtsk;
	ER		ercd;

	check_point(1);

	ercd = dis_wai(TASK1);		/* (C-1) */
	check_ercd(ercd, E_OBJ);

	ercd = ref_tsk(TASK1, &rtsk);	/* �Ԥ��ػ߾��֤Ǥʤ����Ȥ��ǧ(1) */
	check_ercd(ercd, E_OK);
	check_assert(rtsk.waifbd == false);

	ercd = dly_tsk(0);				/* �Ԥ��ػ߾��֤Ǥʤ����Ȥ��ǧ(2) */
	check_ercd(ercd, E_OK);

	check_point(2);

	ercd = dis_wai(TASK4);		/* (A-1) */
	check_ercd(ercd, E_OBJ);

	ercd = dis_wai(TASK3);		/* (A-2) */
	check_ercd(ercd, E_OBJ);

	check_point(3);

	flag2 = true;
	ercd = sta_alm(ALM1, 0);
	check_ercd(ercd, E_OK);
	while (flag2) ;
}

void
alarm1_phase1(void)
{
	ER		ercd;

	check_point(4);

	ercd = idis_wai(TASK4);		/* (E-1) */
	check_ercd(ercd, E_OBJ);

	ercd = idis_wai(TASK3);		/* (E-2) */
	check_ercd(ercd, E_OBJ);

	ercd = idis_wai(TASK1);		/* (E-3) */
	check_ercd(ercd, E_OBJ);

	flag2 = false;
}

/*
 *	�ե�����2��(A-3)��ƥ���
 *		TASK1����TASK2��ư����TASK2����TASK1��dis_wai��ȯ�Ԥ��롥
 */
void
task1_phase2(void)
{
	ER		ercd;

	check_point(5);

	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);
}

void
task2_phase2(void)
{
	T_RTSK	rtsk;
	ER		ercd;

	ercd = ref_tsk(TASK1, &rtsk);
	check_ercd(ercd, E_OK);
	check_assert(rtsk.texmsk == false);

	ercd = dis_wai(TASK1);		/* (A-3) */
	check_ercd(ercd, E_OBJ);

	ercd = ref_tsk(TASK1, &rtsk);
	check_ercd(ercd, E_OK);
	check_assert(rtsk.waifbd == false);

	ercd = ras_tex(TASK1, 0x0001U);
	check_ercd(ercd, E_OK);
}

/*
 *	�ե�����3��(B-1)��ƥ��ȡ�(C-2)(D-2)��ƥ��Ȥ���
 *		TASK1����EXTSVC1��ƤӽФ������δ֤�ȯ����������߽�����ALM1��
 *		����TASK2��ư���롥TASK2����TASK1��dis_wai��ȯ�Ԥ��롥����ˡ�
 *		EXTSVC1����TASK1��TSK_SELF���Ф���dis_wai��ȯ�Ԥ��ơ�(C-2)��
 *		(D-2)�Υƥ��Ȥ�»ܤ��롥
 *		�ޤ���TASK2����TASK1�˥������㳰�������׵ᤷ���������㳰�����롼
 *		����EXSVC1����Υ꥿�����˼¹Ԥ���뤳�Ȥ��ǧ���롥
 */
void
task1_phase3(void)
{
	ER		ercd;

	check_point(6);

	ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);
}

void
tex_task1_phase3(void)
{
	check_point(11);
}

void
extsvc1_phase3(void)
{
	T_RTSK	rtsk;
	ER		ercd;

	check_point(7);

	flag2 = true;
	ercd = sta_alm(ALM1, 0);
	check_ercd(ercd, E_OK);
	while (flag2) ;				/* ���δ֤�(B-1)��ƥ��� */

	ercd = ref_tsk(TASK1, &rtsk);	/* �Ԥ��ػ߾��֤Ǥ��뤳�Ȥ��ǧ(1) */
	check_ercd(ercd, E_OK);
	check_assert(rtsk.waifbd == true);

	ercd = dly_tsk(1);				/* �Ԥ��ػ߾��֤Ǥ��뤳�Ȥ��ǧ(2) */
	check_ercd(ercd, E_RLWAI);

	check_point(9);

	ercd = dis_wai(TASK1);		/* (C-2) */
	check_ercd(ercd, E_QOVR);

	ercd = dis_wai(TSK_SELF);	/* (D-2) */
	check_ercd(ercd, E_QOVR);

	check_point(10);
}

void
alarm1_phase3(void)
{
	ER		ercd;

	ercd = iact_tsk(TASK2);
	check_ercd(ercd, E_OK);
}

void
task2_phase3(void)
{
	ER		ercd;

	check_point(8);

	ercd = dis_wai(TASK1);		/* (B-1) */
	check_ercd(ercd, E_OK);

	ercd = dis_wai(TASK1);		/* (A-4) */
	check_ercd(ercd, E_QOVR);

	ercd = ras_tex(TASK1, 0x0002U);
	check_ercd(ercd, E_OK);

	flag2 = false;
}

/*
 *	�ե�����4��(D-1)��ƥ���
 *		TASK1����EXTSVC1��ƤӽФ�����������TASK1��dis_wai��ȯ�Ԥ��롥
 */
void
task1_phase4(void)
{
	ER		ercd;

	check_point(12);

	ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);
}

void
extsvc1_phase4()
{
	T_RTSK	rtsk;
	ER		ercd;

	check_point(13);

	ercd = dis_wai(TASK1);		/* (D-1) */
	check_ercd(ercd, E_OK);

	ercd = ref_tsk(TASK1, &rtsk);	/* �Ԥ��ػ߾��֤Ǥ��뤳�Ȥ��ǧ(1) */
	check_ercd(ercd, E_OK);
	check_assert(rtsk.waifbd == true);

	ercd = dly_tsk(1);				/* �Ԥ��ػ߾��֤Ǥ��뤳�Ȥ��ǧ(2) */
	check_ercd(ercd, E_RLWAI);

	check_point(14);
}

/*
 *	�ե�����5��(F-1)��ƥ��ȡ�(E-4)��ƥ��Ȥ���
 *		TASK1����EXTSVC1��ƤӽФ���EXTSVC1�μ¹����ȯ����������߽���
 *		��ALM1�ˤ���TASK1��idis_wai��ȯ�Ԥ��롥����ˡ�TASK1��idis_wai
 *		��ȯ�Ԥ��ơ�(E-4) �Υƥ��Ȥ�»ܤ��롥
 */
void
task1_phase5(void)
{
	ER		ercd;

	check_point(15);

	ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);
}

void
extsvc1_phase5()
{
	ER		ercd;

	check_point(16);

	flag2 = true;
	ercd = sta_alm(ALM1, 0);
	check_ercd(ercd, E_OK);
	while (flag2) ;
}

void
alarm1_phase5(void)
{
	ER		ercd;

	check_point(17);

	ercd = idis_wai(TASK1);		/* (F-1) */
	check_ercd(ercd, E_OK);

	ercd = idis_wai(TASK1);		/* (E-4) */
	check_ercd(ercd, E_QOVR);

	flag2 = false;
}

/*
 *	�ե�����6��(F-2)��ƥ���
 *		TASK1����EXTSVC1��ƤӽФ������δ֤�ȯ����������߽�����ALM1��
 *		����TASK2��ư���롥TASK2�μ¹����ȯ����������߽�����ALM2��
 *		����TASK1��idis_wai��ȯ�Ԥ��롥
 */
void
task1_phase6(void)
{
	ER		ercd;

	check_point(18);

	ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);
}

void
extsvc1_phase6()
{
	ER		ercd;

	check_point(19);

	flag2 = true;
	ercd = sta_alm(ALM1, 0);
	check_ercd(ercd, E_OK);
	while (flag2) ;
}

void
alarm1_phase6(void)
{
	ER		ercd;

	check_point(20);

	ercd = iact_tsk(TASK2);
	check_ercd(ercd, E_OK);

	flag2 = false;
}

void
task2_phase6(void)
{
	ER		ercd;

	check_point(21);

	flag3 = true;
	ercd = sta_alm(ALM2, 0);
	check_ercd(ercd, E_OK);
	while (flag3) ;
}

void
alarm2_phase6(void)
{
	ER		ercd;

	check_point(22);

	ercd = idis_wai(TASK1);			/* (F-2) */
	check_ercd(ercd, E_OK);

	flag3 = false;
}

/*
 *	�ե�����7��(G-1)��ƥ���
 *		TASK1����EXTSVC1��ƤӽФ�������ˤ�������EXTSVC2��ƤӽФ���
 *		EXTSVC2��¹����ȯ����������߽�����ALM1�ˤ���TASK1��idis_wai
 *		��ȯ�Ԥ��롥
 *		����ˡ�EXTSVC1����ä���ˡ�EXTSVC1����TASK1��dis_wai��Ԥ���
 *		���顼�ˤʤ뤳�Ȥ��ǧ���롥
 *		�ޤ���ALM1����TASK1�˥������㳰�������׵ᤷ���������㳰�����롼
 *		����EXSVC1����Υ꥿�����˼¹Ԥ���뤳�Ȥ��ǧ���롥
 */
void
task1_phase7(void)
{
	ER		ercd;

	check_point(23);

	ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);
}

void
tex_task1_phase7(void)
{
	check_point(29);
}

void
extsvc1_phase7(void)
{
	ER		ercd;

	check_point(24);

	ercd = cal_svc(TFN_EXTSVC2, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);

	ercd = dis_wai(TASK1);
	check_ercd(ercd, E_QOVR);

	check_point(28);
}

void
extsvc2_phase7(void)
{
	ER		ercd;

	check_point(25);

	flag2 = true;
	ercd = sta_alm(ALM1, 0);
	check_ercd(ercd, E_OK);
	while (flag2) ;

	check_point(27);
}

void
alarm1_phase7(void)
{
	ER		ercd;

	check_point(26);

	ercd = idis_wai(TASK1);
	check_ercd(ercd, E_OK);

	ercd = iras_tex(TASK1, 0x0002U);
	check_ercd(ercd, E_OK);

	flag2 = false;
}

/*
 *	�ե�����8��(G-2)��ƥ���
 *		TASK1����EXTSVC1��ƤӽФ�����������TASK1��dis_wai��ȯ�Ԥ��롥
 *		³����EXTSVC1����EXTSVC2��ƤӽФ���EXTSVC2��¹����ȯ��������
 *		���߽�����ALM1�ˤ���TASK1��idis_wai��ȯ�Ԥ���ʥ��顼�ˤʤ�ˡ�
 *		����ˡ�EXTSVC1����ä���ˡ�EXTSVC1����TASK1��dis_wai��Ԥ���
 *		���顼�ˤʤ뤳�Ȥ��ǧ���롥
 *		�ޤ���ALM1����TASK1�˥������㳰�������׵ᤷ���������㳰�����롼
 *		����EXSVC1����Υ꥿�����˼¹Ԥ���뤳�Ȥ��ǧ���롥
 */
void
task1_phase8(void)
{
	ER		ercd;

	check_point(30);

	ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);
}

void
tex_task1_phase8(void)
{
	check_point(36);
}

void
extsvc1_phase8(void)
{
	ER		ercd;

	check_point(31);

	ercd = dis_wai(TASK1);
	check_ercd(ercd, E_OK);

	ercd = cal_svc(TFN_EXTSVC2, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);

	ercd = dis_wai(TASK1);
	check_ercd(ercd, E_QOVR);

	check_point(35);
}

void
extsvc2_phase8(void)
{
	ER		ercd;

	check_point(32);

	flag2 = true;
	ercd = sta_alm(ALM1, 0);
	check_ercd(ercd, E_OK);
	while (flag2) ;

	check_point(34);
}

void
alarm1_phase8(void)
{
	ER		ercd;

	check_point(33);

	ercd = idis_wai(TASK1);
	check_ercd(ercd, E_QOVR);

	ercd = iras_tex(TASK1, 0x0002U);
	check_ercd(ercd, E_OK);

	flag2 = false;
}

/*
 *  �ƽ���ñ�̤�ʬ������
 */
void
task1(intptr_t exinf)
{
	ER		ercd;

	ercd = ena_tex();
	check_ercd(ercd, E_OK);

	test_phase = 1U;
	task1_phase1();

	test_phase = 2U;
	task1_phase2();

	test_phase = 3U;
	task1_phase3();

	test_phase = 4U;
	task1_phase4();

	test_phase = 5U;
	task1_phase5();

	test_phase = 6U;
	task1_phase6();

	test_phase = 7U;
	task1_phase7();

	test_phase = 8U;
	task1_phase8();

	check_finish(37);
}

void
tex_task1(TEXPTN texptn, intptr_t exinf)
{
	if ((texptn & 0x0001U) != 0) {
		flag2 = false;
	}
	if ((texptn & 0x0002U) != 0) {
		switch (test_phase) {
		case 3U:
			tex_task1_phase3();
			break;
		case 7U:
			tex_task1_phase7();
			break;
		case 8U:
			tex_task1_phase8();
			break;
		}
	}
}

void
task2(intptr_t exinf)
{
	switch (test_phase) {
	case 2U:
		task2_phase2();
		break;
	case 3U:
		task2_phase3();
		break;
	case 6U:
		task2_phase6();
		break;
	default:
		check_point(0);
		break;
	}
}

void
task3(intptr_t exinf)
{
}

void
task4(intptr_t exinf)
{
}

void
alarm1_handler(intptr_t exinf)
{
	switch (test_phase) {
	case 1U:
		alarm1_phase1();
		break;
	case 3U:
		alarm1_phase3();
		break;
	case 5U:
		alarm1_phase5();
		break;
	case 6U:
		alarm1_phase6();
		break;
	case 7U:
		alarm1_phase7();
		break;
	case 8U:
		alarm1_phase8();
		break;
	default:
		check_point(0);
		break;
	}
}

void
alarm2_handler(intptr_t exinf)
{
	switch (test_phase) {
	case 6U:
		alarm2_phase6();
		break;
	default:
		check_point(0);
		break;
	}
}

ER_UINT
extsvc1_routine(intptr_t par1, intptr_t par2, intptr_t par3,
								intptr_t par4, intptr_t par5, ID cdmid)
{
	switch (test_phase) {
	case 3U:
		extsvc1_phase3();
		break;
	case 4U:
		extsvc1_phase4();
		break;
	case 5U:
		extsvc1_phase5();
		break;
	case 6U:
		extsvc1_phase6();
		break;
	case 7U:
		extsvc1_phase7();
		break;
	case 8U:
		extsvc1_phase8();
		break;
	default:
		check_point(0);
		break;
	}
	return(E_OK);
}

ER_UINT
extsvc2_routine(intptr_t par1, intptr_t par2, intptr_t par3,
								intptr_t par4, intptr_t par5, ID cdmid)
{
	switch (test_phase) {
	case 7U:
		extsvc2_phase7();
		break;
	case 8U:
		extsvc2_phase8();
		break;
	default:
		check_point(0);
		break;
	}
	return(E_OK);
}
