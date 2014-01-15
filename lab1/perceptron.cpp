#include <iostream>
#include <vector>
#include <cmath>

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

int main(){
  int numOfInputs;
  //cout<<"Please enter the number of inputs\n";
  cin>>numOfInputs;
  vector<vector<int> > table;
  int numOfEntries = pow(2,numOfInputs);
  for(int i=0;i<numOfEntries;i++){
    //cout<<"Enter the input values separated by spaces \n";
    vector<int> temp;
    temp.push_back(-1);
    for(int j=0;j<numOfInputs;j++){
      int x;
      cin>>x;
      temp.push_back(x);
    }
    //cout<<"Enter the output value\n";
    int y;
    cin>>y;
    if(y==0){
      for(int j=0;j<numOfInputs+1;j++)
	temp[j] = -temp[j];
    }
    table.push_back(temp);
  }
  
  vector<int> w;
  for(int i=0;i<numOfInputs+1;i++)
    w.push_back(0);

  int count = 0;
  int index = 0;
  int steps = 0;
  int updates = 0;
  while(count!=numOfEntries){
    if(dot(w,table[index])>0)
      count+=1;
    else{
      count = 0;
      for(int i=0;i<numOfInputs+1;i++)
	w[i]=w[i]+table[index][i];
      print(w);
      //cout<<index<<endl;
      //index = -1;
      updates++;
    }
    index = (index + 1)%(numOfEntries);
    steps++;
  }
  print(w);
  cout<<"Converged in "<< steps<<" steps\n";
  cout<<"NUmber of updates made = "<< updates<<"\n"; 
  return 0;
}
