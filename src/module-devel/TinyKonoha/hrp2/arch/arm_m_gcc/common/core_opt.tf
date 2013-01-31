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

$ $DEBUG_OPT_TF = 1$

$
$  保護ドメインのラベルの作成
$	DOM.LABEL[domid]：保護ドメインのラベル
$
$DOM.LABEL[TDOM_KERNEL] = "kernel"$
$FOREACH domid DOM.ID_LIST$
	$DOM.LABEL[domid] = domid$
$END$
$DOM.LABEL[TDOM_NONE] = "shared"$

$ 
$  保護ドメイン毎のデフォルトのアクセス許可パターンの作成
$ 
$DEFAULT_ACPTN[TDOM_KERNEL] = VALUE("TACP_KERNEL", TACP_KERNEL)$
$FOREACH domid DOM.ID_LIST$
	$DEFAULT_ACPTN[domid] = VALUE(FORMAT("TACP(%1%)", domid), 1 << (domid - 1))$
$END$
$DEFAULT_ACPTN[TDOM_NONE] = VALUE("TACP_SHARED", TACP_SHARED)$

$ MO_CLASS_LISTの生成
$ メモリ保護属性が同じメモリオブジェクトをまとめたリスト
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
$  メモリ保護単位の実際のサイズを受け取り，受け取ったサイズ以上で，
$  ARM MPUのサイズ制約を満たす最小値を返す
$  ARM MPUのサイズ制約は，32B~4GBの範囲の2のべき乗
$  ARGV[1]：実際のサイズ
$  RESULT：ARM MPUのサイズ制約を満たす最小値
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
$  受け取った番地以上で，
$  ARM MPUのアライン制約を満たす最小値を返す
$  ARM MPUのアライン制約は，32B~4GBの範囲の2のべき乗
$  ARGV[1]：番地
$  RESULT：ARM MPUのアライン制約を満たす最小値
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
$  受け取った番地が満たす，ARM MPUのアライン制約の最大値を返す
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
$  MO_BLOCK[moid]：メモリオブジェクトの配置を並べ替える単位
$  MO_BLOCK.SIZE[moid]：MPUのサイズ制約を満たすようにアラインしたサイズ
$  MO_BLOCK_LIST：サイズが0でないMO_BLOCKのリスト
$  MO_BLOCK.MO_LIST[moid]：MO_BLOCKに含まれるMOのリスト

$  MO_BLOCKの決定
$prev = -1$
$mo_block_top = -1$
$MO_LIST_CACHE = {}$
$FOREACH moid MO_START_LIST$
    $IF LENGTH(FIND(MO_MPROTECT_LIST, moid))$
        $IF (mo_block_top != -1) && (!LENGTH(MO.SRPW[prev]) || !LENGTH(MO.SRPW[moid]) || !MO.SRPW[prev] || !MO.SRPW[moid])$
$           // MO_BLOCKの終わり
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
$           // MO_BLOCKの先頭
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
$  suppresszero：アドレス0に対応するエントリを出力しない
$  MO.SUPPRESSLIMIT[moid]：上限アドレスのエントリを出力しない
$  MO_REG_LIST[reg]：regに属するMO_BLOCKのリスト
$  MO_NONREG_LIST：regに属さないMO_BLOCKのリスト
$  CONTEXT_LIST：regとmem（regに属さないMO_BLOCK）をpass3でのリンク順に並べたリスト
$  REG.REALBASE[reg]：MPUのアライン制約を満たすようにアラインしたregの先頭番地

$  メモリリージョンに関する情報の整理
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

$  MO_SIZE_REG_LIST[reg]：regに属するMO_BLOCKをサイズ順に並べたリスト
$  MO.REALBASE[moid]：MO_BLOCKを再配置する先の番地
$FOREACH reg REG_ORDER$
    $MO_SIZE_REG_LIST[reg] = LSORT(MO_REG_LIST[reg], "COMPARE_MO_SIZE")$
    $IF LENGTH(MO_SIZE_REG_LIST)$
        $IF LENGTH(DEBUG_OPT_TF)$
            $WARNING$// $FORMAT("{ %x:%x } ", REG.REALBASE[reg], SEARCH_ARM_MPU_ALIGN(REG.REALBASE[reg]))$ $END$
        $END$
    $END$

