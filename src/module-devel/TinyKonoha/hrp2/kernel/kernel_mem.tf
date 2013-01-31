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
$   $Id: kernel_mem.tf 837 2012-12-26 15:09:59Z ertl-hiro $
$  
$ =====================================================================

$
$  �ѥ�2���ѥ�3����ξ�����ɹ���
$
$INCLUDE "cfg2_out.tf"$
$INCLUDE "cfg3_out.tf"$

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
$ kernel_mem.c�ζ�����ʬ������
$ =====================================================================

$FILE "kernel_mem.c"$
/* kernel_mem.c */$NL$
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
$ ����ܥ�Ȳ����ꥪ�֥������Ƚ�����֥�å����ɹ��ߤ�������
$ =====================================================================

$
$ ����ܥ�Ȳ����ꥪ�֥������Ƚ�����֥�å����ɹ���
$
$ MO.BASEADDR[moid]�����ꥪ�֥������Ȥ���Ƭ����
$ MO.LIMITADDR[moid]�����ꥪ�֥������Ȥξ������
$ MO.POFFSET[moid]��ʪ�����ɥ쥹�ȤΥ��ե��å�
$ MO_MEMTOP_LIST����������0�Ǥʤ����ꥪ�֥������ȤΥꥹ��

$IF !OMIT_STANDARD_MEMINIB$
	$MO_MEMTOP_LIST = {}$
	$memtop_table = SYMBOL("_kernel_memtop_table")$
	$offset = 0$
	$FOREACH moid MO_START_LIST$
		$IF MO.LINKER[moid]$
			$MO.BASEADDR[moid] = SYMBOL(CONCAT("__start_", MO.MLABEL[moid]))$
			$MO.LIMITADDR[moid] = SYMBOL(CONCAT("__limit_", MO.MLABEL[moid]))$
			$MO.POFFSET[moid] = 0$
		$ELSE$
			$MO.BASEADDR[moid] = PEEK(memtop_table + offset, sizeof_void_ptr)$
			$offset = offset + sizeof_void_ptr$
			$MO.LIMITADDR[moid] = (MO.BASEADDR[moid] + MO.SIZE[moid]) & ((1 << sizeof_void_ptr * 8) - 1)$
			$IF LENGTH(MO.PADDR[moid])$
				$MO.POFFSET[moid] = MO.PADDR[moid] - MO.BASEADDR[moid]$
			$ELSE$
				$MO.POFFSET[moid] = 0$
			$END$
		$END$

		$IF MO.BASEADDR[moid] != MO.LIMITADDR[moid]$
			$IF MO.BASEADDR[moid] < MO.LIMITADDR[moid]
											|| MO.LIMITADDR[moid] == 0$
				$MO_MEMTOP_LIST = APPEND(MO_MEMTOP_LIST, moid)$
			$ELIF MO.TYPE[moid] == TOPPERS_ATTMEM$
				$ERROR MO.TEXT_LINE[moid]$E_PAR: 
					$FORMAT(_("%1% `%2%\' is too large in %3%"),
								"size", MO.SIZE[moid], MO.APINAME[moid])$
				$END$
			$ELSE$
				$ERROR MO.TEXT_LINE[moid]$E_SYS: 
					$FORMAT(_("illegal memory object size"))$
				$END$
			$END$
		$END$
	$END$
$END$

$
$ ���ꥪ�֥������ȤνŤʤ�Υ����å�
$
$ MO.SUPPRESSLIMIT[moid]�����Υ��ꥪ�֥������Ȥ����ܤ��Ƥ���
$ MO.MERGED[moid]��ʻ�礵�줿�桼�������å��ΰ��ʻ����
$ MO_MEMTOP_ORDER�����ꥪ�֥������ȤΥ١������ɥ쥹��Υꥹ��

$MO_MEMTOP_ORDER = {}$
$prev = 0$
$FOREACH moid SORT(MO_MEMTOP_LIST, "MO.BASEADDR")$
	$IF !prev || (MO.LIMITADDR[prev] <= MO.BASEADDR[moid]
											&& MO.LIMITADDR[prev] != 0)$
		$MO_MEMTOP_ORDER = APPEND(MO_MEMTOP_ORDER, moid)$
		$IF prev && MO.LIMITADDR[prev] == MO.BASEADDR[moid]$
			$MO.SUPPRESSLIMIT[prev] = 1$
		$END$
		$prev = moid$
	$ELSE$
