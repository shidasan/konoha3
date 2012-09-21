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

#include "tinykonoha.h"
#include "tinyvm_gen.h"
#include "tinyvm.h"
#include "constant.h"

static KMETHOD MethodFunc_runVirtualMachine(KonohaContext *kctx, KonohaStack *sfp)
{
	kMethod *mtd = sfp[K_MTDIDX].mtdNC;
	DBG_ASSERT(IS_Method(mtd));
	KonohaVirtualMachine_run(kctx, sfp, mtd->pc_start);
}

static char *receive_buf(unsigned char *buf)
{
	int er;
	//dly_tsk(500);
	while ((er = bluetooth_receive(CONSOLE_PORTID, buf)) <= 0 || er < 97 || er > 107) {
		dly_tsk(3);
	}
	if (er < 97 || er > 107) {
		TDBG_abort("invalid er");
	}
	int pos = 0;
	for (; buf[pos] != ' '; pos++) ;
	pos++; //eat ' '
	return buf + pos;
}

static void undefCode(KonohaContext *kctx, char *buf, VirtualMachineInstruction *pc, int pos)
{
	OPNOP *op = (OPNOP*)(pc + pos);
	op->opcode = OPCODE_NOP;
	//TDBG_i("undefined", buf[0]);
}
void CT_addMethod(KonohaContext *kctx, KonohaClassVar *ct, kMethod *mtd);
static void genNSET(KonohaContext *kctx, char *buf, VirtualMachineInstruction *pc, int pos)
{
	OPNSET *op = (OPNSET*)(pc + pos);
	int8_t opcode = buf[0]; buf++; //eat opcode
	op->a = buf[0]; buf++; //eat a
	int16_t ty = (int16_t)buf[0]; buf+=2; //eat ty
	switch(ty) {
	case TY_float:
	case TY_Int: {
		op->n = (int32_t)buf[0];
		//TDBG_i("ivalue", op->n);
		break;
	}
	case TY_String: {
		size_t strsize = buf[0]; buf++; //eat strsize
		//TDBG_i("strsize", strsize);
		char *str = (char *)KLIB Kmalloc(kctx, strsize+1);
		memcpy(str, buf, strsize);
		str[strsize] = '\0';
		kStringVar *string = (kStringVar*)KLIB new_kObject(kctx, CT_(TY_String), (uintptr_t)str);
		op->n = (int32_t)string;
		break;
	}
	case TY_Method: {
		int16_t cid = (int16_t)buf[0]; buf+=2; //eat cid
		int16_t mn = (int16_t)buf[0]; buf+=2; //eat mn
		//TDBG_i("cid", cid);
		//TDBG_i("mn", mn);
		kMethod *mtd = KLIB kNameSpace_getMethodNULL(kctx, NULL, cid, mn, 0, 0);
		if (mtd != NULL) {
			op->n = (int32_t)mtd;
		} else {
			if (CT_(cid) != NULL) {
				uintptr_t flag = kMethod_Static|kMethod_Public;
				kMethod *mtd = KLIB new_kMethod(kctx, flag, cid, mn, NULL);
				op->n = (int32_t)mtd;
				CT_addMethod(kctx, (KonohaClassVar*)CT_(cid), mtd);
			} else {
				op->n = (int32_t)kctx->share->constNull;
			}
		}
		//TDBG_i("method", (int32_t)mtd);
		break;
	}
	default: {
		//TDBG_i("undefined type", ty);
		op->n = (int32_t)kctx->share->constNull;
		break;
	}
	}
}
static void genNMOV(KonohaContext *kctx, char *buf, VirtualMachineInstruction *pc, int pos)
{
	OPNMOV *op = (OPNMOV*)(pc + pos);
	int8_t opcode = buf[0]; buf++; //eat opcode
	op->a = buf[0]; buf++;
	op->b = buf[0]; buf++;
}
static void genCALL(KonohaContext *kctx, char *buf, VirtualMachineInstruction *pc, int pos)
{
	OPCALL *op = (OPCALL*)(pc + pos);
	buf++; //eat opcode
	op->thisidx = buf[0]; buf++;//eat thisidx
	op->espshift = buf[0]; buf++;//eat espshift
	op->tyo = kctx->share->constNull;
	//TDBG_i("CALL", buf[0]);
}
static void genRET(KonohaContext *kctx, char *buf, VirtualMachineInstruction *pc, int pos)
{
	//TDBG_i("RET", buf[0]);
}
static void genJMP(KonohaContext *kctx, char *buf, VirtualMachineInstruction *pc, int pos)
{
	OPJMP *op = (OPJMP*)(pc + pos);
	buf++; //eat opcode
	op->jumppc = (int16_t)buf[0]; buf+=2; //eat jumppc
}
static void genJMPF(KonohaContext *kctx, char *buf, VirtualMachineInstruction *pc, int pos)
{
	OPJMPF *op = (OPJMPF*)(pc + pos);
	buf++; //eat opcode
	op->jumppc = (int16_t)buf[0]; buf+=2; //eat jumppc
	op->a = buf[0]; buf++; //eat a
}

