/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 * 
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
 *  @(#) $Id: test_lib.c 837 2012-12-26 15:09:59Z ertl-hiro $
 */

/* 
 *		�ƥ��ȥץ�����ѥ饤�֥��
 */

#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include <test_lib.h>

/*
 *	��λ�����å��ݥ����
 */
void
check_finish(uint_t count)
{
	check_point(count);
	syslog_0(LOG_NOTICE, "All check points passed.");
	test_finish();
}

/*
 *	�������å��Υ��顼����
 */
void
_check_assert(const char *expr, const char *file, int_t line)
{
	syslog_3(LOG_ERROR, "## Assertion `%s' failed at %s:%u.",
								expr, file, line);
	test_finish();
}

/*
 *	���顼�����ɥ����å��Υ��顼����
 */
void
_check_ercd(ER ercd, const char *file, int_t line)
{
	syslog_3(LOG_ERROR, "## Unexpected error %s detected at %s:%u.",
								itron_strerror(ercd), file, line);
	test_finish();
}

/*
 *	�����ƥ���֤Υ����å��ʥ���������ƥ������ѡ�
 */
void
check_state(bool_t ctx, bool_t loc, PRI ipm, bool_t dsp,
										bool_t dpn, bool_t tex)
{
	PRI		intpri;
	ER		ercd;

	check_assert(sns_ctx() == ctx);
	check_assert(sns_loc() == loc);
	if (!loc) {
		/*
		 *  IPM�Υ����å��ϡ�CPU��å�������֤ξ��ˤΤ߹Ԥ���
		 */
		ercd = get_ipm(&intpri);
		check_ercd(ercd, E_OK);
		check_assert(intpri == ipm);
	}
	check_assert(sns_dsp() == dsp);
	check_assert(sns_dpn() == dpn);
	check_assert(sns_tex() == tex);
}

/*
 *	�����ƥ���֤Υ����å����󥿥�������ƥ������ѡ�
 */
void
check_state_i(bool_t ctx, bool_t loc, bool_t dsp, bool_t dpn, bool_t tex)
{
	check_assert(sns_ctx() == ctx);
	check_assert(sns_loc() == loc);
	check_assert(sns_dsp() == dsp);
	check_assert(sns_dpn() == dpn);
	check_assert(sns_tex() == tex);
}
