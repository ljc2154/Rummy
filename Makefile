CC = g++

INCLUDES =

CFLAGS   = -g -Wall $(INCLUDES)

LDFLAGS = -g

LDLIBS =

rummy: rummy.o

rummy.o: rummy.cpp rummy.h

.PHONY: clean
clean:
	rm -f *.o a.out core rummy

.PHONY: all
all: clean rummy