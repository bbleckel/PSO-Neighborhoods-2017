#include "PSO.h"

using namespace std;

PSO::PSO(string neighborhood, int swarmSize, int iterations, string function, int dimension) {
	this->neighborhood = neighborhood;
	this->swarmSize = swarmSize;
	this->iterations = iterations;
	this->function = function;
	this->dimension = dimension;
}

PSO::~PSO() {
	
}

PSO::updateVelocity() {
	
}

PSO::updatePosition() {
	
}