$		// ���ꥪ�֥������Ȥ��ΰ�˽Ťʤ꤬������
		$IF OMIT_CHECK_USTACK_OVERLAP
					&& MO.TYPE[moid] == TOPPERS_USTACK
					&& MO.TYPE[prev] == TOPPERS_USTACK
					&& MO.DOMAIN[prev] == MO.DOMAIN[moid]$
$			// �桼�������å��ΰ��ʻ�����
			$MO.TSKID[prev] = 0$
			$MO.TSKID[moid] = 0$
			$MO.BASE[moid] = MO.BASE[prev]$
			$MO.BASEADDR[moid] = MO.BASEADDR[prev]$
			$IF MO.LIMITADDR[prev] < MO.LIMITADDR[moid]
											&& MO.LIMITADDR[prev] != 0$
				$MO.SIZE[prev] = MO.LIMITADDR[moid] - MO.BASEADDR[prev]$
				$MO.LIMITADDR[prev] = MO.LIMITADDR[moid]$
			$ELSE$
				$MO.SIZE[moid] = MO.SIZE[prev]$
				$MO.LIMITADDR[moid] = MO.LIMITADDR[prev]$
			$END$
			$MO.MERGED[moid] = prev$
		$ELSE$
$			// ���顼��å������ν���
			$IF MO.TYPE[moid] == TOPPERS_ATTMEM$
				$ERROR MO.TEXT_LINE[moid]$E_OBJ: 
					$FORMAT(_("memory object registered with %1% overlaps with another memory object"), MO.APINAME[moid])$
				$END$
			$ELIF MO.TYPE[prev] == TOPPERS_ATTMEM$
				$ERROR MO.TEXT_LINE[prev]$E_OBJ: 
					$FORMAT(_("memory object registered with %1% overlaps with another memory object"), MO.APINAME[prev])$
				$END$
			$ELIF MO.TYPE[moid] == TOPPERS_USTACK$
				$ERROR MO.TEXT_LINE[moid]$E_OBJ: 
					$FORMAT(_("user stack area registered with %1% overlaps with another memory object"), MO.APINAME[moid])$
				$END$
			$ELIF MO.TYPE[prev] == TOPPERS_USTACK$
				$ERROR MO.TEXT_LINE[prev]$E_OBJ: 
					$FORMAT(_("user stack area registered with %1% overlaps with another memory object"), MO.APINAME[prev])$
				$END$
			$ELSE$
				$ERROR MO.TEXT_LINE[moid]$E_SYS: 
					$FORMAT(_("memory objects overlap"))$
				$END$
			$END$
		$END$
	$END$
$END$
$IF MO.LIMITADDR[prev] == 0$
	$MO.SUPPRESSLIMIT[prev] = 1$
$END$

$ =====================================================================
$ ���ꥪ�֥������Ƚ�����֥�å�������
$ =====================================================================

$IF ISFUNCTION("GENERATE_MEMINIB_TABLE")$
$	// �������åȰ�¸���Υ��ꥪ�֥������Ƚ�����֥�å�����������Ƥ�
	$GENERATE_MEMINIB_TABLE()$
$ELIF !OMIT_STANDARD_MEMINIB$
$	// ���ꥪ�֥������Ƚ�����֥�å��˽��Ϥ��륨��ȥ�η���
$
$	// tnum_meminib�����ꥪ�֥������Ƚ�����֥�å��˽��Ϥ��륨��ȥ��
$	// genzero�����ɥ쥹0���б����륨��ȥ����Ϥ���
	$tnum_meminib = 0$
	$prev = 0$
	$FOREACH moid MO_MEMTOP_ORDER$
		$IF !prev && MO.BASEADDR[moid] != 0$
			$genzero = 1$
			$tnum_meminib = tnum_meminib + 1$
		$END$
		$IF LENGTH(MO.SUPPRESSLIMIT[moid])$
			$tnum_meminib = tnum_meminib + 1$
		$ELSE$
			$tnum_meminib = tnum_meminib + 2$
		$END$
		$prev = moid$
	$END$

$	// tsize_meminib�������������å�
	$IF tsize_meminib < tnum_meminib$
		$ERROR$E_SYS: 
			$FORMAT(_("illegal memory object initialization block size"))$
		$END$
	$END$

$	// memtop_table�ǻ��Ȥ����٥�����������
	$FOREACH moid MO_MEMTOP_ORDER$
		$IF MO.LINKER[moid]$
			extern char __start_$MO.MLABEL[moid]$;$NL$
			$IF !LENGTH(MO.SUPPRESSLIMIT[moid])$
				extern char __limit_$MO.MLABEL[moid]$;$NL$
			$END$
		$END$
	$END$$NL$

