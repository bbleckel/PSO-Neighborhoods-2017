#include "PSO.h"

using namespace std;

int MAX_VEL_RAND_VALUE[3] = {2, 4, 4};
int MIN_VEL_RAND_VALUE = -2;
double MAX_POS_RAND_VALUE[3] = {30.0, 32.0, 5.12};
double MIN_POS_RAND_VALUE[3] = {15.0, 16.0, 2.56};
double PHI_1 = 2.05;
double PHI_2 = 2.05;

int Particle::IDCounter;
int Neighborhood::IDCounter;

Particle::Particle(int dimension, int function) {
    pBestValue = INT_MAX;
    ID = IDCounter;
    IDCounter++;

	for (int i = 0; i < dimension; i++) {
		// generate random value within specified range for each function
		double velRandom = (rand() % (MAX_VEL_RAND_VALUE[function] - MIN_VEL_RAND_VALUE + 1)) + MIN_VEL_RAND_VALUE;

		double total = MAX_POS_RAND_VALUE[function] - MIN_POS_RAND_VALUE[function];
		double ratio = ((double) rand())/RAND_MAX;
		double posRandom = total * ratio + MIN_POS_RAND_VALUE[function];

		velocity.push_back(velRandom);
		pBest.push_back(posRandom);
		position.push_back(posRandom);

	}
}

Particle::~Particle() {

}

int Particle::isEqual(Particle p) {
    return p.ID == ID;
}

Neighborhood::Neighborhood(int function, int dimension) {
    size = 0;
    bestValue = INT_MAX;
    this->function = function;
    this->dimension = dimension;
    ID = IDCounter;
    IDCounter++;
    
    for(int i = 0; i < dimension; i++) {
        double total = MAX_POS_RAND_VALUE[function] - MIN_POS_RAND_VALUE[function];
        double ratio = ((double) rand())/RAND_MAX;
        double posRandom = total * ratio + MIN_POS_RAND_VALUE[function];
        bestPos.push_back(posRandom);
    }
}

Neighborhood::~Neighborhood() {
    
}

void Neighborhood::add(Particle &x) {
    neighborhood.push_back(&x);
    size++;
}

void Neighborhood::updateBest() {
    for (int i = 0; i < size; i++) {
        if (neighborhood[i]->pBestValue < bestValue) {
            // if particle's value better than neighborhood best, replace
            bestValue = neighborhood[i]->pBestValue;
            bestPos = neighborhood[i]->pBest;
        }
    }
}

void Neighborhood::reset() {
    bestPos.clear();
    neighborhood.clear();
    // reset vector values
    for(int i = 0; i < dimension; i++) {
        double total = MAX_POS_RAND_VALUE[function] - MIN_POS_RAND_VALUE[function];
        double ratio = ((double) rand())/RAND_MAX;
        double posRandom = total * ratio + MIN_POS_RAND_VALUE[function];
        bestPos.push_back(posRandom);
    }
    
    bestValue = INT_MAX;
    size = 0;
}

void Neighborhood::printNeighborhood() {
    cout << "Printing neighborhood " << ID << ":" << endl;
    for(int i = 0; i < neighborhood.size(); i++) {
        cout << neighborhood[i]->ID << endl;
    }
}

PSO::PSO(int neighborhood, int swarmSize, int iterations, int function, int dimension) {
	this->neighborhood = neighborhood;
	this->swarmSize = swarmSize;
	this->iterations = iterations;
	this->function = function;
	this->dimension = dimension;
	constrict = 0.7298;
    gBestValue = INT_MAX;

	for(int i = 0; i < dimension; i++) {
		// fill gBest with random viable values
		double total = MAX_POS_RAND_VALUE[function] - MIN_POS_RAND_VALUE[function];
		double ratio = ((double) rand())/RAND_MAX;
		double posRandom = total * ratio + MIN_POS_RAND_VALUE[function];
		gBest.push_back(posRandom);
	}
    
    for(int i = 0; i < swarmSize; i++) {
        vector<double> position;
        for(int j = 0; j < dimension; j++) {
            position.clear();
            double total = MAX_POS_RAND_VALUE[function] - MIN_POS_RAND_VALUE[function];
            double ratio = ((double) rand())/RAND_MAX;
            double posRandom = total * ratio + MIN_POS_RAND_VALUE[function];
            position.push_back(posRandom);
            
            
        }
    }
}

PSO::~PSO() {

}

void PSO::updateVelocity(int index) {
	Particle p = swarm[index];
	// iterate through dimensions, updating respective velocities
	for(int i = 0; i < dimension; i++) {
        // attraction from personal best
		double pAttract = ((double) rand()/RAND_MAX) * PHI_1 * (swarm[index].pBest[i] - swarm[index].position[i]);

        // get this particle's neighborhood best
        vector<double> partBestPosition = neighborhoodList[index].bestPos;
        // attraction from neighborhood best
		double nAttract = ((double) rand()/RAND_MAX) * PHI_2 * (partBestPosition[i] - swarm[index].position[i]);
		double velChange = pAttract + nAttract;
		swarm[index].velocity[i] += velChange;
		swarm[index].velocity[i] *= constrict;
	}
}

