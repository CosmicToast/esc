#include "esc.h"
#include <string.h>

// C1 is simply stuff to print after esc
struct c1seq {
	const char *name;
	const char seq;
};

struct c1seq c1seqs[] = {
	{"BPH",                                  '\x42'},
	{"bph",                                  '\x42'},
	{"breakpermittedhere",                   '\x42'},
	{"NBH",                                  '\x43'},
	{"nbh",                                  '\x43'},
	{"nobreakhere",                          '\x43'},
	{"NEL",                                  '\x45'},
	{"nel",                                  '\x45'},
	{"nextline",                             '\x45'},
	{"SSA",                                  '\x46'},
	{"ssa",                                  '\x46'},
	{"startofselectedarea",                  '\x46'},
	{"ESA",                                  '\x47'},
	{"esa",                                  '\x47'},
	{"endofselectedarea",                    '\x47'},
	{"HTS",                                  '\x48'},
	{"hts",                                  '\x48'},
	{"charactertabulationset",               '\x48'},
	{"HTJ",                                  '\x49'},
	{"htj",                                  '\x49'},
	{"charactertabulationwithjustification", '\x49'},
	{"VTS",                                  '\x4a'},
	{"vts",                                  '\x4a'},
	{"linetabulationset",                    '\x4a'},
	{"PLD",                                  '\x4b'},
	{"pld",                                  '\x4b'},
	{"partiallineforward",                   '\x4b'},
	{"PLU",                                  '\x4c'},
	{"plu",                                  '\x4c'},
	{"partiallinebackward",                  '\x4c'},
	{"RI",                                   '\x4d'},
	{"ri",                                   '\x4d'},
	{"reverselinefeed",                      '\x4d'},
	{"SS2",                                  '\x4e'},
	{"ss2",                                  '\x4e'},
	{"singleshifttwo",                       '\x4e'},
	{"SS3",                                  '\x4f'},
	{"ss3",                                  '\x4f'},
	{"singleshiftthree",                     '\x4f'},
	{"DCS",                                  '\x50'},
	{"dcs",                                  '\x50'},
	{"devicecontrolstring",                  '\x50'},
	{"PU1",                                  '\x51'},
	{"pu1",                                  '\x51'},
	{"privateuseone",                        '\x51'},
	{"PU2",                                  '\x52'},
	{"pu2",                                  '\x52'},
	{"privateusetwo",                        '\x52'},
	{"STS",                                  '\x53'},
	{"sts",                                  '\x53'},
	{"settransmitstate",                     '\x53'},
	{"CCH",                                  '\x54'},
	{"cch",                                  '\x54'},
	{"cancelcharacter",                      '\x54'},
	{"MW",                                   '\x55'},
	{"mw",                                   '\x55'},
	{"messagewaiting",                       '\x55'},
	{"SPA",                                  '\x56'},
	{"spa",                                  '\x56'},
	{"startofguardedarea",                   '\x56'},
	{"EPA",                                  '\x57'},
	{"epa",                                  '\x57'},
	{"endofguardedarea",                     '\x57'},
	{"SOS",                                  '\x58'},
	{"sos",                                  '\x58'},
	{"startofheading",                       '\x59'},
	{"SCI",                                  '\x5a'},
	{"sci",                                  '\x5a'},
	{"singlecharacterintroducer",            '\x5a'},
	{"CSI",                                  '\x5b'},
	{"csi",                                  '\x5b'},
	{"controlsequenceintroducer",            '\x5b'},
	{"ST",                                   '\x5c'},
	{"st",                                   '\x5c'},
	{"stringterminator",                     '\x5c'},
	{"OSC",                                  '\x5d'},
	{"osc",                                  '\x5d'},
	{"operatingsystemcommand",               '\x5d'},
	{"PM",                                   '\x5e'},
	{"pm",                                   '\x5e'},
	{"privacymessage",                       '\x5e'},
	{"APC",                                  '\x5f'},
	{"apc",                                  '\x5f'},
	{"applicationprogramcommand",            '\x5f'},
	{NULL, 0},
};

// you do not need this
const char c1_8bit[] = ESC "\x26\x40";
const char c1_7bit[] = ESC "\x20\x46";

static int c1_print(const char *name) {
	for (struct c1seq *ptr = c1seqs; ptr->name; ptr++) {
		if (!strcmp(name, ptr->name)) return printf (ESC "%c", ptr->seq) > 0;
	}
	// 8bit sequences are not truly supported because of utf8
	if (!strcmp("enable", name)) return printf("%s", c1_7bit) > 0;
	// if you really want it... however I still won't output them
	if (!strcmp("enable8bit", name)) return printf("%s", c1_8bit) > 0;
	return 0;
}

int esc_c1(int argc, char *argv[]) {
	if (argc == 1) return 127;
	while (argc > 1) {
		if (!c1_print(*(++argv))) return 127;
		argc--;
	}
	return 0;
}
