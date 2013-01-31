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
 *  $Id: test_extsvc1.c 837 2012-12-26 15:09:59Z ertl-hiro $
 */

/* 
 *		��ĥ�����ӥ�������˴ؤ���ƥ���(1)
 *
 * �ڥƥ��Ȥ���Ū��
 *
 *  ��ĥ�����ӥ������뵡ǽ������Ū�˥ƥ��Ȥ��롥
 *
 * �ڥƥ��ȼ»ܾ����ա�
 *
 *  ���Υƥ��Ȥϡ���ĥ�����ӥ�������θƤӽФ����˥����å��ΰ褬��­��
 *  ��E_NOMEM���֤륱�����ȡ��ͥ��ȥ�٥뤬255��Ķ����E_SYS���֤륱����
 *  ��ƥ��Ȥ��Ƥ��롥���Υƥ��Ȥκݤξ���򡤰ʲ���2�ĤΥ�å������ʿ�
 *  �ͤϥ������åȤˤ��ۤʤ�ˤǽ��Ϥ��Ƥ��롥
 *
 *  cal_svc returns E_NOMEM when svclevel = 23
 *  cal_svc returns E_SYS when svclevel = 255
 *
 *  ���Υƥ��Ȥ��������»ܤ���ˤϡ��������Υ����å���������Ŭ�ڤ�����
 *  ����ɬ�פ����롥Ŭ�ڤʥ����å��������ϥ������åȰ�¸�Ȥʤ뤿�ᡤ����
 *  ���åȤˤ�äƤϡ������å���������ʲ��Τ褦��Ĵ������ɬ�פ����롥
 *
 *  �嵭��E_NOMEM����𤵤��٤��Ȥ����E_SYS����𤵤�ƥ��顼��ߤ�
 *  ����ˤϡ�TASK1�Υ����ƥॹ���å����������礭�����롥���Τ��ᡤ
 *  OVERFLOW_STACK_SIZE��ǥե���ȡ�STACK_SIZE�ˤ��⾮�����ͤ������
 *  ��ɬ�פ����롥
 *
 *  �դ�E_SYS����𤵤��٤��Ȥ����E_NOMEM����𤵤�ƥ��顼��ߤ���
 *  ���ˤϡ�TASK2�Υ����ƥॹ���å������������������롥���Τ��ᡤ
 *  NON_OVERFLOW_STACK_SIZE��ǥե���ȡ�STACK_SIZE * 20�ˤ����礭��
 *  �ͤ��������ɬ�פ����롥�դˡ�RAM���̤���­������ˤϡ��������ͤ�
 *  ���ꤷ��ư���ǧ����ɬ�פ����롥
 *
 * �ڥƥ��Ȥǥ��С�������ͥ�����
 *		��NGKI1243�ϡ�NGKI0189��
 *		��NGKI3160�ϡ�NGKI3162�ϡ�NGKI3165�ϡ�NGKI3166�ϡ�NGKI3167��
 *		��NGKI3192�ϡ�NGKI3193�ϡ�NGKI3194��
 *		��NGKI3195�ϡ�NGKI3197�ϡ�NGKI3198��
 *
 * �ڹͻ���
 *
 * �ڥƥ��ȹ��ܡ�
 *
 *	(A) ref_tex�Ǥγ�ĥ�����ӥ�������Υͥ��ȥ�٥�λ��ȡ�NGKI1243��
 *		(A-1) �оݥ���������ĥ�����ӥ��������ƤӽФ��Ƥ��ʤ���
 *		(A-2) �оݥ���������ĥ�����ӥ��������ƤӽФ��Ƥ��ꡤ�ͥ�����
 *			  ����1�λ�
 *		(A-3) �оݥ���������ĥ�����ӥ��������ƤӽФ��Ƥ��ꡤ�ͥ�����
 *			  ����2�λ�
 *		�� �оݥ�������¾�������ǥƥ��Ȥ���
 *	(B) �ø��⡼�ɤ�����ĥ�����ӥ��������ƤӽФ����NGKI3160��
 *		(B-1) �����ƥॿ���������ĥ�����ӥ��������Ƥ�
 *		(B-2) �󥿥�������ƥ����Ȥ����ĥ�����ӥ��������Ƥ�
 *		(B-3) ��ĥ�����ӥ������뤫���ĥ�����ӥ��������Ƥ�
 *	(C) ��ĥ�����ӥ������뤬���������μ��ΤȤʤ��NGKI3162��
 *		(C-1) �桼������������ƤӽФ�����ĥ�����ӥ������뤫�顤������
 *			  ��ɥᥤ��Τߤ����������Ǥ��륪�֥������Ȥ˥��������Ǥ���
 *	(D) cdmid�ˤϡ���ĥ�����ӥ��������ƤӽФ�������ñ�̤�°����ɥᥤ
 *		��ID���Ϥ�����NGKI3165��
 *		(D-1) �����ƥॿ��������ƤӽФ������ˤ�TDOM_KERNEL
 *		(D-2) �󥿥�������ƥ����Ȥ���ƤӽФ������ˤ�TDOM_KERNEL
 *		(D-3) ��ĥ�����ӥ������뤫��ƤӽФ������ˤ�TDOM_KERNEL
 *		(D-4) �桼������������ƤӽФ������ˤϡ����줬°�����ݸ�ɥᥤ��
 *	(E) par1��par5�ˤϡ���ĥ�����ӥ���������Ф���ѥ�᡼�����Ϥ����
 *		��NGKI3166��
 *	(F) cal_svc�Υ��顼����
 *		(F-1) fncd��0��NGKI3192��
 *		(F-2) fncd��TMAX_FNCD�����礭����NGKI3193��
 *		(F-3) fncd���Ф����ĥ�����ӥ������뤬̤�����NGKI3194��
 *		(F-4) �����å��λĤ��ΰ褬��­��NGKI3197��
 *		(F-5) �ͥ��ȥ�٥뤬��¤�Ķ�����NGKI3198��
 *	(G) ��ĥ�����ӥ�������μ¹Գ���ľ��ξ��֡�NGKI0189��
 *		(G-1) CPU��å����֤ǸƤӽФ������
 *		(G-2) CPU��å�������֤ǸƤӽФ������
 *		(G-3) �����ͥ���٥ޥ�����TMAX_INTPRI�ξ��֤ǸƤӽФ������
 *		(G-4) �����ͥ���٥ޥ�����������֤ǸƤӽФ������
 *		(G-5) �ǥ����ѥå��ػ߾��֤ǸƤӽФ������
 *		(G-6) �ǥ����ѥå����ľ��֤ǸƤӽФ������
 *	(H) cal_svc������
 *		(H-1) ��ĥ�����ӥ�����������ͤ��֤���NGKI3195��
 *	(I) ��ĥ�����ӥ�������Υ꥿���󳫻�ľ��ξ��֡�NGKI0189��
 *		(I-1) CPU��å����֤ǥ꥿���󤷤����
 *		(I-2) CPU��å�������֤ǥ꥿���󤷤����
 *		(I-3) �����ͥ���٥ޥ���������Ǥʤ����֤ǥ꥿���󤷤����
 *		(I-4) �����ͥ���٥ޥ�����������֤ǥ꥿���󤷤����
 *		(I-5) �ǥ����ѥå��ػ߾��֤ǥ꥿���󤷤����
 *		(I-6) �ǥ����ѥå����ľ��֤ǥ꥿���󤷤����
 *	(J) TMAX_FNCD����ĥ�����ӥ�������ε�ǽ�ֹ�κ����ͤ���������
 *		��NGKI3167��
 *
 * �ڻ��ѥ꥽������
 *
 *	TASK1: �桼������������ĥ�����ӥ��������ƤӽФ�
 *	TASK2: �����ƥॿ��������ĥ�����ӥ��������ƤӽФ�
 *	TASK3: �оݥ��������Ф��ƾ��ֻ��Ȥ��뤿��Υ�����
 *	ALM1: ��ĥ�����ӥ��������ƤӽФ�
 *	EXTSVC1: ��ĥ�����ӥ�������
 *	EXTSVC2: ¿�ŤǸƤӽФ���ĥ�����ӥ�������
 *	EXTSVC3: ���顼�ˤʤ�ޤ�¿�Ť˸ƤӽФ������ӥ�������
 *
 * �ڥƥ��ȥ������󥹡�
 *
 *	== TASK1��ͥ���١�10��==
 *	1:	act_tsk(TASK2) -> E_OACV
 *		act_tsk(TASK3)
 *	== TASK3-1��ͥ���١�9��1���ܡ�==
 *	2:	ref_tsk(TASK1, &rtsk)
 *		assert(rtsk.svclevel == 0)							... (A-1)
 *		ext_tsk()
 *	== TASK1��³����==
 *	3:	cal_svc(0, 0, 0, 0, 0, 0) -> E_RSFN					... (F-1)
 *		cal_svc(TFN_EXTSVC3+1, 0, 0, 0, 0, 0) -> E_RSFN		... (F-2)(J)
 *		cal_svc(TFN_EXTSVC0, 0, 0, 0, 0, 0) -> E_RSFN		... (F-3)
 *		cal_svc(TFN_EXTSVC1, PAR1_1, PAR1_2, PAR1_3, PAR1_4, PAR1_5) \
 *															... (G-2)(G-4)(G-6)
 *	== EXTSVC1-1��1���ܡ�==
 *	4:	state(false, false, TIPM_ENAALL, false, false, true)
 *		assert(par1 == PAR1_1 && par2 == PAR1_2 && par3 == PAR1_3 \
 *				&& par4 == PAR1_4 && par5 == PAR1_5)		... (E)
 *		assert(cdmid == DOM1)								... (D-4)
 *		act_tsk(TASK3)
 *	== TASK3-2��2���ܡ�==
 *	5:	ref_tsk(TASK1, &rtsk)
 *		assert(rtsk.svclevel == 1)							... (A-2)
 *		ext_tsk()
 *	== EXTSVC1-1��³����==
 *	6:	cal_svc(TFN_EXTSVC2, PAR2_1, PAR2_2, PAR2_3, PAR2_4, PAR2_5) ... (B-3)
 *	== EXTSVC2-1��1���ܡ�==
 *	7:	state(false, false, TIPM_ENAALL, false, false, true)
 *		assert(par1 == PAR2_1 && par2 == PAR2_2 && par3 == PAR2_3 \
 *				&& par4 == PAR2_4 && par5 == PAR2_5)		... (E)
 *		assert(cdmid == TDOM_KERNEL)						... (D-3)
 *		act_tsk(TASK3)
 *	== TASK3-3��3���ܡ�==
 *	8:	ref_tsk(TASK1, &rtsk)
 *		assert(rtsk.svclevel == 2)							... (A-2)
 *		ext_tsk()
 *	== EXTSVC2-1��³����==
 *	9:	dis_dsp()
 *		chg_ipm(TMAX_INTPRI)
 *		loc_cpu()
 *		RETURN(E_OK)										... (I-1)(I-3)(I-5)
 *	== EXTSVC1-1��³����==
 *	10:	state(false, true, TMAX_INTPRI, true, true, true)
 *		cal_svc(TFN_EXTSVC2, 0, 0, 0, 0, 0) -> E_PAR		... (G-1)(G-3)(G-5)
 *	== EXTSVC2-2��2���ܡ�==
 *	11:	state(false, true, TMAX_INTPRI, true, true, true)
 *		unl_cpu()
 *		chg_ipm(TIPM_ENAALL)
 *		RETURN(E_PAR)										... (H-1)(I-2)(I-4)
 *	== EXTSVC1-1��³����==
 *	12:	state(false, false, TIPM_ENAALL, true, true, true)
 *		ena_dsp()											... (I-6)
 *		act_tsk(TASK2)										... (C-1)
 *		RETURN(E_OK)
 *	== TASK1��³����==
 *	13:	state(false, false, TIPM_ENAALL, false, false, true)
 *		cal_svc(TFN_EXTSVC3, 0, 0, 0, 0, 0) -> E_NOMEM		... (F-4)
 *	.. ������ EXTSVC3 ���¹Ԥ���뤬�����ν����ϼ�񤭤���
 *	== TASK1��³����==
 *	14:	ext_tsk()
 *	== TASK2��ͥ���١�10��==
 *	15:	act_tsk(TASK3)
 *	== TASK3-4��4���ܡ�==
 *	16:	ref_tsk(TASK2, &rtsk)
 *		assert(rtsk.svclevel == 0)							... (A-1)
 *		ext_tsk()
 *	== TASK2��³����==
 *	17:	cal_svc(0, 0, 0, 0, 0, 0) -> E_RSFN					... (F-1)
 *		cal_svc(TFN_EXTSVC3+1, 0, 0, 0, 0, 0) -> E_RSFN		... (F-2)
 *		cal_svc(TFN_EXTSVC0, 0, 0, 0, 0, 0) -> E_RSFN		... (F-3)
 *		cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)					... (B-1)
 *	== EXTSVC1-2��2���ܡ�==
 *	18:	state(false, false, TIPM_ENAALL, false, false, true)
 *		assert(cdmid == TDOM_KERNEL)						... (D-1)
 *		act_tsk(TASK3)
 *	== TASK3-5��5���ܡ�==
 *	19:	ref_tsk(TASK2, &rtsk)
 *		assert(rtsk.svclevel == 1)							... (A-2)
 *		ext_tsk()
 *	== EXTSVC1-2��³����==
 *	20:	RETURN(E_OK)
 *	== TASK2��³����==
 *	21:	cal_svc(TFN_EXTSVC3, 0, 0, 0, 0, 0) -> E_SYS		... (F-4)
 *	.. ������ EXTSVC3 ���¹Ԥ���뤬�����ν����ϼ�񤭤���
 *	== TASK2��³����==
 *	22:	sta_alm(ALM1, 0U)
 *		dly_tsk(1U)
 *	== ALM1 ==
 *	23:	cal_svc(0, 0, 0, 0, 0, 0) -> E_RSFN					... (F-1)
 *		cal_svc(TFN_EXTSVC3+1, 0, 0, 0, 0, 0) -> E_RSFN		... (F-2)
 *		cal_svc(TFN_EXTSVC0, 0, 0, 0, 0, 0) -> E_RSFN		... (F-3)
 *		cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)					... (B-2)
 *	== EXTSVC1-3��3���ܡ�==
 *	24:	state_i(true, false, false, true, true)
 *		assert(cdmid == TDOM_KERNEL)						... (D-2)
 *		RETURN(E_OK)
 *	== ALM1��³����==
 *	25:	state_i(true, false, false, true, true)
 *		RETURN
 *	== TASK2��³����==
 *	26:	END
 */

