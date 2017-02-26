#ifndef PARTICLE_H
#define PARTICLE_H

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

class partcile {
public:
	particle();
	~particle();
private:
	double pBest;
	double velocity;
	double psoX;
	double posY;
};

#endif
