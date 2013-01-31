$ ======================================================================
$
$   TOPPERS/HRP Kernel
$       Toyohashi Open Platform for Embedded Real-Time Systems/
$       High Reliable system Profile Kernel
$
$   Copyright (C) 2012 by Embedded and Real-Time Systems Laboratory
$               Graduate School of Information Science, Nagoya Univ., JAPAN
$  
$   上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
$   ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
$   変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
$   (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
$       権表示，この利用条件および下記の無保証規定が，そのままの形でソー
$       スコード中に含まれていること．
$   (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
$       用できる形で再配布する場合には，再配布に伴うドキュメント（利用
$       者マニュアルなど）に，上記の著作権表示，この利用条件および下記
$       の無保証規定を掲載すること．
$   (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
$       用できない形で再配布する場合には，次のいずれかの条件を満たすこ
$       と．
$     (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
$         作権表示，この利用条件および下記の無保証規定を掲載すること．
$     (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
$         報告すること．
$   (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
$       害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
$       また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
$       由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
$       免責すること．
$  
$   本ソフトウェアは，無保証で提供されているものである．上記著作権者お
$   よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
$   に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
$   アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
$   の責任を負わない．
$
$  
$ =====================================================================

$ 
$  パス4のプロセッサ依存テンプレート（ARM-M用）
$  core_check.tfより
$  
$FUNCTION GET_SSTK_TSKINICTXB$
    $bottom = PEEK(ARGV[1] + offsetof_TINIB_TSKINICTXB_sstk_bottom, sizeof_void_ptr)$
    $size = PEEK(ARGV[1] + offsetof_TINIB_TSKINICTXB_sstksz, sizeof_SIZE)$
    $RESULT = (bottom - size)$
$END$

$FUNCTION GET_USTK_TSKINICTXB$
    $bottom = PEEK(ARGV[1] + offsetof_TINIB_TSKINICTXB_stk_bottom, sizeof_void_ptr)$
    $size = PEEK(ARGV[1] + offsetof_TINIB_TSKINICTXB_stksz, sizeof_SIZE)$
    $RESULT = (bottom - size)$
$END$

$
$  保護ドメインのラベルの作成
$	DOM.LABEL[domid]：保護ドメインのラベル
$
$DOM.LABEL[TDOM_KERNEL] = "kernel"$
$FOREACH domid DOM.ID_LIST$
	$DOM.LABEL[domid] = domid$
$END$
$DOM.LABEL[TDOM_NONE] = "shared"$

$ 
$  保護ドメイン毎のデフォルトのアクセス許可パターンの作成
$ 
$DEFAULT_ACPTN[TDOM_KERNEL] = VALUE("TACP_KERNEL", TACP_KERNEL)$
$FOREACH domid DOM.ID_LIST$
	$DEFAULT_ACPTN[domid] = VALUE(FORMAT("TACP(%1%)", domid), 1 << (domid - 1))$
$END$
$DEFAULT_ACPTN[TDOM_NONE] = VALUE("TACP_SHARED", TACP_SHARED)$


$ $OMIT_STANDARD_MEMINIB = 1$
$ $MO_MEMTOP_LIST = MO_MEMTOP_REAL_ORDER$

$INCLUDE "kernel/kernel_mem.tf"$

$ 
$  共有領域の初期化ブロックと保護ドメイン初期化ブロックのmem依存部を生成
$ 

$FILE "kernel_mem.c"$

$ 
$ 保護ドメイン初期化コンテキストブロックのための宣言
$ 
$FUNCTION PREPARE_DOMINICTXB$
    $IF LENGTH(DOM.ID_LIST)$
        $FOREACH domid DOM.ID_LIST$
$   RX領域（専用）
            extern char __start_text_$DOM.LABEL[domid]$;$NL$
            extern char __limit_text_$DOM.LABEL[domid]$;$NL$
$   R領域（専用）
            extern char __start_rodata_$DOM.LABEL[domid]$;$NL$
            extern char __limit_rodata_$DOM.LABEL[domid]$;$NL$
$   RWX領域（専用）
            extern char __start_ram_$DOM.LABEL[domid]$;$NL$
            extern char __limit_ram_$DOM.LABEL[domid]$;$NL$
$   共有リード専用ライト
            extern char $FORMAT("__start_ram_%s_%x_%x", DOM.LABEL[domid], +DEFAULT_ACPTN[domid], +TACP_SHARED)$;$NL$
            extern char $FORMAT("__limit_ram_%s_%x_%x", DOM.LABEL[domid], +DEFAULT_ACPTN[domid], +TACP_SHARED)$;$NL$
        $END$
        $NL$
    $END$$NL$

$  共有領域
    extern char __start_text_$DOM.LABEL[TDOM_NONE]$;$NL$
    extern char __limit_text_$DOM.LABEL[TDOM_NONE]$;$NL$
    extern char __start_rodata_$DOM.LABEL[TDOM_NONE]$;$NL$
    extern char __limit_rodata_$DOM.LABEL[TDOM_NONE]$;$NL$
    extern char __start_ram_$DOM.LABEL[TDOM_NONE]$;$NL$
    extern char __limit_ram_$DOM.LABEL[TDOM_NONE]$;$NL$
$   共有リード専用ライト領域全体
    extern char __start_srpw_all;$NL$
    extern char __limit_srpw_all;$NL$
    $NL$
	extern const DOMINIB_INFO _kernel_dominib_info_tbl[];$NL$
$END$

$PREPARE_DOMINICTXB()$

$IF LENGTH(DOM.ID_LIST) > 0$
    const DOMINIB_INFO _kernel_dominib_info_tbl[TNUM_DOMID] ={$NL$
    $dominib_info = SYMBOL("_kernel_dominib_info_tbl")$
    $JOINEACH domid DOM.ID_LIST ",\n"$
        $TAB${$NL$
$   RX領域（専用）
        $base = PEEK(dominib_info, 4)$
        $attr = PEEK(dominib_info + 4, 4)$
        $TAB$$TAB$$FORMAT("( (char *)0x%x )", base)$, /* region 4 : __start_text_$DOM.LABEL[domid]$ */$NL$
        $TAB$$TAB$$FORMAT("( 0x%x )", attr)$,$NL$
$   RWX領域（専用）
        $base = PEEK(dominib_info + 8, 4)$
        $attr = PEEK(dominib_info + 12, 4)$
        $TAB$$TAB$$FORMAT("( (char *)0x%x )", base)$, /* region 5 : __start_ram_$DOM.LABEL[domid]$ */$NL$
        $TAB$$TAB$$FORMAT("( 0x%x )", attr)$,$NL$
$   共有リード専用ライト
        $base = PEEK(dominib_info + 16, 4)$
        $attr = PEEK(dominib_info + 20, 4)$
        $TAB$$TAB$$FORMAT("( (char *)0x%x )", base)$, /* region 6 : $FORMAT("__start_ram_%s_%x_%x", DOM.LABEL[domid], +DEFAULT_ACPTN[domid], +TACP_SHARED)$ */$NL$
        $TAB$$TAB$$FORMAT("( 0x%x )", attr)$,$NL$
$   共有リード専用ライト
        $base = PEEK(dominib_info + 24, 4)$
        $attr = PEEK(dominib_info + 28, 4)$
        $TAB$$TAB$$FORMAT("( (char *)0x%x )", base)$, /* region 7 : ATT_MEM  */$NL$
        $TAB$$TAB$$FORMAT("( 0x%x )", attr)$,$NL$
        $TAB$}
        $dominib_info = dominib_info + 32$
    $END$
    ,$NL$};$NL$
    $NL$
$END$

$TNUM_SHARED_REGION = 3$
const uint_t tnum_shared_mem = $TNUM_SHARED_REGION * 2$;$NL$
char * const shared_meminib_table[$TNUM_SHARED_REGION * 2$] = {$NL$
    $shared_info = SYMBOL("shared_meminib_table")$
    $base = PEEK(shared_info, 4)$
    $attr = PEEK(shared_info + 4, 4)$
    $TAB$$TAB$$FORMAT("( (char *)0x%x )", base)$, /* region 0 : __start_text_$DOM.LABEL[TDOM_NONE]$ */$NL$
    $TAB$$TAB$$FORMAT("( (char *)0x%x )", attr)$,$NL$
    $base = PEEK(shared_info + 8, 4)$
    $attr = PEEK(shared_info + 12, 4)$
    $TAB$$TAB$$FORMAT("( (char *)0x%x )", base)$, /* region 1 : __start_ram_$DOM.LABEL[TDOM_NONE]$ */$NL$
    $TAB$$TAB$$FORMAT("( (char *)0x%x )", attr)$,$NL$
    $base = PEEK(shared_info + 16, 4)$
    $attr = PEEK(shared_info + 20, 4)$
    $TAB$$TAB$$FORMAT("( (char *)0x%x )", base)$, /* region 2 : __start_srpw_all */$NL$
    $TAB$$TAB$$FORMAT("( (char *)0x%x )", attr)$,$NL$
};$NL$
$NL$


