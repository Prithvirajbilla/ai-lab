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

  double *outputError, *hiddenError;

  double learningFactor, momentumFactor;

public:
  neuralNetwork(int numIn, int numHid, int numOut, double lf, double mf)
  {
    nInputs = numIn;
    nHidden = numHid;
    nOutputs = numOut;

    learningFactor = lf;
    momentumFactor = mf;

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
      for(int j=0;j<nHidden;j++)
      {
        weightHidden[i][j] = 0;
        deltaHidden[i][j] = 0;
      }    
    }

    weightOutput = new double*[nHidden+1];
    deltaOutput = new double*[nHidden+1];
    for (int i = 0; i < nHidden+1; ++i)
    {
      weightOutput[i] = new double[nOutputs];
      deltaOutput[i] = new double[nOutputs];
      for(int j=0;j<nOutputs;j++)
      {
        weightOutput[i][j] = 0;
        deltaOutput[i][j] = 0;
      }
    }

    hiddenError = new double[nHidden+1];
    for (int i = 0; i < nHidden+1; ++i)
    {
      hiddenError[i] = 0;
    }

    outputError = new double[nOutputs+1];
    for (int i = 0; i < nOutputs+1; ++i)
    {
      outputError[i] = 0;
    }
  }

  void initializeWeights()
  {
    srand (time(NULL));

    for(int i=0;i<nInputs+1;i++)
    {
      for (int j = 0; j < nHidden; ++j)
      {
        weightHidden[i][j] = (rand()%10)/10.0;
      }
    }

    for (int i = 0; i < nHidden+1; ++i)
    {
      for (int j = 0; j < nOutputs; ++j)
      {
        weightOutput[i][j] = (rand()%10)/10.0;
      }
    }
  }

  double* feedInputs(double *inputs)
  {
    feedForward(inputs);
    return outputNeurons;
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
    hiddenNeurons[nHidden] = -1;

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
    for (int i = 0; i < nOutputs; ++i)
    {
      for (int j = 0; j < nHidden+1; ++j)
      {
        deltaOutput[j][i] = momentumFactor*deltaOutput[j][i] + learningFactor*(desiredValues[i]-outputNeurons[i])*outputNeurons[i]*(1- outputNeurons[i])*hiddenNeurons[j];
      }
    }

    for(int i=0; i<nHidden; ++i)
    {
      for(int j=0; j<nInputs+1;++j)
      {
        deltaHidden[j][i] = momentumFactor*deltaHidden[j][i];
        for(int k=0;k<nOutputs;k++)
        {
          deltaHidden[j][i] += weightOutput[i][k]*(desiredValues[k]-outputNeurons[k])*outputNeurons[i]*(1- outputNeurons[i]);
        }
        deltaHidden[j][i] *= learningFactor*inputNeurons[j]*hiddenNeurons[i]*(1 - hiddenNeurons[i]);
      }
    }

    updateWeights();
  }

  void updateWeights()
  {
    for (int i = 0; i <= nInputs; ++i)
    {
      for (int j = 0; j < nHidden; ++j)
      {
        weightHidden[i][j] += deltaHidden[i][j];
      }
    }

    for (int i = 0; i <= nHidden; ++i)
    {
      for (int j = 0; j < nOutputs; ++j)
      {
        weightOutput[i][j] += deltaOutput[i][j];
      }
    }
  }

  double sigmoid(double x)
  {
    return 1/(1+exp(-1*x));
  }

  void printWeights()
  {
    for(int i=0;i<nInputs+1;i++)
      for(int j=0;j<nHidden;j++)
        cout<<i<<" "<<j<<" "<<weightHidden[i][j]<<endl;
    cout<<endl;

    for(int i=0;i<nHidden+1;i++)
      for(int j=0;j<nOutputs;j++)
        cout<<i<<" "<<j<<" "<<weightOutput[i][j]<<endl;
    cout<<endl;
  }

};

int main()
{
  neuralNetwork n(2,2,1,0.1,0.1);
  n.initializeWeights();

  double **inputs;
  inputs = new double*[4];
  for(int i=0;i<4;i++)
    inputs[i] = new double[2];

  inputs[0][0] = 0;
  inputs[0][1] = 0;
  inputs[1][0] = 0;
  inputs[1][1] = 1;
  inputs[2][0] = 1;
  inputs[2][1] = 0;
  inputs[3][0] = 1;
  inputs[3][1] = 1;

  double **outputs;
  outputs = new double*[4];
  for (int i = 0; i < 4; ++i)
  {
    outputs[i] = new double[1];
  }

  outputs[0][0] = 0;
  outputs[1][0] = 1;
  outputs[2][0] = 1;
  outputs[3][0] = 0;

  int i=0;
  while(i<2000000)
  {
    n.feedForward(inputs[i%4]);
    n.backpropagate(outputs[i%4]);
    i++;
  }

  n.printWeights();
  cout<<endl;

  for(int i=0;i<4;i++)
  {
    cout<<inputs[i][0]<<" "<<inputs[i][1]<<" ";
    double *output;
    output = n.feedInputs(inputs[i]);
    cout<<output[0]<<endl;
  }
  return 0;
}
