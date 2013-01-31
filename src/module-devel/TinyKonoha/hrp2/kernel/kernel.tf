$ ======================================================================
$
$   TOPPERS/HRP Kernel
$       Toyohashi Open Platform for Embedded Real-Time Systems/
$       High Reliable system Profile Kernel
$
$   Copyright (C) 2007 by TAKAGI Nobuhisa
$   Copyright (C) 2007-2012 by Embedded and Real-Time Systems Laboratory
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
$   $Id: kernel.tf 837 2012-12-26 15:09:59Z ertl-hiro $
$
$ =====================================================================

$ =====================================================================
$ kernel_cfg.h������
$ =====================================================================

$ ��ĥ�����ӥ��������ֹ�κ����ͤ�tmax_fncd�˵���
$tmax_fncd = 0$
$FOREACH order SVC.ORDER_LIST$
	$IF SVC.FNCD[order] > tmax_fncd$
		$tmax_fncd = SVC.FNCD[order]$
	$END$
$END$

$FILE "kernel_cfg.h"$
/* kernel_cfg.h */$NL$
#ifndef TOPPERS_KERNEL_CFG_H$NL$
#define TOPPERS_KERNEL_CFG_H$NL$
$NL$
#define TNUM_DOMID	$LENGTH(DOM.ID_LIST)$$NL$
#define TNUM_TSKID	$LENGTH(TSK.ID_LIST)$$NL$
#define TNUM_SEMID	$LENGTH(SEM.ID_LIST)$$NL$
#define TNUM_FLGID	$LENGTH(FLG.ID_LIST)$$NL$
#define TNUM_DTQID	$LENGTH(DTQ.ID_LIST)$$NL$
#define TNUM_PDQID	$LENGTH(PDQ.ID_LIST)$$NL$
#define TNUM_MTXID	$LENGTH(MTX.ID_LIST)$$NL$
#define TNUM_MPFID	$LENGTH(MPF.ID_LIST)$$NL$
#define TNUM_CYCID	$LENGTH(CYC.ID_LIST)$$NL$
#define TNUM_ALMID	$LENGTH(ALM.ID_LIST)$$NL$
$NL$
#define TMAX_FNCD	$tmax_fncd$$NL$
$NL$
$FOREACH id DOM.ID_LIST$
	#define $id$	$+id$$NL$
$END$
$FOREACH id TSK.ID_LIST$
	#define $id$	$+id$$NL$
$END$
$FOREACH id SEM.ID_LIST$
	#define $id$	$+id$$NL$
$END$
$FOREACH id FLG.ID_LIST$
	#define $id$	$+id$$NL$
$END$
$FOREACH id DTQ.ID_LIST$
	#define $id$	$+id$$NL$
$END$
$FOREACH id PDQ.ID_LIST$
	#define $id$	$+id$$NL$
$END$
$FOREACH id MTX.ID_LIST$
	#define $id$	$+id$$NL$
$END$
$FOREACH id MPF.ID_LIST$
	#define $id$	$+id$$NL$
$END$
$FOREACH id CYC.ID_LIST$
	#define $id$	$+id$$NL$
$END$
$FOREACH id ALM.ID_LIST$
	#define $id$	$+id$$NL$
$END$
$NL$
#endif /* TOPPERS_KERNEL_CFG_H */$NL$

$ =====================================================================
$ �ݸ�ɥᥤ��˴ؤ���������
$ =====================================================================

$
$  �ݸ�ɥᥤ��ꥹ�Ȥκ���
$	DOMLIST���桼���ɥᥤ��Υꥹ��
$	DOMLIST_ALL�������ͥ�ɥᥤ�󡤥桼���ɥᥤ��̵��°�Υꥹ��
$
$FOREACH domid DOM.ID_LIST$
	$DOMLIST = APPEND(DOMLIST, domid)$
$END$
$DOMLIST_ALL = APPEND(TDOM_KERNEL, DOMLIST, TDOM_NONE)$

$
$  �ݸ�ɥᥤ����Υǥե���ȤΥ����������ĥѥ�����κ���
$
$DEFAULT_ACPTN[TDOM_KERNEL] = VALUE("TACP_KERNEL", TACP_KERNEL)$
$FOREACH domid DOM.ID_LIST$
	$DEFAULT_ACPTN[domid] = VALUE(FORMAT("TACP(%1%)", domid), 1 << (domid - 1))$
$END$
$DEFAULT_ACPTN[TDOM_NONE] = VALUE("TACP_SHARED", TACP_SHARED)$

$
$  �ݸ�ɥᥤ����Υǥե���ȤΥ����������ĥ٥�����ʸ����ˤκ���
$
$FOREACH domid DOMLIST_ALL$
	$DEFAULT_ACVCT[domid] = FORMAT(" { %1%, %1%, %1%, %1% }",
											DEFAULT_ACPTN[domid])$
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

$ =====================================================================
$ ���ꥪ�֥������Ȥ˴ؤ���������
$
$ �������Υ��ꥪ�֥������Ȥξ����MO.XXXX[moid]���������롥
$
$ nummo���������Υ��ꥪ�֥������Ȥο�
$ MO.TYPE[moid]�����ꥪ�֥������ȤΥ�����
$	TOPPERS_ATTMOD��ATT_MOD��ATA_MOD����Ͽ���줿���������
$					�⥸�塼��̾��MO.MODULE[moid]������
$	TOPPERS_ATTSEC��ATT_SEC��ATA_SEC����Ͽ���줿���������
$	TOPPERS_ATTMEM��ATT_MEM��ATA_MEM��ATT_PMA��ATA_PMA����Ͽ���줿���������
$					��Ƭ���Ϥ�MO.BASE[moid]������
$					��������MO.SIZE[moid]������
$					ʪ�����ɥ쥹��MO.PADDR[moid]�������ATT_PMA��ATA_PMA�λ���
$	TOPPERS_USTACK���������Υ桼�������å��ΰ�ʥ�åɥ����������ξ��Υ�
$					�ߡ������å��ΰ�⤳�Υ����ס�
$					������ID��MO.TSKID[moid]������ʥ��ߡ������å��ΰ�ξ�
$					���0��
$					��Ƭ���Ϥ�MO.BASE[moid]������ʥ桼�������å��ΰ��
$					�ץꥱ������󤬻��ꤷ�����Τߡ�
$					��������MO.SIZE[moid]������
$	TOPPERS_MPFAREA������Ĺ����ס����ΰ�ʥ���ե�����졼��������դ�
$					 ����Τߡ�
$					 ����Ĺ����ס���ID��MO.MPFID[moid]������
$ MO.LINKER[moid]����󥫤����֤�����ꥪ�֥������Ȥ���
$ MO.DOMAIN[moid]��°����ɥᥤ���̵��°�ξ���TDOM_NONE��
$ MO.MEMREG[moid]������꡼������ֹ�ʥ�󥫤����֤�����Τߡ�
$ MO.SECTION[moid]�����������̾�ʥ�󥫤����֤�����Τߡ�
$ MO.MEMATR[moid]�����ꥪ�֥�������°��
$ MO.ACPTN1[moid]���̾����1�ʽ���ߡˤΥ����������ĥѥ�����
$ MO.ACPTN2[moid]���̾����2���ɽФ����¹ԡˤΥ����������ĥѥ�����
$ MO.ACPTN4[moid]���������Υ����������ĥѥ�����
$ MO.TEXT_LINE[moid]�����ꥪ�֥������Ȥ���Ͽ������ŪAPI�ι��ֹ�
$ MO.APINAME[moid]�����ꥪ�֥������Ȥ���Ͽ������ŪAPI��̾��
$ MO_USTACK_LIST������ե�����졼��������դ���桼�������å��ΰ�Υꥹ��
$ =====================================================================

$TOPPERS_ATTMOD = TOPPERS_ATTSEC + 1$
$TOPPERS_MPFAREA = TOPPERS_ATTSEC + 2$
$nummo = 0$
$MO_USTACK_LIST = {}$

$
$  ���֤��륻�������˴ؤ���������
$
$ LNK_SEC�����֤��륻�������ʥ��ꥪ�֥������ȤȤ�����Ͽ���ʤ��ˤξ�
$ ���LNKSEC[lsid]���������롥
$
$ numls�����֤��륻�������ο�
$ LNKSEC.MEMREG[lsid]������꡼������ֹ�
$ LNKSEC.SECTION[lsid]�����������̾

$numls = 0$

$
$  ATT_REG����Ͽ���줿�꡼�����˴ؤ��륨�顼�����å���������
$
$ REG_LIST�������ѤߤΥ���꡼�����Υꥹ��
$ REG.REGNAME[reg]������꡼�����̾�ʡ�UNESCSTR(MO.REGION[reg])��
$
$FOREACH reg REG.ORDER_LIST$
$	// REG.REGNAME[reg]�κ���
	$REG.REGNAME[reg] = UNESCSTR(REG.REGION[reg])$

$	// ����꡼�����̾����Ͽ�Ѥߤξ���E_OBJ��
	$FOREACH reg2 REG_LIST$
		$IF EQ(REG.REGNAME[reg], REG.REGNAME[reg2])$
			$ERROR REG.TEXT_LINE[reg]$E_OBJ: $FORMAT(_("%1% `%2%\' in %3% is duplicated"), "memory region", REG.REGNAME[reg], "ATT_REG")$$END$
		$END$
	$END$

$	// regatr���ʡ�TA_NOWRITE�ϡˤǤʤ�����E_RSATR��
	$IF (REG.REGATR[reg] & ~(TA_NOWRITE|TARGET_REGATR)) != 0$
		$ERROR REG.TEXT_LINE[reg]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' in %3%"), "regatr", REG.REGATR[reg], "ATT_REG")$$END$
	$END$

$	// �ݸ�ɥᥤ��˽�°���Ƥ������E_RSATR��
	$IF LENGTH(REG.DOMAIN[reg])$
		$ERROR REG.TEXT_LINE[reg]$E_RSATR: $FORMAT(_("%1% `%2%\' belongs to a protection domain in %3%"), "memory region", REG.REGNAME[reg], "ATT_REG")$$END$
	$END$

$	// size��0�ξ���E_PAR��
	$IF REG.SIZE[reg] == 0$
		$ERROR REG.TEXT_LINE[reg]$E_PAR: $FORMAT(_("%1% `%2%\' is zero in %3%"), "size", REG.SIZE[reg], "ATT_REG")$$END$
	$END$

$	// base+size�����祢�ɥ쥹��ۤ������E_PAR��
	$limit = (REG.BASE[reg] + REG.SIZE[reg]) & ((1 << sizeof_void_ptr * 8) - 1)$
	$IF limit < REG.BASE[reg] && limit != 0$
		$ERROR REG.TEXT_LINE[reg]$E_PAR: $FORMAT(_("%1% `%2%\' is too large in %3%"), "size", REG.SIZE[reg], "ATT_REG")$$END$
	$END$

$	// ��Ͽ�ѤߤΥ���꡼�������ΰ褬�Ťʤ����E_OBJ��
	$FOREACH reg2 REG_LIST$
		$IF ((REG.BASE[reg] <= REG.BASE[reg2]
						&& REG.BASE[reg] + REG.SIZE[reg] > REG.BASE[reg2])
		  || (REG.BASE[reg2] < REG.BASE[reg]
						&& REG.BASE[reg2] + REG.SIZE[reg2] > REG.BASE[reg]))$
			$ERROR REG.TEXT_LINE[reg]$E_OBJ: $FORMAT(_("%1% `%2%\' overlaps with another %1% `%3%\'"), "memory region", REG.REGNAME[reg], REG.REGNAME[reg2])$$END$
		$END$
	$END$

$	// �������åȰ�¸�Υ��顼�����å�
	$IF ISFUNCTION("HOOK_ERRORCHECK_REG")$
		$HOOK_ERRORCHECK_REG(reg)$
	$END$
	$REG_LIST = APPEND(REG_LIST, reg)$
$END$

$ REG_ORDER������
$REG_ORDER = SORT(REG.ORDER_LIST, "REG.BASE")$

$
$  DEF_SRG��������줿ɸ�����꡼�����˴ؤ��륨�顼�����å���������
$
$ STANDARD_ROM��ɸ��ROM�꡼�����Υ���꡼������ֹ�
$ STANDARD_RAM��ɸ��RAM�꡼�����Υ���꡼������ֹ�
$
$IF !LENGTH(SRG.ORDER_LIST)$
$	// DEF_SRG���ʤ����ϡ������ǽ�����ߤ��ʰʹߤΥ��顼���޻ߡ�
$	//��NGKI3259��
	$ERROR$$FORMAT(_("no standard memory region is defined"))$$END$
	$DIE()$
$ELSE$
$	// �ݸ�ɥᥤ��ΰϤߤ���˵��Ҥ���Ƥ������E_RSATR�ˡ�NGKI3262�� 
	$IF LENGTH(SRG.DOMAIN[1])$
		$ERROR SEG.TEXT_LINE[1]$E_RSATR: $FORMAT(_("%1% must be outside of protection domains"), "DEF_SRG")$$END$
	$END$

$	// ��ŪAPI��DEF_SRG�פ�ʣ�������E_OBJ�ˡ�NGKI3263��
	$IF LENGTH(SRG.ORDER_LIST) > 1$
		$ERROR$E_OBJ: $FORMAT(_("too many %1%"), "DEF_SRG")$$END$
	$END$

$	// stdrom����Ͽ����Ƥ��뤫�Υ����å���E_OBJ�ˡ�NGKI3264��
	$STANDARD_ROM = 0$
	$FOREACH reg REG.ORDER_LIST$
		$IF EQ(UNESCSTR(SRG.STDROM[1]), REG.REGNAME[reg])$
			$STANDARD_ROM = reg$
		$END$
	$END$
	$IF STANDARD_ROM == 0$
		$ERROR SRG.TEXT_LINE[1]$E_OBJ: 
			$FORMAT(_("illegal %1% `%2%\' in %3%"), "region name", UNESCSTR(SRG.STDROM[1]), "DEF_SRG")$
		$END$
	$END$

$	// stdrom��TA_NOWRITE°�����Υ����å���E_OBJ�ˡ�NGKI3268��
	$IF (REG.REGATR[STANDARD_ROM] & TA_NOWRITE) == 0$
		$ERROR SRG.TEXT_LINE[1]$E_OBJ: $FORMAT(_("standard ROM region must have TA_NOWRITE attribute"))$$END$
	$END$

$	// stdram����Ͽ����Ƥ��뤫�Υ����å���E_OBJ�ˡ�NGKI3272��
	$STANDARD_RAM = 0$
	$FOREACH reg REG.ORDER_LIST$
		$IF EQ(UNESCSTR(SRG.STDRAM[1]), REG.REGNAME[reg])$
			$STANDARD_RAM = reg$
		$END$
	$END$
	$IF STANDARD_RAM == 0$
		$ERROR SRG.TEXT_LINE[1]$E_OBJ: 
			$FORMAT(_("illegal %1% `%2%\' in %3%"), "region name", UNESCSTR(SRG.STDRAM[1]), "DEF_SRG")$
		$END$
	$END$

$	// stdram��TA_NOWRITE°���Ǥʤ����Υ����å���E_OBJ�ˡ�NGKI3270��
	$IF (REG.REGATR[STANDARD_RAM] & TA_NOWRITE) != 0$
		$ERROR SRG.TEXT_LINE[1]$E_OBJ: $FORMAT(_("standard RAM region must not have TA_NOWRITE attribute"))$$END$
	$END$

$	// �ɤ��餫�����顼�ξ��ϡ������ǽ�����ߤ��ʰʹߤΥ��顼���޻ߡ�
	$IF STANDARD_ROM==0 || STANDARD_RAM==0$
		$DIE()$
	$END$
$END$

$
$  ɸ��Υ��������������ɸ�ॻ�������Υꥹ�Ȥκ���
$
$ DSEC_SECTION_LIST��ɸ��Υ����������ݸ�ɥᥤ����ɸ�ॻ�������Υꥹ��
$
$DEFINE_DSEC()$

$FOREACH dsec DSEC.ORDER_LIST$
	$DSEC_SECTION_LIST = APPEND(DSEC_SECTION_LIST, DSEC.SECTION[dsec])$
$END$
$FOREACH domid DOMLIST_ALL$
	$FOREACH dsec DSEC.ORDER_LIST$
		$DSEC_SECTION_LIST = APPEND(DSEC_SECTION_LIST,
					FORMAT("%s_%s", DSEC.SECTION[dsec], DOM.LABEL[domid]))$
	$END$
$END$

$
$  ATT_MOD�����Τ�Ʊ���˰����⥸�塼��ν���
$
$ ��Ƭ��ATT_MOD�����Τ�Ʊ����START_OBJS, libkernel.o, kernel_mem.o, libkernel.a
$ ������ATT_MOD�����Τ�Ʊ����*, END_OBJS
$
$IF TOPPERS_SUPPORT_ATT_MOD$
	$nummod = LENGTH(MOD.ORDER_LIST)$

	$FUNCTION ATT_MOD_FIRST$
		$nummod = nummod + 1$
		$MOD.ORDER_LIST = APPEND(nummod, MOD.ORDER_LIST)$
		$MOD.MODULE[nummod] = ESCSTR(ARGV[1])$
		$MOD.DOMAIN[nummod] = ARGV[2]$
		$MOD.TEXT_LINE[nummod] = 0$
	$END$
 
	$FUNCTION ATT_MOD_LAST$
		$nummod = nummod + 1$
		$MOD.ORDER_LIST = APPEND(MOD.ORDER_LIST, nummod)$
		$MOD.MODULE[nummod] = ESCSTR(ARGV[1])$
		$MOD.DOMAIN[nummod] = ARGV[2]$
		$MOD.TEXT_LINE[nummod] = 0$
	$END$

	$FOREACH module APPEND("libkernel.a", "kernel_mem.o", "kernel_cfg.o",
															START_OBJS)$
		$ATT_MOD_FIRST(module, TDOM_KERNEL)$
	$END$

	$ATT_MOD_LAST("*", TDOM_NONE)$
	$FOREACH module END_OBJS$
		$ATT_MOD_LAST(module, TDOM_KERNEL)$
	$END$
$END$

$
$  ATT_MOD��ATA_MOD����Ͽ���줿�⥸�塼��˴ؤ�����������
$
$ MOD_LIST�������ѤߤΥ⥸�塼��Υꥹ��
$
$FOREACH mod MOD.ORDER_LIST$
$	// ATT_MOD/ATA_MOD�����ݡ��Ȥ���Ƥ��ʤ�����E_NOSPT��
	$IF !TOPPERS_SUPPORT_ATT_MOD$
		$ERROR MOD.TEXT_LINE[mod]$E_NOSPT: $FORMAT(_("%1% is not supported on this target"), MOD.APINAME[mod])$$END$
	$END$

$	// module����Ͽ�Ѥߤξ���E_OBJ��
	$FOREACH mod2 MOD_LIST$
		$IF EQ(MOD.MODULE[mod], MOD.MODULE[mod2])$
			$ERROR MOD.TEXT_LINE[mod]$E_OBJ: $FORMAT(_("%1% `%2%\' in %3% is duplicated"), "module", UNESCSTR(MOD.MODULE[mod]), MOD.APINAME[mod])$$END$
		$END$
	$END$

$	// �������åȰ�¸�Υ��顼�����å�
	$IF ISFUNCTION("HOOK_ERRORCHECK_MOD")$
		$HOOK_ERRORCHECK_MOD(mod)$
	$END$

