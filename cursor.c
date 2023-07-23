#include "esc.h"
#include <unistd.h>

// collection of cursor control functions as per ECMA 48 8.2.7

static void printcsi(int terminator, const char *args) {
	if (args) printf(CSI "%s%c", args, terminator);
	else      printf(CSI "%c", terminator);
}

int esc_cursor(int argc, char *argv[]) {
	/* Cursor Control Functions:
	 * -l | -L n: left by n (1 if -l)
	 * -r | -R n: right by n (1 if -r)
	 * -u | -U n: up by n (1 if -u)
	 * -d | -D n: down by n (1 if -d)
	 * -t | -T n: line tabulation by n (1 if -t)
	 * -b | -B n: backwards tabulation by n (1 if -b)
	 * -a | -A n: place on character n of line (1 if -a)
	 * -f | -F n: forward tabulation by n (1 if -f)
	 * -n | -N n: 1st character of following nth line (1 if -n)
	 * -p | -P n: 1st character of previous nth line (1 if -p)
	 * -C N: passed as is to cursor tabulation control
	 * -X N: passed as is to cursor position
	 */
	int c, errflag = 0;
	char *arg = NULL;
	setbuf(stdout, NULL);
	while ((c = getopt(argc, argv, "lL:rR:uU:dD:tT:bB:aA:fF:nN:pP:C:X:")) != -1) {
		switch(c) {
			case 'L': // CUB: CSI Pn 04/04
				arg = optarg;
			case 'l':
				printcsi(0x44, arg);
				break;
			case 'R': // CUF: CSI Pn 04/03
				arg = optarg;
			case 'r':
				printcsi(0x43, arg);
				break;
			case 'U': // CUU: CSI Pn 04/01
				arg = optarg;
			case 'u':
				printcsi(0x41, arg);
				break;
			case 'D': // CUD: CSI Pn 04/02
				arg = optarg;
			case 'd':
				printcsi(0x42, arg);
				break;
			case 'T': // CVT: CSI Pn 05/09
				arg = optarg;
			case 't':
				printcsi(0x59, arg);
				break;
			case 'B': // CBT: CSI Pn 05/10
				arg = optarg;
			case 'b':
				printcsi(0x5a, arg);
				break;
			case 'A': // CHA: CSI Pn 04/07
				arg = optarg;
			case 'a':
				printcsi(0x47, arg);
				break;
			case 'F': // CHT: CSI Pn 04/09
				arg = optarg;
			case 'f':
				printcsi(0x49, arg);
				break;
			case 'N': // CNL: CSI Pn 04/05
				arg = optarg;
			case 'n':
				printcsi(0x45, arg);
				break;
			case 'P': // CPL: CSI Pn 04/06
				arg = optarg;
			case 'p':
				printcsi(0x46, arg);
				break;
			case 'C': // CTC: CSI Ps... 05/07
				printcsi(0x57, optarg);
				break;
			case 'X': // CUP: CSI Pn1;Pn2 04/08
				printcsi(0x48, optarg);
				break;
		}
		arg = NULL;
	}
	return 0;
}
