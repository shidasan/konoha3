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

typedef struct {
	float kp;
	float ki;
	float kd;
} PIDParam;

//static void setPID(PIDParam);

static const PIDParam PID_BASIC = { 0.36, 0.08, 0.05 };
static const PIDParam PID_LINE  = { 0.36, 0.08, 0.05 };
static const PIDParam PID_CURVE = { 0.38, 0.08, 0.05 };

#endif

typedef struct nxt_state_t {
#ifdef K_USING_TOPPERS
	int timer;
	int tail;
	U16 light_previous;
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

	PIDParam pidParam;

	int turn_offset;
	//F32 kp;
	//F32 ki;
	//F32 kd;
#endif
}nxt_state_t;

typedef struct {
	KonohaObjectHeader h;
	nxt_state_t *state;
} kNXT;
nxt_state_t nxtstate;

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
	nxtstate.gyro_offset = getGyroOffset();
	nxtstate.grayflag = 0;
	nxtstate.tail = 0;
	nxtstate.pid_integral = 0;
	nxtstate.light = ecrobot_get_light_sensor(NXT_PORT_S3);
	nxtstate.blacklight = nxtstate.light;
	nxtstate.target_light = (getWhiteLight() + nxtstate.blacklight)/2 - 25;
	nxtstate.pidParam = PID_BASIC;
	nxtstate.turn_offset = 0;
#endif
}
//static KMETHOD NXT_dly(KonohaContext *kctx, KonohaStack *sfp)
//{
//#ifdef K_USING_TOPPERS
//	int delay = Int_to(int, sfp[1]);
//	dly_tsk(delay);
//#endif
//}
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
//#define P_GAIN 2.5F
//#define PWM_ABS_MAX 60
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
//static KMETHOD NXT_waiSem(KonohaContext *kctx, KonohaStack *sfp)
//{
//#ifdef K_USING_TOPPERS
//	wai_sem(EVT_SEM);
//#endif
//}
//static KMETHOD NXT_balanceControl(KonohaContext *kctx, KonohaStack *sfp)
//{
//#ifdef K_USING_TOPPERS
//	balance_control(
//			Int_to(int, sfp[1]),
//			Int_to(int, sfp[2]),
//			ecrobot_get_gyro_sensor(NXT_PORT_S1),
//			nxtstate.gyro_offset,
//			nxt_motor_get_count(NXT_PORT_C),
//			nxt_motor_get_count(NXT_PORT_B),
//			ecrobot_get_battery_voltage(),
//			&pwm_L,
//			&pwm_R);
//	ecrobot_set_motor_speed(NXT_PORT_C, pwm_L);
//	ecrobot_set_motor_speed(NXT_PORT_B, pwm_R);
//#endif
//}

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
			(float)nxtstate.gyro,
			(float)nxtstate.gyro_offset,
			(float)nxtstate.diff_C_motor[1],
			(float)nxtstate.diff_B_motor[1],
			(float)ecrobot_get_battery_voltage(),
			&pwm_L,
			&pwm_R);
	//ecrobot_set_motor_speed(NXT_PORT_C, pwm_L);
	//ecrobot_set_motor_speed(NXT_PORT_B, pwm_R);
	ecrobot_set_motor_speed(NXT_PORT_C, (1.189 *pwm_L));      /* 左モータPWM出力セット */
	ecrobot_set_motor_speed(NXT_PORT_B, (1.13 * pwm_R));      /* 右モータPWM出力セット */
	wai_sem(EVT_SEM);
	nxtstate.timer += 4;
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

#ifdef K_USING_TOPPERS
static System_tailwalk(int pwm_Linput, int pwm_Rinput)
{
	ecrobot_set_motor_speed(NXT_PORT_C, pwm_Linput);
	ecrobot_set_motor_speed(NXT_PORT_B, pwm_Rinput);
	wai_sem(EVT_SEM);
	nxtstate.timer += 4;
}
#endif

static KMETHOD NXT_tailwalk(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	//ecrobot_sound_tone(1000, 200, 50);
	signed char pwm_L = Int_to(int, sfp[1]);
	signed char pwm_R = Int_to(int, sfp[2]);
	System_tailwalk(pwm_L, pwm_R);
#endif
}