$   // 初期化
$   // MO_SIZEORDER_LIST_REG[reg]: リージョンごとに再配置した結果のMO_BLOCKの
$   //                             配置順を格納したリスト
    $SIZE_LIST = {}$
    $MO_SIZEORDER_LIST_REG[reg] = {}$
    $REG.LIMIT[reg] = 0$

$   // サイズごとの配列MO_LIST_SIZE[size]にMO_BLOCKを分類
$   // SIZE_LIST：分類されたsizeをサイズ順に並べたリスト
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

$   // MO_BLOCKの配置番地を決定
    $base = REG.REALBASE[reg]$
    $IF LENGTH(DEBUG_OPT_TF)$
        $WARNING$// !base=$base$: size_list=$SIZE_LIST$$END$
    $END$
    $WHILE (LENGTH(SIZE_LIST) > 0)$
$       // オーバフローチェック
        $IF (base >= (REG.BASE[reg] + REG.SIZE[reg]))$
            $ERROR$
                $FORMAT("error: overflow reg[%s], %x", reg, base)$
            $END$
            $DIE()$
        $END$
$       // align：再配置先の先頭番地をアラインした番地が，ARM MPUのどのサイズ制約
$       //        の倍数かを示す
        $align = SEARCH_ARM_MPU_ALIGN(base)$
        $IF LENGTH(DEBUG_OPT_TF)$
            $WARNING$$FORMAT("!base=%x,align=%x: ", base, align)$ $SIZE_LIST$$NL$$END$
        $END$
$       // アラインした番地に配置可能なサイズをサーチ
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

$       // MO_BLOCKの再配置を決定
        $TMP_LIST = {}$
        $idx0_flg = 1$
$       // size == alignならばそのサイズのMO_BLOCKをこの番地に配置する
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
$           // MO_LIST_SIZEから先頭のMO_BLOCKを削除
            $MO_LIST_SIZE[size] = TMP_LIST$
$           // MO_LIST_SIZEが空になったら
            $IF (LENGTH(MO_LIST_SIZE[size]) == 0)$
                $FOREACH sz SIZE_LIST$
                    $IF (sz != size)$
                        $TMP_LIST = APPEND(TMP_LIST, sz)$
                    $END$
                $END$
$               // SIZE_LISTからそのサイズを削除
                $SIZE_LIST = TMP_LIST$
            $END$
            $IF LENGTH(DEBUG_OPT_TF)$
                $WARNING$// size_list update#1 : $MO_LIST_SIZE[size]$$NL$$END$
            $END$
$           // 先頭番地を更新
            $base = base + size$
$           // regの終了番地を更新
            $IF REG.LIMIT[reg] < base$
                $REG.LIMIT[reg] = base$
            $END$

$       // size > alignならばそれよりも1段階小さいサイズのMO_BLOCKを
$       // この番地に配置する
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
$           // MO_LIST_SIZEから先頭のMO_BLOCKを削除
            $MO_LIST_SIZE[size] = TMP_LIST$
$           // MO_LIST_SIZEが空になったら
            $IF (LENGTH(MO_LIST_SIZE[size]) == 0)$
                $FOREACH sz SIZE_LIST$
                    $IF (sz != size)$
                        $TMP_LIST = APPEND(TMP_LIST, sz)$
                    $END$
                $END$
$               // SIZE_LISTからそのサイズを削除
                $SIZE_LIST = TMP_LIST$
            $END$
            $IF LENGTH(DEBUG_OPT_TF)$
                $WARNING$// size_list update#2 : $MO_LIST_SIZE[size]$$NL$$END$
            $END$
$           // 先頭番地を更新
            $base = base + size$
$           // regの終了番地を更新
            $IF REG.LIMIT[reg] < base$
                $REG.LIMIT[reg] = base$
            $END$

$       // size（最大値） < alignならばそのサイズのMO_BLOCKをこの番地に配置する
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
$           // MO_LIST_SIZEから先頭のMO_BLOCKを削除
            $MO_LIST_SIZE[size] = TMP_LIST$
