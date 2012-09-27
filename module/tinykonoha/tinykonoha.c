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

#ifdef K_USING_TOPPERS
void TDBG_i(const char *key, int value)
{
	display_clear(0);
	display_goto_xy(0, 0);
	display_string(key);
	display_goto_xy(0, 1);
	display_int(value, 1);
	display_update();
	//dly_tsk(500);
}
void TDBG_s(const char *key)
{
	display_clear(0);
	display_goto_xy(0, 0);
	display_string(key);
	display_update();
	//dly_tsk(500);
}
void TDBG_abort(const char *msg)
{
	display_clear(0);
	display_goto_xy(0, 0);
	display_string("abort");
	display_goto_xy(0, 1);
	display_string(msg);
	display_update();
	while (1) {
		dly_tsk(1000U);
	}
}
#include "tinykonoha_config.h"
#include "kernel_id.h"
#include "ecrobot_base.h"
#include "ecrobot_interface.h"
#include "balancer.h"
#include "loader.h"
#include "nxt.h"
#else

#define TDBG_i(KEY, VALUE)						\
	printf("%s %d\n", KEY, VALUE)               \

#define TDBG_s(KEY)								\
	printf("%s\n", KEY)                         \

#define TDBG_abort(MSG)							\
	printf("%s\n", MSG);                        \
    assert(0)                                   \

#include "stdio.h"
#endif

#include "tinykonoha.h"
#include "allocate.h"
#include "../tinyvm/tinyvm_gen.h"
#include "bytecode.h"
#include "../msgc/msgc.c"
#include "../../src/konoha/methods.h"
#include "../../include/minikonoha/sugar.h"
#include "datatype.h"

#define K_STACK_SIZE 65

//nxt_state_t *getnxtstate() {
//	return &nxtstate;
//}

static void KRUNTIME_reftrace(KonohaContext *kctx, KonohaContext *ctx)
{
	//TDBG_abort("runtime trace");
	//KonohaStack *sp = ctx->stack->stack;
	//BEGIN_REFTRACE((kctx->esp - sp)+1);
	//while(sp < ctx->esp) {
	//	KREFTRACEv(sp[0].o);
	//	sp++;
	//}
	//KREFTRACEv(ctx->stack->gcstack);
	//END_REFTRACE();
}

static void kshare_reftrace(KonohaContext *kctx, KonohaContext *ctx)
{
	KonohaRuntime *share = ctx->share;
	KonohaClass **cts = (KonohaClass**)kctx->share->classTable.classItems;
	size_t i, size = kctx->share->classTable.bytesize/sizeof(struct _kclass*);
	for(i = 0; i < size; i++) {
		KonohaClass *ct = cts[i];
		{
			BEGIN_REFTRACE(1);
			//KREFTRACEv(ct->cparam);
			KREFTRACEn(ct->methodList);
			//KREFTRACEn(ct->shortNameNULL);
			//KREFTRACEn(ct->nulvalNUL);
			END_REFTRACE();
		}
//		if (ct->constNameMapSO) kmap_reftrace(ct->constNameMapSO, keyval_reftrace);
		//if (ct->constPoolMapNO) kmap_reftrace(ct->constPoolMapNO, val_reftrace);
	}

	BEGIN_REFTRACE(2);
	KREFTRACEn(share->constNull);
	KREFTRACEn(share->constData);
	//KREFTRACEv(share->constTrue);
	//KREFTRACEv(share->constFalse);
	//KREFTRACEv(share->emptyString);
	KREFTRACEn(share->emptyArray);

	//KREFTRACEv(share->fileidList);
	//KREFTRACEv(share->packList);
	//KREFTRACEv(share->symbolList);
	//KREFTRACEv(share->unameList);
	//KREFTRACEv(share->paramList);
	//KREFTRACEv(share->paramdomList);
	END_REFTRACE();
}