typedef void (*genByteCode)(KonohaContext *, char *, VirtualMachineInstruction *pc, int pos);
genByteCode genCode[] = {NULL, NULL, NULL, NULL,
	                     genNSET, genNMOV, NULL, NULL, 
						 NULL, NULL, NULL, genCALL,
						 genRET, NULL, NULL, genJMP,
						 genJMPF, NULL, NULL, NULL,
						 NULL, NULL, NULL};

static void loadByteCode(KonohaContext *kctx)
{
	//TDBG_s("load");
	int i = 0;
	char buf[128] = {0};
	//TDBG_s("hi");
	//dly_tsk(1999);
	do {
		bluetooth_connect();
		dly_tsk(1);
	} while (bluetooth_get_connect_state(CONSOLE_PORTID) == 0);
	int8_t magicValue = 0;

	/* method loading loop*/
	int counter = 0;
	while (1) {
		counter++;
		char *data = receive_buf(buf);
		magicValue = data[0];
		data++;// eat magicValue
		if (magicValue != -1) {
			//TDBG_i("magicValue", magicValue);
			break;
		}
		int opsize = (int32_t)*data; data += 4;//eat opsize
		int16_t cid = (int16_t)*data; data += 2;//eat cid
		int16_t mn = (int16_t)*data; data += 2;//eat cid
		//TDBG_i("opsize", opsize);
		
		/* bytecode loading loop */
		VirtualMachineInstruction *pc = (VirtualMachineInstruction*)KLIB Kmalloc(kctx, sizeof(VirtualMachineInstruction) * opsize);
		for (i = 0; i < opsize; i++) {
			data = receive_buf(buf);
			int8_t opcode = data[0];
			pc[i].opcode = opcode;
			if (genCode[opcode] != NULL) {
				genCode[opcode](kctx, data, pc, i);
			} else {
				undefCode(kctx, data, pc, i);
			}
		}
		//TDBG_i("cid", cid);
		//TDBG_i("mn", mn);
		if (cid == 0 && mn == 0) {
			OPEXIT opEXIT = {OPCODE_EXIT};
			krbp_t *rbp = (krbp_t*)kctx->esp;
			rbp[K_PCIDX2].pc = (VirtualMachineInstruction*)&opEXIT;
			rbp[K_SHIFTIDX2].shift = 0;
			//TDBG_s("toplevel");
			//KonohaVirtualMachine_run(kctx, kctx->esp, pc);
			//dly_tsk(1000);
			//TDBG_s("toplevel end");
			//KLIB Kfree(kctx, pc, sizeof(VirtualMachineInstruction) * opsize);
			KLIB kArray_add(kctx, kctx->share->topLevelMethodList, pc);
		} else {
			//TDBG_s("function");
			uintptr_t flag = kMethod_Static|kMethod_Public;
			kMethodVar *mtd = (kMethodVar*)KLIB new_kMethod(kctx, flag, cid, mn, MethodFunc_runVirtualMachine);
			mtd->pc_start = pc;
			CT_addMethod(kctx, (KonohaClassVar*)CT_(cid), (kMethod*)mtd);
		}
	}
}