$           // MO_LIST_SIZEが空になったら
            $IF (LENGTH(MO_LIST_SIZE[size]) == 0)$
                $FOREACH sz SIZE_LIST$
                    $IF (sz != size)$
                        $TMP_LIST = APPEND(TMP_LIST, sz)$
                    $END$
                $END$
$               // SIZE_LISTからそのサイズを削除
                $SIZE_LIST = TMP_LIST$
            $END$
            $IF LENGTH(DEBUG_OPT_TF)$
                $WARNING$// size_list update#3 : $MO_LIST_SIZE[size]$$NL$$END$
            $END$
$           // 先頭番地を更新
            $base = base + size$
$           // regの終了番地を更新
            $IF REG.LIMIT[reg] < base$
                $REG.LIMIT[reg] = base$
            $END$

$       // size（最小値） > alignならば番地を再計算
        $ELSE$
            $IF LENGTH(DEBUG_OPT_TF)$
                $WARNING$$FORMAT("size = %d, pre base = %x", size, base)$$NL$$END$
            $END$
            $pre_base = base$
            $IF ((base % size) != 0)$
$               // sizeのビットより下位ビットをすべて0にする                
                $base = ((base / size) * size) + size$
            $ELSE$
$               // sizeのビットより下位ビットをすべて0にする                
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

$  MO_BLOCKの再配置順のリストを統合
$  MO_MEMTOP_REAL_LIST：再配置したMEMTOP_LIST
$  NO_LINKERなMO_BLOCKを先頭に配置し，その後に，LINKERなMO_BLOCKを
$  適切な順で配置する
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
$  メモリオブジェクト初期化ブロックに出力しないエントリの決定
$ 
$  suppresszero：アドレス0に対応するエントリを出力しない
$  MO.SUPPRESSLIMIT[moid]：上限アドレスのエントリを出力しない
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
$           // NO_LINKERなMOはLIMITを必ず省略する
$           // kernel_mem.tfのコードを流用するため            
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

$  memtop_tableで参照するラベルの宣言の生成
$FOREACH moid MO_MEMTOP_REAL_ORDER$
    $IF MO.LINKER[moid]$
        extern char __start_$MO.MLABEL[moid]$;$NL$
        $IF !LENGTH(MO.SUPPRESSLIMIT_REAL[moid])$
            extern char __limit_$MO.MLABEL[moid]$;$NL$
        $END$
    $END$
$END$$NL$


$  tnum_meminibの生成
const uint_t _kernel_tnum_meminib = $tnum_meminib$U;$NL$
$NL$

$  memtop_tableの生成
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

$  memtop_tableの生成
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

$  meminib_tableの生成
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

$ MO_REAL_ORDER：再配置する順番にMOを並べたリスト
$FOREACH memtop MO_MEMTOP_REAL_ORDER$
    // $memtop$ : $MO_CLASS_LIST[memtop]$,$NL$
    $MO_REAL_ORDER = APPEND(MO_REAL_ORDER, MO_CLASS_LIST[memtop])$
$END$

$ 
$  複数のセクションにまたがるメモリ保護単位の場合，
$  メモリ保護単位の先頭がMEMTOP_ORDERに登録されるとは限らないので，
$  メモリ保護単位の中にあるrealbaseとsizeを，メモリ保護単位の
$  先頭のメモリオブジェクトの属性に付与する
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
$  arch/arm_m_gcc/common/ldscript.tfのターゲット依存部
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
$   RX領域（専用）
            PROVIDE(__start_text_$DOM.LABEL[domid]$ = 0xffffffff);$NL$
            PROVIDE(__limit_text_$DOM.LABEL[domid]$ = 0xffffffff);$NL$
$   R領域（専用）
            PROVIDE(__start_rodata_$DOM.LABEL[domid]$ = 0xffffffff);$NL$
            PROVIDE(__limit_rodata_$DOM.LABEL[domid]$ = 0xffffffff);$NL$
$   RWX領域（専用）
            PROVIDE(__start_ram_$DOM.LABEL[domid]$ = 0xffffffff);$NL$
            PROVIDE(__limit_ram_$DOM.LABEL[domid]$ = 0xffffffff);$NL$