static void KonohaContext_reftrace(KonohaContext *kctx, KonohaContext *ctx)
{
	size_t i;
	kshare_reftrace(kctx, ctx);
	for(i = 0; i < KonohaModule_MAXSIZE; i++) {
		KonohaModule *p = ctx->modshare[i];
		if(p != NULL && p->reftrace != NULL) {
			p->reftrace(kctx, p);
		}
	}
	KRUNTIME_reftrace(kctx, ctx);
	for(i = 0; i < KonohaModule_MAXSIZE; i++) {
		KonohaModuleContext *p = ctx->modlocal[i];
		if(p != NULL && p->reftrace != NULL) {
			p->reftrace(kctx, p);
		}
	}
}

void KonohaContext_reftraceAll(KonohaContext *kctx)
{
	KonohaContext_reftrace(kctx, (KonohaContext*)kctx);
}

void KONOHA_freeObjectField(KonohaContext *kctx, kObjectVar *o)
{
	KonohaClass *ct = O_ct(o);
	//if(o->h.kvproto->bytemax > 0) {
	//	KUtilsGrowingArray *p = o->h.kvproto;
	//	KFREE(p->bytebuf, p->bytemax);
	//	KFREE(p, sizeof(KUtilsGrowingArray));
	//	o->h.kvproto = kvproto_null();
	//}
	ct->free(kctx, o);
}

void KONOHA_reftraceObject(KonohaContext *kctx, kObject *o)
{
	KonohaClass *ct = O_ct(o);
	//if(o->h.kvproto->bytemax > 0) {
	//	size_t i, pmax = o->h.kvproto->bytemax / sizeof(kvs_t);
	//	kvs_t *d = o->h.kvproto->kvs;
	//	BEGIN_REFTRACE(pmax);
	//	for(i = 0; i < pmax; i++) {
	//		if(FN_isBOXED(d->key)) {
	//			KREFTRACEv(d->oval);
	//		}
	//		d++;
	//	}
	//	END_REFTRACE();
	//}
	ct->reftrace(kctx, o);
}

kObjectVar** KONOHA_reftail(KonohaContext *kctx, size_t size)
{
	KonohaStackRuntimeVar *stack = kctx->stack;
	size_t ref_size = stack->reftail - stack->ref.refhead;
	if(stack->ref.bytemax/sizeof(void*) < size + ref_size) {
		KLIB Karray_expand(kctx, &stack->ref, (size + ref_size) * sizeof(kObject*));
		stack->reftail = stack->ref.refhead + ref_size;
	}
	kObjectVar **reftail = stack->reftail;
	stack->reftail = NULL;
	return reftail;
}

static kbool_t KRUNTIME_setModule(KonohaContext *kctx, int x, KonohaModule *d, kfileline_t pline)
{
	if (kctx->modshare[x] == NULL) {
		kctx->modshare[x] = d;
		return 1;
	} else {
		return 0;
	}
}

static void Kreport(KonohaContext *kctx, int level, const char *msg)
{
	/* TODO */
}

static void Kreportf(KonohaContext *kctx, kinfotag_t level, kfileline_t pline, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	const char *str = va_arg(ap, const char*);
	//TDBG_s("reportf");
	//dly_tsk(1000);
	//TDBG_s(fmt);
	//dly_tsk(1000);
	if (fmt[0] == '%' && fmt[1] == 's') {
		TDBG_s(str);
		dly_tsk(1000);
	}
}

void CT_addMethod(KonohaContext *kctx, KonohaClassVar *ct, kMethod *mtd)
{
	if(ct->methodList == K_EMPTYARRAY) {
		KINITv(((KonohaClassVar*)ct)->methodList, new_(MethodArray, 8));
	}
	KLIB kArray_add(kctx, ct->methodList, mtd);
}

static void KonohaSpace_addMethod(KonohaContext *kctx, kNameSpace *ks, kMethod *mtd)
{
	if(ks->methodList == K_EMPTYARRAY) {
		KINITv(((kNameSpaceVar*)ks)->methodList, new_(MethodArray, 8));
	}
	KLIB kArray_add(kctx, ks->methodList, mtd);
}