$	// ���ꥪ�֥������Ⱦ��������
	$FOREACH dsec DSEC.ORDER_LIST$
		$nummo = nummo + 1$
		$MO.TYPE[nummo] = TOPPERS_ATTMOD$
		$MO.MODULE[nummo] = UNESCSTR(MOD.MODULE[mod])$
		$MO.LINKER[nummo] = 1$
		$IF EQ(MOD.DOMAIN[mod], "")$
			$MO.DOMAIN[nummo] = TDOM_NONE$
		$ELSE$
			$MO.DOMAIN[nummo] = MOD.DOMAIN[mod]$
		$END$
		$MO.MEMREG[nummo] = DSEC.MEMREG[dsec]$
		$MO.SECTION[nummo] = DSEC.SECTION[dsec]$
		$MO.MEMATR[nummo] = DSEC.MEMATR[dsec]$

		$domptn = DEFAULT_ACPTN[MO.DOMAIN[nummo]]$
		$MO.ACPTN1[nummo] = ALT(MOD.ACPTN1[mod], domptn)$
		$MO.ACPTN2[nummo] = ALT(MOD.ACPTN2[mod], domptn)$
		$MO.ACPTN4[nummo] = ALT(MOD.ACPTN4[mod], domptn)$
		$MO.TEXT_LINE[nummo] = MOD.TEXT_LINE[mod]$
		$MO.APINAME[nummo] = MOD.APINAME[mod]$
	$END$
	$MOD_LIST = APPEND(MOD_LIST, mod)$
$END$

$
$  ATT_SEC��ATA_SEC��LNK_SEC����Ͽ���줿���������˴ؤ�����������
$
$ SEC_LIST�������ѤߤΥ��������Υꥹ��
$
$FOREACH sec SEC.ORDER_LIST$
$	// section��ɸ��Υ��������ξ���E_PAR��
	$IF TOPPERS_SUPPORT_ATT_MOD || !LENGTH(SEC.MEMATR[sec])$
		$IF LENGTH(FIND(DSEC_SECTION_LIST, UNESCSTR(SEC.SECTION[sec])))$
			$ERROR SEC.TEXT_LINE[sec]$E_PAR: 
				$FORMAT(_("default section `%1%\' cannot be attached with %2%"), UNESCSTR(SEC.SECTION[sec]), SEC.APINAME[sec])$
			$END$
		$END$
	$END$

$	// section����Ͽ�Ѥߤξ���E_OBJ��
	$FOREACH sec2 SEC_LIST$
		$IF EQ(SEC.SECTION[sec], SEC.SECTION[sec2])$
			$ERROR SEC.TEXT_LINE[sec]$E_OBJ: 
				$FORMAT(_("%1% `%2%\' in %3% is duplicated"), "section", UNESCSTR(SEC.SECTION[sec]), SEC.APINAME[sec])$
			$END$
		$END$
	$END$

$	// memreg�Υ����å���E_OBJ��
	$memreg = 0$
	$FOREACH reg REG.ORDER_LIST$
		$IF EQ(UNESCSTR(SEC.MEMREG[sec]), REG.REGNAME[reg])$
			$memreg = reg$
		$END$
	$END$
	$IF memreg == 0$
		$ERROR SEC.TEXT_LINE[sec]$E_OBJ: 
			$FORMAT(_("illegal %1% `%2%\' in %3%"), "region name", UNESCSTR(SEC.MEMREG[sec]), SEC.APINAME[sec])$
		$END$
$		// �ʹߤΥ��顼���޻�
		$memreg = STANDARD_RAM$
	$END$

	$IF LENGTH(SEC.MEMATR[sec])$
$		// ATT_SEC��ATA_SEC�ξ��

$		// mematr���ʡ�TA_NOWRITE|TA_NOREAD|TA_EXEC|TA_MEMINI|TA_MEMPRSV|TA_SDATA|TA_UNCACHE|TA_IODEV�ϡˤǤʤ�����E_RSATR��
$		// mematr��TA_MEMINI��TA_MEMPRSV��ξ������ꤷ������TA_RSATR��
		$IF (SEC.MEMATR[sec] & ~(TA_NOWRITE|TA_NOREAD|TA_EXEC|TA_MEMINI|TA_MEMPRSV|TA_SDATA|TA_UNCACHE|TA_IODEV|TARGET_MEMATR)) != 0
			|| (SEC.MEMATR[sec] & (TA_MEMINI|TA_MEMPRSV)) == (TA_MEMINI|TA_MEMPRSV)$
			$ERROR SEC.TEXT_LINE[sec]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' in %3%"), "mematr", SEC.MEMATR[sec], SEC.APINAME[sec])$$END$
		$END$

$		// �������åȰ�¸�Υ��顼�����å�
		$IF ISFUNCTION("HOOK_ERRORCHECK_SEC")$
			$HOOK_ERRORCHECK_SEC(sec)$
		$END$

$		// ���ꥪ�֥������Ⱦ��������
		$nummo = nummo + 1$
		$MO.TYPE[nummo] = TOPPERS_ATTSEC$
		$MO.LINKER[nummo] = 1$
		$IF EQ(SEC.DOMAIN[sec], "")$
			$MO.DOMAIN[nummo] = TDOM_NONE$
		$ELSE$
			$MO.DOMAIN[nummo] = SEC.DOMAIN[sec]$
		$END$
		$MO.MEMREG[nummo] = memreg$
		$MO.SECTION[nummo] = UNESCSTR(SEC.SECTION[sec])$
		$IF (REG.REGATR[memreg] & TA_NOWRITE) != 0$
$			// ����꡼�����°����TA_NOWRITE�����ꤵ��Ƥ�����ϡ�
$			// ���ꥪ�֥�������°����TA_NOWRITE�����ꤹ�롥
			$MO.MEMATR[nummo] = SEC.MEMATR[sec] | TA_NOWRITE$
		$ELSE$
			$MO.MEMATR[nummo] = SEC.MEMATR[sec]$
		$END$

		$domptn = DEFAULT_ACPTN[MO.DOMAIN[nummo]]$
		$MO.ACPTN1[nummo] = ALT(SEC.ACPTN1[sec], domptn)$
		$MO.ACPTN2[nummo] = ALT(SEC.ACPTN2[sec], domptn)$
		$MO.ACPTN4[nummo] = ALT(SEC.ACPTN4[sec], domptn)$
		$MO.TEXT_LINE[nummo] = SEC.TEXT_LINE[sec]$
		$MO.APINAME[nummo] = SEC.APINAME[sec]$
	$ELSE$
$		// LNK_SEC�ξ��

$		// ���֤��륻���������������
		$numls = numls + 1$
		$LNKSEC.MEMREG[numls] = memreg$
		$LNKSEC.SECTION[numls] = UNESCSTR(SEC.SECTION[sec])$
	$END$
	$SEC_LIST = APPEND(SEC_LIST, sec)$
$END$

$
$  �ݸ�ɥᥤ�����ɸ�ॻ�������˴ؤ�����������
$
$FOREACH domid DOMLIST_ALL$
	$FOREACH dsec DSEC.ORDER_LIST$
$		// ���ꥪ�֥������Ⱦ��������
		$nummo = nummo + 1$
		$MO.TYPE[nummo] = TOPPERS_ATTSEC$
		$MO.LINKER[nummo] = 1$
		$MO.DOMAIN[nummo] = domid$
		$MO.MEMREG[nummo] = DSEC.MEMREG[dsec]$
		$MO.SECTION[nummo] = FORMAT("%s_%s", DSEC.SECTION[dsec], DOM.LABEL[domid])$
		$MO.MEMATR[nummo] = DSEC.MEMATR[dsec]$

		$domptn = DEFAULT_ACPTN[domid]$
		$MO.ACPTN1[nummo] = domptn$
		$MO.ACPTN2[nummo] = domptn$
		$MO.ACPTN4[nummo] = domptn$
	$END$
$END$

$
$  ATT_MEM��ATA_MEM��ATT_PMA��ATA_PMA����Ͽ���줿���������˴ؤ�����������
$
$FOREACH mem MEM.ORDER_LIST$
$	// ��ŪAPI��̾�Τ�����
	$IF LENGTH(MEM.PADDR[mem])$
$		// ATT_PMA��ATA_PMA����Ѥ������Υ��顼�����å���E_NOSPT��
		$IF !TOPPERS_SUPPORT_ATT_PMA$
			$ERROR MEM.TEXT_LINE[mem]$E_NOSPT: $FORMAT(_("%1% is not supported on this target"), MEM.APINAME[mem])$$END$
		$END$
	$END$

$	// mematr���ʡ�TA_NOWRITE|TA_NOREAD|TA_EXEC|TA_MEMINI|TA_MEMPRSV|TA_SDATA|TA_UNCACHE|TA_IODEV�ϡˤǤʤ�����E_RSATR��
$	// mematr��TA_MEMPRSV����ꤷ�ʤ���TA_MEMINI����ꤷ������TA_RSATR��
	$IF (MEM.MEMATR[mem] & ~(TA_NOWRITE|TA_NOREAD|TA_EXEC|TA_MEMINI|TA_MEMPRSV|TA_UNCACHE|TA_IODEV|TARGET_MEMATR)) != 0
		|| (MEM.MEMATR[mem] & (TA_MEMINI|TA_MEMPRSV)) != TA_MEMPRSV$
		$ERROR MEM.TEXT_LINE[mem]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' in %3%"), "mematr", MEM.MEMATR[mem], MEM.APINAME[mem])$$END$
	$END$

$	// size��0�ξ��
	$IF MEM.SIZE[mem] == 0$
		$ERROR MEM.TEXT_LINE[mem]$E_PAR: $FORMAT(_("%1% `%2%\' is zero in %3%"), "size", MEM.SIZE[mem], MEM.APINAME[mem])$$END$
	$END$

$	// �������åȰ�¸�Υ��顼�����å�
	$IF ISFUNCTION("HOOK_ERRORCHECK_MEM")$
		$HOOK_ERRORCHECK_MEM(mem)$
	$END$

$	// ���ꥪ�֥������Ⱦ��������
	$nummo = nummo + 1$
	$MO.TYPE[nummo] = TOPPERS_ATTMEM$
	$MO.BASE[nummo] = MEM.BASE[mem]$
	$MO.SIZE[nummo] = MEM.SIZE[mem]$
	$MO.PADDR[nummo] = MEM.PADDR[mem]$
	$MO.LINKER[nummo] = 0$
	$IF EQ(MEM.DOMAIN[mem], "")$
		$MO.DOMAIN[nummo] = TDOM_NONE$
	$ELSE$
		$MO.DOMAIN[nummo] = MEM.DOMAIN[mem]$
	$END$
	$MO.MEMATR[nummo] = MEM.MEMATR[mem]$

	$domptn = DEFAULT_ACPTN[MO.DOMAIN[nummo]]$
	$MO.ACPTN1[nummo] = ALT(MEM.ACPTN1[mem], domptn)$
	$MO.ACPTN2[nummo] = ALT(MEM.ACPTN2[mem], domptn)$
	$MO.ACPTN4[nummo] = ALT(MEM.ACPTN4[mem], domptn)$
	$MO.TEXT_LINE[nummo] = MEM.TEXT_LINE[mem]$
	$MO.APINAME[nummo] = MEM.APINAME[mem]$
$END$

$
$  �������åȰ�¸�Υ��ꥪ�֥������Ⱦ�������
$
$IF ISFUNCTION("HOOK_ADDITIONAL_MO")$
	$HOOK_ADDITIONAL_MO()$
$END$

$ =====================================================================
$ kernel_mem2.c�ζ�����ʬ������
$ =====================================================================

$FILE "kernel_mem2.c"$
/* kernel_mem2.c */$NL$
#include "kernel/kernel_int.h"$NL$
#include "kernel_cfg.h"$NL$
$NL$
#if TKERNEL_PRID != 0x06u$NL$
#error The kernel does not match this configuration file.$NL$
#endif$NL$
$NL$

/*$NL$
$SPC$*  Include Directives (#include)$NL$
$SPC$*/$NL$
$NL$
$INCLUDES$
$NL$

$ =====================================================================
$ kernel_cfg.c������
$ =====================================================================

$FILE "kernel_cfg.c"$
/* kernel_cfg.c */$NL$
#include "kernel/kernel_int.h"$NL$
#include "kernel_cfg.h"$NL$
$NL$
#if TKERNEL_PRID != 0x06u$NL$
#error "The kernel does not match this configuration file."$NL$
#endif$NL$
$NL$

$
$  ���󥯥롼�ɥǥ��쥯�ƥ��֡�#include��
$
/*$NL$
$SPC$*  Include Directives (#include)$NL$
$SPC$*/$NL$
$NL$
$INCLUDES$
$NL$

$
$  ���֥������Ȥ�ID�ֹ���ݻ������ѿ�
$
$IF USE_EXTERNAL_ID$
	/*$NL$
	$SPC$*  Variables for Object ID$NL$
	$SPC$*/$NL$
	$NL$
	$FOREACH id DOM.ID_LIST$
		const ID $id$_id$SPC$=$SPC$$+id$;$NL$
	$END$
	$FOREACH id TSK.ID_LIST$
		const ID $id$_id$SPC$=$SPC$$+id$;$NL$
	$END$
	$FOREACH id SEM.ID_LIST$
		const ID $id$_id$SPC$=$SPC$$+id$;$NL$
	$END$
	$FOREACH id FLG.ID_LIST$
		const ID $id$_id$SPC$=$SPC$$+id$;$NL$
	$END$
	$FOREACH id DTQ.ID_LIST$
		const ID $id$_id$SPC$=$SPC$$+id$;$NL$
	$END$
	$FOREACH id PDQ.ID_LIST$
		const ID $id$_id$SPC$=$SPC$$+id$;$NL$
	$END$
	$FOREACH id MTX.ID_LIST$
		const ID $id$_id$SPC$=$SPC$$+id$;$NL$
	$END$
	$FOREACH id MPF.ID_LIST$
		const ID $id$_id$SPC$=$SPC$$+id$;$NL$
	$END$
	$FOREACH id CYC.ID_LIST$
		const ID $id$_id$SPC$=$SPC$$+id$;$NL$
	$END$
	$FOREACH id ALM.ID_LIST$
		const ID $id$_id$SPC$=$SPC$$+id$;$NL$
	$END$
$END$

$
$  �ȥ졼�����ޥ���Υǥե�������
$
/*$NL$
$SPC$*  Default Definitions of Trace Log Macros$NL$
$SPC$*/$NL$
$NL$
#ifndef LOG_ISR_ENTER$NL$
#define LOG_ISR_ENTER(intno)$NL$
#endif /* LOG_ISR_ENTER */$NL$
$NL$
#ifndef LOG_ISR_LEAVE$NL$
#define LOG_ISR_LEAVE(intno)$NL$
#endif /* LOG_ISR_LEAVE */$NL$
$NL$

$
$  �ݸ�ɥᥤ��
$
/*$NL$
$SPC$*  Protection Domain Management Functions$NL$
$SPC$*/$NL$
$NL$

$ �ݸ�ɥᥤ��ID�ֹ�κ�����
const ID _kernel_tmax_domid = (TMIN_DOMID + TNUM_DOMID - 1);$NL$
$NL$

$ �ݸ�ɥᥤ����������ƥ����ȥ֥�å��Τ�������
$IF ISFUNCTION("PREPARE_DOMINICTXB")$
	$PREPARE_DOMINICTXB()$
$END$

$ �����ͥ�ɥᥤ����ݸ�ɥᥤ�������֥�å�������
const DOMINIB _kernel_dominib_kernel = { TACP_KERNEL
$IF USE_DOMINICTXB$
	, $DOMINICTXB_KERNEL$
$END$
$SPC$};$NL$
$NL$

$ �ݸ�ɥᥤ�������֥�å�������
$IF LENGTH(DOM.ID_LIST)$
	const DOMINIB _kernel_dominib_table[TNUM_DOMID] = {$NL$
	$JOINEACH domid DOM.ID_LIST ",\n"$
		$TAB${ TACP($domid$)
		$IF USE_DOMINICTXB$
			, $GENERATE_DOMINICTXB(domid)$
		$END$
		$SPC$}
	$END$$NL$
	};$NL$
	$NL$
$ELSE$
	TOPPERS_EMPTY_LABEL(const DOMINIB, _kernel_dominib_table);$NL$
$END$$NL$

$
$  �����ƥॹ���å��ΰ�γ��ݴؿ�
$
$IF !ISFUNCTION("ALLOC_SSTACK")$
$FUNCTION ALLOC_SSTACK$
	static STK_T $ARGV[1]$[COUNT_STK_T($ARGV[2]$)];$NL$
$END$
$END$

$
$  ������
$
/*$NL$
$SPC$*  Task Management Functions$NL$
$SPC$*/$NL$
$NL$

$ ��������1�İʾ�¸�ߤ��뤳�ȤΥ����å�
$IF !LENGTH(TSK.ID_LIST)$
	$ERROR$$FORMAT(_("no task is registered"))$$END$
$END$

$ ������ID�ֹ�κ�����
const ID _kernel_tmax_tskid = (TMIN_TSKID + TNUM_TSKID - 1);$NL$
$NL$

$ ���顼�����å�
$FOREACH tskid TSK.ID_LIST$
$	// �ݸ�ɥᥤ��˽�°���Ƥ��ʤ�����E_RSATR��
	$IF !LENGTH(TSK.DOMAIN[tskid])$
		$ERROR TSK.TEXT_LINE[tskid]$E_RSATR: $FORMAT(_("%1% `%2%\' must belong to a protection domain in %3%"), "task", tskid, "CRE_TSK")$$END$
$		// �ʹߤΥ��顼���޻�
		$TSK.DOMAIN[tskid] = TDOM_KERNEL$
	$END$

$	// tskatr���ʡ�TA_ACT�ϡˤǤʤ�����E_RSATR��
	$IF (TSK.TSKATR[tskid] & ~(TA_ACT|TARGET_TSKATR)) != 0$
		$ERROR TSK.TEXT_LINE[tskid]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "tskatr", TSK.TSKATR[tskid], tskid, "CRE_TSK")$$END$
	$END$

$	// (TMIN_TPRI <= itskpri && itskpri <= TMAX_TPRI)�Ǥʤ�����E_PAR��
	$IF !(TMIN_TPRI <= TSK.ITSKPRI[tskid] && TSK.ITSKPRI[tskid] <= TMAX_TPRI)$
		$ERROR TSK.TEXT_LINE[tskid]$E_PAR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "itskpri", TSK.ITSKPRI[tskid], tskid, "CRE_TSK")$$END$
	$END$

$ 	// texatr����TA_NULL�ˤǤʤ�����E_RSATR��
	$IF LENGTH(TSK.TEXATR[tskid]) && TSK.TEXATR[tskid] != 0$
		$ERROR DEF_TEX.TEXT_LINE[tskid]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "texatr", TSK.TEXATR[tskid], tskid, "DEF_TEX")$$END$
	$END$

$	// DEF_TEX��CRE_TSK�Ȱۤʤ��ݸ�ɥᥤ���°�������E_RSATR��
	$IF LENGTH(TSK.TEXATR[tskid]) && ALT(DEF_TEX.DOMAIN[tskid], TDOM_NONE) != TSK.DOMAIN[tskid]$
		$ERROR DEF_TEX.TEXT_LINE[tskid]$E_RSATR: $FORMAT(_("%1% for `%2%\' must belong to the same protection domain with %3%"), "DEF_TEX", tskid, "CRE_TSK")$$END$
	$END$

$	// SAC_TSK��CRE_TSK�Ȱۤʤ��ݸ�ɥᥤ���°�������E_RSATR��
	$IF LENGTH(TSK.ACPTN1[tskid]) && ALT(SAC_TSK.DOMAIN[tskid], TDOM_NONE) != TSK.DOMAIN[tskid]$
		$ERROR SAC_TSK.TEXT_LINE[tskid]$E_RSATR: $FORMAT(_("%1% for `%2%\' must belong to the same protection domain with %3%"), "SAC_TSK", tskid, "CRE_TSK")$$END$
	$END$
