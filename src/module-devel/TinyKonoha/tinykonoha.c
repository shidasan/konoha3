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
 *  $Id: tinykonoha.c 837 2012-12-26 15:09:59Z ertl-hiro $
 */

/* 
 *  ����ץ�ץ����(1)������
 *
 *  HRP2�����ͥ�δ���Ū��ư����ǧ���뤿��Υ���ץ�ץ���ࡥ
 *
 *  �ץ����γ���:
 *
 *  �桼�����󥿥ե�������������ĥᥤ�󥿥����ʥ�����ID: MAIN_TASK��ͥ
 *  ����: MAIN_PRIORITY�ˤȡ�3�Ĥ��¹Լ¹Ԥ���륿�����ʥ�����ID:
 *  TASK1��TASK3�����ͥ����: MID_PRIORITY�ˤǹ�������롥�ޤ�����ư��
 *  ����2�äμ����ϥ�ɥ�ʼ����ϥ�ɥ�ID: CYCHDR1�ˤ��Ѥ��롥
 *
 *  �¹Լ¹Ԥ���륿�����ϡ�task_loop����롼�פ�¹Ԥ����٤ˡ���������
 *  �¹���Ǥ��뤳�Ȥ򤢤�魯��å�������ɽ�����롥���롼�פ�¹Ԥ���
 *  �Τϡ����롼�פʤ��ǥ�å���������Ϥ���ȡ�¿�̤Υ�å�����������
 *  ���졤�ץ�����ư���ǧ�����餯�ʤ뤿��Ǥ��롥�ޤ�����®�ʥ�
 *  �ꥢ��ݡ��Ȥ��Ѥ��ƥ�å���������Ϥ�����ˡ����٤ƤΥ�å�����
 *  �����ϤǤ���褦�ˡ���å��������̤����¤���Ȥ�����ͳ�⤢�롥
 *
 *  �����ϥ�ɥ�ϡ����Ĥ�ͥ���١�HIGH_PRIORITY��MID_PRIORITY��
 *  LOW_PRIORITY�ˤΥ�ǥ����塼���ž�����롥�ץ����ε�ưľ��ϡ�
 *  �����ϥ�ɥ����߾��֤ˤʤäƤ��롥
 *
 *  �ᥤ�󥿥����ϡ����ꥢ��I/O�ݡ��Ȥ����ʸ�����Ϥ�Ԥ���ʸ�����Ϥ�
 *  �ԤäƤ���֤ϡ��¹Լ¹Ԥ���륿�������¹Ԥ���Ƥ���ˡ����Ϥ��줿
 *  ʸ�����б�����������¹Ԥ��롥���Ϥ��줿ʸ���Ƚ����δط��ϼ����̤ꡥ
 *  Control-C�ޤ���'Q'�����Ϥ����ȡ��ץ�����λ���롥
 *
 *  '1' : �оݥ�������TASK1���ڤ괹����ʽ������ˡ�
 *  '2' : �оݥ�������TASK2���ڤ괹���롥
 *  '3' : �оݥ�������TASK3���ڤ괹���롥
 *  '4' : �оݥ���������TASK1��act_tsk�ˤ�굯ư���롥
 *  '5' : �оݥ���������TASK2��act_tsk�ˤ�굯ư���롥
 *  '6' : �оݥ���������TASK3��act_tsk�ˤ�굯ư���롥
 *  'a' : �оݥ�������act_tsk�ˤ�굯ư���롥
 *  'A' : �оݥ��������Ф��뵯ư�׵��can_act�ˤ�ꥭ��󥻥뤹�롥
 *  'e' : �оݥ�������ext_tsk��ƤӽФ�������λ�����롥
 *  't' : �оݥ�������ter_tsk�ˤ�궯����λ���롥
 *  '>' : �оݥ�������ͥ���٤�HIGH_PRIORITY�ˤ��롥
 *  '=' : �оݥ�������ͥ���٤�MID_PRIORITY�ˤ��롥
 *  '<' : �оݥ�������ͥ���٤�LOW_PRIORITY�ˤ��롥
 *  'G' : �оݥ�������ͥ���٤�get_pri���ɤ߽Ф���
 *  's' : �оݥ�������slp_tsk��ƤӽФ����������Ԥ��ˤ����롥
 *  'S' : �оݥ�������tslp_tsk(10��)��ƤӽФ����������Ԥ��ˤ����롥
 *  'w' : �оݥ�������wup_tsk�ˤ�굯�����롥
 *  'W' : �оݥ��������Ф��뵯���׵��can_wup�ˤ�ꥭ��󥻥뤹�롥
 *  'l' : �оݥ�������rel_wai�ˤ�궯��Ū���Ԥ�����ˤ��롥
 *  'u' : �оݥ�������sus_tsk�ˤ�궯���Ԥ����֤ˤ��롥
 *  'm' : �оݥ������ζ����Ԥ����֤�rsm_tsk�ˤ�������롥
 *  'd' : �оݥ�������dly_tsk(10��)��ƤӽФ��������ַв��Ԥ��ˤ����롥
 *  'x' : �оݥ��������㳰�ѥ�����0x0001���㳰�������׵᤹�롥
 *  'X' : �оݥ��������㳰�ѥ�����0x0002���㳰�������׵᤹�롥
 *  'y' : �оݥ�������dis_tex��ƤӽФ������������㳰��ػߤ��롥
 *  'Y' : �оݥ�������ena_tex��ƤӽФ������������㳰����Ĥ��롥
 *  'r' : 3�Ĥ�ͥ���١�HIGH_PRIORITY��MID_PRIORITY��LOW_PRIORITY�ˤΥ�
 *        �ǥ����塼���ž�����롥
 *  'c' : �����ϥ�ɥ��ư��Ϥ����롥
 *  'C' : �����ϥ�ɥ��ư����ߤ����롥
 *  'b' : ���顼��ϥ�ɥ��5�ø�˵�ư����褦ư��Ϥ����롥
 *  'B' : ���顼��ϥ�ɥ��ư����ߤ����롥
 *  'z' : �оݥ�������CPU�㳰��ȯ��������ʥ�������λ������ˡ�
 *  'Z' : �оݥ�������CPU��å����֤�CPU�㳰��ȯ��������ʥץ�����
 *        ��λ����ˡ�
 *  'V' : get_utm����ǽɾ���ѥ����ƥ�����2���ɤࡥ
 *  'o' : �оݥ��������Ф��ƥ����Х��ϥ�ɥ��ư��Ϥ�����
 *  'O' : �оݥ��������Ф��ƥ����Х��ϥ�ɥ��ư����ߤ�����
 *  'v' : ȯ�Ԥ��������ƥॳ�����ɽ������ʥǥե���ȡˡ�
 *  'q' : ȯ�Ԥ��������ƥॳ�����ɽ�����ʤ���
 */

