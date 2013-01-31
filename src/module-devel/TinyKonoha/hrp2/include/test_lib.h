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
 *  $Id: test_lib.h 837 2012-12-26 15:09:59Z ertl-hiro $
 */

/* 
 *		�ƥ��ȥץ�����ѥ饤�֥��
 */

#ifndef TOPPERS_TEST_LIB_H
#define TOPPERS_TEST_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <extsvc_fncode.h>

/*
 *  �������åȰ�¸�����
 */
#include "target_syssvc.h"
#include "target_test.h"

/*
 *  �ƥ��ȥץ�����ѥ饤�֥��γ�ĥ�����ӥ�������Υ����å�������
 */ 
#ifndef SSZ_TEST_CHECK_POINT
#define SSZ_TEST_CHECK_POINT	1024
#endif /* SSZ_TEST_CHECK_POINT */

#ifndef SSZ_TEST_SET_BIT_FUNC
#define SSZ_TEST_SET_BIT_FUNC	1024
#endif /* SSZ_TEST_SET_BIT_FUNC */

#ifndef SSZ_TEST_SYSLOG_FLUSH
#define SSZ_TEST_SYSLOG_FLUSH	1024
#endif /* SSZ_TEST_SYSLOG_FLUSH */

#ifndef SSZ_TEST_TEST_FINISH
#define SSZ_TEST_TEST_FINISH	1024
#endif /* SSZ_TEST_TEST_FINISH */

/*
 *	���ʿ��Ǵؿ��η�
 */
typedef ER (*BIT_FUNC)(void);

/*
 *	��λ�����å��ݥ����
 */
extern void	check_finish(uint_t count);

/*
 *	�������å�
 */
extern void	_check_assert(const char *expr, const char *file, int_t line);
#define check_assert(exp) \
	((void)(!(exp) ? (_check_assert(#exp, __FILE__, __LINE__), 0) : 0))

/*
 *	���顼�����ɥ����å�
 */
extern void	_check_ercd(ER ercd, const char *file, int_t line);
#define check_ercd(ercd, expected_ercd) \
	((void)((ercd) != (expected_ercd) ? \
					(_check_ercd(ercd, __FILE__, __LINE__), 0) : 0))

/*
 *	�����ƥ���֤Υ����å��ʥ���������ƥ������ѡ�
 *
 *  �����ƥ���֤��Ф��뻲�������Ĥ���Ƥ��ʤ�����������ϡ����δ�
 *  �����Ѥ��뤳�ȤϤǤ��ʤ����󥿥�������ƥ������ѤΥ����ƥ���֤�
 *  �����å���check_state_i�ˤ��Ѥ��뤳�ȤϤǤ��롥
 */
extern void check_state(bool_t ctx, bool_t loc, PRI ipm, bool_t dsp,
												bool_t dpn, bool_t tex);

/*
 *	�����ƥ���֤Υ����å����󥿥�������ƥ������ѡ�
 */
extern void check_state_i(bool_t ctx, bool_t loc, bool_t dsp,
												bool_t dpn, bool_t tex);

/*
 *  �ƥ��ȥץ�����ѥ饤�֥��γ�ĥ�����ӥ�������ˤ��ƽФ�����
 *  �ե�����
 */
#ifndef TOPPERS_SVC_CALL

/*
 *	�����å��ݥ����
 */
Inline void
check_point(uint_t count)
{
	(void) cal_svc(TFN_TEST_CHECK_POINT, (intptr_t) count, 0, 0, 0, 0);
}

/*
 *	���ʿ��Ǵؿ�������
 */
Inline void
set_bit_func(BIT_FUNC bit_func)
{
	(void) cal_svc(TFN_TEST_SET_BIT_FUNC, (intptr_t) bit_func, 0, 0, 0, 0);
}

/*
 *  �����ƥ���ν��Ͻ���
 */
Inline void
syslog_flush(void)
{
	(void) cal_svc(TFN_TEST_SYSLOG_FLUSH, 0, 0, 0, 0, 0);
}

/*
 *	�ƥ��ȥץ����ν�λ
 */
Inline void
test_finish(void)
{
	(void) cal_svc(TFN_TEST_TEST_FINISH, 0, 0, 0, 0, 0);
}

#endif /* TOPPERS_SVC_CALL */

/*
 *  �ƥ��ȥץ�����ѥ饤�֥��δؿ��ƽФ��ˤ��ƽФ����󥿥ե�����
 */
extern void	_test_check_point(uint_t count) throw();
extern void	_test_set_bit_func(BIT_FUNC bit_func) throw();
extern void	_test_syslog_flush(void) throw();
extern void	_test_test_finish(void) throw();

#ifdef TOPPERS_SVC_CALL
#define check_point		_test_check_point
#define set_bit_func	_test_set_bit_func
#define syslog_flush	_test_syslog_flush
#define test_finish		_test_test_finish
#endif /* TOPPERS_SVC_CALL */

/*
 *  �ƥ��ȥץ�����ѥ饤�֥����ĥ�����ӥ�������Ȥ�����Ͽ���뤿��
 *  �����
 */
extern ER_UINT	extsvc_check_point(intptr_t portid, intptr_t par2,
									intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();
extern ER_UINT	extsvc_set_bit_func(intptr_t portid, intptr_t par2,
									intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();
extern ER_UINT	extsvc_syslog_flush(intptr_t portid, intptr_t par2,
									intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();
extern ER_UINT	extsvc_test_finish(intptr_t portid, intptr_t par2,
									intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();

#ifdef __cplusplus
}
#endif

#endif /* TOPPERS_TEST_LIB_H */
