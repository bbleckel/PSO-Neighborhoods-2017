#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include "PSO.h"

using namespace std;

int GLOBAL_NEIGHBORHOOD_INT = 0;
int RING_NEIGHBORHOOD_INT = 1;
int VON_NEUMANN_NEIGHBORHOOD_INT = 2;
int RANDOM_NEIGHBORHOOD_INT = 3;

int ROSENBROCK_FUNCTION_INT = 0;
int ACKLEY_FUNCTION_INT = 1;
int RASTRIGIN_FUNCTION_INT = 2;


void printInfo() {
	cout << endl;
	cout << "Usage:\nFor Particle Swarm Optimization:\n./main neighborhood size iterations function dimensions" << endl;
	cout << "    neighborhood   = which neighborhood topology to test (string):" << endl;
	cout << "                      gl = global; every particle's neighborhood is entire swarm" << endl;
	cout << "                      ri = ring; particles imagined in a ring and neighbors are the particles to the left and right" << endl;
	cout << "                      vn = von Neumann; particles imagined in a grid and neighbors are in the four cardinal directions" << endl;
	cout << "                      ra = random; random neighborhoods created for each particle, changed on each iteration with probability 0.2" << endl;
	cout << "    size           = size of swarm (int)" << endl;
	cout << "    iterations     = number of iterations (int)" << endl;
	cout << "    function       = which function to optimize (string):" << endl;
	cout << "                      rok = Rosenbrock" << endl;
	cout << "                      ack = Ackley" << endl;
	cout << "                      ras = Rastrigin" << endl;
	cout << "    dimensions     = dimension of the function" << endl;
	cout << endl;
}

struct tests {
	double val;
	vector<double> vect;
};

bool compare(tests i, tests j) {return (i.val < j.val); }

//function used for testing. please excuse any un-documented code, it
//was made hastily and changed often. not to be used in normal use of the
//program
void testCases() {
	int neighborhood[4] = {GLOBAL_NEIGHBORHOOD_INT, RING_NEIGHBORHOOD_INT, VON_NEUMANN_NEIGHBORHOOD_INT, RANDOM_NEIGHBORHOOD_INT};
	string strNeighborhood[4] = {"Global", "Ring", "von Neumann", "Random"};
	int swarmSize[3] = {16, 30, 49};
	int iterations = 10000;
	int function[3] = {ROSENBROCK_FUNCTION_INT, ACKLEY_FUNCTION_INT, RASTRIGIN_FUNCTION_INT};
	string strFunction[3] = {"Rosenbrock", "Ackley", "Rastrigin"};
	int dimensions = 30;
	int num = 0;

	// vary neighborhood type
	for(int n = 0; n < 4; n++) {

		// vary swarm size
		for(int s = 0; s < 3; s++) {

			// vary function
			for(int f = 0; f < 1; f++) {

				vector<tests> gBestVect;
				//cout << "Test inputs:\nNeighborhood Type: " << strNeighborhood[n] << "\nSwarm Size: " << swarmSize[s] << "\nIterations: " << iterations << "\nFunction: " << strFunction[f] << "\nDimension: " << dimensions << endl;
				cout << "%\\ inputs: " << strNeighborhood[n] << ", " << swarmSize[s] << ", " << iterations << ", " << strFunction[f] << ", " << dimensions << endl;
				for(int j = 0; j < 20; j++) {
					//cout << "Run " << j+1 << " of 20" << endl;
					//cout << "Test inputs:\nNeighborhood Type: " << strNeighborhood[n] << "\nSwarm Size: " << swarmSize[s] << "\nIterations: " << iterations << "\nFunction: " << strFunction[f] << "\nDimension: " << dimensions << endl;

					PSO solver = PSO(neighborhood[n], swarmSize[s], iterations, function[f], dimensions);
					tests test;
					test.vect = solver.solvePSO();
					test.val = solver.gBestValue;
					gBestVect.push_back(test);
					//cout << endl;


				}

				// do things with the gBestVect here

				// print the list before sorting
				//				cout << "Before sorting: ";
				//				for(int i = 0; i < gBestVect.size(); i++) {
				//					cout << gBestVect[i].val << "  ";
				//				}
				//				cout << endl;

				// sort the list
				sort(gBestVect.begin(), gBestVect.end(), compare);

				// print the list after sorting
				//				cout << "After sorting: ";
				//				for(int i = 0; i < gBestVect.size(); i++) {
				//					cout << gBestVect[i].val << "  ";
				//				}
				//				cout << endl;

				cout << "% Median: " << gBestVect[10].val << endl;
				cout << "\\begin{filecontents*}{data" << num << ".txt}" << endl;
				for(int i = 0; i < gBestVect[10].vect.size(); i++) {
					cout << "\t" << i*1000;
					cout << "  " << gBestVect[10].vect[i] << endl;
				}
				cout << "\\end{filecontents*}" << endl;
				cout << endl << endl;
				num++;
			}

		}

	}

}

