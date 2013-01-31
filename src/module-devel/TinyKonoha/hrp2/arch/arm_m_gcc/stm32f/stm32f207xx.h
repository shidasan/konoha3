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
#ifndef TOPPERS_ST32F207XX_H
#define TOPPERS_ST32F207XX_H

/*
 *  割込み番号の最大値
 */
#define TMAX_INTNO   (16 + 80)

/*
 *  割込み優先度のビット幅
 */
#define TBITW_IPRI     4

/*
 *  割込み優先度ビット幅中のサブ優先度のビット幅
 */
#define TBITW_SUBIPRI  0

#include <sil.h>

/*
 * ARM-M依存部のインクルード
 */
#include "arm_m_gcc/common/arm_m.h"

/*
 *  割込みベクタ番号定義
 *  16を足すのは，例外番号0からのオフセットとするため
 */
#define IRQ_VECTOR_USART1		(16 + 37)
#define IRQ_VECTOR_USART2		(16 + 38)
#define IRQ_VECTOR_USART3		(16 + 39)
#define IRQ_VECTOR_USART4		(16 + 52)
#define IRQ_VECTOR_USART5		(16 + 53)
#define IRQ_VECTOR_USART6		(16 + 71)

/*
 * ペリフェラルレジスタ定義
 */
#define PERIPH_REG_BASE			(0x40000000UL)
#define SRAM_BASE				(0x20000000UL)

#define APB1_PERIPH				(PERIPH_REG_BASE)
#define APB2_PERIPH				(PERIPH_REG_BASE + 0x10000)
#define AHB1_PERIPH				(PERIPH_REG_BASE + 0x20000)
#define AHB2_PERIPH				(PERIPH_REG_BASE + 0x10000000)
#define AHB3_PERIPH				(PERIPH_REG_BASE + 0x10000000)

/* BUS:APB1 */
#define TIM2_BASE				(APB1_PERIPH)
#define TIM3_BASE				(APB1_PERIPH + 0x400)
#define TIM4_BASE				(APB1_PERIPH + 0x800)
#define TIM5_BASE				(APB1_PERIPH + 0xc00)
#define TIM6_BASE				(APB1_PERIPH + 0x1000)
#define TIM7_BASE				(APB1_PERIPH + 0x1400)
#define TIM12_BASE				(APB1_PERIPH + 0x1800)
#define TIM13_BASE				(APB1_PERIPH + 0x1c00)
#define TIM14_BASE				(APB1_PERIPH + 0x2000)
#define RTC_BASE				(APB1_PERIPH + 0x2800)
#define WWDG_BASE				(APB1_PERIPH + 0x2C00)
#define IWDG_BASE				(APB1_PERIPH + 0x3000)
#define SPI2_BASE				(APB1_PERIPH + 0x3800)
#define SPI3_BASE				(APB1_PERIPH + 0x3c00)
#define USART2_BASE				(APB1_PERIPH + 0x4400)
#define USART3_BASE				(APB1_PERIPH + 0x4800)
#define USART4_BASE				(APB1_PERIPH + 0x4c00)
#define USART5_BASE				(APB1_PERIPH + 0x5000)
#define I2C1_BASE				(APB1_PERIPH + 0x5400)
#define I2C2_BASE				(APB1_PERIPH + 0x5800)
#define I2C3_BASE				(APB1_PERIPH + 0x5c00)
#define CAN1_BASE				(APB1_PERIPH + 0x6400)
#define CAN2_BASE				(APB1_PERIPH + 0x6800)
#define PWR_BASE				(APB1_PERIPH + 0x7000)
#define DAC_BASE				(APB1_PERIPH + 0x7400)

/* BUS:APB2 */
#define TIM1_BASE				(APB2_PERIPH)
#define TIM8_BASE				(APB2_PERIPH + 0x400)
#define USART1_BASE				(APB2_PERIPH + 0x1000)
#define USART6_BASE				(APB2_PERIPH + 0x1400)
#define ADC_BASE				(APB2_PERIPH + 0x2000)
#define SDIO_BASE				(APB2_PERIPH + 0x2c00)
#define SPI1_BASE				(APB2_PERIPH + 0x3000)
#define SYSCFG_BASE				(APB2_PERIPH + 0x3800)
#define EXTI_BASE				(APB2_PERIPH + 0x3c00)
#define TIM9_BASE				(APB2_PERIPH + 0x4000)
#define TIM10_BASE				(APB2_PERIPH + 0x4400)
#define TIM11_BASE				(APB2_PERIPH + 0x4800)

