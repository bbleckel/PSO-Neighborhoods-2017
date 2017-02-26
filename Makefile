CPPFLAGS = -O3 -Wall -Werror
CC = g++

PROGS = main
default: $(PROGS)

main: main.o
	$(CC) $(CPPFLAGS) -o $@ main.o

main.o: main.cpp
	$(CC) -c main.cpp -o $@

clean:
	rm *.o
	rm -f main
