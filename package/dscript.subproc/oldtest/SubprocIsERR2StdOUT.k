//Written by Joseph

import("konoha.new");
import("dscript.subproc");

void test() {
	Subproc s = new Subproc("", true);
	assert(s.isERR2StdOUT() == false);

	s = new Subproc("", false);
	assert(s.isERR2StdOUT() == false);

	s = new Subproc("ls", true);
	assert(s.isERR2StdOUT() == false);

	s = new Subproc("ls", false);
	assert(s.isERR2StdOUT() == false);
}

test();
