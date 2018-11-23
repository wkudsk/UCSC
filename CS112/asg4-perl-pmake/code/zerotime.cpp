// $Id: zerotime.cpp,v 1.1 2018-11-06 18:51:47-08 - - $

#include <sys/types.h>
#include <utime.h>

int main (int, char** argv) {
   struct utimbuf times {0, 0};
   utime (argv[1], &times);
}