#define __TOPPERS__

#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"

#include <stdlib.h>

#include "tinykonoha.h"
#include "allocate.h"

#include "stm32f2xx.h"
#include "stm32f2xx_conf.h"

#include "minikonoha/minikonoha.h"
#include "minikonoha/sugar.h"
#include "minikonoha/klib.h"
#include "minikonoha/platform.h"

/*
 *  �����ӥ�������Υ��顼�Υ�����
 */
Inline void
svc_perror(const char *file, int_t line, const char *expr, ER ercd)
{
	if (ercd < 0) {
		t_perror(LOG_ERROR, file, line, expr, ercd);
	}
}

#define	SVC_PERROR(expr)	svc_perror(__FILE__, __LINE__, #expr, (expr))

/*
 *  �¹Լ¹Ԥ���륿�����ؤΥ�å������ΰ�
 */
char	message[3];

/*
 *  �롼�ײ��
 */
ulong_t	task_loop;		/* ��������ǤΥ롼�ײ�� */
ulong_t	tex_loop;		/* �㳰�����롼������ǤΥ롼�ײ�� */

/*
 *  �¹Ԥ��Ƽ¹Ԥ���륿�����ѤΥ������㳰�����롼����
 */
void tex_routine(TEXPTN texptn, intptr_t exinf)
{
	volatile ulong_t	i;
	int_t	tskno = (int_t) exinf;

	syslog(LOG_NOTICE, "task%d receives exception 0x%04x.", tskno, texptn);
	for (i = 0; i < tex_loop; i++);

	if ((texptn & 0x8000U) != 0U) {
		syslog(LOG_INFO, "#%d#ext_tsk()", tskno);
		SVC_PERROR(ext_tsk());
		assert(0);
	}
}

