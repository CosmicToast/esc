#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "esc.h"
#include "globals.h"

#define BREAD_BASE64_IMPLEMENTATION
#include "base64.h"

int esc_copy(int argc, char *argv[]) {
	// TODO: getopt for selection
	char selection = 0;
	int istty = isatty(fileno(stdin));
	char *data; size_t len;

	if (istty) {
		len = readall(&data, stdin);
	}

	if (selection) {
		fprintf(termout, OSC "52;%c;", selection);
	} else {
		fprintf(termout, OSC "52;;");
	}

	if (istty) {
		be64bs(termout, data, len);
	} else {
		be64ss(termout, stdin);
	}

	fprintf(termout, ST);
	return 0;
}

int esc_paste(int argc, char *argv[]) {
	// TODO: getopt for selection
	char selection = 0;

	if (esc_pushraw(fileno(termout), &term)) return 1;

	ssize_t len = selection ? 8 : 7;
	if (selection) {
		fprintf(termout, OSC "52;%c;?" ST, selection);
	} else {
		fprintf(termout, OSC "52;;?" ST);
	}
	// TODO: verify the response is appropriate
	while (--len) fgetc(termin);
	bd64ss(stdout, termin);
	// remove ST from stdin
	fgetc(termin); fgetc(termin);

	esc_popraw(fileno(termout), &term);
	return 0;
}
