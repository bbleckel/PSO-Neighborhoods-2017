#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include "PSO.h"

using namespace std;

int GLOBAL_NEIGHBORHOOD_INT = 0;
int RING_NEIGHBORHOOD_INT = 1;
int VON_NEUMANN_NEIGHBORHOOD_INT = 2;
int RANDOM_NEIGHBORHOOD_INT = 3;

int ROSENBROCK_FUNCTION_INT = 0;
int ACKLEY_FUNCTION_INT = 1;
int RASTRIGIN_FUNCTION_INT = 2;

void printInfo() {
    cout << endl;
    cout << "Usage:\nFor Particle Swarm Optimization:\n./main neighborhood size iterations function dimensions" << endl;
    cout << "    neighborhood   = which neighborhood topology to test (string):" << endl;
    cout << "                      gl = global; every particle's neighborhood is entire swarm" << endl;
    cout << "                      ri = ring; particles imagined in a ring and neighbors are the particles to the left and right" << endl;
    cout << "                      vn = von Neumann; particles imagined in a grid and neighbors are in the four cardinal directions" << endl;
    cout << "                      ra = random; random neighborhoods created for each particle, changed on each iteration with probability 0.2" << endl;
    cout << "    size           = size of swarm (int)" << endl;
    cout << "    iterations     = number of iterations (int)" << endl;
    cout << "    function       = which function to optimize (string):" << endl;
    cout << "                      rok = Rosenbrock" << endl;
    cout << "                      ack = Ackley" << endl;
    cout << "                      ras = Rastrigin" << endl;
    cout << "    dimensions     = dimension of the function" << endl;
    cout << endl;
}

int main (int argc, char** argv) {
    int neighborhood;
    int size;
    int iterations;
    int function;
    int dimensions;
    
    if(argc != 6) {
        // incorrect input
        printInfo();
        exit(1);
    } else {
        // check neighborhood type
        if (!strcmp(argv[1], "gl")) {
            neighborhood = GLOBAL_NEIGHBORHOOD_INT;
        } else if (!strcmp(argv[1], "ri")) {
            neighborhood = RING_NEIGHBORHOOD_INT;
        } else if (!strcmp(argv[1], "vn")) {
            neighborhood = VON_NEUMANN_NEIGHBORHOOD_INT;
        } else if (!strcmp(argv[1], "ra")) {
            neighborhood = RANDOM_NEIGHBORHOOD_INT;
        } else {
            cout << "Invalid first argument specifying neighborhood type. Please use:" << endl;
            cout << "    neighborhood   = which neighborhood topology to test (string):" << endl;
            cout << "                      gl = global; every particle's neighborhood is entire swarm" << endl;
            cout << "                      ri = ring; particles imagined in a ring and neighbors are the particles to the left and right" << endl;
            cout << "                      vn = von Neumann; particles imagined in a grid and neighbors are in the four cardinal directions" << endl;
            cout << "                      ra = random; random neighborhoods created for each particle, changed on each iteration with probability 0.2" << endl;
            exit(1);
        }

        // check swarm size
        try {
            // stoi could throw exception if argv[2] cannot be converted; catch and show error
            size = stoi(argv[2]);
            if (size < 0) {
                cout << "Invalid second argument specifying swarm size. Swarm cannot have negative size. Please use:" << endl;
                cout << "\tsize = size of swarm (int)" << endl;
                return 0;
            }
        } catch (invalid_argument&) {
            // catch invalid_argument error
            cout << "Invalid second argument specifying swarm size. Must be entered as integer value. Please use:" << endl;
            cout << "\tsize = size of swarm (int)" << endl;
            return 0;
        }
        
        try {
            iterations = stoi(argv[3]);
            if (iterations < 0) {
                cout << "Invalid second argument specifying swarm size. Swarm cannot have negative size. Please use:" << endl;
                cout << "\tsize = size of swarm (int)" << endl;
                return 0;
            }
        } catch (invalid_argument&) {
            cout << "Invalid third argument specifying number of iterations. Must be entered as integer value. Please use:" << endl;
            cout << "\titerations = number of iterations (int)" << endl;
            return 0;
        }
        
        // check optimization function
        if (!strcmp(argv[4], "rok")) {
            function = ROSENBROCK_FUNCTION_INT;
        } else if (!strcmp(argv[4], "ack")) {
            function = ACKLEY_FUNCTION_INT;
        } else if (!strcmp(argv[4], "ras")) {
            function = RASTRIGIN_FUNCTION_INT;
        } else {
            cout << "Invalid fourth argument specifying optimization function. Please use:" << endl;
            cout << "    function       = which function to optimize (string):" << endl;
            cout << "                      rok = Rosenbrock" << endl;
            cout << "                      ack = Ackley" << endl;
            cout << "                      ras = Rastrigin" << endl;
            exit(1);
        }
        
        try {
            dimensions = stoi(argv[5]);
            if (dimensions < 0) {
                cout << "Invalid fifth argument specifying number of dimensions. Cannot have negative dimensions. Please use:" << endl;
                cout << "\tdimensions = dimension of the function" << endl;
                return 0;
            }
        } catch (invalid_argument&) {
            cout << "Invalid fifth argument specifying number of dimensions. Must be entered as integer value. Please use:" << endl;
            cout << "\tdimensions = dimension of the function (int)" << endl;
            return 0;
        }
        
        
        cout << "Your inputs:\nNeighborhood Type: " << neighborhood << "\nSwarm Size: " << size << "\nIterations: " << iterations << "\nFunction: " << function << "\nDimension: " << dimensions << endl;
        
        PSO solver = PSO(neighborhood, size, iterations, function, dimensions);
        solver.solvePSO();
   
    }
    
}
