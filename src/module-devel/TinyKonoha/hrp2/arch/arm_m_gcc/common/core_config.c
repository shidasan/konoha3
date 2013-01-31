/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 * 
 *  Copyright (C) 2008-2012 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: core_config.c 2193 2011-07-25 04:34:11Z ertl-honda $
 */

/*
 *		コア依存モジュール（ARM-M用）
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"

/*
 *  CPUロックフラグ実現のための変数
 */
volatile bool_t		lock_flag;		/* CPUロックフラグの値を保持する変数 */
volatile uint32_t	saved_iipm;		/* 割込み優先度マスクを保存する変数 */

/*
 *  ベクタテーブル(kernel_cfg.c)
 */
extern const FP vector_table[];

/*
 *  システム例外・割込みの（例外番号 4〜15）
 *  割込み優先度設定レジスタへのアクセスのための配列
 */
static const unsigned int nvic_sys_pri_reg[] = {
	0,
	NVIC_SYS_PRI1,
	NVIC_SYS_PRI2,
	NVIC_SYS_PRI3
};

/*
 *  例外と割込みの割込み優先度をセット
 *
 *  excnoはARM-Mで定められている Exception Number を指定．
 */
void
set_exc_int_priority(uint32_t excno, uint32_t iipm){
	uint32_t tmp, reg;

	/*
	 *  割込み優先度設定レジスタの決定
	 */
	if ((EXCNO_MPU <= excno) && (excno <= IRQNO_SYSTICK)) {
		/*
		 * Exception Number 4(Memory Management)から
		 * Exception Number 15(SysTick)までの割込み優先度はシステム優先度
		 * レジスタにより設定．
		 */
		reg = nvic_sys_pri_reg[excno >> 2];
	}
	else if ((TMIN_INTNO < excno) && (excno <= TMAX_INTNO)){
		/*
		 * IRQ割込みなら
		 */
		reg = NVIC_PRI0 + (((excno - (TMIN_INTNO + 1)) >> 2) * 4);
	}
	else {
		return ;
	}
	
	tmp = sil_rew_mem((void *)reg);
	tmp &= ~(0xFF << (8 * (excno & 0x03)));
	tmp |= iipm << (8 * (excno & 0x03));
	sil_wrw_mem((void *)reg, tmp);
}

/*
 *  例外の許可
 *
 *  Memory Management, Bus Fault, Usage Fault は禁止・許可が可能
 */
void
enable_exc(EXCNO excno)
{
	uint32_t tmp;

	switch (excno) {
	  case EXCNO_MPU:
		tmp = sil_rew_mem((void *)NVIC_SYS_HND_CTRL);
		tmp |= NVIC_SYS_HND_CTRL_MEM;
		sil_wrw_mem((void *)NVIC_SYS_HND_CTRL, tmp);
		break;
	  case EXCNO_BUS:
		tmp = sil_rew_mem((void *)NVIC_SYS_HND_CTRL);
		tmp |= NVIC_SYS_HND_CTRL_BUS;
		sil_wrw_mem((void *)NVIC_SYS_HND_CTRL, tmp);
		break;
	  case EXCNO_USAGE:
		tmp = sil_rew_mem((void *)NVIC_SYS_HND_CTRL);
		tmp |= NVIC_SYS_HND_CTRL_USAGE;
		sil_wrw_mem((void *)NVIC_SYS_HND_CTRL, tmp);
		break;
	}
}

/*
 *  例外の禁止
 */
void
disable_exc(EXCNO excno)
{
	uint32_t tmp;

	switch (excno) {
	  case EXCNO_MPU:
		tmp = sil_rew_mem((void *)NVIC_SYS_HND_CTRL);
		tmp &= ~NVIC_SYS_HND_CTRL_MEM;
		sil_wrw_mem((void *)NVIC_SYS_HND_CTRL, tmp);
		break;
	  case EXCNO_BUS:
		tmp = sil_rew_mem((void *)NVIC_SYS_HND_CTRL);
		tmp &= ~NVIC_SYS_HND_CTRL_BUS;
		sil_wrw_mem((void *)NVIC_SYS_HND_CTRL, tmp);
		break;
	  case EXCNO_USAGE:
		tmp = sil_rew_mem((void *)NVIC_SYS_HND_CTRL);
		tmp &= ~NVIC_SYS_HND_CTRL_USAGE;
		sil_wrw_mem((void *)NVIC_SYS_HND_CTRL, tmp);
		break;
	}
}


/*
 *  コア依存の初期化
 */
void
core_initialize(void)
{
	/*
	 *  CPUロックフラグ実現のための変数の初期化
	 */
	lock_flag = true;
	saved_iipm = IIPM_ENAALL;

	/*
	 *  ベクタテーブルを設定
	 */
	sil_wrw_mem((void*)NVIC_VECTTBL, (uint32_t)vector_table);

	/*
	 *  各例外の優先度を設定
	 *  CPUロック状態でも発生するように，BASEPRIレジスタでマスクでき
	 *  ない'0'とする．
	 */
	set_exc_int_priority(EXCNO_HARD, 0);
	set_exc_int_priority(EXCNO_MPU, 0);
	set_exc_int_priority(EXCNO_BUS, 0);
	set_exc_int_priority(EXCNO_USAGE, 0);
	set_exc_int_priority(EXCNO_SVCALL, 0);
	set_exc_int_priority(EXCNO_DEBUG, 0);
	set_exc_int_priority(EXCNO_PENDSV, 0);

	/*
	 *  SVCハンドラを有効に
	 */
	x_enable_int(EXCNO_SVCALL);

    /*
     *  Configuration Control RegisterのSTKALIGNビットを0にする
     *  スタックは8byteアラインでなく、4byteアライン
     */
    sil_andw((void *)CCR_BASE, ~CCR_STKALIGN);
}

