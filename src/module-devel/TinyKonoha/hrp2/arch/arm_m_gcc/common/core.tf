$ ======================================================================
$
$   TOPPERS/HRP Kernel
$       Toyohashi Open Platform for Embedded Real-Time Systems/
$       High Reliable system Profile Kernel
$
$   Copyright (C) 2011-2012 by Embedded and Real-Time Systems Laboratory
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
$ =====================================================================

$ 
$     �ѥ�2�Υ������ƥ������¸�ƥ�ץ졼�ȡ�ARM-M�ѡ�
$ 

$ 
$  ͭ���ʳ�����ֹ桤����ߥϥ�ɥ��ֹ�
$ 
$INTNO_VALID = RANGE(15, TMAX_INTNO)$
$INHNO_VALID = INTNO_VALID$

$ 
$  ͭ����CPU�㳰�ֹ�
$  7,8�ϥ��ߥ�졼�Ȥ��줿�㳰
$ 
$EXCNO_VALID = { 2,3,4,5,6,7,8,11,12,14 }$

$ 
$  ATT_ISR�ǻ��ѤǤ��������ֹ�Ȥ�����б��������ߥϥ�ɥ��ֹ�
$ 
$INTNO_ATTISR_VALID = INTNO_VALID$
$INHNO_ATTISR_VALID = INHNO_VALID$

$ 
$  DEF_INT��DEF_EXC�ǻ��ѤǤ������ߥϥ�ɥ��ֹ桿CPU�㳰�ϥ�ɥ��ֹ�
$ 
$INHNO_DEFINH_VALID = INHNO_VALID$
$EXCNO_DEFEXC_VALID = EXCNO_VALID$

$ 
$  CFG_INT�ǻ��ѤǤ��������ֹ�ȳ����ͥ����
$  ����ͥ���٤�BASEPRI�쥸�����ǥޥ����Ǥ��ʤ�ͥ���١�����ͥ����'0'��
$  ���Τ��ᡤ�����ͥ�������γ���ߤǤΤ߻����ǽ��
$INTNO_CFGINT_VALID = INTNO_VALID$
$INTPRI_CFGINT_VALID = RANGE(-(1 << TBITW_IPRI),-1)$
           
$ 
$  kernel/kernel.tf �Υ������åȰ�¸��
$ 

$ 
$  �桼�������å��ΰ����ݤ��륳���ɤ���Ϥ���
$  ARGV[1]��������ID
$  ARGV[2]�������å�������
$ 
$FUNCTION ALLOC_USTACK$
    static STK_T _kernel_ustack_$ARGV[1]$[COUNT_STK_T($ARGV[2]$)]
    $SPC$__attribute__((section($FORMAT("\".user_stack.%s\"", ARGV[1])$)));$NL$

    $TSK.TINIB_USTKSZ[ARGV[1]] = VALUE(FORMAT("ROUND_STK_T(%s)", ARGV[2]), +ARGV[2])$
    $TSK.TINIB_USTK[ARGV[1]] = FORMAT("_kernel_ustack_%s", ARGV[1])$
$END$

$ 
$  �桼�������å��ΰ�Υ��������̾���֤�
$  ARGV[1]��������ID
$ 
$FUNCTION SECTION_USTACK$
    $RESULT = FORMAT(".user_stack.%s", ARGV[1])$
$END$

$ 
$  arch/gcc/ldscript.tf�Υ������åȰ�¸��
$ 

$FUNCTION GENERATE_PROVIDE$
    PROVIDE(hardware_init_hook = 0);$NL$
    PROVIDE(software_init_hook = 0);$NL$
    PROVIDE(software_term_hook = 0);$NL$
    PROVIDE(_kernel_bsssecinib_table = 0);$NL$
    PROVIDE(_kernel_tnum_bsssec = 0);$NL$
    PROVIDE(_kernel_datasecinib_table = 0);$NL$
    PROVIDE(_kernel_tnum_datasec = 0);$NL$
    $NL$

    $IF LENGTH(DOM.ID_LIST)$
        $FOREACH domid DOM.ID_LIST$
$   RX�ΰ�����ѡ�
            PROVIDE(__start_text_$DOM.LABEL[domid]$ = 0xffffffff);$NL$
            PROVIDE(__limit_text_$DOM.LABEL[domid]$ = 0xffffffff);$NL$
