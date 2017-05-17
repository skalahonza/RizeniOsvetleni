SHELL := /bin/bash
CFLAGS+= -Wall -g -std=c++0x
objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
program: $(objects)
	g++ -std=c++11 $(objects) -lpthread -o program -lm

run:
	./program

clean:
	rm -f *.o
	rm -f program
	rm -f hw.zip
	rm -f TEST_*

all: clean program