/*
 *  CPU�㳰�ϥ�ɥ�
 */
#ifdef CPUEXC1

void
cpuexc_handler(void *p_excinf)
{
	ID		tskid;

	syslog(LOG_NOTICE, "CPU exception handler (p_excinf = %08p).", p_excinf);
	if (sns_ctx() != true) {
		syslog(LOG_WARNING,
					"sns_ctx() is not true in CPU exception handler.");
	}
	if (sns_dpn() != true) {
		syslog(LOG_WARNING,
					"sns_dpn() is not true in CPU exception handler.");
	}
	syslog(LOG_INFO, "sns_loc = %d sns_dsp = %d sns_tex = %d",
									sns_loc(), sns_dsp(), sns_tex());
	syslog(LOG_INFO, "xsns_dpn = %d xsns_xpn = %d",
									xsns_dpn(p_excinf), xsns_xpn(p_excinf));

	if (xsns_xpn(p_excinf)) {
		syslog(LOG_NOTICE, "Sample program ends with exception.");
		SVC_PERROR(ext_ker());
		assert(0);
	}

	SVC_PERROR(iget_tid(&tskid));
	SVC_PERROR(iras_tex(tskid, 0x8000U));
}

#endif /* CPUEXC1 */

/*
 *  �����ϥ�ɥ�
 *
 *  HIGH_PRIORITY��MID_PRIORITY��LOW_PRIORITY �γ�ͥ���٤Υ�ǥ����塼
 *  ���ž�����롥
 */
void cyclic_handler(intptr_t exinf)
{
	SVC_PERROR(irot_rdq(HIGH_PRIORITY));
	SVC_PERROR(irot_rdq(MID_PRIORITY));
	SVC_PERROR(irot_rdq(LOW_PRIORITY));
}

/*
 *  ���顼��ϥ�ɥ�
 *
 *  HIGH_PRIORITY��MID_PRIORITY��LOW_PRIORITY �γ�ͥ���٤Υ�ǥ����塼
 *  ���ž�����롥
 */
void alarm_handler(intptr_t exinf)
{
	SVC_PERROR(irot_rdq(HIGH_PRIORITY));
	SVC_PERROR(irot_rdq(MID_PRIORITY));
	SVC_PERROR(irot_rdq(LOW_PRIORITY));
}

/*
 *  �����Х��ϥ�ɥ�
 */
#ifdef TOPPERS_SUPPORT_OVRHDR

void
overrun_handler(ID tskid, intptr_t exinf)
{
	int_t		tskno = (int_t) exinf;

	syslog(LOG_NOTICE, "Overrun handler for task%d.", tskno);
	syslog(LOG_INFO, "#iras_tex(%d, 0x0004U)", tskno);
	SVC_PERROR(iras_tex(tskid, 0x0004U));
}

#endif /* TOPPERS_SUPPORT_OVRHDR */