$   R�ΰ�����ѡ�
            PROVIDE(__start_rodata_$DOM.LABEL[domid]$ = 0xffffffff);$NL$
            PROVIDE(__limit_rodata_$DOM.LABEL[domid]$ = 0xffffffff);$NL$
$   RWX�ΰ�����ѡ�
            PROVIDE(__start_ram_$DOM.LABEL[domid]$ = 0xffffffff);$NL$
            PROVIDE(__limit_ram_$DOM.LABEL[domid]$ = 0xffffffff);$NL$
$   ��ͭ�꡼�����ѥ饤��
            PROVIDE($FORMAT("__start_ram_%s_%x_%x", DOM.LABEL[domid], +DEFAULT_ACPTN[domid], +TACP_SHARED)$ = 0xffffffff);$NL$
            PROVIDE($FORMAT("__limit_ram_%s_%x_%x", DOM.LABEL[domid], +DEFAULT_ACPTN[domid], +TACP_SHARED)$ = 0xffffffff);$NL$
        $END$
        $NL$
    $END$$NL$

$  ��ͭ�ΰ�
    PROVIDE(__start_text_$DOM.LABEL[TDOM_NONE]$ = 0xffffffff);$NL$
    PROVIDE(__limit_text_$DOM.LABEL[TDOM_NONE]$ = 0xffffffff);$NL$
    PROVIDE(__start_rodata_$DOM.LABEL[TDOM_NONE]$ = 0xffffffff);$NL$
    PROVIDE(__limit_rodata_$DOM.LABEL[TDOM_NONE]$ = 0xffffffff);$NL$
    PROVIDE(__start_ram_$DOM.LABEL[TDOM_NONE]$ = 0xffffffff);$NL$
    PROVIDE(__limit_ram_$DOM.LABEL[TDOM_NONE]$ = 0xffffffff);$NL$
$   ��ͭ�꡼�����ѥ饤���ΰ�����
    PROVIDE(__start_srpw_all = 0xffffffff);$NL$
    PROVIDE(__limit_srpw_all = 0xffffffff);$NL$
    $NL$
$END$

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

$ 
$  DOMINICTXB�ν�������������
$ 
$DOMINICTXB_KERNEL = "{ NULL }"$

$FUNCTION GENERATE_DOMINICTXB$
	{ (DOMINIB_INFO *)&_kernel_dominib_info_tbl[$ARGV[1]$ - 1] }
$END$

$region_size = 32$
$region_size_mask = 0x04$
$WHILE (region_size <= (4*1024*1024*1024))$
    $hash_region_size_mask[region_size] = (region_size_mask << 1)$
    $region_size = region_size * 2$
    $region_size_mask = region_size_mask + 1$
$END$

$ 
$  TSKINICTXB�ν�������������
$ 
$FUNCTION GENERATE_TSKINICTXB$
	$SPC${
    $SPC$$TSK.TINIB_SSTKSZ[ARGV[1]]$, 
	$SPC$((void *)((char *)($TSK.TINIB_SSTK[ARGV[1]]$)
    $SPC$+ ($TSK.TINIB_SSTKSZ[ARGV[1]]$))),
    $IF (TSK.DOMAIN[ARGV[1]] == TDOM_KERNEL)$
        $SPC$0, 0, 0, 0 },
    $ELSE$
        $SPC$$TSK.TINIB_USTKSZ[ARGV[1]]$, 
        $SPC$((void *)((char *)($TSK.TINIB_USTK[ARGV[1]]$)
        $SPC$+ ($TSK.TINIB_USTKSZ[ARGV[1]]$))),
        $SPC$((char *)$TSK.TINIB_USTK[ARGV[1]]$ + 0x10 + 0x03 ),
        $SPC$( TO_MPU_AP( MPU_AP_PURW ) | MPU_REGATR_C | MPU_REGATR_B | $hash_region_size_mask[TSK.STKSZ[ARGV[1]]]$ | MPU_REGATR_ENABLE ),$SPC$
        $SPC$},
    $END$
$END$

