# Makefile for main.c with macros

FLAGS   = -std=c99 -Wall
SOURCES = main.c intVec.c
OBJECTS = main.o intVec.o
EXEBIN  = main

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)

check :
	valgrind --leak-check=full $(EXEBIN) queueClient.c out.txt

clean :
	rm -f $(EXEBIN) $(OBJECTS)

