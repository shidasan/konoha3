#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"

#include <stdlib.h>

#include <tinykonoha.h>

void _sbrk(int bytes){}
void abort() {}
void _write() {}
void _close() {}
void _fstat() {}
void _isatty() {}
void _lseek() {}
void _read() {}
void _stat() {}
lldiv_t __aeabi_uldivmod(unsigned long long n, unsigned long long d) 
{
	lldiv_t res;
	if (d != 0) {
		res.quot = n / d;
		res.rem = n % d;
	} else {
		res.quot = 0;
		res.rem = 0;
	}
	return res;
}
unsigned int __aeabi_uidiv(unsigned int n, unsigned int d)
{
	if (d != 0) {
		return n / d;
	} else {
		return 0;
	}
}
