# Sample Makefile
CFLAGS := $(shell pkg-config --cflags glib-2.0 gtk+-2.0) -g
LDFLAGS := $(shell pkg-config --libs glib-2.0 gtk+-2.0)

wordfreq: wordfreq.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)