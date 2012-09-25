/****************************************************************************
 * Copyright (c) 2012, the Konoha project authors. All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *	this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *	notice, this list of conditions and the following disclaimer in the
 *	documentation and/or other materials provided with the distribution.
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

#include <minikonoha/minikonoha.h>
#include <minikonoha/float.h>
#include <minikonoha/sugar.h>
#include <unistd.h>
#include <stdio.h>
#include <windows.h>
#include <winuser.h>

#define PORT         "COM5:"
#define BUFSIZE      128
#define USLEEP_PARAM 50000
//#define USLEEP_PARAM 2000000

typedef struct bt_buffer_t {
	char buf[BUFSIZE];
	size_t size;
}bt_buffer_t;

static bt_buffer_t *bt_buffer_new(KonohaContext *kctx)
{
	bt_buffer_t *buf = (bt_buffer_t*)KLIB Kmalloc(kctx, sizeof(bt_buffer_t));
	buf->size = 0;
	return buf;
}

static void bt_buffer_free(KonohaContext *kctx, bt_buffer_t *buf)
{
	KLIB Kfree(kctx, buf, sizeof(bt_buffer_t));
}

static void bt_buffer_clear(KonohaContext *kctx, bt_buffer_t *buf)
{
	memset(buf->buf, 0, BUFSIZE);
	buf->size = 0;
}

static void bt_buffer_append(KonohaContext *kctx, bt_buffer_t *buf, void *ptr, size_t size)
{
	memcpy(buf->buf + buf->size, ptr, size);
	buf->size += size;
}

static void sendBuf(KonohaContext *kctx, HANDLE hComm, bt_buffer_t *writebuf)
{
	char buf[BUFSIZE] = {0};
	const char *magicstr = "abcdefghi "; //Sometimes a few bytes of received buffer at front had brewed out, to avoid it.
	size_t strsize = strlen(magicstr);
	DWORD readsize = 0;
	memset(buf, 0, BUFSIZE);
	memcpy(buf, magicstr, strsize);
	memcpy(buf+strsize, writebuf->buf, writebuf->size);
	buf[strsize + writebuf->size] = '\r';
	buf[strsize + writebuf->size + 1] = '\n';
	//printf("%s\n", buf);
	usleep(USLEEP_PARAM);
	while (!WriteFile(hComm, buf, BUFSIZE, &readsize, NULL)) {
		//CloseHandle(hComm);
		printf("cannot send buffer\n");
		KLIB KonohaRuntime_raise(kctx, EXPT_("Cannnot send buffer"), NULL, 0, NULL);
	}
}

static HANDLE hComm = NULL;
static HANDLE bluetooth_connect(KonohaContext *kctx)
{
	if (hComm != NULL) return hComm;
	printf("sendBluetooth\n");
	char port[] = PORT;
	char *portStr = port;
	printf("-\n");
	hComm = CreateFile(
			portStr,
			GENERIC_WRITE | GENERIC_READ,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
	fprintf(stderr, "0");
	COMMTIMEOUTS timeout;
	if (!GetCommTimeouts(hComm, &timeout)) {
		CloseHandle(hComm);
		printf("cannnot get TIMEOUTS\n");
		KLIB KonohaRuntime_raise(kctx, EXPT_("Cannot get TIMEOUTS"), NULL, 0, NULL);
	}
	fprintf(stderr, "1");
	timeout.ReadIntervalTimeout = MAXDWORD;
	timeout.ReadTotalTimeoutMultiplier = 50;
	timeout.ReadTotalTimeoutConstant = 0;
	timeout.WriteTotalTimeoutMultiplier = 50;
	printf("2");
	if (!SetCommTimeouts(hComm, &timeout)) {
		CloseHandle(hComm);
		KLIB KonohaRuntime_raise(kctx, EXPT_("Cannot set TIMEOUTS"), NULL, 0, NULL);
	}
	printf("3");

	if (hComm == INVALID_HANDLE_VALUE) {
		CloseHandle(hComm);
		KLIB KonohaRuntime_raise(kctx, EXPT_("Invalid handle value"), NULL, 0, NULL);
	}
	usleep(USLEEP_PARAM * 5);
	return hComm;
}

static void sendBluetooth(KonohaContext *kctx, kMethod *mtd)
{
	HANDLE hComm = bluetooth_connect(kctx);
	bt_buffer_t *writebuf = bt_buffer_new(kctx);
	int8_t magicValue = -1;
	int32_t opsize = 0;
	int16_t cid = mtd->typeId;
	int16_t mn = mtd->mn;
	printf("cid %d mn %d\n", cid, mtd->mn);

	int16_t opcode_count[KOPCODE_MAX] = {0};
	while (mtd->pc_start[opsize].opcode != OPCODE_RET) {
		opcode_count[mtd->pc_start[opsize].opcode]++;
		opsize++;
	}
	opsize++; // OPCODE_RET
	bt_buffer_append(kctx, writebuf, &magicValue, sizeof(int8_t));
	bt_buffer_append(kctx, writebuf, &opsize, sizeof(int32_t));
	bt_buffer_append(kctx, writebuf, &cid, sizeof(int16_t));
	bt_buffer_append(kctx, writebuf, &mn, sizeof(int16_t));
	size_t j;
	for (j = 0; j < KOPCODE_MAX; j++) {
		//printf("opcode%d count: %d\n", j, opcode_count[j]);
		bt_buffer_append(kctx, writebuf, opcode_count + j, sizeof(int16_t));
	}
	sendBuf(kctx, hComm, writebuf);
	//bt_buffer_clear(kctx, writebuf);
	//usleep(USLEEP_PARAM);
	//sendBuf(kctx, hComm, writebuf);
	VirtualMachineInstruction *pc = NULL;
	int i = 0;
	printf("opsize %d\n", opsize);
	for (; i < opsize; i++) {
		bt_buffer_clear(kctx, writebuf);
		pc = mtd->pc_start + i;
		bt_buffer_append(kctx, writebuf, &pc->opcode, sizeof(int8_t));
		printf("\nop%d\n", i);
		switch (pc->opcode) {
		case OPCODE_NSET: {
			OPNSET *op = (OPNSET*)pc;
			printf("nset\n");
			int8_t a = op->a;
			int32_t n = op->n;
			int16_t ty = op->ty->typeId;
			bt_buffer_append(kctx, writebuf, &a, sizeof(int8_t));
			bt_buffer_append(kctx, writebuf, &ty, sizeof(int16_t));
			switch(ty) {
			case TY_boolean:
			case TY_int: {
				printf("int %d\n", n);
				bt_buffer_append(kctx, writebuf, &n, sizeof(int32_t));
				break;
			}
			case TY_String: {
				kString *str = (kString*)op->n;
				printf("string %s\n", str->text);
				int8_t length = strlen(str->text);
				bt_buffer_append(kctx, writebuf, &length, sizeof(int8_t));
				bt_buffer_append(kctx, writebuf, str->text, length+1);
				break;
			}
			case TY_Method: {
				kMethod *mtd = (kMethod*)op->n;
				int16_t cid = mtd->typeId;
				int16_t mn = SYM_UNMASK(mtd->mn);
				printf("method %s\n", SYM_t(SYM_UNMASK(mtd->mn)));
				printf("cid %d, mn %d\n", cid, mn);
				bt_buffer_append(kctx, writebuf, &cid, sizeof(int16_t));
				bt_buffer_append(kctx, writebuf, &(mn), sizeof(int16_t));
				break;
			}
			default: {
				if (KonohaContext_getFloatModule(kctx) != NULL && pc->opcode == TY_float) {
					bt_buffer_append(kctx, writebuf, &n, sizeof(int32_t));
				}
			}
			}
			break;
		}
		case OPCODE_NMOV: {
			OPNMOV *op = (OPNMOV*)pc;
			printf("NMOV\n");
			int8_t a = op->a;
			int8_t b = op->b;
			bt_buffer_append(kctx, writebuf, &a, sizeof(int8_t));
			bt_buffer_append(kctx, writebuf, &b, sizeof(int8_t));
			break;
		}
		case OPCODE_CALL: {
			OPCALL *op = (OPCALL*)pc;
			printf("call\n");
			int8_t thisidx = op->thisidx;
			int8_t espshift = op->espshift;
			bt_buffer_append(kctx, writebuf, &thisidx, sizeof(int8_t));
			bt_buffer_append(kctx, writebuf, &espshift, sizeof(int8_t));
			break;
		}
		case OPCODE_RET: {
			OPRET *op = (OPRET*)pc;
			printf("RET\n");
			break;
		}
		case OPCODE_JMP: {
			OPJMP *op = (OPJMP*)pc;
			printf("JMP\n");
			int16_t jumppc = op->jumppc - mtd->pc_start;
			printf("jumppc %d\n", jumppc);
			bt_buffer_append(kctx, writebuf, &jumppc, sizeof(int16_t));
			break;
		}
		case OPCODE_JMPF: {
			OPJMPF *op = (OPJMPF*)pc;
			printf("JMPF\n");
			int16_t jumppc = op->jumppc - mtd->pc_start;
			printf("jumppc %d\n", jumppc);
			int8_t a = op->a;
			bt_buffer_append(kctx, writebuf, &jumppc, sizeof(int16_t));
			bt_buffer_append(kctx, writebuf, &a, sizeof(int8_t));
			break;
		}
		case OPCODE_BNOT: {
			OPBNOT *op = (OPBNOT*)pc;
			printf("BNOT\n");
			int8_t c = op->c;
			int8_t a = op->a;
			bt_buffer_append(kctx, writebuf, &c, sizeof(int8_t));
			bt_buffer_append(kctx, writebuf, &a, sizeof(int8_t));
			break;
		}
		default: {
					 printf("default opcode: %d\n", pc->opcode);
			//int8_t terminator = 0xff;
			//bt_buffer_append(kctx, writebuf, &terminator, sizeof(int8_t));
			break;
		}
		}
		sendBuf(kctx, hComm, writebuf);
	}
	printf("8");
	bt_buffer_free(kctx, writebuf);
}

static void bt_close(KonohaContext *kctx)
{
	printf("bt_close\n");
	bt_buffer_t writebuf;
	bt_buffer_clear(kctx, &writebuf);
	int8_t i = 0;
	bt_buffer_append(kctx, &writebuf, &i, sizeof(int8_t));
	sendBuf(kctx, hComm, &writebuf);
	printf("bt_close end\n");
	CloseHandle(hComm);
}
