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
 *  $Id: kernel.h 837 2012-12-26 15:09:59Z ertl-hiro $
 */

/*
 *		TOPPERS/HRP�����ͥ� ɸ��إå��ե�����
 *
 *  TOPPERS/HRP�����ͥ뤬���ݡ��Ȥ��륵���ӥ������������ȡ�ɬ�פʥǡ�
 *  ������������ޥ���������ޤ�إå��ե����롥
 *
 *  ������֥����Υ������ե����뤫�餳�Υե�����򥤥󥯥롼�ɤ����
 *  �ϡ�TOPPERS_MACRO_ONLY��������Ƥ���������ˤ�ꡤ�ޥ�������ʳ���
 *  �����褦�ˤʤäƤ��롥
 *
 *  ���Υե�����򥤥󥯥롼�ɤ������˥��󥯥롼�ɤ��Ƥ����٤��ե�����
 *  �Ϥʤ���
 */

#ifndef TOPPERS_KERNEL_H
#define TOPPERS_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 *	TOPPERS���̤Υǡ�������������ޥ���
 */
#include <t_stddef.h>

/*
 *  �������åȰ�¸��
 */
#include "target_kernel.h"

#ifndef TOPPERS_MACRO_ONLY

/*
 *  �ǡ����������
 */

/*
 *  �ӥåȥѥ�����䥪�֥��������ֹ�η����
 */
typedef	uint_t		TEXPTN;		/* �������㳰�װ��Υӥåȥѥ����� */
typedef	uint_t		FLGPTN;		/* ���٥�ȥե饰�Υӥåȥѥ����� */
typedef	ulong_t		OVRTIM;		/* �ץ��å����� */
typedef	uint_t		INTNO;		/* ������ֹ� */
typedef	uint_t		INHNO;		/* ����ߥϥ�ɥ��ֹ� */
typedef	uint_t		EXCNO;		/* CPU�㳰�ϥ�ɥ��ֹ� */

/*
 *  ����ñ�̤η����
 */
typedef void	(*TASK)(intptr_t exinf);
typedef void	(*TEXRTN)(TEXPTN texptn, intptr_t exinf);
typedef void	(*CYCHDR)(intptr_t exinf);
typedef void	(*ALMHDR)(intptr_t exinf);
typedef void	(*OVRHDR)(ID tskid, intptr_t exinf);
typedef void	(*ISR)(intptr_t exinf);
typedef void	(*INTHDR)(void);
typedef void	(*EXCHDR)(void *p_excinf);
typedef ER_UINT	(*EXTSVC)(intptr_t par1, intptr_t par2, intptr_t par3,
								intptr_t par4, intptr_t par5, ID cdmid);
typedef void	(*INIRTN)(intptr_t exinf);
typedef void	(*TERRTN)(intptr_t exinf);

/*
 *  �����ΰ���ݤΤ���η����
 */
#ifndef TOPPERS_STK_T
#define TOPPERS_STK_T	intptr_t
#endif /* TOPPERS_STK_T */
typedef	TOPPERS_STK_T	STK_T;	/* �����å��ΰ����ݤ��뤿��η� */

#ifndef TOPPERS_MPF_T
#define TOPPERS_MPF_T	intptr_t
#endif /* TOPPERS_MPF_T */
typedef	TOPPERS_MPF_T	MPF_T;	/* ����Ĺ����ס����ΰ����ݤ��뤿��η� */

/*
 *  ��å������إå��η����
 */
typedef	struct t_msg {			/* �᡼��ܥå����Υ�å������إå� */
	struct t_msg	*pk_next;
} T_MSG;

typedef	struct t_msg_pri {		/* ͥ�����դ���å������إå� */
	T_MSG	msgque;				/* ��å������إå� */
	PRI		msgpri;				/* ��å�����ͥ���� */
} T_MSG_PRI;

/*
 *  �ѥ��åȷ��������
 */
