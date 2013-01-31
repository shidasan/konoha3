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

$ $DEBUG_OPT_TF = 1$

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

$ MO_CLASS_LIST������
$ �����ݸ�°����Ʊ�����ꥪ�֥������Ȥ�ޤȤ᤿�ꥹ��
$prev = -1$
$FOREACH memtop MO_START_LIST$
    $IF (prev != -1)$
        $prev_idx = FIND(MO_ORDER, prev)$
        $curr_idx = FIND(MO_ORDER, memtop)$
        $IF (!LENGTH(prev_idx) || !LENGTH(curr_idx))$
            $ERROR$$FORMAT("error: cannot find mo %d", prev_idx)$$END$
        $ELSE$
            $WHILE (prev_idx < curr_idx)$
                $MO_CLASS_LIST[prev] = APPEND(MO_CLASS_LIST[prev], AT(MO_ORDER, prev_idx))$
                $prev_idx = prev_idx + 1$
            $END$
        $END$
    $END$

    $prev = memtop$
$END$

$moid = AT(MO_ORDER, curr_idx)$
$WHILE (curr_idx < LENGTH(MO_ORDER))$
    $MO_CLASS_LIST[memtop] = APPEND(MO_CLASS_LIST[memtop], moid)$
    $curr_idx = curr_idx + 1$
    $moid = AT(MO_ORDER, curr_idx)$
$END$

$ 
$  �����ݸ�ñ�̤μºݤΥ������������ꡤ������ä��������ʾ�ǡ�
$  ARM MPU�Υ�����������������Ǿ��ͤ��֤�
$  ARM MPU�Υ���������ϡ�32B~4GB���ϰϤ�2�Τ٤���
$  ARGV[1]���ºݤΥ�����
$  RESULT��ARM MPU�Υ�����������������Ǿ���
$FUNCTION SEARCH_ARM_MPU_SIZE$
    $IF ARGV[1] <= 0$
        $RESULT = 0$
    $ELSE$
        $search_state = 0$
        $FOREACH bit_offset { 31,30,...,5 }$
            $compare_bit = 1 << bit_offset$
            $IF ((ARGV[1] & compare_bit) != 0)$
                $IF (search_state == 0)$
                    $result_size = compare_bit$
                    $search_state = 1$
                $ELIF (search_state == 1)$
                    $result_size = (result_size << 1)$
                    $search_state = 2$
                $END$
            $END$
        $END$
        $IF (search_state == 0)$
            $result_size = (1 << 5)$
        $ELIF (search_state == 1) && ((ARGV[1] & 0x1f) != 0)$
            $result_size = (result_size << 1)$
        $END$
        $RESULT = result_size$
    $END$
$END$

$ 
$  ������ä����ϰʾ�ǡ�
$  ARM MPU�Υ��饤��������������Ǿ��ͤ��֤�
$  ARM MPU�Υ��饤������ϡ�32B~4GB���ϰϤ�2�Τ٤���
$  ARGV[1]������
$  RESULT��ARM MPU�Υ��饤��������������Ǿ���
$FUNCTION ARM_MPU_ALIGN$
    $compare_mask = 0x0f$
    $result_addr = ARGV[1] & (~compare_mask)$
    $IF ((ARGV[1] & compare_mask) != 0)$
       $result_addr = result_addr + 0x10$ 
    $END$
    $RESULT = result_addr$
$END$

$FUNCTION COMPARE_MO_SIZE$
    $RESULT = MO_BLOCK.SIZE[ARGV[1]] - MO_BLOCK.SIZE[ARGV[2]]$
$END$

$ 
$  ������ä����Ϥ���������ARM MPU�Υ��饤������κ����ͤ��֤�
$ 
$FUNCTION SEARCH_ARM_MPU_ALIGN$
    $IF ((ARGV[1] & 0x0f) != 0)$
        $ERROR$
            $FORMAT("error: not aligned. %x", ARGV[1])$$NL$
        $END$
    $END$
    $result_align = 0$
    $FOREACH bit_offset { 5,6,...,31 }$
        $compare_bit = 1 << bit_offset$
        $IF (!result_align && ((ARGV[1] & compare_bit) != 0))$
            $result_align = compare_bit$
        $END$
    $END$
    $IF !result_align$
        $result_align = 1 << 32$
    $END$
    $RESULT = result_align$
$END$

$FUNCTION COMPARE_NORMAL$
    $RESULT = ARGV[1] - ARGV[2]$
$END$

$FOREACH reg REG.ORDER$
    $MO_REG_LIST[reg] = {}$
$END$

$  =begin GENERATE_MEMINIB_TABLE
$FUNCTION GENERATE_MEMINIB_TABLE$
    /* generate meminib by target_opt.tf */
$  MO_BLOCK[moid]�����ꥪ�֥������Ȥ����֤��¤��ؤ���ñ��
$  MO_BLOCK.SIZE[moid]��MPU�Υ�����������������褦�˥��饤�󤷤�������
$  MO_BLOCK_LIST����������0�Ǥʤ�MO_BLOCK�Υꥹ��
$  MO_BLOCK.MO_LIST[moid]��MO_BLOCK�˴ޤޤ��MO�Υꥹ��

$  MO_BLOCK�η���
$prev = -1$
$mo_block_top = -1$
$MO_LIST_CACHE = {}$
$FOREACH moid MO_START_LIST$
    $IF LENGTH(FIND(MO_MPROTECT_LIST, moid))$
        $IF (mo_block_top != -1) && (!LENGTH(MO.SRPW[prev]) || !LENGTH(MO.SRPW[moid]) || !MO.SRPW[prev] || !MO.SRPW[moid])$
