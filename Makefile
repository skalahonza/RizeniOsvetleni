SHELL := /bin/bash
CFLAGS+= -Wall -std=c++11
objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
program: $(objects)
	${CC} ${CFLAGS} -o program $(objects) -lm
run:
	./program

clean:
	rm -f *.o
	rm -f program
	rm -f hw.zip
	rm -f TEST_*

all: clean program
