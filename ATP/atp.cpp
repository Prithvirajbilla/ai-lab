#include <iostream>
#include <string>

using namespace std;

class WFF
{
public:
	WFF * lhs;
	WFF * rhs;
	char Symbol;

	WFF(string r)
	{
		read(r);
	}

	WFF(char a)
	{
		init(a);
	}

	void init(a)
	{
		lhs = NULL;
		rhs = NULL;
		Symbol = a;
	}

	void read(string formula)
	{
		if(formula[0]=='(')
		{

		}
		else
		{
			// lhs = WFF(formula[0]);
			WFF * l = new WFF(formula[0]);
			lhs = l;
		}
	}
};