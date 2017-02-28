#include "PSO.h"

using namespace std;

particle::particle() {
	
}

particle::~particle() {
	
}

PSO::PSO(string neighborhood, int swarmSize, int iterations, string function, int dimension) {
	this->neighborhood = neighborhood;
	this->swarmSize = swarmSize;
	this->iterations = iterations;
	this->function = function;
	this->dimension = dimension;
}

PSO::~PSO() {
	
}

void PSO::updateVelocity() {
	
}

void PSO::updatePosition() {
	
}

void initializeSwarm() {
	
}

void solvePSO() {
	initializeSwarm();
}
