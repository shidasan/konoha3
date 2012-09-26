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

static signed char pwm_L, pwm_R;

#endif

typedef struct nxt_state_t {
#ifdef K_USING_TOPPERS
	int timer;
	int tail;
	U16 light;
	U16 target_light;
	int gyro;
	int gyro_offset;
	int gyro_prev;
	BOOL grayflag;
	F32 diff_C_motor[2];
	F32 diff_B_motor[2];
	int motor_velocity_C;
	int motor_velocity_B;
	int whitelight;
	int blacklight;

	S32 sonar;
	int bottle_side;

	S32 pid_diff[2];
	U16 pid_integral;
	
	F32 distance;
	F32 theta;
#endif
}nxt_state_t;

typedef struct {
	KonohaObjectHeader h;
	nxt_state_t *state;
} kNXT;

static nxt_state_t state;

static void kNXT_init(KonohaContext *kctx, kObject *o, void *conf)
{

}

static void kNXT_free(KonohaContext *kctx, kObject *o)
{

}

#define Int_to(T, a)               ((T)a.intValue)
#define Float_to(T, a)             ((T)a.floatValue)

static KMETHOD NXT_init(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	balance_init();
	nxt_motor_set_count(NXT_PORT_C, 0);
	nxt_motor_set_count(NXT_PORT_B, 0);
	state.gyro_offset = getGyroOffset();
	state.grayflag = 0;
	state.tail = 0;
	state.pid_integral = 0;
	state.light = ecrobot_get_light_sensor(NXT_PORT_S3);
	state.blacklight = state.light;
	state.target_light = (getWhiteLight() + state.blacklight)/2 - 25;
	state.bottle_side = 0;
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
static KMETHOD NXT_balanceControl(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	balance_control(
			Int_to(int, sfp[1]),
			Int_to(int, sfp[2]),
			ecrobot_get_gyro_sensor(NXT_PORT_S1),
			state.gyro_offset,
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
	RETURNi_(getSonarValue());
#endif
}

static void NXT_balance_inner(float forward, float turn)
{
#ifdef K_USING_TOPPERS
	signed char pwm_L, pwm_R;
	balance_control(
			(float)forward,
			(float)turn,
			(float)state.gyro,
			(float)state.gyro_offset,
			(float)state.diff_C_motor[1],
			(float)state.diff_B_motor[1],
			(float)ecrobot_get_battery_voltage(),
			&pwm_L,
			&pwm_R);
	ecrobot_set_motor_speed(NXT_PORT_C, pwm_L);
	ecrobot_set_motor_speed(NXT_PORT_B, pwm_R);
	wai_sem(EVT_SEM);
	state.timer += 4;
#endif
}

static KMETHOD NXT_balance(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	int forward = Int_to(int, sfp[1]);
	int turn = Int_to(int, sfp[2]);
	NXT_balance_inner(forward, turn);
#endif
}

static KMETHOD NXT_tailwalk(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	//ecrobot_sound_tone(1000, 200, 50);
	signed char pwm_L = Int_to(int, sfp[1]);
	signed char pwm_R = Int_to(int, sfp[2]);
	signed char pwm_L0, pwm_R0;
	balance_control(
			(float)0,
			(float)0,
			(float)state.gyro,
			(float)state.gyro_offset,
			(float)state.diff_C_motor[1],
			(float)state.diff_B_motor[1],
			(float)ecrobot_get_battery_voltage(),
			&pwm_L0,
			&pwm_R0);
	ecrobot_set_motor_speed(NXT_PORT_C, pwm_L);
	ecrobot_set_motor_speed(NXT_PORT_B, pwm_R);
	wai_sem(EVT_SEM);
	state.timer += 4;
#endif
}

static KMETHOD NXT_tailwalkPid(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
#define delta_T            0.004
#define KP                 0.38
#define KI                 0.10
#define KD                 0.08

	int32_t forward_i = Int_to(int, sfp[1]);
	F32 forward = (F32)forward_i;
	F32 p, i, d;
	state.pid_integral += (state.pid_diff[1] + state.pid_diff[0])/2.0 * delta_T;

	p = state.pid_diff[1] * KP;
	i = state.pid_integral * KI;
	d = (state.pid_diff[1] - state.pid_diff[0])/delta_T * KD;

	F32 turn = p + i + d;
	if (turn > 100) turn = 100;
	else if (turn < -50) turn = -100;

	if (forward > 50) forward = 50;
	turn = turn * forward / 50;

	ecrobot_set_motor_speed(NXT_PORT_C, (forward + turn));
	ecrobot_set_motor_speed(NXT_PORT_B, (forward - turn));
	wai_sem(EVT_SEM);
	state.timer += 4;
#endif
}

static KMETHOD NXT_balancePid(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS

#define delta_T            0.004
#define KP                 0.38
#define KI                 0.10
#define KD                 0.08

	F32 p, i, d;
	state.pid_integral += (state.pid_diff[1] + state.pid_diff[0])/2.0 * delta_T;

	p = state.pid_diff[1] * KP;
	i = state.pid_integral * KI;
	d = (state.pid_diff[1] - state.pid_diff[0]) / delta_T * KD;

	F32 turn = p + i + d;
	if (100 < turn) turn = 100;
	else if (turn < -100) turn = -100;

	int forward = Int_to(int, sfp[1]);
	NXT_balance_inner(forward, turn);
#endif
}

static KMETHOD NXT_updateStatus(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS

#define M_PI          3.14
#define ROBOT_BREADTH 16
#define WHEEL_RADIUS  4

	tail_control(state.tail); /* バランス走行用角度に制御 */
	state.sonar = getSonarValue();
	state.light = ecrobot_get_light_sensor(NXT_PORT_S3);
	state.gyro_prev = state.gyro;
	state.gyro = ecrobot_get_gyro_sensor(NXT_PORT_S1);
	state.pid_diff[0] = state.pid_diff[1];
	state.pid_diff[1] = state.light - state.target_light;
	state.grayflag = abs(state.pid_diff[1] - state.pid_diff[0]) >= 10 ? 1 : 0;
	state.diff_C_motor[0] = state.diff_C_motor[1];
	state.diff_C_motor[1] = nxt_motor_get_count(NXT_PORT_C);
	state.diff_B_motor[0] = state.diff_B_motor[1];
	state.diff_B_motor[1] = nxt_motor_get_count(NXT_PORT_B);
	state.motor_velocity_C = (state.diff_C_motor[1] - state.diff_C_motor[0])/delta_T;
	state.motor_velocity_B = (state.diff_B_motor[1] - state.diff_B_motor[0])/delta_T;

	float r_len = 2 * M_PI * WHEEL_RADIUS * (state.diff_C_motor[1] - state.diff_C_motor[0]) / 360;
	float l_len = 2 * M_PI * WHEEL_RADIUS * (state.diff_B_motor[1] - state.diff_B_motor[0]) / 360;
	state.distance += (r_len + l_len)/2;
	state.theta    += 360.0 * (r_len - l_len) / (2 * M_PI *ROBOT_BREADTH);
#endif
}

static KMETHOD NXT_getgrayFlag(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	if (state.grayflag) {
		ecrobot_sound_tone(2000, 200, 50);
	}
	RETURNb_(state.grayflag);
#else
	RETURNb_(0);
#endif
}

static KMETHOD NXT_soundTone(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	ecrobot_sound_tone(Int_to(int, sfp[1]), Int_to(int, sfp[2]), 50);
#endif
}

static KMETHOD NXT_getgyroOffset(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	RETURNi_(state.gyro_offset);
#endif
}

static KMETHOD NXT_setgyroOffset(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	state.gyro_offset = Int_to(int, sfp[1]);
#endif
}

static KMETHOD NXT_gettail(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	RETURNi_(state.tail);
#endif
}

static KMETHOD NXT_settail(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	state.tail = Int_to(int, sfp[1]);
#endif
}

static KMETHOD NXT_getdistance(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	RETURNi_(state.distance);
#endif
}

static KMETHOD NXT_setdistance(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	state.distance = Int_to(int, sfp[1]);
#endif
}

#define _Public   kMethod_Public
#define _Static   kMethod_Static
#define _Imm      kMethod_Immutable
#define _F(F)   (intptr_t)(F)

#ifdef K_USING_TINYVM
kbool_t tinykonoha_nxtMethodInit(KonohaContext *kctx, kNameSpace *ks)
{
	KDEFINE_CLASS defNXT = {
		STRUCTNAME(NXT),
		.cflag = kClass_Final,
		.init = kNXT_init,
		.free = kNXT_free,
		.typeId = TY_NXT,
	};

	KonohaClass *cNXT = KLIB Konoha_defineClass(kctx, 0, PN_konoha, NULL, &defNXT, 0);
	KINITv(((KonohaClassVar*)cNXT)->methodList, K_EMPTYARRAY);
	intptr_t MethodData[] = {
		_F(NXT_init), TY_NXT, MN_(NXT_init),
		_F(NXT_dly), TY_NXT, MN_(NXT_dly),
		_F(NXT_ecrobotIsRunning), TY_NXT, MN_(NXT_ecrobotIsRunning),
		_F(NXT_tailControl), TY_NXT, MN_(NXT_tailControl),
		_F(NXT_manipulateTail), TY_NXT, MN_(NXT_manipulateTail),
		_F(NXT_ecrobotGetGyroSensor), TY_NXT, MN_(NXT_ecrobotGetGyroSensor),
		_F(NXT_ecrobotGetLightSensor), TY_NXT, MN_(NXT_ecrobotGetLightSensor),
		_F(NXT_waiSem), TY_NXT, MN_(NXT_waiSem),
		_F(NXT_balanceControl), TY_NXT, MN_(NXT_balanceControl),
		_F(NXT_getSonarSensor), TY_NXT, MN_(NXT_getsonarSensor),

		_F(NXT_updateStatus), TY_NXT, MN_(NXT_updateStatus),
		_F(NXT_balancePid), TY_NXT, MN_(NXT_balancePid),
		_F(NXT_balance), TY_NXT, MN_(NXT_balance),
		_F(NXT_tailwalk), TY_NXT, MN_(NXT_tailwalk),
		_F(NXT_tailwalkPid), TY_NXT, MN_(NXT_tailwalkPid),
		_F(NXT_getgrayFlag), TY_NXT, MN_(NXT_getgrayFlag),
		_F(NXT_soundTone), TY_NXT, MN_(NXT_soundTone),
		_F(NXT_getgyroOffset), TY_NXT, MN_(NXT_getgyroOffset),
		_F(NXT_setgyroOffset), TY_NXT, MN_(NXT_setgyroOffset),
		_F(NXT_gettail), TY_NXT, MN_(NXT_gettail),
		_F(NXT_settail), TY_NXT, MN_(NXT_settail),
		_F(NXT_getdistance), TY_NXT, MN_(NXT_getdistance),
		_F(NXT_setdistance), TY_NXT, MN_(NXT_setdistance),
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
			//_Public             , _F(NXT_new), TY_NXT, TY_NXT, MN_("new"), 0, 
			_Public|_Static|_Imm, _F(NXT_init), TY_void, TY_NXT, MN_("init"), 0,

			_Public|_Static|_Imm, _F(NXT_balanceControl), TY_void, TY_NXT, MN_("balanceControl"), 2, TY_int, FN_x, TY_int, FN_y, 
			//_Public|_Static|_Imm, _F(NXT_balanceInit), TY_void, TY_NXT, MN_("balanceInit"), 0,
			_Public|_Static|_Imm, _F(NXT_dly), TY_void, TY_NXT, MN_("dly"), 1, TY_int, FN_x, 
			_Public|_Static|_Imm, _F(NXT_ecrobotIsRunning), TY_boolean, TY_NXT, MN_("ecrobotIsRunning"), 0, 
			_Public|_Static|_Imm, _F(NXT_tailControl), TY_void, TY_NXT, MN_("tailControl"), 1, TY_int, FN_x, 
			_Public|_Static|_Imm, _F(NXT_manipulateTail), TY_void, TY_NXT, MN_("manipulateTail"), 0,
			_Public|_Static|_Imm, _F(NXT_ecrobotGetGyroSensor), TY_int, TY_NXT, MN_("ecrobotGetGyroSensor"), 0,
			_Public|_Static|_Imm, _F(NXT_ecrobotGetLightSensor), TY_int, TY_NXT, MN_("ecrobotGetLightSensor"), 0,
			_Public|_Static|_Imm, _F(NXT_waiSem), TY_void, TY_NXT, MN_("waiSem"), 0,
			_Public|_Static|_Imm, _F(NXT_getSonarSensor), TY_int, TY_NXT, MN_("getsonarSensor"), 0,

			_Public|_Static|_Imm, _F(NXT_updateStatus), TY_void, TY_NXT, MN_("updateStatus"), 0,
			_Public|_Static|_Imm, _F(NXT_balancePid), TY_void, TY_NXT, MN_("balancePid"), 1, TY_int, FN_x,
			_Public|_Static|_Imm, _F(NXT_balance), TY_void, TY_NXT, MN_("balance"), 2, TY_int, FN_x, TY_int, FN_y,
			_Public|_Static|_Imm, _F(NXT_tailwalk), TY_void, TY_NXT, MN_("tailwalk"), 2, TY_int, FN_x, TY_int, FN_y,
			_Public|_Static|_Imm, _F(NXT_tailwalkPid), TY_void, TY_NXT, MN_("tailwalkPid"), 1, TY_int, FN_x,
			_Public|_Static|_Imm, _F(NXT_getgrayFlag), TY_boolean, TY_NXT, MN_("getgrayFlag"), 0,
			_Public|_Static|_Imm, _F(NXT_soundTone), TY_boolean, TY_NXT, MN_("soundTone"), 2, TY_int, FN_x, TY_int, FN_y, 
			_Public|_Static|_Imm, _F(NXT_getgyroOffset), TY_int, TY_NXT, MN_("getgyroOffset"), 0,
			_Public|_Static|_Imm, _F(NXT_setgyroOffset), TY_void, TY_NXT, MN_("setgyroOffset"), 1, TY_int, FN_x,
			_Public|_Static|_Imm, _F(NXT_gettail), TY_int, TY_NXT, MN_("gettail"), 0,
			_Public|_Static|_Imm, _F(NXT_settail), TY_void, TY_NXT, MN_("settail"), 1, TY_int, FN_x,
			_Public|_Static|_Imm, _F(NXT_getdistance), TY_int, TY_NXT, MN_("getdistance"), 0,
			_Public|_Static|_Imm, _F(NXT_setdistance), TY_void, TY_NXT, MN_("setdistance"), 1, TY_int, FN_x,
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
