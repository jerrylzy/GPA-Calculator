OPTIMIZE = -O3

CC = g++
STD = 14
CFLAGS = -std=c++$(STD) $(OPTIMIZE) -march=native -mtune=native

gpacalc: gpacalc.cpp
	$(CC) $(CFLAGS) Course.cpp Quarter.cpp gpacalc.cpp -o $@

clean:
	rm -f *.o *.s gpacalc
	find . -type f -name "*~" -delete
