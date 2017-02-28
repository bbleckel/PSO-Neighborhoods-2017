#include "PSO.h"

using namespace std;

int MAX_VEL_RAND_VALUE[3] = {2, 4, 4};
int MIN_VEL_RAND_VALUE = -2;


Particle::Particle(int dimension, int function) {
	for (int i = 0; i < dimension; i++) {
        // generate random value within specified range for each function
        double random = (rand() % (MAX_VEL_RAND_VALUE[function] - MIN_VEL_RAND_VALUE + 1)) + MIN_VEL_RAND_VALUE;
		velocity.push_back(random);
        pBest.push_back(INT_MAX);
        position.push_back(rand() % 100);
	}
}

Particle::~Particle() {
	
}

PSO::PSO(int neighborhood, int swarmSize, int iterations, int function, int dimension) {
	this->neighborhood = neighborhood;
	this->swarmSize = swarmSize;
	this->iterations = iterations;
	this->function = function;
	this->dimension = dimension;
}

PSO::~PSO() {
	
}

void PSO::updateVelocity(int index) {
    Particle p = swarm[index];
    // iterate through dimensions, updating respective velocities
    for(int i = 0; i < dimension; i++) {
//        double personalAttract =
        cout << "Particle " << index << " has velocity at dim " << i << " = " << swarm[index].velocity[i] << endl;
    }
}

void PSO::updatePosition(int index) {
	
}

void PSO::initializeSwarm() {
    // create swarm of 'swarmSize' particles
	for (int i = 0; i < swarmSize; i++) {
		Particle newParticle = Particle(dimension, function);
		swarm.push_back(newParticle);
	}
}

void PSO::solvePSO() {
	srand(time(NULL));
	
	initializeSwarm();
    
    int iterRemaining = iterations;
    while(iterRemaining >= 0) {
        // iterate through particles, updating velocity & position
        for(int i = 0; i < swarmSize; i++) {
            updateVelocity(i);
            updatePosition(i);
        }
        
        iterRemaining--;
    }
    
    
    
    
    
}




