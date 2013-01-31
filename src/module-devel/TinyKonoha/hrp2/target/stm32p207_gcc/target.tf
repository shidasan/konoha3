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
$     �ѥ�2�Υ������åȰ�¸�ƥ�ץ졼�ȡ�STM32P207�ѡ�
$ 

$ 
$  kernel/kernel.tf �Υ������åȰ�¸��
$ 

$ 
$  ɸ��Υ��������Υ��ꥪ�֥�������°�������
$ 
$MEMATR_TEXT = (TA_NOWRITE|TA_EXEC)$
$MEMATR_RODATA = (TA_NOWRITE|TA_EXEC)$
$MEMATR_DATA = TA_MEMINI$
$MEMATR_BSS = TA_NULL$
$MEMATR_PRSV = TA_MEMPRSV$

$TARGET_MEMATR_USTACK = TA_NULL$

$ 
$  ɸ��Υ��������˴ؤ������
$  DSEC.ORDER_LIST��ID�Υꥹ��
$  DESC.MEMREG���������������֤������꡼�����
$  DESC.SECTION�����������̾
$  DESC.MEMATR�����������Υ��ꥪ�֥�������°��
$ 
$FUNCTION DEFINE_DSEC$
    $DSEC.ORDER_LIST = RANGE(0,3)$

    $IF TOPPERS_RAM_DEBUG$
        $DSEC.MEMREG[0] = STANDARD_RAM$
    $ELSE$
        $DSEC.MEMREG[0] = STANDARD_ROM$
    $END$
    $DSEC.SECTION[0] = ".text"$
    $DSEC.MEMATR[0] = MEMATR_TEXT$

    $IF TOPPERS_RAM_DEBUG$
        $DSEC.MEMREG[1] = STANDARD_RAM$
    $ELSE$
        $DSEC.MEMREG[1] = STANDARD_ROM$
    $END$
    $DSEC.SECTION[1] = ".rodata"$
    $DSEC.MEMATR[1] = MEMATR_RODATA$

    $DSEC.MEMREG[2] = STANDARD_RAM$
    $DSEC.SECTION[2] = ".data"$
    $DSEC.MEMATR[2] = MEMATR_DATA$

    $DSEC.MEMREG[3] = STANDARD_RAM$
    $DSEC.SECTION[3] = ".bss"$
    $DSEC.MEMATR[3] = MEMATR_BSS$

$END$

$ 
$  arch/gcc/ldscript.tf�Υ������åȰ�¸��
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
$  �����ͥ뤬�������ʤ�������������Ϥ���
$  �������åȰ�¸��ɬ�פʥ��������
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
$  �ڡ����������ȥ��饤����Ȥ�����
$ 
$TARGET_PAGE_SIZE_STR = 1024$
$TARGET_SEC_ALIGN_STR = 1024$

$
$  ��󥫤Τ���Υ�������󵭽Ҥ�����
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

$ 
$  ���åװ�¸�Υƥ�ץ졼�ȥե�����Υ��󥯥롼��
$ 
$INCLUDE"arm_m_gcc/stm32f/chip.tf"$

