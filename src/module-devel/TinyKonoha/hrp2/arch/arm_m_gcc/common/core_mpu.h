/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 *	
 *	Copyright (C) 2012 by Embedded and Real-Time Systems Laboratory
 *				Graduate School of Information Science, Nagoya Univ., JAPAN
 *	
 *	上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *	ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *	変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *	(1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *		権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *		スコード中に含まれていること．
 *	(2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *		用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *		者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *		の無保証規定を掲載すること．
 *	(3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *		用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *		と．
 *	  (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *		  作権表示，この利用条件および下記の無保証規定を掲載すること．
 *	  (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *		  報告すること．
 *	(4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *		害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *		また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *		由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *		免責すること．
 *	
 *	本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *	よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *	に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *	アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *	の責任を負わない．
 *	
 */

/*
 *	MPUドライバ
 */

#ifndef TOPPERS_CORE_MPU_H
#define TOPPERS_CORE_MPU_H

/*
 *  MPUタイプレジスタ
 *  [- 31:24] [IREGION 23:16] [DREGION 15:8] [- 7:1] SEPARATE
 */
#define MPU_TYPE    0xe000ed90
#define MPU_TYPE_IREGION    0x00ff0000
#define MPU_TYPE_DREGION    0x0000ff00
#define MPU_TYPE_SEPARATE   0x00000001

/*
 *  MPU制御レジスタ
 *  [- 31:2] PRIVDEFENA HFNMIENA ENABLE
 */
#define MPU_CR      0xe000ed94
#define MPU_CR_PRIVDEFENA   0x00000004 
#define MPU_CR_HFNMIENA     0x00000002 
#define MPU_CR_ENABLE       0x00000001

/*
 *  MPU領域番号レジスタ
 *  [- 31:8] [REGION 7:0]
 */
#define MPU_REGNO   0xe000ed98
#define MPU_REGNO_REGION    0x000000ff

/*
 *  MPU領域ベースアドレスレジスタ
 *  [ADDR 31:N] [VALID 4] [REGION 3:0]
 */
#define MPU_REGBASE 0xe000ed9c
#define MPU_REGBASE_ADDR    0xffffffe0 /* ベースアドレスフィールド */
#define MPU_REGBASE_VALID   0x00000010 /* 領域番号有効ビット */
#define MPU_REGBASE_REGION  0x0000000f /* 領域番号オーバライドフィールド */

/*
 *  MPU領域属性およびサイズレジスタ
 *  [- 31:29] XN - [AP 26:24] [- 23:22] [TEX 21:19] S C B [SRD 15:8] [- 7:6] [SIZE 5:1] ENABLE
 */
#define MPU_REGATR  0xe000eda0
#define MPU_REGATR_XN 0x10000000 /* 命令アクセス禁止ビット */
#define MPU_REGATR_AP 0x07000000 /* データアクセス許可フィールド */
#define TO_MPU_AP(ap) (ap << 24)

/*
 *  データアクセス許可パターン
 */
#define MPU_AP_NOT      0x00 /* アクセス禁止 */
#define MPU_AP_PRW      0x01 /* 特権のみアクセス可能 */
#define MPU_AP_PRWUR    0x02 /* ユーザは読出しのみ可能，特権はアクセス可能 */
#define MPU_AP_PURW     0x03 /* ユーザ，特権ともにアクセス可能 */
#define MPU_AP_PR       0x05 /* 特権のみ読出しアクセス可能 */
#define MPU_AP_PUR      0x06 /* ユーザ，特権ともに読出しアクセス可能 */

#define MPU_REGATR_TEX  0x00380000 /* タイプ拡張フィールド */
#define MPU_REGATR_S    0x00040000 /* 共有可ビット */
#define MPU_REGATR_C    0x00020000 /* キャッシュ可ビット */
#define MPU_REGATR_B    0x00010000 /* バッファ可ビット */
#define MPU_REGATR_SRD  0x0000ff00 /* サブ領域禁止フィールド */
#define MPU_REGATR_SIZE 0x0000003e /* 領域サイズフィールド */
#define TO_MPU_SIZE(size) (size << 1)
#define MPU_REGATR_ENABLE   0x00000001 /* 領域許可ビット */

/*
 *  MPUエイリアス1領域ベースアドレスレジスタ
 */
#define MPU_AL1BASE 0xe000eda4

/*
 *  MPUエイリアス1領域属性およびサイズレジスタ
 */
#define MPU_AL1ATR  0xe000eda8

/*
 *  MPUエイリアス2領域ベースアドレスレジスタ
 */
#define MPU_AL2BASE 0xe000edac

/*
 *  MPUエイリアス2領域属性およびサイズレジスタ
 */
#define MPU_AL2ATR  0xe000edb0

/*
 *  MPUエイリアス3領域ベースアドレスレジスタ
 */
#define MPU_AL3BASE 0xe000edb4

/*
 *  MPUエイリアス3領域属性およびサイズレジスタ
 */
#define MPU_AL3ATR  0xe000edb8

/*
 *  例外番号の定義
 */
// メモリ保護違反
#define EXCNO_MEM_MNG       0x04

#ifndef TOPPERS_MACRO_ONLY
// 初期化ルーチン 
extern void target_mpu_initialize(void);
// メモリ保護違反例外ハンドラ
extern void target_mpu_exc_handler(void *p_excinf);
// タスク例外実行開始時スタック不正ハンドラ
extern void target_emulate_texrtn_handler(void *p_excinf);
// タスク例外リターン時スタック不正ハンドラ
extern void target_emulate_ret_tex_handler(void *p_excinf);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_CORE_MPU_H */