static KMETHOD NXT_tailwalkPid(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
#define delta_T            0.004
//#define KP                 0.12
//#define KI                 0.20
//#define KD                 0.12

	int32_t forward_i = Int_to(int, sfp[1]);
	F32 forward = (F32)forward_i;
	F32 p, i, d;
	nxtstate.pid_integral += (nxtstate.pid_diff[1] + nxtstate.pid_diff[0])/2.0 * delta_T;

	p = nxtstate.pid_diff[1] * nxtstate.pidParam.kp;
	i = nxtstate.pid_integral * nxtstate.pidParam.ki;
	d = (nxtstate.pid_diff[1] - nxtstate.pid_diff[0])/delta_T * nxtstate.pidParam.kd;

	F32 turn = p + i + d + nxtstate.turn_offset;
	if (turn > 100) turn = 100;
	else if (turn < -50) turn = -100;

	if (forward > 50) forward = 50;
	turn = turn * forward / 50;

	ecrobot_set_motor_speed(NXT_PORT_C, (forward + turn));
	ecrobot_set_motor_speed(NXT_PORT_B, (forward - turn));
	wai_sem(EVT_SEM);
	nxtstate.timer += 4;
#endif
}

#ifdef K_USING_TOPPERS
static void balancePid(float forward)
{
	F32 p, i, d;
	nxtstate.pid_integral += (nxtstate.pid_diff[1] + nxtstate.pid_diff[0])/2.0 * delta_T;

	p = nxtstate.pid_diff[1] * nxtstate.pidParam.kp;
	i = nxtstate.pid_integral * nxtstate.pidParam.ki;
	d = (nxtstate.pid_diff[1] - nxtstate.pid_diff[0]) / delta_T * nxtstate.pidParam.kd;

	F32 turn = p + i + d + nxtstate.turn_offset;
	if (100 < turn) turn = 100;
	else if (turn < -100) turn = -100;
	NXT_balance_inner(forward, turn);
}
#endif

static KMETHOD NXT_balancePid(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	int forward = Int_to(int, sfp[1]);
	balancePid(forward);
#endif
}

//// method System.update()
//void System_update() {
//	tail_control(share->tail); /* バランス走行用角度に制御 */
//	share->light_previous = share->light;
//	share->light = (PID_FILTER * ecrobot_get_light_sensor(NXT_PORT_S3) + (1.0 - PID_FILTER) * share->light_previous);
//	share->gyro_prev = share->gyro;
//	share->gyro = (GYRO_FILTER * ecrobot_get_gyro_sensor(NXT_PORT_S1) + (1.0 - GYRO_FILTER) * share->gyro_prev);
//	share->pid_diff[0] = share->pid_diff[1];
//	share->pid_diff[1] = share->light - share->target_light;
//	share->grayflag = abs(share->pid_diff[1] - share->pid_diff[0]) >= 7 ? ON : OFF;
//	share->diff_C_motor[0] = share->diff_C_motor[1];
//	share->diff_C_motor[1] = nxt_motor_get_count(NXT_PORT_C);
//	share->diff_B_motor[0] = share->diff_B_motor[1];
//	share->diff_B_motor[1] = nxt_motor_get_count(NXT_PORT_B);
//	share->motor_velocity_C = (share->diff_C_motor[1] - share->diff_C_motor[0])/delta_T;
//	share->motor_velocity_B = (share->diff_B_motor[1] - share->diff_B_motor[0])/delta_T;
//
//	float r_len = 2 * M_PI * WHEEL_RADIUS * (share->diff_C_motor[1] - share->diff_C_motor[0]) / 360;
//	float l_len = 2 * M_PI * WHEEL_RADIUS * (share->diff_B_motor[1] - share->diff_B_motor[0]) / 360;
//	share->distance += (r_len + l_len)/2;
//	share->theta    += 360.0 * (r_len - l_len) / (2 * M_PI *ROBOT_BREADTH);
//}

