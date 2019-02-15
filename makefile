CC = gcc
CFLAGS = -g -Wall -std=c11 -D_XOPEN_SOURCE=700 -D_POSIX_C_SOURCE=200809L -D_POSIX_SOURCE=1 -D_DEFAULT_SOURCE=1 -D_GNU_SOURCE=1

RM = rm -rf

all: clean hexDump

hexDump:
	$(CC) -o hexDump hexDump.c $(CFLAGS)

clean:
	-$(RM) inotify
