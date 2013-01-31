/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
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
 */

/*
 * �������åȰ�¸�⥸�塼���STM32P207�ѡ�
 */
#include "kernel_impl.h"
#include <sil.h>
#include "stm32p207.h"
#include "usart.h"
#include "task.h"
#include "memory.h"

/*
 * �������åȰ�¸�������������
 */
void
target_initialize(void)
{
	/*
	 *  �ץ��å�����å�(RCC)�ν����
	 */
	/* HSI��ͭ���� */
	sil_orw((void*)RCC_CR, CR_HSI_ON);

    /* CFGR�Υꥻ�å� */
    sil_wrw_mem((void *)RCC_CFGR, 0x00000000);

	/* HSEON, CSSON, PLLON �Υ��ꥢ */
	sil_andw((void*)RCC_CR, 0xFEF6FFFF);

    /* PLLCFGR�Υꥻ�å� */
    sil_wrw_mem((void *)RCC_PLLCFGR, 0x00000000);

	/* HSEBYP �Υ��ꥢ */
	sil_andw((void*)RCC_CR, 0xFFFBFFFF);

	/* ����߶ػ� */
    sil_wrw_mem((void *)RCC_CIR, 0x00000000);

	/*
	 *  120Mhz������
	 */
	/* HSE��ͭ���� */
	sil_orw((void*)RCC_CR, CR_HSE_ON);

	/* HSEͭ���Ԥ� */
	while((sil_rew_mem((void*)RCC_CR) & CR_HSE_RDY) == 0);

	/* HCLK = SYSCLK, PCLK2 = HCLK, PCLK1 = HCLK/2  */
	sil_orw((void*)RCC_CFGR, (0x00 << 4) | (0x00 << 13) | (0x04 << 10));

	/* PLLCLK = (25MHz * (PLLN / PLLM)) / PLLP = (25MHz * (48 / 5)) / 2 = 120MHz, HSE as PLL clock */
    sil_wrw_mem((void *)(RCC_PLLCFGR), (CFGR_PLL_SRC | (0x00 << 16) | (48 << 6) | (5 << 0)));

	/* PLL��ͭ���� */
	sil_orw((void*)RCC_CR, CR_PLL_ON);

	/* PLLͭ���Ԥ� */
	while((sil_rew_mem((void*)RCC_CR) & CR_PLL_RDY) == 0);

	/* FLASH ROM��2wait������ */
	sil_andw((void*)FLASH_ACR, ~ACR_LATENCY_MASK);
	sil_orw((void*)FLASH_ACR, ACR_LATENCY_TWO);

	/* FLASH ROM�Υץ�ե��å��Хåե���D����å��塢I����å����ѡ��� */
	sil_andw((void*)FLASH_ACR, ~(ACR_DCEN | ACR_ICEN | ACR_PRFTEN));
	sil_orw((void*)FLASH_ACR, (ACR_DCRST | ACR_ICRST));
	/* FLASH ROM�Υץ�ե��å��Хåե���D����å��塢I����å����ͭ���� */
	sil_orw((void*)FLASH_ACR, (ACR_DCEN | ACR_ICEN | ACR_PRFTEN));

	/* PLL�򥷥��ƥ९��å������� */
	sil_andw((void*)RCC_CFGR, ~CFGR_SW_MASK);
	sil_orw((void*)RCC_CFGR, CFGR_SW_PLL);
  
	/* PLL�Υ����ƥ९��å������Ԥ� */
	while((sil_rew_mem((void*)RCC_CFGR) & CFGR_SWS_MASK) != (CFGR_SW_PLL << 2));

	/*
	 *  ���åװ�¸���ν����
	 */
	chip_initialize();

	/*
	 *  �ڥ�ե�����ͭ����
     *  USART6(RS232_1)
	 */
	sil_orw((void*)RCC_AHB1ENR, AHB1ENR_GPIOG_EN | AHB1ENR_GPIOC_EN);
	sil_orw((void*)RCC_APB2ENR, APB2ENR_USART6_EN);
#if (TNUM_PORT >= 2)
	/*
     *  USART3(RS232_1)
	 */
	sil_orw((void*)RCC_AHB1ENR, AHB1ENR_GPIOD_EN);
	sil_orw((void*)RCC_APB1ENR, APB1ENR_USART3_EN);
#endif
	/*
	 *  I/O�ݡ��Ȥν����
     *  Alternative Function
     *  MODE: mode, output speed
     *  CNF: pull-up/pull-down, output type
	 */
	/* USART6(RX) */
	set_cr_af(GPIOG_BASE, 9, 8);
	set_cr_mode(GPIOG_BASE, 9, MODE_AF);
	set_cr_otype(GPIOG_BASE, 9, OTYPE_PP);
	set_cr_ospeed(GPIOG_BASE, 9, OSPEED_50MHz);
	set_cr_pupd(GPIOG_BASE, 9, PUPD_UP);

	/* USART6(TX) */
	set_cr_af(GPIOC_BASE, 6, 8);
	set_cr_mode(GPIOC_BASE, 6, MODE_AF);
	set_cr_otype(GPIOC_BASE, 6, OTYPE_PP);
	set_cr_ospeed(GPIOC_BASE, 6, OSPEED_50MHz);
	set_cr_pupd(GPIOC_BASE, 6, PUPD_UP);

#if (TNUM_PORT >= 2)
	/* USART3(RX) */
	set_cr_af(GPIOD_BASE, 9, 7);
	set_cr_mode(GPIOD_BASE, 9, MODE_AF);
	set_cr_otype(GPIOD_BASE, 9, OTYPE_PP);
	set_cr_ospeed(GPIOD_BASE, 9, OSPEED_50MHz);
	set_cr_pupd(GPIOD_BASE, 9, PUPD_UP);

	/* USART3(TX) */
	set_cr_af(GPIOD_BASE, 8, 7);
	set_cr_mode(GPIOD_BASE, 8, MODE_AF);
	set_cr_otype(GPIOD_BASE, 8, OTYPE_PP);
	set_cr_ospeed(GPIOD_BASE, 8, OSPEED_50MHz);
	set_cr_pupd(GPIOD_BASE, 8, PUPD_UP);
#endif

    /*
     *  MPU�ν����
     */
    target_mpu_initialize();

	/*
	 *  �Хʡ������ѤΥ��ꥢ������
	 */
	usart_init(SIO_PORTID);
}

/*
 * �������åȰ�¸������λ����
 */
void
target_exit(void)
{
	/* ���åװ�¸���ν�λ���� */
	chip_exit();
	while(1);
}

 /*
 * �����ƥ�������٥���ϤΤ����ʸ������
 */
void
target_fput_log(char c)
{
	if (c == '\n') {
		sio_pol_snd_chr('\r', SIO_PORTID);
	}
	sio_pol_snd_chr(c, SIO_PORTID);
}