static void System_update()
{
#ifdef K_USING_TOPPERS

#define M_PI          3.14
#define ROBOT_BREADTH 16
#define WHEEL_RADIUS  4
#define PID_FILTER 0.5
#define GYRO_FILTER 0.8


	tail_control(nxtstate.tail); /* 繝舌Λ繝ｳ繧ｹ襍ｰ陦檎畑隗貞ｺｦ縺ｫ蛻ｶ蠕｡ */
	nxtstate.sonar = getSonarValue();
	nxtstate.light_previous = nxtstate.light;
	nxtstate.light = (PID_FILTER * ecrobot_get_light_sensor(NXT_PORT_S3) + (1.0 - PID_FILTER) * nxtstate.light_previous);
	//nxtstate.light = ecrobot_get_light_sensor(NXT_PORT_S3);
	nxtstate.gyro_prev = nxtstate.gyro;
	nxtstate.gyro = ecrobot_get_gyro_sensor(NXT_PORT_S1);
	nxtstate.pid_diff[0] = nxtstate.pid_diff[1];
	nxtstate.pid_diff[1] = nxtstate.light - nxtstate.target_light;
	nxtstate.grayflag = (nxtstate.pid_diff[1] - nxtstate.pid_diff[0]) >= 5 ? 1 : 0;
	//nxtstate.grayflag = abs(nxtstate.pid_diff[1] - nxtstate.pid_diff[0]) >= 7 ? 1 : 0;
	nxtstate.diff_C_motor[0] = nxtstate.diff_C_motor[1];
	nxtstate.diff_C_motor[1] = nxt_motor_get_count(NXT_PORT_C);
	nxtstate.diff_B_motor[0] = nxtstate.diff_B_motor[1];
	nxtstate.diff_B_motor[1] = nxt_motor_get_count(NXT_PORT_B);
	nxtstate.motor_velocity_C = (nxtstate.diff_C_motor[1] - nxtstate.diff_C_motor[0])/delta_T;
	nxtstate.motor_velocity_B = (nxtstate.diff_B_motor[1] - nxtstate.diff_B_motor[0])/delta_T;

	float r_len = 2 * M_PI * WHEEL_RADIUS * (nxtstate.diff_C_motor[1] - nxtstate.diff_C_motor[0]) / 360;
	float l_len = 2 * M_PI * WHEEL_RADIUS * (nxtstate.diff_B_motor[1] - nxtstate.diff_B_motor[0]) / 360;
	nxtstate.distance += (r_len + l_len)/2;
	nxtstate.theta    += 360.0 * (r_len - l_len) / (2 * M_PI *ROBOT_BREADTH);
#endif
}

static KMETHOD NXT_updateStatus(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	System_update();
#endif
}

static KMETHOD NXT_getgrayFlag(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	//if (nxtstate.grayflag) {
	//	ecrobot_sound_tone(2000, 200, 50);
	//}
	RETURNb_(nxtstate.grayflag);
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
	RETURNi_(nxtstate.gyro_offset);
#endif
}

static KMETHOD NXT_setgyroOffset(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	nxtstate.gyro_offset = Int_to(int, sfp[1]);
#endif
}

static KMETHOD NXT_gettail(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	RETURNi_(nxtstate.tail);
#endif
}

static KMETHOD NXT_settail(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	nxtstate.tail = Int_to(int, sfp[1]);
#endif
}

static KMETHOD NXT_getdistance(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	RETURNi_(nxtstate.distance);
#endif
}

static KMETHOD NXT_setdistance(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	nxtstate.distance = Int_to(int, sfp[1]);
#endif
}
static KMETHOD NXT_gettimer(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	RETURNi_(nxtstate.timer);
#endif
}

static KMETHOD NXT_cleartimer(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	nxtstate.timer = 0;
#endif
}

static KMETHOD NXT_gettheta(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	RETURNi_((int)nxtstate.theta);
#endif
}

