CC=g++
CCFLAGS=-std=c++11
LIBS=-lm
imageops: 	driver.o imageops.o	
		$(CC)	$(CCFLAGS) imageops.o driver.o -o imageops $(LIBS)		
imageops.o:	Image.cpp
		$(CC) $(CCFLAGS) Image.cpp -c
driver.o:	driver.cpp
		$(CC) $(CCFLAGS) driver.cpp -c
clean:
		@rm -f *.o
		@rm -f imageops
