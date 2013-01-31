/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2012 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: t_syslog.h 837 2012-12-26 15:09:59Z ertl-hiro $
 */

/*
 *		�����ƥ�����Ϥ�Ԥ���������
 *
 *  �����ƥ�������ӥ��ϡ������ƥ�Υ��������Ϥ��뤿��Υ����ӥ�
 *  �Ǥ��롥�����ͥ뤫��Υ�����ν��Ϥˤ��Ѥ��뤿�ᡤ�������Ԥ�����
 *  �ˤϤ��뤳�ȤϤʤ���
 *
 *  ������ϡ������ͥ���Υ��Хåե��˽񤭹��फ�����٥��ʸ����
 *  �ϴؿ����Ѥ��ƽ��Ϥ��롥�ɤ����Ȥ����ϡ���ĥ�����ӥ���������ڤ�
 *  �����뤳�Ȥ��Ǥ��롥
 *
 *  ���Хåե��ΰ褬�����Хե��������ˤϡ��Ť��������ä��ƾ�
 *  �񤭤��롥
 *
 *  ������֥����Υ������ե����뤫�餳�Υե�����򥤥󥯥롼�ɤ����
 *  �ϡ�TOPPERS_MACRO_ONLY��������Ƥ������Ȥǡ��ޥ�������ʳ��ε��Ҥ�
 *  �������Ȥ��Ǥ��롥
 *
 *  ���Υե�����򥤥󥯥롼�ɤ������ˡ�t_stddef.h�򥤥󥯥롼�ɤ��Ƥ�
 *  �����Ȥ�ɬ�פǤ����TOPPERS_SVC_CALL��������Ƥ��ʤ����ˤϡ��ʲ�
 *  ��kernel.h�򥤥󥯥롼�ɤ��뤿�ᡤt_stddef.h�򥤥󥯥롼�ɤ��ʤ���
 *  ������ʤ�����ASP�����ͥ�Ȥθߴ����Τ���ˤ��Τ褦�ʥ롼��ˤ��Ƥ�
 *  ���ˡ�
 */

#ifndef TOPPERS_T_SYSLOG_H
#define TOPPERS_T_SYSLOG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TOPPERS_SVC_CALL
#include <kernel.h>
#endif /* TOPPERS_SVC_CALL */
#include <extsvc_fncode.h>

/*
 *  ������μ��̤����
 */
#define LOG_TYPE_COMMENT	UINT_C(0x01)	/* ������ */
#define LOG_TYPE_ASSERT		UINT_C(0x02)	/* �����������μ��� */

#define LOG_TYPE_INH		UINT_C(0x11)	/* ����ߥϥ�ɥ� */
#define LOG_TYPE_ISR		UINT_C(0x12)	/* ����ߥ����ӥ��롼���� */
#define LOG_TYPE_CYC		UINT_C(0x13)	/* �����ϥ�ɥ� */
#define LOG_TYPE_ALM		UINT_C(0x14)	/* ���顼��ϥ�ɥ� */
#define LOG_TYPE_OVR		UINT_C(0x15)	/* �����Х��ϥ�ɥ� */
#define LOG_TYPE_EXC		UINT_C(0x16)	/* CPU�㳰�ϥ�ɥ� */
#define LOG_TYPE_TEX		UINT_C(0x17)	/* �������㳰�����롼���� */
#define LOG_TYPE_TSKSTAT	UINT_C(0x18)	/* �����������Ѳ� */
#define LOG_TYPE_DSP		UINT_C(0x19)	/* �ǥ����ѥå��� */
#define LOG_TYPE_SVC		UINT_C(0x1a)	/* �����ӥ������� */

#define LOG_ENTER			UINT_C(0x00)	/* ���������� */
#define LOG_LEAVE			UINT_C(0x80)	/* �и�����λ */

/*
 *  ������ν����٤����
 */
#define LOG_EMERG			UINT_C(0)		/* ����åȥ�������ͤ��륨�顼 */
#define LOG_ALERT			UINT_C(1)
#define LOG_CRIT			UINT_C(2)
#define LOG_ERROR			UINT_C(3)		/* �����ƥ२�顼 */
#define LOG_WARNING			UINT_C(4)		/* �ٹ��å����� */
#define LOG_NOTICE			UINT_C(5)
#define LOG_INFO			UINT_C(6)
#define LOG_DEBUG			UINT_C(7)		/* �ǥХå��ѥ�å����� */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  ������Υǡ�����¤
 */

#define TMAX_LOGINFO	6

typedef struct {
	uint_t		logtype;				/* ������μ��� */
	SYSTIM		logtim;					/* ������ */
	intptr_t	loginfo[TMAX_LOGINFO];	/* ����¾�Υ����� */
} SYSLOG;

/*
 *  ������ν����٤Υӥåȥޥåפ��뤿��Υޥ���
 */
