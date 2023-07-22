#include "esc.h"
#include "globals.h"
#include <libgen.h>

int main(int argc, char *argv[]) {
	termout = fopen("/dev/tty", "w");
	termin  = fopen("/dev/tty", "r");
	setbuf(termout, NULL);
	setbuf(termin, NULL);

	escmain fun = findesc(basename(argv[0]));
	if (fun) return fun(argc, argv);
	if (argc > 1) {
		fun = findesc(argv[1]);
		if (fun) return fun(argc - 1, argv + 1);
	}

	return 127; // command not found
}