/*
 *  コア依存の終了処理
 */
void
core_terminate(void)
{
	extern void    software_term_hook(void);
	void (*volatile fp)(void) = software_term_hook;

	/*
	 *  software_term_hookへのポインタを，一旦volatile指定のあるfpに代
	 *  入してから使うのは，0との比較が最適化で削除されないようにするた
	 *  めである．
	 */
	if (fp != 0) {
		(*fp)();
	}
}

/*
 *  割込み要求ライン属性の設定
 */
void
x_config_int(INTNO intno, ATR intatr, PRI intpri)
{
	assert(VALID_INTNO_CFGINT(intno));
	assert(TMIN_INTPRI <= intpri && intpri <= TMAX_INTPRI);

	/* 
	 *  一旦割込みを禁止する
	 */    
	(void)x_disable_int(intno);

	/*
	 *  割込み優先度をセット
	 */
	set_exc_int_priority(intno, INT_IPM(intpri));

	/*
	 *  割込み要求マスク解除(必要な場合)
	 */
	if ((intatr & TA_ENAINT) != 0U) {
		(void) x_enable_int(intno);
	}    
}


#ifndef OMIT_DEFAULT_EXC_HANDLER
/*
 *  Trapa以外の例外で登録されていない例外が発生すると呼び出される
 */
void
default_exc_handler(void *p_excinf)
{
	uint32_t basepri = *(((uint32_t*)p_excinf) + P_EXCINF_OFFSET_BASEPRI);
	uint32_t pc      = *(((uint32_t*)p_excinf) + P_EXCINF_OFFSET_PC);
	uint32_t xpsr    = *(((uint32_t*)p_excinf) + P_EXCINF_OFFSET_XPSR);
	uint32_t excno   = get_ipsr() & IPSR_ISR_NUMBER;

	syslog(LOG_EMERG, "\nUnregistered Exception occurs.");
	syslog(LOG_EMERG, "Excno = %08x PC = %08x XPSR = %08x basepri = %08X, p_excinf = %08X",
		   excno, pc, xpsr, basepri, p_excinf);

	target_exit();
}
#endif /* OMIT_DEFAULT_EXC_HANDLER */

#ifndef OMIT_DEFAULT_INT_HANDLER
/*
 *  未登録の割込みが発生した場合に呼び出される
 */
void
default_int_handler(void *p_excinf)
{
	uint32_t basepri = *(((uint32_t*)p_excinf) + P_EXCINF_OFFSET_BASEPRI);
	uint32_t pc      = *(((uint32_t*)p_excinf) + P_EXCINF_OFFSET_PC);
	uint32_t xpsr    = *(((uint32_t*)p_excinf) + P_EXCINF_OFFSET_XPSR);
	uint32_t excno   = get_ipsr() & IPSR_ISR_NUMBER;

	syslog(LOG_EMERG, "\nUnregistered Interrupt occurs.");
	syslog(LOG_EMERG, "Excno = %08x PC = %08x XPSR = %08x basepri = %08X, p_excinf = %08X",
		   excno, pc, xpsr, basepri, p_excinf);

	target_exit();
}
#endif /* OMIT_DEFAULT_INT_HANDLER */

/*
 *  メモリ領域がユーザスタック領域に含まれているかのチェック
 *
 *  先頭番地がbaseでサイズがsizeのメモリ領域が，p_tcbで指定されるタスク
 *  のユーザスタック領域に含まれている場合にtrue，そうでない場合に
 *  falseを返す．
 *
 *  メモリ領域の先頭番地からユーザスタックの底までの長さが
 *  メモリ領域のサイズよりも大きく，かつ，
 *  ユーザスタックのサイズよりも小さければ，メモリ領域は，
 *  ユーザスタックの範囲内である．
 *
 */
bool_t
within_ustack(const void *base, SIZE size, TCB *p_tcb)
{
    SIZE stk_bottom = (SIZE)(p_tcb->p_tinib->tskinictxb.stk_bottom);
    SIZE len = stk_bottom - (SIZE)base;

    return ((SIZE)base < stk_bottom
            && len >= size
            && len <= (SIZE)(p_tcb->p_tinib->tskinictxb.stksz));
}

/*
 *  ユーザタスクのタスク例外処理呼び出し時に使用するスタックサイズが足りないか？
 */
bool_t
i_check_tex_runtsk()
{
    SIZE ustk_top = (SIZE)(p_runtsk->tskctxb.usp);

    if(!PROBE_STACK((void *)(ustk_top - USRTEX_STKSZ), 
                USRTEX_STKSZ)){
        return (true);
    }

    return (false);
}  