$           // MO_BLOCK�ν����
            $MO_BLOCK.LIMITADDR[mo_block_top] = MO.LIMITADDR[prev]$
            $IF LENGTH(DEBUG_OPT_TF)$
                $WARNING$pre MO_BLOCK.SIZE[$mo_block_top$] = $MO_BLOCK.LIMITADDR[mo_block_top] - MO_BLOCK.BASEADDR[mo_block_top]$$END$
            $END$
            $MO_BLOCK.SIZE[mo_block_top] = SEARCH_ARM_MPU_SIZE(MO_BLOCK.LIMITADDR[mo_block_top] - MO_BLOCK.BASEADDR[mo_block_top])$
            $IF LENGTH(DEBUG_OPT_TF)$
                $WARNING$MO_BLOCK.SIZE[$mo_block_top$] = $+MO_BLOCK.SIZE[mo_block_top]$$END$
            $END$
            $IF (MO_BLOCK.SIZE[mo_block_top] > 0)$
                $MO_BLOCK_LIST = APPEND(MO_BLOCK_LIST, mo_block_top)$
                $MO_BLOCK.MO_LIST[mo_block_top] = MO_LIST_CACHE$
                $IF LENGTH(DEBUG_OPT_TF)$
                    $WARNING$MO_LIST[$mo_block_top$] = $MO_BLOCK.MO_LIST[mo_block_top]$$END$
                    $WARNING$MO_BLOCK.SIZE[$mo_block_top$] = $+MO_BLOCK.SIZE[mo_block_top]$$END$
                $END$
            $END$
            $MO_LIST_CACHE = {}$
        $END$
        $IF (mo_block_top == -1) || !LENGTH(MO.SRPW[moid]) || !LENGTH(MO.SRPW[prev]) || !MO.SRPW[moid] || !MO.SRPW[prev]$
$           // MO_BLOCK����Ƭ
            $MO_BLOCK.BASEADDR[moid] = MO.BASEADDR[moid]$
            $mo_block_top = moid$
        $END$
    $END$
    
    $prev = moid$
    $MO_LIST_CACHE = APPEND(MO_LIST_CACHE, moid)$
$END$
$MO_BLOCK.LIMITADDR[mo_block_top] = MO.LIMITADDR[prev]$
$IF LENGTH(DEBUG_OPT_TF)$
    $WARNING$pre MO_BLOCK.SIZE[$mo_block_top$] = $MO_BLOCK.LIMITADDR[mo_block_top] - MO_BLOCK.BASEADDR[mo_block_top]$$END$
$END$
$MO_BLOCK.SIZE[mo_block_top] = SEARCH_ARM_MPU_SIZE(MO_BLOCK.LIMITADDR[mo_block_top] - MO_BLOCK.BASEADDR[mo_block_top])$
$IF LENGTH(DEBUG_OPT_TF)$
    $WARNING$MO_BLOCK.SIZE[$mo_block_top$] = $+MO_BLOCK.SIZE[mo_block_top]$$END$
$END$
$IF (MO_BLOCK.SIZE[mo_block_top] > 0)$
    $MO_BLOCK_LIST = APPEND(MO_BLOCK_LIST, mo_block_top)$
    $MO_BLOCK.MO_LIST[mo_block_top] = MO_LIST_CACHE$
    $IF LENGTH(DEBUG_OPT_TF)$
        $WARNING$MO_LIST[$mo_block_top$] = $MO_BLOCK.MO_LIST[mo_block_top]$$END$
        $WARNING$MO_BLOCK.SIZE[$mo_block_top$] = $+MO_BLOCK.SIZE[mo_block_top]$$END$
    $END$
$END$
$MO_LIST_CACHE = {}$

$IF LENGTH(DEBUG_OPT_TF)$
    $WARNING$MO_BLOCK_LIST: $MO_BLOCK_LIST$$END$
$END$
$ 
$  suppresszero�����ɥ쥹0���б����륨��ȥ����Ϥ��ʤ�
$  MO.SUPPRESSLIMIT[moid]����¥��ɥ쥹�Υ���ȥ����Ϥ��ʤ�
$  MO_REG_LIST[reg]��reg��°����MO_BLOCK�Υꥹ��
$  MO_NONREG_LIST��reg��°���ʤ�MO_BLOCK�Υꥹ��
$  CONTEXT_LIST��reg��mem��reg��°���ʤ�MO_BLOCK�ˤ�pass3�ǤΥ�󥯽���¤٤��ꥹ��
$  REG.REALBASE[reg]��MPU�Υ��饤��������������褦�˥��饤�󤷤�reg����Ƭ����

$  ����꡼�����˴ؤ�����������
$prev = 0$
$reg_state = -1$
$nonreg_no = 0$
$CONTEXT_LIST = {}$
$MO_TOP_SRPW = -1$
$MO_TOP_PROTECT = -1$
$FOREACH moid SORT(MO_BLOCK_LIST, "MO_BLOCK.BASEADDR")$
    $IF LENGTH(MO.MEMREG[moid])$
        $MO_REG_LIST[MO.MEMREG[moid]] = APPEND(MO_REG_LIST[MO.MEMREG[moid]], moid)$
        $IF ((LENGTH(current_reg) && (current_reg != MO.MEMREG[moid])) || (reg_state != 1))$
            $CONTEXT_LIST = APPEND(CONTEXT_LIST, VALUE("REG",MO.MEMREG[moid]))$
            $reg_state = 1$
            $current_reg = MO.MEMREG[moid]$
        $END$
        $IF LENGTH(DEBUG_OPT_TF)$
            $WARNING$// append $moid$ to $MO.MEMREG[moid]$$END$
        $END$

        $IF !LENGTH(REG.REALBASE[MO.MEMREG[moid]])$
            $REG.REALBASE[MO.MEMREG[moid]] = ARM_MPU_ALIGN(MO_BLOCK.BASEADDR[moid])$
        $END$

    $ELSE$
        $IF reg_state != 0$
            $nonreg_no = nonreg_no + 1$
            $CONTEXT_LIST = APPEND(CONTEXT_LIST, VALUE("NONREG",+nonreg_no))$
            $reg_state = 0$
        $END$
        $MO_NONREG_LIST[nonreg_no] = APPEND(MO_NONREG_LIST[nonreg_no], moid)$
        $IF LENGTH(DEBUG_OPT_TF)$
            $WARNING$// $moid$ is not joined MEMREG (NO.$nonreg_no$)$END$
        $END$
    $END$

    $prev = moid$
