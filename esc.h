#pragma once
#include <stdio.h>
#include <termios.h>

// magic values and utilities
#define ESC "\x1b"
#define CSI ESC "["
#define OSC ESC "]"
#define ST  ESC "\\"
void cfmakerawesc(struct termios*);
int esc_pushraw(int, struct termios*);
int esc_popraw(int, struct termios*);
size_t readall(char **dst, FILE *src);

// commands
typedef int (*escmain)(int, char*[]);
escmain findesc(const char*);
#define EXPORT(x) int esc_##x (int, char*[])

// control sets
EXPORT(c0);

// SGR (CSI -> \x6d)
EXPORT(sgr);

// OSC 52
EXPORT(copy);
EXPORT(paste);

#undef EXPORT
