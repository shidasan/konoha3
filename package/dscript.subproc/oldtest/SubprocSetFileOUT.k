// written by shinpei
import("konoha.new");
import("dscript.subproc");

void test () {
	Subproc s = new Subproc("echo hello", false);
	FILE f = System.fopen("/dev/null", "w");
	s.setFileOUT(f);
	assert(s.fg() == 0);
}

test();