$END$

$  �����ƥॹ���å�����������0�Ǥ��뤫���������å�����κǾ���
$  ��TARGET_MIN_SSTKSZ�ˤ��⾮�������Υ��顼�����å��ؿ���E_PAR��
$FUNCTION CHECK_MIN_SSTKSZ$
	$IF ARGV[1] == 0 || (TARGET_MIN_SSTKSZ && ARGV[1] < TARGET_MIN_SSTKSZ)$
		$ERROR TSK.TEXT_LINE[tskid]$E_PAR: $FORMAT(_("%1% `%2%\' of `%3%\' in %4% is too small"), ARGV[2], ARGV[1], tskid, "CRE_TSK")$$END$
	$END$
$END$

$ �����ƥॹ���å��ΰ�������Ȥ���˴ؤ��륨�顼�����å�
$FOREACH tskid TSK.ID_LIST$
	$IF TSK.DOMAIN[tskid] == TDOM_KERNEL$
$		// �����ƥॿ�����ξ��ν���

$		// sstk����ά����Ƥ��餺��NULL�Ǥʤ�����E_PAR��
		$IF LENGTH(TSK.SSTK[tskid]) && !EQ(TSK.SSTK[tskid],"NULL")$
			$ERROR TSK.TEXT_LINE[tskid]$E_PAR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "sstk", TSK.SSTK[tskid], tskid, "CRE_TSK")$$END$
		$END$

$		// stksz��0�ξ���E_PAR��
		$IF TSK.STKSZ[tskid] == 0$
			$ERROR TSK.TEXT_LINE[tskid]$E_PAR: $FORMAT(_("%1% `%2%\' of `%3%\' in %4% is zero"), "stksz", TSK.STKSZ[tskid], tskid, "CRE_TSK")$$END$
		$END$

		$IF EQ(TSK.STK[tskid],"NULL")$
$			// stk��NULL�ξ��ν���

			$IF LENGTH(TSK.SSTKSZ[tskid])$
$				// sstksz����ά����Ƥ��ʤ����ν���

$				// �����ƥॹ���å��ΰ�Υ����������ʥ��顼�����å���
$				// �Ȥ����ᡤ���顼�����å������˵��Ƥ�����
				$sstksz = VALUE(FORMAT("(%1%) + (%2%)",
									TSK.STKSZ[tskid], TSK.SSTKSZ[tskid]),
								TSK.STKSZ[tskid]+TSK.SSTKSZ[tskid])$

$				// stksz+sstksz���������å�����κǾ��ͤ��⾮��������E_PAR��
				$CHECK_MIN_SSTKSZ(sstksz, "stksz+sstksz")$
			$ELSE$
$				// sstksz����ά����Ƥ�����ν���

$				// stksz�����������å�����κǾ��ͤ��⾮��������E_PAR��
				$CHECK_MIN_SSTKSZ(TSK.STKSZ[tskid], "stksz")$

$				// �����ƥॹ���å��ΰ�Υ����������
				$sstksz = TSK.STKSZ[tskid]$
			$END$

$			// �����ƥॹ���å��ΰ�γ���
			$ALLOC_SSTACK(CONCAT("_kernel_sstack_", tskid), sstksz)$
			$TSK.TINIB_SSTKSZ[tskid] = FORMAT("ROUND_STK_T(%1%)", sstksz)$
			$TSK.TINIB_SSTK[tskid] = CONCAT("_kernel_sstack_", tskid)$
		$ELSE$
$			// stk��NULL�Ǥʤ����ν���

$			// stksz�����������å�����κǾ��ͤ��⾮��������E_PAR��
			$CHECK_MIN_SSTKSZ(TSK.STKSZ[tskid], "stksz")$

$			// stksz�������å��ΰ�Υ�������������������Ƥ��ʤ�����E_PAR��
			$IF CHECK_STKSZ_ALIGN
							&& (TSK.STKSZ[tskid] & (CHECK_STKSZ_ALIGN - 1))$
				$ERROR TSK.TEXT_LINE[tskid]$E_PAR: $FORMAT(_("%1% `%2%\' of `%3%\' in %4% is not aligned"), "stksz", TSK.STKSZ[tskid], tskid, "CRE_TSK")$$END$
			$END$

$			// sstksz����ά����Ƥ��餺��0�Ǥʤ�����E_PAR��
			$IF LENGTH(TSK.SSTKSZ[tskid]) && (TSK.SSTKSZ[tskid] != 0)$
				$ERROR TSK.TEXT_LINE[tskid]$E_PAR: $FORMAT(_("%1% `%2%\' of `%3%\' in %4% must be 0"), "sstksz", TSK.SSTKSZ[tskid], tskid, "CRE_TSK")$$END$
			$END$

			$TSK.TINIB_SSTKSZ[tskid] = TSK.STKSZ[tskid]$
			$TSK.TINIB_SSTK[tskid] = TSK.STK[tskid]$
		$END$
	$ELSE$
$		// �桼���������ξ��
		$IF !LENGTH(TSK.SSTK[tskid]) || EQ(TSK.SSTK[tskid],"NULL")$
$			// sstk����ά����Ƥ��뤫��NULL�ξ��ν���

			$IF LENGTH(TSK.SSTKSZ[tskid])$
$				// sstksz����ά����Ƥ��ʤ����ν���

$				// sstksz��0�����������å�����κǾ��ͤ��⾮��������E_PAR��
				$CHECK_MIN_SSTKSZ(TSK.SSTKSZ[tskid], "sstksz")$

$				// �����ƥॹ���å��ΰ�Υ����������
				$sstksz = TSK.SSTKSZ[tskid]$
			$ELSE$
$				// sstksz����ά����Ƥ�����ν���

$				// �����ƥॹ���å��ΰ�Υ����������
				$sstksz = "DEFAULT_SSTKSZ"$
			$END$

$			// �����ƥॹ���å��ΰ�γ���
			$ALLOC_SSTACK(CONCAT("_kernel_sstack_", tskid), sstksz)$
			$TSK.TINIB_SSTKSZ[tskid] = FORMAT("ROUND_STK_T(%1%)", sstksz)$
			$TSK.TINIB_SSTK[tskid] = CONCAT("_kernel_sstack_", tskid)$
		$ELSE$
$			// sstk����ά����Ƥ��餺��NULL�Ǥʤ����ν���

$			// sstksz��0�����������å�����κǾ��ͤ��⾮��������E_PAR��
			$CHECK_MIN_SSTKSZ(TSK.SSTKSZ[tskid], "sstksz")$

$			// sstksz�������å��ΰ�Υ�������������������Ƥ��ʤ�����E_PAR��
			$IF CHECK_STKSZ_ALIGN
							&& (TSK.SSTKSZ[tskid] & (CHECK_STKSZ_ALIGN - 1))$
				$ERROR TSK.TEXT_LINE[tskid]$E_PAR: $FORMAT(_("%1% `%2%\' of `%3%\' in %4% is not aligned"), "sstksz", TSK.SSTKSZ[tskid], tskid, "CRE_TSK")$$END$
			$END$

			$TSK.TINIB_SSTKSZ[tskid] = TSK.SSTKSZ[tskid]$
			$TSK.TINIB_SSTK[tskid] = TSK.SSTK[tskid]$
		$END$
	$END$
$END$
$NL$

$ �桼�������å��ΰ�������Ȥ���˴ؤ��륨�顼�����å�
$FOREACH tskid TSK.ID_LIST$
	$IF TSK.DOMAIN[tskid] == TDOM_KERNEL$
$		// �����ƥॿ�����ξ��ν���
		$TSK.TINIB_USTKSZ[tskid] = 0$
		$TSK.TINIB_USTK[tskid] = "NULL"$
	$ELSE$
$		// �桼���������ξ��ν���

$		// stksz��0�����������å�����κǾ��͡�TARGET_MIN_USTKSZ�ˤ���
$		// ����������E_PAR��
		$IF TSK.STKSZ[tskid] == 0 || (TARGET_MIN_USTKSZ
							&& TSK.STKSZ[tskid] < TARGET_MIN_USTKSZ)$
			$ERROR TSK.TEXT_LINE[tskid]$E_PAR: $FORMAT(_("%1% `%2%\' of `%3%\' in %4% is too small"), "stksz", TSK.STKSZ[tskid], tskid, "CRE_TSK")$$END$
		$END$

		$IF EQ(TSK.STK[tskid],"NULL")$
$			// stk��NULL�ξ��ν���

$			// �桼�������å��ΰ�γ���
			$ALLOC_USTACK(tskid, TSK.STKSZ[tskid])$
		$ELSE$
$			// stk��NULL�Ǥʤ��ξ��ν���

$			// stksz�������å��ΰ�Υ�������������������Ƥ��ʤ�����E_PAR��
			$IF CHECK_USTKSZ_ALIGN
							&& (TSK.STKSZ[tskid] & (CHECK_USTKSZ_ALIGN - 1))$
				$ERROR TSK.TEXT_LINE[tskid]$E_PAR: $FORMAT(_("%1% `%2%\' of `%3%\' in %4% is not aligned"), "stksz", TSK.STKSZ[tskid], tskid, "CRE_TSK")$$END$
			$END$

			$TSK.TINIB_USTKSZ[tskid] = TSK.STKSZ[tskid]$
			$TSK.TINIB_USTK[tskid] = TSK.STK[tskid]$
		$END$

$		// ���ꥪ�֥������Ⱦ��������
		$nummo = nummo + 1$
		$MO.TYPE[nummo] = TOPPERS_USTACK$
		$MO.TSKID[nummo] = tskid$
		$MO.SIZE[nummo] = TSK.TINIB_USTKSZ[tskid]$
		$IF !EQ(TSK.STK[tskid],"NULL")$
			$MO.BASE[nummo] = TSK.STK[tskid]$
			$MO.LINKER[nummo] = 0$
		$ELSE$
			$MO.LINKER[nummo] = 1$
			$MO.MEMREG[nummo] = STANDARD_RAM$
			$MO.SECTION[nummo] = SECTION_USTACK(tskid)$
			$MO_USTACK_LIST = APPEND(MO_USTACK_LIST, nummo)$
		$END$
		$MO.DOMAIN[nummo] = TSK.DOMAIN[tskid]$
		$MO.MEMATR[nummo] = TARGET_MEMATR_USTACK$

		$domptn = DEFAULT_ACPTN[MO.DOMAIN[nummo]]$
		$MO.ACPTN1[nummo] = domptn$
		$MO.ACPTN2[nummo] = domptn$
		$MO.ACPTN4[nummo] = domptn$
		$MO.TEXT_LINE[nummo] = TSK.TEXT_LINE[tskid]$
		$MO.APINAME[nummo] = TSK.APINAME[tskid]$
	$END$
$END$
$NL$

$ ������������֥�å��������ʥ�������1�İʾ�¸�ߤ����
const TINIB _kernel_tinib_table[TNUM_TSKID] = {$NL$
$JOINEACH tskid TSK.ID_LIST ",\n"$
$	// �ݸ�ɥᥤ�������֥�å��ؤΥݥ���
	$TAB${
	$IF TSK.DOMAIN[tskid] == TDOM_KERNEL$
		$SPC$&_kernel_dominib_kernel,
	$ELSE$
		$SPC$&_kernel_dominib_table[INDEX_DOM($TSK.DOMAIN[tskid]$)],
	$END$

$	// ������°������ĥ���󡤵�ư���ϡ���ư��ͥ����
	$SPC$($TSK.TSKATR[tskid]$), (intptr_t)($TSK.EXINF[tskid]$),
	$SPC$((TASK)($TSK.TASK[tskid]$)), INT_PRIORITY($TSK.ITSKPRI[tskid]$),

$	// ���������������ƥ����ȥ֥�å��������å��ΰ�
	$IF USE_TSKINICTXB$
		$GENERATE_TSKINICTXB(tskid)$
	$ELSE$
		$SPC$$TSK.TINIB_SSTKSZ[tskid]$, $TSK.TINIB_SSTK[tskid]$,
		$SPC$$TSK.TINIB_USTKSZ[tskid]$, $TSK.TINIB_USTK[tskid]$,
	$END$

$	// �������㳰�����롼�����°���ȵ�ư����
	$SPC$($ALT(TSK.TEXATR[tskid],"TA_NULL")$), ($ALT(TSK.TEXRTN[tskid],"NULL")$),

$	// �����������ĥ٥���
	$IF LENGTH(TSK.ACPTN1[tskid])$
		$SPC${ $TSK.ACPTN1[tskid]$, $TSK.ACPTN2[tskid]$, $TSK.ACPTN3[tskid]$, $TSK.ACPTN4[tskid]$ }
	$ELSE$
		$DEFAULT_ACVCT[TSK.DOMAIN[tskid]]$
	$END$
	}
$END$$NL$
};$NL$
$NL$

$ �����������֥�å�������
TCB _kernel_tcb_table[TNUM_TSKID];$NL$
$NL$

$ ��������������ơ��֥������
const ID _kernel_torder_table[TNUM_TSKID] = {$NL$
$TAB$$JOINEACH tskid TSK.ORDER_LIST ", "$$tskid$$END$$NL$
};$NL$
$NL$

$
$  ���ޥե�
$
/*$NL$
$SPC$*  Semaphore Functions$NL$
$SPC$*/$NL$
$NL$

$ ���ޥե�ID�ֹ�κ�����
const ID _kernel_tmax_semid = (TMIN_SEMID + TNUM_SEMID - 1);$NL$
$NL$

$IF LENGTH(SEM.ID_LIST)$
$	// ���顼�����å�
	$FOREACH semid SEM.ID_LIST$
$		// �ݸ�ɥᥤ��˽�°���Ƥ��ʤ�����̵��°�Ȥ���
		$IF !LENGTH(SEM.DOMAIN[semid])$
			$SEM.DOMAIN[semid] = TDOM_NONE$
		$END$

$		// sematr���ʡ�TA_TPRI�ϡˤǤʤ�����E_RSATR��
		$IF (SEM.SEMATR[semid] & ~TA_TPRI) != 0$
			$ERROR SEM.TEXT_LINE[semid]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "sematr", SEM.SEMATR[semid], semid, "CRE_SEM")$$END$
		$END$

$		// (0 <= isemcnt && isemcnt <= maxsem)�Ǥʤ�����E_PAR��
		$IF !(0 <= SEM.ISEMCNT[semid] && SEM.ISEMCNT[semid] <= SEM.MAXSEM[semid])$
			$ERROR SEM.TEXT_LINE[semid]$E_PAR: $FORMAT(_("too large %1% `%2%\' of `%3%\' in %4%"), "isemcnt", SEM.ISEMCNT[semid], semid, "CRE_SEM")$$END$
		$END$

$		// (1 <= maxsem && maxsem <= TMAX_MAXSEM)�Ǥʤ�����E_PAR��
		$IF !(1 <= SEM.MAXSEM[semid] && SEM.MAXSEM[semid] <= TMAX_MAXSEM)$
			$ERROR SEM.TEXT_LINE[semid]$E_PAR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "maxsem", SEM.MAXSEM[semid], semid, "CRE_SEM")$$END$
		$END$

$		// SAC_SEM��CRE_SEM�Ȱۤʤ��ݸ�ɥᥤ���°�������E_RSATR��
		$IF LENGTH(SEM.ACPTN1[semid]) && ALT(SAC_SEM.DOMAIN[semid], TDOM_NONE) != SEM.DOMAIN[semid]$
			$ERROR SAC_SEM.TEXT_LINE[semid]$E_RSATR: $FORMAT(_("%1% for `%2%\' must belong to the same protection domain with %3%"), "SAC_SEM", semid, "CRE_SEM")$$END$
		$END$
	$END$	

$	// ���ޥե�������֥�å�������
	const SEMINIB _kernel_seminib_table[TNUM_SEMID] = {$NL$
	$JOINEACH semid SEM.ID_LIST ",\n"$
		$TAB${ ($SEM.SEMATR[semid]$), ($SEM.ISEMCNT[semid]$), ($SEM.MAXSEM[semid]$),
		$IF LENGTH(SEM.ACPTN1[semid])$
			$SPC${ $SEM.ACPTN1[semid]$, $SEM.ACPTN2[semid]$, $SEM.ACPTN3[semid]$, $SEM.ACPTN4[semid]$ }
		$ELSE$
			$DEFAULT_ACVCT[SEM.DOMAIN[semid]]$
		$END$
		}
	$END$$NL$
	};$NL$
	$NL$

$	// ���ޥե������֥�å�
	SEMCB _kernel_semcb_table[TNUM_SEMID];$NL$
$ELSE$
	TOPPERS_EMPTY_LABEL(const SEMINIB, _kernel_seminib_table);$NL$
	TOPPERS_EMPTY_LABEL(SEMCB, _kernel_semcb_table);$NL$
$END$$NL$

$
$  ���٥�ȥե饰
$
/*$NL$
$SPC$*  Eventflag Functions$NL$
$SPC$*/$NL$
$NL$

$ ���٥�ȥե饰ID�ֹ�κ�����
const ID _kernel_tmax_flgid = (TMIN_FLGID + TNUM_FLGID - 1);$NL$
$NL$

$IF LENGTH(FLG.ID_LIST)$
$	// ���顼�����å�
	$FOREACH flgid FLG.ID_LIST$
$		// �ݸ�ɥᥤ��˽�°���Ƥ��ʤ�����̵��°�Ȥ���
		$IF !LENGTH(FLG.DOMAIN[flgid])$
			$FLG.DOMAIN[flgid] = TDOM_NONE$
		$END$

$		// flgatr���ʡ�TA_TPRI�ϡá�TA_WMUL�ϡá�TA_CLR�ϡˤǤʤ�����E_RSATR��
		$IF (FLG.FLGATR[flgid] & ~(TA_TPRI|TA_WMUL|TA_CLR)) != 0$
			$ERROR FLG.TEXT_LINE[flgid]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "flgatr", FLG.FLGATR[flgid], flgid, "CRE_FLG")$$END$
		$END$

$		// SAC_FLG��CRE_FLG�Ȱۤʤ��ݸ�ɥᥤ���°�������E_RSATR��
		$IF LENGTH(FLG.ACPTN1[flgid]) && ALT(SAC_FLG.DOMAIN[flgid], TDOM_NONE) != FLG.DOMAIN[flgid]$
			$ERROR SAC_FLG.TEXT_LINE[flgid]$E_RSATR: $FORMAT(_("%1% for `%2%\' must belong to the same protection domain with %3%"), "SAC_FLG", flgid, "CRE_FLG")$$END$
		$END$
	$END$

$	// ���٥�ȥե饰������֥�å�������
	const FLGINIB _kernel_flginib_table[TNUM_FLGID] = {$NL$
	$JOINEACH flgid FLG.ID_LIST ",\n"$
		$TAB${ ($FLG.FLGATR[flgid]$), ($FLG.IFLGPTN[flgid]$),
		$IF LENGTH(FLG.ACPTN1[flgid])$
			$SPC${ $FLG.ACPTN1[flgid]$, $FLG.ACPTN2[flgid]$, $FLG.ACPTN3[flgid]$, $FLG.ACPTN4[flgid]$ }
		$ELSE$
			$DEFAULT_ACVCT[FLG.DOMAIN[flgid]]$
		$END$
		}
	$END$$NL$
	};$NL$
	$NL$

$	// ���٥�ȥե饰�����֥�å�
	FLGCB _kernel_flgcb_table[TNUM_FLGID];$NL$
