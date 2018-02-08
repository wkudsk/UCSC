# Makefile for the graph02 program

# graph02 needs: IntVec and loadGraph
# Please make sure to use the .c and .h files.
# the main file is graph02.c
# the executable should be graph02
# the program requires one input file in the form of a textfile.
# example run: "./graph02 input.txt"

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


graph02:    graph02.o  intVec.o loadGraph.o
		${CC} -o graph02 ${CFLAGS} graph02.o intVec.o loadGraph.o

graph02.o:  graph02.c
		${CC} -c ${CFLAGS} graph02.c

intVec.o:     intVec.c
		${CC} -c ${CFLAGS} intVec.c

loadGraph.o:     loadGraph.c
		${CC} -c ${CFLAGS} loadGraph.c