$ 
$  �����ݸ�ñ�̤μºݤΥ������������ꡤ������ä�����������
$  ARM MPU�Υ�������������������ɤ������֤�
$  
$FUNCTION CHECK_ARM_MPU_SIZE$
    $search_state = 0$
    $FOREACH bit_offset { 31,30,...,5 }$
        $compare_bit = 1 << bit_offset$
        $IF ((ARGV[1] & compare_bit) != 0)$
            $IF (search_state == 0)$
                $RESULT = 1$
                $search_state = 1$
            $ELIF (search_state == 1)$
                $RESULT = 0$
                $search_state = 2$
            $END$
        $END$
    $END$
    $IF (search_state == 0)$
        $RESULT = 0$
    $ELIF (search_state == 1) && ((ARGV[1] & 0x1f) != 0)$
        $RESULT = 0$
    $END$
$END$

$ 
$  ATT_MEM�Υ������åȰ�¸��
$  ATTMEM_LIST: ATT_MEM����Ͽ���줿MEM�Υꥹ��
$  DOM.MEM_COUNT[domid]: �ݸ�ɥᥤ���°����MEM�ο�
$                       1�ݸ�ɥᥤ�󤢤����1�Ĥ�MEM�Τ�°���뤳�Ȥ��Ǥ���
$                       1�Ĥ�MEM����ͭ�Ǥ��ä����ˤϡ�¾��MEM����Ͽ�Ǥ��ʤ�
$  SHARED_MEM_COUNT: ��ͭ��MEM�ο�
$  ALL_MEM_COUNT: MEM�ο�
$  DOM.MEM_BASE[domid]: �ݸ�ɥᥤ���°����MEM����Ƭ����
$  DOM.MEM_SIZE[domid]: �ݸ�ɥᥤ���°����MEM�Υ�����
$ATTMEM_LIST = {}$
$ALL_MEM_COUNT = 0$
$SHARED_MEM_COUNT = 0$
$FOREACH domid DOM.ID_LIST$
    $DOM.MEM_COUNT[domid] = 0$
    $DOM.MEM_BASE[domid] = 0$
    $DOM.MEM_SIZE[domid] = 0$
$END$
$FUNCTION HOOK_ERRORCHECK_MEM$
    $memid = ARGV[1]$
    $IF !CHECK_ARM_MPU_SIZE(MEM.SIZE[memid])$
        $ERROR$$FORMAT("size of MEM(base:%1%, size:%2%) does not meet MPU constraints.", MEM.BASE[memid], MEM.SIZE[memid])$$END$
    $END$

    $IF EQ(MEM.DOMAIN[memid], "")$
$       // ��ͭ�ξ��
        $IF ALL_MEM_COUNT > 0$
            $ERROR$$FORMAT("ATT_MEM is too much.")$$END$
        $ELSE$
            $SHARED_MEM_COUNT = SHARED_MEM_COUNT + 1$
            $ATTMEM_LIST = APPEND(ATTMEM_LIST, memid)$

            $FOREACH domid DOM.ID_LIST$
                $DOM.MEM_BASE[domid] = MEM.BASE[memid]$
                $DOM.MEM_SIZE[domid] = MEM.SIZE[memid]$
            $END$
        $END$
    $ELIF SHARED_MEM_COUNT == 0$
$       // ��ͭ��MEM��¸�ߤ������ݸ�ɥᥤ���°������
        $IF DOM.MEM_COUNT[MEM.DOMAIN[memid]] > 0$
            $ERROR$$FORMAT("ATT_MEM is too much in DOMAIN(%1%).", MEM.DOMAIN[memid])$$END$
        $ELSE$
            $DOM.MEM_COUNT[MEM.DOMAIN[memid]] = DOM.MEM_COUNT[MEM.DOMAIN[memid]] + 1$
            $ATTMEM_LIST = APPEND(ATTMEM_LIST, memid)$

            $DOM.MEM_BASE[MEM.DOMAIN[memid]] = MEM.BASE[memid]$
            $DOM.MEM_SIZE[MEM.DOMAIN[memid]] = MEM.SIZE[memid]$
        $END$
    $ELSE$
        $ERROR$$FORMAT("ATT_MEM is too much.")$$END$
    $END$
    $ALL_MEM_COUNT = ALL_MEM_COUNT + 1$
$END$

$ 
$  ɸ��ƥ�ץ졼�ȥե�����Υ��󥯥롼��
$ 
$INCLUDE "kernel/kernel.tf"$

