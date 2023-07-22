#include "esc.h"
#include <stdlib.h>

void esc_cfmakeraw(struct termios *termios_p) {
	termios_p->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                | INLCR | IGNCR | ICRNL | IXON);
	// we do want output processing for the most part
	/* termios_p->c_oflag &= ~OPOST; */
	termios_p->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	termios_p->c_cflag &= ~(CSIZE | PARENB);
	termios_p->c_cflag |= CS8;
	termios_p->c_cc[VMIN] = 0;
	termios_p->c_cc[VTIME] = 1;
}

// make fildes raw, save old config in tp
int esc_pushraw(int fildes, struct termios *tp) {
	int tmp = tcgetattr(fildes, tp);
	if (tmp) return tmp;
	struct termios new = *tp;
	esc_cfmakeraw(&new);
	return tcsetattr(fildes, TCSADRAIN, &new);
}

// undo pushraw
int esc_popraw(int fildes, struct termios *tp) {
	return tcsetattr(fildes, TCSADRAIN, tp);
}

#ifndef READALL_BUFSIZE
#define READALL_BUFSIZE 1024
#endif

size_t readall(char **dst, FILE *src) {
	size_t size = READALL_BUFSIZE, read = 0;
	*dst = malloc(size);
	while(!feof(src)) {
		if (size - read < READALL_BUFSIZE) {
			size = (size - read) + READALL_BUFSIZE;
			*dst = realloc(*dst, size);
		}
		read += fread((*dst) + read, 1, READALL_BUFSIZE, src);
	}
	return read;
}
