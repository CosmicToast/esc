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

// SGR (CSI -> \x6d)
int esc_sgr(int, char*[]);

// OSC 52
int esc_copy(int, char*[]);
int esc_paste(int, char*[]);
