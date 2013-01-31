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
 *  $Id: serial.h 837 2012-12-26 15:09:59Z ertl-hiro $
 */

/*
 *		���ꥢ�륤�󥿥ե������ɥ饤��
 */

#ifndef TOPPERS_SERIAL_H
#define TOPPERS_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <extsvc_fncode.h>
#include "target_syssvc.h"

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Фγ�ĥ�����ӥ�������Υ����å�������
 */ 
#ifndef SSZ_SERIAL_OPN_POR
#define SSZ_SERIAL_OPN_POR	1024
#endif /* SSZ_SERIAL_OPN_POR */

#ifndef SSZ_SERIAL_CLS_POR
#define SSZ_SERIAL_CLS_POR	1024
#endif /* SSZ_SERIAL_CLS_POR */

#ifndef SSZ_SERIAL_REA_DAT
#define SSZ_SERIAL_REA_DAT	1024
#endif /* SSZ_SERIAL_REA_DAT */

#ifndef SSZ_SERIAL_WRI_DAT
#define SSZ_SERIAL_WRI_DAT	1024
#endif /* SSZ_SERIAL_WRI_DAT */

#ifndef SSZ_SERIAL_CTL_POR
#define SSZ_SERIAL_CTL_POR	1024
#endif /* SSZ_SERIAL_CTL_POR */

#ifndef SSZ_SERIAL_REF_POR
#define SSZ_SERIAL_REF_POR	1024
#endif /* SSZ_SERIAL_REF_POR */

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Ф��Ѥ���ѥ��å�
 */
typedef struct {
	uint_t		reacnt;			/* �����Хåե����ʸ���� */
	uint_t		wricnt;			/* �����Хåե����ʸ���� */
} T_SERIAL_RPOR;

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Фν�����롼����
 */
extern void		serial_initialize(intptr_t exinf) throw();

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Ф����̤����ʸ���μ�Ф�
 */
extern bool_t	serial_get_chr(ID portid, char *p_c) throw();

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Фγ�ĥ�����ӥ�������ˤ��ƽФ�����
 *  ���ե�����
 */
#ifndef TOPPERS_SVC_CALL

Inline ER
serial_opn_por(ID portid)
{
	return((ER) cal_svc(TFN_SERIAL_OPN_POR, (intptr_t) portid, 0, 0, 0, 0));
}

Inline ER
serial_cls_por(ID portid)
{
	return((ER) cal_svc(TFN_SERIAL_CLS_POR, (intptr_t) portid, 0, 0, 0, 0));
}

Inline ER_UINT
serial_rea_dat(ID portid, char *buf, uint_t len)
{
	return(cal_svc(TFN_SERIAL_REA_DAT, (intptr_t) portid, (intptr_t) buf,
													(intptr_t) len, 0, 0));
}

Inline ER_UINT
serial_wri_dat(ID portid, const char *buf, uint_t len)
{
	return(cal_svc(TFN_SERIAL_WRI_DAT, (intptr_t) portid, (intptr_t) buf,
													(intptr_t) len, 0, 0));
}

Inline ER
serial_ctl_por(ID portid, uint_t ioctl)
{
	return((ER) cal_svc(TFN_SERIAL_CTL_POR, (intptr_t) portid,
												(intptr_t) ioctl, 0, 0, 0));
}

Inline ER
serial_ref_por(ID portid, T_SERIAL_RPOR *pk_rpor)
{
	return((ER) cal_svc(TFN_SERIAL_REF_POR, (intptr_t) portid,
											(intptr_t) pk_rpor, 0, 0, 0));
}

#endif /* TOPPERS_SVC_CALL */

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Фδؿ��ƽФ��ˤ��ƽФ����󥿥ե���
 *  ��
 */
extern ER		_serial_serial_opn_por(ID portid) throw();
extern ER		_serial_serial_cls_por(ID portid) throw();
extern ER_UINT	_serial_serial_rea_dat(ID portid, char *buf,
													uint_t len) throw();
extern ER_UINT	_serial_serial_wri_dat(ID portid, const char *buf,
													uint_t len) throw();
extern ER		_serial_serial_ctl_por(ID portid, uint_t ioctl) throw();
extern ER		_serial_serial_ref_por(ID portid,
										T_SERIAL_RPOR *pk_rpor) throw();

#ifdef TOPPERS_SVC_CALL
#define serial_opn_por	_serial_serial_opn_por
#define serial_cls_por	_serial_serial_cls_por
#define serial_rea_dat	_serial_serial_rea_dat
#define serial_wri_dat	_serial_serial_wri_dat
#define serial_ctl_por	_serial_serial_ctl_por
#define serial_ref_por	_serial_serial_ref_por
#endif /* TOPPERS_SVC_CALL */

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Ф��ĥ�����ӥ�������Ȥ�����Ͽ���뤿
 *  ������
 */
extern ER_UINT	extsvc_serial_opn_por(intptr_t portid, intptr_t par2,
									intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();
extern ER_UINT	extsvc_serial_cls_por(intptr_t portid, intptr_t par2,
									intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();
extern ER_UINT	extsvc_serial_rea_dat(intptr_t portid, intptr_t buf,
									intptr_t len, intptr_t par4,
									intptr_t par5, ID cdmid) throw();
extern ER_UINT	extsvc_serial_wri_dat(intptr_t portid, intptr_t buf,
									intptr_t len, intptr_t par4,
									intptr_t par5, ID cdmid) throw();
extern ER_UINT	extsvc_serial_ctl_por(intptr_t portid, intptr_t ioctl,
									intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();
extern ER_UINT	extsvc_serial_ref_por(intptr_t portid, intptr_t pk_rpor,
									intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Ф�ư�������ѤΤ�������
 *
 *  �ʲ�������ϡ��ӥå���������¤�Ȥä��Ѥ��롥
 */
#define	IOCTL_NULL	0U			/* ����ʤ� */
#define	IOCTL_ECHO	0x0001U		/* ��������ʸ���򥨥����Хå� */
#define	IOCTL_CRLF	0x0010U		/* LF��������������CR���ղ� */
#define	IOCTL_FCSND	0x0100U		/* �������Ф��ƥե������Ԥ� */
#define	IOCTL_FCANY	0x0200U		/* �ɤΤ褦��ʸ���Ǥ������Ƴ� */
#define	IOCTL_FCRCV	0x0400U		/* �������Ф��ƥե������Ԥ� */

#ifdef __cplusplus
}
#endif

#endif /* TOPPERS_SERIAL_H */