$	// tnum_meminib������
	const uint_t _kernel_tnum_meminib = $tnum_meminib$U;$NL$
	$NL$

$	// memtop_table������
	void *const _kernel_memtop_table[$tsize_meminib$] = {$NL$
	$IF LENGTH(genzero)$
		$TAB$0,$NL$
	$END$
	$JOINEACH moid MO_MEMTOP_ORDER ",\n"$
		$IF MO.LINKER[moid]$
			$TAB$&__start_$MO.MLABEL[moid]$
			$SPC$/* $FORMAT("%x", MO.BASEADDR[moid])$ */
			$IF !LENGTH(MO.SUPPRESSLIMIT[moid])$
				,$NL$$TAB$&__limit_$MO.MLABEL[moid]$
				$SPC$/* $FORMAT("%x", MO.LIMITADDR[moid])$ */
			$END$
		$ELSE$
			$TAB$(void *)($MO.BASE[moid]$)
			$SPC$/* $FORMAT("%x", MO.BASEADDR[moid])$ */
			$IF !LENGTH(MO.SUPPRESSLIMIT[moid])$
				,$NL$$TAB$(void *)(((char *)($MO.BASE[moid]$)) + ($MO.SIZE[moid]$))
				$SPC$/* $FORMAT("%x", MO.LIMITADDR[moid])$ */
			$END$
		$END$
	$END$$NL$
	};$NL$
	$NL$

$	// meminib_table������
	const MEMINIB _kernel_meminib_table[$tsize_meminib$] = {$NL$
	$IF LENGTH(genzero)$
		$TAB${ TA_NULL, 0U, 0U, 0U },$NL$
	$END$
	$JOINEACH moid MO_MEMTOP_ORDER ",\n"$
		$TAB${
		$IF MO.TYPE[moid] == TOPPERS_USTACK$
			$SPC$TOPPERS_USTACK|($MO.MEMATR[moid]$),
			$SPC$$MO.ACPTN4[moid]$,
			$IF MO.TSKID[moid] != 0$
				$SPC$(ACPTN)(&_kernel_tcb_table[$MO.TSKID[moid]$ - 1]),
			$ELSE$
				$SPC$(ACPTN)(NULL),
			$END$
			$SPC$0U
		$ELSE$
			$IF MO.TYPE[moid] == TOPPERS_ATTMEM$
				$SPC$TOPPERS_ATTMEM|($MO.MEMATR[moid]$),
			$ELSE$
				$SPC$TOPPERS_ATTSEC|($MO.MEMATR[moid]$),
			$END$
			$SPC$$MO.ACPTN4[moid]$,
			$SPC$$MO.ACPTN1[moid]$,
			$SPC$$MO.ACPTN2[moid]$
		$END$
		$SPC$}
		$IF !LENGTH(MO.SUPPRESSLIMIT[moid])$
			,$NL$$TAB${ TA_NULL, 0U, 0U, 0U }
		$END$
	$END$$NL$
	};$NL$
	$NL$
$END$

$
$  data��������������֥�å�������
$
/*$NL$
$SPC$*  Data Section Management Functions$NL$
$SPC$*/$NL$
$NL$

$IF !OMIT_IDATA && LENGTH(DATASEC_LIST)$
$	// ��������0�Ǥʤ�data���������Υꥹ�ȡ�MO_DATASEC_LIST�ˤ����
	$IF !LENGTH(DATASEC_LIST_OPTIMIZED)$
		$MO_DATASEC_LIST = {}$
		$FOREACH moid DATASEC_LIST$
			$IF MO.BASEADDR[moid] != MO.LIMITADDR[moid]$
				$MO_DATASEC_LIST = APPEND(MO_DATASEC_LIST, moid)$
			$END$
		$END$
	$END$

$	// data��������������֥�å��ǻȤ�����ܥ��extern���
	$FOREACH moid MO_DATASEC_LIST$
		extern char __start_$MO.SLABEL[moid]$;$NL$
		extern char __end_$MO.SLABEL[moid]$;$NL$
		extern char __start_$MO.ILABEL[moid]$;$NL$
	$END$$NL$

$	// data���������ο�
	const uint_t _kernel_tnum_datasec = $LENGTH(MO_DATASEC_LIST)$U;$NL$
	$NL$