void PSO::updatePosition(int index) {
	// iterate through dimensions, updating respective positions based on velocity
	for(int i = 0; i < dimension; i++) {
		swarm[index].position[i] += swarm[index].velocity[i];
	}

}

/****************************/
/* Functions */

// Rosenbrock function evaluation for particle x
double PSO::rosenbrock(Particle x) {
	double val = 0;

	for (int i = 0; i < dimension - 1; i++)
		val += 100 * pow((x.position[i + 1] - pow(x.position[i], 2)), 2) + pow((x.position[i] - 1),2);

	return val;
}

// Ackley function evaluation for particle x
double PSO::ackley(Particle x) {
    
	double val = 0;
	//values need to be changed to reflect our choices
	double a = 20.0;
	double b = 0.2;
	double c = 2 * M_PI;
	
	double squaredSum = 0;
	for (int i = 0; i < dimension; i++)
		squaredSum += pow(x.position[i],2);
    
	double cosSum = 0;
	for (int i = 0; i < dimension; i++)
		cosSum += cos(c * x.position[i]);
    
	// carefully combine terms -- prone to strange arithmetic error
    double first = -a * exp(-b * sqrt(squaredSum / dimension));
    double second = exp(cosSum / dimension);
    double third = a + exp(1);

	
	return first - second + third;

}

// Rastrigin function evaluation for particle x
double PSO::rastrigin(Particle x) {
	double val = 10 * dimension;
	
	for (int i = 0; i < dimension; i++)
		val += (pow(x.position[i],2) - 10 * cos(2 * M_PI * x.position[i]));

	return val;
}

/****************************/
/* Neighborhoods */

// Global neighborhood initialization
void PSO::global() {
    // add every particle to a single neighborhood
    for(int i = 0; i < swarmSize; i++) {
        Neighborhood temp(function, dimension);
        for (int j = 0; j < swarmSize; j++) {
            temp.add(swarm[j]);
        }
        neighborhoodList.push_back(temp);
    }
}

// Ring neighborhood initialization
void PSO::ring() {

	for (int i = 0; i < swarmSize; i++) {
        Neighborhood temp(function, dimension);
		int before;
		int after;
		if (i == 0) {
            // wrap to last element if first element
			before = swarmSize - 1;
			after = i + 1;
		} else if (i + 1 == swarmSize) {
            // wrap to first element if last element
			before = i - 1;
			after = 0;
		} else {
            // neighbors are before and after
			before = i - 1;
			after = i + 1;
		}
        
        temp.add(swarm[before]);
        temp.add(swarm[i]);
        temp.add(swarm[after]);
        
        neighborhoodList.push_back(temp);
	}
}

int findNextSquare(int i) {
    // returns closest square number > i
    for(int j = i; j < INT_MAX; j++) {
        double root = sqrt(j);
        // if "floor" of root = root, j is square
        if(((int) root) == root) {
            return j;
        }
    }

    return -1;
}

// von Neumann neighborhood initialization
void PSO::vonNeumann() {
    // CURRENTLY DANGEROUS FOR NON-SQUARE #'S

	// particles as parts of a grid: neighborhood is adjacent particles (up, down, left, right)

    int rowSize = sqrt(findNextSquare(swarmSize));
    cout << "Using rowSize " << rowSize << endl;

    for(int index = 0; index < swarmSize; index++) {
        Neighborhood temp(function, dimension);
        
        // note: (x, y) = (row, col) (in conceptual grid)
        int row = floor(index / rowSize);
        int col = index - (row * rowSize);
        
        // determine coordinates of neighbors
        int neighborUpRow;
        int neighborUpCol;
        int neighborDownRow;
        int neighborDownCol;
        int neighborLeftRow;
        int neighborLeftCol;
        int neighborRightRow;
        int neighborRightCol;

        if(row == 0) {
            // wrap up
            neighborUpRow = rowSize - 1;
            neighborDownRow = row + 1;
        } else if(row == rowSize - 1) {
            // wrap down
            neighborUpRow = row - 1;
            neighborDownRow = 0;
        } else {
            neighborUpRow = row - 1;
            neighborDownRow = row + 1;
        }

        if(col == 0) {
            // wrap left
            neighborLeftCol = rowSize - 1;
            neighborRightCol = col + 1;
        } else if(col == rowSize - 1) {
            // wrap right
            neighborLeftCol = col - 1;
            neighborRightCol = 0;
        } else {
            neighborLeftCol = col - 1;
            neighborRightCol = col + 1;
        }

        // true regardless of particle position
        neighborLeftRow = row;
        neighborRightRow = row;
        neighborUpCol = col;
        neighborDownCol = col;

        // determine indices in swarm of neighbors
        int neighborUp = rowSize * neighborUpRow + neighborUpCol;
        int neighborDown = rowSize * neighborDownRow + neighborDownCol;
        int neighborLeft = rowSize * neighborLeftRow + neighborLeftCol;
        int neighborRight = rowSize * neighborRightRow + neighborLeftCol;
        
        
        // add each neighbor to neighborhood (and self)
        temp.add(swarm[index]);
        temp.add(swarm[neighborUp]);
        temp.add(swarm[neighborDown]);
        temp.add(swarm[neighborLeft]);
        temp.add(swarm[neighborRight]);
        
        neighborhoodList.push_back(temp);
    }

    // DEAL WITH NON-SQUARE NUMBERS?

}