int main (int argc, char** argv) {
	int neighborhood;
	int size;
	int iterations;
	int function;
	int dimensions;

	if(argc != 6) {
		// incorrect input
		printInfo();
		exit(1);
	} else {
		// check neighborhood type
		if (!strcmp(argv[1], "gl")) {
			neighborhood = GLOBAL_NEIGHBORHOOD_INT;
		} else if (!strcmp(argv[1], "ri")) {
			neighborhood = RING_NEIGHBORHOOD_INT;
		} else if (!strcmp(argv[1], "vn")) {
			neighborhood = VON_NEUMANN_NEIGHBORHOOD_INT;
		} else if (!strcmp(argv[1], "ra")) {
			neighborhood = RANDOM_NEIGHBORHOOD_INT;
		} else {
			cout << "Invalid first argument specifying neighborhood type. Please use:" << endl;
			cout << "    neighborhood   = which neighborhood topology to test (string):" << endl;
			cout << "                      gl = global; every particle's neighborhood is entire swarm" << endl;
			cout << "                      ri = ring; particles imagined in a ring and neighbors are the particles to the left and right" << endl;
			cout << "                      vn = von Neumann; particles imagined in a grid and neighbors are in the four cardinal directions" << endl;
			cout << "                      ra = random; random neighborhoods created for each particle, changed on each iteration with probability 0.2" << endl;
			exit(1);
		}

		// check swarm size
		try {
			// stoi could throw exception if argv[2] cannot be converted; catch and show error
			size = stoi(argv[2]);
			if (size < 0) {
				cout << "Invalid second argument specifying swarm size. Swarm cannot have negative size. Please use:" << endl;
				cout << "\tsize = size of swarm (int)" << endl;
				return 0;
			}
		} catch (invalid_argument&) {
			// catch invalid_argument error
			cout << "Invalid second argument specifying swarm size. Must be entered as integer value. Please use:" << endl;
			cout << "\tsize = size of swarm (int)" << endl;
			return 0;
		}

		try {
			iterations = stoi(argv[3]);
			if (iterations < 0) {
				cout << "Invalid second argument specifying swarm size. Swarm cannot have negative size. Please use:" << endl;
				cout << "\tsize = size of swarm (int)" << endl;
				return 0;
			}
		} catch (invalid_argument&) {
			cout << "Invalid third argument specifying number of iterations. Must be entered as integer value. Please use:" << endl;
			cout << "\titerations = number of iterations (int)" << endl;
			return 0;
		}

		// check optimization function
		if (!strcmp(argv[4], "rok")) {
			function = ROSENBROCK_FUNCTION_INT;
		} else if (!strcmp(argv[4], "ack")) {
			function = ACKLEY_FUNCTION_INT;
		} else if (!strcmp(argv[4], "ras")) {
			function = RASTRIGIN_FUNCTION_INT;
		} else {
			cout << "Invalid fourth argument specifying optimization function. Please use:" << endl;
			cout << "    function       = which function to optimize (string):" << endl;
			cout << "                      rok = Rosenbrock" << endl;
			cout << "                      ack = Ackley" << endl;
			cout << "                      ras = Rastrigin" << endl;
			exit(1);
		}

		try {
			dimensions = stoi(argv[5]);
			if (dimensions < 0) {
				cout << "Invalid fifth argument specifying number of dimensions. Cannot have negative dimensions. Please use:" << endl;
				cout << "\tdimensions = dimension of the function" << endl;
				return 0;
			}
		} catch (invalid_argument&) {
			cout << "Invalid fifth argument specifying number of dimensions. Must be entered as integer value. Please use:" << endl;
			cout << "\tdimensions = dimension of the function (int)" << endl;
			return 0;
		}
		// use this instead of the following to iterate through test cases rather than run
		// the algorithm for the specified input

		//print the users' input
		string strFunction[3] = {"Rosenbrock", "Ackley", "Rastrigin"};
		cout << "Your inputs:\nNeighborhood Type: " << neighborhood << "\nSwarm Size: " << size << "\nIterations: " << iterations << "\nFunction: " << strFunction[function] << "\nDimension: " << dimensions << endl;
		//make a new PSO object
		PSO solver = PSO(neighborhood, size, iterations, function, dimensions);
		//solve
		solver.solvePSO();
		cout << "Best found: " << solver.gBestValue << endl;
	}
}