$	// data��������������֥�å�
	const DATASECINIB _kernel_datasecinib_table[$LENGTH(DATASEC_LIST)$] = {
	$IF LENGTH(MO_DATASEC_LIST)$
		$NL$
		$JOINEACH moid MO_DATASEC_LIST ",\n"$
			$TAB${ &__start_$MO.SLABEL[moid]$, &__end_$MO.SLABEL[moid]$, 
			&__start_$MO.ILABEL[moid]$ }
		$END$$NL$
	$ELSE$
		{ 0, 0, 0 }
	$END$
	};$NL$
$ELSE$
	const uint_t _kernel_tnum_datasec = 0U;$NL$
	TOPPERS_EMPTY_LABEL(const DATASECINIB, _kernel_datasecinib_table);$NL$
$END$$NL$

$
$  bss��������������֥�å�������
$
/*$NL$
$SPC$*  BSS Section Management Functions$NL$
$SPC$*/$NL$
$NL$

$IF LENGTH(BSSSEC_LIST)$
$	// ��������0�Ǥʤ�bss���������Υꥹ�ȡ�MO_BSSSEC_LIST�ˤ����
	$IF !LENGTH(BSSSEC_LIST_OPTIMIZED)$
		$MO_BSSSEC_LIST = {}$
		$FOREACH moid BSSSEC_LIST$
			$IF MO.BASEADDR[moid] != MO.LIMITADDR[moid]$
				$MO_BSSSEC_LIST = APPEND(MO_BSSSEC_LIST, moid)$
			$END$
		$END$
	$END$

$	// bss��������������֥�å��ǻȤ�����ܥ��extern���
	$FOREACH moid MO_BSSSEC_LIST$
		extern char __start_$MO.SLABEL[moid]$;$NL$
		extern char __end_$MO.SLABEL[moid]$;$NL$
	$END$$NL$

$	// bss���������ο�
	const uint_t _kernel_tnum_bsssec = $LENGTH(MO_BSSSEC_LIST)$U;$NL$
	$NL$

$	// bss��������������֥�å�
	const BSSSECINIB _kernel_bsssecinib_table[$LENGTH(BSSSEC_LIST)$] = {
	$IF LENGTH(MO_BSSSEC_LIST)$
		$NL$
		$JOINEACH moid MO_BSSSEC_LIST ",\n"$
			$TAB${ &__start_$MO.SLABEL[moid]$, &__end_$MO.SLABEL[moid]$ }
		$END$$NL$
	$ELSE$
		{ 0, 0 }
	$END$
	};$NL$
$ELSE$
	const uint_t _kernel_tnum_bsssec = 0U;$NL$
	TOPPERS_EMPTY_LABEL(const BSSSECINIB, _kernel_bsssecinib_table);$NL$
$END$$NL$

$ =====================================================================
$ �����ݸ�ñ�̤˴ؤ�����������
$ =====================================================================
$
$ nummp�������ݸ��ΰ�ο�
$ MP.BASEADDR[mpid]����Ƭ����
$ MP.LIMITADDR[mpid]���������
$ MP.POFFSET[mpid]��ʪ�����ɥ쥹�ȤΥ��ե��å�
$ MP.MEMATR[mpid]�����ꥪ�֥�������°��
$ MP.ACPTN1[mpid]���̾����1�ʽ���ߡˤΥ����������ĥѥ�����
$ MP.ACPTN2[mpid]���̾����2���ɽФ����¹ԡˤΥ����������ĥѥ�����
$ MP.DOMAIN[mpid]��°����ɥᥤ���̵��°�ξ���TDOM_NONE��
$ MP.GLOBAL[mpid]�������ݸ�°�������٤ƤΥ桼���ɥᥤ���Ʊ��ʥ桼��
$				   �ɥᥤ�󤬤ʤ�����ޤ��
$ MP.PRIVATE[mpid]�������ݸ�°����°����桼���ɥᥤ��ʳ���Ʊ��ʥ桼
$					���ɥᥤ���°������Τ�ͭ����
$ MP.MOID[mpid]����Ƭ�Υ��ꥪ�֥������Ȥ�ID
$
$ ���MMU����ĥ������åȸ����ξ���Ǥ��ꡤMPU����ĥ������åȤǤ�ɬ��
$ �ʤ����ᡤGENERATE_MP_INFO�����ꤵ��Ƥ�����ˤΤ���������

$IF LENGTH(GENERATE_MP_INFO)$
	$nummp = 0$
	$prevaddr = 0$
	$FOREACH moid SORT(MO_MPROTECT_LIST, "MO.BASEADDR")$