typedef struct t_rtsk {
	STAT	tskstat;	/* ���������� */
	PRI		tskpri;		/* �������θ���ͥ���� */
	PRI		tskbpri;	/* �������Υ١���ͥ���� */
	STAT	tskwait;	/* �Ԥ��װ� */
	ID		wobjid;		/* �Ԥ��оݤΥ��֥������Ȥ�ID */
	TMO		lefttmo;	/* �����ॢ���Ȥ���ޤǤλ��� */
	uint_t	actcnt;		/* ��ư�׵ᥭ�塼���󥰿� */
	uint_t	wupcnt;		/* �����׵ᥭ�塼���󥰿� */
	bool_t	texmsk;		/* �������㳰�ޥ������֤��ݤ� */
	bool_t	waifbd;		/* �Ԥ��ػ߾��֤��ݤ� */
	uint_t	svclevel;	/* ��ĥ�����ӥ�������Υͥ��ȥ�٥� */
} T_RTSK;

typedef struct t_rtex {
	STAT	texstat;	/* �������㳰�����ξ��� */
	TEXPTN	pndptn;		/* ��α�㳰�װ� */
} T_RTEX;

typedef struct t_rsem {
	ID		wtskid;		/* ���ޥե����Ԥ��������Ƭ�Υ�������ID�ֹ� */
	uint_t	semcnt;		/* ���ޥե��θ��ߤλ񸻿� */
} T_RSEM;

typedef struct t_rflg {
	ID		wtskid;		/* ���٥�ȥե饰���Ԥ��������Ƭ�Υ�������ID�ֹ� */
	FLGPTN	flgptn;		/* ���٥�ȥե饰�θ��ߤΥӥåȥѥ����� */
} T_RFLG;

typedef struct t_rdtq {
	ID		stskid;		/* �ǡ������塼�������Ԥ��������Ƭ�Υ�������ID�ֹ� */
	ID		rtskid;		/* �ǡ������塼�μ����Ԥ��������Ƭ�Υ�������ID�ֹ� */
	uint_t	sdtqcnt;	/* �ǡ������塼�����ΰ�˳�Ǽ����Ƥ���ǡ����ο� */
} T_RDTQ;

typedef struct t_rpdq {
	ID		stskid;		/* ͥ���٥ǡ������塼�������Ԥ��������Ƭ�Υ�����
						   ��ID�ֹ� */
	ID		rtskid;		/* ͥ���٥ǡ������塼�μ����Ԥ��������Ƭ�Υ�����
						   ��ID�ֹ� */
	uint_t	spdqcnt;	/* ͥ���٥ǡ������塼�����ΰ�˳�Ǽ����Ƥ���ǡ�
						   ���ο� */
} T_RPDQ;

typedef struct t_rmtx {
	ID		htskid;		/* �ߥ塼�ƥå������å����Ƥ��륿������ID�ֹ� */
	ID		wtskid;		/* �ߥ塼�ƥå������Ԥ��������Ƭ�Υ�������ID�ֹ� */
} T_RMTX;

typedef struct t_rmpf {
	ID		wtskid;		/* ����Ĺ����ס�����Ԥ��������Ƭ�Υ�������
						   ID�ֹ� */
	uint_t	fblkcnt;	/* ����Ĺ����ס����ΰ�ζ��������ΰ�˳��
						   �դ��뤳�Ȥ��Ǥ������Ĺ����֥�å��ο� */
} T_RMPF;

typedef struct t_rcyc {
	STAT	cycstat;	/* �����ϥ�ɥ��ư����� */
	RELTIM	lefttim;	/* ���˼����ϥ�ɥ��ư�������ޤǤ����л��� */
} T_RCYC;

typedef struct t_ralm {
	STAT	almstat;	/* ���顼��ϥ�ɥ��ư����� */
	RELTIM	lefttim;	/* ���顼��ϥ�ɥ��ư�������ޤǤ����л��� */
} T_RALM;

typedef struct t_rovr {
	STAT	ovrstat;	/* �����Х��ϥ�ɥ��ư����� */
	OVRTIM	leftotm;	/* �Ĥ�ץ��å����� */
} T_ROVR;

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  �����ӥ�������ƽФ��Τ������������
 */
#include <kernel_fncode.h>				/* ��ǽ�����ɤ���� */
#include "target_svc.h"					/* ���եȥ���������ߤˤ��ƽФ� */
#include <svc_call.h>					/* �ؿ��ƽФ��ˤ��ƽФ� */

