PSO
By: Bo Bleckel, Jasper Houston, and Dylan Parsons
Nature Inspired Computation - CSCI 3445
Bowdoin College

/* This program is implemented in C++ */

This program solves optimization problems using a particle swarm optimization approach.
The goal of the program is to compare four neighborhood topologies: Global, Ring, von Neumann, and Random.
The four topologies are explained in depth in the included paper entitled PSO.pdf.
The main.cpp file deals with executing the file and parsing the command line arguments.
The command line arguments are as follows, in the order presented:

For Particle Swarm Optimization:
./main neighborhood size iterations function dimensions
    neighborhood   = which neighborhood topology to test (string):
                      gl = global; every particle's neighborhood is entire swarm
                      ri = ring; particles imagined in a ring and neighbors are the particles to the left and right
                      vn = von Neumann; particles imagined in a grid and neighbors are in the four cardinal directions
                      ra = random; random neighborhoods created for each particle, changed on each iteration with probability 0.2
    size           = size of swarm (int)
    iterations     = number of iterations (int)
    function       = which function to optimize (string):
                      rok = Rosenbrock
                      ack = Ackley
                      ras = Rastrigin
    dimensions     = dimension of the function

These arguments are entered after the executable for the file, which is ./main
and can be compiled using the included Makefile (simply type make to compile).
Similarly, type “make clean” to remove all executables created by the make file.

The algorithm is implemented using a class for each particle, each neighborhood, and for the 
general PSO algorithm as well. The particle and neighborhood classes are relatively small,
and thus are included in the PSO.cpp and PSO.h files.

There is a testCases() function in the main.cpp file that can be used to loop through many of
the possible parameters. This isn’t useful for most, in that it takes around an hour to complete
and results in many lines being printed in the terminal. That said, should one wish to test
these parameters, that’s a good place to look. 

The folder also includes our paper which details our experimental methodology
as well as our results.