$		// �����ݸ�ñ�̤���Ƭ���ϤȾ�����Ϥ���Ф�
		$IF MO.LINKER[moid]$
			$IF EQ(MO.PLABEL[moid], "")$
				$plabel = MO.SLABEL[moid]$
			$ELSE$
				$plabel = MO.PLABEL[moid]$
			$END$
			$baseaddr = SYMBOL(CONCAT("__start_", plabel))$
			$limitaddr = SYMBOL(CONCAT("__limit_", plabel))$
		$ELSE$
			$baseaddr = MO.BASEADDR[moid]$
			$limitaddr = MO.LIMITADDR[moid]$
		$END$

$		// �����ݸ�ñ�̤˴ؤ�����������
		$IF baseaddr != limitaddr && !LENGTH(MO.MERGED[moid])$
			$IF prevaddr < baseaddr$
$				// ̤�����ΰ����Ͽ
				$nummp = nummp + 1$
				$MP.BASEADDR[nummp] = prevaddr$
				$MP.LIMITADDR[nummp] = baseaddr$
			$END$

$			// �����ݸ��ΰ����Ͽ
			$nummp = nummp + 1$
			$MP.BASEADDR[nummp] = baseaddr$
			$MP.LIMITADDR[nummp] = limitaddr$
			$MP.POFFSET[nummp] = MO.POFFSET[moid]$
			$MP.MEMATR[nummp] = MO.MEMATR[moid]$
			$MP.ACPTN1[nummp] = MO.ACPTN1[moid]$
			$MP.ACPTN2[nummp] = MO.ACPTN2[moid]$
			$MP.DOMAIN[nummp] = MO.DOMAIN[moid]$
			$MP.MOID[nummp] = moid$

$			// MP.GLOBAL[nummp]������
			$IF (MP.ACPTN1[nummp] == TACP_KERNEL
									|| MP.ACPTN1[nummp] == TACP_SHARED)
					&& (MP.ACPTN2[nummp] == TACP_KERNEL
									|| MP.ACPTN2[nummp] == TACP_SHARED)$
				$MP.GLOBAL[nummp] = 1$
			$END$

$			// MP.PRIVATE[nummp]������
			$IF MP.DOMAIN[nummp] > 0$
				$default_acptn = 1 << (MP.DOMAIN[nummp] - 1)$
				$IF (MP.ACPTN1[nummp] == TACP_KERNEL
									|| MP.ACPTN1[nummp] == TACP_SHARED
									|| MP.ACPTN1[nummp] == default_acptn)
						&& (MP.ACPTN2[nummp] == TACP_KERNEL
									|| MP.ACPTN2[nummp] == TACP_SHARED
									|| MP.ACPTN2[nummp] == default_acptn)$
					$MP.PRIVATE[nummp] = 1$
				$END$
			$END$

			$prevaddr = limitaddr$
		$END$
	$END$
	$IF prevaddr != 0$
$		// ̤�����ΰ����Ͽ
		$nummp = nummp + 1$
		$MP.BASEADDR[nummp] = prevaddr$
		$MP.LIMITADDR[nummp] = 0$
	$END$
$END$

$ =====================================================================
$ ���֥������ȴ����ΰ����˴ؤ��륨�顼�����å�
$ =====================================================================

$
$ �����ΰ��ޤ���ꥪ�֥������ȤΥ�����
$
$FUNCTION SEARCH_MO$
	$_base = ARGV[1]$
	$_limit = (ARGV[1] + ARGV[2]) & ((1 << sizeof_void_ptr * 8) - 1)$
	$IF _limit < _base && _limit != 0$
		$RESULT = 0$
	$ELSE$
		$i = 1$
		$j = LENGTH(MO_MEMTOP_ORDER)$
		$found = 0$

		$WHILE !found && i <= j$
			$k = (i + j) / 2$
			$_moid = AT(MO_MEMTOP_ORDER,k-1)$
			$IF _base < MO.BASEADDR[_moid]$
				$j = k - 1$
			$ELIF _base >= MO.LIMITADDR[_moid] && MO.LIMITADDR[_moid] != 0$
				$i = k + 1$
			$ELSE$
				$found = _moid$
			$END$
		$END$
		$IF found && _limit > MO.LIMITADDR[found] && MO.LIMITADDR[found] != 0$
			$found = 0$
		$END$
		$RESULT = found$
	$END$
$END$

$
$ �����ΰ褬���ꥪ�֥������Ȥ˴ޤޤ�Ƥ��뤫�Υ����å�
$
$FUNCTION CHECK_MEMOBJ$
	$IF SEARCH_MO(ARGV[1], ARGV[2])$
		$RESULT = 0$
	$ELSE$		
		$RESULT = 1$
	$END$
$END$