$ 
$  �桼�������å��Υ����������å�
$ 
$FOREACH tskid TSK.ID_LIST$
    $IF (TSK.DOMAIN[tskid] != TDOM_KERNEL) && !CHECK_ARM_MPU_SIZE(TSK.STKSZ[tskid])$
        $ERROR$$FORMAT("the user stack of TASK(%1%) does not meet MPU size constraints. size=%2%", tskid, +TSK.STKSZ[tskid])$$END$
    $END$
$END$

/*$NL$
$SPC$*  Target-dependent Definitions (ARM-M)$NL$
$SPC$*/$NL$
$NL$

$ 
$  �٥������ơ��֥�
$ 
$FILE "kernel_cfg.c"$
$NL$
__attribute__ ((section(".vector"))) $NL$
const FP _kernel_vector_table[] =      $NL$ 
{                                    $NL$
	$TAB$(FP)(TOPPERS_ISTKPT(TOPPERS_ISTK, TOPPERS_ISTKSZ)),   // 0 The initial stack pointer $NL$
	$TAB$(FP)_start,                 // 1 The reset handler         $NL$

$FOREACH excno {2,3,...,14}$ 
	$IF excno == 11$
		$TAB$(FP)(_kernel_svc_handler),      // 11 SVCall handler
	$ELSE$
		$TAB$(FP)(_kernel_core_exc_entry),
	$END$
	$SPC$$FORMAT("/* %d */", +excno)$$NL$
$END$

$FOREACH inhno INTNO_VALID$ 
	$IF LENGTH(INH.INHNO[inhno]) && ((INH.INHATR[inhno] & TA_NONKERNEL) != 0)$
		$TAB$(FP)($INH.INTHDR[inhno]$),
	$ELSE$
		$TAB$(FP)(_kernel_core_int_entry),
	$END$
	$SPC$$FORMAT("/* %d */", +inhno)$$NL$
$END$


$NL$};$NL$
$NL$

$NL$
const FP _kernel_exc_tbl[] = $NL$
{$NL$
$FOREACH excno {0,1,...,14}$
	$IF LENGTH(EXC.EXCNO[excno])$
		$TAB$(FP)($EXC.EXCHDR[excno]$),
	$ELSE$
		$TAB$(FP)(_kernel_default_exc_handler),
	$END$
	$SPC$$FORMAT("/* %d */", +excno)$$NL$
$END$


$FOREACH inhno INTNO_VALID$
	$IF LENGTH(INH.INHNO[inhno])$
		$TAB$(FP)($INH.INTHDR[inhno]$),
	$ELSE$
		$TAB$(FP)(_kernel_default_int_handler),
	$END$
	$SPC$$FORMAT("/* %d */", +inhno)$$NL$
$END$


$NL$};$NL$
$NL$

$ 
$  _kernel_bitpat_cfgint������
$ 

$bitpat_cfgint_num = 0$
$bitpat_cfgint = 0$


const uint32_t _kernel_bitpat_cfgint[
$IF (TMAX_INTNO & 0x0f) == 0x00 $
	$bitpat_cfgint_num = (TMAX_INTNO >> 4)$
$ELSE$
	$bitpat_cfgint_num = (TMAX_INTNO >> 4) + 1$
$END$
	$bitpat_cfgint_num$
] = {$NL$
$FOREACH num RANGE(0,(bitpat_cfgint_num-1))$
$   //boost �ΥС������ˤ�äƵ�ư���Ѥ�뤿����к�
$   //http://www.toppers.jp/TOPPERS-USERS/201004/msg00034.html
	$bitpat_cfgint = 1-1$
	$FOREACH inhno RANGE(num*32, (num*32)+31)$
		$IF LENGTH(INH.INHNO[inhno])$
			$bitpat_cfgint = bitpat_cfgint | (1 << (inhno & 0x01f))$
		$END$
	$END$
	$TAB$UINT32_C($FORMAT("0x%08x", bitpat_cfgint)$), $NL$
$END$

$NL$};$NL$
$NL$


