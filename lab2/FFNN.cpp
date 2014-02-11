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
  int nInputs, nOutputs;

  int nHiddenLayers;
  vector<int> nHidden;

  double *inputNeurons, *outputNeurons, **hiddenNeurons;

  double ***weightHidden, **weightOutput;

  double ***deltaHidden, **deltaOutput;

  double *outputError, **hiddenError;

  double learningFactor, momentumFactor;

public:
  neuralNetwork(int numIn, int numHiddenLayers, int numOut, double lf, double mf, vector<int> v)
  {
    nInputs = numIn;
    nHiddenLayers = numHiddenLayers;
    nOutputs = numOut;

    learningFactor = lf;
    momentumFactor = mf;

    nHidden = v;

    inputNeurons = new double[nInputs+1];
    outputNeurons = new double[nOutputs];

    hiddenNeurons = new double*[nHiddenLayers+1];
    for(int i=0;i<nHiddenLayers;i++)
    {
      hiddenNeurons[i] = new double[nHidden[i]];
    }

    // weightHidden = new double**[nInputs+1];
    // deltaHidden = new double**[nInputs+1];
    // for (int i = 0; i < nInputs+1; ++i)
    // {
    //   weightHidden[i] = new double[nHidden]; 
    //   deltaHidden[i] = new double[nHidden]; 
    //   for(int j=0;j<nHidden;j++)
    //   {
    //     weightHidden[i][j] = 0;
    //     deltaHidden[i][j] = 0;
    //   }    
    // }

    weightHidden = new double**[nHiddenLayers];
    deltaHidden = new double**[nHiddenLayers];
    for(int i=0;i<nHiddenLayers;i++)
    {
      if(i==0) {
        weightHidden[i] = new double*[nInputs+1];
        deltaHidden[i] = new double*[nInputs+1];
        for(int j=0;j<nInputs+1;j++)
        {
          weightHidden[i][j] = new double[nHidden[i]];
          deltaHidden[i][j] = new double[nHidden[i]];
        }
      }
      else  {
        weightHidden[i] = new double*[nHidden[i-1]+1];
        deltaHidden[i] = new double*[nHidden[i-1]+1];
        for(int j=0;j<nHidden[i-1]+1;j++)
        {
          weightHidden[i][j] = new double[nHidden[i]];
          deltaHidden[i][j] = new double[nHidden[i]];
        }
      }
    }


    weightOutput = new double*[nHidden[nHiddenLayers-1]+1];
    deltaOutput = new double*[nHidden[nHiddenLayers-1]+1];
    for (int i = 0; i < nHidden[nHiddenLayers-1]+1; ++i)
    {
      weightOutput[i] = new double[nOutputs];
      deltaOutput[i] = new double[nOutputs];
      for(int j=0;j<nOutputs;j++)
      {
        weightOutput[i][j] = 0;
        deltaOutput[i][j] = 0;
      }
    }

    // hiddenError = new double*[nHidden+1];
    // for (int i = 0; i < nHidden+1; ++i)
    // {
    //   hiddenError[i] = 0;
    // }

    hiddenError = new double*[nHiddenLayers];
    for(int i=0;i<nHiddenLayers;i++)
    {
      hiddenError[i] = new double[nHidden[i]];
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
    for(int k=0;k<nHiddenLayers;k++)
    {
      if(k==0){
        for(int i=0;i<nInputs+1;i++)
        {
          for (int j = 0; j < nHidden[k]; ++j)
          {
            weightHidden[k][i][j] = (rand()%30)/30.0;
          }
        }
      }
      else {
        for(int i=0;i<nHidden[k-1]+1;k++)
        {
          for(int j=0;j<nHidden[k];j++)
          {
            weightHidden[k][i][j] = (rand()%30)/30.0;
          }
        }
      }
    }

    for (int i = 0; i < nHidden[nHiddenLayers-1]+1; ++i)
    {
      for (int j = 0; j < nOutputs; ++j)
      {
        weightOutput[i][j] = (rand()%30)/30.0;
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


    for(int k=0;k<nHiddenLayers;k++){

      for (int i = 0; i < nHidden[k]; ++i)
      {
        hiddenNeurons[k][i] = 0;
        if(k==0){
          for (int j = 0; j <= nInputs; ++j)
          {
            hiddenNeurons[k][i] += weightHidden[k][j][i]*inputNeurons[j];
          }
        }
        else {
          for(int j=0; j<=nHidden[k-1];j++)
          {
            hiddenNeurons[k][i] += weightHidden[k][j][i]*hiddenNeurons[k][j];
          }
        }

        hiddenNeurons[i] = sigmoid(hiddenNeurons[i]);
      }
      hiddenNeurons[nHidden[k]] = -1;
    }


    for (int i = 0; i < nOutputs; ++i)
    {
      outputNeurons[i] = 0;
      for (int j = 0; j <= nHidden[nHiddenLayers-1]; ++j)
      {
        outputNeurons[i] += weightOutput[j][i]*hiddenNeurons[nHiddenLayers-1][j];
      }

      outputNeurons[i] = sigmoid(outputNeurons[i]);
    }
  }

  void backpropagate(double *desiredValues)
  {
    for (int i = 0; i < nOutputs; ++i)
    {
      for (int j = 0; j < nHidden[nHiddenLayers-1]+1; ++j)
      {
        deltaOutput[j][i] = momentumFactor*deltaOutput[j][i] + learningFactor*(desiredValues[i]-outputNeurons[i])*outputNeurons[i]*(1- outputNeurons[i])*hiddenNeurons[nHiddenLayers-1][j];
      }
    }

    // for(int i=0; i<nHidden; ++i)
    // {
    //   for(int j=0; j<nInputs+1;++j)
    //   {
    //     double val = momentumFactor*deltaHidden[j][i];
    //     deltaHidden[j][i] = 0;
    //     for(int k=0;k<nOutputs;k++)
    //     {
    //       deltaHidden[j][i] += weightOutput[i][k]*(desiredValues[k]-outputNeurons[k])*outputNeurons[i]*(1- outputNeurons[i]);
    //     }
    //     deltaHidden[j][i] *= learningFactor*inputNeurons[j]*hiddenNeurons[i]*(1 - hiddenNeurons[i]);
    //     deltaHidden[j][i] += val;
    //   }
    // }

    

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
