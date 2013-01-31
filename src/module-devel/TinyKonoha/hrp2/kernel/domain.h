/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 * 
 *  Copyright (C) 2008-2010 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: domain.h 263 2010-02-14 05:32:25Z ertl-hiro $
 */

/*
 *		�ݸ�ɥᥤ������⥸�塼��
 */

#ifndef TOPPERS_DOMAIN_H
#define TOPPERS_DOMAIN_H

#ifndef TOPPERS_MACRO_ONLY

/*
 *  �ݸ�ɥᥤ�������֥�å�
 */
typedef struct domain_initialization_block {
	ACPTN		domptn;			/* �ݸ�ɥᥤ��Υӥåȥѥ����� */
#ifdef USE_DOMINICTXB
	DOMINICTXB	domctxb;		/* �ݸ�ɥᥤ����������ƥ����ȥ֥�å� */
#endif /* USE_DOMINICTXB */
} DOMINIB;

/*
 *  �ݸ�ɥᥤ��ID�κ����͡�kernel_cfg.c��
 */
extern const ID	tmax_domid;

/*
 *  �ݸ�ɥᥤ�������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern const DOMINIB	dominib_table[];

/*
 *  �����ͥ�ɥᥤ����ݸ�ɥᥤ�������֥�å���kernel_cfg.c��
 */
extern const DOMINIB	dominib_kernel;

/*
 *  �ݸ�ɥᥤ��ID�����ݸ�ɥᥤ�������֥�å�����Ф�����Υޥ���
 */
#define INDEX_DOM(domid)	((uint_t)((domid) - TMIN_DOMID))
#define get_dominib(domid)	(&(dominib_table[INDEX_DOM(domid)]))

/*
 *  �ݸ�ɥᥤ�������֥�å������ݸ�ɥᥤ��ID����Ф�����Υޥ���
 */
#define	DOMID(p_dominib)	(((p_dominib) == &dominib_kernel) ? TDOM_KERNEL \
							: (ID)(((p_dominib) - dominib_table) + TMIN_DOMID))

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_DOMAIN_H_ */
