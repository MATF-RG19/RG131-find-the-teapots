PROGRAM   = findtheteapots
CC        = gcc
CFLAGS    = -g -Wall
LDFLAGS   = -lGL -lGLU -lglut -lm

$(PROGRAM): findtheteapots.o
	$(CC) -o $(PROGRAM) findtheteapots.o $(LDFLAGS)

.PHONY: clean dist run

clean:
	-rm -f *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)

run:
	./$(PROGRAM)