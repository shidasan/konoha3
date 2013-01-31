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
$   $Id: kernel_opt.tf 837 2012-12-26 15:09:59Z ertl-hiro $
$  
$ =====================================================================

$
$  �ѥ�2����ξ�����ɹ���
$
$INCLUDE "cfg2_out.tf"$

$
$  �ǡ�������������LMA����VMA�ؤΥ��ԡ�
$
$FOREACH lma LMA.ORDER_LIST$
	$start_data = SYMBOL(LMA.START_DATA[lma])$
	$end_data = SYMBOL(LMA.END_DATA[lma])$
	$start_idata = SYMBOL(LMA.START_IDATA[lma])$
	$IF !LENGTH(start_data)$
		$ERROR$$FORMAT(_("symbol '%1%' not found"), LMA.START_DATA[lma])$$END$
	$ELIF !LENGTH(end_data)$
		$ERROR$$FORMAT(_("symbol '%1%' not found"), LMA.END_DATA[lma])$$END$
	$ELIF !LENGTH(start_idata)$
		$ERROR$$FORMAT(_("symbol '%1%' not found"), LMA.START_IDATA[lma])$$END$
	$ELSE$
		$BCOPY(start_idata, start_data, end_data - start_data)$
	$END$
$END$

$ =====================================================================
$ kernel_mem3.c�ζ�����ʬ������
$ =====================================================================

$FILE "kernel_mem3.c"$
/* kernel_mem3.c */$NL$
#include "kernel/kernel_int.h"$NL$
#include "kernel_cfg.h"$NL$
$NL$
#if TKERNEL_PRID != 0x06u$NL$
#error "The kernel does not match this configuration file."$NL$
#endif$NL$
$NL$

/*$NL$
$SPC$*  Include Directives (#include)$NL$
$SPC$*/$NL$
$NL$
$INCLUDES$
$NL$

$ =====================================================================
$ ����ܥ�Ȳ����ꥪ�֥������Ƚ�����֥�å����ɹ���
$ =====================================================================

$
$ ����ܥ�Ȳ����ꥪ�֥������Ƚ�����֥�å����ɹ���
$
$ MO.BASEADDR[moid]�����ꥪ�֥������Ȥ���Ƭ����
$ MO.LIMITADDR[moid]�����ꥪ�֥������Ȥξ������

$IF !OMIT_STANDARD_MEMINIB$
	$MO_MEMTOP_LIST = {}$
	$memtop_table = SYMBOL("_kernel_memtop_table")$
	$offset = 0$
	$FOREACH moid MO_START_LIST$
		$IF MO.LINKER[moid]$
			$MO.BASEADDR[moid] = SYMBOL(CONCAT("__start_", MO.MLABEL[moid]))$
			$MO.LIMITADDR[moid] = SYMBOL(CONCAT("__limit_", MO.MLABEL[moid]))$
		$ELSE$
			$MO.BASEADDR[moid] = PEEK(memtop_table + offset, sizeof_void_ptr)$
			$offset = offset + sizeof_void_ptr$
			$MO.LIMITADDR[moid] = (MO.BASEADDR[moid] + MO.SIZE[moid]) & ((1 << sizeof_void_ptr * 8) - 1)$
		$END$
	$END$
$END$

$ =====================================================================
$ ���Υ��깽����������ե����������
$ =====================================================================

$
$  �����ꥪ�֥������Ƚ�����֥�å�������
$
$IF ISFUNCTION("GENERATE_MEMINIB_TABLE")$
$	// �������åȰ�¸���Υ��ꥪ�֥������Ƚ�����֥�å�����������Ƥ�
	$GENERATE_MEMINIB_TABLE()$
$ELIF !OMIT_STANDARD_MEMINIB$
	$IF LENGTH(OPTIMIZE_MEMINIB)$
$		// ���ɥ쥹0���֤��ΰ�
		$tsize_meminib = 1$
		$FOREACH moid MO_START_LIST$
$			// ��������0�Ǥʤ����ꥪ�֥������Ȥ���Ƭ���Ϥ��֤��ΰ�
			$IF MO.BASEADDR[moid] != MO.LIMITADDR[moid]$
				$tsize_meminib = tsize_meminib + 1$
			$END$
			$IF !MO.LINKER[moid]$
$				// ��󥫤����֤��ʤ����ꥪ�֥������ȤϺǽ����Ϥ�ɬ��
				$tsize_meminib = tsize_meminib + 1$
			$ELIF (MO.SEFLAG[MO.MOEND[moid]] & 0x80) != 0$
$				// ����꡼�����κǸ�Υ��ꥪ�֥������ȤϺǽ����Ϥ�ɬ��
				$tsize_meminib = tsize_meminib + 1$
			$END$
		$END$

