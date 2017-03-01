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
    // pBest stores the *position* of the best value achieved
    vector<double> pBest;
    // stores the actual value
    double pBestValue;
private:

};

class PSO {
public:
	PSO(int neighborhood, int swarmSize, int iterations, int function, int dimension);
	~PSO();
	
	/* veloctiy and position updates */
	void updateVelocity(int index);
	void updatePosition(int index);
	
	/* function evaluation */
	void eval();
	double rosenbrock(Particle x);
	double ackley(Particle x);
	double rastrigin(Particle x);
	void updateNeighborhoodBest(double currVal, Particle x);
	
	/* initialization */
	void initializeSwarm();
	
	/* general algorithm controller */
	void solvePSO();

private:
	const static int ROSENBROCK_FUNCTION_INT = 0;
	const static int ACKLEY_FUNCTION_INT = 1;
	const static int RASTRIGIN_FUNCTION_INT = 2;
	
	int swarmSize;
	int iterations;
	int dimension;
    vector<double> gBest;
    double constrict;
	double gBestValue;
	double nBest;
	int neighborhood;
	int function;
	vector<Particle> swarm;
};

#endif
