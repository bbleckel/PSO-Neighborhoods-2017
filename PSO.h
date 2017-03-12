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
	static int IDCounter;
	
	Particle(int dimension, int function);
	~Particle();
	
	vector<double> velocity;
	vector<double> position;
	// pBest stores the *position* of the best value achieved
	vector<double> pBest;
	// stores the actual value
	double pBestValue;
	
	int isEqual(Particle p);
	
	// unique ID's allow isEqual
	int ID;
	
};

class Neighborhood {
public:
	static int IDCounter;
	
	Neighborhood(int function, int dimension);
	~Neighborhood();
	void add(Particle &x);
	void updateBest();
	void reset();
	void printNeighborhood();
	
	vector<double> bestPos;
	vector<Particle*> neighborhood;
	
	double bestValue;
	int size;
	int ID;
	int function;
	int dimension;
};

class PSO {
public:
	PSO(int neighborhood, int swarmSize, int iterations, int function, int dimension);
	~PSO();
	
	/* veloctiy and position updates */
	void updateVelocity(int index);
	void updatePosition(int index);
	
	/* neighborhoods */
	void initializeNeighborhoods();
	void global();
	void ring();
	void vonNeumann();
	void initializeRandomNeighborhood();
	void updateRandomNeighborhood();
	int getNewRandIndex(Neighborhood h);
	
	/* function evaluation */
	void eval(int index);
	double rosenbrock(Particle x);
	double ackley(Particle x);
	double rastrigin(Particle x);
	void updateNeighborhoodBest();
	void printNeighborhoods();
	
	/* initialization */
	void initializeSwarm();
	
	/* general algorithm controller */
	vector<double> solvePSO();
	
	// need to be able to access this from the tester
	double gBestValue;
	
private:
	const static int GLOBAL_NEIGHBORHOOD_INT = 0;
	const static int RING_NEIGHBORHOOD_INT = 1;
	const static int VON_NEUMANN_NEIGHBORHOOD_INT = 2;
	const static int RANDOM_NEIGHBORHOOD_INT = 3;
	
	const static int ROSENBROCK_FUNCTION_INT = 0;
	const static int ACKLEY_FUNCTION_INT = 1;
	const static int RASTRIGIN_FUNCTION_INT = 2;
	
	int swarmSize;
	int iterations;
	int dimension;
	// position of all-time best particle?
	vector<double> gBest;
	vector<Neighborhood> neighborhoodList;
	
	double constrict;
	double nBest;
	int neighborhood;
	int function;
	vector<Particle> swarm;
};

#endif
