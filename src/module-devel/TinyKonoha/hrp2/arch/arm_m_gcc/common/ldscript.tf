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
$   $Id: ldscript.tf 542 2011-10-25 03:29:15Z ertl-hiro $
$  
$ =====================================================================

$ =====================================================================
$ ��󥫥�����ץȤ�����
$ =====================================================================
$FILE "cfg3_out.ld"$

$
$  �������åȰ�¸��OUTPUT���Ҥ�����
$
$IF ISFUNCTION("GENERATE_OUTPUT")$
	$GENERATE_OUTPUT()$
$END$

$
$  MEMORY���Ҥ�����
$
MEMORY {$NL$
$FOREACH reg REG.ORDER_LIST$
	$TAB$$FORMAT("%s : ORIGIN = 0x%x, LENGTH = 0x%x",
				REG.REGNAME[reg], +REG.BASE[reg], +REG.SIZE[reg])$$NL$
$END$
$IF ISFUNCTION("GENERATE_MEMORY")$
	$GENERATE_MEMORY()$
$END$
}$NL$
$NL$

$
$  �������åȰ�¸��PROVIDE���Ҥ�����
$
$IF ISFUNCTION("GENERATE_PROVIDE")$
	$GENERATE_PROVIDE()$
$END$

$
$  �ѿ��ν����
$
$reset_lma = 0$