$
$ �����ΰ褬�����ͥ����ѤΥ��ꥪ�֥������Ȥ˴ޤޤ�Ƥ��뤫�Υ����å�
$
$FUNCTION CHECK_MEMOBJ_KERNEL$
	$moid = SEARCH_MO(ARGV[1], ARGV[2])$
	$IF moid && MO.ACPTN1[moid] == TACP_KERNEL
				&& MO.ACPTN2[moid] == TACP_KERNEL
				&& MO.ACPTN4[moid] == TACP_KERNEL$
		$RESULT = 0$
	$ELSE$		
		$RESULT = 1$
	$END$
$END$

$
$ �����ƥॿ�����Υ����å��ΰ�ȥ桼���������Υ����ƥॹ���å��ΰ褬��
$ �����ͥ����ѤΥ��ꥪ�֥������Ȥ˴ޤޤ�Ƥ��뤫�Υ����å�
$
$IF !USE_TSKINICTXB$
	$tinib = SYMBOL("_kernel_tinib_table")$
	$FOREACH tskid TSK.ID_LIST$
		$sstk = PEEK(tinib + offsetof_TINIB_sstk, sizeof_void_ptr)$
		$sstksz = PEEK(tinib + offsetof_TINIB_sstksz, sizeof_SIZE)$
		$IF CHECK_MEMOBJ_KERNEL(sstk, sstksz)$
			$IF TSK.DOMAIN[tskid] == TDOM_KERNEL$
				$ERROR TSK.TEXT_LINE[tskid]$E_OBJ: 
					$FORMAT(_("stack area of `%1%\' is not included in any kernel memory object"), tskid)$
				$END$
			$ELSE$
				$ERROR TSK.TEXT_LINE[tskid]$E_OBJ: 
					$FORMAT(_("system stack area of `%1%\' is not included in any kernel memory object"), tskid)$
				$END$
			$END$
		$END$
		$tinib = tinib + sizeof_TINIB$
	$END$
$END$

$
$ �󥿥�������ƥ������ѤΥ����å��ΰ褬�������ͥ����ѤΥ��ꥪ�֥���
$ ���Ȥ˴ޤޤ�Ƥ��뤫�Υ����å�
$
$istk = PEEK(SYMBOL("_kernel_istk"), sizeof_void_ptr)$
$istksz = PEEK(SYMBOL("_kernel_istksz"), sizeof_SIZE)$
$IF CHECK_MEMOBJ_KERNEL(istk, istksz)$
	$ERROR ICS.TEXT_LINE[1]$E_OBJ: 
		$FORMAT(_("interrupt context stack area is not included in any kernel memory object"))$
	$END$
$END$

$
$ CRE_MPF�ǻ��ꤷ������Ĺ����ס����ΰ褬�������ͥ����Ͽ���줿����
$ ���֥������Ȥ˴ޤޤ�Ƥ��뤫�Υ����å�
$
$mpfinib = SYMBOL("_kernel_mpfinib_table")$
$FOREACH mpfid MPF.ID_LIST$
	$mpf = PEEK(mpfinib + offsetof_MPFINIB_mpf, sizeof_void_ptr)$
	$blksz = PEEK(mpfinib + offsetof_MPFINIB_blksz, sizeof_uint_t)$
	$blkcnt = PEEK(mpfinib + offsetof_MPFINIB_blkcnt, sizeof_uint_t)$
	$mpfsz = blksz * blkcnt$
	$IF CHECK_MEMOBJ(mpf, mpfsz)$
		$ERROR MPF.TEXT_LINE[mpfid]$E_OBJ: 
			$FORMAT(_("%1% of `%2%\' is not included in any memory object"), "memory pool area", mpfid)$
		$END$
	$END$
	$mpfinib = mpfinib + sizeof_MPFINIB$
$END$

$ =====================================================================
$ ���饤����Ȥ�NULL�Ǥʤ����˴ؤ��륨�顼�����å�
$ =====================================================================