#define SVC_CALL(svc)	_kernel_##svc	/* �ؿ��ƽФ��ˤ��ƤӽФ�̾�� */

/*
 *  ���֥�������°�������
 */
#define TA_ACT			UINT_C(0x02)	/* ��������ư���줿���֤����� */

#define TA_TPRI			UINT_C(0x01)	/* ���������Ԥ������ͥ���ٽ�� */
#define TA_MPRI			UINT_C(0x02)	/* ��å��������塼��ͥ���ٽ�� */

#define TA_WMUL			UINT_C(0x02)	/* ʣ�����Ԥ������� */
#define TA_CLR			UINT_C(0x04)	/* ���٥�ȥե饰�Υ��ꥢ���� */

#define TA_CEILING		UINT_C(0x03)	/* ͥ���پ�¥ץ�ȥ��� */

#define TA_STA			UINT_C(0x02)	/* �����ϥ�ɥ��ư����֤����� */

#define	TA_NOWRITE		UINT_C(0x01)	/* ����ߥ��������ػ� */
#define	TA_NOREAD		UINT_C(0x02)	/* �ɽФ����������ػ� */
#define	TA_EXEC			UINT_C(0x04)	/* �¹ԥ����������� */
#define	TA_MEMINI		UINT_C(0x08)	/* ����ν������Ԥ� */
#define	TA_MEMPRSV		UINT_C(0x10)	/* ����ν������Ԥ�ʤ� */
#define	TA_SDATA		UINT_C(0x20)	/* ���硼�ȥǡ����ΰ������ */
#define	TA_UNCACHE		UINT_C(0x40)	/* ����å����Բ� */
#define	TA_IODEV		UINT_C(0x80)	/* ���եǥХ������ΰ� */

#define TA_NONKERNEL	UINT_C(0x02)	/* �����ͥ�������γ���� */

#define TA_ENAINT		UINT_C(0x01)	/* ������׵�ػߥե饰�򥯥ꥢ */
#define TA_EDGE			UINT_C(0x02)	/* ���å��ȥꥬ */

/*
 *  �����ӥ��������ư��⡼�ɤ����
 */
#define TWF_ORW			UINT_C(0x01)	/* ���٥�ȥե饰��OR�Ԥ� */
#define TWF_ANDW		UINT_C(0x02)	/* ���٥�ȥե饰��AND�Ԥ� */

#define	TPM_WRITE		UINT_C(0x01)	/* ����ߥ����������Υ����å� */
#define	TPM_READ		UINT_C(0x02)	/* �ɽФ������������Υ����å� */
#define	TPM_EXEC		UINT_C(0x04)	/* �¹ԥ����������Υ����å� */

/*
 *  ���֥������Ȥξ��֤����
 */
#define TTS_RUN			UINT_C(0x01)	/* �¹Ծ��� */
#define TTS_RDY			UINT_C(0x02)	/* �¹Բ�ǽ���� */
#define TTS_WAI			UINT_C(0x04)	/* �Ԥ����� */
#define TTS_SUS			UINT_C(0x08)	/* �����Ԥ����� */
#define TTS_WAS			UINT_C(0x0c)	/* ����Ԥ����� */
#define TTS_DMT			UINT_C(0x10)	/* �ٻ߾��� */

#define TTW_SLP			UINT_C(0x0001)	/* �����Ԥ� */
#define TTW_DLY			UINT_C(0x0002)	/* ���ַв��Ԥ� */
#define TTW_SEM			UINT_C(0x0004)	/* ���ޥե��λ񸻳����Ԥ� */
#define TTW_FLG			UINT_C(0x0008)	/* ���٥�ȥե饰�Ԥ� */
#define TTW_SDTQ		UINT_C(0x0010)	/* �ǡ������塼�ؤ������Ԥ� */
#define TTW_RDTQ		UINT_C(0x0020)	/* �ǡ������塼����μ����Ԥ� */
#define TTW_SPDQ		UINT_C(0x0100)	/* ͥ���٥ǡ������塼�ؤ������Ԥ� */
#define TTW_RPDQ		UINT_C(0x0200)	/* ͥ���٥ǡ������塼����μ����Ԥ� */
#define TTW_MTX			UINT_C(0x0080)	/* �ߥ塼�ƥå����Υ�å��Ԥ����� */
#define TTW_MPF			UINT_C(0x2000)	/* ����Ĺ����֥�å��γ����Ԥ� */

