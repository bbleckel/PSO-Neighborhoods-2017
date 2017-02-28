#include "PSO.h"

using namespace std;

particle::particle(int dimension) {
	vector<double> velocity;
	
	for (int i = 0; i < dimension; i++) {
		velocity.push_back((rand() - (RAND_MAX/2)) % 100);
	}
	
	this->pBest = INT_MAX;
	this->velocity = velocity;
	this->posX = rand() % 100;
	this->posY = rand() % 100;
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

void PSO::initializeSwarm() {
	vector<particle> swarm;
	
	for (int i = 0; i < swarmSize; i++) {
		particle particle(dimension);
		swarm.push_back(particle);
	}
	
	//this->swarm = swarm;
}

void PSO::solvePSO() {
	srand(time(NULL));
	
	initializeSwarm();
}
