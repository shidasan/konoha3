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
 *  $Id: test_tex5.c 837 2012-12-26 15:09:59Z ertl-hiro $
 */

/* 
 *		�������㳰�����˴ؤ���ƥ���(5)
 *
 * �ڥƥ��Ȥ���Ū��
 *
 *  �����ͥ�ɥᥤ���°���륿�������Ф��ơ�CPU��å����֤β����unl_cpu��
 *  �ȳ�ĥ�����ӥ�������롼���󤫤�Υ꥿����ˤ�륿�����㳰�����롼
 *  ����μ¹Գ��Ͻ���������Ū�˥ƥ��Ȥ��롥
 *
 * �ڥƥ��ȹ��ܡ�
 *
 *	(A) CPU��å����֤β���ˤ�륿�����㳰�����롼����μ¹Գ���
 *		(A-1) 7��郎·�äơ��������㳰�����롼���󤬼¹Գ���
 *	(B) CPU��å����֤β��������·��ʤ���郎���ꡤ�������㳰�����롼
 *		���󤬼¹Գ��Ϥ���ʤ�
 *		(B-1) �оݥ��������������㳰�����ػ߾���
 *		(B-2) �оݥ���������α�㳰�װ���0
 *		(B-3) �оݥ��������¹Ծ��֤Ǥʤ�
 *		(B-4) �����ͥ���٥ޥ�����������֤Ǥʤ�
 *		(B-5) �оݥ��������������㳰�����ޥ������֡ʳ�ĥ�����ӥ�������
 *			  ��¹Ԥ��Ƥ���֡�
 *	(C) ��ĥ�����ӥ�������롼���󤫤�Υ꥿����ˤ�륿�����㳰�����롼
 *		����μ¹Գ���
 *		(C-1) 7��郎·�äơ��������㳰�����롼���󤬼¹Գ���
 *	(D) ��ĥ�����ӥ�������롼���󤫤�Υ꥿���������·��ʤ���郎��
 *		�ꡤ�������㳰�����롼���󤬼¹Գ��Ϥ���ʤ�
 *		(D-1) �оݥ��������������㳰�����ػ߾���
 *		(D-2) �оݥ���������α�㳰�װ���0
 *		(D-3) �оݥ��������¹Ծ��֤Ǥʤ�
 *		(D-4) �󥿥�������ƥ����Ȥ��¹Ԥ���Ƥ���
 *		(D-5) �����ͥ���٥ޥ�����������֤Ǥʤ�
 *		(D-6) CPU��å����֤Ǥ���
 *		(D-7) �оݥ��������������㳰�����ޥ������֡ʳ�ĥ�����ӥ�������
 *			  ��¹Ԥ��Ƥ���֡�
 *
 * �ڻ��ѥ꥽������
 *
 *	TASK1: �ᥤ��Υ�������CPU��å����֤β����Ԥ�������
 *	TASK2: �оݥ��������¹Ծ��֤Ǥʤ�����ƥ��Ȥ��뤿��Υ�����
 *	CPUEXC: CPU�㳰�ϥ�ɥ�
 *	EXTSVC1: ��ĥ�����ӥ�������1
 *	EXTSVC2: ��ĥ�����ӥ�������2
 *
 * �ڥƥ��ȥ������󥹡�
 *
 *	== TASK1��ͥ���١�10��==
 *	1:	cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)
 *	== EXTSVC1-1��1���ܡ�==
 *	2:	ena_tex()
 *		ras_tex(TSK_SELF, 0x0001)
 *		chg_ipm(TIPM_ENAALL)
 *		loc_cpu()
 *	3:	unl_cpu()								... (B-5)
 *	4:	loc_cpu()
 *	5:	RETURN(E_OK)							... (D-6)
 *	== TASK1��³����==
 *	6:	unl_cpu()								... (A-1)
 *	== TASK1-TEX-1��1���ܡ�==
 *	7:	assert(texptn == 0x0001)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *		RETURN
 *	== TASK1��³����==
 *	8:	cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)
 *	== EXTSVC1-2��2���ܡ�==
 *	9:	ena_tex()
 *		chg_ipm(TIPM_ENAALL)
 *		loc_cpu()
 *		RETURN(E_OK)
 *	== TASK1��³����==
 *	10:	unl_cpu()								... (B-2)
 *	11:	cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)
 *	== EXTSVC1-3��3���ܡ�==
 *	12:	dis_tex()
 *		ras_tex(TSK_SELF, 0x0002)
 *		chg_ipm(TIPM_ENAALL)
 *		loc_cpu()
 *		RETURN(E_OK)
 *	== TASK1��³����==
 *	13:	unl_cpu()								... (B-1)
 *	14:	cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)
 *	== EXTSVC1-4��4���ܡ�==
 *	15:	ena_tex()
 *		ras_tex(TSK_SELF, 0x0004)
 *		chg_ipm(TMAX_INTPRI)
 *		loc_cpu()
 *		RETURN(E_OK)
 *	== TASK1��³����==
 *	16:	unl_cpu()								... (B-4)
 *		chg_ipm(TIPM_ENAALL)
 *	== TASK1-TEX-2��2���ܡ�==
 *	17:	assert(texptn == 0x0006)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *		RETURN
 *	== TASK1��³����==
 *	18:	act_tsk(TASK2)
 *		slp_tsk()
 *	== TASK2��ͥ���١�11��==
 *	19:	ena_tex()
 *		wup_tsk(TASK1)
 *	== TASK1��³����==
 *	20:	ras_tex(TASK2, 0x0008)
 *		loc_cpu()
 *	21:	unl_cpu()								... (B-3)
 *	22:	cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)
 *	== EXTSVC1-5��5���ܡ�==
 *	23:	RETURN(E_OK)							... (D-3)
 *	== TASK1��³����==
 *	24:	cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)
 *	== EXTSVC1-6��6���ܡ�==
 *	25:	ena_tex()
 *		ras_tex(TSK_SELF, 0x0010)
 *		chg_ipm(TIPM_ENAALL)
 *	26:	RETURN(E_OK)							... (C-1)(D-3)
 *	== TASK1-TEX-3��3���ܡ�==
 *	27:	assert(texptn == 0x0010)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *		RETURN
 *	== TASK1��³����==
 *	28:	cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)
 *	== EXTSVC1-7��7���ܡ�==
 *	29:	ena_tex()
 *		chg_ipm(TIPM_ENAALL)
 *	30:	RETURN(E_OK)							... (D-2)
 *	== TASK1��³����==
 *	31:	cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)
 *	== EXTSVC1-8��8���ܡ�==
 *	32:	dis_tex()
 *		ras_tex(TSK_SELF, 0x0020)
 *		chg_ipm(TIPM_ENAALL)
 *	33:	RETURN(E_OK)							... (D-1)
 *	== TASK1��³����==
 *	34:	cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)
 *	== EXTSVC1-9��9���ܡ�==
 *	35:	ena_tex()
 *		ras_tex(TSK_SELF, 0x0040)
 *		chg_ipm(TMAX_INTPRI)
 *	36:	RETURN(E_OK)							... (D-5)
 *	== TASK1��³����==
 *	37:	cal_svc(TFN_EXTSVC2, 0, 0, 0, 0, 0)
 *	== EXTSVC2-1��1���ܡ�==
 *	38:	cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)
 *	== EXTSVC1-10��10���ܡ�==
 *	39:	ena_tex()
 *		ras_tex(TSK_SELF, 0x0080)
 *		chg_ipm(TIPM_ENAALL)
 *	40:	RETURN(E_OK)							... (D-7)
 *	== EXTSVC2-1��³����==
 *	41:	RETURN(E_OK)
 *	== TASK1-TEX-4��4���ܡ�==
 *	42:	assert(texptn == 0x00e0)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *		RETURN
 *	== TASK1��³����==
 *	43:	ena_tex()
 *		chg_ipm(TIPM_ENAALL)
 *		DO(RAISE_CPU_EXCEPTION)
 *	== CPUEXC ==
 *	44:	cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)
 *	== EXTSVC1-11��11���ܡ�==
 *	45:	iras_tex(TASK1, 0x0100)
 *	46:	RETURN(E_OK)							... (D-4)
 *	== CPUEXC��³����==
 *	47:	RETURN
 *	== TASK1-TEX-5��5���ܡ�==
 *	48:	assert(texptn == 0x0100)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *	49:	ext_tsk()
 *	== TASK2-TEX ==
 *	50:	assert(texptn == 0x0008)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *	51:	END
 */