#define LOG_MASK(prio)		(1U << (prio))
#define LOG_UPTO(prio)		((1U << ((prio) + 1)) - 1)

/*
 *  �ѥ��åȷ��������
 */
typedef struct t_syslog_rlog {
	uint_t	count;		/* ���Хåե���Υ��ο� */
	uint_t	lost;		/* ����줿���ο� */
	uint_t	logmask;	/* ���Хåե��˵�Ͽ���٤������� */
	uint_t	lowmask;	/* ���٥���Ϥ��٤������� */
} T_SYSLOG_RLOG;

/*
 *  ���������Ϥ��뤿��Υ饤�֥��ؿ�
 */

#ifndef TOPPERS_OMIT_SYSLOG

/*
 *  ������ν��ϡ�syslog_wri_log�ˤȽ��ϼ��Ի��ν�����syslog_fwri_log��
 *  ��ƤӽФ���������
 */
#ifndef TOPPERS_SVC_CALL

Inline ER
syslog_wri_log(uint_t prio, const SYSLOG *p_syslog)
{
	return((ER) cal_svc(TFN_SYSLOG_WRI_LOG, (intptr_t) prio,
										(intptr_t) p_syslog, 0, 0, 0));
}

Inline ER
syslog_fwri_log(ER ercd, const SYSLOG *p_syslog)
{
	return((ER) cal_svc(TFN_SYSLOG_FWRI_LOG, (intptr_t) ercd,
										(intptr_t) p_syslog, 0, 0, 0));
}

#endif /* TOPPERS_SVC_CALL */

extern ER	_syslog_syslog_wri_log(uint_t prio,
									const SYSLOG *p_syslog) throw();

extern ER	_syslog_syslog_fwri_log(ER ercd,
									const SYSLOG *p_syslog) throw();

#ifdef TOPPERS_SVC_CALL
#define syslog_wri_log	_syslog_syslog_wri_log
#define syslog_fwri_log	_syslog_syslog_fwri_log
#endif /* TOPPERS_SVC_CALL */

Inline void
_syslog_0(uint_t prio, uint_t type)
{
	SYSLOG	logbuf;
	ER		ercd;

	logbuf.logtype = type;
	ercd = syslog_wri_log(prio, &logbuf);
	if (ercd < 0) {
		(void) syslog_fwri_log(ercd, &logbuf);
	}
}

Inline void
_syslog_1(uint_t prio, uint_t type, intptr_t arg1)
{
	SYSLOG	logbuf;
	ER		ercd;

	logbuf.logtype = type;
	logbuf.loginfo[0] = arg1;
	ercd = syslog_wri_log(prio, &logbuf);
	if (ercd < 0) {
		(void) syslog_fwri_log(ercd, &logbuf);
	}
}

Inline void
_syslog_2(uint_t prio, uint_t type, intptr_t arg1, intptr_t arg2)
{
	SYSLOG	logbuf;
	ER		ercd;

	logbuf.logtype = type;
	logbuf.loginfo[0] = arg1;
	logbuf.loginfo[1] = arg2;
	ercd = syslog_wri_log(prio, &logbuf);
	if (ercd < 0) {
		(void) syslog_fwri_log(ercd, &logbuf);
	}
}

Inline void
_syslog_3(uint_t prio, uint_t type, intptr_t arg1, intptr_t arg2,
														intptr_t arg3)
{
	SYSLOG	logbuf;
	ER		ercd;

	logbuf.logtype = type;
	logbuf.loginfo[0] = arg1;
	logbuf.loginfo[1] = arg2;
	logbuf.loginfo[2] = arg3;
	ercd = syslog_wri_log(prio, &logbuf);
	if (ercd < 0) {
		(void) syslog_fwri_log(ercd, &logbuf);
	}
}

Inline void
_syslog_4(uint_t prio, uint_t type, intptr_t arg1, intptr_t arg2,
										intptr_t arg3, intptr_t arg4)
{
	SYSLOG	logbuf;
	ER		ercd;

	logbuf.logtype = type;
	logbuf.loginfo[0] = arg1;
	logbuf.loginfo[1] = arg2;
	logbuf.loginfo[2] = arg3;
	logbuf.loginfo[3] = arg4;
	ercd = syslog_wri_log(prio, &logbuf);
	if (ercd < 0) {
		(void) syslog_fwri_log(ercd, &logbuf);
	}
}

Inline void
_syslog_5(uint_t prio, uint_t type, intptr_t arg1, intptr_t arg2,
							intptr_t arg3, intptr_t arg4, intptr_t arg5)
{
	SYSLOG	logbuf;
	ER		ercd;

	logbuf.logtype = type;
	logbuf.loginfo[0] = arg1;
	logbuf.loginfo[1] = arg2;
	logbuf.loginfo[2] = arg3;
	logbuf.loginfo[3] = arg4;
	logbuf.loginfo[4] = arg5;
	ercd = syslog_wri_log(prio, &logbuf);
	if (ercd < 0) {
		(void) syslog_fwri_log(ercd, &logbuf);
	}
}

