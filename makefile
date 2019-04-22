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
test: test.o imageops.o
		$(CC)	$(CCFLAGS) imageops.o test.o -o test $(LIBS)
test-all:
		./test
quality-test:
		./imageops -i ./images/M1 ./images/M2
		./imageops -l ./images/U1 ./images/M1 ./images/mask1
		./imageops -l ./images/U2 ./images/M2 ./images/mask2
		./imageops -a ./images/mask1 ./images/mask2 ./images/outputofQualityTest
test.o: test.cpp
		$(CC) $(CCFLAGS) -c $^
clean:
		@rm -f *.o
		@rm -f imageops
		@rm -f test