$ELSE$
	TOPPERS_EMPTY_LABEL(const FLGINIB, _kernel_flginib_table);$NL$
	TOPPERS_EMPTY_LABEL(FLGCB, _kernel_flgcb_table);$NL$
$END$$NL$

$
$  �ǡ������塼
$
/*$NL$
$SPC$*  Dataqueue Functions$NL$
$SPC$*/$NL$
$NL$

$ �ǡ������塼ID�ֹ�κ�����
const ID _kernel_tmax_dtqid = (TMIN_DTQID + TNUM_DTQID - 1);$NL$
$NL$

$IF LENGTH(DTQ.ID_LIST)$
$	// ���顼�����å�
	$FOREACH dtqid DTQ.ID_LIST$
$		// �ݸ�ɥᥤ��˽�°���Ƥ��ʤ�����̵��°�Ȥ���
		$IF !LENGTH(DTQ.DOMAIN[dtqid])$
			$DTQ.DOMAIN[dtqid] = TDOM_NONE$
		$END$

$		// dtqatr���ʡ�TA_TPRI�ϡˤǤʤ�����E_RSATR��
		$IF (DTQ.DTQATR[dtqid] & ~TA_TPRI) != 0$
			$ERROR DTQ.TEXT_LINE[dtqid]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "dtqatr", DTQ.DTQATR[dtqid], dtqid, "CRE_DTQ")$$END$
		$END$

$		// dtqmb��NULL�Ǥʤ�����E_NOSPT��
		$IF !EQ(DTQ.DTQMB[dtqid], "NULL")$
			$ERROR DTQ.TEXT_LINE[dtqid]$E_NOSPT: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "dtqmb", DTQ.DTQMB[dtqid], dtqid, "CRE_DTQ")$$END$
		$END$

$		// SAC_DTQ��CRE_DTQ�Ȱۤʤ��ݸ�ɥᥤ���°�������E_RSATR��
		$IF LENGTH(DTQ.ACPTN1[dtqid]) && ALT(SAC_DTQ.DOMAIN[dtqid], TDOM_NONE) != DTQ.DOMAIN[dtqid]$
			$ERROR SAC_DTQ.TEXT_LINE[dtqid]$E_RSATR: $FORMAT(_("%1% for `%2%\' must belong to the same protection domain with %3%"), "SAC_DTQ", dtqid, "CRE_DTQ")$$END$
		$END$

$		// �ǡ������塼�����ΰ�
		$IF DTQ.DTQCNT[dtqid]$
			static DTQMB _kernel_dtqmb_$dtqid$[$DTQ.DTQCNT[dtqid]$];$NL$
		$END$
	$END$

$	// �ǡ������塼������֥�å�������
	const DTQINIB _kernel_dtqinib_table[TNUM_DTQID] = {$NL$
	$JOINEACH dtqid DTQ.ID_LIST ",\n"$
		$TAB${ ($DTQ.DTQATR[dtqid]$), ($DTQ.DTQCNT[dtqid]$),
		$IF DTQ.DTQCNT[dtqid]$
			$SPC$(_kernel_dtqmb_$dtqid$),
		$ELSE$
			$SPC$NULL,
		$END$
		$IF LENGTH(DTQ.ACPTN1[dtqid])$
			$SPC${ $DTQ.ACPTN1[dtqid]$, $DTQ.ACPTN2[dtqid]$, $DTQ.ACPTN3[dtqid]$, $DTQ.ACPTN4[dtqid]$ }
		$ELSE$
			$DEFAULT_ACVCT[DTQ.DOMAIN[dtqid]]$
		$END$
		}
	$END$$NL$
	};$NL$
	$NL$

$	// �ǡ������塼�����֥�å�
	DTQCB _kernel_dtqcb_table[TNUM_DTQID];$NL$
$ELSE$
	TOPPERS_EMPTY_LABEL(const DTQINIB, _kernel_dtqinib_table);$NL$
	TOPPERS_EMPTY_LABEL(DTQCB, _kernel_dtqcb_table);$NL$
$END$$NL$

$
$  ͥ���٥ǡ������塼
$
/*$NL$
$SPC$*  Priority Dataqueue Functions$NL$
$SPC$*/$NL$
$NL$

$ ͥ���٥ǡ������塼ID�ֹ�κ�����
const ID _kernel_tmax_pdqid = (TMIN_PDQID + TNUM_PDQID - 1);$NL$
$NL$

$IF LENGTH(PDQ.ID_LIST)$
$	// ���顼�����å�
	$FOREACH pdqid PDQ.ID_LIST$
$		// �ݸ�ɥᥤ��˽�°���Ƥ��ʤ�����̵��°�Ȥ���
		$IF !LENGTH(PDQ.DOMAIN[pdqid])$
			$PDQ.DOMAIN[pdqid] = TDOM_NONE$
		$END$

$		// pdqatr���ʡ�TA_TPRI�ϡˤǤʤ�����E_RSATR��
		$IF (PDQ.PDQATR[pdqid] & ~TA_TPRI) != 0$
			$ERROR PDQ.TEXT_LINE[pdqid]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "pdqatr", PDQ.PDQATR[pdqid], pdqid, "CRE_PDQ")$$END$
		$END$

$		// (TMIN_DPRI <= maxdpri && maxdpri <= TMAX_DPRI)�Ǥʤ�����E_PAR��
		$IF !(TMIN_DPRI <= PDQ.MAXDPRI[pdqid] && PDQ.MAXDPRI[pdqid] <= TMAX_DPRI)$
			$ERROR PDQ.TEXT_LINE[pdqid]$E_PAR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "maxdpri", PDQ.MAXDPRI[pdqid], pdqid, "CRE_PDQ")$$END$
		$END$

$		// pdqmb��NULL�Ǥʤ�����E_NOSPT��
		$IF !EQ(PDQ.PDQMB[pdqid], "NULL")$
			$ERROR PDQ.TEXT_LINE[pdqid]$E_NOSPT: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "pdqmb", PDQ.PDQMB[pdqid], pdqid, "CRE_PDQ")$$END$
		$END$

$		// SAC_PDQ��CRE_PDQ�Ȱۤʤ��ݸ�ɥᥤ���°�������E_RSATR��
		$IF LENGTH(PDQ.ACPTN1[pdqid]) && ALT(SAC_PDQ.DOMAIN[pdqid], TDOM_NONE) != PDQ.DOMAIN[pdqid]$
			$ERROR SAC_PDQ.TEXT_LINE[pdqid]$E_RSATR: $FORMAT(_("%1% for `%2%\' must belong to the same protection domain with %3%"), "SAC_PDQ", pdqid, "CRE_PDQ")$$END$
		$END$

$		// ͥ���٥ǡ������塼�����ΰ�
		$IF PDQ.PDQCNT[pdqid]$
			static PDQMB _kernel_pdqmb_$pdqid$[$PDQ.PDQCNT[pdqid]$];$NL$
		$END$
	$END$

$	// ͥ���٥ǡ������塼������֥�å�������
	const PDQINIB _kernel_pdqinib_table[TNUM_PDQID] = {$NL$
	$JOINEACH pdqid PDQ.ID_LIST ",\n"$
		$TAB${ ($PDQ.PDQATR[pdqid]$), ($PDQ.PDQCNT[pdqid]$), ($PDQ.MAXDPRI[pdqid]$),
		$IF PDQ.PDQCNT[pdqid]$
			$SPC$(_kernel_pdqmb_$pdqid$),
		$ELSE$
			$SPC$NULL,
		$END$
		$IF LENGTH(PDQ.ACPTN1[pdqid])$
			$SPC${ $PDQ.ACPTN1[pdqid]$, $PDQ.ACPTN2[pdqid]$, $PDQ.ACPTN3[pdqid]$, $PDQ.ACPTN4[pdqid]$ }
		$ELSE$
			$DEFAULT_ACVCT[PDQ.DOMAIN[pdqid]]$
		$END$
	}
	$END$$NL$
	};$NL$
	$NL$

$	// ͥ���٥ǡ������塼�����֥�å�
	PDQCB _kernel_pdqcb_table[TNUM_PDQID];$NL$
$ELSE$
	TOPPERS_EMPTY_LABEL(const PDQINIB, _kernel_pdqinib_table);$NL$
	TOPPERS_EMPTY_LABEL(PDQCB, _kernel_pdqcb_table);$NL$
$END$$NL$

$ 
$  �ߥ塼�ƥå���
$ 
/*$NL$
$SPC$*  Mutex Functions$NL$
$SPC$*/$NL$
$NL$

$ �ߥ塼�ƥå���ID�ֹ�κ�����
const ID _kernel_tmax_mtxid = (TMIN_MTXID + TNUM_MTXID - 1);$NL$
$NL$

$IF LENGTH(MTX.ID_LIST)$
$	// ���顼�����å�
	$FOREACH mtxid MTX.ID_LIST$
$		// �ݸ�ɥᥤ��˽�°���Ƥ��ʤ�����̵��°�Ȥ���
		$IF !LENGTH(MTX.DOMAIN[mtxid])$
			$MTX.DOMAIN[mtxid] = TDOM_NONE$
		$END$

$		// mtxatr���ʡ�TA_TPRI��TA_CEILING�ϡˤǤʤ�����E_RSATR��
		$IF !(MTX.MTXATR[mtxid] == 0 || MTX.MTXATR[mtxid] == TA_TPRI || MTX.MTXATR[mtxid] == TA_CEILING)$
			$ERROR MTX.TEXT_LINE[mtxid]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "mtxatr", MTX.MTXATR[mtxid], mtxid, "CRE_MTX")$$END$
		$END$

$		// ceilpri��̤����ξ���0�ȸ��ʤ�
		$IF !LENGTH(MTX.CEILPRI[mtxid])$
			$MTX.CEILPRI[mtxid] = 0$
		$END$

$		// (TMIN_TPRI <= ceilpri && ceilpri <= TMAX_TPRI)�Ǥʤ�����E_PAR��
		$IF MTX.MTXATR[mtxid] == TA_CEILING && (MTX.CEILPRI[mtxid] < TMIN_TPRI || TMAX_TPRI < MTX.CEILPRI[mtxid])$
			$ERROR MTX.TEXT_LINE[mtxid]$E_PAR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "ceilpri", MTX.CEILPRI[mtxid], mtxid, "CRE_MTX")$$END$
		$END$

$		// SAC_MTX��CRE_MTX�Ȱۤʤ��ݸ�ɥᥤ���°�������E_RSATR��
		$IF LENGTH(MTX.ACPTN1[mtxid]) && ALT(SAC_MTX.DOMAIN[mtxid], TDOM_NONE) != MTX.DOMAIN[mtxid]$
			$ERROR SAC_MTX.TEXT_LINE[mtxid]$E_RSATR: $FORMAT(_("%1% for `%2%\' must belong to the same protection domain with %3%"), "SAC_MTX", mtxid, "CRE_MTX")$$END$
		$END$
	$END$

$	// �ߥ塼�ƥå���������֥�å�������
	const MTXINIB _kernel_mtxinib_table[TNUM_MTXID] = {$NL$
	$JOINEACH mtxid MTX.ID_LIST ",\n"$
		$TAB${ ($MTX.MTXATR[mtxid]$), INT_PRIORITY($MTX.CEILPRI[mtxid]$),
		$IF LENGTH(MTX.ACPTN1[mtxid])$
			$SPC${ $MTX.ACPTN1[mtxid]$, $MTX.ACPTN2[mtxid]$, $MTX.ACPTN3[mtxid]$, $MTX.ACPTN4[mtxid]$ }
		$ELSE$
			$DEFAULT_ACVCT[MTX.DOMAIN[mtxid]]$
		$END$
		}
	$END$$NL$
	};$NL$
	$NL$

$	// �ߥ塼�ƥå��������֥�å�
	MTXCB _kernel_mtxcb_table[TNUM_MTXID];$NL$
$ELSE$
	TOPPERS_EMPTY_LABEL(const MTXINIB, _kernel_mtxinib_table);$NL$
	TOPPERS_EMPTY_LABEL(MTXCB, _kernel_mtxcb_table);$NL$
$END$$NL$

$
$  ����Ĺ����ס���
$
/*$NL$
$SPC$*  Fixed-sized Memorypool Functions$NL$
$SPC$*/$NL$
$NL$

$ ����Ĺ����ס���ID�ֹ�κ�����
const ID _kernel_tmax_mpfid = (TMIN_MPFID + TNUM_MPFID - 1);$NL$
$NL$

$IF LENGTH(MPF.ID_LIST)$
$	// ���顼�����å�
	$FOREACH mpfid MPF.ID_LIST$
$		// �ݸ�ɥᥤ��˽�°���Ƥ��ʤ�����̵��°�Ȥ���
		$IF !LENGTH(MPF.DOMAIN[mpfid])$
			$MPF.DOMAIN[mpfid] = TDOM_NONE$
		$END$

$		// mpfatr���ʡ�TA_TPRI�ϡˤǤʤ�����E_RSATR��
		$IF (MPF.MPFATR[mpfid] & ~TA_TPRI) != 0$
			$ERROR MPF.TEXT_LINE[mpfid]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "mpfatr", MPF.MPFATR[mpfid], mpfid, "CRE_MPF")$$END$
		$END$

$		// blkcnt��0�ξ���E_PAR��
		$IF MPF.BLKCNT[mpfid] == 0$
			$ERROR MPF.TEXT_LINE[mpfid]$E_PAR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "blkcnt", MPF.BLKCNT[mpfid], mpfid, "CRE_MPF")$$END$
		$END$

$		// blksz��0�ξ���E_PAR��
		$IF MPF.BLKSZ[mpfid] == 0$
			$ERROR MPF.TEXT_LINE[mpfid]$E_PAR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "blksz", MPF.BLKSZ[mpfid], mpfid, "CRE_MPF")$$END$
		$END$

$		// SAC_MPF��CRE_MPF�Ȱۤʤ��ݸ�ɥᥤ���°�������E_RSATR��
		$IF LENGTH(MPF.ACPTN1[mpfid]) && ALT(SAC_MPF.DOMAIN[mpfid], TDOM_NONE) != MPF.DOMAIN[mpfid]$
			$ERROR SAC_MPF.TEXT_LINE[mpfid]$E_RSATR: $FORMAT(_("%1% for `%2%\' must belong to the same protection domain with %3%"), "SAC_MPF", mpfid, "CRE_MPF")$$END$
		$END$

$		// ����Ĺ����ס����ΰ�
		$IF EQ(MPF.MPF[mpfid], "NULL")$
			$IF MPF.DOMAIN[mpfid] == TDOM_KERNEL
					&& (!LENGTH(MPF.ACPTN1[mpfid]) || 
							(MPF.ACPTN1[mpfid] == TACP_KERNEL
								&& MPF.ACPTN2[mpfid] == TACP_KERNEL
								&& MPF.ACPTN4[mpfid] == TACP_KERNEL))$
$				// �����ͥ�ɥᥤ���°���������������ĥ٥�����ɸ���
$				// ����Ĺ����ס���ξ��
				static MPF_T _kernel_mpf_$mpfid$[($MPF.BLKCNT[mpfid]$) * COUNT_MPF_T($MPF.BLKSZ[mpfid]$)];$NL$
			$ELSE$
$				// �嵭�ʳ��θ���Ĺ����ס���ξ��
				$ALLOC_UMPF(mpfid, MPF.DOMAIN[mpfid], MPF.BLKCNT[mpfid], MPF.BLKSZ[mpfid])$

$				// ���ꥪ�֥������Ⱦ��������
				$nummo = nummo + 1$
				$MO.TYPE[nummo] = TOPPERS_MPFAREA$
				$MO.MPFID[nummo] = mpfid$
				$MO.LINKER[nummo] = 1$
				$MO.DOMAIN[nummo] = MPF.DOMAIN[mpfid]$
				$MO.MEMREG[nummo] = STANDARD_RAM$
				$MO.SECTION[nummo] = SECTION_UMPF(mpfid)$
				$MO.MEMATR[nummo] = TARGET_MEMATR_MPFAREA$

				$domptn = DEFAULT_ACPTN[MO.DOMAIN[nummo]]$
				$MO.ACPTN1[nummo] = ALT(MPF.ACPTN1[mpfid], domptn)$
				$MO.ACPTN2[nummo] = ALT(MPF.ACPTN2[mpfid], domptn)$
				$MO.ACPTN4[nummo] = ALT(MPF.ACPTN4[mpfid], domptn)$
				$MO.TEXT_LINE[nummo] = MPF.TEXT_LINE[mpfid]$
				$MO.APINAME[nummo] = MPF.APINAME[mpfid]$
			$END$
		$END$

$		// mpfmb��NULL�Ǥʤ�����E_NOSPT��
		$IF !EQ(MPF.MPFMB[mpfid], "NULL")$
			$ERROR MPF.TEXT_LINE[mpfid]$E_NOSPT: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "mpfmb", MPF.MPFMB[mpfid], mpfid, "CRE_MPF")$$END$
		$END$

$		// ����Ĺ����ס�������ΰ�
		static MPFMB _kernel_mpfmb_$mpfid$[$MPF.BLKCNT[mpfid]$];$NL$
	$END$

$	// ����Ĺ����ס��������֥�å�������
	const MPFINIB _kernel_mpfinib_table[TNUM_MPFID] = {$NL$
	$JOINEACH mpfid MPF.ID_LIST ",\n"$
		$TAB${ ($MPF.MPFATR[mpfid]$), ($MPF.BLKCNT[mpfid]$), ROUND_MPF_T($MPF.BLKSZ[mpfid]$),
		$IF EQ(MPF.MPF[mpfid],"NULL")$
			$SPC$(_kernel_mpf_$mpfid$),
		$ELSE$
			$SPC$($MPF.MPF[mpfid]$),
		$END$
		$SPC$(_kernel_mpfmb_$mpfid$),
		$IF LENGTH(MPF.ACPTN1[mpfid])$
			$SPC${ $MPF.ACPTN1[mpfid]$, $MPF.ACPTN2[mpfid]$, $MPF.ACPTN3[mpfid]$, $MPF.ACPTN4[mpfid]$ }
		$ELSE$
			$DEFAULT_ACVCT[MPF.DOMAIN[mpfid]]$
		$END$
		}
	$END$$NL$
	};$NL$
	$NL$

$	// ����Ĺ����ס�������֥�å�
	MPFCB _kernel_mpfcb_table[TNUM_MPFID];$NL$
$ELSE$
	TOPPERS_EMPTY_LABEL(const MPFINIB, _kernel_mpfinib_table);$NL$
	TOPPERS_EMPTY_LABEL(MPFCB, _kernel_mpfcb_table);$NL$
$END$$NL$

$
$  �����ϥ�ɥ�
$
/*$NL$
$SPC$*  Cyclic Handler Functions$NL$
$SPC$*/$NL$
$NL$

$ �����ϥ�ɥ�ID�ֹ�κ�����
const ID _kernel_tmax_cycid = (TMIN_CYCID + TNUM_CYCID - 1);$NL$
$NL$

$IF LENGTH(CYC.ID_LIST)$
$	// ���顼�����å�
	$FOREACH cycid CYC.ID_LIST$
$		// �����ͥ�ɥᥤ��˽�°���Ƥ��ʤ�����E_RSATR��
		$IF !LENGTH(CYC.DOMAIN[cycid]) || CYC.DOMAIN[cycid] != TDOM_KERNEL$
			$ERROR CYC.TEXT_LINE[cycid]$E_RSATR: $FORMAT(_("%1% `%2%\' must belong to the kernel domain in %3%"), "cyclic handler", cycid, "CRE_CYC")$$END$
$			// �ʹߤΥ��顼���޻�
			$CYC.DOMAIN[cycid] = TDOM_KERNEL$
		$END$

