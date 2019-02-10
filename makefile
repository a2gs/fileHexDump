CC = gcc
CFLAGS = -g -Wall -std=c11 -D_XOPEN_SOURCE=700

RM = rm -rf

all: clean hexDump

hexDump:
	$(CC) -o hexDump hexDump.c $(CFLAGS)

clean:
	-$(RM) inotify
