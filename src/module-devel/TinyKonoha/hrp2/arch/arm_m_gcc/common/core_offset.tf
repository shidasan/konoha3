$ ======================================================================
$
$   TOPPERS/HRP Kernel
$       Toyohashi Open Platform for Embedded Real-Time Systems/
$       High Reliable system Profile Kernel
$
$   Copyright (C) 2011-2012 by Embedded and Real-Time Systems Laboratory
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
$ =====================================================================

$
$       オフセットファイル生成用テンプレートファイル（ARM-M用）
$

$
$  オフセット値のマクロ定義の生成
$
$DEFINE("TCB_p_tinib", offsetof_TCB_p_tinib)$
$DEFINE("TCB_texptn", offsetof_TCB_texptn)$
$DEFINE("TCB_pc", offsetof_TCB_pc)$

$DEFINE("TINIB_exinf", offsetof_TINIB_exinf)$
$DEFINE("TINIB_task", offsetof_TINIB_task)$

$
$  ビットオフセット値等のマクロ定義の生成
$
$DEFINE_BIT("TCB_enatex", sizeof_TCB, "B")$

$DEFINE("TINIB_sstksz", offsetof_TINIB_TSKINICTXB_sstksz)$
$DEFINE("TINIB_sstk_bottom", offsetof_TINIB_TSKINICTXB_sstk_bottom)$
$DEFINE("TINIB_ustksz", offsetof_TINIB_TSKINICTXB_stksz)$
$DEFINE("TINIB_ustk_bottom", offsetof_TINIB_TSKINICTXB_stk_bottom)$
$DEFINE("TINIB_start_ustk", offsetof_TINIB_TSKINICTXB_start_ustk)$
$DEFINE("TINIB_atrsz_ustk", offsetof_TINIB_TSKINICTXB_atrsz_ustk)$

$DEFINE("TINIB_p_dominib", offsetof_TINIB_p_dominib)$
$DEFINE("TINIB_texrtn", offsetof_TINIB_texrtn)$
$DEFINE("TCB_svclevel", offsetof_TCB_svclevel)$
$DEFINE_BIT("TCB_waifbd", sizeof_TCB, "B")$
$DEFINE("TCB_ssp", offsetof_TCB_ssp)$
$DEFINE("TCB_usp", offsetof_TCB_usp)$
$DEFINE("TCB_priv_mode", offsetof_TCB_priv_mode)$

$DEFINE("DOMINIB_p_dominib_info", offsetof_DOMINIB_p_dominib_info)$
$DEFINE("DOMINIB_domptn", offsetof_DOMINIB_domptn)$
$DEFINE("DOMINIB_start_rom", offsetof_DOMINIB_start_rom)$
$DEFINE("DOMINIB_atrsz_rom", offsetof_DOMINIB_atrsz_rom)$
$DEFINE("DOMINIB_start_ram", offsetof_DOMINIB_start_ram)$
$DEFINE("DOMINIB_atrsz_ram", offsetof_DOMINIB_atrsz_ram)$
$DEFINE("DOMINIB_start_srpw", offsetof_DOMINIB_start_srpw)$
$DEFINE("DOMINIB_atrsz_srpw", offsetof_DOMINIB_atrsz_srpw)$
$DEFINE("DOMINIB_start_mem", offsetof_DOMINIB_start_mem)$
$DEFINE("DOMINIB_atrsz_mem", offsetof_DOMINIB_atrsz_mem)$