$		// cycatr���ʡ�TA_STA�ϡˤǤʤ�����E_RSATR��
		$IF (CYC.CYCATR[cycid] & ~TA_STA) != 0$
			$ERROR CYC.TEXT_LINE[cycid]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "cycatr", CYC.CYCATR[cycid], cycid, "CRE_CYC")$$END$
		$END$

$		// (0 < cyctim && cyctim <= TMAX_RELTIM)�Ǥʤ�����E_PAR��
		$IF !(0 < CYC.CYCTIM[cycid] && CYC.CYCTIM[cycid] <= TMAX_RELTIM)$
			$ERROR CYC.TEXT_LINE[cycid]$E_PAR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "cyctim", CYC.CYCTIM[cycid], cycid, "CRE_CYC")$$END$
		$END$

$		// (0 <= cycphs && cycphs <= TMAX_RELTIM)�Ǥʤ�����E_PAR��
		$IF !(0 <= CYC.CYCPHS[cycid] && CYC.CYCPHS[cycid] <= TMAX_RELTIM)$
			$ERROR CYC.TEXT_LINE[cycid]$E_PAR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "cycphs", CYC.CYCPHS[cycid], cycid, "CRE_CYC")$$END$
		$END$

$		// �ٹ�cycatr��TA_STA�����ꤵ��Ƥ��ơ�(cycphs == 0)�ξ��
		$IF (CYC.CYCATR[cycid] & TA_STA) != 0 && CYC.CYCPHS[cycid] == 0$
			$WARNING CYC.TEXT_LINE[cycid]$$FORMAT(_("%1% is not recommended when %2% is set to %3% in %4%"), "cycphs==0", "TA_STA", "cycatr", "CRE_CYC")$$END$
		$END$

$		// SAC_CYC��CRE_CYC�Ȱۤʤ��ݸ�ɥᥤ���°�������E_RSATR��
		$IF LENGTH(CYC.ACPTN1[cycid]) && ALT(SAC_CYC.DOMAIN[cycid], TDOM_KERNEL) != CYC.DOMAIN[cycid]$
			$ERROR SAC_CYC.TEXT_LINE[cycid]$E_RSATR: $FORMAT(_("%1% for `%2%\' must belong to the same protection domain with %3%"), "SAC_CYC", cycid, "CRE_CYC")$$END$
		$END$
	$END$

$	// �����ϥ�ɥ������֥�å�������
	const CYCINIB _kernel_cycinib_table[TNUM_CYCID] = {$NL$
	$JOINEACH cycid CYC.ID_LIST ",\n"$
		$TAB${ ($CYC.CYCATR[cycid]$), (intptr_t)($CYC.EXINF[cycid]$), ($CYC.CYCHDR[cycid]$), ($CYC.CYCTIM[cycid]$), ($CYC.CYCPHS[cycid]$),
		$IF LENGTH(CYC.ACPTN1[cycid])$
			$SPC${ $CYC.ACPTN1[cycid]$, $CYC.ACPTN2[cycid]$, $CYC.ACPTN3[cycid]$, $CYC.ACPTN4[cycid]$ }
		$ELSE$
			$DEFAULT_ACVCT[CYC.DOMAIN[cycid]]$
		$END$
		}
	$END$$NL$
	};$NL$
	$NL$

$	// �����ϥ�ɥ�����֥�å�
	CYCCB _kernel_cyccb_table[TNUM_CYCID];$NL$
$ELSE$
	TOPPERS_EMPTY_LABEL(const CYCINIB, _kernel_cycinib_table);$NL$
	TOPPERS_EMPTY_LABEL(CYCCB, _kernel_cyccb_table);$NL$
$END$$NL$

$
$  ���顼��ϥ�ɥ�
$
/*$NL$
$SPC$*  Alarm Handler Functions$NL$
$SPC$*/$NL$
$NL$

$ ���顼��ϥ�ɥ�ID�ֹ�κ�����
const ID _kernel_tmax_almid = (TMIN_ALMID + TNUM_ALMID - 1);$NL$
$NL$

$IF LENGTH(ALM.ID_LIST)$
$	// ���顼�����å�
	$FOREACH almid ALM.ID_LIST$
$		// �����ͥ�ɥᥤ��˽�°���Ƥ��ʤ�����E_RSATR��
		$IF !LENGTH(ALM.DOMAIN[almid]) || ALM.DOMAIN[almid] != TDOM_KERNEL$
			$ERROR ALM.TEXT_LINE[almid]$E_RSATR: $FORMAT(_("%1% `%2%\' must belong to the kernel domain in %3%"), "alarm handler", almid, "CRE_ALM")$$END$
$			// �ʹߤΥ��顼���޻�
			$ALM.DOMAIN[almid] = TDOM_KERNEL$
		$END$

$		// almatr����TA_NULL�ˤǤʤ�����E_RSATR��
		$IF ALM.ALMATR[almid] != 0$
			$ERROR ALM.TEXT_LINE[almid]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "almatr", ALM.ALMATR[almid], almid, "CRE_ALM")$$END$
		$END$

$		// SAC_ALM��CRE_ALM�Ȱۤʤ��ݸ�ɥᥤ���°�������E_RSATR��
		$IF LENGTH(ALM.ACPTN1[almid]) && ALT(SAC_ALM.DOMAIN[almid], TDOM_KERNEL) != ALM.DOMAIN[almid]$
			$ERROR SAC_ALM.TEXT_LINE[almid]$E_RSATR: $FORMAT(_("%1% for `%2%\' must belong to the same protection domain with %3%"), "SAC_ALM", almid, "CRE_ALM")$$END$
		$END$
	$END$

$	// ���顼��ϥ�ɥ������֥�å�������
	const ALMINIB _kernel_alminib_table[TNUM_ALMID] = {$NL$
	$JOINEACH almid ALM.ID_LIST ",\n"$
		$TAB${ ($ALM.ALMATR[almid]$), (intptr_t)($ALM.EXINF[almid]$), ($ALM.ALMHDR[almid]$),
		$IF LENGTH(ALM.ACPTN1[almid])$
			$SPC${ $ALM.ACPTN1[almid]$, $ALM.ACPTN2[almid]$, $ALM.ACPTN3[almid]$, $ALM.ACPTN4[almid]$ }
		$ELSE$
			$DEFAULT_ACVCT[ALM.DOMAIN[almid]]$
		$END$
		}
	$END$$NL$
	};$NL$
	$NL$

$	// ���顼��ϥ�ɥ�����֥�å�
	ALMCB _kernel_almcb_table[TNUM_ALMID];$NL$
$ELSE$
	TOPPERS_EMPTY_LABEL(const ALMINIB, _kernel_alminib_table);$NL$
	TOPPERS_EMPTY_LABEL(ALMCB, _kernel_almcb_table);$NL$
$END$$NL$

$
$  �����Х��ϥ�ɥ�
$
/*$NL$
$SPC$*  Overrun Handler Functions$NL$
$SPC$*/$NL$
$NL$

$ ���顼�����å�
$IF LENGTH(OVR.ORDER_LIST)$
$	// ��ŪAPI��DEF_OVR�פ�ʣ�������E_OBJ��
	$IF LENGTH(OVR.ORDER_LIST) > 1$
		$ERROR$E_OBJ: $FORMAT(_("too many %1%"), "DEF_OVR")$$END$
	$END$

$	// �����ͥ�ɥᥤ��˽�°���Ƥ��ʤ�����E_RSATR��
	$IF !LENGTH(OVR.DOMAIN[1]) || OVR.DOMAIN[1] != TDOM_KERNEL$
		$ERROR OVR.TEXT_LINE[1]$E_RSATR: $FORMAT(_("%1% must belong to the kernel domain in %2%"), "overrun handler", "DEF_OVR")$$END$
	$END$
$END$

$ �����Х��ϥ�ɥ������֥�å�������
#ifdef TOPPERS_SUPPORT_OVRHDR$NL$$NL$
const OVRINIB _kernel_ovrinib = {$NL$
$IF LENGTH(OVR.ORDER_LIST)$
	$TAB$($OVR.OVRATR[1]$), ($OVR.OVRHDR[1]$)$NL$
$ELSE$
	$TAB$TA_NULL, NULL$NL$
$END$
};$NL$$NL$
#endif /* TOPPERS_SUPPORT_OVRHDR */$NL$
$NL$

$
$  �����ƥ���ִ�����ǽ
$
/*$NL$
$SPC$*  System State Management Functions$NL$
$SPC$*/$NL$
$NL$

const ACVCT _kernel_sysstat_acvct =
$IF !LENGTH(SYS.ORDER_LIST)$
$	// SAC_SYS���ʤ����Υǥե�����ͤ�����
	$SPC${ TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }
$ELSE$
$	// SAC_SYS��������
$	// ��ŪAPI��SAC_SYS�פ�ʣ�������E_OBJ��
	$IF LENGTH(SYS.ORDER_LIST) > 1$
		$ERROR$E_OBJ: $FORMAT(_("too many %1%"), "SAC_SYS")$$END$
	$END$

$	// �����ͥ�ɥᥤ��ΰϤߤ���ˤʤ�����E_RSATR��
	$IF !LENGTH(SYS.DOMAIN[1]) || SYS.DOMAIN[1] != TDOM_KERNEL$
		$ERROR SYS.TEXT_LINE[1]$E_RSATR: $FORMAT(_("%1% must be within the kernel domain"), "SAC_SYS")$$END$
	$END$

	$SPC${ $SYS.ACPTN1[1]$, $SYS.ACPTN2[1]$, $SYS.ACPTN3[1]$, $SYS.ACPTN4[1]$ }
$END$
;$NL$
$NL$

$
$  ����ߴ�����ǽ
$
/*$NL$
$SPC$*  Interrupt Management Functions$NL$
$SPC$*/$NL$
$NL$

$ ������ֹ�ȳ���ߥϥ�ɥ��ֹ���Ѵ��ơ��֥�κ���
$IF LENGTH(INTNO_ATTISR_VALID) != LENGTH(INHNO_ATTISR_VALID)$
	$ERROR$length of `INTNO_ATTISR_VALID' is different from length of `INHNO_ATTISR_VALID'$END$
$END$
$i = 0$
$FOREACH intno INTNO_ATTISR_VALID$
	$inhno = AT(INHNO_ATTISR_VALID, i)$
	$INHNO[intno] = inhno$
	$INTNO[inhno] = intno$
	$i = i + 1$
$END$

$ ������׵�饤��˴ؤ��륨�顼�����å�
$i = 0$
$FOREACH intno INT.ORDER_LIST$
$	// �����ͥ�ɥᥤ��ΰϤߤ���ˤʤ�����E_RSATR��
	$IF !LENGTH(INT.DOMAIN[intno]) || INT.DOMAIN[intno] != TDOM_KERNEL$
		$ERROR INT.TEXT_LINE[intno]$E_RSATR: $FORMAT(_("%1% must be within the kernel domain"), "CFG_INT")$$END$
	$END$

$	// intno��CFG_INT���Ф��������ֹ�Ȥ����������ʤ�����E_PAR��
	$IF !LENGTH(FIND(INTNO_CFGINT_VALID, INT.INTNO[intno]))$
		$ERROR INT.TEXT_LINE[intno]$E_PAR: $FORMAT(_("illegal %1% `%2%\' in %3%"), "intno", INT.INTNO[intno], "CFG_INT")$$END$
	$END$

$	// intno��CFG_INT�ˤ�ä�����Ѥߤξ���E_OBJ��
	$j = 0$
	$FOREACH intno2 INT.ORDER_LIST$
		$IF j < i && INT.INTNO[intno] == INT.INTNO[intno2]$
			$ERROR INT.TEXT_LINE[intno]$E_OBJ: $FORMAT(_("%1% `%2%\' in %3% is duplicated"), "intno", INT.INTNO[intno], "CFG_INT")$$END$
		$END$
		$j = j + 1$
	$END$

$	// intatr���ʡ�TA_ENAINT�ϡá�TA_EDGE�ϡˤǤʤ�����E_RSATR��
	$IF (INT.INTATR[intno] & ~(TA_ENAINT|TA_EDGE|TARGET_INTATR)) != 0$
		$ERROR INT.TEXT_LINE[intno]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of %3% `%4%\' in %5%"), "intatr", INT.INTATR[intno], "intno", INT.INTNO[intno], "CFG_INT")$$END$
	$END$

$	// intpri��CFG_INT���Ф�������ͥ���٤Ȥ����������ʤ�����E_PAR��
	$IF !LENGTH(FIND(INTPRI_CFGINT_VALID, INT.INTPRI[intno]))$
		$ERROR INT.TEXT_LINE[intno]$E_PAR: $FORMAT(_("illegal %1% `%2%\' in %3%"), "intpri", INT.INTPRI[intno], "CFG_INT")$$END$
	$END$

$	// �����ͥ�����˸��ꤵ��Ƥ���intno���Ф��ơ�intpri��TMIN_INTPRI
$	// ���⾮�����ͤ����ꤵ�줿����E_OBJ��
	$IF LENGTH(FIND(INTNO_FIX_KERNEL, intno))$
		$IF INT.INTPRI[intno] < TMIN_INTPRI$
			$ERROR INT.TEXT_LINE[intno]$E_OBJ: $FORMAT(_("%1% `%2%\' must not have higher priority than %3%"), "intno", INT.INTNO[intno], "TMIN_INTPRI")$$END$
		$END$
	$END$

$	// �����ͥ�������˸��ꤵ��Ƥ���intno���Ф��ơ�intpri��TMIN_INTPRI
$	// ���⾮�����ͤ����ꤵ��ʤ��ä�����E_OBJ��
	$IF LENGTH(FIND(INTNO_FIX_NONKERNEL, intno))$
		$IF INT.INTPRI[intno] >= TMIN_INTPRI$
			$ERROR INT.TEXT_LINE[intno]$E_OBJ: $FORMAT(_("%1% `%2%\' must have higher priority than %3%"), "intno", INT.INTNO[intno], "TMIN_INTPRI")$$END$
		$END$
	$END$
	$i = i + 1$
$END$

$ ����ߥϥ�ɥ�˴ؤ��륨�顼�����å�
$i = 0$
$FOREACH inhno INH.ORDER_LIST$
$	// �����ͥ�ɥᥤ��˽�°���Ƥ��ʤ�����E_RSATR��
	$IF !LENGTH(INH.DOMAIN[inhno]) || INH.DOMAIN[inhno] != TDOM_KERNEL$
		$ERROR INH.TEXT_LINE[inhno]$E_RSATR: $FORMAT(_("%1% `%2%\' must belong to the kernel domain in %3%"), "interrupt handler", INH.INHNO[inhno], "DEF_INH")$$END$
	$END$

$	// inhno��DEF_INH���Ф������ߥϥ�ɥ��ֹ�Ȥ����������ʤ�����E_PAR��
	$IF !LENGTH(FIND(INHNO_DEFINH_VALID, INH.INHNO[inhno]))$
		$ERROR INH.TEXT_LINE[inhno]$E_PAR: $FORMAT(_("illegal %1% `%2%\' in %3%"), "inhno", INH.INHNO[inhno], "DEF_INH")$$END$
	$END$

$	// inhno��DEF_INH�ˤ�ä�����Ѥߤξ���E_OBJ��
	$j = 0$
	$FOREACH inhno2 INH.ORDER_LIST$
		$IF j < i && INH.INHNO[inhno] == INH.INHNO[inhno2]$
			$ERROR INH.TEXT_LINE[inhno]$E_OBJ: $FORMAT(_("%1% `%2%\' in %3% is duplicated"), "inhno", INH.INHNO[inhno], "DEF_INH")$$END$
		$END$
		$j = j + 1$
	$END$

$	// inhatr����TA_NULL�ˤǤʤ�����E_RSATR��
	$IF (INH.INHATR[inhno] & ~TARGET_INHATR) != 0$
		$ERROR INH.TEXT_LINE[inhno]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of %3% `%4%\' in %5%"), "inhatr", INH.INHATR[inhno], "inhno", INH.INHNO[inhno], "DEF_INH")$$END$
	$END$

$	// �����ͥ�����˸��ꤵ��Ƥ���inhno���Ф��ơ�inhatr��TA_NONKERNEL
$	//�������ꤵ��Ƥ������E_RSATR��
	$IF LENGTH(FIND(INHNO_FIX_KERNEL, inhno))$
		$IF (INH.INHATR[inhno] & TA_NONKERNEL) != 0$
			$ERROR INH.TEXT_LINE[inhno]$E_RSATR: $FORMAT(_("%1% `%2%\' must not be non-kernel interrupt"), "inhno", INH.INHNO[inhno])$$END$
		$END$
	$END$

$	// �����ͥ�������˸��ꤵ��Ƥ���inhno���Ф��ơ�inhatr��TA_NONKERNEL
$	// �����ꤵ��Ƥ��ʤ�����E_RSATR��
	$IF LENGTH(FIND(INHNO_FIX_NONKERNEL, inhno))$
		$IF (INH.INHATR[inhno] & TA_NONKERNEL) == 0$
			$ERROR INH.TEXT_LINE[inhno]$E_RSATR: $FORMAT(_("%1% `%2%\' must be non-kernel interrupt"), "inhno", INH.INHNO[inhno])$$END$
		$END$
	$END$

	$IF LENGTH(INTNO[INH.INHNO[inhno]])$
		$intno = INTNO[INH.INHNO[inhno]]$
		$IF LENGTH(FIND(INTNO_CFGINT_VALID, intno))$
$			// inhno���б�����intno���Ф���CFG_INT���ʤ�����E_OBJ��
			$IF !LENGTH(INT.INTNO[intno])$
				$ERROR INH.TEXT_LINE[inhno]$E_OBJ: $FORMAT(_("%1% `%2%\' corresponding to %3% `%4%\' is not configured with %5%"), "intno", INT.INTNO[intno], "inhno", INH.INHNO[inhno], "CFG_INT")$$END$
			$ELSE$
				$IF (INH.INHATR[inhno] & TA_NONKERNEL) == 0$
$					// inhatr��TA_NONKERNEL�����ꤵ��Ƥ��餺��inhno���б�
$					// ����intno���Ф���CFG_INT�����ꤵ�줿�����ͥ���٤�
$					// TMIN_INTPRI���⾮��������E_OBJ��
					$IF INT.INTPRI[intno] < TMIN_INTPRI$
						$ERROR INT.TEXT_LINE[intno]$E_OBJ: $FORMAT(_("%1% `%2%\' configured for %3% `%4%\' is higher than %5%"), "intpri", INT.INTPRI[intno], "inhno", INH.INHNO[inhno], "TMIN_INTPRI")$$END$
					$END$
				$ELSE$
$					// inhatr��TA_NONKERNEL�����ꤵ��Ƥ��ꡤinhno���б�
$					// ����intno���Ф���CFG_INT�����ꤵ�줿�����ͥ���٤�
$					// TMIN_INTPRI�ʾ�Ǥ������E_OBJ��
					$IF INT.INTPRI[intno] >= TMIN_INTPRI$
						$ERROR INT.TEXT_LINE[intno]$E_OBJ: $FORMAT(_("%1% `%2%\' configured for %3% `%4%\' is lower than or equal to %5%"), "intpri", INT.INTPRI[intno], "inhno", INH.INHNO[inhno], "TMIN_INTPRI")$$END$
					$END$
				$END$
			$END$
		$END$
	$END$
	$i = i + 1$
$END$

$ ����ߥ����ӥ��롼�����ISR�ˤ˴ؤ��륨�顼�����å��ȳ���ߥϥ�ɥ������
$FOREACH order ISR.ORDER_LIST$
$	// �����ͥ�ɥᥤ��˽�°���Ƥ��ʤ�����E_RSATR��
	$IF !LENGTH(ISR.DOMAIN[order]) || ISR.DOMAIN[order] != TDOM_KERNEL$
		$ERROR ISR.TEXT_LINE[order]$E_RSATR: $FORMAT(_("%1% must belong to the kernel domain in %2%"), "interrupt service routine", "ATT_ISR")$$END$
	$END$

