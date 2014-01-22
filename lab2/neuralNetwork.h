#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <math.h>

using namespace std;


class neuralNetwork
{
private:
  int nInputs, nOutputs, nHidden;

  double *inputNeurons, *outputNeurons, *hiddenNeurons;

  int *inputs;
  int *outputs;

  double **weightHidden, **weightOutput;

  double **deltaHidden, **deltaOutput;

  double learningFactor, momentumFactor;

public:
  neuralNetwork(int numIn, int numHid, int numOut)
  {
    nInputs = numIn;
    nHidden = numHid;
    nOutputs = numOut;

    inputNeurons = new double[nInputs+1];
    outputNeurons = new double[nOutputs];
    hiddenNeurons = new double[nHidden+1];

    inputs = new int[nInputs];
    outputs = new int[nOutputs];

    weightHidden = new double*[nInputs+1];
    deltaHidden = new double*[nInputs+1];
    for (int i = 0; i < nInputs+1; ++i)
    {
      weightHidden[i] = new double[nHidden]; 
      deltaHidden[i] = new double[nHidden];     
    }

    weightOutput = new double*[nHidden+1];
    deltaOutput = new double*[nHidden+1];
    for (int i = 0; i < nHidden+1; ++i)
    {
      weightOutput[i] = new double[nOutputs];
      deltaOutput[i] = new double[nOutputs];
    }
  }

  void initializeWeights()
  {
    srand (time(NULL));

    for(int i=0;i<nInputs+1;i++)
    {
      for (int j = 0; j < ; ++j)
      {
        weightHidden[i][j] = (rand()%100)/100.0;
      }
    }

    for (int i = 0; i < nHidden+1; ++i)
    {
      for (int j = 0; j < nOutputs; ++j)
      {
        weightOutput[i][j] = (rand()%100)/100.0;
      }
    }
  }

  void feedForward(double *inputs)
  {
    for (int i = 0; i < nInputs; ++i)
    {
      inputNeurons[i] = inputs[i];
    }
    inputNeurons[nInputs] = -1;

    for (int i = 0; i < nHidden; ++i)
    {
      hiddenNeurons[i] = 0;

      for (int j = 0; j <= nInputs; ++j)
      {
        hiddenNeurons[i] += weightHidden[j][i]*inputNeurons[j];
      }

      hiddenNeurons[i] = sigmoid(hiddenNeurons[i]);
    }

    for (int i = 0; i < nOutputs; ++i)
    {
      outputNeurons[i] = 0;
      for (int j = 0; j <= nHidden; ++j)
      {
        outputNeurons[i] += weightOutput[j][i]*hiddenNeurons[j];
      }

      outputNeurons[i] = sigmoid(outputNeurons[i]);
    }
  }

  void backpropagate(double *desiredValues)
  {
    
  }

  double sigmoid(double x)
  {
    return 1/(1+exp(-1*x));
  }

};