static KMETHOD NXT_cleartheta(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	nxtstate.theta = 0.0;
#endif
}
static KMETHOD NXT_getlight(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	RETURNi_(nxtstate.light);
#endif
}
static KMETHOD NXT_gettargetLight(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	RETURNi_(nxtstate.target_light);
#endif
}
static KMETHOD NXT_settargetLight(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	nxtstate.target_light = Int_to(int, sfp[1]);
#endif
}
static KMETHOD NXT_resetMotor(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	balance_init();
	nxt_motor_set_count(NXT_PORT_C, 0);
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxtstate.diff_C_motor[0] = 0;
	nxtstate.diff_C_motor[1] = 0;
	nxtstate.diff_B_motor[0] = 0;
	nxtstate.diff_B_motor[1] = 0;
#endif
}

#ifdef K_USING_TOPPERS
static int abs(int n) {return n<0 ? -n : n; }
static float fabs(float n) {return n<0 ? -n : n; }
void System_tailwalk_strait(int pwm, float target_theta)
{
#define DIFF_PWM -4
	int d = 0;
	float diff = nxtstate.theta - target_theta;
	if(diff >= 1.0) d = DIFF_PWM;
	else if (diff <= -1.0) d = -DIFF_PWM;
	System_tailwalk(pwm+d, pwm-d);
}

void change_state_rotate(float target)
{
	while (true) {
		System_update();
		float t = nxtstate.theta;
		if (fabs(target - t) < 2.0) break;
		float turn;
		if (t < target) {
			turn = 30;
		} else {
			turn = -30;
		}
		System_tailwalk(turn, -turn);
	}
}

//static void setPID(PIDParam p)
//{
//	nxtstate.kp = p.KP;
//	nxtstate.ki = p.KP;
//	nxtstate.kd = p.KD;
//}

void System_balance_walk_straight(float forward, float theta) {
	float turn = 0;
	if(nxtstate.theta-theta > 2.0) turn = -5.0;
	if(nxtstate.theta-theta < -2.0) turn = 5.0;
	NXT_balance_inner(forward, turn);
}

#endif
static KMETHOD NXT_tailwalkWithBottle(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
#define WALK_TURN_PWD 8
#define WALK_PWM     -20
	int isLeft = Int_to(int, sfp[1]);
	int _target = Int_to(int, sfp[2]);
	int dist_bind   = Int_to(int, sfp[3]);
	int isCheckLight = Int_to(int, sfp[4]);
	float target = _target;
	float dist = dist_bind;

	nxtstate.distance = 0.0;
	int time1 = nxtstate.timer;
	int time2 = nxtstate.timer;
	float dist0 = 0;
	float target0 = target;
	int errcount = 0;
	//TDBG_i("target", _target);
	while(nxtstate.distance < dist) {
		System_update();
		// error: not walking!
		if(nxtstate.timer - time1 > 200) {
			if(fabs(dist0 - nxtstate.distance) < 1.0) {
				//ecrobot_sound_tone(2000, 200, 50);
				time1 = nxtstate.timer;
				if(errcount == 2) {
					target += isLeft ? -60.0 : 60.0;
					isLeft = !isLeft;
					errcount = 0;
				} else {
					target += isLeft ? 20.0 : -20.0;
					errcount++;
				}
				while(nxtstate.timer - time1 < 800) {
					System_update();
					System_tailwalk_strait(-20, target);
				}
				change_state_rotate(target);
				time2 = nxtstate.timer;
			}
			dist0 = nxtstate.distance;
			time1 = nxtstate.timer;
		}
		// error: direction changed
		if(abs(target0 - nxtstate.theta) > 8.0 && nxtstate.timer-time2 > 2000) {
			//ecrobot_sound_tone(1500, 200, 50);
			time2 = nxtstate.timer;
			target = target0;
			change_state_rotate(target);
			time2 = nxtstate.timer;
		}
		// check light sensor
		if(isCheckLight && nxtstate.light > nxtstate.target_light) {
			break;
		}
		System_tailwalk_strait(20, target);
	}
#endif
}

static KMETHOD NXT_rotate(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	int target = Int_to(int, sfp[1]);
	change_state_rotate(target);
#endif
}

static KMETHOD NXT_initPID(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	float kp = Float_to(float, sfp[1]);
	float ki = Float_to(float, sfp[2]);
	float kd = Float_to(float, sfp[3]);
	nxtstate.pidParam.kp = kp;
	nxtstate.pidParam.ki = ki;
	nxtstate.pidParam.kd = kd;
#endif
}