$	// isratr����TA_NULL�ˤǤʤ�����E_RSATR��
	$IF (ISR.ISRATR[order] & ~TARGET_ISRATR) != 0$
		$ERROR ISR.TEXT_LINE[order]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' in %3%"), "isratr", ISR.ISRATR[order], "ATT_ISR")$$END$
	$END$

$	// intno��ATT_ISR���Ф��������ֹ�Ȥ����������ʤ�����E_PAR��
	$IF !LENGTH(FIND(INTNO_ATTISR_VALID, ISR.INTNO[order]))$
		$ERROR ISR.TEXT_LINE[order]$E_PAR: $FORMAT(_("illegal %1% `%2%\' in %3%"), "intno", ISR.INTNO[order], "ATT_ISR")$$END$
	$END$

$	// (TMIN_ISRPRI <= isrpri && isrpri <= TMAX_ISRPRI)�Ǥʤ�����E_PAR��
	$IF !(TMIN_ISRPRI <= ISR.ISRPRI[order] && ISR.ISRPRI[order] <= TMAX_ISRPRI)$
		$ERROR ISR.TEXT_LINE[order]$E_PAR: $FORMAT(_("illegal %1% `%2%\' in %3%"), "isrpri", ISR.ISRPRI[order], "ATT_ISR")$$END$
	$END$
$END$

$FOREACH intno INTNO_ATTISR_VALID$
	$inhno = INHNO[intno]$

$	// ������ֹ�intno���Ф�����Ͽ���줿ISR�Υꥹ�Ȥκ���
	$isr_order_list = {}$
	$FOREACH order ISR.ORDER_LIST$
		$IF ISR.INTNO[order] == intno$
			$isr_order_list = APPEND(isr_order_list, order)$
			$order_for_error = order$
		$END$
	$END$

$	// ������ֹ�intno���Ф�����Ͽ���줿ISR��¸�ߤ�����
	$IF LENGTH(isr_order_list) > 0$
$		// intno���б�����inhno���Ф���DEF_INH���������E_OBJ��
		$IF LENGTH(INH.INHNO[inhno])$
			$ERROR ISR.TEXT_LINE[order_for_error]$E_OBJ: $FORMAT(_("%1% `%2%\' in %3% is duplicated with %4% `%5%\'"), "intno", ISR.INTNO[order_for_error], "ATT_ISR", "inhno", INH.INHNO[inhno])$$END$
		$END$

$		// intno���Ф���CFG_INT���ʤ�����E_OBJ��
		$IF !LENGTH(INT.INTNO[intno])$
			$ERROR ISR.TEXT_LINE[order_for_error]$E_OBJ: $FORMAT(_("%1% `%2%\' is not configured with %3%"), "intno", ISR.INTNO[order_for_error], "CFG_INT")$$END$
		$ELSE$
$			// intno���Ф���CFG_INT�����ꤵ�줿�����ͥ���٤�TMIN_INTPRI
$			// ���⾮��������E_OBJ��
			$IF INT.INTPRI[intno] < TMIN_INTPRI$
				$ERROR INT.TEXT_LINE[intno]$E_OBJ: $FORMAT(_("%1% `%2%\' configured for %3% `%4%\' is higher than %5%"), "intpri", INT.INTPRI[intno], "intno", ISR.INTNO[order_for_error], "TMIN_INTPRI")$$END$
			$END$
		$END$

$		// DEF_INH(inhno, { TA_NULL, _kernel_inthdr_<intno> } );
		$INH.INHNO[inhno] = inhno$
		$INH.INHATR[inhno] = VALUE("TA_NULL", 0)$
		$INH.INTHDR[inhno] = CONCAT("_kernel_inthdr_", intno)$
		$INH.ORDER_LIST = APPEND(INH.ORDER_LIST, inhno)$

$		// ISR�Ѥγ���ߥϥ�ɥ�
		void$NL$
		_kernel_inthdr_$intno$(void)$NL$
		{$NL$
		$IF LENGTH(isr_order_list) > 1$
			$TAB$PRI	saved_ipm;$NL$
			$NL$
			$TAB$i_begin_int($intno$);$NL$
			$TAB$saved_ipm = i_get_ipm();$NL$
		$ELSE$
			$TAB$i_begin_int($intno$);$NL$
		$END$
$		// ISR��ͥ���ٽ�˸ƤӽФ�
		$JOINEACH order SORT(isr_order_list, "ISR.ISRPRI") "\tif (i_sense_lock()) {\n\t\ti_unlock_cpu();\n\t}\n\ti_set_ipm(saved_ipm);\n"$
			$TAB$LOG_ISR_ENTER($intno$);$NL$
			$TAB$((ISR)($ISR.ISR[order]$))((intptr_t)($ISR.EXINF[order]$));$NL$
			$TAB$LOG_ISR_LEAVE($intno$);$NL$
		$END$
		$TAB$i_end_int($intno$);$NL$
		}$NL$
	$END$
$END$
$NL$

$
$  ����ߴ�����ǽ�Τ����ɸ��Ū�ʽ�������������
$
$ ����ߥϥ�ɥ�ν������ɬ�פʾ���
$IF !OMIT_INITIALIZE_INTERRUPT || ALT(USE_INHINIB_TABLE,0)$

$ ����ߥϥ�ɥ��
#define TNUM_INHNO	$LENGTH(INH.ORDER_LIST)$$NL$
const uint_t _kernel_tnum_inhno = TNUM_INHNO;$NL$
$NL$
$FOREACH inhno INH.ORDER_LIST$
	$IF (INH.INHATR[inhno] & TA_NONKERNEL) == 0$
		INTHDR_ENTRY($INH.INHNO[inhno]$, $+INH.INHNO[inhno]$, $INH.INTHDR[inhno]$)$NL$
	$END$
$END$
$NL$

$ ����ߥϥ�ɥ������ơ��֥�
$IF LENGTH(INH.ORDER_LIST)$
	const INHINIB _kernel_inhinib_table[TNUM_INHNO] = {$NL$
	$JOINEACH inhno INH.ORDER_LIST ",\n"$
		$IF (INH.INHATR[inhno] & TA_NONKERNEL) == 0$
			$TAB${ ($INH.INHNO[inhno]$), ($INH.INHATR[inhno]$), (FP)(INT_ENTRY($INH.INHNO[inhno]$, $INH.INTHDR[inhno]$)) }
		$ELSE$
			$TAB${ ($INH.INHNO[inhno]$), ($INH.INHATR[inhno]$), (FP)($INH.INTHDR[inhno]$) }
		$END$
	$END$$NL$
	};$NL$
$ELSE$
	TOPPERS_EMPTY_LABEL(const INHINIB, _kernel_inhinib_table);$NL$
$END$$NL$
$END$

$ ������׵�饤��ν������ɬ�פʾ���
$IF !OMIT_INITIALIZE_INTERRUPT || ALT(USE_INTINTB_TABLE,0)$

$ ������׵�饤���
#define TNUM_INTNO	$LENGTH(INT.ORDER_LIST)$$NL$
const uint_t _kernel_tnum_intno = TNUM_INTNO;$NL$
$NL$

$ ������׵�饤�������ơ��֥�
$IF LENGTH(INT.ORDER_LIST)$
	const INTINIB _kernel_intinib_table[TNUM_INTNO] = {$NL$
	$JOINEACH intno INT.ORDER_LIST ",\n"$
		$TAB${ ($INT.INTNO[intno]$), ($INT.INTATR[intno]$), ($INT.INTPRI[intno]$) }
	$END$$NL$
	};$NL$
$ELSE$
	TOPPERS_EMPTY_LABEL(const INTINIB, _kernel_intinib_table);$NL$
$END$$NL$
$END$

$
$  CPU�㳰������ǽ
$
/*$NL$
$SPC$*  CPU Exception Management Functions$NL$
$SPC$*/$NL$
$NL$

$ CPU�㳰�ϥ�ɥ�˴ؤ��륨�顼�����å�
$i = 0$
$FOREACH excno EXC.ORDER_LIST$
$	// �����ͥ�ɥᥤ��˽�°���Ƥ��ʤ�����E_RSATR��
	$IF !LENGTH(EXC.DOMAIN[excno]) || EXC.DOMAIN[excno] != TDOM_KERNEL$
		$ERROR EXC.TEXT_LINE[excno]$E_RSATR: $FORMAT(_("%1% `%2%\' must belong to the kernel domain in %3%"), "CPU exception handler", EXC.EXCNO[excno], "DEF_EXC")$$END$
	$END$

$	// excno��DEF_EXC���Ф���CPU�㳰�ϥ�ɥ��ֹ�Ȥ����������ʤ�����E_PAR��
	$IF !LENGTH(FIND(EXCNO_DEFEXC_VALID, EXC.EXCNO[excno]))$
		$ERROR EXC.TEXT_LINE[excno]$E_PAR: $FORMAT(_("illegal %1% `%2%\' in %3%"), "excno", EXC.EXCNO[excno], "DEF_EXC")$$END$
	$END$

$	// excno��DEF_EXC�ˤ�ä�����Ѥߤξ���E_OBJ��
	$j = 0$
	$FOREACH excno2 EXC.ORDER_LIST$
		$IF j < i && EXC.EXCNO[excno] == EXC.EXCNO[excno2]$
			$ERROR EXC.TEXT_LINE[excno]$E_OBJ: $FORMAT(_("%1% `%2%\' in %3% is duplicated"), "excno", EXC.EXCNO[excno], "DEF_EXC")$$END$
		$END$
		$j = j + 1$
	$END$

$	// excatr����TA_NULL�ˤǤʤ�����E_RSATR��
	$IF (EXC.EXCATR[excno] & ~TARGET_EXCATR) != 0$
		$ERROR EXC.TEXT_LINE[excno]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of %3% `%4%\' in %5%"), "excatr", EXC.EXCATR[excno], "excno", EXC.EXCNO[excno], "DEF_EXC")$$END$
	$END$
	$i = i + 1$
$END$

$ CPU�㳰�ϥ�ɥ�Τ����ɸ��Ū�ʽ�������������
$IF !OMIT_INITIALIZE_EXCEPTION$

$ CPU�㳰�ϥ�ɥ��
#define TNUM_EXCNO	$LENGTH(EXC.ORDER_LIST)$$NL$
const uint_t _kernel_tnum_excno = TNUM_EXCNO;$NL$
$NL$
$FOREACH excno EXC.ORDER_LIST$
	EXCHDR_ENTRY($EXC.EXCNO[excno]$, $+EXC.EXCNO[excno]$, $EXC.EXCHDR[excno]$)$NL$
$END$
$NL$

$ CPU�㳰�ϥ�ɥ������ơ��֥�
$IF LENGTH(EXC.ORDER_LIST)$
	const EXCINIB _kernel_excinib_table[TNUM_EXCNO] = {$NL$
	$JOINEACH excno EXC.ORDER_LIST ",\n"$
		$TAB${ ($EXC.EXCNO[excno]$), ($EXC.EXCATR[excno]$), (FP)(EXC_ENTRY($EXC.EXCNO[excno]$, $EXC.EXCHDR[excno]$)) }
	$END$$NL$
	};$NL$
$ELSE$
	TOPPERS_EMPTY_LABEL(const EXCINIB, _kernel_excinib_table);$NL$
$END$$NL$
$END$

$
$  ��ĥ�����ӥ�������
$
/*$NL$
$SPC$*  Extended Service Calls$NL$
$SPC$*/$NL$
$NL$

$ ��ĥ�����ӥ�������˴ؤ��륨�顼�����å�
$ SVC_LIST�������Ѥߤγ�ĥ�����ӥ�������Υꥹ��
$
$FOREACH order SVC.ORDER_LIST$
$	// �����ͥ�ɥᥤ��˽�°���Ƥ��ʤ�����E_RSATR��
	$IF !LENGTH(SVC.DOMAIN[order]) || SVC.DOMAIN[order] != TDOM_KERNEL$
		$ERROR SVC.TEXT_LINE[order]$E_RSATR: $FORMAT(_("%1% `%2%\' must belong to the kernel domain in %3%"), "extended service call", SVC.FNCD[order], "DEF_SVC")$$END$
	$END$

$	// fncd��DEF_SVC���Ф��뵡ǽ�����ɤȤ����������ʤ�����E_PAR��
	$IF SVC.FNCD[order] <= 0$
		$ERROR SVC.TEXT_LINE[order]$E_PAR: $FORMAT(_("illegal %1% `%2%\' in %3%"), "fncd", SVC.FNCD[order], "DEF_SVC")$$END$
	$END$

$	// fncd��DEF_SVC�ˤ�ä�����Ѥߤξ���E_OBJ��
	$FOREACH order2 SVC_LIST$
		$IF SVC.FNCD[order] == SVC.FNCD[order2]$
			$ERROR SVC.TEXT_LINE[order]$E_OBJ: $FORMAT(_("%1% `%2%\' in %3% is duplicated"), "fncd", SVC.FNCD[order], "DEF_SVC")$$END$
		$END$
	$END$

$	// svcatr����TA_NULL�ˤǤʤ�����E_RSATR��
	$IF (SVC.SVCATR[order] & ~TARGET_SVCATR) != 0$
		$ERROR SVC.TEXT_LINE[order]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of %3% `%4%\' in %5%"), "svcatr", SVC.SVCATR[order], "fncd", SVC.FNCD[order], "DEF_SVC")$$END$
	$END$

	$svc_order[SVC.FNCD[order]] = order$
	$SVC_LIST = APPEND(SVC_LIST, order)$
$END$

$ ��ǽ�ֹ�κ�����
const FN _kernel_tmax_fncd = TMAX_FNCD;$NL$
$NL$

$ ��ĥ�����ӥ�������ʬ���ơ��֥������
$IF LENGTH(SVC.ORDER_LIST)$
	const SVCINIB _kernel_svcinib_table[TMAX_FNCD] = {$NL$
	$JOINEACH fncd RANGE(1, tmax_fncd) ",\n"$
		$IF LENGTH(svc_order[fncd])$
			$TAB${ (EXTSVC)($SVC.SVCRTN[svc_order[fncd]]$),
			$SPC$$SVC.STKSZ[svc_order[fncd]]$ }
		$ELSE$
			$TAB${ NULL, 0 }
		$END$
	$END$$NL$
	};$NL$
$ELSE$
	TOPPERS_EMPTY_LABEL(const EXTSVC, _kernel_svcinib_table);$NL$
$END$$NL$

$
$  �󥿥�������ƥ������ѤΥ����å��ΰ�
$
/*$NL$
$SPC$*  Stack Area for Non-task Context$NL$
$SPC$*/$NL$
$NL$

$IF !LENGTH(ICS.ORDER_LIST)$
$	// DEF_ICS���ʤ����Υǥե�����ͤ�����
	#ifdef DEFAULT_ISTK$NL$
	$NL$
	#define TOPPERS_ISTKSZ		DEFAULT_ISTKSZ$NL$
	#define TOPPERS_ISTK		DEFAULT_ISTK$NL$
	$NL$
	#else /* DEAULT_ISTK */$NL$
	$NL$
	$ALLOC_SSTACK("_kernel_istack", "DEFAULT_ISTKSZ")$
	#define TOPPERS_ISTKSZ		ROUND_STK_T(DEFAULT_ISTKSZ)$NL$
	#define TOPPERS_ISTK		_kernel_istack$NL$
	$NL$
	#endif /* DEAULT_ISTK */$NL$
$ELSE$
$	// �����ͥ�ɥᥤ��ΰϤߤ���ˤʤ�����E_RSATR��
	$IF !LENGTH(ICS.DOMAIN[1]) || ICS.DOMAIN[1] != TDOM_KERNEL$
		$ERROR ICS.TEXT_LINE[1]$E_RSATR: $FORMAT(_("%1% must be within the kernel domain"), "DEF_ICS")$$END$
	$END$

$	// ��ŪAPI��DEF_ICS�פ�ʣ�������E_OBJ��
	$IF LENGTH(ICS.ORDER_LIST) > 1$
		$ERROR$E_OBJ: $FORMAT(_("too many %1%"), "DEF_ICS")$$END$
	$END$

$	// istksz��0�����������å�����κǾ��͡�TARGET_MIN_ISTKSZ�ˤ���
$	// ����������E_PAR��
	$IF ICS.ISTKSZ[1] == 0 || (TARGET_MIN_ISTKSZ
									&& ICS.ISTKSZ[1] < TARGET_MIN_ISTKSZ)$
		$ERROR ICS.TEXT_LINE[1]$E_PAR: $FORMAT(_("%1% `%2%\' in %3% is too small"), "istksz", ICS.ISTKSZ[1], "DEF_ICS")$$END$
	$END$

$ 	// istksz�������å��ΰ�Υ������Ȥ����������ʤ�����E_PAR��
	$IF !EQ(ICS.ISTK[1], "NULL") && CHECK_STKSZ_ALIGN
							&& (ICS.ISTKSZ[1] & (CHECK_STKSZ_ALIGN - 1))$
		$ERROR ICS.TEXT_LINE[1]$E_PAR: $FORMAT(_("%1% `%2%\' in %3% is not aligned"), "istksz", ICS.ISTKSZ[1], "DEF_ICS")$$END$
	$END$

	$IF EQ(ICS.ISTK[1], "NULL")$
$		// �����å��ΰ�μ�ư���դ�
		$ALLOC_SSTACK("_kernel_istack", ICS.ISTKSZ[1])$
		#define TOPPERS_ISTKSZ		ROUND_STK_T($ICS.ISTKSZ[1]$)$NL$
		#define TOPPERS_ISTK		_kernel_istack$NL$
	$ELSE$
		#define TOPPERS_ISTKSZ		($ICS.ISTKSZ[1]$)$NL$
		#define TOPPERS_ISTK		($ICS.ISTK[1]$)$NL$
	$END$
$END$
$NL$

$ �󥿥�������ƥ������ѤΥ����å��ΰ�
const SIZE		_kernel_istksz = TOPPERS_ISTKSZ;$NL$
STK_T *const	_kernel_istk = TOPPERS_ISTK;$NL$
$NL$
#ifdef TOPPERS_ISTKPT$NL$
STK_T *const	_kernel_istkpt = TOPPERS_ISTKPT(TOPPERS_ISTK, TOPPERS_ISTKSZ);$NL$
#endif /* TOPPERS_ISTKPT */$NL$
$NL$

$
$  �����।�٥�ȴ���
$
/*$NL$
$SPC$*  Time Event Management$NL$
$SPC$*/$NL$
$NL$
TMEVTN   _kernel_tmevt_heap[TNUM_TSKID + TNUM_CYCID + TNUM_ALMID];$NL$
$NL$

$
$  �ƥ⥸�塼��ν�����ؿ�
$
/*$NL$
$SPC$*  Module Initialization Function$NL$
$SPC$*/$NL$
$NL$
void$NL$
_kernel_initialize_object(void)$NL$
{$NL$
$TAB$_kernel_initialize_task();$NL$
$IF LENGTH(SEM.ID_LIST)$$TAB$_kernel_initialize_semaphore();$NL$$END$
$IF LENGTH(FLG.ID_LIST)$$TAB$_kernel_initialize_eventflag();$NL$$END$
$IF LENGTH(DTQ.ID_LIST)$$TAB$_kernel_initialize_dataqueue();$NL$$END$
$IF LENGTH(PDQ.ID_LIST)$$TAB$_kernel_initialize_pridataq();$NL$$END$
$IF LENGTH(MTX.ID_LIST)$$TAB$_kernel_initialize_mutex();$NL$$END$
$IF LENGTH(MPF.ID_LIST)$$TAB$_kernel_initialize_mempfix();$NL$$END$
$IF LENGTH(CYC.ID_LIST)$$TAB$_kernel_initialize_cyclic();$NL$$END$
$IF LENGTH(ALM.ID_LIST)$$TAB$_kernel_initialize_alarm();$NL$$END$
#ifdef TOPPERS_SUPPORT_OVRHDR$NL$
$TAB$_kernel_initialize_overrun();$NL$
#endif /* TOPPERS_SUPPORT_OVRHDR */$NL$
$TAB$_kernel_initialize_interrupt();$NL$
$TAB$_kernel_initialize_exception();$NL$
}$NL$
$NL$

