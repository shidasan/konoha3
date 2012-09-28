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

#ifndef _NXT_H_
#define _NXT_H_
#include "kernel_id.h"
#include "ecrobot_base.h"
#include "ecrobot_interface.h"

/* 下記のパラメータはセンサ個体/環境に合わせてチューニングする必要があります */
#define WHITE               500 /* 白色の光センサ値 */
#define BLACK		        700 /* 黒色の光センサ値 */
#define STOPWAIT            10	/* 停止までの時間(*40ms) */

#define TAIL_ANGLE_STAND_UP 105 /* 完全停止時の角度[度] */
#define TAIL_ANGLE_DRIVE      0 /* バランス走行時の角度[度] */
#define P_GAIN             32.0F //2.5F /* 完全停止用モータ制御比例係数 */
#define PWM_ABS_MAX          60 /* 完全停止用モータ制御PWM絶対最大値 */

U16 getGyroOffset();
int getSonarValue();
int getWhiteLight();
void tail_control(signed int angle);
void TDBG_i(const char *key, int value);
void TDBG_s(const char *key);
void TDBG_abort(const char *msg);
#endif //_NXT_H_
