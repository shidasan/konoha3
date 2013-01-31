/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 * 
 *  Copyright (C) 2012 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 */

/*
 * ターゲット依存モジュール（STM32P207用）
 */
#include "kernel_impl.h"
#include <sil.h>
#include "stm32p207.h"
#include "usart.h"
#include "task.h"
#include "memory.h"

/*
 * ターゲット依存部　初期化処理
 */
void
target_initialize(void)
{
	/*
	 *  プロセッサクロック(RCC)の初期化
	 */
	/* HSIの有効化 */
	sil_orw((void*)RCC_CR, CR_HSI_ON);

    /* CFGRのリセット */
    sil_wrw_mem((void *)RCC_CFGR, 0x00000000);

	/* HSEON, CSSON, PLLON のクリア */
	sil_andw((void*)RCC_CR, 0xFEF6FFFF);

    /* PLLCFGRのリセット */
    sil_wrw_mem((void *)RCC_PLLCFGR, 0x00000000);

	/* HSEBYP のクリア */
	sil_andw((void*)RCC_CR, 0xFFFBFFFF);

	/* 割込み禁止 */
    sil_wrw_mem((void *)RCC_CIR, 0x00000000);

	/*
	 *  120Mhzに設定
	 */
	/* HSEの有効化 */
	sil_orw((void*)RCC_CR, CR_HSE_ON);

	/* HSE有効待ち */
	while((sil_rew_mem((void*)RCC_CR) & CR_HSE_RDY) == 0);

	/* HCLK = SYSCLK, PCLK2 = HCLK, PCLK1 = HCLK/2  */
	sil_orw((void*)RCC_CFGR, (0x00 << 4) | (0x00 << 13) | (0x04 << 10));

	/* PLLCLK = (25MHz * (PLLN / PLLM)) / PLLP = (25MHz * (48 / 5)) / 2 = 120MHz, HSE as PLL clock */
    sil_wrw_mem((void *)(RCC_PLLCFGR), (CFGR_PLL_SRC | (0x00 << 16) | (48 << 6) | (5 << 0)));

	/* PLLの有効化 */
	sil_orw((void*)RCC_CR, CR_PLL_ON);

	/* PLL有効待ち */
	while((sil_rew_mem((void*)RCC_CR) & CR_PLL_RDY) == 0);

	/* FLASH ROMを2waitに設定 */
	sil_andw((void*)FLASH_ACR, ~ACR_LATENCY_MASK);
	sil_orw((void*)FLASH_ACR, ACR_LATENCY_TWO);

	/* FLASH ROMのプリフェッチバッファ、Dキャッシュ、Iキャッシュをパージ */
	sil_andw((void*)FLASH_ACR, ~(ACR_DCEN | ACR_ICEN | ACR_PRFTEN));
	sil_orw((void*)FLASH_ACR, (ACR_DCRST | ACR_ICRST));
	/* FLASH ROMのプリフェッチバッファ、Dキャッシュ、Iキャッシュを有効に */
	sil_orw((void*)FLASH_ACR, (ACR_DCEN | ACR_ICEN | ACR_PRFTEN));

	/* PLLをシステムクロックに選択 */
	sil_andw((void*)RCC_CFGR, ~CFGR_SW_MASK);
	sil_orw((void*)RCC_CFGR, CFGR_SW_PLL);
  
	/* PLLのシステムクロック選択待ち */
	while((sil_rew_mem((void*)RCC_CFGR) & CFGR_SWS_MASK) != (CFGR_SW_PLL << 2));

	/*
	 *  チップ依存部の初期化
	 */
	chip_initialize();

	/*
	 *  ペリフェラルの有効化
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
	 *  I/Oポートの初期化
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
     *  MPUの初期化
     */
    target_mpu_initialize();

	/*
	 *  バナー出力用のシリアル初期化
	 */
	usart_init(SIO_PORTID);
}

/*
 * ターゲット依存部　終了処理
 */
void
target_exit(void)
{
	/* チップ依存部の終了処理 */
	chip_exit();
	while(1);
}

 /*
 * システムログの低レベル出力のための文字出力
 */
void
target_fput_log(char c)
{
	if (c == '\n') {
		sio_pol_snd_chr('\r', SIO_PORTID);
	}
	sio_pol_snd_chr(c, SIO_PORTID);
}