static kbool_t Konoha_ParseCommandOption(KonohaContext* kctx, int argc, char **argv)
{
	kbool_t ret = true;
	int scriptidx = 0;
	KBaseTrace(trace);
	//scriptidx = optind;
	//CommandLine_SetARGV(kctx, argc - scriptidx, argv + scriptidx, trace);
	//if(scriptidx < argc) {
		ret = Konoha_LoadScript(kctx, argv[scriptidx]);
	//}
	return ret;
}

int ExtSRAM_Initialize(void)
{
	int result = 0;
	
	FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef p;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable the FSMC Clock */
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOG | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF, ENABLE);
	
	/*-- GPIO Configuration ------------------------------------------------------*/
	/* SRAM Data lines configuration */
	GPIO_InitStructure.GPIO_Pin =	GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 |
									GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);
	
	GPIO_InitStructure.GPIO_Pin =	GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
									GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
									GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15, GPIO_AF_FSMC);
	
	/* SRAM Address lines configuration */
	GPIO_InitStructure.GPIO_Pin =	GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
									GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12 | GPIO_Pin_13 |
									GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource2, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource3, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource4, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource5, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource12, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource13, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource15, GPIO_AF_FSMC);
	
	GPIO_InitStructure.GPIO_Pin =	GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
									GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource2, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource3, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource4, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource5, GPIO_AF_FSMC);
	
	GPIO_InitStructure.GPIO_Pin =	GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_FSMC);
	
	/* NOE and NWE configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);
	
	/* NE1 configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_FSMC);
	
	/* NBL0, NBL1 configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_FSMC);

	/*-- FSMC Configuration ------------------------------------------------------*/
	p.FSMC_AddressSetupTime = 0;
	p.FSMC_AddressHoldTime = 0;
	p.FSMC_DataSetupTime = 4;
	p.FSMC_BusTurnAroundDuration = 1;
	p.FSMC_CLKDivision = 0;
	p.FSMC_DataLatency = 0;
	p.FSMC_AccessMode = FSMC_AccessMode_A;
	
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;
	
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);
		
	/* Enable FSMC Bank1_SRAM Bank */
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1 , ENABLE);
	
	memset((void *)EXT_SRAM_BASE_ADDRESS, 0x00, EXT_SRAM_SIZE);
	
	return (result ? -1 : 0);
}

/*
 *  �ᥤ�󥿥���
 */
