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

$INCLUDE "cfg2_out.tf"$

$ 
$  arch/arm_m_gcc/common/ldscript.tfのターゲット依存部
$ 
$FUNCTION GENERATE_MEMORY$
    $NOOP()$
$END$


$FUNCTION GENERATE_OUTPUT$
    OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm","elf32-littlearm")$NL$
    OUTPUT_ARCH(arm)$NL$
    STARTUP(start.o)$NL$
    $IF TOPPERS_RAM_DEBUG$
        ENTRY(_start)$NL$
    $END$
    $NL$
$END$

$ 
$  カーネルが管理しないセクションを出力する
$  ターゲット依存で必要なセクション
$ 
$FUNCTION GENERATE_SECTION_FIRST$
    $TAB$.startup : {$NL$
    $IF TOPPERS_RAM_DEBUG$
        $TAB$$TAB$KEEP(*(.vector))$NL$
    $ELSE$
        $TAB$$TAB$*(.vector)$NL$
    $END$
    $TAB$$TAB$start.o(.text_kernel)$NL$
    $TAB$$TAB$start.o(*.text*)$NL$
    $IF TOPPERS_RAM_DEBUG$
        $TAB$} > $REG.REGNAME[STANDARD_RAM]$$NL$
    $ELSE$
        $TAB$} > $REG.REGNAME[STANDARD_ROM]$$NL$
    $END$
    $NL$
	$TAB$.ARM.extab : { *(.ARM.extab* .gnu.linkonce.armextab.*) }$NL$
	$TAB$__exidx_start = .;$NL$
	$TAB$.ARM.exidx : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) }$NL$
	$TAB$__exidx_end = .;$NL$
$END$

$ 
$  ページサイズとアラインメントの制約
$ 
$TARGET_PAGE_SIZE_STR = 1024$
$TARGET_SEC_ALIGN_STR = 1024$

$
$  リンカのためのセクション記述の生成
$
$FUNCTION SECTION_DESCRIPTION$
	$IF EQ(ARGV[1], ".rodata")$
		$RESULT = "*.rodata *.rodata.* .rodata.str1.4"$
	$ELIF EQ(ARGV[1], ".bss")$
		$RESULT = "*.bss *.bss.* COMMON"$
	$ELIF EQ(ARGV[1], ".text")$
		$RESULT = "*.text *.text.* .glue_7t .glue_7"$
	$ELIF EQ(ARGV[1], ".data")$
		$RESULT = "*.data *.data.*"$
	$ELSE$
		$RESULT = ARGV[1]$
	$END$
$END$

$INCLUDE "arm_m_gcc/common/core_opt.tf"$

