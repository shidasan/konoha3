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
 *  タイマドライバ（STM32P207用）
 */

#ifndef TOPPERS_TARGET_TIMER_H
#define TOPPERS_TARGET_TIMER_H

#include "stm32p207.h"

/*
 *  タイマ値の内部表現とミリ秒単位との変換
 */
#define TIMER_CLOCK		(SYS_CLOCK / 1000)

/*
 *  タイマ割込みハンドラ登録のための定数
 */
#define INTPRI_TIMER    (-6)          /* 割込み優先度 */
#define INTATR_TIMER    0U            /* 割込み属性 */

/*
 *  プロセッサ依存部で定義する
 */
#include "arm_m_gcc/common/core_timer.h"

#ifdef TOPPERS_TARGET_SUPPORT_OVRHDR
/*
 *  TIM2を使用する
 */

/*
 *	タイマ割込みハンドラ登録のための定数
 */
#define INHNO_OVRTIMER 	(16 + 28)   /* 割込みハンドラ番号 */
#define INTNO_OVRTIMER 	(16 + 28)   /* 割込み番号 */
#define INTPRI_OVRTIMER	(-7)		  /* 割込み優先度 */
#define INTATR_OVRTIMER	0U			  /* 割込み属性 */

#endif /* TOPPERS_TARGET_SUPPORT_OVRHDR */

#ifndef TOPPERS_MACRO_ONLY
#ifdef TOPPERS_TARGET_SUPPORT_OVRHDR
/*
 *  タイマ値の内部表現とマイクロ秒単位との変換
 */
#define OVRTIMER_CLOCK_UNIT 1
/*
 *  設定できる最大のタイマ周期（単位は内部表現）
 */
#define MAX_OVRTIMER_CLOCK    ((CLOCK) 0xffffffffU)
/*
 *	タイマ値の内部表現とマイクロ秒単位との変換
 *	1μsecあたりのクロックカウント数
 */
#define OVRTIMER_CLOCK(usec) ((usec) * OVRTIMER_CLOCK_UNIT)
#define OVRTIMER_USEC(clock) ((clock) / OVRTIMER_CLOCK_UNIT)

#define OVRTIMER_BASE   TIM2_BASE

/*
 *  レジスタの定義
 */
#define TIMX_CR1(x)     (x + 0x00)
#define TIMX_DIER(x)    (x + 0x0c)
#define TIMX_SR(x)      (x + 0x10)
#define TIMX_EGR(x)     (x + 0x14)
#define TIMX_CNT(x)     (x + 0x24)
#define TIMX_PSC(x)     (x + 0x28)

#define CR1_CEN         (1 << 0)
#define CR1_OPM         (1 << 3)
#define CR1_DIR         (1 << 4)

#define EGR_UG          (1 << 0)

#define SR_UIF          (1 << 0)

#define DIER_UIE        (1 << 0)

/*
 *	オーバランタイマの初期化処理
 *
 *	タイマを初期化する．
 */
extern void target_ovrtimer_initialize(intptr_t exinf);

/*
 *	オーバランタイマの終了処理
 *
 *	タイマの動作を終了する．
 */
extern void target_ovrtimer_terminate(intptr_t exinf);

/*
 *	オーバランタイマの起動処理
 *
 *	タイマを起動する．
 */
extern void target_ovrtimer_start(OVRTIM ovrtim);

/*
 *	オーバランタイマの停止処理
 *
 *	タイマの動作を停止させる．
 */
extern OVRTIM target_ovrtimer_stop(void);

/*
 *	オーバランタイマの現在値の読出し
 */
extern OVRTIM target_ovrtimer_get_current(void);

/*
 *	オーバランタイマ割込みハンドラ
 */
extern void target_ovrtimer_handler(void);

/*
 *  オーバランハンドラ起動ルーチン
 */
extern void	call_ovrhdr(void);

#endif /* TOPPERS_TARGET_SUPPORT_OVRHDR */
#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_TARGET_TIMER_H */
