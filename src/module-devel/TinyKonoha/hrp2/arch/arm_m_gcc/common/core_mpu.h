/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 *	
 *	Copyright (C) 2012 by Embedded and Real-Time Systems Laboratory
 *				Graduate School of Information Science, Nagoya Univ., JAPAN
 *	
 *	�嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *	�����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *	�ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *	(1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *		��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *		����������˴ޤޤ�Ƥ��뤳�ȡ�
 *	(2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *		�ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *		�ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *		��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *	(3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *		�ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *		�ȡ�
 *	  (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *		  �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *	  (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *		  ��𤹤뤳�ȡ�
 *	(4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *		������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *		�ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *		ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *		���դ��뤳�ȡ�
 *	
 *	�ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *	���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *	���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *	�������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *	����Ǥ�����ʤ���
 *	
 */

/*
 *	MPU�ɥ饤��
 */

#ifndef TOPPERS_CORE_MPU_H
#define TOPPERS_CORE_MPU_H

/*
 *  MPU�����ץ쥸����
 *  [- 31:24] [IREGION 23:16] [DREGION 15:8] [- 7:1] SEPARATE
 */
#define MPU_TYPE    0xe000ed90
#define MPU_TYPE_IREGION    0x00ff0000
#define MPU_TYPE_DREGION    0x0000ff00
#define MPU_TYPE_SEPARATE   0x00000001

/*
 *  MPU����쥸����
 *  [- 31:2] PRIVDEFENA HFNMIENA ENABLE
 */
#define MPU_CR      0xe000ed94
#define MPU_CR_PRIVDEFENA   0x00000004 
#define MPU_CR_HFNMIENA     0x00000002 
#define MPU_CR_ENABLE       0x00000001

/*
 *  MPU�ΰ��ֹ�쥸����
 *  [- 31:8] [REGION 7:0]
 */
#define MPU_REGNO   0xe000ed98
#define MPU_REGNO_REGION    0x000000ff

/*
 *  MPU�ΰ�١������ɥ쥹�쥸����
 *  [ADDR 31:N] [VALID 4] [REGION 3:0]
 */
#define MPU_REGBASE 0xe000ed9c
#define MPU_REGBASE_ADDR    0xffffffe0 /* �١������ɥ쥹�ե������ */
#define MPU_REGBASE_VALID   0x00000010 /* �ΰ��ֹ�ͭ���ӥå� */
#define MPU_REGBASE_REGION  0x0000000f /* �ΰ��ֹ楪���Х饤�ɥե������ */

/*
 *  MPU�ΰ�°������ӥ������쥸����
 *  [- 31:29] XN - [AP 26:24] [- 23:22] [TEX 21:19] S C B [SRD 15:8] [- 7:6] [SIZE 5:1] ENABLE
 */
#define MPU_REGATR  0xe000eda0
#define MPU_REGATR_XN 0x10000000 /* ̿�ᥢ�������ػߥӥå� */
#define MPU_REGATR_AP 0x07000000 /* �ǡ��������������ĥե������ */
#define TO_MPU_AP(ap) (ap << 24)

/*
 *  �ǡ��������������ĥѥ�����
 */
#define MPU_AP_NOT      0x00 /* ���������ػ� */
#define MPU_AP_PRW      0x01 /* �ø��Τߥ���������ǽ */
#define MPU_AP_PRWUR    0x02 /* �桼�����ɽФ��Τ߲�ǽ���ø��ϥ���������ǽ */
#define MPU_AP_PURW     0x03 /* �桼�����ø��Ȥ�˥���������ǽ */
#define MPU_AP_PR       0x05 /* �ø��Τ��ɽФ�����������ǽ */
#define MPU_AP_PUR      0x06 /* �桼�����ø��Ȥ���ɽФ�����������ǽ */

#define MPU_REGATR_TEX  0x00380000 /* �����׳�ĥ�ե������ */
#define MPU_REGATR_S    0x00040000 /* ��ͭ�ĥӥå� */
#define MPU_REGATR_C    0x00020000 /* ����å���ĥӥå� */
#define MPU_REGATR_B    0x00010000 /* �Хåե��ĥӥå� */
#define MPU_REGATR_SRD  0x0000ff00 /* �����ΰ�ػߥե������ */
#define MPU_REGATR_SIZE 0x0000003e /* �ΰ襵�����ե������ */
#define TO_MPU_SIZE(size) (size << 1)
#define MPU_REGATR_ENABLE   0x00000001 /* �ΰ���ĥӥå� */

/*
 *  MPU�����ꥢ��1�ΰ�١������ɥ쥹�쥸����
 */
#define MPU_AL1BASE 0xe000eda4

/*
 *  MPU�����ꥢ��1�ΰ�°������ӥ������쥸����
 */
#define MPU_AL1ATR  0xe000eda8

/*
 *  MPU�����ꥢ��2�ΰ�١������ɥ쥹�쥸����
 */
#define MPU_AL2BASE 0xe000edac

/*
 *  MPU�����ꥢ��2�ΰ�°������ӥ������쥸����
 */
#define MPU_AL2ATR  0xe000edb0

/*
 *  MPU�����ꥢ��3�ΰ�١������ɥ쥹�쥸����
 */
#define MPU_AL3BASE 0xe000edb4

/*
 *  MPU�����ꥢ��3�ΰ�°������ӥ������쥸����
 */
#define MPU_AL3ATR  0xe000edb8

/*
 *  �㳰�ֹ�����
 */
// �����ݸ��ȿ
#define EXCNO_MEM_MNG       0x04

#ifndef TOPPERS_MACRO_ONLY
// ������롼���� 
extern void target_mpu_initialize(void);
// �����ݸ��ȿ�㳰�ϥ�ɥ�
extern void target_mpu_exc_handler(void *p_excinf);
// �������㳰�¹Գ��ϻ������å������ϥ�ɥ�
extern void target_emulate_texrtn_handler(void *p_excinf);
// �������㳰�꥿����������å������ϥ�ɥ�
extern void target_emulate_ret_tex_handler(void *p_excinf);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_CORE_MPU_H */
