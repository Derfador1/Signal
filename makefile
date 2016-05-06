
CFLAGS+=-std=c11
CFLAGS+=-Wall -Wextra -Wpedantic
CFLAGS+=-Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline
CFLAGS+=-D _XOPEN_SOURCE=500
CFLAGS+=-D _POSIX_C_SOURCE=200809L

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
