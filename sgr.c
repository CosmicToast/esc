#include "esc.h"
#include <string.h>
#include <unistd.h>

struct named_style {
	const char *name;
	int num;
};

struct color_offset {
	const char *name;
	int offset;
};

struct named_style named_styles[] = {
	{"bold",            1},
	{"faint",           2},
	{"italic",          3},
	{"underline",       4},
	{"blink",           5},
	{"flash",           6},
	{"negative",        7},
	{"conceal",         8},
	{"cross",           9},
	{"font",            10},
	{"normalfont",      10},
	{"font1",           11},
	{"font2",           12},
	{"font3",           13},
	{"font4",           14},
	{"font5",           15},
	{"font6",           16},
	{"font7",           17},
	{"font8",           18},
	{"font9",           19},
	{"fraktur",         20},
	{"dunderline",      21},
	{"doubleunderline", 21},
	{"resetcolor",      22},
	{"noitalicfraktur", 23},
	{"nounderline",     24},
	{"steady",          25},
	{"positive",        27},
	{"reveal",          28},
	{"nocross",         29},
	// colors are skipped
	{"frame",           51},
	{"circle",          52},
	{"overline",        53},
	{"noframecircle",   54},
	{"nooverline",      55},
	{NULL, 0},
};

// technically don't need the struct here
// but it's nicer to target this way
struct color_offset color_offsets[] = {
	{"black",   0},
	{"red",     1},
	{"green",   2},
	{"yellow",  3},
	{"blue",    4},
	{"magenta", 5},
	{"cyan",    6},
	{"white",   7},
	{"reset",   9},
	{"default", 9},
	{NULL, 0},
};

int esc_sgr(int argc, char *argv[]) {
	/* TODO:
	 * -S: integer style: any integer
	 *     used directly for truecolor and co
	 * -s: named style: bold, faint, italic, underline,
	 *     blink (slow blink), flash (fast blink),
	 *     negative, conceal, cross, dunderline (double),
	 *     frame, encircle, overline
	 * -i: short for -s italic
	 * -b: short for -s bold
	 * -n: normal color
	 * -N: normal background
	 * -c: color      black, red, green, yellow, blue, magenta, cyan, white
	 * -C: background black, red, green, yellow, blue, magenta, cyan, white
	 * -r: reset all
	 * -t: table color (0 to 255)
	 * -T: true color (r;g;b)
	 */
	int c, errflag = 0, first = 0;
	setbuf(stdout, NULL);
	printf(CSI);
	while ((c = getopt(argc, argv, "S:s:ibnNc:C:rt:T:")) != -1) {
		if (first++) putchar(';');
		switch (c) {
			case 'S': // use as-is
				printf("%s", optarg);
				break;
			case 's': { // named style
				struct named_style *ptr;
				for (ptr = named_styles; ptr->name; ptr++) {
					if (!strcmp(ptr->name, optarg)) {
						printf("%d", ptr->num);
						break;
					}
				}
				if (!ptr->name) errflag++;
				break;
			}
			case 'i': // italic
				putchar('3');
				break;
			case 'b': // bold
				putchar('1');
				break;
			case 'r': // reset
				putchar('0');
				break;
			case 'n': // normal foreground
				printf("39");
				break;
			case 'N': // normal background
				printf("49");
				break;
			case 'c':
			case 'C': {
				int base = 30;
				if (c == 'C') base += 10;
				struct color_offset *ptr;
				for (ptr = color_offsets; ptr->name; ptr++) {
					if (!strcmp(ptr->name, optarg)) {
						printf("%d", base + ptr->offset);
						break;
					}
				}
				if (!ptr->name) errflag++;
				break;
			}
			case 't':
				printf("38;5;%s", optarg);
				break;
			case 'T':
				printf("38;2;%s", optarg);
				break;
		}
	}
	printf("\x6d");
	return 0;
}