$END$

$IF LENGTH(DEBUG_OPT_TF)$
    $WARNING$context list : $CONTEXT_LIST$$END$
$END$

$  MO_SIZE_REG_LIST[reg]��reg��°����MO_BLOCK�򥵥�������¤٤��ꥹ��
$  MO.REALBASE[moid]��MO_BLOCK������֤����������
$FOREACH reg REG_ORDER$
    $MO_SIZE_REG_LIST[reg] = LSORT(MO_REG_LIST[reg], "COMPARE_MO_SIZE")$
    $IF LENGTH(MO_SIZE_REG_LIST)$
        $IF LENGTH(DEBUG_OPT_TF)$
            $WARNING$// $FORMAT("{ %x:%x } ", REG.REALBASE[reg], SEARCH_ARM_MPU_ALIGN(REG.REALBASE[reg]))$ $END$
        $END$
    $END$

$   // �����
$   // MO_SIZEORDER_LIST_REG[reg]: �꡼����󤴤Ȥ˺����֤�����̤�MO_BLOCK��
$   //                             ���ֽ���Ǽ�����ꥹ��
    $SIZE_LIST = {}$
    $MO_SIZEORDER_LIST_REG[reg] = {}$
    $REG.LIMIT[reg] = 0$

$   // ���������Ȥ�����MO_LIST_SIZE[size]��MO_BLOCK��ʬ��
$   // SIZE_LIST��ʬ�व�줿size�򥵥�������¤٤��ꥹ��
    $FOREACH moid MO_SIZE_REG_LIST[reg]$
        $IF LENGTH(DEBUG_OPT_TF)$
            $WARNING${ $moid$, $MO_BLOCK.SIZE[moid]$ },$END$
        $END$
    
        $IF !LENGTH(FIND(SIZE_LIST, MO_BLOCK.SIZE[moid]))$
            $MO_LIST_SIZE[MO_BLOCK.SIZE[moid]] = { moid }$
            $SIZE_LIST = APPEND(SIZE_LIST, MO_BLOCK.SIZE[moid])$
        $ELSE$
            $MO_LIST_SIZE[MO_BLOCK.SIZE[moid]] = APPEND(MO_LIST_SIZE[MO_BLOCK.SIZE[moid]], moid)$
        $END$
    $END$
    $NL$
    $SIZE_LIST = LSORT(SIZE_LIST, "COMPARE_NORMAL")$

$   // MO_BLOCK���������Ϥ����
    $base = REG.REALBASE[reg]$
    $IF LENGTH(DEBUG_OPT_TF)$
        $WARNING$// !base=$base$: size_list=$SIZE_LIST$$END$
    $END$
    $WHILE (LENGTH(SIZE_LIST) > 0)$
$       // �����Хե������å�
        $IF (base >= (REG.BASE[reg] + REG.SIZE[reg]))$
            $ERROR$
                $FORMAT("error: overflow reg[%s], %x", reg, base)$
            $END$
            $DIE()$
        $END$
$       // align�������������Ƭ���Ϥ򥢥饤�󤷤����Ϥ���ARM MPU�ΤɤΥ���������
$       //        ���ܿ����򼨤�
        $align = SEARCH_ARM_MPU_ALIGN(base)$
        $IF LENGTH(DEBUG_OPT_TF)$
            $WARNING$$FORMAT("!base=%x,align=%x: ", base, align)$ $SIZE_LIST$$NL$$END$
        $END$
$       // ���饤�󤷤����Ϥ����ֲ�ǽ�ʥ������򥵡���
        $search_state = 0$
        $idx = -1$
        $WHILE ((idx < (LENGTH(SIZE_LIST) - 1)) && (search_state == 0))$
            $idx = idx + 1$
            $size = AT(SIZE_LIST, idx)$
            $IF (size >= align)$
                $search_state = 1$
            $END$
        $END$
        $IF (search_state == 0)$
            $idx = idx + 1$
        $END$

$       // MO_BLOCK�κ����֤����
        $TMP_LIST = {}$
        $idx0_flg = 1$
$       // size == align�ʤ�Ф��Υ�������MO_BLOCK�򤳤����Ϥ����֤���
        $IF (size == align)$
            $FOREACH moid MO_LIST_SIZE[size]$
                $IF idx0_flg$
                    $IF LENGTH(DEBUG_OPT_TF)$
                        $WARNING$// push {moid=$moid$,size=$size$}$NL$$END$
                    $END$
                    $MO.REALBASE[moid] = base$
                    $MO_SIZEORDER_LIST_REG[reg] = APPEND(MO_SIZEORDER_LIST_REG[reg], moid)$
                    $idx0_flg = 0$
                $ELSE$
                    $TMP_LIST = APPEND(TMP_LIST, moid)$
                $END$
            $END$
$           // MO_LIST_SIZE������Ƭ��MO_BLOCK����
            $MO_LIST_SIZE[size] = TMP_LIST$