static void kNameSpace_loadMethodData(KonohaContext *kctx, kNameSpace *ks, intptr_t *data)
{
	static int mn_count = 0;
	intptr_t *d = data;
	while(d[0] != -1) {
		uintptr_t flag = kMethod_Static|kMethod_Public|kMethod_NativeMethod;
		MethodFunc f = (MethodFunc)d[0];
		ktype_t rtype = 0;
		ktype_t cid = (ktype_t)d[1];
		mn_count++;
		kmethodn_t mn = (kmethodn_t)d[2];
		size_t psize = 0;
		//kparam_t p[1];
		d += 3;
		kMethod *mtd = KLIB new_kMethod(kctx, flag, cid, mn, f);
		//kMethod_setParam(mtd, rtype, psize, p);
		if(ks == NULL || Method_isPublic(mtd)) {
			CT_addMethod(kctx, (KonohaClassVar*)CT_(cid), mtd);
		} else {
			KonohaSpace_addMethod(kctx, ks, mtd);
		}
	}
}

static void karray_init(KonohaContext *kctx, KUtilsGrowingArray *m, size_t bytemax)
{
	m->bytesize = 0;
	m->bytemax  = bytemax;
	m->bytebuf = (char*)KCALLOC(bytemax, 1);
}

static void karray_resize(KonohaContext *kctx, KUtilsGrowingArray *m, size_t newsize)
{
	size_t oldsize = m->bytemax;
	char *newbody = (char*)KMALLOC(newsize);
	if(oldsize < newsize) {
		memcpy(newbody, m->bytebuf, oldsize);
		bzero(newbody + oldsize, newsize - oldsize);
	}
	else {
		memcpy(newbody, m->bytebuf, newsize);
	}
	KFREE(m->bytebuf, oldsize);
	m->bytebuf = newbody;
	m->bytemax = newsize;
}

static void karray_expand(KonohaContext *kctx, KUtilsGrowingArray *m, size_t minsize)
{
	if(m->bytemax == 0) {
		if(minsize > 0) karray_init(kctx, m, minsize);
	}
	else {
		size_t oldsize = m->bytemax, newsize = oldsize * 2;
		if(minsize > newsize) newsize = minsize;
		karray_resize(kctx, m, newsize);
	}
}

static void karray_free(KonohaContext *kctx, KUtilsGrowingArray *m)
{
	if(m->bytemax > 0) {
		KFREE(m->bytebuf, m->bytemax);
		m->bytebuf = NULL;
		m->bytesize = 0;
		m->bytemax  = 0;
	}
}

static void klib2_init(KonohaLibVar *l)
{
	l->Karray_init       = karray_init;
	l->Karray_resize     = karray_resize;
	l->Karray_expand     = karray_expand;
	l->Karray_free       = karray_free;
	l->KonohaRuntime_setModule        = KRUNTIME_setModule;
	//l->Kreport           = Kreport;
	l->Kreportf          = Kreportf;
	l->kNameSpace_loadMethodData = kNameSpace_loadMethodData;
}

static void KRUNTIME_init(KonohaContextVar *kctx, KonohaContextVar *ctx, size_t stacksize)
{
	size_t i;
	KonohaStackRuntimeVar *base = (KonohaStackRuntimeVar*)KCALLOC(sizeof(KonohaStackRuntimeVar), 1);
	base->stacksize = stacksize;
	base->stack = (KonohaStack*)KCALLOC(sizeof(KonohaStack), stacksize);
	assert(stacksize>64);
	base->stack_uplimit = base->stack + (stacksize);
	for(i = 0; i < stacksize; i++) {
		KINITv(base->stack[i].o, K_NULL);
	}
	//KINITv(base->gcstack, new_(Array, K_PAGESIZE/sizeof(void*)));
	//KINITv(base->gcstack, new_(Array, 5));
	//KARRAY_INIT(&base->cwb, K_PAGESIZE * 4);
	KLIB Karray_init(kctx, &base->ref, 128);
	base->reftail = base->ref.refhead;
	kctx->esp = base->stack + 4;
	kctx->stack = base;
}