/* BUS:AHB1 */
#define GPIOA_BASE				(AHB1_PERIPH)
#define GPIOB_BASE				(AHB1_PERIPH + 0x400)
#define GPIOC_BASE				(AHB1_PERIPH + 0x800)
#define GPIOD_BASE				(AHB1_PERIPH + 0xc00)
#define GPIOE_BASE				(AHB1_PERIPH + 0x1000)
#define GPIOF_BASE				(AHB1_PERIPH + 0x1400)
#define GPIOG_BASE				(AHB1_PERIPH + 0x1800)
#define GPIOH_BASE				(AHB1_PERIPH + 0x1c00)
#define GPIOI_BASE				(AHB1_PERIPH + 0x2000)
#define CRC_BASE				(AHB1_PERIPH + 0x3000)
#define RCC_BASE				(AHB1_PERIPH + 0x3800)
#define FLASH_BASE				(AHB1_PERIPH + 0x3c00)
#define BKPSRAM_BASE			(AHB1_PERIPH + 0x4000)
#define DMA1_BASE				(AHB1_PERIPH + 0x6000)
#define DMA2_BASE				(AHB1_PERIPH + 0x6400)
#define ETHERNET_BASE			(AHB1_PERIPH + 0x8000)
#define USB_OTG_HS_BASE			(AHB1_PERIPH + 0x20000)

/* BUS:AHB2 */
#define USB_OTG_FS_BASE			(AHB2_PERIPH)
#define DCMI_BASE	    		(AHB2_PERIPH + 0x50000)
#define CRYP_BASE	    		(AHB2_PERIPH + 0x60000)
#define HASH_BASE	    		(AHB2_PERIPH + 0x60400)
#define RNG_BASE	    		(AHB2_PERIPH + 0x60800)

/* BUS:AHB3 */
#define FSMC_BASE   			(AHB3_PERIPH)

/* System Control space */
#define SCS_BASE				(0xE000E000)
#define SYSTM_BASE				(SCS_BASE + 0x0010)
#define NVIC_BASE				(SCS_BASE + 0x0100)
#define SYSCB_BASE				(SCS_BASE + 0x0D00)

/* RCC */
#define RCC_CR					(RCC_BASE)
#define RCC_PLLCFGR				(RCC_BASE + 0x04)
#define RCC_CFGR				(RCC_BASE + 0x08)
#define RCC_CIR					(RCC_BASE + 0x0c)
#define RCC_AHB1RSTR			(RCC_BASE + 0x10)
#define RCC_AHB2RSTR			(RCC_BASE + 0x14)
#define RCC_AHB3RSTR			(RCC_BASE + 0x18)
#define RCC_APB1RSTR			(RCC_BASE + 0x20)
#define RCC_APB2RSTR			(RCC_BASE + 0x24)
#define RCC_AHB1ENR				(RCC_BASE + 0x30)
#define RCC_AHB2ENR				(RCC_BASE + 0x34)
#define RCC_AHB3ENR				(RCC_BASE + 0x38)
#define RCC_APB1ENR				(RCC_BASE + 0x40)
#define RCC_APB2ENR				(RCC_BASE + 0x44)
#define RCC_AHB1LPENR			(RCC_BASE + 0x50)
#define RCC_AHB2LPENR			(RCC_BASE + 0x54)
#define RCC_AHB3LPENR			(RCC_BASE + 0x58)
#define RCC_APB1LPENR			(RCC_BASE + 0x60)
#define RCC_APB2LPENR			(RCC_BASE + 0x64)
#define RCC_BDCR				(RCC_BASE + 0x70)
#define RCC_CSR					(RCC_BASE + 0x74)
#define RCC_SSCGR				(RCC_BASE + 0x80)
#define RCC_PLLI2SCFGR			(RCC_BASE + 0x84)

/* FLASH */
#define FLASH_ACR               (FLASH_BASE)

/* NVIC */
#define NVIC_ENAVLE_REG(ch)		(NVIC_BASE + ((ch) >> 5))
#define NVIC_DISABLE_REG(ch)	(NVIC_BASE + 0x80 + ((ch) >> 5))
#define NVIC_SET_PEND_REG(ch)	(NVIC_BASE + 0x100 + ((ch) >> 5))
#define NVIC_CLEAR_PEND_REG(ch)	(NVIC_BASE + 0x180 + ((ch) >> 5))
#define NVIC_ACTIVE_REG(ch)		(NVIC_BASE + 0x200 + ((ch) >> 5))
#define NVIC_PRIO_REG(ch)		(NVIC_BASE + 0x300 + ((ch) >> 2))

