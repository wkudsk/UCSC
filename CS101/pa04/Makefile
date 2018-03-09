# Makefile for the priority04 program

# priority04 needs: adjWgtVec, loadWgtGraph, and minPQ
# Please make sure to use the .c and .h files.
# the main file is priority04.c
# the executable should be priority04
# the program requires a flag (-P for Primm's -D for Dijkstra's), a start vector, and an input file in the form of a textfile.
# example run: "./priority04 -P 2 input.txt"
# You can also give it the flag "-D" to run dijkstra's algorithm.
# example run: "./priority04 -D 2 input.txt"

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


priority04:    priority04.o  adjWgtVec.o loadWgtGraph.o minPQ.o
		${CC} -o priority04 ${CFLAGS} priority04.o adjWgtVec.o loadWgtGraph.o minPQ.o

priority04.o:  priority04.c adjWgtVec.h loadWgtGraph.h minPQ.h priority04.h
		${CC} -c ${CFLAGS} priority04.c

adjWgtVec.o:     adjWgtVec.c adjWgtVec.h
		${CC} -c ${CFLAGS} adjWgtVec.c

loadWgtGraph.o:     loadWgtGraph.c loadWgtGraph.h
		${CC} -c ${CFLAGS} loadWgtGraph.c

minPQ.o:     minPQ.c minPQ.h
		${CC} -c ${CFLAGS} minPQ.c