static void KRUNTIME_free(KonohaContext *kctx, KonohaContext *ctx)
{
	KLIB Karray_free(kctx, &kctx->stack->cwb);
	KLIB Karray_free(kctx, &kctx->stack->ref);
	KFREE(kctx->stack->stack, sizeof(KonohaStack) * ctx->stack->stacksize);
	KFREE(kctx->stack, sizeof(KonohaStackRuntimeVar));
}

static KonohaContext *new_context(size_t stacksize)
{
	heap_init();
	static KonohaContextVar kctx;
	static KonohaModule *modshare[KonohaModule_MAXSIZE] = {0};
	static KonohaModuleContext *modlocal[KonohaModule_MAXSIZE] = {0};
	static KonohaLibVar lib2 = {0};
	klib2_init(&lib2);
	kctx.modshare = modshare;
	kctx.modlocal = modlocal;
	kctx.klib = &lib2;
	MODGC_init(&kctx, &kctx);
	KCLASSTABLE_init(&kctx);
	KRUNTIME_init(&kctx, &kctx, stacksize);
	KCLASSTABLE_loadMethod(&kctx);
	return &kctx;
}

#ifdef K_USING_TOPPERS

static char mstate;				/* 走行体の状態 */
static char keystate;			/* タッチセンサーの状態 */
static U16 gyro_offset_value;
static int sonar_value;
static int whitelight;

U16 getGyroOffset()
{
	return gyro_offset_value;
}

int getSonarValue()
{
	return sonar_value;
}

int getWhiteLight()
{
	return whitelight;
}

void tail_control(signed int angle)
{
	float pwm = (float)(angle - nxt_motor_get_count(NXT_PORT_A))*P_GAIN; /* 比例制御 */
	/* PWM出力飽和処理 */
	if(pwm > PWM_ABS_MAX)
		pwm = PWM_ABS_MAX;
	else if(pwm < -PWM_ABS_MAX)
		pwm = -PWM_ABS_MAX;
	nxt_motor_set_speed(NXT_PORT_A, (signed char)pwm, 1);
}

int ecrobotIsRunning()
{
	return mstate < MPREWAIT;
}

static void execTopLevelExpression(KonohaContext *kctx)
{
	kArray *array = kctx->share->topLevelMethodList;
	size_t i, size = kArray_size(array);
	//TDBG_i("size", size);
	for (i = 4; i < size; i++) {
		OPEXIT opEXIT = {OPCODE_EXIT};
		krbp_t *rbp = (krbp_t*)kctx->esp;
		rbp[K_PCIDX2].pc = (VirtualMachineInstruction*)&opEXIT;
		rbp[K_SHIFTIDX2].shift = 0;
		VirtualMachineInstruction *pc = (VirtualMachineInstruction*)array->objectItems[i];
		//TDBG_s("run"); dly_tsk(1000);
		KonohaVirtualMachine_run(kctx, kctx->esp, pc);
	}
}

void manipulate_tail()
{
	if (mstate == MRUNNING) {
		tail_control(TAIL_ANGLE_DRIVE);
	} else if (mstate == MSTOP1) {
		nxt_motor_set_count(NXT_PORT_A, 0);
		mstate = MSTOP2;
	} else {
		tail_control(TAIL_ANGLE_STAND_UP);
	}
}

