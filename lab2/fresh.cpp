#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include <cstdlib>

using namespace std;

class NeuralNetwork
{
private:
	int nLayers; // Number of layers

	vector<int> nNeurons; // Number of neurons in each layer

	vector<vector<double> > nValue; // Values of the neurons in each layer

	vector<vector<vector<double> > > nWeights; // Weights between each layer

	vector<vector<vector<double> > > nDelta; // Delta values between each layer

	double error; // Error of the neural network

public:
	NeuralNetwork(int numLayers, vector<int> numNeurons)
	{
		nLayers = numLayers;
		nNeurons = numNeurons;

		initializeWeights();
	}

	void initializeWeights()
	{
		srand (time(NULL));
		for(int j=1;j<nLayers;j++)
		{

		}
	}
};