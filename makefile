#
# Author : Dancan Angwenyi
# Date : 8th April 2019
# Computer Science
# C++ Image processing (Using containers and operators)
#
CC=g++
CCFLAGS=-std=c++11
LIBS=-lm
imageops: driver.o imageops.o
		$(CC)	$(CCFLAGS) imageops.o driver.o -o imageops $(LIBS)
imageops.o:	imageops.cpp
		$(CC) $(CCFLAGS) imageops.cpp -c
driver.o: driver.cpp imageops.cpp imageops.h
		$(CC) $(CCFLAGS) -c $^
clean:
		@rm -f *.o
		@rm -f imageops
