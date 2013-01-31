/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 *	
 *	Copyright (C) 2012 by Embedded and Real-Time Systems Laboratory
 *				Graduate School of Information Science, Nagoya Univ., JAPAN
 *	
 *	上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *	ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *	変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *	(1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *		権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *		スコード中に含まれていること．
 *	(2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *		用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *		者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *		の無保証規定を掲載すること．
 *	(3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *		用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *		と．
 *	  (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *		  作権表示，この利用条件および下記の無保証規定を掲載すること．
 *	  (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *		  報告すること．
 *	(4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *		害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *		また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *		由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *		免責すること．
 *	
 *	本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *	よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *	に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *	アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *	の責任を負わない．
 *	
 */

/*
 *	MPUドライバ
 */

#include "kernel_impl.h"
#include "task.h"
#include "memory.h"
#include <sil.h>
#include "kernel_cfg.h"
#include "target_mpu.h"

void
target_mpu_initialize(void)
{
    char *shared_mem_base;
    char *shared_mem_attr;

    sil_wrw_mem((void *)(MPU_REGNO), (uint32_t)(0));
    /*
     *  領域0: 共有リード領域
     */
    shared_mem_base = shared_meminib_table[0];
    shared_mem_attr = shared_meminib_table[1];
    sil_wrw_mem((void *)(MPU_REGBASE), (uint32_t)shared_mem_base);
    sil_wrw_mem((void *)(MPU_REGATR),  (uint32_t)shared_mem_attr);

    /*
     *  領域1: 共有リードライト領域
     */
    shared_mem_base = shared_meminib_table[2];
    shared_mem_attr = shared_meminib_table[3];
    sil_wrw_mem((void *)(MPU_REGBASE), (uint32_t)shared_mem_base);
    sil_wrw_mem((void *)(MPU_REGATR),  (uint32_t)shared_mem_attr);

    /*
     *  領域2: 共有リード専有ライト領域全体
     */
    shared_mem_base = shared_meminib_table[4];
    shared_mem_attr = shared_meminib_table[5];
    sil_wrw_mem((void *)(MPU_REGBASE), (uint32_t)shared_mem_base);
    sil_wrw_mem((void *)(MPU_REGATR),  (uint32_t)shared_mem_attr);

    /*
     *  MPU有効
     *  特権モードではデフォルトのメモリマップ
     *  ハンドラ内ではMPU無効
     */
    sil_wrw_mem((void *)(MPU_CR), (uint32_t)(MPU_CR_PRIVDEFENA | MPU_CR_ENABLE));
}

void
target_mpu_exc_handler(void *p_excinf)
{
    syslog(LOG_EMERG, "MPU EXCEPTION OCCURED!!");
    while(1);
}

// タスク例外実行開始時スタック不正ハンドラ
void
target_emulate_texrtn_handler(void *p_excinf)
{
    syslog(LOG_EMERG, "User stack is no space at prepare texrtn.");
    while(1);
}

// タスク例外リターン時スタック不正ハンドラ
void
target_emulate_ret_tex_handler(void *p_excinf)
{
    syslog(LOG_EMERG, "User stack is no space at return texrtn.");
    while(1);
}