$ 
$  �����ͥ���٥ơ��֥������ɽ����
$ 
const uint32_t _kernel_int_iipm_tbl[] = {$NL$
$FOREACH excno {0,1,...,14}$
	$TAB$$FORMAT("UINT32_C(0x%08x), /* 0x%03x */", 0, +excno)$$NL$
$END$

$FOREACH intno INTNO_VALID$
	$IF LENGTH(INT.INTNO[intno])$
		$intpri = (((1 << TBITW_IPRI) + INT.INTPRI[intno]) << (8 - TBITW_IPRI))$
	$ELSE$
$		// LSB��1�ˤ��Ƥ���Τϡ������°�������ꤵ��Ƥ��ʤ����Ȥ�Ƚ
$		// �̤��뤿��Ǥ��롥
		$intpri = 0 $
	$END$
	$TAB$$FORMAT("UINT32_C(0x%08x), /* 0x%03x */", intpri, +intno)$$NL$
$END$
$NL$};$NL$
$NL$


$ 
$  GCC��¸���Υƥ�ץ졼�ȥե�����Υ��󥯥롼��
$ 
$INCLUDE "gcc/ldscript.tf"$ 

$ 
$  ��ͭ�ΰ�ν�����֥�å�������
$ 
$FILE "kernel_cfg.h"$
extern const uint_t tnum_shared_mem;$NL$
extern char * const shared_meminib_table[];$NL$
$NL$

$FILE "kernel_mem2.c"$

$PREPARE_DOMINICTXB()$

$IF LENGTH(DOMLIST) > 0$
    const DOMINIB_INFO _kernel_dominib_info_tbl[TNUM_DOMID] ={$NL$
    $JOINEACH domid DOM.ID_LIST ",\n"$
        $TAB${$NL$
$   RX�ΰ�����ѡ�
        $TAB$$TAB$( (char *)&__start_text_$DOM.LABEL[domid]$ ),/* region 4 */$NL$
        $TAB$$TAB$( (uint32_t)&__limit_text_$DOM.LABEL[domid]$ ),/* region 4 */$NL$
$   RWX�ΰ�����ѡ�
        $TAB$$TAB$( (char *)&__start_ram_$DOM.LABEL[domid]$ ),/* region 5 */$NL$
        $TAB$$TAB$( (uint32_t)&__limit_ram_$DOM.LABEL[domid]$ ),/* region 5 */$NL$
$   ��ͭ�꡼�����ѥ饤��
        $TAB$$TAB$$FORMAT("( (char *)&__start_ram_%s_%x_%x )", DOM.LABEL[domid], +DEFAULT_ACPTN[domid], +TACP_SHARED)$,/* region 6 */$NL$
        $TAB$$TAB$$FORMAT("( (uint32_t)&__limit_ram_%s_%x_%x )", DOM.LABEL[domid], +DEFAULT_ACPTN[domid], +TACP_SHARED)$,/* region 6 */$NL$
$   ATT_MEM�ΰ�
        $TAB$$TAB$$FORMAT("( (char *)%1% )", DOM.MEM_BASE[domid])$,/* region 7 */$NL$
        $TAB$$TAB$$FORMAT("( (uint32_t)(%1% + %2%) )", DOM.MEM_BASE[domid], DOM.MEM_SIZE[domid])$,/* region 7 */$NL$
        $TAB$}
    $END$
    ,$NL$};$NL$
    $NL$
$END$

$TNUM_SHARED_REGION = 3$
const uint_t tnum_shared_mem = $TNUM_SHARED_REGION * 2$;$NL$
char * const shared_meminib_table[$TNUM_SHARED_REGION * 2$] = {$NL$
    $TAB$((char *)&__start_text_$DOM.LABEL[TDOM_NONE]$),$TAB$/* region 0 */$NL$
    $TAB$((char *)&__limit_text_$DOM.LABEL[TDOM_NONE]$),$TAB$/* region 0 */$NL$
    $TAB$((char *)&__start_ram_$DOM.LABEL[TDOM_NONE]$),$TAB$/* region 1 */$NL$
    $TAB$((char *)&__limit_ram_$DOM.LABEL[TDOM_NONE]$),$TAB$/* region 1 */$NL$
    $TAB$((char *)&__start_srpw_all),$TAB$/* region 2 */$NL$
    $TAB$((char *)&__limit_srpw_all),$TAB$/* region 2 */$NL$
};$NL$
$NL$

$FILE "cfg2_out.tf"$
$JOINEACH domid DOM.ID_LIST "\n"$
    $$DOM.MEM_BASE[$+domid$] = $FORMAT("\"%1%\"", DOM.MEM_BASE[domid])$$$$NL$
    $$DOM.MEM_SIZE[$+domid$] = $DOM.MEM_SIZE[domid]$$$$NL$
$END$