$           // MO_LIST_SIZE�����ˤʤä���
            $IF (LENGTH(MO_LIST_SIZE[size]) == 0)$
                $FOREACH sz SIZE_LIST$
                    $IF (sz != size)$
                        $TMP_LIST = APPEND(TMP_LIST, sz)$
                    $END$
                $END$
$               // SIZE_LIST���餽�Υ���������
                $SIZE_LIST = TMP_LIST$
            $END$
            $IF LENGTH(DEBUG_OPT_TF)$
                $WARNING$// size_list update#1 : $MO_LIST_SIZE[size]$$NL$$END$
            $END$
$           // ��Ƭ���Ϥ򹹿�
            $base = base + size$
$           // reg�ν�λ���Ϥ򹹿�
            $IF REG.LIMIT[reg] < base$
                $REG.LIMIT[reg] = base$
            $END$

$       // size > align�ʤ�Ф������1�ʳ���������������MO_BLOCK��
$       // �������Ϥ����֤���
        $ELIF (idx > 0)$
            $size = AT(SIZE_LIST, idx - 1)$
            $FOREACH moid MO_LIST_SIZE[size]$
                $IF idx0_flg$
                    $IF LENGTH(DEBUG_OPT_TF)$
                        $WARNING$// push {moid=$moid$,size=$size$}$NL$$END$
                    $END$
                    $MO.REALBASE[moid] = base$
                    $MO_SIZEORDER_LIST_REG[reg] = APPEND(MO_SIZEORDER_LIST_REG[reg], moid)$
                    $idx0_flg = 0$
                $ELSE$
                    $TMP_LIST = APPEND(TMP_LIST, moid)$
                $END$
            $END$
$           // MO_LIST_SIZE������Ƭ��MO_BLOCK����
            $MO_LIST_SIZE[size] = TMP_LIST$
$           // MO_LIST_SIZE�����ˤʤä���
            $IF (LENGTH(MO_LIST_SIZE[size]) == 0)$
                $FOREACH sz SIZE_LIST$
                    $IF (sz != size)$
                        $TMP_LIST = APPEND(TMP_LIST, sz)$
                    $END$
                $END$
$               // SIZE_LIST���餽�Υ���������
                $SIZE_LIST = TMP_LIST$
            $END$
            $IF LENGTH(DEBUG_OPT_TF)$
                $WARNING$// size_list update#2 : $MO_LIST_SIZE[size]$$NL$$END$
            $END$
$           // ��Ƭ���Ϥ򹹿�
            $base = base + size$
$           // reg�ν�λ���Ϥ򹹿�
            $IF REG.LIMIT[reg] < base$
                $REG.LIMIT[reg] = base$
            $END$

$       // size�ʺ����͡� < align�ʤ�Ф��Υ�������MO_BLOCK�򤳤����Ϥ����֤���
        $ELIF (size < align)$
            $FOREACH moid MO_LIST_SIZE[size]$
                $IF idx0_flg$
                    $IF LENGTH(DEBUG_OPT_TF)$
                        $WARNING$// push {moid=$moid$,size=$size$}$NL$$END$
                    $END$
                    $MO.REALBASE[moid] = base$
                    $MO_SIZEORDER_LIST_REG[reg] = APPEND(MO_SIZEORDER_LIST_REG[reg], moid)$
                    $idx0_flg = 0$
                $ELSE$
                    $TMP_LIST = APPEND(TMP_LIST, moid)$
                $END$
            $END$
$           // MO_LIST_SIZE������Ƭ��MO_BLOCK����
            $MO_LIST_SIZE[size] = TMP_LIST$
$           // MO_LIST_SIZE�����ˤʤä���
            $IF (LENGTH(MO_LIST_SIZE[size]) == 0)$
                $FOREACH sz SIZE_LIST$
                    $IF (sz != size)$
                        $TMP_LIST = APPEND(TMP_LIST, sz)$
                    $END$
                $END$
$               // SIZE_LIST���餽�Υ���������
                $SIZE_LIST = TMP_LIST$
            $END$
            $IF LENGTH(DEBUG_OPT_TF)$
                $WARNING$// size_list update#3 : $MO_LIST_SIZE[size]$$NL$$END$
            $END$
$           // ��Ƭ���Ϥ򹹿�
            $base = base + size$
$           // reg�ν�λ���Ϥ򹹿�
            $IF REG.LIMIT[reg] < base$
                $REG.LIMIT[reg] = base$
            $END$

$       // size�ʺǾ��͡� > align�ʤ�����Ϥ�Ʒ׻�
        $ELSE$
            $IF LENGTH(DEBUG_OPT_TF)$
                $WARNING$$FORMAT("size = %d, pre base = %x", size, base)$$NL$$END$
            $END$
            $pre_base = base$
            $IF ((base % size) != 0)$
$               // size�ΥӥåȤ�겼�̥ӥåȤ򤹤٤�0�ˤ���                
                $base = ((base / size) * size) + size$
            $ELSE$
$               // size�ΥӥåȤ�겼�̥ӥåȤ򤹤٤�0�ˤ���                
                $base = ((base / size) * size)$
            $END$
            $IF LENGTH(DEBUG_OPT_TF)$
                $WARNING$$FORMAT("post base = %x", base)$$NL$$END$
            $END$
            $IF pre_base == base$
                $ERROR$$FORMAT("Error: base is not updated")$$NL$$END$
                $DIE()$
            $END$
        $END$
    $END$
$END$