$
$  ������롼����μ¹Դؿ�
$
/*$NL$
$SPC$*  Initialization Routine$NL$
$SPC$*/$NL$
$NL$
void$NL$
_kernel_call_inirtn(void)$NL$
{$NL$
$FOREACH order INI.ORDER_LIST$
$	// �����ͥ�ɥᥤ��ΰϤߤ���ˤʤ�����E_RSATR��
	$IF !LENGTH(INI.DOMAIN[order]) || INI.DOMAIN[order] != TDOM_KERNEL$
		$ERROR INI.TEXT_LINE[order]$E_RSATR: $FORMAT(_("%1% must be within the kernel domain"), "ATT_INI")$$END$
	$END$

$ 	// iniatr����TA_NULL�ˤǤʤ�����E_RSATR��
	$IF INI.INIATR[order] != 0$
		$ERROR INI.TEXT_LINE[order]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of %3% `%4%\' in %5%"), "iniatr", INI.INIATR[order], "inirtn", INI.INIRTN[order], "ATT_INI")$$END$
	$END$
	$TAB$((INIRTN)($INI.INIRTN[order]$))((intptr_t)($INI.EXINF[order]$));$NL$
$END$
}$NL$
$NL$

$
$  ��λ�����롼����μ¹Դؿ�
$
/*$NL$
$SPC$*  Termination Routine$NL$
$SPC$*/$NL$
$NL$
void$NL$
_kernel_call_terrtn(void)$NL$
{$NL$
$FOREACH rorder TER.RORDER_LIST$
$	// �����ͥ�ɥᥤ��ΰϤߤ���ˤʤ�����E_RSATR��
	$IF !LENGTH(TER.DOMAIN[rorder]) || TER.DOMAIN[rorder] != TDOM_KERNEL$
		$ERROR TER.TEXT_LINE[rorder]$E_RSATR: $FORMAT(_("%1% must be within the kernel domain"), "ATT_TER")$$END$
	$END$

$ 	// teratr����TA_NULL�ˤǤʤ�����E_RSATR��
	$IF TER.TERATR[rorder] != 0$
		$ERROR TER.TEXT_LINE[rorder]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of %3% `%4%\' in %5%"), "teratr", TER.TERATR[rorder], "terrtn", TER.TERRTN[rorder], "ATT_TER")$$END$
	$END$
	$TAB$((TERRTN)($TER.TERRTN[rorder]$))((intptr_t)($TER.EXINF[rorder]$));$NL$
$END$
}$NL$
$NL$

$
$  ���ꥪ�֥������ȴ�����ǽ
$
/*$NL$
$SPC$*  Memory Object Management Functions$NL$
$SPC$*/$NL$
$NL$

$
$  �桼�������å��ΰ�����ֽ���η���
$
$ MO.STKORDER[moid]���桼�������å��ΰ�����֤�����
$
$IF !USE_REDZONE$
$ 	// ��åɥ����������Ǥʤ����ˤϡ��ɥᥤ����˥�����ID������֤��롥
	$FOREACH moid MO_USTACK_LIST$
		$MO.STKORDER[moid] = MO.TSKID[moid]$
	$END$
$ELSE$
$ 	// ��åɥ����������ˤ�����桼�������å��ΰ�����ֽ���η���
	$IF LENGTH(MO_USTACK_LIST)$
		$INCLUDE "kernel/redzone.tf"$
	$END$
$END$

$
$  �������Υ��ꥪ�֥������Ȥξ���βù�
$
$ �������Υ��ꥪ�֥������Ȥξ���ˡ��ʲ��ξ�����ɲäʤ����Ͻ������
$ ���롥
$
$ MO.MEMATR[moid]�����ꥪ�֥�������°��
$	TA_NOWRITE�����ꤵ��Ƥ�����ϡ�TA_MEMINI��TA_MEMPRSV�򥯥ꥢ����
$ MO.ACPTN1[moid]���̾����1�ʽ���ߡˤΥ����������ĥѥ�����
$	MO.MEMATR[moid]��TA_NOWRITE�����ꤵ��Ƥ������0�ˤ��롥
$ MO.CLASS[moid]�����ꥪ�֥������Ȥ����֤��뤿���ʬ���ɸ�ʥ�󥫤�
$				  ���֤�����Τߡ�
$	0��ɸ��Υ��ꥪ�֥�������°����ACPTN1��ACPTN2��ɸ��
$	  �ʥ������Υ桼�������å��ΰ�⤳���˴ޤ���
$	1��ɸ��Υ��ꥪ�֥�������°����ACPTN1�ޤ���ACPTN2��ɸ��Ǥʤ�
$	2��ɸ��Ǥʤ����ꥪ�֥�������°��
$	3��ɸ��Ǥʤ�����꡼�����ؤ�����
$ MO.SRPW[moid]����ͭ�꡼����ͭ�饤���ΰ褫���ʥ�󥫤����֤�����Τߡ�
$ MO.STDACPTN4[moid]��MO.ACPTN4[moid]��ɸ�फ����ɸ��ʤ�1��
$
$FOREACH moid RANGE(1, nummo)$
	$domptn = DEFAULT_ACPTN[MO.DOMAIN[moid]]$

	$IF (MO.MEMATR[moid] & TA_NOWRITE) != 0$
		$IF MO.LINKER[moid] && (REG.REGATR[MO.MEMREG[moid]] & TA_NOWRITE) != 0$
			$MO.MEMATR[moid] = MO.MEMATR[moid] & ~(TA_MEMINI|TA_MEMPRSV)$
		$END$
		$MO.ACPTN1[moid] = VALUE("0U", 0)$
	$END$

	$IF MO.LINKER[moid]$
		$MO.SRPW[moid] = 0$
		$IF MO.MEMREG[moid] == STANDARD_ROM$
			$IF (MO.MEMATR[moid] & TA_EXEC) != 0
								&& MO.MEMATR[moid] != MEMATR_TEXT
				|| (MO.MEMATR[moid] & TA_EXEC) == 0
								&& MO.MEMATR[moid] != MEMATR_RODATA$
				$MO.CLASS[moid] = 2$
			$ELIF MO.ACPTN2[moid] != domptn$
				$MO.CLASS[moid] = 1$
			$ELSE$
				$MO.CLASS[moid] = 0$
			$END$
		$ELIF MO.MEMREG[moid] == STANDARD_RAM$
			$IF MO.TYPE[moid] == TOPPERS_USTACK$
				$MO.CLASS[moid] = 0$
			$ELIF (MO.MEMATR[moid] & TA_MEMINI) != 0
								&& MO.MEMATR[moid] != MEMATR_DATA
				|| (MO.MEMATR[moid] & TA_MEMPRSV) != 0
								&& MO.MEMATR[moid] != MEMATR_PRSV
				|| (MO.MEMATR[moid] & (TA_MEMINI|TA_MEMPRSV)) == 0
								&& MO.MEMATR[moid] != MEMATR_BSS$
				$MO.CLASS[moid] = 2$
			$ELIF MO.ACPTN1[moid] != domptn$
				$MO.CLASS[moid] = 1$
			$ELIF MO.ACPTN2[moid] != domptn$
				$MO.CLASS[moid] = 1$
				$IF MO.ACPTN2[moid] == TACP_SHARED$
					$MO.SRPW[moid] = 1$
				$END$
			$ELSE$
				$MO.CLASS[moid] = 0$
			$END$
		$ELSE$
			$MO.CLASS[moid] = 3$
		$END$
	$END$

	$IF MO.ACPTN4[moid] == domptn$
		$MO.STDACPTN4[moid] = 1$
	$ELSE$
		$MO.STDACPTN4[moid] = 0$
	$END$
$END$

$
$  �������Υ��ꥪ�֥������Ȥ򥽡��Ȥ��뤿����������
$
$ MO.ORDER[moid]�����ꥪ�֥������Ȥ򥽡��Ȥ��뤿���1����ɸ
$ MO.MEMATR1[moid]�������Ȥ���ݤˡ�ACPTN1��ACPTN2�������Ѥ���°��
$ MO.MEMATR2[moid]�������Ȥ���ݤˡ�ACPTN1��ACPTN2������Ѥ���°��
$
$FOREACH moid RANGE(1, nummo)$
$	// �ޤ�������꡼������ֹ�ν�˥����Ȥ��롥
	$IF MO.LINKER[moid]$
		$memreg = MO.MEMREG[moid]$
	$ELSE$
$		// ��󥫤����֤��ʤ���Τϡ��Ǹ�ˤ��롥
		$memreg = LENGTH(REG.ORDER_LIST) + 1$
	$END$
	$order = memreg$

$	// ���硼�ȥǡ�������������ǽ�����֤���
	$IF (MO.MEMATR[moid] & TA_SDATA) != 0$
		$sdata = 0$
	$ELSE$
		$sdata = 1$
	$END$
	$order = (order << 1) + sdata$

$	// ���ˡ��ݸ�ɥᥤ��ˤ�äƥ����Ȥ��롥
	$IF MO.TYPE[moid] == TOPPERS_USTACK$
$		// �桼�������å��ΰ�ϡ������ͥ�ɥᥤ���ľ������֤��롥
		$type = 1$
$		// ��åɥ����������Ǥʤ����ϡ��ݸ�ɥᥤ��ID�ν�����֤��롥
		$IF !USE_REDZONE$
			$domain = MO.DOMAIN[moid] - 1$
		$END$
	$ELIF MO.DOMAIN[moid] == TDOM_KERNEL$
$		// �����ͥ�ɥᥤ��Ϻǽ�����֤��롥
		$type = 0$
		$domain = 0$
	$ELIF MO.DOMAIN[moid] == TDOM_NONE$
$		// ̵��°�ϺǸ�����֤��롥
		$type = 4$
		$domain = 0$
	$ELSE$
$		// �桼���ɥᥤ��ϡ��ݸ�ɥᥤ��ID�ν�����֤��롥
		$domain = MO.DOMAIN[moid] - 1$
		$IF LENGTH(MO.SRPW[moid]) && MO.SRPW[moid]$
$			// ��ͭ�꡼����ͭ�饤���ΰ�ϡ��桼���ɥᥤ��θ��
$			// �ޤȤ�����֤��롥
			$type = 3$
		$ELSE$
			$type = 2$
		$END$
	$END$
	$order = (order << 3) + type$
	$order = (order << 5) + domain$

$	// ���ˡ����ꥪ�֥������Ȥ����֤��뤿���ʬ���ɸ�ˤ�ä����֤��롥
	$class = 0$
	$IF MO.LINKER[moid] && MO.TYPE[moid] != TOPPERS_USTACK$
		$IF MO.MEMREG[moid] == STANDARD_ROM$
			$IF MO.DOMAIN[moid] == TDOM_NONE$
$				// ɸ��ROM�꡼������̵��°�ϡ�CLASS�εս�����֤��롥
				$class = 3 - MO.CLASS[moid]$
			$ELSE$
$				// �����ͥ�ɥᥤ��ȥ桼���ɥᥤ��ϡ�CLASS�ν�����֤��롥
				$class = MO.CLASS[moid]$
			$END$
		$ELIF MO.MEMREG[moid] == STANDARD_RAM$
			$IF MO.DOMAIN[moid] == TDOM_KERNEL || MO.DOMAIN[moid] == TDOM_NONE$
$				// ɸ��RAM�꡼�����Υ����ͥ�ɥᥤ���̵��°�ϡ�
$				// CLASS�εս�����֤��롥
				$class = 3 - MO.CLASS[moid]$
			$ELSE$
$				// �桼���ɥᥤ��ϡ�CLASS�ν�����֤��롥
				$class = MO.CLASS[moid]$
			$END$
		$END$
	$END$
	$order = (order << 2) + class$

$	// ��̤�MO.ORDER[moid]�˳�Ǽ����
	$MO.ORDER[moid] = order$

$	// MO.MEMATR1[moid]��MO.MEMATR2[moid]�����ꤹ��
	$IF MO.LINKER[moid]$
		$IF (REG.REGATR[MO.MEMREG[moid]] & TA_NOWRITE) != 0$
			$MO.MEMATR1[moid] = MO.MEMATR[moid] & ~TA_EXEC$
			$MO.MEMATR2[moid] = MO.MEMATR[moid] & TA_EXEC$
$			// TA_EXEC�����ꤵ��Ƥ��������������֤���
			$MO.MEMATR2[moid] = MO.MEMATR2[moid] ^ TA_EXEC$
		$ELSE$
			$MO.MEMATR1[moid] = MO.MEMATR[moid] & ~(TA_MEMINI|TA_MEMPRSV)$
			$MO.MEMATR2[moid] = MO.MEMATR[moid] & (TA_MEMINI|TA_MEMPRSV)$
$			// TA_MEMINI�����ꤵ��Ƥ��������������֤���
			$MO.MEMATR2[moid] = MO.MEMATR2[moid] ^ TA_MEMINI$
		$END$
	$END$
$END$

$
$  ���ꥪ�֥������Ȥ򥽡��Ȥ��뤿�����Ӵؿ�
$
$IF !ISFUNCTION("MO_COMPARE")$
$FUNCTION MO_COMPARE$
$	�ޤ��ϡ�MO.ORDER����Ӥ��롥
	$RESULT = MO.ORDER[ARGV[1]] - MO.ORDER[ARGV[2]]$
	$IF (RESULT == 0) && MO.LINKER[ARGV[1]]$
$		// MO.ORDER��Ʊ���ǡ���󥫤������оݤξ��ϡ�����˥����Ȥ��롥
		$_moid1 = ARGV[1]$
		$_moid2 = ARGV[2]$
		$IF MO.TYPE[_moid1] == TOPPERS_USTACK$
$			// �桼�������å��ΰ�ξ��
$			// MO.STKORDER�ǥ����Ȥ��롥
			$RESULT = MO.STKORDER[_moid1] - MO.STKORDER[_moid2]$
		$ELIF MO.MEMATR1[_moid1] != MO.MEMATR1[_moid2]$
$			// MO.MEMATR1���ۤʤ�С�����ǥ����Ȥ��롥
			$RESULT = MO.MEMATR1[_moid1] - MO.MEMATR1[_moid2]$
		$ELIF MO.ACPTN1[_moid1] != MO.ACPTN1[_moid2]$
$			// MO.ACPTN1���ۤʤ�С�����ǥ����Ȥ��롥
			$RESULT = MO.ACPTN1[_moid1] - MO.ACPTN1[_moid2]$
		$ELIF MO.ACPTN2[_moid1] != MO.ACPTN2[_moid2]$
$			// MO.ACPTN2���ۤʤ�С�����ǥ����Ȥ��롥
			$RESULT = MO.ACPTN2[_moid1] - MO.ACPTN2[_moid2]$
		$ELIF MO.MEMATR2[_moid1] != MO.MEMATR2[_moid2]$
$			// MO.MEMATR2���ۤʤ�С�����ǥ����Ȥ��롥
			$RESULT = MO.MEMATR2[_moid1] - MO.MEMATR2[_moid2]$
		$ELIF MO.ACPTN4[_moid1] == MO.ACPTN4[_moid2]$
$			// MO.ACPTN4��Ʊ���Ǥ���С�����ǰʾ好���Ȥ��ʤ���
			$RESULT = 0$
		$ELIF MO.STDACPTN4[_moid1]$
			$IF MO.DOMAIN[_moid1] != TDOM_NONE$
$				// ̵��°�ʳ��Ǥϡ�ɸ���ACPTN4����Ĥ�Τ�������֤��롥
				$RESULT = -1$
			$ELSE$
$				// ̵��°�Ǥϡ�ɸ���ACPTN4����Ĥ�Τ������֤��롥
				$RESULT = 1$
			$END$
		$ELIF MO.STDACPTN4[_moid2]$
			$IF MO.DOMAIN[_moid1] != TDOM_NONE$
$				// ̵��°�ʳ��Ǥϡ�ɸ���ACPTN4����Ĥ�Τ�������֤��롥
				$RESULT = 1$
			$ELSE$
$				// ̵��°�Ǥϡ�ɸ���ACPTN4����Ĥ�Τ������֤��롥
				$RESULT = -1$
			$END$
		$ELSE$
$			// �ɤ����ɸ��Ǥʤ����ϡ�MO.MEMATR4�ǥ����Ȥ��롥
			$RESULT = MO.ACPTN4[_moid1] - MO.ACPTN4[_moid2]$
		$END$
	$END$
$END$
$END$

$
$  ���ꥪ�֥������ȤΥ�����
$
$ �ǽ��MO.ORDER�ǥ����Ȥ��Ƥ������Ȥǡ�MO_COMPARE��Ȥä������Ȥ���Ψ
$ ������뤳�Ȥ���Ԥ��Ƥ��롥
$
$MO_ORDER = SORT(RANGE(1, nummo), "MO.ORDER")$
$MO_ORDER = LSORT(MO_ORDER, "MO_COMPARE")$