#include <kernel.h>
#include <test_lib.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include "kernel_cfg.h"
#include "test_extsvc1.h"

#define PAR1_1		((intptr_t) 1)
#define PAR1_2		((intptr_t) 2)
#define PAR1_3		((intptr_t) 3)
#define PAR1_4		((intptr_t) 4)
#define PAR1_5		((intptr_t) 5)

#define PAR2_1		((intptr_t) -5)
#define PAR2_2		((intptr_t) -4)
#define PAR2_3		((intptr_t) -3)
#define PAR2_4		((intptr_t) -2)
#define PAR2_5		((intptr_t) -1)

/*
 *  extsvc3_routine����������ʤ�
 *
 *  ���γ�ĥ�����ӥ�������Ǥϡ��ͥ��ȥ�٥�κ����ƥ��Ȥ��뤿�ᡤ��
 *  ���椫���ĥ�����ӥ��������Ƥ�Ǥ⡤�������Ƥ٤�Ȥϸ¤�ʤ���
 */

ER_UINT
extsvc3_routine(intptr_t par1, intptr_t par2, intptr_t par3,
								intptr_t par4, intptr_t par5, ID cdmid)
{
	ER		ercd, ercd1;
	T_RTSK	rtsk;

	ercd = cal_svc(TFN_EXTSVC3, 0, 0, 0, 0, 0);
	if (ercd < 0) {
		ercd1 = ref_tsk(TSK_SELF, &rtsk);
		check_ercd(ercd1, E_OK);

		if (SERCD(ercd) == -1) {
			/*
			 *  �Ǥ�ͥ��Ȥο�����ĥ�����ӥ��������1�٤�����å�������
			 *  ���Ϥ��롥
			 *
			 *  cal_svc��E_SYS���֤������Ǥϡ���ĥ�����ӥ�������ƽФ�
			 *  ��ޤ�syslog�ؿ��ϻȤ��ʤ����ᡤsyslog_wri_log��ؿ���
			 *  �Ф����롥
			 */
			{
				SYSLOG	logbuf;
				char	*msg = "cal_svc returns %s when svclevel = %d";

				logbuf.logtype = LOG_TYPE_COMMENT;
				logbuf.loginfo[0] = (intptr_t) msg;
				logbuf.loginfo[1] = (intptr_t) itron_strerror(ercd);
				logbuf.loginfo[2] = (intptr_t) rtsk.svclevel;
				(void) _syslog_syslog_wri_log(LOG_NOTICE, &logbuf);
			}
			ercd = ERCD(MERCD(ercd), -2);
		}
		if (rtsk.svclevel == 1) {
			return(ERCD(MERCD(ercd), -1));
		}
	}
	return(ercd);
}

