/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
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
 *  $Id: syslog.h 837 2012-12-26 15:09:59Z ertl-hiro $
 */

/*
 *		�����ƥ����ǽ
 */

#ifndef TOPPERS_SYSLOG_H
#define TOPPERS_SYSLOG_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  �����ƥ�����Ϥ�Ԥ���������
 */
#include <t_syslog.h>
#include <extsvc_fncode.h>
#include "target_syssvc.h"

/*
 *  ���Хåե��Ȥ���˥����������뤿��Υݥ���
 */
#ifndef TCNT_SYSLOG_BUFFER
#define TCNT_SYSLOG_BUFFER	32		/* ���Хåե��Υ����� */
#endif /* TCNT_SYSLOG_BUFFER */

/*
 *  �����ƥ����ǽ�γ�ĥ�����ӥ�������Υ����å�������
 */ 
#ifndef SSZ_SYSLOG_WRI_LOG
#define SSZ_SYSLOG_WRI_LOG	1024
#endif /* SSZ_SYSLOG_WRI_LOG */

#ifndef SSZ_SYSLOG_REA_LOG
#define SSZ_SYSLOG_REA_LOG	1024
#endif /* SSZ_SYSLOG_REA_LOG */

#ifndef SSZ_SYSLOG_MSK_LOG
#define SSZ_SYSLOG_MSK_LOG	1024
#endif /* SSZ_SYSLOG_MSK_LOG */

#ifndef SSZ_SYSLOG_REF_LOG
#define SSZ_SYSLOG_REF_LOG	1024
#endif /* SSZ_SYSLOG_REF_LOG */

/*
 *  �����ƥ����ǽ�ν����
 */
extern void	syslog_initialize(intptr_t exinf) throw();

/*
 *  �����ƥ����ǽ�γ�ĥ�����ӥ�������ˤ��ƽФ����󥿥ե�����
 */
#ifndef TOPPERS_SVC_CALL

/*
 *  ������ν���
 *
 *  TOPPERS_OMIT_SYSLOG���������Ƥ��ʤ���硤syslog_wri_log��
 *  syslog_fwri_log�ϡ�t_syslog.h���������뤿�ᡤ�����Ǥ�������ʤ���
 */
#ifdef TOPPERS_OMIT_SYSLOG

Inline ER
syslog_wri_log(uint_t prio, const SYSLOG *p_syslog)
{
	return((ER) cal_svc(TFN_SYSLOG_WRI_LOG, (intptr_t) prio,
										(intptr_t) p_syslog, 0, 0, 0));
}

Inline ER
syslog_fwri_log(ER ercd, const SYSLOG *p_syslog)
{
	return((ER) cal_svc(TFN_SYSLOG_WRI_LOG, (intptr_t) ercd,
										(intptr_t) p_syslog, 0, 0, 0));
}

#endif /* TOPPERS_OMIT_SYSLOG */

/*
 *  ���Хåե�����Υ�������ɽФ�
 */
Inline ER_UINT
syslog_rea_log(SYSLOG *p_syslog)
{
	return(cal_svc(TFN_SYSLOG_REA_LOG, (intptr_t) p_syslog, 0, 0, 0, 0));
}

/* 
 *  ���Ϥ��٤�������ν����٤�����
 */
Inline ER_UINT
syslog_msk_log(intptr_t logmask, intptr_t lowmask)
{
	return(cal_svc(TFN_SYSLOG_MSK_LOG, (intptr_t) logmask,
											(intptr_t) lowmask, 0, 0, 0));
}

/* 
 *  ���Хåե��ξ��ֻ���
 */
Inline ER_UINT
syslog_ref_log(intptr_t pk_rlog)
{
	return(cal_svc(TFN_SYSLOG_REF_LOG, (intptr_t) pk_rlog, 0, 0, 0, 0));
}

#endif /* TOPPERS_SVC_CALL */

/*
 *  �����ƥ����ǽ�δؿ��ƽФ��ˤ��ƽФ����󥿥ե�����
 */
extern ER		_syslog_syslog_wri_log(uint_t prio,
										const SYSLOG *p_syslog) throw();
extern ER		_syslog_syslog_fwri_log(ER ercd,
										const SYSLOG *p_syslog) throw();
extern ER_UINT	_syslog_syslog_rea_log(SYSLOG *p_syslog) throw();
extern ER		_syslog_syslog_msk_log(uint_t logmask, uint_t lowmask) throw();
extern ER		_syslog_syslog_ref_log(T_SYSLOG_RLOG *pk_rlog) throw();

#ifdef TOPPERS_SVC_CALL
#define syslog_wri_log	_syslog_syslog_wri_log
#define syslog_fwri_log	_syslog_syslog_fwri_log
#define syslog_rea_log	_syslog_syslog_rea_log
#define syslog_msk_log	_syslog_syslog_msk_log
#define syslog_ref_log	_syslog_syslog_ref_log
#endif /* TOPPERS_SVC_CALL */

/*
 *  �����ƥ����ǽ���ĥ�����ӥ�������Ȥ�����Ͽ���뤿������
 */
extern ER_UINT	extsvc_syslog_wri_log(intptr_t prio, intptr_t p_syslog,
									intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();
extern ER_UINT	extsvc_syslog_fwri_log(intptr_t ercd, intptr_t p_syslog,
									intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();
extern ER_UINT	extsvc_syslog_rea_log(intptr_t p_syslog, intptr_t par2,
									intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();
extern ER_UINT	extsvc_syslog_msk_log(intptr_t logmask, intptr_t lowmask,
									intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();
extern ER_UINT	extsvc_syslog_ref_log(intptr_t pk_rlog, intptr_t par2,
									intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();

#ifdef __cplusplus
}
#endif

#endif /* TOPPERS_SYSLOG_H */
