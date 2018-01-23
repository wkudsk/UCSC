# Makefile for main.c with macros

FLAGS   = -std=c99 -Wall
SOURCES = digraph01.c intVec.c
OBJECTS = digraph01.o intVec.o
EXEBIN  = digraph01

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)

check :
	valgrind --leak-check=full $(EXEBIN) digraph01.c out.txt

clean :
	rm -f $(EXEBIN) $(OBJECTS)

