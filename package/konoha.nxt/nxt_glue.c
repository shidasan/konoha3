/****************************************************************************
 * Copyright (c) 2012, the Konoha project authors. All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ***************************************************************************/

#ifndef K_USING_TINYVM
#include<minikonoha/minikonoha.h>
#include<minikonoha/sugar.h>
#include<minikonoha/float.h>
#else
#include "tinykonoha.h"
#include "tinyvm_gen.h"
#include "constant.h"
#endif

#ifdef K_USING_TOPPERS
#include "tinykonoha_config.h"
#include "kernel_id.h"
#include "ecrobot_base.h"
#include "ecrobot_interface.h"
#include "balancer.h"
#include "nxt.h"
#endif

typedef struct {
	KonohaObjectHeader h;
} kNXT;

static void kNXT_init(KonohaContext *kctx, kObject *o, void *conf)
{

}

static void kNXT_free(KonohaContext *kctx, kObject *o)
{

}

#define Int_to(T, a)               ((T)a.intValue)
#define Float_to(T, a)             ((T)a.floatValue)

static KMETHOD NXT_balanceInit(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	TDBG_s("balance init");
	balance_init();
#endif
}
static KMETHOD NXT_dly(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	int delay = Int_to(int, sfp[1]);
	dly_tsk(delay);
#endif
}
static KMETHOD NXT_ecrobotIsRunning(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	RETURNb_(ecrobotIsRunning());
#else
	RETURNb_(0);
#endif
}
static KMETHOD NXT_tailControl(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
#define P_GAIN 2.5F
#define PWM_ABS_MAX 60
	int angle = Int_to(int, sfp[1]);
	float pwm = (float)(angle - nxt_motor_get_count(NXT_PORT_A)) * P_GAIN;
	if (pwm > PWM_ABS_MAX) {
		pwm = PWM_ABS_MAX;
	} else if (pwm < -PWM_ABS_MAX) {
		pwm = -PWM_ABS_MAX;
	}
	nxt_motor_set_speed(NXT_PORT_A, (signed char)pwm, 1);
#endif
}
static KMETHOD NXT_manipulateTail(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	manipulate_tail();
#endif
}
static KMETHOD NXT_ecrobotGetGyroSensor(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	RETURNi_(ecrobot_get_gyro_sensor(NXT_PORT_S1));
#else
	RETURNi_(0);
#endif
}
static KMETHOD NXT_ecrobotGetLightSensor(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	RETURNi_(ecrobot_get_light_sensor(NXT_PORT_S3));
#else
	RETURNi_(0);
#endif
}
static KMETHOD NXT_waiSem(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	wai_sem(EVT_SEM);
#endif
}
static signed char pwm_L, pwm_R;
static KMETHOD NXT_balanceControl(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	balance_control(
			Int_to(int, sfp[1]),
			Int_to(int, sfp[2]),
			ecrobot_get_gyro_sensor(NXT_PORT_S1),
			getGyroOffset(),
			nxt_motor_get_count(NXT_PORT_C),
			nxt_motor_get_count(NXT_PORT_B),
			ecrobot_get_battery_voltage(),
			&pwm_L,
			&pwm_R);
	ecrobot_set_motor_speed(NXT_PORT_C, pwm_L);
	ecrobot_set_motor_speed(NXT_PORT_B, pwm_R);
#endif
}

static KMETHOD NXT_getSonarSensor(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	RETURNi_(sonar_value);
#endif
}

#define _Public   kMethod_Public
#define _Static   kMethod_Static
#define _Imm      kMethod_Immutable
#define _F(F)   (intptr_t)(F)

#ifdef K_USING_TINYVM
kbool_t tinykonoha_nxtMethodInit(KonohaContext *kctx, kNameSpace *ks)
{
	intptr_t MethodData[] = {
		_F(NXT_balanceInit), TY_System, MN_(NXT_balanceInit),
		_F(NXT_dly), TY_System, MN_(NXT_dly),
		_F(NXT_ecrobotIsRunning), TY_System, MN_(NXT_ecrobotIsRunning),
		_F(NXT_tailControl), TY_System, MN_(NXT_tailControl),
		_F(NXT_manipulateTail), TY_System, MN_(NXT_manipulateTail),
		_F(NXT_ecrobotGetGyroSensor), TY_System, MN_(NXT_ecrobotGetGyroSensor),
		_F(NXT_ecrobotGetLightSensor), TY_System, MN_(NXT_ecrobotGetLightSensor),
		_F(NXT_waiSem), TY_System, MN_(NXT_waiSem),
		_F(NXT_balanceControl), TY_System, MN_(NXT_balanceControl),
		_F(NXT_getSonarSensor), TY_System, MN_(NXT_getsonarSensor),
		DEND,
	};
	KLIB kNameSpace_loadMethodData(kctx, ks, MethodData);
	return true;
}

