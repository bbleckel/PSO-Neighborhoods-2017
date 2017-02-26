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
	
	updateVelocity();
	updatePosition();

private:
	int swarmSize;
	int iterations;
	int dimension;
	double gBest;
	double nBest;
	string neighborhood;
	string function;
};

#endif