void cyc0(VP_INT exinf)
{
	isig_sem(EVT_SEM);
}
void TaskMain(VP_INT exinf)
{
	opcode_check();
	struct KonohaContext *kctx = (struct KonohaContext *)new_context(K_STACK_SIZE);
	loadByteCode((KonohaContext*)kctx);

	mstate = MWAIT;
	ecrobot_set_light_sensor_active(NXT_PORT_S3);
	while (mstate != MRUNNING) {
		//TDBG_i("invoke ptr", (int32_t)MethodFunc_runVirtualMachine);
		tail_control(TAIL_ANGLE_STAND_UP);
		gyro_offset_value = ecrobot_get_gyro_sensor(NXT_PORT_S1);
		//TDBG_i("gyro_offset", gyro_offset);
		dly_tsk(1);
	}
	TDBG_s("press enter");
	check_enter();
	balance_init();
	nxt_motor_set_count(NXT_PORT_C, 0);
	nxt_motor_set_count(NXT_PORT_B, 0);
	sta_cyc(CYC0);
	//TDBG_s("toplevel");
	//dly_tsk(1000);
	execTopLevelExpression((KonohaContext*)kctx);
	//TDBG_s("end toplevel");
	//dly_tsk(1000);
	//act_tsk(TASK0);
}

void TaskDisp(VP_INT exinf)
{
	T_SERIAL_RPOR rpor;
	UB buf[4];
	int wtime = 0;
	char key;
	ER ercd;

	int button_state = 0;

	vmsk_log(LOG_UPTO(LOG_INFO), LOG_UPTO(LOG_EMERG));
	syscall(serial_ctl_por(CONSOLE_PORTID,	(IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV)));
	ecrobot_init_nxtstate();
	ecrobot_init_sensors();
	ecrobot_init_sonar_sensor(NXT_PORT_S2); /* 超音波センサ(I2C通信)を初期化 */
	display_status_bar();
	mstate = MINIT;
	keystate = ecrobot_get_touch_sensor(NXT_PORT_S4);
	nxt_motor_set_count(NXT_PORT_A, 0);		/* 完全停止用モータエンコーダリセット */
	act_tsk(TASK0);
	//mstate = MWAIT;
	//wtime = STOPWAIT;
	while(1){
		ecrobot_poll_nxtstate();
		sonar_value = ecrobot_get_sonar_sensor(NXT_PORT_S2);
		//ercd = serial_ref_por(CONSOLE_PORTID, &rpor);
		//if(ercd == E_OK && rpor.reacnt){
		//	serial_rea_dat(CONSOLE_PORTID, buf, 1);
		//	if(buf[0] == 'g' && mstate == MWAIT)
		//		mstate = MRUNNING;
		//	else if(buf[0] == 's' && mstate == MRUNNING){
		//		mstate = MSTOP1;
		//		wtime = STOPWAIT;
		//	}
		//}
		key = ecrobot_get_touch_sensor(NXT_PORT_S4);
		if(key != keystate){	/* KEYセンサーの検知 */
			if (button_state == 0) {
				whitelight = ecrobot_get_light_sensor(NXT_PORT_S3);
				key = 0;
				button_state = 1;
				ecrobot_sound_tone(1000, 200, 50);
				dly_tsk(1000U);
			} else if (button_state == 1) {
				button_state = 2;
				dly_tsk(1000U);
			} else if (button_state == 2) {
				if (mstate == MWAIT) {
					mstate = MRUNNING;
				} else if (mstate == MRUNNING) {
					mstate = MSTOP1;
					wtime = STOPWAIT;
				}
			}
			keystate = key;
		}
		if(wtime > 0){
			if(--wtime <= 0 && mstate >= MSTOP1 && mstate < MPREWAIT){
				if(++mstate != MPREWAIT)
					wtime = 1;
			}
		}
		//ecrobot_status_monitor("sample JSP"); /* LCD display */
		dly_tsk(40U); /* 40msec wait */
	}
}
#else
int main(int argc, char **args)
{
	opcode_check();
	KonohaContext *kctx = NULL;
	kctx = new_context(K_STACK_SIZE);
	//loadByteCode(kctx);
	//execTopLevelExpression(kctx);
	return 0;
}
#endif