#include <kernel.h>
#include <test_lib.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "test_tex5.h"

void
cpuexc_handler(void *p_excinf)
{
	ER		ercd;

	check_point(44);

	ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);

	check_point(47);

	return;

	check_point(0);
}

static uint_t	extsvc1_count = 0;

ER_UINT
extsvc1_routine(intptr_t par1, intptr_t par2, intptr_t par3,
								intptr_t par4, intptr_t par5, ID cdmid)
{
	ER		ercd;

	switch (++extsvc1_count) {
	case 1:
		check_point(2);

		ercd = ena_tex();
		check_ercd(ercd, E_OK);

		ercd = ras_tex(TSK_SELF, 0x0001);
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TIPM_ENAALL);
		check_ercd(ercd, E_OK);

		ercd = loc_cpu();
		check_ercd(ercd, E_OK);

		check_point(3);

		ercd = unl_cpu();
		check_ercd(ercd, E_OK);

		check_point(4);

		ercd = loc_cpu();
		check_ercd(ercd, E_OK);

		check_point(5);

		return(E_OK);

		check_point(0);

	case 2:
		check_point(9);

		ercd = ena_tex();
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TIPM_ENAALL);
		check_ercd(ercd, E_OK);

		ercd = loc_cpu();
		check_ercd(ercd, E_OK);

		return(E_OK);

		check_point(0);

	case 3:
		check_point(12);

		ercd = dis_tex();
		check_ercd(ercd, E_OK);

		ercd = ras_tex(TSK_SELF, 0x0002);
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TIPM_ENAALL);
		check_ercd(ercd, E_OK);

		ercd = loc_cpu();
		check_ercd(ercd, E_OK);

		return(E_OK);

		check_point(0);

	case 4:
		check_point(15);

		ercd = ena_tex();
		check_ercd(ercd, E_OK);

		ercd = ras_tex(TSK_SELF, 0x0004);
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TMAX_INTPRI);
		check_ercd(ercd, E_OK);

		ercd = loc_cpu();
		check_ercd(ercd, E_OK);

		return(E_OK);

		check_point(0);

	case 5:
		check_point(23);

		return(E_OK);

		check_point(0);

	case 6:
		check_point(25);

		ercd = ena_tex();
		check_ercd(ercd, E_OK);

		ercd = ras_tex(TSK_SELF, 0x0010);
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TIPM_ENAALL);
		check_ercd(ercd, E_OK);

		check_point(26);

		return(E_OK);

		check_point(0);

	case 7:
		check_point(29);

		ercd = ena_tex();
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TIPM_ENAALL);
		check_ercd(ercd, E_OK);

		check_point(30);

		return(E_OK);

		check_point(0);

	case 8:
		check_point(32);

		ercd = dis_tex();
		check_ercd(ercd, E_OK);

		ercd = ras_tex(TSK_SELF, 0x0020);
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TIPM_ENAALL);
		check_ercd(ercd, E_OK);

		check_point(33);

		return(E_OK);

		check_point(0);

	case 9:
		check_point(35);

		ercd = ena_tex();
		check_ercd(ercd, E_OK);

		ercd = ras_tex(TSK_SELF, 0x0040);
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TMAX_INTPRI);
		check_ercd(ercd, E_OK);

		check_point(36);

		return(E_OK);

		check_point(0);

	case 10:
		check_point(39);

		ercd = ena_tex();
		check_ercd(ercd, E_OK);

		ercd = ras_tex(TSK_SELF, 0x0080);
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TIPM_ENAALL);
		check_ercd(ercd, E_OK);

		check_point(40);

		return(E_OK);

		check_point(0);

	case 11:
		check_point(45);

		ercd = iras_tex(TASK1, 0x0100);
		check_ercd(ercd, E_OK);

		check_point(46);

		return(E_OK);

		check_point(0);
	}
	check_point(0);
	return(E_SYS);
}

