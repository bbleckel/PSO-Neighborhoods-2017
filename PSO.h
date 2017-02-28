#ifndef PSO_H
#define PSO_H

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <ctime>
#include <climits>
#include <cmath>
#include <fstream>

using namespace std;

/* particle class */
class Particle {
public:
    Particle(int dimension, int function);
    ~Particle();
    
    vector<double> velocity;
    vector<double> position;
    vector<double> pBest;
private:

};

class PSO {
public:
	PSO(int neighborhood, int swarmSize, int iterations, int function, int dimension);
	~PSO();
	
	/* veloctiy and position updates */
	void updateVelocity(int index);
	void updatePosition(int index);
	
	/* initialization */
	void initializeSwarm();
	
	/* general algorithm controller */
	void solvePSO();

private:
	int swarmSize;
	int iterations;
	int dimension;
	double gBest;
	double nBest;
	int neighborhood;
	int function;
	vector<Particle> swarm;
};

#endif