/* GPIOx */
#define GPIO_MODER(x)			(x)
#define GPIO_OTYPER(x)			((x) + 0x04)
#define GPIO_OSPEED(x)			((x) + 0x08)
#define GPIO_PUPDR(x)			((x) + 0x0C)
#define GPIO_IDR(x) 			((x) + 0x10)
#define GPIO_ODR(x)				((x) + 0x14)
#define GPIO_BSRR(x)			((x) + 0x18)
#define GPIO_LCKR(x)			((x) + 0x1c)
#define GPIO_AFRL(x)			((x) + 0x20)
#define GPIO_AFRH(x)			((x) + 0x24)

/* RCCレジスタ定義 */
#define CR_PLL_RDY				(0x02000000)
#define CR_PLL_ON				(0x01000000)
#define CR_HSE_RDY				(0x00020000)
#define CR_HSE_ON				(0x00010000)
#define CR_HSI_RDY				(0x00000002)
#define CR_HSI_ON				(0x00000001)
#define CFGR_PLL_SRC			(0x00400000)
#define CFGR_HPRE_MASK			(0x000000F0)
#define CFGR_PPRE2_MASK			(0x0000e000)
#define CFGR_PPRE1_MASK			(0x00001c00)
#define CFGR_SWS_MASK			(0x0000000C)
#define CFGR_SW_MASK			(0x00000003)
#define CFGR_SW_PLL				(0x02)

#define AHB1ENR_GPIOA_EN        (0x01)
#define AHB1ENR_GPIOB_EN        (0x02)
#define AHB1ENR_GPIOC_EN        (0x04)
#define AHB1ENR_GPIOD_EN        (0x08)
#define AHB1ENR_GPIOE_EN        (0x010)
#define AHB1ENR_GPIOF_EN        (0x020)
#define AHB1ENR_GPIOG_EN        (0x040)
#define AHB1ENR_GPIOH_EN        (0x080)
#define AHB1ENR_GPIOI_EN        (0x0100)
#define AHB1ENR_CRC_EN          (0x1000)
#define AHB1ENR_BKPSRAM_EN      (0x40000)
#define AHB1ENR_DMA1_EN         (0x200000)
#define AHB1ENR_DMA2_EN         (0x400000)
#define AHB1ENR_ETHMAC_EN       (0x2000000)
#define AHB1ENR_ETHMACTX_EN     (0x4000000)
#define AHB1ENR_ETHMACRX_EN     (0x8000000)
#define AHB1ENR_ETHMACPTP_EN    (0x10000000)
#define AHB1ENR_OTGHS_EN        (0x20000000)
#define AHB1ENR_OTGHSULPI_EN    (0x40000000)

#define AHB2ENR_DCMI_EN         (0x01)
#define AHB2ENR_CRYP_EN         (0x010)
#define AHB2ENR_HASH_EN         (0x020)
#define AHB2ENR_RNG_EN          (0x040)
#define AHB2ENR_OTGFS_EN        (0x080)

#define AHB3ENR_FSMC_EN         (0x01)

#define APB1ENR_TIM2_EN         (0x01)
#define APB1ENR_TIM3_EN         (0x02)
#define APB1ENR_TIM4_EN         (0x04)
#define APB1ENR_TIM5_EN         (0x08)
#define APB1ENR_TIM6_EN         (0x010)
#define APB1ENR_TIM7_EN         (0x020)
#define APB1ENR_TIM12_EN        (0x040)
#define APB1ENR_TIM13_EN        (0x080)
#define APB1ENR_TIM14_EN        (0x0100)
#define APB1ENR_WWDG_EN         (0x0800)
#define APB1ENR_SPI2_EN         (0x4000)
#define APB1ENR_SPI3_EN         (0x8000)
#define APB1ENR_USART2_EN       (0x20000)
#define APB1ENR_USART3_EN       (0x40000)
#define APB1ENR_USART4_EN       (0x80000)
#define APB1ENR_USART5_EN       (0x100000)
#define APB1ENR_I2C1_EN         (0x200000)
#define APB1ENR_I2C2_EN         (0x400000)
#define APB1ENR_I2C3_EN         (0x800000)
#define APB1ENR_CAN1_EN         (0x2000000)
#define APB1ENR_CAN2_EN         (0x4000000)
#define APB1ENR_PWR_EN          (0x10000000)
#define APB1ENR_DAC_EN          (0x20000000)

