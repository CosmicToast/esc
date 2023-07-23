#include "esc.h"
#include <string.h>

struct escname {
	const char *name;
	escmain     fun;
};

struct escname names[] = {
	// control sets
	{"c0", esc_c0},
	{"C0", esc_c0},
	{"c1", esc_c1},
	{"C1", esc_c1},
	// SGR (CSI -> \x6d)
	{"sgr",   esc_sgr},
	{"color", esc_sgr},
	{"esgr",  esc_sgr},
	// OSC 52
	{"copy",   esc_copy},
	{"ecopy",  esc_copy},
	{"epaste", esc_paste},
	{"paste",  esc_paste},
	{0, 0},
};

escmain findesc(const char *s) {
	for (struct escname *ptr = names; ptr->name; ptr++) {
		if (!strcmp(ptr->name, s)) return ptr->fun;
	}
	return 0;
}
