# Makefile for the scc03 program

# scc03 needs: IntVec, loadGraph, and dfsTracec1
# Please make sure to use the .c and .h files.
# the main file is scc03.c
# the executable should be scc03
# the program requires one input file in the form of a textfile.
# example run: "./scc03 input.txt"
# You can also give it the flag "-U" to make the graph undirected.
# example run: "./scc03 -U input.txt"

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


scc03:    scc03.o  intVec.o loadGraph.o dfsTrace1.o
		${CC} -o scc03 ${CFLAGS} scc03.o intVec.o loadGraph.o dfsTrace1.o

scc03.o:  scc03.c
		${CC} -c ${CFLAGS} scc03.c

intVec.o:     intVec.c
		${CC} -c ${CFLAGS} intVec.c

loadGraph.o:     loadGraph.c
		${CC} -c ${CFLAGS} loadGraph.c

dfsTrace1.o:     dfsTrace1.c
		${CC} -c ${CFLAGS} dfsTrace1.c