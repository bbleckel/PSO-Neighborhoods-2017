#include <unistd.h>

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
  cout << "    dimensions     = the dimensionality of the function" << endl;
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
    if (strcmp(argv[1], "gl")) {
      neighborhood = GLOBAL_NEIGHBORHOOD_INT;
    } else if (strcmp(argv[1], "ri")) {
      neighborhood = RING_NEIGHBORHOOD_INT;
    } else if (strcmp(argv[1], "vn")) {
      neighborhood = VON_NEUMANN_NEIGHBORHOOD_INT;
    } else if (strcmp(argv[1], "ra")) {
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

//NOTE
//NOTE
//NOTE: should these be always positive or just not negative???

    // check swarm size
    if (isInteger(argv[2])) {
      if (argv[2] >= 0) {
        size = argv[2];
      } else {
        cout << "Invalid second argument specifying swarm size. Swarm cannot have negative size. Please use:" << endl;
        cout << "    size           = size of swarm (int)" << endl;
      }
    } else {
      cout << "Invalid second argument specifying swarm size. Must be entered as integer value. Please use:" << endl;
      cout << "    size           = size of swarm (int)" << endl;
    }

    // check iterations
    if (isInteger(argv[3])) {
      if (argv[3] >= 0) {
        iterations = argv[3];
      } else {
        cout << "Invalid third argument specifying number of iterations. Cannot perform negative iterations. Please use:" << endl;
        cout << "    iterations     = number of iterations (int)" << endl;
      }
    } else {
      cout << "Invalid third argument specifying number of iterations. Must be entered as integer value. Please use:" << endl;
      cout << "    iterations     = number of iterations (int)" << endl;
    }

    // check optimization function
    if (strcmp(argv[4], "rok")) {
      function = ROSENBROCK_FUNCTION_INT;
    } else if (strcmp(argv[4], "ack")) {
      function = ACKLEY_FUNCTION_INT;
    } else if (strcmp(argv[4], "ras")) {
      function = RASTRIGIN_FUNCTION_INT;
    } else {
      cout << "Invalid fourth argument specifying optimization function. Please use:" << endl;
      cout << "    function       = which function to optimize (string):" << endl;
      cout << "                      rok = Rosenbrock" << endl;
      cout << "                      ack = Ackley" << endl;
      cout << "                      ras = Rastrigin" << endl;
      exit(1);
    }

    // check dimensions
    if (isInteger(argv[5])) {
      if (argv[5] >= 0) {
        dimensions = argv[5];
      } else {
        cout << "Invalid fifth argument specifying number of dimensions. Cannot have negative dimensions. Please use:" << endl;
        cout << "    dimensions     = the dimensionality of the function" << endl;
      }
    } else {
      cout << "Invalid third argument specifying number of dimensions. Must be entered as integer value. Please use:" << endl;
      cout << "    dimensions     = the dimensionality of the function" << endl;
    }





  }

}


// helper function for checking input parameters
int isInteger(auto x) {
  if (x == floor(x)) {
    return 1;
  }
  return 0;
}
