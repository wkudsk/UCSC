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
graph02:    graph02.o  intVec.o loadGraph.o
		${CC} -o graph02 ${CFLAGS} graph02.o intVec.o loadGraph.o

graph02.o:  graph02.c  intVec.h loadGraph.h
		${CC} -c ${CFLAGS} graph02.c

intVec.o:     intVec.c  intVec.h
		${CC} -c ${CFLAGS} intVec.c

loadGraph.o:     loadGraph.c  loadGraph.h intVec.h
		${CC} -c ${CFLAGS} loadGraph.c