#define APB2ENR_TIM1_EN         (0x01)
#define APB2ENR_TIM8_EN         (0x02)
#define APB2ENR_USART1_EN       (0x010)
#define APB2ENR_USART6_EN       (0x020)
#define APB2ENR_ADC1_EN         (0x0100)
#define APB2ENR_ADC2_EN         (0x0200)
#define APB2ENR_ADC3_EN         (0x0400)
#define APB2ENR_SDIO_EN         (0x0800)
#define APB2ENR_SPI1_EN         (0x1000)
#define APB2ENR_SYSCFG_EN       (0x4000)
#define APB2ENR_TIM9_EN         (0x10000)
#define APB2ENR_TIM10_EN        (0x20000)
#define APB2ENR_TIM11_EN        (0x40000)

/* FLASHレジスタ定義 */
#define ACR_DCRST				(0x1000)
#define ACR_ICRST				(0x800)
#define ACR_DCEN				(0x400)
#define ACR_ICEN				(0x200)
#define ACR_PRFTEN				(0x100)
#define ACR_LATENCY_MASK		(0x07)
#define ACR_LATENCY_ZERO		(0x00)
#define ACR_LATENCY_ONE			(0x01)
#define ACR_LATENCY_TWO			(0x02)

/* GPIOxレジスタ定義 */
#define MODE_INPUT				(0x00)
#define MODE_OUTPUT             (0x01)
#define MODE_AF                 (0x02)
#define MODE_ANALOG             (0x03)
#define OTYPE_PP                (0x00)
#define OTYPE_OD                (0x01)
#define OSPEED_2MHz				(0x00)
#define OSPEED_25MHz			(0x01)
#define OSPEED_50MHz			(0x02)
#define OSPEED_100MHz			(0x03)
#define PUPD_NON				(0x00)
#define PUPD_UP 	    		(0x01)
#define PUPD_DOWN		    	(0x02)

#define CR_MODE_MASK(x)			(0x03 << ((x) << 1))
#define CR_OTYPE_MASK(x)	    (0x01 << (x))
#define CR_AF_MASK(x)			(0x0f << ((x & 0x07) << 2))
#define CR_MODE(x,v)			(((v) & 0x03) << ((x) << 1))
#define CR_OTYPE(x,v)			(((v) & 0x01) << (x))
#define CR_AF(x,v)			    ((v) << ((x & 0x07) << 2))

/* AFIOレジスタ定義 */
#define MAPR_USART2_REMAP		(0x0008)

#ifndef TOPPERS_MACRO_ONLY
/*
 * GPIOレジスタ操作関数
 */
Inline void
set_cr_af(uint32_t reg, uint_t p, uint8_t af)
{
    af &= 0x0f;
    if(p < 8){
		sil_andw((void*)GPIO_AFRL(reg), ~CR_AF_MASK(p));
		sil_orw((void*)GPIO_AFRL(reg), CR_AF(p, af));
    } else if(8 <= p && p < 16){
		sil_andw((void*)GPIO_AFRH(reg), ~CR_AF_MASK(p));
		sil_orw((void*)GPIO_AFRH(reg), CR_AF(p, af));
    }
}

Inline void
set_cr_mode(uint32_t reg, uint_t p, int_t v)
{
    sil_andw((void *)GPIO_MODER(reg), ~CR_MODE_MASK(p));
    sil_orw((void *)GPIO_MODER(reg), CR_MODE(p,v));
}

Inline void
set_cr_otype(uint32_t reg, uint_t p, int_t v)
{
    sil_andw((void *)GPIO_OTYPER(reg), ~CR_MODE_MASK(p));
    sil_orw((void *)GPIO_OTYPER(reg), CR_MODE(p,v));
}

Inline void
set_cr_ospeed(uint32_t reg, uint_t p, int_t v)
{
    sil_andw((void *)GPIO_OSPEED(reg), ~CR_MODE_MASK(p));
    sil_orw((void *)GPIO_OSPEED(reg), CR_MODE(p,v));
}

Inline void
set_cr_pupd(uint32_t reg, uint_t p, int_t v)
{
    sil_andw((void *)GPIO_PUPDR(reg), ~CR_MODE_MASK(p));
    sil_orw((void *)GPIO_PUPDR(reg), CR_MODE(p,v));
}

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_ST32F207XX_H */
