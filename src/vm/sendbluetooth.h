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

#include <windows.h>
#include <winuser.h>

#define PORT         "COM5:"
#define BUFSIZE      128
#define USLEEP_PARAM 2000000

static void sendBuf(KonohaContext *kctx, HANDLE hComm, char *writebuf, size_t size)
{
	char buf[BUFSIZE] = {0};
	const char *magicstr = "abcdefghi "; //Sometimes a few bytes of received buffer at front had brewed out, to avoid it.
	size_t strsize = strlen(magicstr);
	DWORD readsize = 0;
	memcpy(buf, magicstr, strsize);
	memcpy(buf+strsize, writebuf, size);
	buf[strsize + size] = '\r';
	buf[strsize + size + 1] = '\n';
	if (!WriteFile(hComm, writebuf, BUFSIZE, &readsize, NULL)) {
		CloseHandle(hComm);
		KLIB KonohaRuntime_raise(kctx, EXPT_("Cannnot send buffer"), NULL, 0, NULL);
	}
	usleep(USLEEP_PARAM);
}

static void sendBluetooth(KonohaContext *kctx, kMethod *mtd)
{
	HANDLE hComm;
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

	char writebuf[BUFSIZE];
	int32_t opsize = 0;

	while (mtd->pc_start[opsize].opcode != OPCODE_RET) {
		opsize++;
	}
	opsize++; // OPCODE_RET
	memcpy(writebuf, &opsize, sizeof(int32_t));
	sendBuf(kctx, hComm, writebuf, sizeof(int32_t));
	VirtualMachineInstruction *pc = NULL;
	int i = 0;
	for (; i < opsize; i++) {
		pc = mtd->pc_start + i;
		switch (pc->opcode) {
		case OPCODE_NSET: {
			OPNSET *op = pc;
			break;
		}
		default: {
			int i = 0;
		}
		}
	}
}
