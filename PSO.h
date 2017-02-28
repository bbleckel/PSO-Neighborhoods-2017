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

class PSO {
public:
	PSO(string neighborhood, int swarmSize, int iterations, string function, int dimension);
	~PSO();
	
	/* veloctiy and position updates */
	void updateVelocity();
	void updatePosition();
	
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
	string neighborhood;
	string function;
	//vector<particle> swarm;
};

/* particle class */
class particle {
public:
	particle(int dimension);
	~particle();
private:
	double pBest;
	vector<double> velocity;
	double posX;
	double posY;
};

#endif