/*
 *  �������鲼�����������
 */

void
alarm1_handler(intptr_t exinf)
{
	ER		ercd;

	check_point(23);

	ercd = cal_svc(0, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_RSFN);

	ercd = cal_svc(TFN_EXTSVC3+1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_RSFN);

	ercd = cal_svc(TFN_EXTSVC0, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_RSFN);

	ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);

	check_point(25);
	check_state_i(true, false, false, true, true);

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
		check_point(4);
		check_state(false, false, TIPM_ENAALL, false, false, true);
		check_assert(par1 == PAR1_1 && par2 == PAR1_2 && par3 == PAR1_3 && par4 == PAR1_4 && par5 == PAR1_5);
		check_assert(cdmid == DOM1);

		ercd = act_tsk(TASK3);
		check_ercd(ercd, E_OK);

		check_point(6);

		ercd = cal_svc(TFN_EXTSVC2, PAR2_1, PAR2_2, PAR2_3, PAR2_4, PAR2_5);
		check_ercd(ercd, E_OK);

		check_point(10);
		check_state(false, true, TMAX_INTPRI, true, true, true);

		ercd = cal_svc(TFN_EXTSVC2, 0, 0, 0, 0, 0);
		check_ercd(ercd, E_PAR);

		check_point(12);
		check_state(false, false, TIPM_ENAALL, true, true, true);

		ercd = ena_dsp();
		check_ercd(ercd, E_OK);

		ercd = act_tsk(TASK2);
		check_ercd(ercd, E_OK);

		return(E_OK);

		check_point(0);

	case 2:
		check_point(18);
		check_state(false, false, TIPM_ENAALL, false, false, true);
		check_assert(cdmid == TDOM_KERNEL);

		ercd = act_tsk(TASK3);
		check_ercd(ercd, E_OK);

		check_point(20);

		return(E_OK);

		check_point(0);

	case 3:
		check_point(24);
		check_state_i(true, false, false, true, true);
		check_assert(cdmid == TDOM_KERNEL);

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
		check_point(7);
		check_state(false, false, TIPM_ENAALL, false, false, true);
		check_assert(par1 == PAR2_1 && par2 == PAR2_2 && par3 == PAR2_3 && par4 == PAR2_4 && par5 == PAR2_5);
		check_assert(cdmid == TDOM_KERNEL);

		ercd = act_tsk(TASK3);
		check_ercd(ercd, E_OK);

		check_point(9);

		ercd = dis_dsp();
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TMAX_INTPRI);
		check_ercd(ercd, E_OK);

		ercd = loc_cpu();
		check_ercd(ercd, E_OK);

		return(E_OK);

		check_point(0);

	case 2:
		check_point(11);
		check_state(false, true, TMAX_INTPRI, true, true, true);

		ercd = unl_cpu();
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TIPM_ENAALL);
		check_ercd(ercd, E_OK);

		return(E_PAR);

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

	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OACV);

	ercd = act_tsk(TASK3);
	check_ercd(ercd, E_OK);

	check_point(3);

	ercd = cal_svc(0, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_RSFN);

	ercd = cal_svc(TFN_EXTSVC3+1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_RSFN);

	ercd = cal_svc(TFN_EXTSVC0, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_RSFN);

	ercd = cal_svc(TFN_EXTSVC1, PAR1_1, PAR1_2, PAR1_3, PAR1_4, PAR1_5);
	check_ercd(ercd, E_OK);

	check_point(13);
	check_state(false, false, TIPM_ENAALL, false, false, true);

	ercd = cal_svc(TFN_EXTSVC3, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_NOMEM);

	check_point(14);

	ercd = ext_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}