#define TTEX_ENA		UINT_C(0x01)	/* �������㳰�������ľ��� */
#define TTEX_DIS		UINT_C(0x02)	/* �������㳰�����ػ߾��� */

#define TCYC_STP		UINT_C(0x01)	/* �����ϥ�ɥ餬ư��Ƥ��ʤ� */
#define TCYC_STA		UINT_C(0x02)	/* �����ϥ�ɥ餬ư��Ƥ��� */

#define TALM_STP		UINT_C(0x01)	/* ���顼��ϥ�ɥ餬ư��Ƥ��ʤ� */
#define TALM_STA		UINT_C(0x02)	/* ���顼��ϥ�ɥ餬ư��Ƥ��� */

#define TOVR_STP		UINT_C(0x01)	/* �����Х��ϥ�ɥ餬ư��Ƥ��ʤ�*/
#define TOVR_STA		UINT_C(0x02)	/* �����Х��ϥ�ɥ餬ư��Ƥ��� */

/*
 *  �ݸ�ɥᥤ��ID
 */
#define TDOM_SELF		0				/* ����������°�����ݸ�ɥᥤ�� */
#define TDOM_KERNEL		(-1)			/* �����ͥ�ɥᥤ�� */
#define TDOM_NONE		(-2)			/* ̵��°���ݸ�ɥᥤ���°���ʤ���*/

/*
 *  ����¾����������
 */
#define TSK_SELF		0			/* ������������ */
#define TSK_NONE		0			/* �������륿�������ʤ� */

#define TPRI_SELF		0			/* ���������Υ١���ͥ���� */
#define TPRI_INI		0			/* �������ε�ư��ͥ���� */

#define TIPM_ENAALL		0			/* �����ͥ���٥ޥ�������� */

/*
 *  ��������ȥޥ���
 */

/*
 *  ���ݡ��Ȥ��뵡ǽ
 */
#ifdef TOPPERS_TARGET_SUPPORT_DIS_INT
#define TOPPERS_SUPPORT_DIS_INT			/* dis_int�����ݡ��Ȥ���Ƥ��� */
#endif /* TOPPERS_TARGET_SUPPORT_DIS_INT */

#ifdef TOPPERS_TARGET_SUPPORT_ENA_INT
#define TOPPERS_SUPPORT_ENA_INT			/* ena_int�����ݡ��Ȥ���Ƥ��� */
#endif /* TOPPERS_TARGET_SUPPORT_ENA_INT */

#ifdef TOPPERS_TARGET_SUPPORT_GET_UTM
#define TOPPERS_SUPPORT_GET_UTM			/* get_utm�����ݡ��Ȥ���Ƥ��� */
#endif /* TOPPERS_TARGET_SUPPORT_GET_UTM */

#define TOPPERS_SUPPORT_MUTEX			/* �ߥ塼�ƥå�����ǽ��ĥ */

#ifdef TOPPERS_TARGET_SUPPORT_OVRHDR
#define TOPPERS_SUPPORT_OVRHDR			/* �����Х��ϥ�ɥ鵡ǽ��ĥ */
#endif /* TOPPERS_TARGET_SUPPORT_OVRHDR */

#define TOPPERS_SUPPORT_PROTECT			/* �ݸǽ�б��Υ����ͥ� */

#ifdef TOPPERS_TARGET_SUPPORT_ATT_MOD
#define TOPPERS_SUPPORT_ATT_MOD			/* ATT_MOD�����ݡ��Ȥ���Ƥ��� */
#endif /* TOPPERS_TARGET_SUPPORT_ATT_MOD */

#ifdef TOPPERS_TARGET_SUPPORT_ATT_PMA
#define TOPPERS_SUPPORT_ATT_PMA			/* ATT_PMA�����ݡ��Ȥ���Ƥ��� */
#endif /* TOPPERS_TARGET_SUPPORT_ATT_PMA */