$  MO_BLOCK�κ����ֽ�Υꥹ�Ȥ�����
$  MO_MEMTOP_REAL_LIST�������֤���MEMTOP_LIST
$  NO_LINKER��MO_BLOCK����Ƭ�����֤������θ�ˡ�LINKER��MO_BLOCK��
$  Ŭ�ڤʽ�����֤���
$FOREACH ctx CONTEXT_LIST$
    $IF EQ(ctx, "REG")$
        $IF LENGTH(DEBUG_OPT_TF)$
            $WARNING$$FORMAT("ctx is %s: %d", ctx, +ctx)$$END$
        $END$
        $TMP_LIST = MO_SIZEORDER_LIST_REG[ctx]$
        $MO_MEMTOP_REAL_LIST = APPEND(MO_MEMTOP_REAL_LIST, TMP_LIST)$
    $ELIF EQ(ctx, "NONREG")$
        $IF LENGTH(DEBUG_OPT_TF)$
            $WARNING$$FORMAT("ctx is %s: %d", ctx, +ctx)$$END$
        $END$
        $TMP_LIST = MO_NONREG_LIST[ctx]$
        $MO_MEMTOP_REAL_LIST = APPEND(TMP_LIST, MO_MEMTOP_REAL_LIST)$
    $ELSE$
        $ERROR$error: context$END$
        $DIE()$
    $END$
    $IF LENGTH(DEBUG_OPT_TF)$
        $WARNING$ list : $TMP_LIST$$END$
        $WARNING$ real_list : $MO_MEMTOP_REAL_LIST$$END$
    $END$
$END$

/*$NL$
$FOREACH moid MO_MEMTOP_REAL_LIST$
    $IF MO.LINKER[moid]$
        $IF LENGTH(DEBUG_OPT_TF)$
            $WARNING$$FORMAT("label is %s: base=%x, size=%x(%d): linker", MO.MLABEL[moid], MO.REALBASE[moid], MO_BLOCK.SIZE[moid], MO_BLOCK.SIZE[moid])$$NL$$END$
        $END$
        $FORMAT("label is %s: base=%x, size=%x(%d)", MO.MLABEL[moid], MO.REALBASE[moid], MO_BLOCK.SIZE[moid], MO_BLOCK.SIZE[moid])$$NL$
    $ELSE$
        $IF LENGTH(DEBUG_OPT_TF)$
            $WARNING$$FORMAT("label is %s: base=%x, size=%x(%d): no linker", MO.BASE[moid], MO.BASE[moid], MO_BLOCK.SIZE[moid], MO_BLOCK.SIZE[moid])$$NL$$END$
        $END$
        $FORMAT("label is %s: base=%x, size=%x(%d)", MO.BASE[moid], MO.BASE[moid], MO_BLOCK.SIZE[moid], MO_BLOCK.SIZE[moid])$$NL$
    $END$
$END$
*/$NL$

$ 
$  ���ꥪ�֥������Ƚ�����֥�å��˽��Ϥ��ʤ�����ȥ�η���
$ 
$  suppresszero�����ɥ쥹0���б����륨��ȥ����Ϥ��ʤ�
$  MO.SUPPRESSLIMIT[moid]����¥��ɥ쥹�Υ���ȥ����Ϥ��ʤ�
$tsize_meminib = LENGTH(MO_START_LIST) * 2 + 1$
$tnum_suppresslimit = 0$

$IF LENGTH(DEBUG_OPT_TF)$
    $WARNING$Difinition of SUPPRESSLIMIT$END$
$END$
$prev = 0$
$FOREACH moid MO_MEMTOP_REAL_LIST$
    $IF MO.LINKER[moid]$
        $base = MO.REALBASE[moid]$
        $IF !LENGTH(MO_BLOCK.MO_LIST[moid])$
            $ERROR$MO_LIST[$moid$] is empty$END$
        $END$
        $FOREACH mo MO_BLOCK.MO_LIST[moid]$
            $IF mo != AT(MO_BLOCK.MO_LIST[moid], LENGTH(MO_BLOCK.MO_LIST[moid]) - 1)$
                $MO.SUPPRESSLIMIT_REAL[mo] = 1$
            $END$
            $IF MO.BASEADDR[mo] != MO.LIMITADDR[mo]$
                $MO_MEMTOP_REAL_ORDER = APPEND(MO_MEMTOP_REAL_ORDER, mo)$
                $IF LENGTH(MO.SUPPRESSLIMIT_REAL[mo]) && MO.SUPPRESSLIMIT_REAL[mo]$
                    $tnum_suppresslimit = tnum_suppresslimit - 1$
                $END$
            $END$
        $END$
    $ELSE$
        $base = MO.BASEADDR[moid]$
        $MO_MEMTOP_REAL_ORDER = APPEND(MO_MEMTOP_REAL_ORDER, moid)$
    $END$

    $IF !prev$
        $suppresszero_real = 1$
        $tnum_suppresslimit = tnum_suppresslimit - 1$
        $prev_limit = 0$
    $ELSE$
        $IF MO.LINKER[prev]$
            $prev_limit = MO.REALBASE[prev] + MO_BLOCK.SIZE[prev]$
            $IF LENGTH(MO_BLOCK.MO_LIST[prev])$
                $prev_listend = AT(MO_BLOCK.MO_LIST[prev],LENGTH(MO_BLOCK.MO_LIST[prev]) - 1)$
            $END$
            $IF base == prev_limit$
                $MO.SUPPRESSLIMIT_REAL[prev_listend] = 1$
                $tnum_suppresslimit = tnum_suppresslimit - 1$
            $END$
        $ELSE$
$           // NO_LINKER��MO��LIMIT��ɬ����ά����
$           // kernel_mem.tf�Υ����ɤ�ή�Ѥ��뤿��            
            $prev_limit = MO_BLOCK.LIMITADDR[prev]$
            $MO.SUPPRESSLIMIT_REAL[prev] = 1$
            $tnum_suppresslimit = tnum_suppresslimit - 1$
        $END$
        $IF LENGTH(DEBUG_OPT_TF)$
            $WARNING$$FORMAT("prev = %d", prev)$$END$
            $WARNING$$FORMAT("prev_limit = 0x%x", prev_limit)$$END$
            $WARNING$$FORMAT("base = 0x%x", base)$$END$
        $END$
    $END$

    $prev = moid$
    $IF LENGTH(DEBUG_OPT_TF)$
        $WARNING$$FORMAT("prev = %d", prev)$$END$
    $END$