#define L_SLOPE 238 // in: 238, out: 160

#define BALANCE_PID(cond, forward, offset) \
    /*nxtstate.turn_offset = 0.0;*/\
	nxtstate.turn_offset = offset;\
    while(cond) { \
        System_update(); \
        balancePid(forward); \
    } \
    /*ecrobot_sound_tone(1000, 200, 50);*/

static KMETHOD NXT_basicStage(KonohaContext *kctx, KonohaStack *sfp)
{
#ifdef K_USING_TOPPERS
	const int FORWARD_LINE = 150;
	const int FORWARD_CURVE1 = 150;
	const int FORWARD_CURVE2 = 150;

	/* 0: startup */
	System_update();
	nxtstate.timer = 0;
	nxtstate.distance = 0;
	while(nxtstate.timer < 1500) {
		System_update();
		System_balance_walk_straight(60.0, 0.0);
	}
	///* debug upstair */
	//while(nxtstate.timer < 4000 || !System_getGrayFlag()) {
	//	System_update();
	//	System_balancePid(80.0);
	//}
	//ecrobot_sound_tone(1000, 200, 50);
	//change_state_outside_kaidan();

	/* 1: start */
	nxtstate.timer = 0;
	nxtstate.pidParam = PID_BASIC;

	while(nxtstate.timer < 1000) { 
		System_update(); 
		balancePid(100); 
	}
	//ecrobot_sound_tone(1000, 200, 50);

	nxtstate.pidParam = PID_LINE;
	BALANCE_PID(nxtstate.distance < (L_SLOPE-20), FORWARD_LINE, 0);

	/* 2: to previous slope */
	//syslog_0(LOG_NOTICE, " 2: to previous slope (int)p, (int)i, (int)d, (int)turn");
	nxtstate.theta = 0;
	BALANCE_PID(nxtstate.distance < (L_SLOPE+20), 90.0, 0);

	/* 3: to slope downing */
	//syslog_0(LOG_NOTICE, " 3: to slope downing (int)p, (int)i, (int)d, (int)turn");
	BALANCE_PID(nxtstate.distance < (L_SLOPE+180), FORWARD_LINE, 0);

	/* 4 */
	//syslog_0(LOG_NOTICE, " 4 (int)p, (int)i, (int)d, (int)turn");
	nxtstate.pidParam = PID_CURVE;
	BALANCE_PID(nxtstate.theta < 80, FORWARD_CURVE1, 20);

	/* 5 */
	//syslog_0(LOG_NOTICE, " 5 (int)p, (int)i, (int)d, (int)turn");
	nxtstate.distance = 0;
	nxtstate.pidParam = PID_LINE;
	BALANCE_PID(nxtstate.distance < 150, FORWARD_LINE, 0);

	/* 6 */
	//syslog_0(LOG_NOTICE, " 6 (int)p, (int)i, (int)d, (int)turn");
	nxtstate.theta = 0;
	nxtstate.pidParam = PID_CURVE;
	BALANCE_PID(nxtstate.theta < 180, FORWARD_CURVE2, 30);

	/* 7 */
	//syslog_0(LOG_NOTICE, " 7 (int)p, (int)i, (int)d, (int)turn");
	nxtstate.distance = 0;
	nxtstate.pidParam = PID_LINE;
	BALANCE_PID(nxtstate.distance < 120, FORWARD_LINE, 0);

	/* 8 */
	//syslog_0(LOG_NOTICE, " 8 (int)p, (int)i, (int)d, (int)turn");
	nxtstate.theta = 0;
	nxtstate.pidParam = PID_CURVE;
	BALANCE_PID(nxtstate.theta > -160, FORWARD_CURVE1, -20);

	/* 9 */
	//syslog_0(LOG_NOTICE, " 9 (int)p, (int)i, (int)d, (int)turn");
	nxtstate.distance = 0;
	nxtstate.pidParam = PID_LINE;
	BALANCE_PID(nxtstate.distance < 120, FORWARD_LINE, 0);

	/* 10 */
	//syslog_0(LOG_NOTICE, " 10 (int)p, (int)i, (int)d, (int)turn");
	nxtstate.theta = 0;
	nxtstate.pidParam = PID_CURVE;
	BALANCE_PID(nxtstate.theta < 70, FORWARD_CURVE1, 20);

	nxtstate.turn_offset = 0;

	nxtstate.pidParam = PID_LINE;
    ///* 1: start */
	//nxtstate.distance = 0;
	//nxtstate.timer = 0;
    //nxtstate.pidParam = PID_BASIC;

	//while(nxtstate.timer < 1000) {
	//	System_update();
    //    balancePid(100);
    //}
    //ecrobot_sound_tone(1000, 200, 50);

    //nxtstate.pidParam = PID_LINE;
    //BALANCE_PID(nxtstate.distance < (L_SLOPE-20), 100.0);

    ///* 2: to previous slope */
	//nxtstate.theta = 0;
    //BALANCE_PID(nxtstate.distance < (L_SLOPE+20), 100.0);

    ///* 3: to slope downing */
    //BALANCE_PID(nxtstate.distance < (L_SLOPE+180), 100.0);

    ///* 4 */
    //nxtstate.pidParam = PID_CURVE;
    //BALANCE_PID(nxtstate.theta < 80, 100.0);

    ///* 5 */
    //nxtstate.distance = 0;
    //nxtstate.pidParam = PID_LINE;
    //BALANCE_PID(nxtstate.distance < 150, 100.0);

    ///* 6 */
	//nxtstate.theta = 0;
    //nxtstate.pidParam = PID_CURVE;
    //BALANCE_PID(nxtstate.theta < 180, 100.0);

    ///* 7 */
    //nxtstate.distance = 0;
    //nxtstate.pidParam = PID_LINE;
    //BALANCE_PID(nxtstate.distance < 140, 100.0);

    ///* 8 */
	//nxtstate.theta = 0;
    //nxtstate.pidParam = PID_CURVE;
    //BALANCE_PID(nxtstate.theta > -160, 70.0);

    ///* 9 */
    //nxtstate.distance = 0;
    //nxtstate.pidParam = PID_LINE;
    //BALANCE_PID(nxtstate.distance < 120, 100.0);

    ///* 10 */
	//nxtstate.theta = 0;
    //nxtstate.pidParam = PID_CURVE;
    //BALANCE_PID(nxtstate.theta < 70, 100.0);
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
	KINITv(((KonohaClassVar*)cNXT)->methodList, new_(MethodArray, 40));
	//KINITv(((KonohaClassVar*)cNXT)->methodList, K_EMPTYARRAY);
	intptr_t MethodData[] = {
		_F(NXT_init), TY_NXT, MN_(NXT_init),
		//_F(NXT_dly), TY_NXT, MN_(NXT_dly),
		_F(NXT_ecrobotIsRunning), TY_NXT, MN_(NXT_ecrobotIsRunning),
		_F(NXT_tailControl), TY_NXT, MN_(NXT_tailControl),
		_F(NXT_manipulateTail), TY_NXT, MN_(NXT_manipulateTail),
		_F(NXT_ecrobotGetGyroSensor), TY_NXT, MN_(NXT_ecrobotGetGyroSensor),
		_F(NXT_ecrobotGetLightSensor), TY_NXT, MN_(NXT_ecrobotGetLightSensor),
		//_F(NXT_waiSem), TY_NXT, MN_(NXT_waiSem),
		//_F(NXT_balanceControl), TY_NXT, MN_(NXT_balanceControl),
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
		_F(NXT_gettimer), TY_NXT, MN_(NXT_gettimer),
		_F(NXT_cleartimer), TY_NXT, MN_(NXT_cleartimer),
		_F(NXT_gettheta), TY_NXT, MN_(NXT_gettheta),
		_F(NXT_cleartheta), TY_NXT, MN_(NXT_cleartheta),
		_F(NXT_getlight), TY_NXT, MN_(NXT_getlight),
		_F(NXT_gettargetLight), TY_NXT, MN_(NXT_gettargetLight),
		_F(NXT_settargetLight), TY_NXT, MN_(NXT_settargetLight),
		_F(NXT_resetMotor), TY_NXT, MN_(NXT_resetMotor),
		_F(NXT_tailwalkWithBottle), TY_NXT, MN_(NXT_tailwalkWithBottle),
		_F(NXT_rotate), TY_NXT, MN_(NXT_rotate),
		_F(NXT_initPID), TY_NXT, MN_(NXT_initPID),
		_F(NXT_basicStage), TY_NXT, MN_(NXT_basicStage),
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
	int FN_z = FN_("z");
	int FN_w = FN_("w");
	intptr_t MethodData[] = {
			//_Public             , _F(NXT_new), TY_NXT, TY_NXT, MN_("new"), 0, 
			_Public|_Static|_Imm, _F(NXT_init), TY_void, TY_NXT, MN_("init"), 0,

			//_Public|_Static|_Imm, _F(NXT_balanceControl), TY_void, TY_NXT, MN_("balanceControl"), 2, TY_int, FN_x, TY_int, FN_y, 
			//_Public|_Static|_Imm, _F(NXT_balanceInit), TY_void, TY_NXT, MN_("balanceInit"), 0,
			//_Public|_Static|_Imm, _F(NXT_dly), TY_void, TY_NXT, MN_("dly"), 1, TY_int, FN_x, 
			_Public|_Static|_Imm, _F(NXT_ecrobotIsRunning), TY_boolean, TY_NXT, MN_("ecrobotIsRunning"), 0, 
			//_Public|_Static|_Imm, _F(NXT_tailControl), TY_void, TY_NXT, MN_("tailControl"), 1, TY_int, FN_x, 
			//_Public|_Static|_Imm, _F(NXT_manipulateTail), TY_void, TY_NXT, MN_("manipulateTail"), 0,
			_Public|_Static|_Imm, _F(NXT_ecrobotGetGyroSensor), TY_int, TY_NXT, MN_("ecrobotGetGyroSensor"), 0,
			_Public|_Static|_Imm, _F(NXT_ecrobotGetLightSensor), TY_int, TY_NXT, MN_("ecrobotGetLightSensor"), 0,
			//_Public|_Static|_Imm, _F(NXT_waiSem), TY_void, TY_NXT, MN_("waiSem"), 0,
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
			_Public|_Static|_Imm, _F(NXT_gettimer), TY_int, TY_NXT, MN_("gettimer"), 0,
			_Public|_Static|_Imm, _F(NXT_cleartimer), TY_void, TY_NXT, MN_("cleartimer"), 0,
			_Public|_Static|_Imm, _F(NXT_gettheta), TY_int, TY_NXT, MN_("gettheta"), 0,
			_Public|_Static|_Imm, _F(NXT_cleartheta), TY_void, TY_NXT, MN_("cleartheta"), 0,
			_Public|_Static|_Imm, _F(NXT_getlight), TY_int, TY_NXT, MN_("getlight"), 0,
			_Public|_Static|_Imm, _F(NXT_gettargetLight), TY_int, TY_NXT, MN_("gettargetLight"), 0,
			_Public|_Static|_Imm, _F(NXT_settargetLight), TY_void, TY_NXT, MN_("settargetLight"), 1, TY_int, FN_x,
			_Public|_Static|_Imm, _F(NXT_resetMotor), TY_void, TY_NXT, MN_("resetMotor"), 0,
			_Public|_Static|_Imm, _F(NXT_tailwalkWithBottle), TY_void, TY_NXT, MN_("tailwalkWithBottle"), 4, 
					TY_boolean, FN_x, TY_int, FN_y, TY_int, FN_z, TY_boolean, FN_w,
			_Public|_Static|_Imm, _F(NXT_rotate), TY_void, TY_NXT, MN_("rotate"), 1, TY_int, FN_x,
			_Public|_Static|_Imm, _F(NXT_initPID), TY_void, TY_NXT, MN_("initPID"), 3, TY_float, FN_x, TY_float, FN_y, TY_float, FN_z,
			_Public|_Static|_Imm, _F(NXT_basicStage), TY_void, TY_NXT, MN_("basicStage"), 0,
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
