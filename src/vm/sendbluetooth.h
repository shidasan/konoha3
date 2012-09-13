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

#include <unistd.h>
#include <windows.h>
#include <winuser.h>

#define PORT         "COM5:"
#define BUFSIZE      128
#define USLEEP_PARAM 2000000

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
	memcpy(buf, magicstr, strsize);
	memcpy(buf+strsize, writebuf->buf, writebuf->size);
	buf[strsize + writebuf->size] = '\r';
	buf[strsize + writebuf->size + 1] = '\n';
	if (!WriteFile(hComm, buf, BUFSIZE, &readsize, NULL)) {
		CloseHandle(hComm);
		printf("cannot send buffer\n");
		KLIB KonohaRuntime_raise(kctx, EXPT_("Cannnot send buffer"), NULL, 0, NULL);
	}
	usleep(USLEEP_PARAM);
}

static void sendBluetooth(KonohaContext *kctx, kMethod *mtd)
{
	HANDLE hComm = NULL;
	//hComm = CreateFile(
	//		PORT,
	//		GENERIC_WRITE | GENERIC_READ,
	//		0,
	//		NULL,
	//		OPEN_EXISTING,
	//		FILE_ATTRIBUTE_NORMAL,
	//		NULL);
	//COMMTIMEOUTS timeout;
	//if (!GetCommTimeouts(hComm, &timeout)) {
	//	CloseHandle(hComm);
	//	KLIB KonohaRuntime_raise(kctx, EXPT_("Cannot get TIMEOUTS"), NULL, 0, NULL);
	//}
	//timeout.ReadIntervalTimeout = MAXDWORD;
	//timeout.ReadTotalTimeoutMultiplier = 50;
	//timeout.ReadTotalTimeoutConstant = 0;
	//timeout.WriteTotalTimeoutMultiplier = 50;
	//if (!SetCommTimeouts(hComm, &timeout)) {
	//	CloseHandle(hComm);
	//	KLIB KonohaRuntime_raise(kctx, EXPT_("Cannot set TIMEOUTS"), NULL, 0, NULL);
	//}

	//if (hComm = INVALID_HANDLE_VALUE) {
	//	CloseHandle(hComm);
	//	KLIB KonohaRuntime_raise(kctx, EXPT_("Invalid handle value"), NULL, 0, NULL);
	//}

	bt_buffer_t *writebuf = bt_buffer_new(kctx);
	int32_t opsize = 0;

	while (mtd->pc_start[opsize].opcode != OPCODE_RET) {
		opsize++;
	}
	opsize++; // OPCODE_RET
	bt_buffer_append(kctx, writebuf, (char*)&opsize, sizeof(int32_t));
	sendBuf(kctx, hComm, writebuf);
	VirtualMachineInstruction *pc = NULL;
	int i = 0;
	for (; i < opsize; i++) {
		bt_buffer_clear(kctx, writebuf);
		pc = mtd->pc_start + i;
		bt_buffer_append(kctx, writebuf, (char*)&pc->opcode, sizeof(int8_t));
		switch (pc->opcode) {
		case OPCODE_NSET: {
			OPNSET *op = (OPNSET*)pc;
			int8_t a = op->a;
			int32_t n = op->n;
			int16_t ty = op->ty->typeId;
			bt_buffer_append(kctx, writebuf, &a, sizeof(int8_t));
			bt_buffer_append(kctx, writebuf, &n, sizeof(int32_t));
			bt_buffer_append(kctx, writebuf, &ty, sizeof(int16_t));
			break;
		}
		case OPCODE_NMOV: {
			OPNMOV *op = (OPNMOV*)pc;
			int8_t a = op->a;
			int8_t b = op->b;
			bt_buffer_append(kctx, writebuf, &a, sizeof(int8_t));
			bt_buffer_append(kctx, writebuf, &b, sizeof(int8_t));
			break;
		}
		case OPCODE_CALL: {
			OPCALL *op = (OPCALL*)pc;
			int8_t thisidx = op->thisidx;
			int8_t espshift = op->espshift;
			bt_buffer_append(kctx, writebuf, &thisidx, sizeof(int8_t));
			bt_buffer_append(kctx, writebuf, &espshift, sizeof(int8_t));
			break;
		}
		default: {
			int8_t terminator = 0xff;
			bt_buffer_append(kctx, writebuf, &terminator, sizeof(int8_t));
			break;
		}
		}
		sendBuf(kctx, hComm, writebuf);
	}
	bt_buffer_free(kctx, writebuf);
}