$		// �������åȰ�¸��tsize_meminib������������
		$IF ISFUNCTION("CALC_TSIZE_MEMINIB")$
			$CALC_TSIZE_MEMINIB()$
		$END$
	$END$

	const uint_t _kernel_tnum_meminib = $tsize_meminib$U;$NL$
	$NL$

	void *const _kernel_memtop_table[$tsize_meminib$] = {
	$IF LENGTH(MO_START_LIST_NOLINKER)$
		$NL$
		$JOINEACH moid MO_START_LIST_NOLINKER ",\n"$
			$TAB$(void *)($MO.BASE[moid]$)
		$END$$NL$
	$ELSE$
		$SPC$0$SPC$
	$END$
	};$NL$
	$NL$

	const MEMINIB _kernel_meminib_table[$tsize_meminib$] =
	$SPC${{ TA_NULL, 0U, 0U, 0U }};$NL$
	$NL$
$END$

$
$  ��data��������������֥�å�������
$
$IF LENGTH(OPTIMIZE_DATASEC_LIST) && !OMIT_IDATA && LENGTH(DATASEC_LIST)$
$	// ��data��������������֥�å��Υ�������Ŭ��������
$	// ��������0�Ǥʤ�data���������Υꥹ�ȡ�MO_DATASEC_LIST�ˤ����
	$MO_DATASEC_LIST = {}$
	$FOREACH moid DATASEC_LIST$
		$IF MO.BASEADDR[moid] != MO.LIMITADDR[moid]$
			$MO_DATASEC_LIST = APPEND(MO_DATASEC_LIST, moid)$
		$END$
	$END$

$	// �ѥ�4�˰����Ϥ�����
	$DATASEC_LIST = MO_DATASEC_LIST$
	$DATASEC_LIST_OPTIMIZED = 1$
$END$

$	// data���������ο���data��������������֥�å�
$IF !OMIT_IDATA && LENGTH(DATASEC_LIST)$
	const uint_t _kernel_tnum_datasec = $LENGTH(DATASEC_LIST)$U;$NL$
	const DATASECINIB _kernel_datasecinib_table[$LENGTH(DATASEC_LIST)$] =
	$SPC${{ 0, 0, 0 }};$NL$
$ELSE$
	const uint_t _kernel_tnum_datasec = 0U;$NL$
	TOPPERS_EMPTY_LABEL(const DATASECINIB, _kernel_datasecinib_table);$NL$
$END$$NL$

$
$  ��bss��������������֥�å�������
$
$IF LENGTH(OPTIMIZE_BSSSEC_LIST) && LENGTH(BSSSEC_LIST)$
$	// ��bss��������������֥�å��Υ�������Ŭ��������
$	// ��������0�Ǥʤ�bss���������Υꥹ�ȡ�MO_BSSSEC_LIST�ˤ����
	$MO_BSSSEC_LIST = {}$
	$FOREACH moid BSSSEC_LIST$
		$IF MO.BASEADDR[moid] != MO.LIMITADDR[moid]$
			$MO_BSSSEC_LIST = APPEND(MO_BSSSEC_LIST, moid)$
		$END$
	$END$

$	// �ѥ�4�˰����Ϥ�����
	$BSSSEC_LIST = MO_BSSSEC_LIST$
	$BSSSEC_LIST_OPTIMIZED = 1$
$END$

$	// bss���������ο���bss��������������֥�å�
$IF LENGTH(BSSSEC_LIST)$
	const uint_t _kernel_tnum_bsssec = $LENGTH(BSSSEC_LIST)$U;$NL$
	const BSSSECINIB _kernel_bsssecinib_table[$LENGTH(BSSSEC_LIST)$] =
	$SPC${{ 0, 0 }};$NL$
$ELSE$
	const uint_t _kernel_tnum_bsssec = 0U;$NL$
	TOPPERS_EMPTY_LABEL(const BSSSECINIB, _kernel_bsssecinib_table);$NL$
$END$$NL$

$ =====================================================================
$  �ѥ�4���Ϥ����������
$ =====================================================================

$FILE "cfg3_out.tf"$
$$ cfg3_out.tf$NL$
$NL$

$ tsize_meminib�ν���
$IF !OMIT_STANDARD_MEMINIB$
	$$tsize_meminib = $tsize_meminib$$$$NL$
	$NL$
$END$

$ DATASEC_LIST��MO_DATASEC_LIST��DATASEC_LIST_OPTIMIZED�ν���
$$DATASEC_LIST = { $DATASEC_LIST$ }$$$NL$
$IF LENGTH(DATASEC_LIST_OPTIMIZED)$
	$$MO_DATASEC_LIST = { $MO_DATASEC_LIST$ }$$$NL$
	$$DATASEC_LIST_OPTIMIZED = $DATASEC_LIST_OPTIMIZED$$$$NL$
$END$
$NL$

$ BSSSEC_LIST��MO_BSSSEC_LIST��BSSSEC_LIST_OPTIMIZED�ν���
$$BSSSEC_LIST = { $BSSSEC_LIST$ }$$$NL$
$IF LENGTH(BSSSEC_LIST_OPTIMIZED)$
	$$MO_BSSSEC_LIST = { $MO_BSSSEC_LIST$ }$$$NL$
	$$BSSSEC_LIST_OPTIMIZED = $BSSSEC_LIST_OPTIMIZED$$$$NL$
$END$
$NL$