// Random neighborhood initialization
void PSO::initializeRandomNeighborhood() {
	int k = 5;
    cout << "Here!" << endl;

	for (int i = 0; i < swarmSize; i++) {
        Neighborhood temp(function, dimension);
        // particle is in its own neighborhood
        temp.add(swarm[i]);
        cout << i << endl;
		for (int j = 0; j < k - 1; j++) {
			// get non-duplicate index
			int randIndex = getNewRandIndex(temp);
			// add the index that is not a duplicate
            temp.add(swarm[randIndex]);
		}
        neighborhoodList.push_back(temp);
	}
}

// Random neighborhood update function
void PSO::updateRandomNeighborhood() {
	int k = 5;
	double minProb = 0.2;

	for (int i = 0; i < swarmSize; i++) {
		double probability = ((double) rand()) / RAND_MAX;
		if (probability < minProb) {
			// clear neighborhood
			neighborhoodList[i].reset();
            neighborhoodList[i].add(swarm[i]);
			for (int j = 0; j < k - 1; j++) {
				// get non-duplicate index
				int randIndex = getNewRandIndex(neighborhoodList[i]);
				// add the index that isn't a duplicate to the neighborhood
                neighborhoodList[i].add(swarm[randIndex]);
			}
		}
	}
}

int PSO::getNewRandIndex(Neighborhood h) {
	int randIndex = rand() % swarmSize;

	// check to make sure that this index isn't a duplicate
	bool indexAlreadySelected = false;
	while (!indexAlreadySelected) {
		indexAlreadySelected = true;
        // iterate through particle swarm[i]'s neighborhood
		for (int n = 0; n < h.neighborhood.size(); n++) {
            Particle randPart = swarm[randIndex];
            if (h.neighborhood[n]->isEqual(randPart)){
				// if you've added the index already
				// break, get a new number, and repeat
				indexAlreadySelected = false;
				break;
			}
		}
		if (indexAlreadySelected == false) {
			randIndex = rand() % swarmSize;
		}
	}

	return randIndex;
}

// Neighborhood initialization controller
void PSO::initializeNeighborhoods() {
	if (neighborhood == RANDOM_NEIGHBORHOOD_INT) {
		initializeRandomNeighborhood();
	} else if (neighborhood == RING_NEIGHBORHOOD_INT) {
		ring();
	} else if (neighborhood == VON_NEUMANN_NEIGHBORHOOD_INT) {
		vonNeumann();
	} else {
		global();
	}
}

void PSO::updateNeighborhoodBest() {
    // iterate through neighborhoods, updating bests
    for(int i = 0; i < swarmSize; i++) {
        // update each particle's neighborhood
        neighborhoodList[i].updateBest();
    }
}

void PSO::printNeighborhoods() {
    cout << "Printing neighborhoods: " << endl;
    for(int i = 0; i < neighborhoodList.size(); i++) {
        neighborhoodList[i].printNeighborhood();
    }
}

// Evaluation controller
void PSO::eval(int index) {
    Particle p = swarm[index];
    double pVal;
    
    if (function == ROSENBROCK_FUNCTION_INT)
        pVal = rosenbrock(p);
    else if (function == ACKLEY_FUNCTION_INT)
        pVal = ackley(p);
    else
        pVal = rastrigin(p);
    
    if (pVal < p.pBestValue) {
        swarm[index].pBest = p.position;
        swarm[index].pBestValue = pVal;
    }
    
    if(pVal < gBestValue) {
        gBestValue = pVal;
        gBest = p.pBest;
    }
    updateNeighborhoodBest();
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
	initializeNeighborhoods();

	int iterRemaining = iterations;

	while(iterRemaining >= 0) {

		// iterate through particles, updating velocity & position
		for(int i = 0; i < swarmSize; i++) {
			updateVelocity(i);
			updatePosition(i);
            // evaluate at position so later particles benefit from moves before
            eval(i);
		}
        
        if (neighborhood == RANDOM_NEIGHBORHOOD_INT) {
            updateRandomNeighborhood();
        }
        cout << "gBest = " << gBestValue << endl;

        iterRemaining--;
	}

}
