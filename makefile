
CC=gcc
CFLAGS+=-Wall -Wextra -Wpedantic
CFLAGS+=-Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

LDLIBS+=-lm

signaler:signaler.o

profile:CFLAGS+=-pg
profile:LDFLAGS+=-pg
profile:signaler

.PHONY: clean debug profile

clean:
	rm *.o signaler

debug: CFLAGS+=-g
debug: signaler
