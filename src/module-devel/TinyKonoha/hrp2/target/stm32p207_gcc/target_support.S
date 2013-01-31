
#define TOPPERS_MACRO_ONLY
#define UINT_C(val)		(val)		/* uint_t型の定数を作るマクロ */
#define ULONG_C(val)	(val)		/* ulong_t型の定数を作るマクロ */
#define CAST(type, val)	(val)		/* 型キャストを行うマクロ */

#include "kernel_impl.h"
#include "arm_m.h"
#include "offset.h"
#include "target_asm.inc"
#if 0

    /*
     *  ret_tex，ext_tsk，ext_kerをsvc命令で呼び出す
     */
    ATEXT
    AALIGN(4)
    ATHUMB(call_ret_tex)
    AGLOBAL(call_ret_tex)
ALABEL(call_ret_tex)
    mov     r4, #TFN_EXT_TSK
    svc     #NO_RET_TEX
    nop
    mov     r4, #TFN_EXT_TSK
    svc     #NO_SVC
    nop
    mov     r4, #TFN_EXT_KER
    svc     #NO_SVC
    nop
#endif

