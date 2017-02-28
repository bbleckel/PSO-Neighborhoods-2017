#include "PSO.h"

using namespace std;

int MAX_VEL_RAND_VALUE[3] = {2, 4, 4};
int MIN_VEL_RAND_VALUE = -2;
double MAX_POS_RAND_VALUE[3] = {30.0, 32.0, 5.12};
double MIN_POS_RAND_VALUE[3] = {15.0, 16.0, 2.56};
double PHI_1 = 2.05;
double PHI_2 = 2.05;


Particle::Particle(int dimension, int function) {
	for (int i = 0; i < dimension; i++) {
        // generate random value within specified range for each function
        double velRandom = (rand() % (MAX_VEL_RAND_VALUE[function] - MIN_VEL_RAND_VALUE + 1)) + MIN_VEL_RAND_VALUE;
        
        double total = MAX_POS_RAND_VALUE[function] - MIN_POS_RAND_VALUE[function];
        double ratio = ((double) rand())/RAND_MAX;
        double posRandom = total * ratio + MIN_POS_RAND_VALUE[function];
        
        velocity.push_back(velRandom);
        pBest.push_back(INT_MAX);
        position.push_back(posRandom);
        
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
    constrict = 0.7298;
    
    for(int i = 0; i < dimension; i++) {
        // fill gBest with random viable values
        double total = MAX_POS_RAND_VALUE[function] - MIN_POS_RAND_VALUE[function];
        double ratio = ((double) rand())/RAND_MAX;
        double posRandom = total * ratio + MIN_POS_RAND_VALUE[function];
        gBest.push_back(posRandom);
    }
}

PSO::~PSO() {
	
}

void PSO::updateVelocity(int index) {
    Particle p = swarm[index];
    // iterate through dimensions, updating respective velocities
    for(int i = 0; i < dimension; i++) {
        double pAttract = ((double) rand()/RAND_MAX) * PHI_1 * (swarm[index].pBest[i] - swarm[index].position[i]);
        cout << swarm[index].pBest[i] << endl;
        double gAttract = ((double) rand()/RAND_MAX) * PHI_2 * (gBest[i] - swarm[index].position[i]);
        double velChange = pAttract + gAttract;
        swarm[index].velocity[i] += velChange;
        swarm[index].velocity[i] *= constrict;
//        cout << "Particle " << i << ": " << swarm[index].velocity[i] << " to " << (swarm[index].velocity[i] + velChange) * constrict << endl;

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