$
$  �ؿ�����Ƭ���ϤΥ����å�
$
$IF CHECK_FUNC_ALIGN || CHECK_FUNC_NONNULL$
$	// �������ȥ������㳰�����롼�������Ƭ���ϤΥ����å�
	$tinib = SYMBOL("_kernel_tinib_table")$
	$FOREACH tskid TSK.ID_LIST$
		$task = PEEK(tinib + offsetof_TINIB_task, sizeof_FP)$
		$IF CHECK_FUNC_ALIGN && (task & (CHECK_FUNC_ALIGN - 1)) != 0$
			$ERROR TSK.TEXT_LINE[tskid]$E_PAR: 
				$FORMAT(_("%1% `%2%\' of `%3%\' in %4% is not aligned"),
				"task", TSK.TASK[tskid], tskid, "CRE_TSK")$$END$
		$END$
		$IF CHECK_FUNC_NONNULL && task == 0$
			$ERROR TSK.TEXT_LINE[tskid]$E_PAR: 
				$FORMAT(_("%1% `%2%\' of `%3%\' in %4% is null"),
				"task", TSK.TASK[tskid], tskid, "CRE_TSK")$$END$
		$END$
		$texrtn = PEEK(tinib + offsetof_TINIB_texrtn, sizeof_FP)$
		$IF CHECK_FUNC_ALIGN && (texrtn & (CHECK_FUNC_ALIGN - 1)) != 0$
			$ERROR DEF_TEX.TEXT_LINE[tskid]$E_PAR: 
				$FORMAT(_("%1% `%2%\' of `%3%\' in %4% is not aligned"),
				"texrtn", TSK.TEXRTN[tskid], tskid, "DEF_TEX")$$END$
		$END$
		$tinib = tinib + sizeof_TINIB$
	$END$

$	// �����ϥ�ɥ����Ƭ���ϤΥ����å�
	$cycinib = SYMBOL("_kernel_cycinib_table")$
	$FOREACH cycid CYC.ID_LIST$
		$cychdr = PEEK(cycinib + offsetof_CYCINIB_cychdr, 4)$
		$IF CHECK_FUNC_ALIGN && (cychdr & (CHECK_FUNC_ALIGN - 1)) != 0$
			$ERROR CYC.TEXT_LINE[cycid]$E_PAR: 
				$FORMAT(_("%1% `%2%\' of `%3%\' in %4% is not aligned"),
				"cychdr", CYC.CYCHDR[cycid], cycid, "CRE_CYC")$$END$
		$END$
		$IF CHECK_FUNC_NONNULL && cychdr == 0$
			$ERROR CYC.TEXT_LINE[cycid]$E_PAR: 
				$FORMAT(_("%1% `%2%\' of `%3%\' in %4% is null"),
				"cychdr", CYC.CYCHDR[cycid], cycid, "CRE_CYC")$$END$
		$END$
		$cycinib = cycinib + sizeof_CYCINIB$
	$END$

$	// ���顼��ϥ�ɥ����Ƭ���ϤΥ����å�
	$alminib = SYMBOL("_kernel_alminib_table")$
	$FOREACH almid ALM.ID_LIST$
		$almhdr = PEEK(alminib + offsetof_ALMINIB_almhdr, 4)$
		$IF CHECK_FUNC_ALIGN && (almhdr & (CHECK_FUNC_ALIGN - 1)) != 0$
			$ERROR ALM.TEXT_LINE[almid]$E_PAR: 
				$FORMAT(_("%1% `%2%\' of `%3%\' in %4% is not aligned"),
				"almhdr", ALM.ALMHDR[almid], almid, "CRE_ALM")$$END$
		$END$
		$IF CHECK_FUNC_NONNULL && almhdr == 0$
			$ERROR ALM.TEXT_LINE[almid]$E_PAR: 
				$FORMAT(_("%1% `%2%\' of `%3%\' in %4% is null"),
				"almhdr", ALM.ALMHDR[almid], almid, "CRE_ALM")$$END$
		$END$
		$alminib = alminib + sizeof_ALMINIB$
	$END$
$END$

$
$  �����å��ΰ����Ƭ���ϤΥ����å�
$
$IF CHECK_STACK_ALIGN || CHECK_STACK_NONNULL$
	$tinib = SYMBOL("_kernel_tinib_table")$
	$FOREACH tskid TSK.ID_LIST$