$
$  ��󥯻��������
$
SECTIONS {$NL$
$ �������åȰ�¸�Υ�������󵭽Ҥ�����
$IF ISFUNCTION("GENERATE_SECTION_FIRST")$
	$GENERATE_SECTION_FIRST()$
$END$

$IF TOPPERS_LABEL_ASM$
	$PREFIX_START = "___start_"$
	$PREFIX_END   = "___end_"$
	$PREFIX_LIMIT = "___limit_"$
$ELSE$
	$PREFIX_START = "__start_"$
	$PREFIX_END   = "__end_"$
	$PREFIX_LIMIT = "__limit_"$
$END$

$  ������MO_REAL_ORDER��Ȥ�ʤ��Τϡ�REG_align�ν�����ˡ��ѥ�2��
$  ���̲����뤿��
$FOREACH moid MO_ORDER$
	$IF MO.LINKER[moid]$
$		// ���������γ��ϵ��Ҥ�����
		$IF (MO.SEFLAG[moid] & 0x01) != 0$
			$TAB$.$MO.SLABEL[moid]$ 
            $IF LENGTH(MO.REALBASE[moid])$
                $FORMAT("(0x%x)", MO.REALBASE[moid])$
            $END$
            : {$NL$
		$END$

$		// ���������ȥ��ꥪ�֥������Ȥγ��ϥ�٥������
		$IF (MO.SEFLAG[moid] & 0x100) != 0$
			$TAB$$TAB$$PREFIX_START$srpw_all = .;$NL$
		$END$
		$IF (MO.SEFLAG[moid] & 0x10) != 0$
            $ALIGN_SIZE = MO.SIZE[moid]$
			$IF !EQ(MO.PLABEL[moid], "")$
				$TAB$$TAB$$PREFIX_START$$MO.PLABEL[moid]$ = .;$NL$
			$END$
		$END$
		$IF (MO.SEFLAG[moid] & 0x01) != 0$
			$IF !EQ(MO.SLABEL[moid], ALT(omit_start_slabel,""))$
				$TAB$$TAB$$PREFIX_START$$MO.SLABEL[moid]$ = .;$NL$
			$END$
		$END$
		$IF (MO.SEFLAG[moid] & 0x04) != 0$
			$IF (MO.SEFLAG[moid] & 0x01) == 0$
				$NL$
			$END$
			$IF !EQ(MO.MLABEL[moid], MO.SLABEL[moid])$
				$TAB$$TAB$$PREFIX_START$$MO.MLABEL[moid]$ = .;$NL$
			$END$
			$TAB$$TAB$
		$END$

$		// ��󥯤���ե����뵭�Ҥ�����
		$section_dscr = SECTION_DESCRIPTION(MO.SECTION[moid])$
		$IF MO.TYPE[moid] == TOPPERS_ATTMOD$
			$IF EQ(MO.MODULE[moid], "kernel_mem.o")$
				kernel_mem3.o
			$ELSE$
				$MO.MODULE[moid]$
			$END$
			($section_dscr$)$SPC$
		$ELIF MO.TYPE[moid] == TOPPERS_ATTSEC$
			*($section_dscr$)$SPC$
		$ELSE$
			kernel_cfg.o($section_dscr$)$SPC$
		$END$

$		// ���������ȥ��ꥪ�֥������Ȥν�λ��٥������
		$IF (MO.SEFLAG[moid] & 0x08) != 0$
			$NL$
			$IF !EQ(MO.MLABEL[moid], MO.SLABEL[moid])$
				$TAB$$TAB$$PREFIX_END$$MO.MLABEL[moid]$ = .;$NL$
			$END$
		$END$
		$IF (MO.SEFLAG[moid] & 0x02) != 0$
			$TAB$$TAB$$PREFIX_END$$MO.SLABEL[moid]$ = .;$NL$
		$END$
		$IF (MO.SEFLAG[moid] & 0x200) != 0$
			$TAB$$TAB$$PREFIX_END$srpw_all = .;$NL$
		$END$

$		// ���������ν�λ���Ҥ�����
		$IF (MO.SEFLAG[moid] & 0x02) != 0$
			$TAB$} > $REG.REGNAME[MO.MEMREG[moid]]$
			$IF !OMIT_IDATA$
				$IF !EQ(MO.ILABEL[moid], "")$
					$SPC$AT > $REG.REGNAME[STANDARD_ROM]$
					$reset_lma = 1$
				$ELIF reset_lma$
					$SPC$AT > $REG.REGNAME[MO.MEMREG[moid]]$
					$reset_lma = 0$
				$END$
			$END$$NL$
			$IF !OMIT_IDATA && !EQ(MO.ILABEL[moid], "")$
				$TAB$$PREFIX_START$$MO.ILABEL[moid]$ = LOADADDR(.$MO.SLABEL[moid]$);$NL$
			$END$
		$END$

$		// ���饤�󵭽Ҥ�����
		$IF (MO.SEFLAG[moid] & 0x20) != 0$
            $IF LENGTH(ALIGN_SIZE)$
                $TAB$. = ALIGN($ALIGN_SIZE$);$NL$
            $ELSE$
                $NOOP()$
$                $TAB$. = ALIGN($TARGET_PAGE_SIZE_STR$);$NL$
            $END$
		$ELIF (MO.SEFLAG[moid] & 0x08) != 0$
$			// ��������󤬷�³���Ƥ�����ˤϡ�TAB��1�Ľ���
			$IF (MO.SEFLAG[moid] & 0x02) == 0$$TAB$$END$
$			$TAB$. = ALIGN($TARGET_SEC_ALIGN_STR$);$NL$
		$END$

$		// ���������ȥ��ꥪ�֥������Ȥξ�¥�٥������
		$IF (MO.SEFLAG[moid] & 0x08) != 0$
			$IF !EQ(MO.MLABEL[moid], MO.SLABEL[moid])$
$				// ��������󤬷�³���Ƥ�����ˤϡ�TAB��1�Ľ���
				$IF (MO.SEFLAG[moid] & 0x02) == 0$$TAB$$END$
				$TAB$$PREFIX_LIMIT$$MO.MLABEL[moid]$ = .;$NL$
			$END$
		$END$
		$IF (MO.SEFLAG[moid] & 0x02) != 0$
			$TAB$$PREFIX_LIMIT$$MO.SLABEL[moid]$ = .;$NL$
		$END$
		$IF (MO.SEFLAG[moid] & 0x20) != 0$
			$IF !EQ(MO.PLABEL[moid], "")$
				$TAB$$PREFIX_LIMIT$$MO.PLABEL[moid]$ = .;$NL$
			$END$
		$END$
		$IF (MO.SEFLAG[moid] & 0x200) != 0$
			$TAB$$PREFIX_LIMIT$srpw_all = .;$NL$
		$END$

		$IF (MO.SEFLAG[moid] & 0x02) != 0$
			$NL$
		$END$

$		// ����꡼��������ǥ��饤�󤵤��뤿��Υ��ߡ���������������
		$IF (MO.SEFLAG[moid] & 0x80) != 0$
			$TAB$.$REG.REGNAME[MO.MEMREG[moid]]$_align 
			$IF LENGTH(REG.LIMIT[MO.MEMREG[moid]])$		
                $FORMAT("(0x%x)", REG.LIMIT[MO.MEMREG[moid]])$
            $ELSE$
                ALIGN($TARGET_SEC_ALIGN_STR$)
            $END$
            : {$NL$
			$TAB$$TAB$__$REG.REGNAME[MO.MEMREG[moid]]$_align = .;$NL$
			$TAB$} > $REG.REGNAME[MO.MEMREG[moid]]$$NL$
			$NL$
		$END$
	$END$
$END$

$FOREACH lsid RANGE(1, numls)$
	$TAB$$LNKSEC.SECTION[lsid]$ : {$NL$
	$TAB$$TAB$*($LNKSEC.SECTION[lsid]$)$NL$
	$TAB$} > $REG.REGNAME[LNKSEC.MEMREG[lsid]]$$NL$
	$NL$
$END$

$TAB$/DISCARD/ : {$NL$
$TAB$$TAB$*(.rel.dyn)$NL$
$TAB$}$NL$
$NL$

$TAB$/* DWARF debug sections.$NL$
$TAB$Symbols in the DWARF debugging sections are relative to $NL$
$TAB$the beginning of the section so we begin them at 0.  */$NL$
$NL$
$TAB$/* DWARF 1 */$NL$
$TAB$.debug          0 : { *(.debug) }$NL$
$TAB$.line           0 : { *(.line) }$NL$
$NL$
$TAB$/* GNU DWARF 1 extensions */$NL$
$TAB$.debug_srcinfo  0 : { *(.debug_srcinfo) }$NL$
$TAB$.debug_sfnames  0 : { *(.debug_sfnames) }$NL$
$NL$
$TAB$/* DWARF 1.1 and DWARF 2 */$NL$
$TAB$.debug_aranges  0 : { *(.debug_aranges) }$NL$
$TAB$.debug_pubnames 0 : { *(.debug_pubnames) }$NL$
$NL$
$TAB$/* DWARF 2 */$NL$
$TAB$.debug_info     0 : { *(.debug_info) }$NL$
$TAB$.debug_abbrev   0 : { *(.debug_abbrev) }$NL$
$TAB$.debug_line     0 : { *(.debug_line) }$NL$
$TAB$.debug_frame    0 : { *(.debug_frame) }$NL$
$TAB$.debug_str      0 : { *(.debug_str) }$NL$
$TAB$.debug_loc      0 : { *(.debug_loc) }$NL$
$TAB$.debug_macinfo  0 : { *(.debug_macinfo) }$NL$
$TAB$.debug_ranges   0 : { *(.debug_ranges) }$NL$
$NL$
$TAB$/* SGI/MIPS DWARF 2 extensions */$NL$
$TAB$.debug_weaknames 0 : { *(.debug_weaknames) }$NL$
$TAB$.debug_funcnames 0 : { *(.debug_funcnames) }$NL$
$TAB$.debug_typenames 0 : { *(.debug_typenames) }$NL$
$TAB$.debug_varnames  0 : { *(.debug_varnames) }$NL$
$NL$
}$NL$
