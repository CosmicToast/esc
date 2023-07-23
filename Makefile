CC ?= cc
CFLAGS ?= -Os -pipe

SRC := main.c util.c globals.c names.c \
	   c0.c sgr.c osc52.c
OBJ := ${SRC:.c=.o}

esc: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

.PHONY: clean
clean:
	@rm -f $(OBJ) esc