$		// �������Υ����ƥॹ���å��ΰ����Ƭ���ϤΥ����å�
		$IF USE_TSKINICTXB$
			$sstk = GET_SSTK_TSKINICTXB(tinib)$
		$ELSE$
			$sstk = PEEK(tinib + offsetof_TINIB_sstk, sizeof_void_ptr)$
		$END$
		$IF CHECK_STACK_ALIGN && (sstk & (CHECK_STACK_ALIGN - 1)) != 0$
			$IF TSK.DOMAIN[tskid] == TDOM_KERNEL$
				$ERROR TSK.TEXT_LINE[tskid]$E_PAR: 
					$FORMAT(_("%1% `%2%\' of `%3%\' in %4% is not aligned"),
					"stk", TSK.STK[tskid], tskid, "CRE_TSK")$$END$
			$ELSE$
				$ERROR TSK.TEXT_LINE[tskid]$E_PAR: 
					$FORMAT(_("%1% `%2%\' of `%3%\' in %4% is not aligned"),
					"sstk", TSK.SSTK[tskid], tskid, "CRE_TSK")$$END$
			$END$
		$END$
		$IF CHECK_STACK_NONNULL && sstk == 0$
			$IF TSK.DOMAIN[tskid] == TDOM_KERNEL$
				$ERROR TSK.TEXT_LINE[tskid]$E_PAR: 
					$FORMAT(_("%1% `%2%\' of `%3%\' in %4% is null"),
					"stk", TSK.STK[tskid], tskid, "CRE_TSK")$$END$
			$ELSE$
				$ERROR TSK.TEXT_LINE[tskid]$E_PAR: 
					$FORMAT(_("%1% `%2%\' of `%3%\' in %4% is null"),
					"sstk", TSK.SSTK[tskid], tskid, "CRE_TSK")$$END$
			$END$
		$END$

$		// �������Υ桼�������å��ΰ����Ƭ���ϤΥ����å�
		$IF TSK.DOMAIN[tskid] != TDOM_KERNEL$
			$IF USE_TSKINICTXB$
				$ustk = GET_USTK_TSKINICTXB(tinib)$
			$ELSE$
				$ustk = PEEK(tinib + offsetof_TINIB_ustk, sizeof_void_ptr)$
			$END$
			$IF CHECK_USTACK_ALIGN && (ustk & (CHECK_USTACK_ALIGN - 1)) != 0$
				$ERROR TSK.TEXT_LINE[tskid]$E_PAR: 
					$FORMAT(_("%1% `%2%\' of `%3%\' in %4% is not aligned"),
					"stk", TSK.STK[tskid], tskid, "CRE_TSK")$$END$
			$END$
			$IF CHECK_USTACK_NONNULL && ustk == 0$
				$ERROR TSK.TEXT_LINE[tskid]$E_PAR: 
					$FORMAT(_("%1% `%2%\' of `%3%\' in %4% is null"),
					"stk", TSK.STK[tskid], tskid, "CRE_TSK")$$END$
			$END$
		$END$

		$tinib = tinib + sizeof_TINIB$
	$END$

$	// �󥿥�������ƥ������ѤΥ����å��ΰ����Ƭ���ϤΥ����å�
	$istk = PEEK(SYMBOL("_kernel_istk"), sizeof_void_ptr)$
	$IF CHECK_STACK_ALIGN && (istk & (CHECK_STACK_ALIGN - 1)) != 0$
		$ERROR ICS.TEXT_LINE[1]$E_PAR: 
			$FORMAT(_("%1% `%2%\' in %3% is not aligned"),
			"istk", ICS.ISTK[1], "DEF_ICS")$$END$
	$END$
	$IF CHECK_STACK_NONNULL && istk == 0$
		$ERROR ICS.TEXT_LINE[1]$E_PAR: 
			$FORMAT(_("%1% `%2%\' in %3% is null"),
			"istk", ICS.ISTK[1], "DEF_ICS")$$END$
	$END$
$END$

$
$  ����Ĺ����ס����ΰ����Ƭ���ϤΥ����å�
$
$IF CHECK_MPF_ALIGN || CHECK_MPF_NONNULL$
$	// ����Ĺ����ס����ΰ����Ƭ���ϤΥ����å�
	$mpfinib = SYMBOL("_kernel_mpfinib_table")$
	$FOREACH mpfid MPF.ID_LIST$
		$mpf = PEEK(mpfinib + offsetof_MPFINIB_mpf, sizeof_void_ptr)$
		$IF CHECK_MPF_ALIGN && (mpf & (CHECK_MPF_ALIGN - 1)) != 0$
			$ERROR MPF.TEXT_LINE[mpfid]$E_PAR: 
				$FORMAT(_("%1% `%2%\' of `%3%\' in %4% is not aligned"),
				"mpf", MPF.MPF[mpfid], mpfid, "CRE_MPF")$$END$
		$END$
		$IF CHECK_MPF_NONNULL && mpf == 0$
			$ERROR MPF.TEXT_LINE[mpfid]$E_PAR: 
				$FORMAT(_("%1% `%2%\' of `%3%\' in %4% is null"),
				"mpf", MPF.MPF[mpfid], mpfid, "CRE_MPF")$$END$
		$END$
		$mpfinib = mpfinib + sizeof_MPFINIB$
	$END$
$END$
