$ ======================================================================
$
$   TOPPERS/HRP Kernel
$       Toyohashi Open Platform for Embedded Real-Time Systems/
$       High Reliable system Profile Kernel
$
$   Copyright (C) 2011 by Embedded and Real-Time Systems Laboratory
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
$   $Id: redzone.tf 471 2011-04-05 05:41:43Z ertl-hiro $
$  
$ =====================================================================

$ =====================================================================
$  ��åɥ����������ˤ�����桼�������å��ΰ�����ֽ���η���
$
$ ���������ֽ������ꤹ��Τϡ�����ե�����졼��������դ���桼����
$ ���å��ΰ�ΤߤǤ��ꡤ���ץꥱ������󤬻��ꤷ����Τ��оݤȤ��ʤ���
$ =====================================================================

$
$  �ɥᥤ����Υ桼�������å��ΰ�Υꥹ�Ȥκ����ȿ��Υ������
$
$ total_num_ustack���桼�������å��ΰ�ο��ι��
$ ustack_list_dom[domid]���ɥᥤ����Υ桼�������å��ΰ�Υꥹ��
$ max_num_ustack���ɥᥤ����Υ桼�������å��ΰ�ο��κ�����
$ max_ustack_dom���桼�������å��ΰ�ο�������Ǥ���ɥᥤ��

$total_num_ustack = 0$
$max_num_ustack = 0$
$FOREACH moid MO_USTACK_LIST$
	$total_num_ustack = total_num_ustack + 1$
	$ustack_list_dom[MO.DOMAIN[moid]]
					= APPEND(ustack_list_dom[MO.DOMAIN[moid]], moid)$
	$IF max_num_ustack < LENGTH(ustack_list_dom[MO.DOMAIN[moid]])$
		$max_num_ustack = LENGTH(ustack_list_dom[MO.DOMAIN[moid]])$
		$max_ustack_dom = MO.DOMAIN[moid]$
	$END$
$END$

$
$  ���ߡ������å��ΰ���ɲ�
$
$num_dummy = max_num_ustack * 2 - 1 - total_num_ustack$
$IF num_dummy > 0$
	$FOREACH dummy RANGE(1,num_dummy)$
$		// ���ߡ�������̾
		$dummy_name = FORMAT("TOPPERS_DUMMY%d", dummy)$

$		// ���ߡ������å��ΰ�γ���
		$ALLOC_USTACK_DUMMY(dummy_name, TARGET_DUMMY_STKSZ)$

$		// ���ߡ������å��ΰ�Υ��ꥪ�֥������Ⱦ��������
$		// ���ߡ������å��ΰ��°����ɥᥤ���̵��°�Ȥ���
		$nummo = nummo + 1$
		$MO.TYPE[nummo] = TOPPERS_USTACK$
		$MO.TSKID[nummo] = VALUE(dummy_name, 0)$
		$MO.SIZE[nummo] = TARGET_DUMMY_STKSZ$
		$MO.LINKER[nummo] = 1$
		$MO.MEMREG[nummo] = STANDARD_RAM$
		$MO.SECTION[nummo] = SECTION_USTACK(dummy_name)$
		$MO_USTACK_LIST = APPEND(MO_USTACK_LIST, nummo)$
		$MO.DOMAIN[nummo] = TDOM_NONE$
		$MO.MEMATR[nummo] = TARGET_MEMATR_USTACK$
		$MO.ACPTN1[nummo] = TACP_KERNEL$
		$MO.ACPTN2[nummo] = TACP_KERNEL$
		$MO.ACPTN4[nummo] = TACP_KERNEL$

		$total_num_ustack = total_num_ustack + 1$
		$ustack_list_dom[MO.DOMAIN[nummo]]
					= APPEND(ustack_list_dom[MO.DOMAIN[nummo]], nummo)$
	$END$
$END$

$
$  ���ֽ���η���
$

$ ���ֽ���γ�����ƴؿ�
$FUNCTION ASSIGN_STKORDER$
	$stkorder = stkorder + 1$
	$MO.STKORDER[AT(ustack_list_dom[ARGV[1]], at_dom[ARGV[1]])] = stkorder$
	$at_dom[ARGV[1]] = at_dom[ARGV[1]] + 1$

	$total_num_ustack = total_num_ustack - 1$
	$IF ARGV[1] == max_ustack_dom$
		$max_num_ustack = max_num_ustack - 1$
	$END$
$END$

$ at_dom[domid]�ν�����ʳ����Ǥ�0�ˤ����
$FOREACH domid DOMLIST_ALL$
	$at_dom[domid] = 0$
$END$

$ ���ֽ�����˳�����Ƥ�
$stkorder = 0$
$WHILE stkorder < LENGTH(MO_USTACK_LIST)$
	$FOREACH domid DOMLIST_ALL$
		$IF at_dom[domid] < LENGTH(ustack_list_dom[domid])$
			$IF domid != max_ustack_dom
								&& max_num_ustack * 2 > total_num_ustack$
				$ASSIGN_STKORDER(max_ustack_dom)$
			$END$
			$ASSIGN_STKORDER(domid)$
		$END$
	$END$
$END$