$
$  ���ꥪ�֥������Ȥ��������
$
$ MO.SEFLAG[moid]���ʲ��ΥӥåȤΥӥå��������¤����ꤹ�롥
$	0x01��������������Ƭ
$	0x02�����������κǸ�
$	0x04�����ꥪ�֥������Ȥ���Ƭ
$	0x08�����ꥪ�֥������ȤκǸ�
$	0x10�������ݸ�ñ�̤���Ƭ
$	0x20�������ݸ�ñ�̤κǸ�
$	0x40������꡼��������Ƭ
$	0x80������꡼�����κǸ�
$	0x100����ͭ�꡼�����ѥ饤���ΰ����Τ���Ƭ
$	0x200����ͭ�꡼�����ѥ饤���ΰ����ΤκǸ�
$ MO.MOEND[moid]�������Υ��ꥪ�֥������ȤκǸ��moid��������
$							���ꥪ�֥������Ȥ���Ƭ��moid���Ф��������
$ MO_SECTION_LIST��������������Ƭ�Υꥹ��
$ MO_START_LIST�����ꥪ�֥������Ȥ���Ƭ�Υꥹ��
$ MO_START_LIST_NOLINKER����󥫤����֤��ʤ����ꥪ�֥������Ȥ���Ƭ�Υꥹ��
$ MO_MPROTECT_LIST�������ݸ�ñ�̤���Ƭ�Υꥹ��
$
$MO_SECTION_LIST = {}$
$MO_START_LIST = {}$
$MO_START_LIST_NOLINKER = {}$
$MO_MPROTECT_LIST = {}$
$i = 0$
$FOREACH moid MO_ORDER$
	$IF i == 0$
		$MO.SEFLAG[moid] = 0x15$
		$mostart = moid$
		$IF MO.LINKER[moid]$
			$MO.SEFLAG[moid] = MO.SEFLAG[moid] | 0x40$
		$END$
	$ELSE$
		$IF MO.ORDER[moid] != MO.ORDER[prev_moid]
				|| (MO.TYPE[moid] & TOPPERS_ATTSEC) == 0
				|| (MO.TYPE[prev_moid] & TOPPERS_ATTSEC) == 0
				|| (MO.MEMATR[moid] & ~(TA_MEMINI|TA_MEMPRSV))
						!= (MO.MEMATR[prev_moid] & ~(TA_MEMINI|TA_MEMPRSV))
				|| MO.ACPTN1[moid] != MO.ACPTN1[prev_moid]
				|| MO.ACPTN2[moid] != MO.ACPTN2[prev_moid]$
			$MO.SEFLAG[moid] = 0x15$
			$MO.SEFLAG[prev_moid] = MO.SEFLAG[prev_moid] | 0x2a$
			$MO.MOEND[mostart] = prev_moid$
			$mostart = moid$
		$ELIF MO.MEMATR[moid] != MO.MEMATR[prev_moid]$
			$MO.SEFLAG[moid] = 0x05$
			$MO.SEFLAG[prev_moid] = MO.SEFLAG[prev_moid] | 0x0a$
			$MO.MOEND[mostart] = prev_moid$
			$mostart = moid$
		$ELIF MO.ACPTN4[moid] != MO.ACPTN4[prev_moid]$
			$MO.SEFLAG[moid] = 0x04$
			$MO.SEFLAG[prev_moid] = MO.SEFLAG[prev_moid] | 0x08$
			$MO.MOEND[mostart] = prev_moid$
			$mostart = moid$
		$ELSE$
			$MO.SEFLAG[moid] = 0$
		$END$

		$IF MO.LINKER[prev_moid] && MO.LINKER[moid]
					&& MO.MEMREG[prev_moid] != MO.MEMREG[moid]$
			$MO.SEFLAG[moid] = MO.SEFLAG[moid] | 0x40$
			$MO.SEFLAG[prev_moid] = MO.SEFLAG[prev_moid] | 0x80$
		$ELIF MO.LINKER[prev_moid] && !MO.LINKER[moid]$
			$MO.SEFLAG[prev_moid] = MO.SEFLAG[prev_moid] | 0x80$
		$END$

		$IF !(MO.LINKER[prev_moid] && MO.SRPW[prev_moid])
					&& (MO.LINKER[moid] && MO.SRPW[moid])$
			$MO.SEFLAG[moid] = MO.SEFLAG[moid] | 0x100$
		$END$
		$IF (MO.LINKER[prev_moid] && MO.SRPW[prev_moid])
					&& !(MO.LINKER[moid] && MO.SRPW[moid])$
			$MO.SEFLAG[prev_moid] = MO.SEFLAG[prev_moid] | 0x200$
		$END$
	$END$

$	// MO_SECTION_LIST��MO_START_LIST��MO_MPROTECT_LIST�ؤ��ɲ�
	$IF (MO.SEFLAG[moid] & 0x01) != 0$
		$MO_SECTION_LIST = APPEND(MO_SECTION_LIST, moid)$
	$END$
	$IF (MO.SEFLAG[moid] & 0x04) != 0$
		$MO_START_LIST = APPEND(MO_START_LIST, moid)$
		$IF (!MO.LINKER[moid])$
			$MO_START_LIST_NOLINKER = APPEND(MO_START_LIST_NOLINKER, moid)$
		$END$
	$END$
	$IF (MO.SEFLAG[moid] & 0x10) != 0$
		$MO_MPROTECT_LIST = APPEND(MO_MPROTECT_LIST, moid)$
	$END$

	$prev_moid = moid$
	$i = i + 1$
$END$
$MO.SEFLAG[prev_moid] = MO.SEFLAG[prev_moid] | 0x2a$
$MO.MOEND[mostart] = prev_moid$
$IF MO.LINKER[prev_moid]$
	$MO.SEFLAG[prev_moid] = MO.SEFLAG[prev_moid] | 0x80$
$END$
$IF MO.LINKER[prev_moid] && MO.SRPW[prev_moid]$
	$MO.SEFLAG[prev_moid] = MO.SEFLAG[prev_moid] | 0x200$
$END$

$
$  ���ꥪ�֥������ȤΥ�٥������
$
$ MO.SLABEL[moid]�����������Υ�٥�
$ MO.ILABEL[moid]��������ǡ����ΰ�Υ�٥�
$ MO.MLABEL[moid]�����ꥪ�֥������ȤΥ�٥�
$ MO.PLABEL[moid]�������ݸ�ñ�̤Υ�٥�
$ DATASEC_LIST��data���������Υꥹ��
$ BSSSEC_LIST��bss���������Υꥹ��
$
$DATASEC_LIST = {}$
$BSSSEC_LIST = {}$
$FOREACH moid MO_ORDER$
	$IF MO.LINKER[moid]$
		$domlabel = DOM.LABEL[MO.DOMAIN[moid]]$
		$IF (REG.REGATR[MO.MEMREG[moid]] & TA_NOWRITE) != 0$
			$IF (MO.MEMATR[moid] & TA_EXEC) != 0$
				$typelabel = "text"$
			$ELSE$
				$typelabel = "rodata"$
			$END$
			$acptn12 = FORMAT("%x", +MO.ACPTN2[moid])$
			$plabel = ""$
		$ELSE$
			$IF (MO.MEMATR[moid] & TA_MEMINI) != 0$
				$typelabel = "data"$
				$IF (MO.SEFLAG[moid] & 0x01) != 0$
					$DATASEC_LIST = APPEND(DATASEC_LIST, moid)$
				$END$
			$ELIF (MO.MEMATR[moid] & TA_MEMPRSV) != 0$
				$typelabel = "prsv"$
			$ELSE$
				$typelabel = "bss"$
				$IF (MO.SEFLAG[moid] & 0x01) != 0$
					$BSSSEC_LIST = APPEND(BSSSEC_LIST, moid)$
				$END$
			$END$
			$acptn12 = FORMAT("%x_%x", +MO.ACPTN1[moid], +MO.ACPTN2[moid])$
			$plabel = FORMAT("%s_%s", "ram", domlabel)$
		$END$
		$label = FORMAT("%s_%s", typelabel, domlabel)$
		$IF EQ(typelabel, "data")$
			$ilabel = FORMAT("idata_%s", domlabel)$
		$ELSE$
			$ilabel = ""$
		$END$

		$IF MO.TYPE[moid] == TOPPERS_USTACK$
			$MO.SLABEL[moid] = REGEX_REPLACE(MO.SECTION[moid], "\\.", "")$
			$MO.MLABEL[moid] = REGEX_REPLACE(MO.SECTION[moid], "\\.", "")$
			$MO.PLABEL[moid] = ""$
		$ELIF MO.CLASS[moid] == 0$
			$MO.SLABEL[moid] = label$
			$IF !EQ(ilabel, "")$
				$MO.ILABEL[moid] = ilabel$
			$END$
			$IF MO.STDACPTN4[moid]$
				$MO.MLABEL[moid] = FORMAT("%s__std", label)$
			$ELSE$
				$MO.MLABEL[moid] = FORMAT("%s__%x", label, +MO.ACPTN4[moid])$
			$END$
			$IF !EQ(plabel, "")$
				$MO.PLABEL[moid] = plabel$
			$END$
		$ELIF MO.CLASS[moid] == 1$
			$MO.SLABEL[moid] = FORMAT("%s_%s", label, acptn12)$
			$IF !EQ(ilabel, "")$
				$MO.ILABEL[moid] = FORMAT("%s_%s", ilabel, acptn12)$
			$END$
			$MO.MLABEL[moid] = FORMAT("%s__%s_%x", label,
												acptn12, +MO.ACPTN4[moid])$
			$IF !EQ(plabel, "")$
				$MO.PLABEL[moid] = FORMAT("%s_%s", plabel, acptn12)$
			$END$
		$ELIF MO.CLASS[moid] == 2$
			$MO.SLABEL[moid] = FORMAT("%s_%x_%s", label,
												+MO.MEMATR[moid], acptn12)$
			$IF !EQ(ilabel, "")$
				$MO.ILABEL[moid] = FORMAT("%s_%x_%s", ilabel,
												+MO.MEMATR[moid], acptn12)$
			$END$
			$MO.MLABEL[moid] = FORMAT("%s__%x_%s_%x", label,
								+MO.MEMATR[moid], acptn12, +MO.ACPTN4[moid])$
			$IF !EQ(plabel, "")$
				$MO.PLABEL[moid] = FORMAT("%s_%x_%s", plabel,
						MO.MEMATR[moid] & ~(TA_MEMINI|TA_MEMPRSV), acptn12)$
			$END$
		$ELSE$
			$regname = REG.REGNAME[MO.MEMREG[moid]]$
			$MO.SLABEL[moid] = FORMAT("%s_%s_%x_%s", regname, label,
												+MO.MEMATR[moid], acptn12)$
			$IF !EQ(ilabel, "")$
				$MO.ILABEL[moid] = FORMAT("%s_%s_%x_%s", regname, ilabel,
												+MO.MEMATR[moid], acptn12)$
			$END$
			$MO.MLABEL[moid] = FORMAT("%s_%s__%x_%s_%x", regname, label,
								+MO.MEMATR[moid], acptn12, +MO.ACPTN4[moid])$
			$IF !EQ(plabel, "")$
				$MO.PLABEL[moid] = FORMAT("%s_%s_%x_%s", regname, plabel,
						MO.MEMATR[moid] & ~(TA_MEMINI|TA_MEMPRSV), acptn12)$
			$END$
		$END$
	$END$
$END$

$ =====================================================================
$ ���Υ��깽����������ե����������
$ =====================================================================
$FILE "kernel_mem2.c"$

$
$  �����ꥪ�֥������Ƚ�����֥�å�������
$
$IF !OMIT_STANDARD_MEMINIB$
$	// ���ɥ쥹0���֤��ΰ�
	$tsize_meminib = 1$
	$FOREACH moid MO_START_LIST$
$		// ���ꥪ�֥������Ȥ���Ƭ���Ϥ��֤��ΰ�
		$tsize_meminib = tsize_meminib + 1$
		$IF !MO.LINKER[moid]$
$			// ��󥫤����֤��ʤ����ꥪ�֥������ȤϺǽ����Ϥ�ɬ��
			$tsize_meminib = tsize_meminib + 1$
		$ELIF (MO.SEFLAG[MO.MOEND[moid]] & 0x80) != 0$
$			// ����꡼�����κǸ�Υ��ꥪ�֥������ȤϺǽ����Ϥ�ɬ��
			$tsize_meminib = tsize_meminib + 1$
		$END$
	$END$

$	// �������åȰ�¸��tsize_meminib������������
	$IF ISFUNCTION("CALC_TSIZE_MEMINIB")$
		$CALC_TSIZE_MEMINIB()$
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
$IF !OMIT_IDATA && LENGTH(DATASEC_LIST)$
	$tnum_datasec = LENGTH(DATASEC_LIST)$
	const uint_t _kernel_tnum_datasec = $tnum_datasec$U;$NL$
	const DATASECINIB _kernel_datasecinib_table[$tnum_datasec$] =
	$SPC${{ 0, 0, 0 }};$NL$
$ELSE$
	const uint_t _kernel_tnum_datasec = 0U;$NL$
	TOPPERS_EMPTY_LABEL(const DATASECINIB, _kernel_datasecinib_table);$NL$
$END$$NL$

$
$  ��bss��������������֥�å�������
$
$IF LENGTH(BSSSEC_LIST)$
	$tnum_bsssec = LENGTH(BSSSEC_LIST)$
	const uint_t _kernel_tnum_bsssec = $tnum_bsssec$U;$NL$
	const BSSSECINIB _kernel_bsssecinib_table[$tnum_bsssec$] = {{ 0, 0 }};$NL$
$ELSE$
	const uint_t _kernel_tnum_bsssec = 0U;$NL$
	TOPPERS_EMPTY_LABEL(const BSSSECINIB, _kernel_bsssecinib_table);$NL$
$END$$NL$

$ =====================================================================
$  �ѥ�3�ʹߤ��Ϥ����������
$ =====================================================================

$FILE "cfg2_out.tf"$
$$ cfg2_out.tf$NL$
$NL$

$ STANDARD_ROM��STANDARD_RAM�ν���
$$STANDARD_ROM = $STANDARD_ROM$$$$NL$
$$STANDARD_RAM = $STANDARD_RAM$$$$NL$
$NL$

$ REG_ORDER�ν���
$$REG_ORDER = { $REG_ORDER$ }$$$NL$
$NL$

$ REG.*�ν���
$FOREACH reg REG.ORDER_LIST$
	$$REG.REGNAME[$reg$] = $REG.REGION[reg]$$$$NL$
	$$REG.REGATR[$reg$] = VALUE($ESCSTR(REG.REGATR[reg])$,
									$SPC$$+REG.REGATR[reg]$)$$$NL$
	$$REG.BASE[$reg$] = VALUE($ESCSTR(REG.BASE[reg])$,
									$SPC$$+REG.BASE[reg]$)$$$NL$
	$$REG.SIZE[$reg$] = VALUE($ESCSTR(REG.SIZE[reg])$,
									$SPC$$+REG.SIZE[reg]$)$$$NL$
	$NL$
$END$

$ MO_ORDER��MO_SECTION_LIST��MO_START_LIST��MO_START_LIST_NOLINKER��
$ MO_MPROTECT_LIST�ν���
$$MO_ORDER = { $MO_ORDER$ }$$$NL$
$NL$
$$MO_SECTION_LIST = { $MO_SECTION_LIST$ }$$$NL$
$NL$
$$MO_START_LIST = { $MO_START_LIST$ }$$$NL$
$NL$
$$MO_START_LIST_NOLINKER = { $MO_START_LIST_NOLINKER$ }$$$NL$
$NL$
$$MO_MPROTECT_LIST = { $MO_MPROTECT_LIST$ }$$$NL$
$NL$

$ tsize_meminib�ν���
$IF !OMIT_STANDARD_MEMINIB$
	$$tsize_meminib = $tsize_meminib$$$$NL$
	$NL$
$END$

$ MO.*�ν���
$FOREACH moid MO_ORDER$
	$$MO.TYPE[$moid$] = $MO.TYPE[moid]$$$$NL$
	$IF MO.TYPE[moid] == TOPPERS_ATTMOD$
		$$MO.MODULE[$moid$] = $ESCSTR(MO.MODULE[moid])$$$$NL$
	$ELIF MO.TYPE[moid] == TOPPERS_ATTMEM$
		$$MO.BASE[$moid$] = $ESCSTR(MO.BASE[moid])$$$$NL$
		$$MO.SIZE[$moid$] = VALUE($ESCSTR(MO.SIZE[moid])$,
									$SPC$$+MO.SIZE[moid]$)$$$NL$
		$IF LENGTH(MO.PADDR[moid])$
			$$MO.PADDR[$moid$] = VALUE($ESCSTR(MO.PADDR[moid])$,
									$SPC$$+MO.PADDR[moid]$)$$$NL$
		$END$
	$ELIF MO.TYPE[moid] == TOPPERS_USTACK$
		$$MO.TSKID[$moid$] = VALUE($ESCSTR(MO.TSKID[moid])$,
									$SPC$$+MO.TSKID[moid]$)$$$NL$
		$IF !MO.LINKER[moid]$
			$$MO.BASE[$moid$] = $ESCSTR(MO.BASE[moid])$$$$NL$
			$$MO.SIZE[$moid$] = VALUE($ESCSTR(MO.SIZE[moid])$,
									$SPC$$+MO.SIZE[moid]$)$$$NL$
		$ELSE$
			$$MO.SIZE[$moid$] = $ESCSTR(MO.SIZE[moid])$$$$NL$
		$END$
		$IF LENGTH(MO.STKORDER[moid])$
			$$MO.STKORDER[$moid$] = $+MO.STKORDER[moid]$$$$NL$
		$END$
	$ELIF MO.TYPE[moid] == TOPPERS_MPFAREA$
		$$MO.MPFID[$moid$] = VALUE($ESCSTR(MO.MPFID[moid])$,
									$SPC$$+MO.MPFID[moid]$)$$$NL$
	$END$
	$$MO.LINKER[$moid$] = $MO.LINKER[moid]$$$$NL$
	$$MO.DOMAIN[$moid$] = VALUE($ESCSTR(MO.DOMAIN[moid])$,
									$SPC$$+MO.DOMAIN[moid]$)$$$NL$
	$IF MO.LINKER[moid]$
		$$MO.MEMREG[$moid$] = $MO.MEMREG[moid]$$$$NL$
		$$MO.SECTION[$moid$] = $ESCSTR(MO.SECTION[moid])$$$$NL$
		$$MO.CLASS[$moid$] = $MO.CLASS[moid]$$$$NL$
		$$MO.SRPW[$moid$] = $MO.SRPW[moid]$$$$NL$
		$$MO.MEMATR1[$moid$] = $MO.MEMATR1[moid]$$$$NL$
		$$MO.MEMATR2[$moid$] = $MO.MEMATR2[moid]$$$$NL$
	$END$
	$$MO.MEMATR[$moid$] = VALUE($ESCSTR(MO.MEMATR[moid])$,
									$SPC$$+MO.MEMATR[moid]$)$$$NL$
	$$MO.ACPTN1[$moid$] = VALUE($ESCSTR(MO.ACPTN1[moid])$,
									$SPC$$+MO.ACPTN1[moid]$)$$$NL$
	$$MO.ACPTN2[$moid$] = VALUE($ESCSTR(MO.ACPTN2[moid])$,
									$SPC$$+MO.ACPTN2[moid]$)$$$NL$
	$$MO.ACPTN4[$moid$] = VALUE($ESCSTR(MO.ACPTN4[moid])$,
									$SPC$$+MO.ACPTN4[moid]$)$$$NL$
	$IF LENGTH(MO.TEXT_LINE[moid])$
		$$MO.TEXT_LINE[$moid$] = VALUE($ESCSTR(MO.TEXT_LINE[moid])$,
									$SPC$$+MO.TEXT_LINE[moid]$)$$$NL$
	$END$
	$IF LENGTH(MO.APINAME[moid])$
		$$MO.APINAME[$moid$] = $ESCSTR(MO.APINAME[moid])$$$$NL$
	$END$
	$$MO.STDACPTN4[$moid$] = $MO.STDACPTN4[moid]$$$$NL$
	$$MO.ORDER[$moid$] = $MO.ORDER[moid]$$$$NL$
	$$MO.SEFLAG[$moid$] = 0x$FORMAT("%x", +MO.SEFLAG[moid])$$$$NL$
	$IF LENGTH(MO.MOEND[moid])$
		$$MO.MOEND[$moid$] = $MO.MOEND[moid]$$$$NL$
	$END$
	$$MO.SLABEL[$moid$] = $ESCSTR(MO.SLABEL[moid])$$$$NL$
	$$MO.ILABEL[$moid$] = $ESCSTR(MO.ILABEL[moid])$$$$NL$
	$$MO.MLABEL[$moid$] = $ESCSTR(MO.MLABEL[moid])$$$$NL$
	$$MO.PLABEL[$moid$] = $ESCSTR(MO.PLABEL[moid])$$$$NL$
	$NL$
$END$

$ LNKSEC.*�ν���
$$numls = $numls$$$$NL$
$NL$
$FOREACH lsid RANGE(1, numls)$
	$$LNKSEC.MEMREG[$lsid$] = $LNKSEC.MEMREG[lsid]$$$$NL$
	$$LNKSEC.SECTION[$lsid$] = $ESCSTR(LNKSEC.SECTION[lsid])$$$$NL$
	$NL$
$END$

$ DATASEC_LIST��BSSSEC_LIST�ν���
$$DATASEC_LIST = { $DATASEC_LIST$ }$$$NL$
$$BSSSEC_LIST = { $BSSSEC_LIST$ }$$$NL$
$NL$

$FILE "kernel_cfg.c"$
