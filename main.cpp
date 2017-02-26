#include <unistd.h>

using namespace std;

void printInfo() {
  cout << endl;
  cout << "Usage:\nFor Particle Swarm Optimization:\n./main neighborhood size iterations function dimensions" << endl;
  cout << "    neighborhood   = which neighborhood topology to test (string):" << endl;
  cout << "                      gl = global, every particle's neighborhood is entire swarm" << endl;
  cout << "                      ri = ring, particles imagined in a ring and neighbors are the particles to the left and right" << endl;
  cout << "                      vn = von Neumann, particles imagined in a grid and neighbors are in the four cardinal directions" << endl;
  cout << "                      ra = random, random neighborhoods created for each particle, changed on each iteration with probability 0.2" << endl;
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
  string neighborhood;
  int size;
  int iterations;
  string function;
  int dimensions;
}
