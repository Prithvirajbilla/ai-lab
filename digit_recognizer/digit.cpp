#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>

using namespace std;

int dot(vector<int> w, vector<int> entry){
  int sum = 0;
  for(int i=0;i<w.size();i++)
    sum+=w[i]*entry[i];
  return sum;
}

void print(vector<int> w){
  for(int i=0;i<w.size();i++)
    cout<<w[i]<<" ";
  cout<<endl;
}

class perceptron{
	
	int numOfInputs;
	vector<vector<int> > table;
	int numOfEntries;
	
	public:
	vector<int> weights;
	
	perceptron(int N){
		int digit = 0;
		numOfInputs = 7;
		numOfEntries = 128;
		switch(N){
			case 0:
				digit = 126;
				break;
			case 1:
				digit = 48;
				break;
			case 2:
				digit = 109;
				break;
			case 3:
				digit = 121;
				break;
			case 4:
				digit = 51;
				break;
			case 5:
				digit = 91;
				break;
			case 6:
				digit = 95;
				break;
			case 7:
				digit = 112;
				break;
			case 8:
				digit = 127;
				break;
			case 9:
				digit = 115;
				break;
			default:
				digit =-1;
				cout<<"error"<<endl;
				break;
		}
		
		cout<< "Checking if the digit formed is :"<<N<<endl;
		for(int i=0; i<128; i++){
			bitset<7> x(i);
			vector<int> temp;
			if(i == digit){
				temp.push_back(-1);
				for(int j=0; j<7; j++){
					temp.push_back(x[6-j]);
				}
			}
			else{
				temp.push_back(1);
				for(int j=0; j<7; j++){
					temp.push_back(-x[6-j]);
				}
			}
			table.push_back(temp);
		}
	}
	
	void train(){		
		for(int i=0;i<numOfInputs+1;i++)
		  weights.push_back(0);

		int count = 0;
		int index = 0;
		//int steps = 0;
		int updates = 0;
		while(count!=numOfEntries){
		  if(dot(weights,table[index])>0)
		    count+=1;
		  else{
		    count = 0;
		    for(int i=0;i<numOfInputs+1;i++)
					weights[i]=weights[i]+table[index][i];
		    //print(weights);
		    //cout<<index<<endl;
		    //index = -1;
		    //updates++;
		  }
		  index = (index + 1)%(numOfEntries);
		  //steps++;
		}
		//cout<<"Weights for digit "<<N<<" are :";
		print(weights);
		
		//cout<<"Converged in "<< steps<<" steps\n";
		//cout<<"Number of updates made = "<< updates<<"\n"; 
	}
};

int main(){
	int N;
	while(1){
		vector<int> input;
		input.push_back(-1);
		cout<<"please give an inputs seperated by spaces: "<<endl;
		int temp;
		for(int i=0; i<7; i++){
			cin>>temp;
			input.push_back(temp);
		}
		for(int j=0; j<10; j++){
			N=j;
			perceptron p(N);
			p.train();
		
			if(dot(p.weights, input) > 0){
				cout<<"digit formed : "<<j<<endl;
				break;
			}
			else
				cout<<"digit is not : "<<j<<endl;
		}
	}
}
