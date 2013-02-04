#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"

#include <stdlib.h>

#include <tinykonoha.h>

void _sbrk(int bytes)
{
	//static char HEAP[HEAP_SIZE];
	//static char *break_block = HEAP;
	//char *old_break_block = break_block;
	//break_block += bytes;
	//if (break_block < HEAP || break_block > HEAP + HEAP_SIZE) {
	//	return -1;
	//}
	//return old_break_block;
}
void abort() {}
void _write() {}
void _close() {}
void _fstat() {}
void _isatty() {}
void _lseek() {}
void _read() {}
void _stat() {}
void __aeabi_uldivmod() {}
void __aeabi_uidiv() {}