#else

static	kbool_t nxt_initPackage(KonohaContext *kctx, kNameSpace *ks, int argc, const char**args, kfileline_t pline)
{
	KDEFINE_CLASS defNXT = {
		STRUCTNAME(NXT),
		.cflag = kClass_Final,
		.init  = kNXT_init,
		.free  = kNXT_free,
	};
	KonohaClass *cNXT = KLIB kNameSpace_defineClass(kctx, ks, NULL, &defNXT, pline);
	ktype_t TY_NXT = cNXT->typeId;
	int FN_x = FN_("x");
	int FN_y = FN_("y");
	intptr_t MethodData[] = {
			_Public|_Static|_Imm, _F(NXT_balanceControl), TY_void, TY_NXT, MN_("balanceControl"), 2, TY_int, FN_x, TY_int, FN_y, 
			_Public|_Static|_Imm, _F(NXT_balanceInit), TY_void, TY_NXT, MN_("balanceInit"), 0,
			_Public|_Static|_Imm, _F(NXT_dly), TY_void, TY_NXT, MN_("dly"), 1, TY_int, FN_x, 
			_Public|_Static|_Imm, _F(NXT_ecrobotIsRunning), TY_boolean, TY_NXT, MN_("ecrobotIsRunning"), 0, 
			_Public|_Static|_Imm, _F(NXT_tailControl), TY_void, TY_NXT, MN_("tailControl"), 1, TY_int, FN_x, 
			_Public|_Static|_Imm, _F(NXT_manipulateTail), TY_void, TY_NXT, MN_("manipulateTail"), 0,
			_Public|_Static|_Imm, _F(NXT_ecrobotGetGyroSensor), TY_int, TY_NXT, MN_("ecrobotGetGyroSensor"), 0,
			_Public|_Static|_Imm, _F(NXT_ecrobotGetLightSensor), TY_int, TY_NXT, MN_("ecrobotGetLightSensor"), 0,
			_Public|_Static|_Imm, _F(NXT_waiSem), TY_void, TY_NXT, MN_("waiSem"), 0,
			_Public|_Static|_Imm, _F(NXT_getSonarSensor), TY_int, TY_NXT, MN_("getsonarSensor"), 0,
			DEND,
	};
	KLIB kNameSpace_loadMethodData(kctx, ks, MethodData);

	//KDEFINE_FLOAT_CONST FloatData[] = {
	//		{_KVf(E)},
	//		{_KVf(LOG2E)},
	//		{_KVf(LOG10E)},
	//		{_KVf(LN2)},
	//		{_KVf(LN10)},
	//		{_KVf(PI)},
	//		{_KVf(SQRT2)},
	//		{}
	//};
	//kNameSpace_loadConstData(ks, FloatData, 0);
	return true;
}

static kbool_t nxt_setupPackage(KonohaContext *kctx, kNameSpace *ks, isFirstTime_t isFirstTime, kfileline_t pline)
{
	return true;
}

static kbool_t nxt_initNameSpace(KonohaContext *kctx,  kNameSpace *packageNameSpace, kNameSpace *ks, kfileline_t pline)
{
	//KEXPORT_PACKAGE("konoha.float", ks, pline);
	return true;
}

static kbool_t nxt_setupNameSpace(KonohaContext *kctx, kNameSpace *packageNameSpace, kNameSpace *ks, kfileline_t pline)
{
	return true;
}
KDEFINE_PACKAGE* nxt_init(void)
{
	static KDEFINE_PACKAGE d = {
		KPACKNAME("nxt", "1.0"),
		.initPackage = nxt_initPackage,
		.setupPackage = nxt_setupPackage,
		.initNameSpace = nxt_initNameSpace,
		.setupNameSpace = nxt_setupNameSpace,
	};
	return &d;
}

#endif