void
task2(intptr_t exinf)
{
	ER		ercd;

	check_point(15);

	ercd = act_tsk(TASK3);
	check_ercd(ercd, E_OK);

	check_point(17);

	ercd = cal_svc(0, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_RSFN);

	ercd = cal_svc(TFN_EXTSVC3+1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_RSFN);

	ercd = cal_svc(TFN_EXTSVC0, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_RSFN);

	ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);

	check_point(21);

	ercd = cal_svc(TFN_EXTSVC3, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_SYS);

	check_point(22);

	ercd = sta_alm(ALM1, 0U);
	check_ercd(ercd, E_OK);

	ercd = dly_tsk(1U);
	check_ercd(ercd, E_OK);

	check_finish(26);

	check_point(0);
}

static uint_t	task3_count = 0;

void
task3(intptr_t exinf)
{
	ER		ercd;
	T_RTSK	rtsk;

	switch (++task3_count) {
	case 1:
		check_point(2);

		ercd = ref_tsk(TASK1, &rtsk);
		check_ercd(ercd, E_OK);
		check_assert(rtsk.svclevel == 0);

		ercd = ext_tsk();
		check_ercd(ercd, E_OK);

		check_point(0);

	case 2:
		check_point(5);

		ercd = ref_tsk(TASK1, &rtsk);
		check_ercd(ercd, E_OK);
		check_assert(rtsk.svclevel == 1);

		ercd = ext_tsk();
		check_ercd(ercd, E_OK);

		check_point(0);

	case 3:
		check_point(8);

		ercd = ref_tsk(TASK1, &rtsk);
		check_ercd(ercd, E_OK);
		check_assert(rtsk.svclevel == 2);

		ercd = ext_tsk();
		check_ercd(ercd, E_OK);

		check_point(0);

	case 4:
		check_point(16);

		ercd = ref_tsk(TASK2, &rtsk);
		check_ercd(ercd, E_OK);
		check_assert(rtsk.svclevel == 0);

		ercd = ext_tsk();
		check_ercd(ercd, E_OK);

		check_point(0);

	case 5:
		check_point(19);

		ercd = ref_tsk(TASK2, &rtsk);
		check_ercd(ercd, E_OK);
		check_assert(rtsk.svclevel == 1);

		ercd = ext_tsk();
		check_ercd(ercd, E_OK);

		check_point(0);
	}
	check_point(0);
}