/*
 *  ͥ���٤��ϰ�
 */
#define TMIN_TPRI		1			/* ������ͥ���٤κǾ��͡ʺǹ��͡�*/
#define TMAX_TPRI		16			/* ������ͥ���٤κ����͡ʺ����͡�*/
#define TMIN_DPRI		1			/* �ǡ���ͥ���٤κǾ��͡ʺǹ��͡�*/
#define TMAX_DPRI		16			/* �ǡ���ͥ���٤κ����͡ʺ����͡�*/
#define TMIN_MPRI		1			/* ��å�����ͥ���٤κǾ��͡ʺǹ��͡�*/
#define TMAX_MPRI		16			/* ��å�����ͥ���٤κ����͡ʺ����͡�*/
#define TMIN_ISRPRI		1			/* ����ߥ����ӥ��롼����ͥ���٤κǾ��� */
#define TMAX_ISRPRI		16			/* ����ߥ����ӥ��롼����ͥ���٤κ����� */

/*
 *  �С���������
 */
#define TKERNEL_MAKER	UINT_C(0x0118)	/* �����ͥ�Υ᡼���������� */
#define TKERNEL_PRID	UINT_C(0x0006)	/* �����ͥ�μ����ֹ� */
#define TKERNEL_SPVER	UINT_C(0xf515)	/* �����ͥ���ͤΥС�������ֹ� */
#define TKERNEL_PRVER	UINT_C(0x2010)	/* �����ͥ�ΥС�������ֹ� */

/*
 *  ���塼���󥰲���κ�����
 */
#define TMAX_ACTCNT		UINT_C(1)		/* ��ư�׵ᥭ�塼���󥰿��κ����� */
#define TMAX_WUPCNT		UINT_C(1)		/* �����׵ᥭ�塼���󥰿��κ����� */

/*
 *  �ӥåȥѥ�����Υӥåȿ�
 */
#ifndef TBIT_TEXPTN					/* �������㳰�װ��Υӥåȿ� */
#define TBIT_TEXPTN		(sizeof(TEXPTN) * CHAR_BIT)
#endif /* TBIT_TEXPTN */

#ifndef TBIT_FLGPTN					/* ���٥�ȥե饰�Υӥåȿ� */
#define TBIT_FLGPTN		(sizeof(FLGPTN) * CHAR_BIT)
#endif /* TBIT_FLGPTN */

/*
 *  �ץ��å����֡�OVRTIM�ˤκ�����
 */
#ifndef TMAX_OVRTIM
#define TMAX_OVRTIM		ULONG_MAX
#endif /* TMAX_OVRTIM */

/*
 *  �����ΰ���ݤΤ���Υޥ���
 *
 *  �ʲ���TOPPERS_COUNT_SZ��TOPPERS_ROUND_SZ������ϡ�unit��2�ζҾ�Ǥ�
 *  �뤳�Ȥ��ꤷ�Ƥ��롥
 */
#ifndef TOPPERS_COUNT_SZ
#define TOPPERS_COUNT_SZ(sz, unit)	(((sz) + (unit) - 1) / (unit))
#endif /* TOPPERS_COUNT_SZ */
#ifndef TOPPERS_ROUND_SZ
#define TOPPERS_ROUND_SZ(sz, unit)	(((sz) + (unit) - 1) & ~((unit) - 1))
#endif /* TOPPERS_ROUND_SZ */

#define COUNT_STK_T(sz)		TOPPERS_COUNT_SZ(sz, sizeof(STK_T))
#define ROUND_STK_T(sz)		TOPPERS_ROUND_SZ(sz, sizeof(STK_T))

#define COUNT_MPF_T(blksz)	TOPPERS_COUNT_SZ(blksz, sizeof(MPF_T))
#define ROUND_MPF_T(blksz)	TOPPERS_ROUND_SZ(blksz, sizeof(MPF_T))

/*
 *  ����¾�ι������
 */
#define TMAX_MAXSEM		UINT_MAX	/* ���ޥե��κ���񸻿��κ����� */

#ifdef __cplusplus
}
#endif

#endif /* TOPPERS_KERNEL_H */