$END$
$IF prev_limit == 0$
    $IF MO.LINKER[prev]$
        $IF LENGTH(MO_BLOCK.MO_LIST[prev])$
            $prev = AT(MO_BLOCK.MO_LIST[prev],LENGTH(MO_BLOCK.MO_LIST[prev]) - 1)$
        $END$
        $MO.SUPPRESSLIMIT_REAL[prev] = 1$
        $tnum_suppresslimit = tnum_suppresslimit - 1$
    $ELSE$
        $MO.SUPPRESSLIMIT_REAL[prev] = 1$
        $tnum_suppresslimit = tnum_suppresslimit - 1$
    $END$
$END$

$tnum_meminib = LENGTH(MO_MEMTOP_REAL_ORDER) * 2 + 1$
$tnum_meminib = tnum_meminib + tnum_suppresslimit$

$  memtop_table�ǻ��Ȥ����٥�����������
$FOREACH moid MO_MEMTOP_REAL_ORDER$
    $IF MO.LINKER[moid]$
        extern char __start_$MO.MLABEL[moid]$;$NL$
        $IF !LENGTH(MO.SUPPRESSLIMIT_REAL[moid])$
            extern char __limit_$MO.MLABEL[moid]$;$NL$
        $END$
    $END$
$END$$NL$


$  tnum_meminib������
const uint_t _kernel_tnum_meminib = $tnum_meminib$U;$NL$
$NL$