$   共有リード専用ライト
            PROVIDE($FORMAT("__start_ram_%s_%x_%x", DOM.LABEL[domid], +DEFAULT_ACPTN[domid], +TACP_SHARED)$ = 0xffffffff);$NL$
            PROVIDE($FORMAT("__limit_ram_%s_%x_%x", DOM.LABEL[domid], +DEFAULT_ACPTN[domid], +TACP_SHARED)$ = 0xffffffff);$NL$
$  共有領域
            PROVIDE(__start_text_$DOM.LABEL[TDOM_NONE]$ = 0xffffffff);$NL$
            PROVIDE(__limit_text_$DOM.LABEL[TDOM_NONE]$ = 0xffffffff);$NL$
            PROVIDE(__start_rodata_$DOM.LABEL[TDOM_NONE]$ = 0xffffffff);$NL$
            PROVIDE(__limit_rodata_$DOM.LABEL[TDOM_NONE]$ = 0xffffffff);$NL$
            PROVIDE(__start_ram_$DOM.LABEL[TDOM_NONE]$ = 0xffffffff);$NL$
            PROVIDE(__limit_ram_$DOM.LABEL[TDOM_NONE]$ = 0xffffffff);$NL$
        $END$
        $NL$
    $END$$NL$
$   共有リード専用ライト領域全体
    PROVIDE(__start_srpw_all = 0xffffffff);$NL$
    PROVIDE(__limit_srpw_all = 0xffffffff);$NL$
    $NL$
$END$

$TOPPERS_ATTMOD = TOPPERS_ATTSEC + 1$
$TOPPERS_MPFAREA = TOPPERS_ATTSEC + 2$

$INCLUDE "arm_m_gcc/common/ldscript.tf"$

$NL$


$ 
$  共有領域の初期化ブロックと保護ドメイン初期化ブロックのmem依存部を生成
$ 

$FILE "kernel_mem3.c"$

$ 
$ 保護ドメイン初期化コンテキストブロックのための宣言
$ 
$FUNCTION PREPARE_DOMINICTXB$
    $IF LENGTH(DOM.ID_LIST)$
        $FOREACH domid DOM.ID_LIST$
$   RX領域（専用）
            extern char __start_text_$DOM.LABEL[domid]$;$NL$
            extern char __limit_text_$DOM.LABEL[domid]$;$NL$
$   R領域（専用）
            extern char __start_rodata_$DOM.LABEL[domid]$;$NL$
            extern char __limit_rodata_$DOM.LABEL[domid]$;$NL$
$   RWX領域（専用）
            extern char __start_ram_$DOM.LABEL[domid]$;$NL$
            extern char __limit_ram_$DOM.LABEL[domid]$;$NL$
$   共有リード専用ライト
            extern char $FORMAT("__start_ram_%s_%x_%x", DOM.LABEL[domid], +DEFAULT_ACPTN[domid], +TACP_SHARED)$;$NL$
            extern char $FORMAT("__limit_ram_%s_%x_%x", DOM.LABEL[domid], +DEFAULT_ACPTN[domid], +TACP_SHARED)$;$NL$
        $END$
        $NL$
    $END$$NL$

$  共有領域
    extern char __start_text_$DOM.LABEL[TDOM_NONE]$;$NL$
    extern char __limit_text_$DOM.LABEL[TDOM_NONE]$;$NL$
    extern char __start_rodata_$DOM.LABEL[TDOM_NONE]$;$NL$
    extern char __limit_rodata_$DOM.LABEL[TDOM_NONE]$;$NL$
    extern char __start_ram_$DOM.LABEL[TDOM_NONE]$;$NL$
    extern char __limit_ram_$DOM.LABEL[TDOM_NONE]$;$NL$
$   共有リード専用ライト領域全体
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
$   RX領域（専用）
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
$   RWX領域（専用）
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
$   共有リード専用ライト
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
$           // MEMのサイズチェックはパス2で実施済み
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
$  cfg3_out.tfの生成
$  pass 4 に持ち越す情報を出力
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

