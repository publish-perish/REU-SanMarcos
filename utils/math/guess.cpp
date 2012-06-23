#include "guess.h"
#include "boost/tuple/tuple.hpp"
typedef boost::tuple<int, int, int> tuple
typedef vector< tuple<int,int, int> > tuple_list





void CoefTable::makeCoefTable()
{

for(int i=0; i < genBound; i++)
{
	for(int j=0; j <= i; j++)
	{
		for(int k=0; k <= j; k++)
		{
			Coeftable::filter(i, i-j, k);
		}	
	}
}
count =0;
return;
}

void CoefTable::filter(int x, int y, int z)
{
	holdingTank.clear();
	holdingTank.insert(tuple(x, y, z));
	holdingTank.insert(tuple(x, z, y));
	holdingTank.insert(tuple(y, x, z));
	holdingTank.insert(tuple(y, z, x));
	holdingTank.insert(tuple(z, x, y));
	holdingTank.insert(tuple(z, y, x));
	for(set::iterator i = holdingTank.begin(); i != holdingTank.end; i++)
     { 
       coefTable.insert(*i);       
     }
     holdingTank.clear();
	
return
}

int CoefTable::size()
{
return coefList.size();
}


tuple CoefTable::guessCoef()
{
tuple Q= coefList.at(coCount);
coCount++;
return Q;
}



void GenTable::makeGenTable()
{
for(int i=2; i < genBound); i++)
{
	for(int j=1; j < i; j++)
	{
		genList.push_back(tuple(1, i, j));
	}
}
count=0;
return;
}

int GenTable::size()
{
return genList.size();
}

tuple GenTable::guessGen()
{
tuple A= genList.at(genCount);
genCount++;
return A;
}