$  memtop_table������
#if 0$NL$
void *const _kernel_memtop_table[$tsize_meminib$] = {$NL$
$IF !LENGTH(suppresszero_real)$
    $TAB$0,$NL$
$END$
$JOINEACH moid MO_MEMTOP_ORDER ",\n"$
    $IF MO.LINKER[moid]$
        $TAB$&__start_$MO.MLABEL[moid]$
        $SPC$/* $FORMAT("base=%x, size=%x(%d)", MO.BASEADDR[moid], (MO.LIMITADDR[moid] - MO.BASEADDR[moid]), (MO.LIMITADDR[moid] - MO.BASEADDR[moid]))$ */
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
#endif$NL$
$NL$

$  memtop_table������
void *const _kernel_memtop_table[$tsize_meminib$] = {$NL$
$IF !LENGTH(suppresszero_real)$
    $TAB$0,$NL$
$END$
$JOINEACH moid MO_MEMTOP_REAL_ORDER ",\n"$
    $IF MO.LINKER[moid]$
        $TAB$&__start_$MO.MLABEL[moid]$
        $IF LENGTH(MO.REALBASE[moid])$
            $SPC$/* $FORMAT("base=%x, size=%x(%d)", MO.REALBASE[moid], MO_BLOCK.SIZE[moid], MO_BLOCK.SIZE[moid])$ */
        $END$
        $IF !LENGTH(MO.SUPPRESSLIMIT_REAL[moid])$
            ,$NL$$TAB$&__limit_$MO.MLABEL[moid]$
        $END$
    $ELSE$
        $TAB$(void *)($MO.BASE[moid]$)
        $SPC$/* $FORMAT("%x", MO.BASE[moid])$ */
        $IF !LENGTH(MO.SUPPRESSLIMIT_REAL[moid])$
            ,$NL$$TAB$(void *)(((char *)($MO.BASE[moid]$)) + ($MO.SIZE[moid]$))
            $SPC$/* $FORMAT("%x", MO.LIMITADDR[moid])$ */
        $END$
    $END$
$END$$NL$
};$NL$
$NL$

$  meminib_table������
const MEMINIB _kernel_meminib_table[$tsize_meminib$] = {$NL$
$IF !LENGTH(suppresszero_real)$
    $TAB${ TA_NULL, 0, 0, 0 },$NL$
$END$
$JOINEACH moid MO_MEMTOP_REAL_ORDER ",\n"$
    $TAB${
    $IF MO.TYPE[moid] == TOPPERS_USTACK$
        $SPC$TOPPERS_USTACK|($MO.MEMATR[moid]$),
        $SPC$$MO.ACPTN4[moid]$,
        $IF MO.TSKID[moid] != 0$
            $SPC$(ACPTN)(&_kernel_tcb_table[$MO.TSKID[moid]$ - 1]),
        $ELSE$
            $SPC$(ACPTN)(NULL),
        $END$
        $SPC$0
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
    $IF !LENGTH(MO.SUPPRESSLIMIT_REAL[moid])$
        ,$NL$$TAB${ TA_NULL, 0, 0, 0 }
    $END$
$END$$NL$
};$NL$

$ MO_REAL_ORDER�������֤�����֤�MO���¤٤��ꥹ��
$FOREACH memtop MO_MEMTOP_REAL_ORDER$
    // $memtop$ : $MO_CLASS_LIST[memtop]$,$NL$
    $MO_REAL_ORDER = APPEND(MO_REAL_ORDER, MO_CLASS_LIST[memtop])$
$END$

$ 
$  ʣ���Υ��������ˤޤ���������ݸ�ñ�̤ξ�硤
$  �����ݸ�ñ�̤���Ƭ��MEMTOP_ORDER����Ͽ�����Ȥϸ¤�ʤ��Τǡ�
$  �����ݸ�ñ�̤���ˤ���realbase��size�򡤥����ݸ�ñ�̤�
$  ��Ƭ�Υ��ꥪ�֥������Ȥ�°������Ϳ����
$ 
$plabel_moid = 0$
$FOREACH moid MO_ORDER$
    $IF (MO.SEFLAG[moid] & 0x10) != 0$
        $plabel_moid = moid$
        $IF LENGTH(DEBUG_OPT_TF)$
            $WARNING$$FORMAT("plabel is %d", moid)$$END$
        $END$
    $END$
    $IF LENGTH(MO_BLOCK.SIZE[moid])$
        $IF !plabel_moid$
            $ERROR$$FORMAT("error: not exist within plabel: mo = %d", moid)$$END$
        $END$
        $MO.REALBASE[plabel_moid] = MO.REALBASE[moid]$
        $MO.SIZE[plabel_moid] = MO_BLOCK.SIZE[moid]$
    $END$
    $IF (MO.SEFLAG[moid] & 0x20) != 0$
        $plabel_moid = 0$
    $END$
$END$
$END$
$  =end GENERATE_MEMINIB_TABLE

$INCLUDE "kernel/kernel_opt.tf"$

$ 
$  arch/arm_m_gcc/common/ldscript.tf�Υ������åȰ�¸��
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
$  ��ͭ�ΰ�
            PROVIDE(__start_text_$DOM.LABEL[TDOM_NONE]$ = 0xffffffff);$NL$
            PROVIDE(__limit_text_$DOM.LABEL[TDOM_NONE]$ = 0xffffffff);$NL$
            PROVIDE(__start_rodata_$DOM.LABEL[TDOM_NONE]$ = 0xffffffff);$NL$
            PROVIDE(__limit_rodata_$DOM.LABEL[TDOM_NONE]$ = 0xffffffff);$NL$
            PROVIDE(__start_ram_$DOM.LABEL[TDOM_NONE]$ = 0xffffffff);$NL$
            PROVIDE(__limit_ram_$DOM.LABEL[TDOM_NONE]$ = 0xffffffff);$NL$
        $END$
        $NL$
    $END$$NL$
$   ��ͭ�꡼�����ѥ饤���ΰ�����
    PROVIDE(__start_srpw_all = 0xffffffff);$NL$
    PROVIDE(__limit_srpw_all = 0xffffffff);$NL$
    $NL$
$END$

$TOPPERS_ATTMOD = TOPPERS_ATTSEC + 1$
$TOPPERS_MPFAREA = TOPPERS_ATTSEC + 2$

$INCLUDE "arm_m_gcc/common/ldscript.tf"$

$NL$


$ 
$  ��ͭ�ΰ�ν�����֥�å����ݸ�ɥᥤ�������֥�å���mem��¸��������
$ 

$FILE "kernel_mem3.c"$

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

$region_size = 32$
$region_size_mask = 0x04$
$WHILE (region_size <= (4*1024*1024*1024))$
    $hash_region_size_mask[region_size] = (region_size_mask << 1)$
    $region_size = region_size * 2$
    $region_size_mask = region_size_mask + 1$
$END$

$IF LENGTH(DOM.ID_LIST) > 0$
    const DOMINIB_INFO _kernel_dominib_info_tbl[TNUM_DOMID] ={$NL$
    $dominib_info = SYMBOL("_kernel_dominib_info_tbl")$
    $JOINEACH domid DOM.ID_LIST ",\n"$
        $TAB${$NL$
$   RX�ΰ�����ѡ�
        $start_label = PEEK(dominib_info, 4)$
        $limit_label = PEEK(dominib_info + 4, 4)$
        $size = limit_label - start_label$
        $IF size != 0$
            $size = SEARCH_ARM_MPU_SIZE(size)$
            $TAB$$TAB$( (char *)&__start_text_$DOM.LABEL[domid]$ + 0x10 + 0x04 ), /* region 4 : $FORMAT("0x%x", start_label)$ */$NL$
            $TAB$$TAB$( TO_MPU_AP( MPU_AP_PRWUR ) | MPU_REGATR_C | MPU_REGATR_B | $hash_region_size_mask[size]$ | MPU_REGATR_ENABLE ), /* size=$size$ */$NL$
        $ELSE$
            $TAB$$TAB$(char *)( 0x14 ), /* region 4 */$NL$
            $TAB$$TAB$( 0 ), /* size=0 */$NL$
        $END$
$   RWX�ΰ�����ѡ�
        $start_label = PEEK(dominib_info + 8, 4)$
        $limit_label = PEEK(dominib_info + 12, 4)$
        $size = limit_label - start_label$
        $IF size != 0$
            $size = SEARCH_ARM_MPU_SIZE(size)$
            $TAB$$TAB$( (char *)&__start_ram_$DOM.LABEL[domid]$ + 0x10 + 0x05 ),/* region 5 : $FORMAT("0x%x", start_label)$ */$NL$
            $TAB$$TAB$( TO_MPU_AP( MPU_AP_PURW ) | MPU_REGATR_C | MPU_REGATR_B | $hash_region_size_mask[size]$ | MPU_REGATR_ENABLE ), /* size=$size$ */$NL$
        $ELSE$
            $TAB$$TAB$(char *)( 0x15 ), /* region 5 */$NL$
            $TAB$$TAB$( 0 ), /* size=0 */$NL$
        $END$
$   ��ͭ�꡼�����ѥ饤��
        $start_label = PEEK(dominib_info + 16, 4)$
        $limit_label = PEEK(dominib_info + 20, 4)$
        $size = limit_label - start_label$
        $IF size != 0$
            $size = SEARCH_ARM_MPU_SIZE(size)$
            $TAB$$TAB$$FORMAT("( (char *)&__start_ram_%s_%x_%x + 0x10 + 0x06 )", DOM.LABEL[domid], +DEFAULT_ACPTN[domid], +TACP_SHARED)$,/* region 6 : $FORMAT("0x%x", start_label)$ */$NL$
            $TAB$$TAB$( TO_MPU_AP( MPU_AP_PURW ) | MPU_REGATR_C | MPU_REGATR_B | $hash_region_size_mask[size]$ | MPU_REGATR_ENABLE ), /* size=$size$ */$NL$
        $ELSE$
            $TAB$$TAB$(char *)( 0x16 ), /* region 6 */$NL$
            $TAB$$TAB$( 0 ), /* size=0 */$NL$
        $END$
$   ATT_MEM
        $start_label = PEEK(dominib_info + 24, 4)$
        $limit_label = PEEK(dominib_info + 28, 4)$
        $size = limit_label - start_label$
        $IF size != 0$
$           // MEM�Υ����������å��ϥѥ�2�Ǽ»ܺѤ�
            $TAB$$TAB$$FORMAT("( (char *)%s + 0x10 + 0x07 )", DOM.MEM_BASE[domid])$,/* region 7 : ATT_MEM */$NL$
            $TAB$$TAB$( TO_MPU_AP( MPU_AP_PURW ) | MPU_REGATR_C | MPU_REGATR_B | $hash_region_size_mask[size]$ | MPU_REGATR_ENABLE ), /* size=$size$ */$NL$
        $ELSE$
            $TAB$$TAB$(char *)( 0x17 ), /* region 7 */$NL$
            $TAB$$TAB$( 0 ), /* size=0 */$NL$
        $END$
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
    $start_label = PEEK(shared_info, 4)$
    $limit_label = PEEK(shared_info + 4, 4)$
    $size = limit_label - start_label$
    $IF size != 0$
        $size = SEARCH_ARM_MPU_SIZE(size)$
        $TAB$$TAB$((char *)&__start_text_$DOM.LABEL[TDOM_NONE]$ + 0x10 + 0x00),$TAB$/* region 0 : $FORMAT("0x%x", start_label)$ */$NL$
        $TAB$$TAB$(char *)( TO_MPU_AP( MPU_AP_PRWUR ) | MPU_REGATR_S | MPU_REGATR_C | MPU_REGATR_B | $hash_region_size_mask[size]$ | MPU_REGATR_ENABLE ), /* size=$size$ */$NL$
    $ELSE$
        $TAB$$TAB$(char *)( 0x10 ), /* region 0 */$NL$
        $TAB$$TAB$(char *)( 0 ), /* size=0 */$NL$
    $END$
    $start_label = PEEK(shared_info + 8, 4)$
    $limit_label = PEEK(shared_info + 12, 4)$
    $size = limit_label - start_label$
    $IF size != 0$
        $size = SEARCH_ARM_MPU_SIZE(size)$
        $TAB$$TAB$((char *)&__start_ram_$DOM.LABEL[TDOM_NONE]$ + 0x10 + 0x01),$TAB$/* region 1 : $FORMAT("0x%x", start_label)$ */$NL$
        $TAB$$TAB$(char *)( TO_MPU_AP( MPU_AP_PURW ) | MPU_REGATR_S | MPU_REGATR_C | MPU_REGATR_B | $hash_region_size_mask[size]$ | MPU_REGATR_ENABLE ), /* size=$size$ */$NL$
    $ELSE$
        $TAB$$TAB$(char *)( 0x11 ), /* region 1 */$NL$
        $TAB$$TAB$(char *)( 0 ), /* size=0 */$NL$
    $END$
    $start_label = PEEK(shared_info + 16, 4)$
    $limit_label = PEEK(shared_info + 20, 4)$
    $size = limit_label - start_label$
    $IF size != 0$
        $size = SEARCH_ARM_MPU_SIZE(size)$
        $TAB$$TAB$((char *)&__start_srpw_all + 0x10 + 0x02),$TAB$/* region 2 : $FORMAT("0x%x", start_label)$ */$NL$
        $TAB$$TAB$(char *)( TO_MPU_AP( MPU_AP_PRWUR ) | MPU_REGATR_S | MPU_REGATR_C | MPU_REGATR_B | $hash_region_size_mask[size]$ | MPU_REGATR_ENABLE ), /* size=$size$ */$NL$
    $ELSE$
        $TAB$$TAB$(char *)( 0x12 ), /* region 2 */$NL$
        $TAB$$TAB$(char *)( 0 ), /* size=0 */$NL$
    $END$
};$NL$
$NL$

$ 
$  cfg3_out.tf������
$  pass 4 �˻����ۤ���������
$ 
$FILE "cfg3_out.tf"$

$$MO_MEMTOP_REAL_LIST = { $MO_MEMTOP_REAL_LIST$ }$$$NL$
$$MO_MEMTOP_REAL_ORDER = { $MO_MEMTOP_REAL_ORDER$ }$$$NL$
$NL$

$JOINEACH moid MO_MEMTOP_REAL_LIST "\n"$
    $IF MO.LINKER[moid]$
        $$MO.REALBASE[$moid$] = $MO.REALBASE[moid]$$$
    $END$
$END$
$NL$

$$MO_BLOCK_LIST = { $MO_BLOCK_LIST$ }$$$NL$
$NL$
$JOINEACH mbid MO_BLOCK_LIST "\n"$
    $$MO_BLOCK.SIZE[$mbid$] = $MO_BLOCK.SIZE[mbid]$$$$NL$
    $$MO_BLOCK.MO_LIST[$mbid$] = { $MO_BLOCK.MO_LIST[mbid]$ }$$$NL$
$END$

$$MO_MEMTOP_REAL_LIST = { $MO_MEMTOP_REAL_LIST$ }$$$NL$

