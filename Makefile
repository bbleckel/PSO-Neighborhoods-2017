CPPFLAGS = -O3 -Wall -Werror
CC = g++

PROGS = main
default: $(PROGS)

main: main.o PSO.o
	$(CC) $(CPPFLAGS) -o $@ main.o PSO.o

main.o: main.cpp PSO.h
	$(CC) -c main.cpp -o $@

PSO.o: PSO.cpp PSO.h
	$(CC) -c PSO.cpp -o $@

clean:
	rm *.o
	rm -f main