void main_task(intptr_t exinf)
{
	int argc = 0;
	char **argv = {"noname"};
	struct KonohaFactory factory = {};
	int sram = ExtSRAM_Initialize();
	heap_init();
	KonohaFactory_SetDefaultFactory(&factory, ToppersFactory, argc, argv);
	KonohaContext *konoha = KonohaFactory_CreateKonoha(&factory);
	Konoha_ParseCommandOption(konoha, argc, argv);
}
//void main_task(intptr_t exinf)
//{
//	char	c;
//	//ID		tskid = TASK1;
//	int_t	tskno = 1;
//	ER_UINT	ercd;
//	PRI		tskpri;
//#ifndef TASK_LOOP
//	volatile ulong_t	i;
//	SYSTIM	stime1, stime2;
//#endif /* TASK_LOOP */
//#ifdef TOPPERS_SUPPORT_GET_UTM
//	SYSUTM	utime1, utime2;
//#endif /* TOPPERS_SUPPORT_GET_UTM */
//
//	SVC_PERROR(syslog_msk_log(LOG_UPTO(LOG_INFO), LOG_UPTO(LOG_EMERG)));
//	syslog(LOG_NOTICE, "Sample program starts (exinf = %d).", (int_t) exinf);
//
//	/*
//	 *  ���ꥢ��ݡ��Ȥν����
//	 *
//	 *  �����ƥ����������Ʊ�����ꥢ��ݡ��Ȥ�Ȥ����ʤɡ����ꥢ��
//	 *  �ݡ��Ȥ������ץ�Ѥߤξ��ˤϤ�����E_OBJ���顼�ˤʤ뤬���پ��
//	 *  �ʤ���
//	 */
//	ercd = serial_opn_por(TASK_PORTID);
//	if (ercd < 0 && MERCD(ercd) != E_OBJ) {
//		syslog(LOG_ERROR, "%s (%d) reported by `serial_opn_por'.",
//									itron_strerror(ercd), SERCD(ercd));
//	}
//	SVC_PERROR(serial_ctl_por(TASK_PORTID,
//							(IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV)));
//
//	/*
// 	 *  �롼�ײ��������
//	 *
//	 *  �¹Լ¹Ԥ���륿������Ǥζ��롼�פβ����task_loop�ˤϡ����롼
//	 *  �פμ¹Ի��֤���0.4�äˤʤ�褦�����ꤹ�롥��������Τ���ˡ�
//	 *  LOOP_REF��ζ��롼�פμ¹Ի��֤򡤤��������get_tim��Ƥ֤��Ȥ�
//	 *  ¬�ꤷ������¬���̤�����롼�פμ¹Ի��֤�0.4�äˤʤ�롼�ײ�
//	 *  �����ᡤtask_loop�����ꤹ�롥
//	 *
//	 *  LOOP_REF�ϡ��ǥե���ȤǤ�1,000,000�����ꤷ�Ƥ��뤬�����ꤷ����
//	 *  ���٤��ץ��å��Ǥϡ�����ץ�ץ����μ¹Գ��Ϥ˻��֤�����
//	 *  �ꤹ����Ȥ�������������롥�դ����ꤷ�����®���ץ��å��Ǥϡ�
//	 *  LOOP_REF��ζ��롼�פμ¹Ի��֤�û���ʤꡤtask_loop�����ꤹ����
//	 *  �θ����礭���ʤ�Ȥ������꤬���롥
//	 *
//	 *  �����ǡ����Τ褦�ʥ������åȤǤϡ�target_test.h�ǡ�LOOP_REF��Ŭ
//	 *  �ڤ��ͤ��������Τ�˾�ޤ�����
//	 *
//	 *  �ޤ���task_loop���ͤ���ꤷ�������ˤϡ������ͤ�TASK_LOOP�˥�
//	 *  ����������롥TASK_LOOP���ޥ����������Ƥ����硤�嵭��¬���
//	 *  �Ԥ鷺�ˡ�TASK_LOOP��������줿�ͤ���롼�פβ���Ȥ��롥
//	 *
//	 * �������åȤˤ�äƤϡ����롼�פμ¹Ի��֤�1���ܤ�¬��ǡ������
//	 * ���Ĺ��ˤʤ��Τ����롥���Τ褦�ʥ������åȤǤϡ�MEASURE_TWICE
//	 * ��ޥ���������뤳�Ȥǡ�1���ܤ�¬���̤�ΤƤơ�2���ܤ�¬����
//	 * ��Ȥ���
//	 *
//	 *  �������㳰�����롼������Ǥζ��롼�פβ����tex_loop�ˤϡ�
//	 *  task_loop��4ʬ��1���͡ʶ��롼�פμ¹Ի��֤�0.1�äˤʤ�롼�ײ�
//	 *  ���ˤ����ꤹ�롥
//	 */
//#ifdef TASK_LOOP
//	task_loop = TASK_LOOP;
//#else /* TASK_LOOP */
//
//#ifdef MEASURE_TWICE
//	task_loop = LOOP_REF;
//	SVC_PERROR(get_tim(&stime1));
//	for (i = 0; i < task_loop; i++);
//	SVC_PERROR(get_tim(&stime2));
//#endif /* MEASURE_TWICE */
//
//	task_loop = LOOP_REF;
//	SVC_PERROR(get_tim(&stime1));
//	for (i = 0; i < task_loop; i++);
//	SVC_PERROR(get_tim(&stime2));
//	task_loop = LOOP_REF * 400UL / (stime2 - stime1);
//
//#endif /* TASK_LOOP */
//	tex_loop = task_loop / 4;
//
//	/*
// 	 *  �������ε�ư
//	 */
//	//SVC_PERROR(act_tsk(TASK1));
//	//SVC_PERROR(act_tsk(TASK2));
//	//SVC_PERROR(act_tsk(TASK3));
//
//	/*
// 	 *  �ᥤ��롼��
//	 */
//	do {
//		SVC_PERROR(serial_rea_dat(TASK_PORTID, &c, 1));
//		switch (c) {
//		case '4':
//		case '5':
//		case '6':
//		case 'e':
//		case 's':
//		case 'S':
//		case 'd':
//		case 'y':
//		case 'Y':
//		case 'z':
//		case 'Z':
//			message[tskno-1] = c;
//			break;
//		case '1':
//			tskno = 1;
//			tskid = TASK1;
//			break;
//		case '2':
//			tskno = 2;
//			tskid = TASK2;
//			break;
//		case '3':
//			tskno = 3;
//			tskid = TASK3;
//			break;
//		case 'a':
//			syslog(LOG_INFO, "#act_tsk(%d)", tskno);
//			SVC_PERROR(act_tsk(tskid));
//			break;
//		case 'A':
//			syslog(LOG_INFO, "#can_act(%d)", tskno);
//			SVC_PERROR(ercd = can_act(tskid));
//			if (ercd >= 0) {
//				syslog(LOG_NOTICE, "can_act(%d) returns %d", tskno, ercd);
//			}
//			break;
//		case 't':
//			syslog(LOG_INFO, "#ter_tsk(%d)", tskno);
//			SVC_PERROR(ter_tsk(tskid));
//			break;
//		case '>':
//			syslog(LOG_INFO, "#chg_pri(%d, HIGH_PRIORITY)", tskno);
//			SVC_PERROR(chg_pri(tskid, HIGH_PRIORITY));
//			break;
//		case '=':
//			syslog(LOG_INFO, "#chg_pri(%d, MID_PRIORITY)", tskno);
//			SVC_PERROR(chg_pri(tskid, MID_PRIORITY));
//			break;
//		case '<':
//			syslog(LOG_INFO, "#chg_pri(%d, LOW_PRIORITY)", tskno);
//			SVC_PERROR(chg_pri(tskid, LOW_PRIORITY));
//			break;
//		case 'G':
//			syslog(LOG_INFO, "#get_pri(%d, &tskpri)", tskno);
//			SVC_PERROR(ercd = get_pri(tskid, &tskpri));
//			if (ercd >= 0) {
//				syslog(LOG_NOTICE, "priority of task %d is %d", tskno, tskpri);
//			}
//			break;
//		case 'w':
//			syslog(LOG_INFO, "#wup_tsk(%d)", tskno);
//			SVC_PERROR(wup_tsk(tskid));
//			break;
//		case 'W':
//			syslog(LOG_INFO, "#can_wup(%d)", tskno);
//			SVC_PERROR(ercd = can_wup(tskid));
//			if (ercd >= 0) {
//				syslog(LOG_NOTICE, "can_wup(%d) returns %d", tskno, ercd);
//			}
//			break;
//		case 'l':
//			syslog(LOG_INFO, "#rel_wai(%d)", tskno);
//			SVC_PERROR(rel_wai(tskid));
//			break;
//		case 'u':
//			syslog(LOG_INFO, "#sus_tsk(%d)", tskno);
//			SVC_PERROR(sus_tsk(tskid));
//			break;
//		case 'm':
//			syslog(LOG_INFO, "#rsm_tsk(%d)", tskno);
//			SVC_PERROR(rsm_tsk(tskid));
//			break;
//		case 'x':
//			syslog(LOG_INFO, "#ras_tex(%d, 0x0001U)", tskno);
//			SVC_PERROR(ras_tex(tskid, 0x0001U));
//			break;
//		case 'X':
//			syslog(LOG_INFO, "#ras_tex(%d, 0x0002U)", tskno);
//			SVC_PERROR(ras_tex(tskid, 0x0002U));
//			break;
//		case 'r':
//			syslog(LOG_INFO, "#rot_rdq(three priorities)");
//			SVC_PERROR(rot_rdq(HIGH_PRIORITY));
//			SVC_PERROR(rot_rdq(MID_PRIORITY));
//			SVC_PERROR(rot_rdq(LOW_PRIORITY));
//			break;
//		case 'c':
//			syslog(LOG_INFO, "#sta_cyc(1)");
//			SVC_PERROR(sta_cyc(CYCHDR1));
//			break;
//		case 'C':
//			syslog(LOG_INFO, "#stp_cyc(1)");
//			SVC_PERROR(stp_cyc(CYCHDR1));
//			break;
//		case 'b':
//			syslog(LOG_INFO, "#sta_alm(1, 5000)");
//			SVC_PERROR(sta_alm(ALMHDR1, 5000));
//			break;
//		case 'B':
//			syslog(LOG_INFO, "#stp_alm(1)");
//			SVC_PERROR(stp_alm(ALMHDR1));
//			break;
//
//		case 'V':
//#ifdef TOPPERS_SUPPORT_GET_UTM
//			SVC_PERROR(get_utm(&utime1));
//			SVC_PERROR(get_utm(&utime2));
//			syslog(LOG_NOTICE, "utime1 = %ld, utime2 = %ld",
//										(ulong_t) utime1, (ulong_t) utime2);
//#else /* TOPPERS_SUPPORT_GET_UTM */
//			syslog(LOG_NOTICE, "get_utm is not supported.");
//#endif /* TOPPERS_SUPPORT_GET_UTM */
//			break;
//
//		case 'o':
//#ifdef TOPPERS_SUPPORT_OVRHDR
//			syslog(LOG_INFO, "#sta_ovr(%d, 2000000)", tskno);
//			SVC_PERROR(sta_ovr(tskid, 2000000));
//#else /* TOPPERS_SUPPORT_OVRHDR */
//			syslog(LOG_NOTICE, "sta_ovr is not supported.");
//#endif /* TOPPERS_SUPPORT_OVRHDR */
//			break;
//		case 'O':
//#ifdef TOPPERS_SUPPORT_OVRHDR
//			syslog(LOG_INFO, "#stp_ovr(%d)", tskno);
//			SVC_PERROR(stp_ovr(tskid));
//#else /* TOPPERS_SUPPORT_OVRHDR */
//			syslog(LOG_NOTICE, "stp_ovr is not supported.");
//#endif /* TOPPERS_SUPPORT_OVRHDR */
//			break;
//
//		case 'v':
//			SVC_PERROR(syslog_msk_log(LOG_UPTO(LOG_INFO),
//										LOG_UPTO(LOG_EMERG)));
//			break;
//		case 'q':
//			SVC_PERROR(syslog_msk_log(LOG_UPTO(LOG_NOTICE),
//										LOG_UPTO(LOG_EMERG)));
//			break;
//
//#ifdef BIT_KERNEL
//		case ' ':
//			SVC_PERROR(loc_cpu());
//			{
//				extern ER	bit_kernel(void);
//
//				SVC_PERROR(ercd = bit_kernel());
//				if (ercd >= 0) {
//					syslog(LOG_NOTICE, "bit_kernel passed.");
//				}
//			}
//			SVC_PERROR(unl_cpu());
//			break;
//#endif /* BIT_KERNEL */
//
//		default:
//			break;
//		}
//	} while (c != '\003' && c != 'Q');
//
//	syslog(LOG_NOTICE, "Sample program ends.");
//	SVC_PERROR(ext_ker());
//	assert(0);
//}
