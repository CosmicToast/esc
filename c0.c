#include "esc.h"
#include <string.h>

// C0 is simply stuff to print
struct c0seq {
	const char *name;
	const char seq;
};

struct c0seq c0seqs[] = {
	{"NUL",                      '\x00'},
	{"nul",                      '\x00'},
	{"null",                     '\x00'},
	{"SOH",                      '\x01'},
	{"soh",                      '\x01'},
	{"startofheading",           '\x01'},
	{"STX",                      '\x02'},
	{"stx",                      '\x02'},
	{"startoftext",              '\x02'},
	{"ETX",                      '\x03'},
	{"etx",                      '\x03'},
	{"endoftext",                '\x03'},
	{"EOT",                      '\x04'},
	{"eot",                      '\x04'},
	{"endoftransmission",        '\x04'},
	{"ENQ",                      '\x05'},
	{"enq",                      '\x05'},
	{"enquiry",                  '\x05'},
	{"ACK",                      '\x06'},
	{"ack",                      '\x06'},
	{"acknowledge",              '\x06'},
	{"BEL",                      '\x07'},
	{"bel",                      '\x07'},
	{"bell",                     '\x07'},
	{"BS",                       '\x08'},
	{"bs",                       '\x08'},
	{"backspace",                '\x08'},
	{"HT",                       '\x09'},
	{"ht",                       '\x09'},
	{"charactertabulation",      '\x09'},
	{"LF",                       '\x0a'},
	{"lf",                       '\x0a'},
	{"linefeed",                 '\x0a'},
	{"NL",                       '\x0a'},
	{"nl",                       '\x0a'},
	{"newline",                  '\x0a'},
	{"VT",                       '\x0b'},
	{"vt",                       '\x0b'},
	{"linetabulation",           '\x0b'},
	{"FF",                       '\x0c'},
	{"ff",                       '\x0c'},
	{"formfeed",                 '\x0c'},
	{"CR",                       '\x0d'},
	{"cr",                       '\x0d'},
	{"carriagereturn",           '\x0d'},
	{"SO",                       '\x0e'},
	{"so",                       '\x0e'},
	{"shiftout",                 '\x0e'},
	{"LS1",                      '\x0e'},
	{"ls1",                      '\x0e'},
	{"lockingshiftone",          '\x0e'},
	{"SI",                       '\x0f'},
	{"si",                       '\x0f'},
	{"shiftin",                  '\x0f'},
	{"LS0",                      '\x0f'},
	{"ls0",                      '\x0f'},
	{"lockingshiftzero",         '\x0f'},
	{"DLE",                      '\x10'},
	{"dle",                      '\x10'},
	{"datalinkescape",           '\x10'},
	{"DC1",                      '\x11'},
	{"dc1",                      '\x11'},
	{"devicecontrolone",         '\x11'},
	{"DC2",                      '\x12'},
	{"dc2",                      '\x12'},
	{"devicecontroltwo",         '\x12'},
	{"DC3",                      '\x13'},
	{"dc3",                      '\x13'},
	{"devicecontrolthree",       '\x13'},
	{"DC4",                      '\x14'},
	{"dc4",                      '\x14'},
	{"devicecontrolfour",        '\x14'},
	{"NAK",                      '\x15'},
	{"nak",                      '\x15'},
	{"negativeacknowledge",      '\x15'},
	{"SYN",                      '\x16'},
	{"syn",                      '\x16'},
	{"synchronousidle",          '\x16'},
	{"ETB",                      '\x17'},
	{"etb",                      '\x17'},
	{"endoftransmissionblock",   '\x17'},
	{"CAN",                      '\x18'},
	{"can",                      '\x18'},
	{"cancel",                   '\x18'},
	{"EM",                       '\x19'},
	{"em",                       '\x19'},
	{"endofmedium",              '\x19'},
	{"SUB",                      '\x1a'},
	{"sub",                      '\x1a'},
	{"substitute",               '\x1a'},
	{"ESC",                      '\x1b'},
	{"esc",                      '\x1b'},
	{"escape",                   '\x1b'},
	{"IS4",                      '\x1c'},
	{"is4",                      '\x1c'},
	{"informationseparatorfour", '\x1c'},
	{"FS",                       '\x1c'},
	{"fs",                       '\x1c'},
	{"fileseparator",            '\x1c'},
	{"IS3",                      '\x1d'},
	{"is3",                      '\x1d'},
	{"informationseparator3",    '\x1d'},
	{"GS",                       '\x1d'},
	{"gs",                       '\x1d'},
	{"groupseparator",           '\x1d'},
	{"IS2",                      '\x1e'},
	{"is2",                      '\x1e'},
	{"informationseparatortwo",  '\x1e'},
	{"RS",                       '\x1e'},
	{"rs",                       '\x1e'},
	{"recordseparator",          '\x1e'},
	{"IS1",                      '\x1f'},
	{"is1",                      '\x1f'},
	{"informationseparatorone",  '\x1f'},
	{"US",                       '\x1f'},
	{"us",                       '\x1f'},
	{"unitseparator",            '\x1f'},
	{NULL, 0},
};

// you do not need this
const char c0enable[] = ESC "\x21\x40";

static int c0_print(const char *name) {
	for (struct c0seq *ptr = c0seqs; ptr->name; ptr++) {
		if (!strcmp(name, ptr->name)) return putchar(ptr->seq) != EOF;
	}
	if (!strcmp("enable", name)) return printf("%s", c0enable) > 0;
	return 0;
}

int esc_c0(int argc, char *argv[]) {
	if (argc == 1) return 127;
	while (argc > 1) {
		if (!c0_print(*(++argv))) return 127;
		argc--;
	}
	return 0;
}
