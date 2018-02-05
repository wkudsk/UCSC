# Makefile for digraph01.c with macros

#FLAGS   = -std=c99 -Wall
#SOURCES = digraph01.c intVec.c
#OBJECTS = digraph01.o intVec.o
#EXEBIN  = digraph01

#all: $(EXEBIN)

#$(EXEBIN) : $(OBJECTS)
#	gcc -o $(EXEBIN) $(OBJECTS)

#$(OBJECTS) : $(SOURCES)
#	gcc -c $(FLAGS) $(SOURCES)

#check :
#	valgrind --leak-check=full $(EXEBIN) digraph01.c out.txt

#clean :
#	rm -f $(EXEBIN) $(OBJECTS)


# Makefile sample illustrating separate compilation and dependencies.

# Students are welcome to use this as a starter or model, but be sure
# to replace these comments with comments relevant to YOUR assignment
# (including your name and cats login!).  If the reader has to wade
# through "junk comments" you will lose credit.

# Explanatory comments follow the ``real code.''
# Everything after the # on any line is a comment

# ===================================================================
# Here we define a few important "make" variables.
# CFLAGS is platform dependent.  This one is for Linux.

CC     = gcc
CFLAGS = -g -Wall -O0 -std=c99 -D_SVID_SOURCE

# The next line has the first target.  Typing "make" without any names
# causes "make" to default to this target.
# A common first target would read "all: hex shuffle" but this is omitted
# because shuffle.c is not in this directory.
#
digraph01:    digraph01.o  intVec.o
		${CC} -o digraph01 ${CFLAGS} digraph01.o intVec.o

digraph01.o:  digraph01.c  intVec.h
		${CC} -c ${CFLAGS} digraph01.c

intVec.o:     intVec.c  intVec.h
		${CC} -c ${CFLAGS} intVec.c

shuffle:        shuffle.o  intVec.o
		${CC} -o shuffle ${CFLAGS} shuffle.o  intVec.o
shuffle.o:		shuffle.c  intVec.h
		${CC} -c ${CFLAGs} shuffle.c