static uint_t	extsvc2_count = 0;

ER_UINT
extsvc2_routine(intptr_t par1, intptr_t par2, intptr_t par3,
								intptr_t par4, intptr_t par5, ID cdmid)
{
	ER		ercd;

	switch (++extsvc2_count) {
	case 1:
		check_point(38);

		ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
		check_ercd(ercd, E_OK);

		check_point(41);

		return(E_OK);

		check_point(0);
	}
	check_point(0);
	return(E_SYS);
}

void
task1(intptr_t exinf)
{
	ER		ercd;

	check_point(1);

	ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);

	check_point(6);

	ercd = unl_cpu();
	check_ercd(ercd, E_OK);

	check_point(8);

	ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);

	check_point(10);

	ercd = unl_cpu();
	check_ercd(ercd, E_OK);

	check_point(11);

	ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);

	check_point(13);

	ercd = unl_cpu();
	check_ercd(ercd, E_OK);

	check_point(14);

	ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);

	check_point(16);

	ercd = unl_cpu();
	check_ercd(ercd, E_OK);

	ercd = chg_ipm(TIPM_ENAALL);
	check_ercd(ercd, E_OK);

	check_point(18);

	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(20);

	ercd = ras_tex(TASK2, 0x0008);
	check_ercd(ercd, E_OK);

	ercd = loc_cpu();
	check_ercd(ercd, E_OK);

	check_point(21);

	ercd = unl_cpu();
	check_ercd(ercd, E_OK);

	check_point(22);

	ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);

	check_point(24);

	ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);

	check_point(28);

	ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);

	check_point(31);

	ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);

	check_point(34);

	ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);

	check_point(37);

	ercd = cal_svc(TFN_EXTSVC2, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);

	check_point(43);

	ercd = ena_tex();
	check_ercd(ercd, E_OK);

	ercd = chg_ipm(TIPM_ENAALL);
	check_ercd(ercd, E_OK);

	RAISE_CPU_EXCEPTION;

	check_point(0);
}

