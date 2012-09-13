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

static char *receive_buf(unsigned char *buf)
{
	int er;
	while ((er = bluetooth_receive(CONSOLE_PORTID, buf)) <= 0) {
		dly_tsk(2);
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
	TDBG_i("undefined", buf[0]);
}
static void genNSET(KonohaContext *kctx, char *buf, VirtualMachineInstruction *pc, int pos)
{
	OPNSET *op = (OPNSET*)(pc + pos);
	int8_t opcode = buf[0]; buf++; //eat opcode
	op->a = buf[0]; buf++; //eat a
	int16_t ty = (int16_t)buf[0]; buf+=2; //eat ty
	switch(ty) {
	case TY_Int: {
		op->n = (int32_t)buf[0];
		TDBG_i("ivalue", op->n);
		break;
	}
	case TY_String: {
		size_t strsize = buf[0]; buf++; //eat strsize
		TDBG_i("strsize", strsize);
		char *str = (char *)KLIB Kmalloc(kctx, strsize+1);
		memcpy(str, buf, strsize);
		str[strsize] = '\0';
		kStringVar *string = (kStringVar*)KLIB new_kObject(kctx, CT_(TY_String), (uintptr_t)str);
		op->n = (int32_t)string;
		TDBG_s(str);
		break;
	}
	}
}
static void genNMOV(KonohaContext *kctx, char *buf, VirtualMachineInstruction *pc, int pos)
{
	TDBG_i("NMOV", buf[0]);
}
static void genCALL(KonohaContext *kctx, char *buf, VirtualMachineInstruction *pc, int pos)
{
	TDBG_i("CALL", buf[0]);
}
static void genRET(KonohaContext *kctx, char *buf, VirtualMachineInstruction *pc, int pos)
{
	TDBG_i("RET", buf[0]);
}
static void genJMP(KonohaContext *kctx, char *buf, VirtualMachineInstruction *pc, int pos)
{
	TDBG_i("JMP", buf[0]);
}
static void genJMPF(KonohaContext *kctx, char *buf, VirtualMachineInstruction *pc, int pos)
{
	TDBG_i("JMPF", buf[0]);
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
	TDBG_s("load");
	int i = 0;
	char buf[128] = {0};
	do {
		bluetooth_connect();
	} while (bluetooth_get_connect_state(CONSOLE_PORTID) == 0);
	int8_t magicValue = 0;

	/* method loading loop*/
	while (1) {
		char *data = receive_buf(buf);
		magicValue = data[0];
		data++;// eat magicValue
		if (magicValue != -1) {
			TDBG_s("method loop end");
			break;
		}
		int opsize = (int32_t)*data; data += 4;//eat opsize
		int16_t cid = (int16_t)*data; data += 2;//eat cid
		int16_t mn = (int16_t)*data; data += 2;//eat cid
		TDBG_i("opsize", opsize);
		
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
	}
	TDBG_abort("load end");
}
