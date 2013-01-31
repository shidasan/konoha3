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
 *  @(#) $Id: core_support.S 2268 2011-11-22 16:22:45Z ertl-honda $
 */

/*
 *  プロセッサ依存モジュール アセンブリ言語部（ARM-M用）
 */

#define TOPPERS_MACRO_ONLY
#define UINT_C(val)		(val)		/* uint_t型の定数を作るマクロ */
#define ULONG_C(val)	(val)		/* ulong_t型の定数を作るマクロ */
#define CAST(type, val)	(val)		/* 型キャストを行うマクロ */

#include "kernel_impl.h"
#include "arm_m.h"
#include "offset.h"
#include "target_asm.inc"

/*
 *  タスクディスパッチャ
 */
	ATEXT
	AALIGN(2)
	ATHUMB(dispatch)
	AGLOBAL(dispatch)
ALABEL(dispatch)
#ifdef TOPPERS_SUPPORT_OVRHDR
    push    {lr}
    bl      ovrtimer_stop
    pop     {lr}
#endif /* TOPPERS_SUPPORT_OVRHDR */
	/*
	 *
	 *  このルーチンは，タスクコンテキスト・CPUロック状態・ディパッチ許可状態
	 *  ・（モデル上の）割込み優先度マスク全開状態で呼び出される．
	 */
	stmfd sp!,{r4-r11,lr}         /* レジスタの保存 */
	ldr   r0, =p_runtsk           /* p_runtskを読み込む */
	ldr   r1, [r0]
	str   sp, [r1,#TCB_ssp]        /* タスクのシステムスタックを保存 */
	ldr   lr, =dispatch_r         /* 実行再開番地を保存 */
	str   lr, [r1,#TCB_pc]        
	b     dispatcher

	ATHUMB(dispatch_r)
	AGLOBAL(dispatch_r)
ALABEL(dispatch_r)
	ldmfd sp!,{r4 - r11,lr}       /* レジスタの復帰 */
#ifdef TOPPERS_SUPPORT_OVRHDR
    push    {r1, lr}
    bl      ovrtimer_start
    pop     {r1, lr}
#endif /* TOPPERS_SUPPORT_OVRHDR */
	/*
	 * タスク例外処理ルーチンの起動
	 * dispatcherから呼び出されるため，TCBのアドレスはr1に入っている
	 */
	ldrb  r0,[r1,#TCB_enatex]
	tst   r0,#TCB_enatex_mask
	beq   dispatch_r_1            /* enatex が false ならリターン */
	ldr   r0,[r1,#TCB_texptn]     /* texptn が 0 ならリターン     */
	tst   r0,r0
	beq   dispatch_r_1            
	ldr   r2, =ipmflg             /* ipmflgが false ならリターン  */
	ldr   r0, [r2]
	tst   r0,r0
	beq   dispatch_r_1
    ldr     r2, =rundom
	ldr     r0, [r2]
	tst     r0, r0                /* rundom == 0(TACP_KERNEL) か？ */
	bne     dispatch_r_1
    ldrb    r0, [r1, #TCB_svclevel]  /* r0 = svclevel */
    tst     r0, r0              /* svclevel == 0 ? */
    bne     dispatch_r_1       /* 拡張サービスコール呼出し中ならばdispatch_r_1へ */
	ldr   r0, =call_texrtn_stask  /* タスク例外ルーチンの呼び出し */
	bx    r0
ALABEL(dispatch_r_1)              /* タスクへのcall_textnから戻る */
	bx    lr


/*
 *  CPU例外エントリ
 *
 *  割込みエントリと処理の内容は同等だが，ログの種類が異なるため，
 *  分けている．
 */
	AALIGN(2)
	ATEXT
	ATHUMB(core_exc_entry)
	AGLOBAL(core_exc_entry)
ALABEL(core_exc_entry)
	/*
	 *  例外/割込みが発生すると，発生時にアクティブなスタックにスクラ
	 *  ッチレジスタ等が保存される．
	 *  この内容に加えて，CPU例外ハンドラへの情報として，basepri の値と，
	 *  EXC_RETURNの情報を加えて保存する．basepriの値は，CPU例外からの
	 *  リターン時に割込み優先度マスクの値を元に戻すためにも用いられる．
	 *
	 *   -----------
	 *  | EXC_RETURN|  
	 *   -----------
	 *  |  basepri  |  
	 *   -----------
	 *  |    R0     |  
	 *   -----------
	 *  |    R1     |
	 *   -----------
	 *  |    R2     |
	 *   -----------
	 *  |    R3     |
	 *   -----------
	 *  |    R12    |
	 *   -----------
	 *  |    LR     |
	 *   -----------
	 *  |    PC     |
	 *   -----------
	 *  |   xPSR    |
	 *   -----------
	 *
	 */

	/*
	 *  カーネル管理外の例外かチェック
	 *  カーネル内のクリティカルセクションの実行中，全割込みロック状態，
	 *  CPUロック状態，カーネル管理外の割込みハンドラ実行中のいずれかで
	 *  発生したCPU例外を，カーネル管理外のCPU例外と呼ぶ
	 *  全割込みロック状態はFAULTMASKが'1'の場合
	 *  CPUロック状態はbasepriがIIPM_LOCKかで判断する．
	 */
	mrs   r2, FAULTMASK           /* 全割込みロック状態ならカーネル管理外例外処理へ */
	cbnz  r2, core_nonkernel_exc_entry

	mrs   r2, basepri             /* baepriの値を取得 */
	cmp   r2, #IIPM_LOCK          /* CPUロック状態ならカーネル管理外例外処理へ */
	beq   core_nonkernel_exc_entry


	/*
	 * スタックを変更する必要があるかチェック
	 * EXC_RETURN（割込み時にLRに設定される値）をチェックして，例外発生時に
	 * アクティブなスタックを特定することで多重割込みか判定する．
	 */
	tst   lr, #EXC_RETURN_PSP    /* 割込み元がMSPなら多重割込み */
	beq   core_exc_entry_1       /* 多重割込みならcore_exc_entry_1へ */
	mrs   r0, psp                /* 一段目の割込みの場合はPSP上に */
	stmfd r0!,{r2}               /* 割込み発生時の割込み優先度マスクを積む */
	stmfd r0!,{lr}               /* EXC_RETURN を積む             */
	msr   psp, r0                /* CPU例外ハンドラへの引数となる */
	push  {lr}                   /* MSP上にもEXC_RETURN を積む    */ 
#ifdef TOPPERS_SUPPORT_OVRHDR
    push    {r0}
    bl      ovrtimer_stop
    pop     {r0}
#endif /* TOPPERS_SUPPORT_OVRHDR */
	b     core_exc_entry_2
ALABEL(core_exc_entry_1)         /* 多重割込みの場合 */
	push  {r2}                   /* 割込み発生時の割込み優先度マスクを積む */
	push  {lr}                   /* EXC_RETURN を積む             */ 
	mov   r0, sp                 /* CPU例外ハンドラへの引数となる */

	/*
	 *  共通処理
	 */
ALABEL(core_exc_entry_2)
	mrs   r3, ipsr               /* ハンドラアドレスを取得 */
ALABEL(core_exc_entry_3)
	ldr   r1, =_kernel_exc_tbl
	ldr   r2, [r1, r3, lsl #2]

#ifdef LOG_EXC_ENTER
	push  {r0,r2,r3}
	mov   r0, r3                 /* 例外番号をパラメータに  */
	bl    log_exc_enter          /* log_exc_enterを呼び出す */
	pop   {r0,r2,r3}
	push  {r3}                   /* 例外番号をスタックへ    */
#endif /* LOG_EXC_ENTER */

	/*
	 *  CPU例外ハンドラの呼び出し
	 */
	blx   r2

#ifdef LOG_EXC_ENTER
	pop   {r0}                   /* 例外番号を引数に        */
	bl    log_exc_leave          /* log_exc_leaveを呼び出す */
#endif /* LOG_EXC_ENTER */

	b     ret_exc

/*
 *  カーネル管理外のCPU例外の出入口処理
 */
ALABEL(core_nonkernel_exc_entry)
	tst   lr, #EXC_RETURN_PSP    /* 割込み元がMSPなら多重割込み */
	beq   core_nonkernel_exc_entry_1  /* 多重割込みなら */
	mrs   r0, psp                /* 一段目の割込みの場合はPSP上に */
	stmfd r0!,{r2}               /* 割込み発生時の割込み優先度マスクを積む */
	stmfd r0!,{lr}               /* EXC_RETURN を積む             */
	msr   psp, r0                /* CPU例外ハンドラへの引数となる */
	push  {lr}                   /* MSP上にもEXC_RETURN を積む    */ 
	b     core_nonkernel_exc_entry_2
ALABEL(core_nonkernel_exc_entry_1) /* 多重割込みの場合 */
	push  {r2}                   /* 割込み発生時の割込み優先度マスクを積む */
	push  {lr}                   /* EXC_RETURN を積む             */ 
	mov   r0, sp                 /* CPU例外ハンドラへの引数となる */

ALABEL(core_nonkernel_exc_entry_2)
	mrs   r3, ipsr               /* CPU例外ハンドラのアドレスを取得 */
	ldr   r1, =_kernel_exc_tbl
	ldr   r2, [r1, r3, lsl #2]

	/*
	 *  CPU例外ハンドラの呼び出し
	 */
	blx   r2

	/*
	 *  割込みロック状態とする．
	 */
	cpsid f

	/*
	 *  戻り先のコンテキストの判定
	 * 
	 *  割込みハンドラ実行にLRにセットされるEXC_RETURNをチェックして，戻り
	 *  先でMSPが使われていれば，割込み先が非タスクコンテキストと判定する．
	 */
	pop   {r3}                     /* lrをスタックから取得         */
	tst   r3, #EXC_RETURN_PSP      /* 戻り先がPSPなら              */
	bne   core_nonkernel_ret_exc_1
	pop   {r1}                     /* 元の割込み優先度マスク(basepri) */
	b     core_nonkernel_ret_exc_2 /* の値をMSPから取得 */

ALABEL(core_nonkernel_ret_exc_1)
	/*
	 *  PSP上からEXC_RETURNを削除
	 */
	mrs   r2, psp
	add   r2, r2, #4
	/*
	 *  元の割込み優先度マスク(basepri)の値をPSPから取得
	 */
	ldmfd r2!, {r1} 
	msr   psp, r2

ALABEL(core_nonkernel_ret_exc_2)
	msr   basepri, r1             /* 割込み優先度マスクを割込み前に状態へ */
	bx    r3                      /* リターン */

/*
 *  割込みエントリ
 */
	ATHUMB(core_int_entry)
	AGLOBAL(core_int_entry)
ALABEL(core_int_entry)
	/*
	 *  割込み発生時の割込み優先度マスクをスタックに保存するため取得
	 */
	mrs   r2, basepri             /* baepriの値を取得 */

	/*
	 * 多重割込みかチェック
	 * EXC_RETURN（割込み時にLRに設定される値）をチェックして，例外発生時に
	 * アクティブなスタックを特定することで多重割込みか判定する．
	 */
	tst   lr, #EXC_RETURN_PSP    /* 割込み元がMSPなら多重割込み */
	beq   core_int_entry_1       /* 多重割込みならcore_int_entry_1へ */
	mrs   r0, psp                /* 一段目の割込みの場合はPSP上に */
	stmfd r0!,{r2}               /* 割込み発生時の割込み優先度マスクを積む */
	stmfd r0!,{lr}               /* EXC_RETURN を積む             */
	msr   psp, r0                /* CPU例外ハンドラへの引数となる */
	push  {lr}                   /* MSP上にもEXC_RETURN を積む    */ 
#ifdef TOPPERS_SUPPORT_OVRHDR
    push    {r0}
    bl      ovrtimer_stop
    pop     {r0}
#endif /* TOPPERS_SUPPORT_OVRHDR */
	b     core_int_entry_2
ALABEL(core_int_entry_1)         /* 多重割込みの場合 */
	push  {r2}                   /* 割込み発生時の割込み優先度マスクを積む */
	push  {lr}                   /* EXC_RETURN を積む             */ 
	mov   r0, sp                 /* 未定義の割込みが発生した場合の情報とする */

	/*
	 *  共通処理
	 */
ALABEL(core_int_entry_2)
	mrs   r3, ipsr               /* ハンドラアドレスを取得 */
	ldr   r1, =_kernel_exc_tbl
	ldr   r2, [r1, r3, lsl #2]

	/*
	 *  basepriの設定
	 *  NVIC優先度マスクが自動的に設定されるため優先度マスクの点では必要な
	 *  いが，x_get_ipm()がbasepriを参照するため，basepriも更新する．
	 */
	ldr   r1, =_kernel_int_iipm_tbl
	ldr   lr, [r1, r3, lsl #2]
	msr   basepri, lr

#ifdef LOG_INH_ENTER
	push  {r0,r2,r3}
	mov   r0, r3                 /* 例外番号をパラメータに  */
	bl    log_inh_enter          /* log_exc_enterを呼び出す */
	pop   {r0,r2,r3}
	push  {r3}                   /* 例外番号をスタックへ    */
#endif /* LOG_EXC_ENTER */

	/*
	 *  割込みハンドラの呼び出し
	 */
	blx   r2

#ifdef LOG_INH_LEAVE
	pop   {r0}                   /* 例外番号を引数に        */
	bl    log_exc_leave          /* log_exc_leaveを呼び出す */
#endif /* LOG_INH_LEAVE */



/*
 *  割込み/例外出口
 *
 *  ret_exc/ret_intは，CPU例外/割込みハンドラから戻った直後に実行する
 *  ルーチンである．
 */
ALABEL(ret_exc)
ALABEL(ret_int)
	/*
	 *  割込みロック状態とする．この時点では，CPUロック状態にはならない
	 * （basepriとlock_flagとsaved_iipmは更新しない）．
	 *
	 *  割込みロック状態とするのは，戻り先のコンテキストのチェックと，
	 *  戻り先が非タスクコンテキストであった場合のリターンをアトミック
	 *  に行うためである．bsepriをCPUロックの値にすることでもアトミッ
	 *  クなチェックと復帰は可能であるが，割込みからリターンしても，
	 *  basepri の設定内容は元に戻らないため，使用することができない． 
	 *  一方，FAULTMASKは，割込みからのリターン処理によって，'0'にクリ
	 *  アされる．
	 */
	cpsid f

	/*
	 *  戻り先のコンテキストの判定
	 * 
	 *  割込みハンドラ実行にLRにセットされるEXC_RETURNをチェックして，戻り
	 *  先でMSPが使われていれば，割込み先が非タスクコンテキストと判定する．
	 */
	pop   {r3}                     /* lrをスタックから取得         */
	tst   r3, #EXC_RETURN_PSP      /* 戻り先がPSPなら ret_int_1 へ */
	bne   ret_int_1
	pop   {r1}                     /* 元の割込み優先度マスク(basepri)をr1へ */
	b     ret_int_2                /* の値をMSPから取得 */

	/*
	 *  一段目の割込みの出口処理
	 */
ALABEL(ret_int_1)
	/*
	 *  PSP上から，EXC_RETURN(r0)と元の割込み優先度マスク(basepri)(r1)
	 *  を取得
	 */
	mrs   r2, psp
	ldmfd r2!, {r0,r1} 
	msr   psp, r2

	/*
	 *  reqflgをチェックする
	 * 
	 *  カーネル管理内の割込みは禁止した状態で実行する必要があるため，
	 *  FAULTMASKを'1'にした状態で実行する．
	 *  reqflgをチェックする前に割込みを禁止するのは，reqflgをチェック
	 *  した直後に割込みハンドラが起動され，その中でディスパッチが要求
	 *  された場合に，すぐにディスパッチされないという問題が生じるため
	 *  である．
	 */
	ldr   r0, =reqflg             /* reqflgがfalseならそのまま戻る */
	ldr   r2, [r0]
	cbnz  r2, ret_int_3           /* trueならret_int_3へ           */

#ifdef TOPPERS_SUPPORT_OVRHDR
    push    {r1,r3}
    bl      ovrtimer_start
    pop     {r1,r3}
#endif /* TOPPERS_SUPPORT_OVRHDR */
ALABEL(ret_int_2)
	/*
	 *  ここには割込みロック状態（FAULTMASKがセット）された状態で来る．
	 *  Threadモードからのリターンにより自動的に割込みロック解除状態になる．
	 *  割込み優先度マスクは割込み前に状態に戻す．
	 */ 
	msr   basepri, r1             /* 割込み優先度マスクを割込み前に状態へ */
	bx    r3                      /* リターン */

ALABEL(ret_int_3)
	/*
	 *  ここでは，戻り先がタスクであり，PSP上にスクラッチレジスタと割
	 *  込み優先度マスク(basepri)が保存された状態になっている．また，
	 *  プロセッサは，Handlerモード・割込みロック状態となっている．
	 *  また，r0には，reqflgのアドレス，r3には割込み受付時のlrの値が保
	 *  持されている．
	 */
	/*
	 *  タスク例外ハンドラやディスパッチをする際にThreadモードへ遷移する
	 *  ダミーのスタックフレームを作成して，bx命令でHandlerモードからリ
	 *  ターンする．また，遅延ディスパッチする場合も，再び割り込んだタス
	 *  クに戻る際には，svc命令で，svc_handlerを呼び出す．
	 *  スタックフレームは，Configureation and Control Register(CCR)の
	 *  STKALIGNが'1'の場合は，8byte境界にアラインされる．
	 *  参考 : DDI0403B_arm_architecture_v7m_reference_manual(P.220)
	 *  そのため，この時点のスタックは割込みや例外発生時に作成された
	 *  スタックフレームから，8byte境界のサイズにしておくと，svc_handler
	 *  等でスタックフレームのアライメントの有無の確認を省略できる．
	 *  ただし，システム起動後は，動的にCCRのSTKALIGNの設定を変更するのは
	 *  禁止とする．
	 *  この時点は標準のスタックフレームは，割込み・例外発生時と同等であ
	 *  るため，タスクスタック(PSP)は8byte境界になっている．
	 */
	mov   r1, #0                   /* reqflgをfalseに */
	str   r1, [r0]

	/*
	 *  CPUロック状態に移行する．
	 *
	 *  カーネルの管理内の割込みを禁止するようにbasepriを設定し，
	 *  lock_flag と saved_iipm を更新する．saved_iipmは，戻り先の割込み
	 *  優先度マスク（の内部表現）に設定する．
	 *  この時点でCPUロック状態とするのは，dispatcherへ分岐する時と，
	 *  call_texrtnを呼び出す時に，CPUロック状態になっている必要がある
	 *  ためである．
	 *  なお，この処理の後，Threadモードへの移行処理を行なうため，割込み
	 *  ロック状態(FAULTMASKを"1")は保持する．
	 */
	ldr   r1, =IIPM_LOCK          /* CPUロック状態 */ 
	msr   basepri, r1          
	mov   r1, #0x01               /* lock_flag を trueに */
	ldr   r0, =lock_flag          
	str   r1, [r0]

	/*
	 *  割込み優先度マスクを，全解除状態（TIPM_ENAALL）に設定する
	 *  すでにCPUロック状態なので，saved_iipmをIIPM_ENAALLとする．
	 */
	ldr   r1, =IIPM_ENAALL
	ldr   r0, =saved_iipm
	str   r1, [r0]

    /*
     *  戻り先の実行モードを保存するため，CONTROLをpspに退避
     */
    mrs     r0, control /* r0 = CONTROL */
    mrs     r2, psp
    stmfd   r2!, {r0}   /* CONTROLをpspに積む */
    mov     r0, #0x00   
    msr     control, r0 /* svc後に特権モードへ移行 */

	/*
	 *  Threadモードへ移行する．
	 *
	 *  dispatcherやcall_texrnを呼び出す場合は，Threadモードである必
	 *  要があるため，PSPスタック上にダミーの例外フレームを置いて，
	 *  擬似的に割込みハンドラからリターンする．
	 *  リターンと同時にFAULTMASKが自動的にクリアされ，カーネル管理外の
	 *  割込みが許可される．
	 */
	ldr   r0, =ret_int_4          /* PC   */
	ldr   r1, =EPSR_T             /* xPSR(Tビットが'1'である必要がある) */
	stmfd r2!, {r0-r1}            /* ダミーフレームをスタック上に積む   */
	sub   r2, #(EXC_FRAME_SIZE - (4*2)) /* r0-r3,r12,lrの内容は設定する必要がない */
	msr   psp,r2                  
	bx    r3                      /* Threadモード（特権）へ移行 */
    
ALABEL(ret_int_4)
	/*
	 *  上記の処理により，Threadモード（特権）で実行される．
	 *  dspflgがfalseである場合と，p_runtskとp_schedtskが同じ場合には，
	 *  ディスパッチを行わない．このチェックが必要なのは，タスク例外処
	 *  理ルーチンの呼出しが必要な場合に，ディスパッチが必要なくても，
	 *  reqflgをtrueにするためである．
	 */
	ldr   r0, =p_runtsk       /* ディスパッチを行わない場合でも，r1にp_runtsk の値(TCB) */
	ldr   r1, [r0]            /* が入っている必要があるので，先に読み込む */
    pop     {r0}              /* pspから戻り先のCONTROLを取得 */
    /*
     *  戻り先がユーザモードか？
     */
    mov     r2, #0x01           /* r2 = CONTROL_USER */
    tst     r0, r2              /* 戻り先が特権モードか？ */
    beq     ret_int_5           /* 戻り先が特権モードならばpspを切り替えない */
    nop
    /*
     *  pspをsspに切り替え
     *  ここでは，戻り先のタスクはタスク例外保留状態でないので，priv_modeは
     *  切り替えない
     */
	str     sp, [r1,#TCB_usp]   /* タスクのuspを保存 */
    ldr     sp, [r1,#TCB_ssp]   /* タスクのsspを復帰 */

ALABEL(ret_int_5)
    push    {r0}                /* pspに戻り先のcontrolを退避 */
	ldr   r0, =dspflg         
	ldr   r2, [r0]
	cbz   r2, ret_int_r_1     /* dspflgがfalseならret_int_r_1へ */
	ldr   r0, =p_schedtsk     
	ldr   r2, [r0]
	cmp   r1, r2              /* p_runtskとp_schedtskが同じなら */
	beq   ret_int_r_1         /*                  ret_int_r_1へ */

	stmfd sp!, {r4-r11}       /* 残りのレジスタを保存 */
	str   sp, [r1,#TCB_ssp]   /* タスクのシステムスタックを保存 */
	ldr   lr, =ret_int_r      /* 実行再開番地を保存   */
	str   lr, [r1,#TCB_pc]
	b     dispatcher          /* ディスパッチャへ */

/*
 * 割込みによりプリエンプトされたタスクへのリターン処理
 *
 * Threadモードで，ディスパッチャや割込みの出口処理から呼び出される．
 * 割込みによりプリエンプトされたタスクへリターンするには，いったん
 * Handlerモードに移行し，PCに0xfffffffdを代入してリターンする必要
 * がある．そのため，SVCにより，SVCハンドラを呼び出し，Handlerモー
 * ドへ移行する．
 */
	ATHUMB(ret_int_r)
	AGLOBAL(ret_int_r)
ALABEL(ret_int_r)
	pop {r4-r11}                  /* レジスタの復帰 */
    /*
     *  この時点では必ず，PSP = sspである．
     */
ALABEL(ret_int_r_1)
#ifdef TOPPERS_SUPPORT_OVRHDR
    push    {r1}
    bl      ovrtimer_start
    pop     {r1}
#endif /* TOPPERS_SUPPORT_OVRHDR */
    pop     {r3}                /* pspから戻り先のCONTROLを取得 */
	/*
	 *  enatexがtrueで，texptnが0でなければ，タスク例外処理ルーチンを
	 *  呼び出す．
	 *  dispatcherから呼び出されるため，TCBのアドレスはr1に入っている
	 */
	ldrb  r0, [r1,#TCB_enatex]
	tst   r0, #TCB_enatex_mask
	beq   ret_int_r_2           /* enatex が false なら ret_int_r_2へ */
	ldr   r0, [r1,#TCB_texptn]  /* texptn が 0 ならリターン     */
	cbz   r0, ret_int_r_2
	ldr   r2, =ipmflg           /* ipmflgが false ならリターン  */
	ldr   r0, [r2]
	cbz   r0, ret_int_r_2
    /*
     *  戻り先がユーザモードか？
     */
    tst     r3, #0x01           /* 戻り先が特権モードか？ */
    bne     ret_int_r_user      /* 戻り先がユーザモードならばret_int_r_userへ */

	ldrb    r0, [r1,#TCB_svclevel]  /* svclevel が 0 でないならリターン     */
    tst     r0, r0
    bne     ret_int_r_3
    nop

ALABEL(ret_int_r_ker)
	bl    call_texrtn_stask     /* タスク例外ルーチンの呼び出し */
    b       ret_int_r_3
ALABEL(ret_int_r_user)
    /*
     *  ユーザタスクのタスク例外処理ルーチンの入り口へジャンプする
     *  R0 = p_runtsk
     *  CPUロック解除
     */
	mov   r0, #0
	ldr   r2, =lock_flag          /* CPUロック解除状態へ */
	str   r0, [r2]
	ldr   r0, =IIPM_ENAALL        /* 割込み優先度マスクを全解除状態に設定 */
	msr   basepri, r0             
    mov   r0, r1
    svc     #NO_UTEX
    nop
    /*
     *  CPUロック
     */
	ldr   r0, =IIPM_LOCK          /* CPUロック状態 */ 
	msr   basepri, r0          
	mov   r2, #0x01               /* lock_flag を trueに */
	ldr   r0, =lock_flag          
	str   r2, [r0]

ALABEL(ret_int_r_2)
    /*
     *  ここにはsvcからのリターンで戻るため，
     *  r1とr3には，p_runtskと戻り先のCONTROLが入っている
     */
    tst     r3, #0x01
    beq     ret_int_r_3
    /*
     *  pspをuspに切り替え
     *  ret_intでは，priv_modeは切り替えないので，ここでも切り替えない
     */
	str     sp, [r1,#TCB_ssp]   /* タスクのsspを保存 */
    ldr     sp, [r1,#TCB_usp]   /* タスクのuspを復帰 */
ALABEL(ret_int_r_3)
    /*
     *  戻り先がユーザタスクならば，この時点で，PSP = uspである．
     */
    push    {r3}
	svc   0                     /* SVCの呼び出し */

/*
 *  SVCハンドラ
 */
	ATHUMB(svc_handler)
	AGLOBAL(svc_handler)
ALABEL(svc_handler)
	/*
	 *  割込み処理からのリターンにより，CPUロック解除状態に移行するよ
	 *  う準備する．
	 */
	cpsid f                       /* 割込みロック状態へ */
    /*
     *  r0には返り値 or TCBが入っている可能性があるため，使用しない
     *  r1にはTCBが入っている可能性があるため，使用しない
     */
    tst     lr, #0x04
    ite     eq
    mrseq   r2, msp
    mrsne   r2, psp
    ldr     r2, [r2, #24]
    ldrb    r2, [r2, #-2]
    ldr     r3, =svc_vector_tbl
    ldr     r3, [r3, r2, lsl #2]
    mov     pc, r3

/*
 *  ret_int_rの出口
 */
	ATHUMB(ret_int_r_4)
	AGLOBAL(ret_int_r_4)
ALABEL(ret_int_r_4)
	mrs   r0, psp
	add   r0, #EXC_FRAME_SIZE     /* スタックを捨てる   */
    /*
     *  実行モードを元に戻す
     */
    ldmfd   r0!, {r1}           /* pspから戻り先のcontrolを取得 */
    msr     control, r1
	msr   psp, r0
	mov   r0, #0
	ldr   r1, =lock_flag          /* CPUロック解除状態へ */
	str   r0, [r1]
	ldr   r1, =IIPM_ENAALL        /* 割込み優先度マスクを全解除状態に設定 */
	msr   basepri, r1             
	bx    lr                      /* リターン     */

/*
 *  ディスパッチャの動作開始
 */
	ATHUMB(start_dispatch)
	AGLOBAL(start_dispatch)
ALABEL(start_dispatch)
	/*
	 *  このルーチンは，カーネル起動時に，すべての割込みを禁止した状態
	 * （割込みロック状態と同等）で呼び出される．また，割込みモード（非
	 *  タスクコンテキストと同等）で呼び出されることを想定している．
	 *
	 *  core_initializeで，lock_flagをtrueに，saved_iipmをIIPM_ENAALLに
	 *  初期化しているため，カーネル管理外の割込みを許可することで，
	 *  CPUロック状態・（モデル上の）割込み優先度マスク全解除状態になる．
	 *  また，task_initializeでdisdspをfalseに初期化しているため，ディ
	 *  スパッチ許可状態になっている．
	 */
	ldr   r0,=istkpt              /* MSPを初期化   */
	ldr   r1,[r0]                 /* start_dispatch呼び出し時に呼び出し用に */
	msr   msp, r1                 /* 使用しているため初期化する             */
	ldr   r1, =IIPM_LOCK          /* カーネル管理内の割込みを禁止 */
	msr   basepri, r1 
	cpsie f                       /* カーネル管理外の割込みを許可 */
	mov   r0, #CONTROL_PSP        /* PSPを有効に  */
	msr   control, r0
	isb                           /* control の操作後に必要 */

/*
 *  現在のコンテキストを捨ててディスパッチ
 */
	ATHUMB(exit_and_dispatch)
	AGLOBAL(exit_and_dispatch)
ALABEL(exit_and_dispatch)
	/* ディスパッチャ本体（dispatcher）へ */ 


/*
 *  ディスパッチャ本体
 */
ALABEL(dispatcher)
	/*
	 *  このルーチンは，タスクコンテキスト・CPUロック状態・ディスパッチ
	 *  許可状態・（モデル上の）割込み優先度マスク全解除状態で呼び出さ
	 *  れる．
	 *
	 *  すなわち，Threadモード・lock_flagがtrue・disdspがfalse・dspflg
	 *  がtrue・saved_iipmがIIPM_ENAALLとなっている．実行再開番地へもこ
	 *  の状態のまま分岐する．
	 */
#ifdef LOG_DSP_ENTER
	ldr   r1, =p_runtsk     /* p_runtskをパラメータに */
	ldr   r0, [r1]        
	bl    log_dsp_enter
#endif /* LOG_DSP_ENTER */
ALABEL(dispatcher_0)
	ldr   r0, =p_schedtsk   /* p_schedtskをp_runtskに */
	ldr   r1, [r0]
	ldr   r2, =p_runtsk   
	str   r1, [r2]        
	cbz   r1, dispatcher_1  /* p_runtskがNULLならdispatcher_1へ */           
	ldr   sp, [r1,#TCB_ssp] /* タスクのシステムスタックを保存 */

    ldr     r2, [r1, #TCB_p_tinib]
    ldr     r3, [r2, #TINIB_p_dominib]
    ldr     r4, [r3, #DOMINIB_domptn]
    ldrb    r5, [r1, #TCB_svclevel]
    ldr     r0, =rundom
    cmp     r5, #0                      /* svclevel == 0か？ */
    bne     dispatcher_3
    nop
    /*
     *  rundom = p_runtsk->p_tinib->p_dominib->domptn
     */
    str     r4, [r0]
    b       dispatcher_4
    nop

ALABEL(dispatcher_3)
    mov     r5, #0
    str     r5, [r0]
ALABEL(dispatcher_4)
    cmp     r4, #0      /* domptn == 0（カーネルドメイン）か？ */
    beq     dispatcher_5

	/*
	 *  MPUに保護領域を設定
	 */

    /*
     *  ユーザスタック領域
     */
    ldr     r0, =#MPU_REGBASE   /* r0: 領域ベースアドレスレジスタ */
    ldr     r5, [r2, #TINIB_start_ustk]  /* 先頭番地 */
    ldr     r4, [r2, #TINIB_atrsz_ustk]  /* 保護属性とサイズ */
    ldr     r2, =#MPU_REGATR    /* r2: 領域属性およびサイズレジスタ */
    str     r5, [r0]
    str     r4, [r2]

   	/*
	 *  実行ドメインと保護ドメイン(MPUの設定)が同じならば，
     *  ドメイン毎のコード領域・データ領域をMPUに設定し直す必要はない
     */
    ldr     r5, =p_ctxdom       /* r5 = &p_ctxdom */	
    ldr     r4, [r5]            /* r4 = p_ctxdom */
	cmp     r4, r3              /* p_ctxdom == p_dominb ? */
	beq     dispatcher_5        /* 同じならdispatcher_5へ */
    nop
	str     r3, [r5]            /* p_ctxdom = p_dominib : 保護ドメインを切替え */
    ldr     r3, [r3, #DOMINIB_p_dominib_info]
  
    /*
     *  自保護ドメイン専用のRX領域
     */
    ldr     r5, [r3, #DOMINIB_start_rom]  /* 先頭番地 */
    ldr     r4, [r3, #DOMINIB_atrsz_rom]  /* 保護属性とサイズ */
    str     r5, [r0]
    str     r4, [r2]

    /* 
     * 自保護ドメイン専用のRWX領域
     */
    ldr     r5, [r3, #DOMINIB_start_ram]  /* 先頭番地 */
    ldr     r4, [r3, #DOMINIB_atrsz_ram]  /* 保護属性とサイズ */
    str     r5, [r0]
    str     r4, [r2]

    /*
     * 共有リード/専用ライト領域の専用領域
     */
    ldr     r5, [r3, #DOMINIB_start_srpw]  /* 先頭番地 */
    ldr     r4, [r3, #DOMINIB_atrsz_srpw]  /* 保護属性とサイズ */
    str     r5, [r0]
    str     r4, [r2]

    /*
     * ATT_MEMで登録された領域
     */
    ldr     r5, [r3, #DOMINIB_start_mem]  /* 先頭番地 */
    ldr     r4, [r3, #DOMINIB_atrsz_mem]  /* 保護属性とサイズ */
    str     r5, [r0]
    str     r4, [r2]

ALABEL(dispatcher_5)
#ifdef LOG_DSP_LEAVE
	mov   r0, r1            /* p_runtskをパラメータに */
	mov   r4, r1            /* r1はスクラッチレジスタなので保存 */
	bl    log_dsp_leave
	mov   r1, r4
#endif /* LOG_DSP_LEAVE */
	ldr   pc, [r1,#TCB_pc]  /* 実行再開番地を復帰   */    
ALABEL(dispatcher_1)
	/*
	 * CPUロック状態の解除と，非タスクコンテキスト実行状態への
	 * 準備をする
	 */
	mov   r0, #CONTROL_MSP  /* MSPを有効に  */
	msr   control, r0       
	isb                     /* control の操作後に必要 */
	mov   r4, #0            /* r4 <- '0' */
	ldr   r5, =IIPM_LOCK    /* r5 <- 割込みロック状態の割込み優先度マスクの値 */
	ldr   r6, =reqflg       /* r6 <- reqflg */
	ldr   r7, =lock_flag    /* r7 <- lock_flg */
	str   r4, [r7]          /* CPUロック解除状態へ */
ALABEL(dispatcher_2)
	/*
	 *  割込みを許可し，非タスクコンテキスト実行状態とし割込みを待つ．
	 *
	 *  ここで非タスクコンテキスト実行状態に切り換えるのは，ここで発生
	 *  する割込み処理にどのスタックを使うかという問題の解決と，割込み
	 *  ハンドラ内でのタスクディスパッチの防止という2つの意味がある．
	 *
	 *  プロセッサを割込み待ちに移行させる処理と，割込み許可とは，不可
	 *  分に行なう必要がある．
	 *  これを不可分に行なわない場合，割込みを許可した直後に割込
	 *  みが入り，その中でタスクが実行可能状態になると，実行すべきタス
	 *  クがあるにもかかわらずプロセッサが割込み待ちになってしまう．
	 *  ARM-Mでは，PRIMASKをセットした状態でWFIを呼び出すことで実現できる．
	 *  この状態で割込みが入ると，割込みは実行されず，WFIからリターンす
	 *  ることになるので，一旦割込みを許可して割込みハンドラを実行する．
	 *
	 *  割込み待ちの間は，p_runtskをNULL（＝0）に設定しなければならな
	 *  い．このように設定しないと，割込みハンドラからiget_tidを呼び出
	 *  した際の動作が仕様に合致しなくなる．
	 *
	 *  ターゲットによっては，省電力モード等に移行するため，標準の方法と
	 *  異なる手順が必要な場合がある．
	 *  そのようなターゲットでは，ターゲット依存において，TOPPERS_CUSTOM_IDLE
	 *  を定義し，アセンブラマクロとして，toppers_asm_custom_idle を用意
	 *  すればよい．
	 *
	 *  なお，toppers_asm_custom_idle の記述にあたっては，次のレジスタは
	 *  toppers_asm_custom_idleの前後で使用するため，
	 *  toppers_asm_custom_idle 内で使用する場合は，前後で保存復帰すること．
	 *  これらのレジスタは Calee saved レジスタであるため， 
	 *  toppers_asm_custom_idle として関数呼び出しをした場合は，呼び出した
	 *  関数で自動的に保存復帰されるため，アセンブラレベルでの保存復帰は必
	 *  要ない．
	 *
	 *  レジスタ : 内容
	 *   r4      : '0'
	 *   r5      : 'IIPM_LOCK'
	 *   r6      : reqflgのアドレス
	 *   r7      : lock_flgのアドレス
	 *   sp      : 非タスクコンテキスト用のスタックの先頭アドレス(msp)
	 */
#ifdef TOPPERS_CUSTOM_IDLE
	toppers_asm_custom_idle
#else
	cpsid i               /* PRIMASK をセット */
	msr   basepri, r4     /* 全割込み許可 */ 
	wfi
	cpsie i               /* PRIMASK をクリア（割込みを受け付ける） */
	msr   basepri, r5     /* CPUロック状態へ */ 
#endif /* TOPPERS_CUSTOM_IDLE */

	ldr   r0, [r6]        /* reqflgがfalseならdispatcher_2へ */
	cmp   r0, #0
	beq   dispatcher_2
	str   r4, [r6]        /* reqflgをfalseに */

	/*
	 *  CPUロック状態に戻す．割込み待ちの間に実行した割込みハンドラによ
	 *  り，saved_iipmが書き換えられる可能性があるため，元の値に戻す必
	 *  要がある．dispatcherが実行される時は，saved_iipmがIIPM_ENAALL
	 *  となっているため，ここではsaved_iipmをIIPM_ENAALL（＝0）に戻せ
	 *  ばよい．
	 */
	mov   r0, #CONTROL_PSP  /* PSPを有効に  */ 
	msr   control, r0      
	isb                     /* control の操作後に必要 */
	mov   r2, #1            /* lock_flagをtrueへ */
	str   r2, [r7]
	ldr   r0, =saved_iipm   /* saved_iipm を0に */
	str   r4, [r0]
	b     dispatcher_0


/*
 *  カーネルの終了処理の呼出し
 *
 *  スタックを非タスクコンテキスト用に切り替え．
 *  
 */
	ATHUMB(call_exit_kernel)
	AGLOBAL(call_exit_kernel)
ALABEL(call_exit_kernel)
	mov   r0, #CONTROL_MSP
	msr   control, r0       /* MSPを有効に  */
	isb                     /* control の操作後に必要 */
	ldr   r0, =exit_kernel  /* カーネルの終了処理を呼ぶ */
	bx    r0


/*
 *  タスク起動処理
 *
 *  dispatcherから呼び出されるため，TCBのアドレスはr1に入っている
 *
 */ 
	ATHUMB(start_stask_r)
	AGLOBAL(start_stask_r)
ALABEL(start_stask_r)
#ifdef TOPPERS_SUPPORT_OVRHDR
    push    {r1}  /* TCBのアドレスを退避 */
    bl      ovrtimer_start
    nop
    pop     {r1} /* TCBのアドレスを復帰 */
#endif /* TOPPERS_SUPPORT_OVRHDR */
	mov   r0, #0
	ldr   r4, =lock_flag                    /* CPUロック解除状態へ */
	str   r0, [r4]
	msr   basepri, r0                       /* 割込み許可   */
	ldr   lr, =ext_tsk                      /* 戻り番地設定 */
	ldr   r2, [r1, #TCB_p_tinib]            /* p_runtsk->p_tinibをr2に  */
	ldr   r0, [r2, #TINIB_exinf]            /* exinfを引数レジスタr0に  */
	ldr   r1, [r2, #TINIB_task]             /* タスク起動番地にジャンプ */
	bx    r1

	ATHUMB(start_utask_r)
	AGLOBAL(start_utask_r)
ALABEL(start_utask_r)
#ifdef TOPPERS_SUPPORT_OVRHDR
    push    {r1}  /* TCBのアドレスを退避 */
    bl      ovrtimer_start
    nop
    pop     {r1} /* TCBのアドレスを復帰 */
#endif /* TOPPERS_SUPPORT_OVRHDR */
    svc     #NO_UTASK_START
    nop

    /*
     *  例外からのリターンでユーザモード、割込み許可となり、
     *  タスクの起動番地にジャンプするように準備する
     *  ここには，handlerモードの割込みロック状態でくる（FAULTMASK = 1）
     *  例外からのリターンにより，割込みロックは解除される
     *  sspは初期値から変更されないので，ここで例外フレームを
     *  捨てる必要はない
     */
	ATHUMB(start_utask_r_1)
	AGLOBAL(start_utask_r_1)
ALABEL(start_utask_r_1)
    mov     r0, #0
    ldr     r4, =lock_flag
    str     r0, [r4]                        /* CPUロック解除 */
    msr     basepri, r0                     /* 割込み許可 */
    ldr     r4, [r1, #TCB_p_tinib]          /* r4 = p_runtsk->p_tinib */
    strb    r0, [r1, #TCB_priv_mode]        /* 特権モード実行を抜ける */
    ldr     r3, [r4, #TINIB_ustk_bottom]    /* r3 = ユーザスタックポインタの初期値 */
    mov     r0, #0x01                       /* ユーザモードに移行 */
    msr     control, r0
    ldr     r0, =call_ext_tsk               /* lr */
    orr     r0, r0, #0x01                   /* 戻り先はthumbモード */
	ldr     r1, [r4, #TINIB_task]           /* PC */
	ldr     r2, =EPSR_T                     /* xPSR(Tビットが'1'である必要がある) */
    stmfd   r3!, {r0-r2}                    /* xPSR, PC, lrをpspに積む */
    sub     r3, #(4*4)                      /* r12,r3,r2,r1は積まない */
	ldr     r0, [r4, #TINIB_exinf]          /* r0：引数 */
    stmfd   r3!, {r0}                       /* r0をpspに積む */
    msr     psp, r3                         /* pspをユーザスタックポインタで初期化 */
    bx      lr                              /* タスクの起動番地へ */
    nop

    nop

    /*
     *  ext_tskをsvc命令で呼び出す
     */
    ASECTION(.text_shared)
    AALIGN(2)
    ATHUMB(call_ext_tsk)
    AGLOBAL(call_ext_tsk)
ALABEL(call_ext_tsk)
    mov     r4, #TFN_EXT_TSK
    svc     #NO_SVC
    nop
    mov     r4, #TFN_EXT_KER
    svc     #NO_SVC
    nop

/*
 *  svcベクタテーブル
 */
    AGLOBAL(svc_vector_tbl)
    ASECTION(.text_kernel)
ALABEL(svc_vector_tbl)
    ALONG  ret_int_r_4
    ALONG  start_utask_r_1
    ALONG  svc_entry
    ALONG  svc_entry_r_2
    ALONG  prepare_texrtn_utask
    ALONG  ret_tex
    ALONG  ret_tex_r

    /*
     *  svc_entryをsvc命令で呼び出す
     */
    ASECTION(.text_shared)
    AALIGN(2)
    ATHUMB(call_svc_entry)
    AGLOBAL(call_svc_entry)
ALABEL(call_svc_entry)
    push    {r5-r10,lr}
    mrs     r8, ipsr
    tst     r8, r8
    beq     call_svc_entry_1
    /*
     *  呼び出し元が割込みや例外
     */
    stmfd   sp!, {r0-r3,r12}
    mrs     r9, control
    mov     r9, #0x00
    bl      svc_entry_1
    cpsie   f
    ldmfd   sp!, {r0-r3,r12}
    b       call_svc_entry_2
ALABEL(call_svc_entry_1)
    /*
     *  呼び出し元が割込みや例外でない
     */
    svc     #NO_SVC
ALABEL(call_svc_entry_2)
    pop     {r5-r10,lr}
    bx      lr

    /*
     *  サービスコールの出入口処理
     *  呼び出し条件：
     *    Handlerモード
     *    r4: func ID
     */
	ATEXT
	AALIGN(2)
	ATHUMB(svc_entry)
    AGLOBAL(svc_entry)
ALABEL(svc_entry)
    ldr     r8, =p_runtsk   /* 実行中のタスク */
    ldr     r8, [r8]        /* 実行中のタスクのTCB */
    /* 
     *  R9: 呼び出し元を特定するためのビットマップ
     *    0x01: excnest_count == 0 && rundom != TACP_KERNEL
     *    0x02: excnest_count == 0
     */
    mov     r9, #0          /* 0初期化 */

    /*
	 *  タスクコンテキストからの呼び出しかチェック
	 */
	tst     lr, #EXC_RETURN_PSP /* 戻り先がPSPでないか？  */
	beq     svc_entry_1         /* 非タスクコンテキストからの呼出しならばスキップ */
    nop
    orr     r9, r9, #0x02       /* タスクコンテキストのビットをセット */

    /*
     *  ユーザドメインからの呼び出しかチェック
     *  拡張サービスコール実行中であれば，
     *  カーネルドメインからの呼び出しとなるので，
     *  svclevelのチェックは必要ない
     *  svc命令によって，引数はpspに積まれている
     */
    mrs     r10, psp
    ldmfd   r10, {r0-r3,r12}             /* 引数を復帰 */
    ldr     r6, =rundom
    ldr     r6, [r6]        /* r6 = rudom */
    tst     r6, r6          /* rundom == TACP_KERNEL(0)？ */
    beq     svc_entry_1     /* TACP_KERNELならばスキップ */
    orr     r9, r9, #0x01   /* rundom != TACP_KERNELのビットをセット */

    /*
     *  ユーザスタックとシステムスタックを入れ替える
     *  タスクの状態を特権モード実行中に移行する
     *  戻り先がタスクコンテキストならば，タスク実行中であるはず
     *  なので，p_runtskがNULLかどうかのチェックは必要ないはず
     */
    mov     r6, #0x00
    msr     control, r6                 /* 特権モードへ移行 */
    str     r10, [r8, #TCB_usp]          /* uspを保存 */
    ldr     r10, [r8, #TCB_ssp]          /* sspを復帰 */
    mov     r6, #0x01
    strb    r6, [r8, #TCB_priv_mode]

ALABEL(svc_entry_1)
    /*
     *  機能コードのチェック
     */
    cmp     r4, #TMIN_FNCD
	blt     svc_entry_7     /* 下限よりも下ならばエラー */
	cmp     r4, #0 			/* 機能コードの符号チェック(0 < r1) */
    ble     svc_entry_2     /* サービスコールの場合 */
    nop
	b       extsvc_entry   /* 拡張サービスコールの場合 */
    nop

ALABEL(svc_entry_2)
    /*
     *  呼び出し元が非タスクコンテキストか？
     */
    tst     r9, #0x02       
	beq     svc_entry_3  /* 非タスクコンテキストならばスキップ */

    /*
     *  svcからのリターン
     *  例外処理マスク状態を解除
     *  r10 = psp
     */
	ldr     r6, =EPSR_T                 /* xPSR(Tビットが'1'である必要がある) */
    ldr     r5, =svc_entry_4            
    stmfd   r10!, {r4-r6}                /* xPSR, pc, lrを積む（lrはダミー） */
    stmfd   r10!, {r0-r3,r12}            /* r0-r3,r12を積み直し */
    msr     psp, r10
    bx      lr

ALABEL(svc_entry_3)
    cpsie   f
    ldmfd   sp, {r0-r3,r12}             /* 引数を復帰 */
    push    {lr}                        /* EXC_RETURNを保存 */

ALABEL(svc_entry_4)
    /*
     *  タスクコンテキストからの呼出しならば
     *    Threadモード, PSP, 特権モード
     */
    stmfd   sp!, {r12}      /* 第5引数をスタックに積む */

    /*
     *  サービスコールのテーブルを引き，
     *  サービスコールの本体を呼ぶ
     */
    rsb     r4, r4, #0              /* 符号反転 */
    ldr     r5, =svc_table
	ldr     r5, [r5, r4, lsl #0x02] /* テーブルを引く */
	blx     r5                      /* サービスコール処理ルーチンを呼ぶ */
    nop

	ldmfd   sp!, {r12}              /* 第5引数をスタックから取り除く */

    /*
     *  例外処理マスク状態へ
     */
    cpsid   f

ALABEL(svc_entry_r)
    /*
     *  ここには例外処理マスク状態でジャンプしてくる
     */
    /*
     *  この時点での割込み優先度マスクをr3に保存する
     *  chg_ipmやloc_cpuでbasepriを更新した時への対応
     */
    mrs     r3, basepri

    /*
	 *  戻り先がタスクコンテキストかチェック
	 */
    tst     r9, #0x02       /* 非タスクコンテキストからの呼出し */
    ittt    eq
    popeq   {lr}
    mrseq   r10, msp
    beq     svc_entry_r_4   /* ならばスキップ */

    /*
     *  戻り先がユーザドメインかチェック
     *  拡張サービスコール実行中であれば，
     *  戻り先はカーネルドメインなので，
     *  svclevelのチェックは必要ない
     */
    tst     r9, #0x01       /* カーネルドメインからの呼出し */
    beq     svc_entry_r_1   /* ならばスキップ */

	/*
	 *  待ち禁止を解除
	 */
    ldrb    r1, [r8, #TCB_waifbd]
    bfc     r1, #TCB_waifbd_bit, #1
    strb    r1, [r8, #TCB_waifbd]
	
    /*
	 *  タスク例外処理実行条件がそろっているかチェック
	 */
	ldrb    r1, [r8, #TCB_texptn]       /* 保留例外要因の読出し */
	cbz     r1, svc_entry_r_1           /* 0ならリターン */
	ldrb    r1, [r8, #TCB_enatex]       /* タスク例外処理許可状態の読出し */
    tst     r1, #TCB_enatex_mask        /* タスク例外処理禁止状態か？ */
	beq     svc_entry_r_1               /* 禁止ならリターン */

	/*
     *  割込みマスク全解除状態か？ 
     */
    ldr     r1, =ipmflg
    ldr     r1, [r1]
    cbz     r1, svc_entry_r_1   /* ipmflg == falseならリターン */

	/*
     *  サービスコールからのリターン後のシステム状態がCPUロック解除状態か？
     */
    ldr     r1, =lock_flag
    ldr     r1, [r1]
    cbnz    r1, svc_entry_r_1   /* CPUロック解除状態でなければリターン */

    /*
     *  タスク例外呼び出し条件が揃っていれば，
     *  ユーザタスクのタスク例外処理へ
     *  r0 = p_runtsk
     */
    stmfd   sp!, {r0,r3}    /* 返り値とbasepriをスタックに保存 */
    mov     r0, r8
    cpsie   f
    svc     #NO_UTEX
    nop
    ldmfd   sp!, {r0,r3}    /* 返り値とbasepriをスタックから復帰 */

ALABEL(svc_entry_r_1)
    cpsie   f
    svc     #NO_SVC_R

	ATHUMB(svc_entry_r_2)
    AGLOBAL(svc_entry_r_2)
ALABEL(svc_entry_r_2)
    /*
     *  戻り先がユーザドメインかチェック
     */
    mrs     r10, psp
	add     r10, #EXC_FRAME_SIZE     /* スタックを捨てる   */
    tst     r9, #0x01               /* カーネルドメインからの呼出し */
    beq     svc_entry_r_3           /* ならばスキップ */

    /* 
     *  特権モード実行を抜ける
     */
    mov     r1, #0
    strb    r1, [r8, #TCB_priv_mode]
    /*
     *  sstkとustkを入れ替える
     *  タスクの状態をユーザモード実行中に移行する
     *  戻り先がタスクコンテキストならば，タスク実行中であるはず
     *  なので，p_runtskがNULLかどうかのチェックは必要ないはず
     */
    mov     r1, #0x01
    msr     control, r1                 /* ユーザモードへ移行 */
    str     r10, [r8, #TCB_ssp]          /* sspを保存 */
    ldr     r10, [r8, #TCB_usp]          /* uspを復帰 */
    
ALABEL(svc_entry_r_3)
    msr     psp, r10     /* pspを切り替え */

ALABEL(svc_entry_r_4)
    str     r0, [r10]    /* リターン時のspの先頭を返り値で置き換え */
    bx      lr          /* 呼出し元へリターン */
    nop

/*
 *  エラー処理には例外処理マスク状態でジャンプしてくる
 */
ALABEL(svc_entry_7)
	ldr     r0, =#E_RSFN    /* エラーコードを返り値に */ 
    b       svc_entry_error_r
    nop

ALABEL(svc_entry_error_r)
    /*
	 *  戻り先がタスクコンテキストかチェック
	 */
    tst     r9, #0x02       /* 非タスクコンテキストからの呼出し */
    itt     eq
    mrseq   r10, msp
    beq     svc_entry_r_4   /* ならばsvc_entry_r_4へ */

    /*
     *  戻り先がユーザドメインかチェック
     *  r10 = sspであり，何も積まれていない
     */
    tst     r9, #0x01               /* カーネルドメインからの呼出し */
    beq     svc_entry_r_3           /* ならばスキップ */

    /* 
     *  特権モード実行を抜ける
     */
    mov     r1, #0
    strb    r1, [r8, #TCB_priv_mode]
    /*
     *  sstkとustkを入れ替える
     *  タスクの状態をユーザモード実行中に移行する
     *  戻り先がタスクコンテキストならば，タスク実行中であるはず
     *  なので，p_runtskがNULLかどうかのチェックは必要ないはず
     */
    mov     r1, #0x01
    msr     control, r1                 /* ユーザモードへ移行 */
    str     r10, [r8, #TCB_ssp]          /* sspを保存 */
    ldr     r10, [r8, #TCB_usp]          /* uspを復帰 */
    
    b       svc_entry_r_3

#define SVCINIB_svcrtn 0
#define SVCINIB_stksz  4

	ATHUMB(extsvc_entry)
    AGLOBAL(extsvc_entry)
ALABEL(extsvc_entry)
    /*
     *  機能コードのチェック
     */
    ldr     r5, =tmax_fncd
    ldr     r5, [r5]
    cmp     r4, r5                  /* 機能コードの上限チェック(tmax_fncd < r4) */
    bgt     extsvc_error_RSFN       /* 上限をオーバしているならばエラー */

    /*
     *  拡張サービスコールのテーブルを引く
     *  R3 = &svcinib
     */
    ldr     r5, =svcinib_table
    sub     r4, r4, #1                  /* 機能コード -= 1 */
    add     r5, r5, r4, lsl #3          /* offset = (機能コード - 1) << 3 (*=8) */

    /*
     *  拡張サービスコール本体のアドレスがNULLでないか？
     */
    ldr     r4, [r5, #SVCINIB_svcrtn]   /* R0 = svcinib->svcrtn */
    tst     r4, r4
    beq     extsvc_error_RSFN           /* NULLならばエラー */
    nop
    push    {r4}                        /* svcrtnをistkに保存 */

    /*
     *  呼び出し元が非タスクコンテキストか？
     */
	mov     r4, #TDOM_KERNEL    /* 呼び出し元はTDOM_KERNEL */
    tst     r9, #0x02       
	beq     extsvc_entry_2  /* 非タスクコンテキストならばスキップ */

    /*
     *  スタックの残量をチェック
     *  r10 = ssp
     */
    ldr     r4, [r8, #TCB_p_tinib]          /* r4 = p_runtsk->tinib */
    ldr     r6, [r4, #TINIB_sstk_bottom]    /* r6 = sstkの底のアドレス */
    subs    r6, r6, r10                     /* r6 = sstk_bottom - ssp */
    blo     extsvc_error_NOMEM              /* r6 < r10 ならばエラー処理へ */
    ldr     r5, [r5, #SVCINIB_stksz]        /* R4 = svcinib->stksz */
    add     r6, r6, r5                      /* r6 = r6 + 使用するスタックサイズ */
    bvs     extsvc_error_NOMEM              /* オーバフローしたらエラー処理へ */
    ldr     r5, [r4, #TINIB_sstksz]         /* r4 = sstkのサイズ */
    cmp     r6, r5                          /* r6 <= r5 ？ */
    bhi     extsvc_error_NOMEM              /* そうでなければエラー処理へ */
    nop

    /*
     *  svclevelをインクリメント
     */
    ldrb    r5, [r8, #TCB_svclevel] /* svclevelを読み込む */
    cmp     r5, #255                /* svclevelの上限チェック */
	bhs     extsvc_error_SYS        /* ネストの上限だった場合エラー */
	add     r5, r5, #1              /* svclevel += 1 */
    strb    r5, [r8, #TCB_svclevel] /* svclevelを更新 */

    /*
     *  実行ドメインをカーネルドメインへ
     */
	mov     r6, #TDOM_KERNEL    /* 呼び出し元はTDOM_KERNEL */
    tst     r9, #0x01           /* rundom != TACP_KERNEL か？ */
	beq     extsvc_entry_1      /* カーネルドメインならばスキップ */
    ldr     r5, =rundom
    mov     r6, #0x00
	str     r6, [r5]            /* rundom = TACP_KERNEL */

    /*
     *  domidを求める
     */
    ldr     r5, [r4, #TINIB_p_dominib]  /* R5 = p_dominib */
    ldr     r4, =dominib_table          /* R4 = dominib_table */
    sub     r4, r5, r4                  /* R4 = &dominib_table[x] - &dominib_table[0] */
    /*
     *  dominibのサイズは8byte
     */
    /*
     *  R0 = 8x 
     *  => 8x / 8 = x
     *  右に3bitシフト
     */
    asr     r4, #3
    add     r6, r4, #TMIN_DOMID
    nop

ALABEL(extsvc_entry_1)
    mov     r4, r6
    /*
     *  svcからのリターン
     *  例外処理マスク状態を解除
     *  r0-r3, r12を復帰
     */
	ldr     r6, =EPSR_T                 /* xPSR(Tビットが'1'である必要がある) */
    ldr     r5, =extsvc_entry_3            
    stmfd   r10!, {r4-r6}                /* xPSR, pc, lrを積む（lrはダミー） */
    stmfd   r10!, {r0-r3,r12}            /* r0-r3,r12を積み直し */
    msr     psp, r10
    pop     {r6}                        /* svcrtnを復帰 */
    bx      lr

ALABEL(extsvc_entry_2)
    cpsie   f
    pop     {r6}                        /* svcrtnを復帰 */
    ldmfd   sp, {r0-r3,r12}             /* 引数を復帰 */
    push    {lr}                        /* EXC_RETURNを保存 */

ALABEL(extsvc_entry_3)
    /*
     *  タスクコンテキストからの呼出しならば
     *    Threadモード, PSP, 特権モード
     */
    stmfd   sp!, {r4}           /* 呼び出し元のdomidと第5引数をスタックに積む */
    stmfd   sp!, {r12}          /* 呼び出し元のdomidと第5引数をスタックに積む */

    /*
     *  拡張サービスコールの本体を呼ぶ
     */
	blx     r6                  /* サービスコール処理ルーチンを呼ぶ */
    nop
    ldmfd   sp!, {r1,r2}        /* 呼び出し元のdomidと第5引数をスタックから除去 */

    /*
     *  例外処理マスク状態へ
     */
    cpsid   f

ALABEL(extsvc_entry_r)
    /*
     *  ここには例外処理マスク状態でジャンプしてくる
     */
    /*
     *  この時点での割込み優先度マスクをr3に保存する
     *  chg_ipmやloc_cpuでbasepriを更新した時への対応
     */
    mrs     r3, basepri

    /*
     *  呼び出し元が非タスクコンテキストか？
     */
    mrs     r10, msp
    tst     r9, #0x02       /* 非タスクコンテキストからの呼出し */
    itt     eq
    popeq   {lr}
    beq     svc_entry_r_4   /* ならばスキップ */

    /*
     *  svclevelをデクリメント
     */
    ldrb    r1, [r8, #TCB_svclevel] /* svclevelを読み込む */
    sub     r1, r1, #1              /* svclevel -= 1 */
    strb    r1, [r8, #TCB_svclevel] /* svclevelを更新 */
    tst     r1, r1
    bne     svc_entry_r_1           /* svclevel == 0でなければリターン */
    
    /*
     *  実行ドメインを所属ドメインに戻す
     */
   	ldr     r1, [r8, #TCB_p_tinib]      /* タスク初期化ブロックの読み出し */
	ldr     r1, [r1, #TINIB_p_dominib]  /* ドメイン初期化ブロックの読み出し */
	ldr     r1, [r1, #DOMINIB_domptn]   /* 所属ドメインの取得 */
    ldr     r2, =rundom                 /* R2 = &rundom */
    str     r1, [r2]                    /* rundom = 所属ドメイン */
    /*
     *  サービスコール実行中に拡張サービスコールに入ることはないため、
     *  リターン先が非タスクコンテキストでないならば、リターン後は
     *  タスク例外処理保留状態ではない
     */

    /*
     *  待ち禁止状態を解除する
     */
    ldrb    r1, [r8, #TCB_waifbd]
    bfc     r1, #TCB_waifbd_bit, #1
    strb    r1, [r8, #TCB_waifbd]

    /*
	 *  タスク例外処理実行条件がそろっているかチェック
	 */
	ldrb    r1, [r8, #TCB_texptn]       /* 保留例外要因の読出し */
    tst     r1, r1
	beq     svc_entry_r_1               /* 0ならリターン */
	ldrb    r1, [r8, #TCB_enatex]       /* タスク例外処理許可状態の読出し */
    tst     r1, #TCB_enatex_mask        /* タスク例外処理禁止状態か？ */
	beq     svc_entry_r_1               /* 禁止ならリターン */

	/*
     *  割込みマスク全解除状態か？ 
     */
    ldr     r1, =ipmflg
    ldr     r1, [r1]
    tst     r1, r1
    beq     svc_entry_r_1   /* ipmflg == falseならリターン */

	/*
     *  サービスコールからのリターン後のシステム状態がCPUロック解除状態か？
     */
    ldr     r1, =lock_flag
    ldr     r1, [r1]
    tst     r1, r1
    bne     svc_entry_r_1   /* CPUロック解除状態でなければリターン */

    /*
     *  戻り先がユーザドメインかチェック
     */
    tst     r9, #0x01           /* 呼び出し元のドメイン == TACP_KERNELか？ */
	bne     extsvc_usr_r_texrtn

ALABEL(extsvc_prv_r_texrtn)
    /*
     *  CPUロック
     */
    ldr     r2, =#IIPM_LOCK
    msr     basepri, r2
    ldr     r1, =lock_flag
    mov     r2, #0x01
    str     r2, [r1]
    ldr     r1, =saved_iipm
    mov     r2, #IIPM_ENAALL
    str     r2, [r1]

    stmfd   sp!, {r0,r3}    /* 返り値とbasepriをスタックに保存 */

    /*
     *  例外処理マスク状態解除
     */
    cpsie   f

    /* 
     *  システムタスク用のタスク例外処理入り口へ
     */
    bl      call_texrtn_stask
    nop

    /*
     *  例外処理マスク状態へ
     */
    cpsid   f

    ldmfd   sp!, {r0,r3}    /* 返り値とbasepriをスタックにから復帰 */

    /*
     *  リターン後にCPUロック解除，割込み優先度マスク全解除となるよう
     *  準備する
     *  call_texrtn_staskの出口処理でipmflgはtrueになっており，また，
     *  その出口処理でディスパッチしても，そのディスパッチ元に戻る時点
     *  では，ipmflgはtrueであるため，lock_flagとbasepriだけ更新する
     */
    ldr     r1, =lock_flag
    mov     r2, #0
    str     r2, [r1]
    ldr     r2, =#IIPM_ENAALL
    msr     basepri, r2

    b       svc_entry_r_1   /* リターン */
    nop

ALABEL(extsvc_usr_r_texrtn)
    stmfd   sp!, {r0,r3}    /* 返り値とbasepriをスタックに保存 */
    mov     r0, r8          /* r0 = p_runtsk */
    cpsie   f
    svc     #NO_UTEX        /* ユーザタスク用のタスク例外処理入り口へ */
    nop
    ldmfd   sp!, {r0,r3}    /* 返り値とbasepriをスタックから復帰 */
    b       svc_entry_r_1   /* リターン */
    nop

ALABEL(extsvc_error_RSFN)
	ldr     r0, =#E_RSFN    /* エラーコードを返す */
    b       svc_entry_error_r
    nop
ALABEL(extsvc_error_NOMEM)
	ldr     r0, =#E_NOMEM   /* エラーコードを返す */
    pop     {r6}            /* svcrtnをスタックから削除 */
    b       svc_entry_error_r
    nop
ALABEL(extsvc_error_SYS)
	ldr     r0, =#E_SYS     /* エラーコードを返す */
    pop     {r6}            /* svcrtnをスタックから削除 */
    b       svc_entry_error_r
    nop

    /*
     *  ユーザタスクのタスク例外処理ルーチンの入り口
     *  呼出し条件
     *  - Handlerモード
     *  - FAULTMASK = 1
     *  - 特権モード（CONTROL[0] == 0）
     *  - psp = sstk
     *  - R0 = p_runtsk
     */
    ATHUMB(prepare_texrtn_utask)
    AGLOBAL(prepare_texrtn_utask)
ALABEL(prepare_texrtn_utask)
    push    {r4-r6}                         /* ret_texで復帰する */
    /*
     *  ユーザスタックの残量をチェック
     *  uspの現在値
     *  特権モード時に使用するサイズ
     *    タスク例外処理本体で使用する分については，
     *    ユーザモードで実行するため，
     *    実行時にスタックオーバフローを検出できる
     */
    ldr     r1, [r0, #TCB_p_tinib]          /* r1 = p_runtsk->tinib */
    ldr     r3, [r1, #TINIB_ustk_bottom]    /* r3 = ユーザスタックの底のアドレス */
    ldr     r2, [r0, #TCB_usp]              /* r2 = usp */
    subs    r3, r3, r2                      /* r3 = ustk_bottom - usp */
    blo     error_nomem_texrtn              /* r3 < r2 ならばエラー処理へ */
    add     r3, r3, #USRTEX_STKSZ           /* r3 = r3 + 使用するスタックサイズ */
    bvs     error_nomem_texrtn              /* オーバフローしたらエラー処理へ */
    ldr     r4, [r1, #TINIB_ustksz]         /* r4 = ユーザスタックのサイズ */
    cmp     r3, r4                          /* r3 <= r4 ？ */
    bhi     error_nomem_texrtn              /* そうでなければエラー処理へ */
    nop

    /* 
     *  ユーザスタックへの退避
     *   ディスパッチ禁止状態：disdsp   <- new usp
     *                                  <- old usp
     */
    ldr     r4, =disdsp         /* r4 = &disdsp */
    ldr     r4, [r4]            /* r4 = disdsp */
    stmfd   r2!, {r4}        /* ユーザスタックに退避 */
    str     r2, [r0, #TCB_usp]  /* uspのセット */

    /*
     * R0 = p_runtsk
     * R1 = p_tinib
     * R2 = usp
     */
ALABEL(prepare_texrtn_utask_r)
    /*
     *  特権モードを解除してタスク例外処理ルーチンへジャンプ
     */
    /*
     *  タスク例外処理ルーチンのアドレスを準備
     *  タスク例外処理ルーチンからの戻り番地をcall_ret_texに指定
     */
	ldr     r5, =EPSR_T                 /* xPSR(Tビットが'1'である必要がある) */
    ldr     r4, [r1, #TINIB_texrtn]
    ldr     r3, =call_ret_tex
    orr     r3, r3, #0x01       /* 戻り先はthumbモード */
    stmfd   r2!, {r3-r5}        /* ユーザスタックに退避 */

    /*
     *  タスク例外処理ルーチンの引数を準備
     */
    /* 第1引数：R0 = p_runtsk->texptn */
    /* 第2引数：R1 = p_runtsk->p_tinib->exinf */
    ldr     r3, [r0, #TCB_texptn]       /* 例外パターン */
    ldr     r4, [r1, #TINIB_exinf]      /* 拡張情報 */
    stmfd   r2!, {r3-r6,r12}            /* ユーザスタックに退避（r0,r1以外はダミー） */

    /*
     *  ユーザスタックへの切り替え
     */
    mrs     r1, psp
    str     r1, [r0, #TCB_ssp]          /* sspの保存 */
    msr     psp, r2

    /* 
     *  特権モード実行を抜ける
     */
    mov     r1, #0x01
    msr     control, r1
    mov     r1, #0
    strb    r1, [r0, #TCB_priv_mode]    

	str     r1, [r0, #TCB_texptn]       /* p_runtsk->texptn = 0 */
    /* 
     *  p_runtsk->enatex = false
     */
    ldrb    r1, [r0, #TCB_enatex]
    bfc     r1, #TCB_enatex_bit, #1
	strb    r1,	[r0, #TCB_enatex]       /* p_runtsk->enatex = false */
   
    bx      lr                          /* 例外からのリターンによってタスク例外処理へ */
    nop
/*
 *  タスク例外実行開始時スタック不正例外ハンドラを呼び出す
 */
ALABEL(error_nomem_texrtn)
    /*
     *  エミュレートされたCPU例外を呼ぶ
     *  例外からのリターンでprepare_texrtn_utaskの呼び出し元に戻る
     */
	mrs   r0, psp                /* 一段目の割込みの場合はPSP上に */
	mrs   r2, basepri             /* baepriの値を取得 */
	stmfd r0!,{r2}               /* 割込み発生時の割込み優先度マスクを積む */
	stmfd r0!,{lr}               /* EXC_RETURN を積む             */
	msr   psp, r0                /* CPU例外ハンドラへの引数となる */
	push  {lr}                   /* MSP上にもEXC_RETURN を積む    */ 
#ifdef TOPPERS_SUPPORT_OVRHDR
    push    {r0}
    bl      ovrtimer_stop
    pop     {r0}
#endif /* TOPPERS_SUPPORT_OVRHDR */
    ldr     r3, =#EXCNO_EMU_TEXRTN
    cpsie   f
    b       core_exc_entry_3
    nop
    /*
     *  ここにはこないはず
     */
ALABEL(error_nomem_texrtn_loop)
    b       error_nomem_texrtn_loop
    nop

    /*
     *  ret_tex，ext_tsk，ext_kerをsvc命令で呼び出す
     */
    ASECTION(.text_shared)
    AALIGN(2)
    ATHUMB(call_ret_tex)
    AGLOBAL(call_ret_tex)
ALABEL(call_ret_tex)
    svc     #NO_RET_TEX
    nop
    mov     r4, #TFN_EXT_TSK
    svc     #NO_SVC
    nop
    mov     r4, #TFN_EXT_KER
    svc     #NO_SVC
    nop


#define ACVCT_ACPTN1 0
#define USTK_disdsp  0

    /*
     *  タスク例外の出口処理
     *  呼び出し時の状態
     *    システムスタック使用中
     */
    ASECTION(.text_kernel)
    AALIGN(2)
    ATHUMB(ret_tex)
    AGLOBAL(ret_tex)
ALABEL(ret_tex)
    /*
	 *  非タスクコンテキストからの呼び出しならばエラー
	 */
	tst     lr, #EXC_RETURN_PSP /* 戻り先がPSPでないか？  */
    bne     ret_tex_0
	bx      lr                  /* 非タスクコンテキストからの呼出しならばリターン */

ALABEL(ret_tex_0)
    /*
     *  呼出し元が特権モードならばエラー
     *  CONTROLをチェックする
     */
    mrs     r0, control
    tst     r0, #0x01
    bne     ret_tex_1
	bx      lr              /* 特権モードからの呼出しならばリターン */
    nop

ALABEL(ret_tex_1)
    /*
     *  r0 = p_runtsk
     */
    ldr     r0, =p_runtsk
    ldr     r0, [r0]
    /*
     *  ユーザスタックの残量をチェック
     *  uspの現在値
     *  特権モード時に使用するサイズ
     *    タスク例外処理でユーザスタックを不正に操作された場合への対応
     */
    ldr     r1, [r0, #TCB_p_tinib]          /* r1 = p_runtsk->tinib */
    ldr     r3, [r1, #TINIB_ustk_bottom]    /* r3 = ユーザスタックの底のアドレス */
    ldr     r4, [r1, #TINIB_ustksz]         /* r4 = ユーザスタックのサイズ */
    subs    r4, r3, r4                      /* r4 = ustk_bottom - ustksz */
    blo     error_nomem_ret_tex             /* r3 < r4 ならばエラー処理へ */
    mrs     r2, psp                         /* r2 = usp */
    cmp     r2, r4                          /* r4 > r2 ならば */
    blo     error_nomem_ret_tex             /* エラー処理へ */
    add     r4, r2, #(EXC_FRAME_SIZE+1*4)   /* r4 = 退避前のusp */
    bvs     error_nomem_texrtn              /* オーバフローしたらエラー処理へ */
    cmp     r3, r4                          /* r3 < r4 ならば */
    blo     error_nomem_texrtn              /* エラー処理へ */
    add     r2, #EXC_FRAME_SIZE             /* スタックを捨てる */
    nop

    /*
     *  この時点で，r2 = 退避後のusp
     */
    str     r2, [r0, #TCB_usp]          /* uspを保存 */
    ldr     r6, [r0, #TCB_ssp]          /* psp = ssp */
    msr     psp, r6
    /* 
     *  p_runtsk->priv_mode = true
     */
    mov     r1, #1
    strb    r1, [r0, #TCB_priv_mode]    
    mov     r1, #0x00
    msr     control, r1

    /*
     *  r3 = rundom
     */
    ldr     r3, =rundom
    ldr     r3, [r3]

    /*
     *  CPUロックを解除
     *  ipmを全解除
     *    タスク例外処理から，CPUロックや割込み優先度マスクを
     *    変更したままリターンした場合への対策
     */
    /*
     *  リターン後のシステム状態をCPUロック解除状態とする
     */
    ldr     r5, =lock_flag
    mov     r1, #0
    str     r1, [r5]
    /*
     *  basepriのセット
     */
    ldr     r5, =#IIPM_ENAALL
    msr     basepri, r5
    /*
     *  ipmflgをtrueにする
     */
    ldr     r5, =ipmflg
    mov     r1, #1
    str     r1, [r5]

ALABEL(ret_tex_2)
    /*
     *  disdspをユーザスタックから復帰
     *    タスク例外処理から，ディスパッチを禁止したまま
     *    リターンした場合への対策
     */
    ldr     r1, =disdsp
    ldr     r4, =sysstat_acvct
    ldr     r4, [r4, #ACVCT_ACPTN1]
    tst     r4, r3                  /* sysstat_acvct.acptn1 & rundom == 0? */
    beq     ret_tex_3
    /*
     *  disdspをユーザスタックから復帰
     */
    ldr     r3, [r2, #USTK_disdsp]
    str     r3, [r1]

ALABEL(ret_tex_3)
    /*
     *  dspflgを更新
     *  割込み優先度マスクは全解除状態のはずなので，
     *  disdspのみで判断すればよい
     *  タスク例外処理でCPUロックや割込み優先度マスク
     *  がセットされた場合にもdspflgは変化するため，
     *  dspflgを更新する必要があるのは，disdspを戻す
     *  場合だけでない
     */
    ldr     r3, [r1]
    eor     r3, r3, #1
    ldr     r1, =dspflg
    str     r3, [r1]

    /*
     *  p_runtsk->enatex = false
     */
    ldrb    r1, [r0, #TCB_enatex]
    bfc     r1, #TCB_enatex_bit, #1
    strb    r1, [r0, #TCB_enatex]

    /*
     *  dspflgがtrueか？
     */
    ldr     r3, =dspflg
    ldr     r3, [r3]
    tst     r3, r3      /* dspflg == false? */
    beq     ret_tex_r_1 /* falseならディスパッチしない */
    /*
     *  p_runtsk != p_schedtsk か？
     */
	ldr     r3, =p_schedtsk     /* r3 <- schedtsk */
	ldr     r3, [r3]
	cmp     r0, r3              /* runtsk と schedtsk を比較 */
	beq     ret_tex_r_1         /* 同じならディスパッチしない */
    /*
     *  CPUロック状態へ
     */
    /*
     *  basepriのセット
     *  カーネル管理の割込みを禁止
     */
    ldr     r3, =#IIPM_LOCK
    msr     basepri, r3

    ldr     r4, =lock_flag
    mov     r1, #0
    str     r1, [r4]

    ldr     r4, =saved_iipm
    ldr     r1, =#IIPM_ENAALL
    str     r1, [r4]

	ldr     r5, =EPSR_T                 /* xPSR(Tビットが'1'である必要がある) */
    ldr     r4, =ret_tex_4
    stmfd   r6!, {r4-r5}
    sub     r6, r6, #(EXC_FRAME_SIZE - (2*4))
    msr     psp, r6
    bx      lr

ALABEL(ret_tex_4)
    /*
     *  dispatchへ
     */
    bl      dispatch
    nop
    svc     #NO_RET_TEX_R     
    nop

    ATHUMB(ret_tex_r)
    AGLOBAL(ret_tex_r)
ALABEL(ret_tex_r)
    mrs     r6, psp
    add     r6, r6, #EXC_FRAME_SIZE
    msr     psp, r6
    /*
     *  リターン後のシステム状態をCPUロック解除状態とする
     */
    ldr     r1, =lock_flag
    mov     r0, #0
    str     r0, [r1]
    /*
     *  basepriのセット
     */
    ldr     r3, =#IIPM_ENAALL
    msr     basepri, r3

ALABEL(ret_tex_r_1)
    /*
	 *  保留例外要因があるかチェック
	 */
    ldr     r0, =p_runtsk
    ldr     r0, [r0]
	ldr     r2, [r0, #TCB_usp]          /* uspの読出し */
	ldr     r3, [r0, #TCB_texptn]       /* 保留例外要因の読出し */
    tst     r3, r3                      /* 0でなければtexrtnを再実行 */
    itt     ne
    ldrne   r1, [r0, #TCB_p_tinib]      /* r1 = p_runtsk->tinib */
    bne     prepare_texrtn_utask_r      /* 0でなければtexrtnを再実行 */
    nop

    add     r2, r2, #1*4        /* r2(usp)から捨てる */
    str     r2, [r0, #TCB_usp]  /* uspを戻す */

    /*
     *  p_runtsk->enatex = true
     */
    ldrb    r1, [r0, #TCB_enatex]   /* タスク例外処理許可状態の読出し */
    mov     r2, #TCB_enatex_mask
    orr     r1, r1, r2
    strb    r1, [r0, #TCB_enatex]

    pop     {r4-r6}                 /* prepare_texrtnの先頭で保存したレジスタを復帰 */
    bx      lr                      /* prepare_texrtnの呼出し元へリターン */
    nop

/*
 *  タスク例外リターン時スタック不正例外ハンドラを呼び出す
 */
ALABEL(error_nomem_ret_tex)
    /*
     *  エミュレートされたCPU例外を呼ぶ
     *  例外からのリターンでret_texの呼び出し元に戻る
     *  TODO: 例外からリターンした場合の動作は不定
     */
	mrs   r0, psp                /* 一段目の割込みの場合はPSP上に */
	mrs   r2, basepri             /* baepriの値を取得 */
	stmfd r0!,{r2}               /* 割込み発生時の割込み優先度マスクを積む */
	stmfd r0!,{lr}               /* EXC_RETURN を積む             */
	msr   psp, r0                /* CPU例外ハンドラへの引数となる */
	push  {lr}                   /* MSP上にもEXC_RETURN を積む    */ 
#ifdef TOPPERS_SUPPORT_OVRHDR
    push    {r0}
    bl      ovrtimer_stop
    pop     {r0}
#endif /* TOPPERS_SUPPORT_OVRHDR */
    ldr     r3, =#EXCNO_EMU_RET_TEX
    cpsie   f
    b       core_exc_entry_3
    nop
    /*
     *  ここにはこないはず
     */
ALABEL(error_nomem_ret_tex_loop)
    b     error_nomem_ret_tex_loop
    nop

/*
 *  微少時間待ち
 */
	AALIGN(2)
	ATEXT
	ATHUMB(sil_dly_nse)
	AGLOBAL(sil_dly_nse)
ALABEL(sil_dly_nse)
	sub   r0, r0, #SIL_DLY_TIM1
	cmp   r0, #0
	bgt   sil_dly_nse1
	bx    lr
ALABEL(sil_dly_nse1)
	sub   r0, r0, #SIL_DLY_TIM2
	cmp   r0, #0
	bgt   sil_dly_nse1
	bx    lr

