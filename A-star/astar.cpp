#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <queue>


using namespace std;

class AstarNodeState
{
public:
	float g;
	float h;
	AstarNodeState * parent;

	AstarNodeState()
	{
		g = 0;
		h = 0;
		parent = NULL;
	}

	virtual float move_cost(AstarNodeState * state) = 0;
	virtual std::vector<AstarNodeState*> getAllNextStates() = 0;
	virtual bool equal(AstarNodeState * state) = 0;
	virtual void printState() = 0;
};


class AstarState
{
public:
	AstarNodeState  * state;
	vector<AstarNodeState> OL;
	map<AstarNodeState, float> CL;

	AstarState(AstarNodeState * a)
	{
		state = a;
	}

	virtual float heuristic(AstarNodeState * node, AstarNodeState * start, AstarNodeState * end) = 0;

	vector<AstarNodeState> search(AstarNodeState * start, AstarNodeState * end)
	{
		AstarNodeState * current = start;
		OL.push_back(*start);
		push_heap(OL.begin(), OL.end());
		while(!(OL.empty()))
		{
			pop_heap(OL.begin(), OL.end());
			*current = OL.back();
			OL.pop_back();

			if(current->equal(end))
			{
				vector<AstarNodeState> path;
				while(current->parent)
				{
					path.push_back(*current);
					current = current->parent;
				}
				path.push_back(*current);
				return path;
			}

			CL[*current] = current->g;
			for (std::vector<AstarNodeState*>::iterator i = current->getAllNextStates().begin(); i != current->getAllNextStates().end(); ++i)
			{
				AstarNodeState * node = *i;
				if(CL.find(*node)!=CL.end())
					continue;
				bool found = false;
				for(vector<AstarNodeState * >::iterator j = OL.begin(); j! = OL.end(); ++j)
				{
					if(node->equal(*j))
					{
						found = true;
						float new_g = current->g + current->move_cost(node);
						if(new_g<node->g)
						{
							node->g = new_g;
							node->parent = current;
						}
					}
				}
				if(!found)
				{
					node->g = current->g + current->move_cost(node);
					node->h = heuristic(node, start, end);
					node->parent = current;
					OL.push_back(*node);
					push_heap(OL.begin(), OL.end());
				}
			}
		}
		return NULL;
	}
};

class puzzleState : public AstarNodeState
{
public:
	vector<int> array;

	puzzleState(std::vector<int> ar)
	{
		array = ar;
	}

	std::vector<puzzleState*> getAllNextStates()
	{
		int pos;
		for(int i=0;i<9;i++)
			if(array[i]==0)
				pos = i;

		vector<puzzleState*> returnValue;
		if(pos>=3)
		{
			int ar[9];
			copyArray(ar, array);
			int temp = ar[pos];
			ar[pos] = ar[pos-3];
			ar[pos-3] = temp;
			puzzleState * p = new puzzleState(ar, g+1, this);
			returnValue.push_back(p);
		}

		if(pos<6)
		{
			int ar[9];
			copyArray(ar, array);
			int temp = ar[pos];
			ar[pos] = ar[pos+3];
			ar[pos+3] = temp;
			puzzleState * p = new puzzleState(ar, g+1, this);
			returnValue.push_back(p);
		}

		if(pos%3!=2)
		{
			int ar[9];
			copyArray(ar, array);
			int temp = ar[pos];
			ar[pos] = ar[pos+1];
			ar[pos+1] = temp;
			puzzleState * p = new puzzleState(ar, g+1, this);
			returnValue.push_back(p);
		}

		if(pos%3!=0)
		{
			int ar[9];
			copyArray(ar, array);
			int temp = ar[pos];
			ar[pos] = ar[pos-1];
			ar[pos-1] = temp;
			puzzleState * p = new puzzleState(ar, g+1, this);
			returnValue.push_back(p);
		}
		return returnValue;
	}

	float move_cost(puzzleState * state)
	{
		return 1;
	}

	bool equal(puzzleState * state)
	{
		for(int i=0;i<9;i++)
		{
			if(state->array[i]!=array[i])
			{
				return false;
			}
		}
		return true;
	}

	void printState()
	{
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++)
			{
				cout<<array[i*3 + j]<< " ";
			}
			cout<<endl;
		}
	}
};

class eightPuzzle: public AstarState
{
public:
	float heuristic(puzzleState * node, puzzleState * start, puzzleState * end)
	{
		int ans = 0;
		vector<int> array = node->array;
		for(int i = 0; i < 9; i++) {
			if(array[i] == 0) continue;
			int num = array[i];
			int row = i/3;
			int col = i%3;
			int expi = (num-1)/3;
			int expj = (num-1)%3;
			ans += abs(expi - row) + abs(expj - col);
		}
		return ans;
	}
};


int main()
{
	int start[] = {0,3,2,1,6,8,5,7,4};
	int end[] = {1,2,3,4,5,6,7,8,0};

	std::vector<int> startv(start, start+9);
	std::vector<int> endv(end, end+9);

	puzzleState startState(startv);
	puzzleState endState(endv);

	eightPuzzle game(startState);
	vector<puzzleState> path = game.search(startState, endState);
	for (std::vector<puzzleState>::iterator i = path.begin(); i != path.end(); ++i)
	{
		(*i).printState();
		cout<<endl;
	}

	return 0;
}