$ ======================================================================
$
$   TOPPERS/HRP Kernel
$       Toyohashi Open Platform for Embedded Real-Time Systems/
$       High Reliable system Profile Kernel
$
$   Copyright (C) 2012 by Embedded and Real-Time Systems Laboratory
$               Graduate School of Information Science, Nagoya Univ., JAPAN
$  
$   �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
$   �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
$   �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
$   (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
$       ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
$       ����������˴ޤޤ�Ƥ��뤳�ȡ�
$   (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
$       �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
$       �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
$       ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
$   (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
$       �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
$       �ȡ�
$     (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
$         �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
$     (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
$         ��𤹤뤳�ȡ�
$   (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
$       ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
$       �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
$       ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
$       ���դ��뤳�ȡ�
$  
$   �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
$   ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
$   ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
$   �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
$   ����Ǥ�����ʤ���
$
$  
$ =====================================================================

$ 
$  �ѥ�4�Υץ��å���¸�ƥ�ץ졼�ȡ�ARM-M�ѡ�
$  core_check.tf���
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
$  �ݸ�ɥᥤ��Υ�٥�κ���
$	DOM.LABEL[domid]���ݸ�ɥᥤ��Υ�٥�
$
$DOM.LABEL[TDOM_KERNEL] = "kernel"$
$FOREACH domid DOM.ID_LIST$
	$DOM.LABEL[domid] = domid$
$END$
$DOM.LABEL[TDOM_NONE] = "shared"$

$ 
$  �ݸ�ɥᥤ����Υǥե���ȤΥ����������ĥѥ�����κ���
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
$  ��ͭ�ΰ�ν�����֥�å����ݸ�ɥᥤ�������֥�å���mem��¸��������
$ 

$FILE "kernel_mem.c"$

$ 
$ �ݸ�ɥᥤ����������ƥ����ȥ֥�å��Τ�������
$ 
$FUNCTION PREPARE_DOMINICTXB$
    $IF LENGTH(DOM.ID_LIST)$
        $FOREACH domid DOM.ID_LIST$
$   RX�ΰ�����ѡ�
            extern char __start_text_$DOM.LABEL[domid]$;$NL$
            extern char __limit_text_$DOM.LABEL[domid]$;$NL$
$   R�ΰ�����ѡ�
            extern char __start_rodata_$DOM.LABEL[domid]$;$NL$
            extern char __limit_rodata_$DOM.LABEL[domid]$;$NL$
$   RWX�ΰ�����ѡ�
            extern char __start_ram_$DOM.LABEL[domid]$;$NL$
            extern char __limit_ram_$DOM.LABEL[domid]$;$NL$
$   ��ͭ�꡼�����ѥ饤��
            extern char $FORMAT("__start_ram_%s_%x_%x", DOM.LABEL[domid], +DEFAULT_ACPTN[domid], +TACP_SHARED)$;$NL$
            extern char $FORMAT("__limit_ram_%s_%x_%x", DOM.LABEL[domid], +DEFAULT_ACPTN[domid], +TACP_SHARED)$;$NL$
        $END$
        $NL$
    $END$$NL$

$  ��ͭ�ΰ�
    extern char __start_text_$DOM.LABEL[TDOM_NONE]$;$NL$
    extern char __limit_text_$DOM.LABEL[TDOM_NONE]$;$NL$
    extern char __start_rodata_$DOM.LABEL[TDOM_NONE]$;$NL$
    extern char __limit_rodata_$DOM.LABEL[TDOM_NONE]$;$NL$
    extern char __start_ram_$DOM.LABEL[TDOM_NONE]$;$NL$
    extern char __limit_ram_$DOM.LABEL[TDOM_NONE]$;$NL$
$   ��ͭ�꡼�����ѥ饤���ΰ�����
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
$   RX�ΰ�����ѡ�
        $base = PEEK(dominib_info, 4)$
        $attr = PEEK(dominib_info + 4, 4)$
        $TAB$$TAB$$FORMAT("( (char *)0x%x )", base)$, /* region 4 : __start_text_$DOM.LABEL[domid]$ */$NL$
        $TAB$$TAB$$FORMAT("( 0x%x )", attr)$,$NL$
$   RWX�ΰ�����ѡ�
        $base = PEEK(dominib_info + 8, 4)$
        $attr = PEEK(dominib_info + 12, 4)$
        $TAB$$TAB$$FORMAT("( (char *)0x%x )", base)$, /* region 5 : __start_ram_$DOM.LABEL[domid]$ */$NL$
        $TAB$$TAB$$FORMAT("( 0x%x )", attr)$,$NL$
$   ��ͭ�꡼�����ѥ饤��
        $base = PEEK(dominib_info + 16, 4)$
        $attr = PEEK(dominib_info + 20, 4)$
        $TAB$$TAB$$FORMAT("( (char *)0x%x )", base)$, /* region 6 : $FORMAT("__start_ram_%s_%x_%x", DOM.LABEL[domid], +DEFAULT_ACPTN[domid], +TACP_SHARED)$ */$NL$
        $TAB$$TAB$$FORMAT("( 0x%x )", attr)$,$NL$
$   ��ͭ�꡼�����ѥ饤��
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