static uint_t	tex_task1_count = 0;

void
tex_task1(TEXPTN texptn, intptr_t exinf)
{
	ER		ercd;

	switch (++tex_task1_count) {
	case 1:
		check_point(7);
		check_assert(texptn == 0x0001);
		check_state(false, false, TIPM_ENAALL, false, false, true);

		return;

		check_point(0);

	case 2:
		check_point(17);
		check_assert(texptn == 0x0006);
		check_state(false, false, TIPM_ENAALL, false, false, true);

		return;

		check_point(0);

	case 3:
		check_point(27);
		check_assert(texptn == 0x0010);
		check_state(false, false, TIPM_ENAALL, false, false, true);

		return;

		check_point(0);

	case 4:
		check_point(42);
		check_assert(texptn == 0x00e0);
		check_state(false, false, TIPM_ENAALL, false, false, true);

		return;

		check_point(0);

	case 5:
		check_point(48);
		check_assert(texptn == 0x0100);
		check_state(false, false, TIPM_ENAALL, false, false, true);

		check_point(49);

		ercd = ext_tsk();
		check_ercd(ercd, E_OK);

		check_point(0);
	}
	check_point(0);
}

void
task2(intptr_t exinf)
{
	ER		ercd;

	check_point(19);

	ercd = ena_tex();
	check_ercd(ercd, E_OK);

	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(0);
}

void
tex_task2(TEXPTN texptn, intptr_t exinf)
{
	ER		ercd;

	check_point(50);
	check_assert(texptn == 0x0008);
	check_state(false, false, TIPM_ENAALL, false, false, true);

	check_finish(51);

	check_point(0);
}