Inline void
_syslog_6(uint_t prio, uint_t type, intptr_t arg1, intptr_t arg2,
				intptr_t arg3, intptr_t arg4, intptr_t arg5, intptr_t arg6)
{
	SYSLOG	logbuf;
	ER		ercd;

	logbuf.logtype = type;
	logbuf.loginfo[0] = arg1;
	logbuf.loginfo[1] = arg2;
	logbuf.loginfo[2] = arg3;
	logbuf.loginfo[3] = arg4;
	logbuf.loginfo[4] = arg5;
	logbuf.loginfo[5] = arg6;
	ercd = syslog_wri_log(prio, &logbuf);
	if (ercd < 0) {
		(void) syslog_fwri_log(ercd, &logbuf);
	}
}

/*
 *  ������ʥ����ȡˤ���Ϥ��뤿��Υ饤�֥��ؿ���vasyslog.c��
 */
extern void	syslog(uint_t prio, const char *format, ...) throw();

#else /* TOPPERS_OMIT_SYSLOG */

/*
 *  �����ƥ�����Ϥ��޻ߤ�����
 */

Inline void
_syslog_0(uint_t prio, uint_t type)
{
}

Inline void
_syslog_1(uint_t prio, uint_t type, intptr_t arg1)
{
}

Inline void
_syslog_2(uint_t prio, uint_t type, intptr_t arg1, intptr_t arg2)
{
}

Inline void
_syslog_3(uint_t prio, uint_t type, intptr_t arg1, intptr_t arg2,
														intptr_t arg3)
{
}

Inline void
_syslog_4(uint_t prio, uint_t type, intptr_t arg1, intptr_t arg2,
										intptr_t arg3, intptr_t arg4)
{
}

Inline void
_syslog_5(uint_t prio, uint_t type, intptr_t arg1, intptr_t arg2,
							intptr_t arg3, intptr_t arg4, intptr_t arg5)
{
}

Inline void
_syslog_6(uint_t prio, uint_t type, intptr_t arg1, intptr_t arg2,
				intptr_t arg3, intptr_t arg4, intptr_t arg5, intptr_t arg6)
{
}

Inline void
syslog(uint_t prio, const char *format, ...)
{
}

#endif /* TOPPERS_OMIT_SYSLOG */

/*
 *  ������ʥ����ȡˤ���Ϥ��뤿��Υޥ���
 *
 *  format����Ӹ�³�ΰ����������������å������򡤽�����prio�ǥ���
 *  ��Ȥ��ƽ��Ϥ��뤿��Υޥ���arg1��argn��intptr_t���˥��㥹�Ȥ���
 *  ���ᡤintptr_t���˷��Ѵ��Ǥ���Ǥ�դη��Ǥ褤��
 */

#define syslog_0(prio, format) \
				_syslog_1(prio, LOG_TYPE_COMMENT, (intptr_t)(format))

#define syslog_1(prio, format, arg1) \
				_syslog_2(prio, LOG_TYPE_COMMENT, (intptr_t)(format), \
														(intptr_t)(arg1))

#define syslog_2(prio, format, arg1, arg2) \
				_syslog_3(prio, LOG_TYPE_COMMENT, (intptr_t)(format), \
										(intptr_t)(arg1), (intptr_t)(arg2))

#define syslog_3(prio, format, arg1, arg2, arg3) \
				_syslog_4(prio, LOG_TYPE_COMMENT, (intptr_t)(format), \
						(intptr_t)(arg1), (intptr_t)(arg2), (intptr_t)(arg3))

#define syslog_4(prio, format, arg1, arg2, arg3, arg4) \
				_syslog_5(prio, LOG_TYPE_COMMENT, (intptr_t)(format), \
						(intptr_t)(arg1), (intptr_t)(arg2), (intptr_t)(arg3), \
														(intptr_t)(arg4))

#define syslog_5(prio, format, arg1, arg2, arg3, arg4, arg5) \
				_syslog_6(prio, LOG_TYPE_COMMENT, (intptr_t)(format), \
						(intptr_t)(arg1), (intptr_t)(arg2), (intptr_t)(arg3), \
										(intptr_t)(arg4), (intptr_t)(arg5))

/*
 *  ������ʥ����������μ��ԡˤ���Ϥ��뤿��Υޥ���
 */
#ifndef TOPPERS_assert_fail
#define TOPPERS_assert_fail(exp, file, line) \
				_syslog_3(LOG_EMERG, LOG_TYPE_ASSERT, (intptr_t)(file), \
										(intptr_t)(line), (intptr_t)(exp))
#endif /* TOPPERS_assert_fail */

#endif /* TOPPERS_MACRO_ONLY */

#ifdef __cplusplus
}
#endif

#endif /* TOPPERS_T_SYSLOG_H */
