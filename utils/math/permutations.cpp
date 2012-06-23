#include "../basic/permutations.h"
#include "boost/tuple/tuple.hpp"
#include <iterator>





void CoefTable::makeCoefTable(int coefBound)
{

for(int i=0; i < coefBound; i++)
{
	for(int j=0; j <= i; j++)
	{
		for(int k=0; k <= j; k++)
		{
			filter(i, i-j, k);
		}	
	}
}
//coCount =0;
return;
}

void CoefTable::filter(int x, int y, int z)
{
	std::ofstream myfile ("cotable.txt");
	holdingTank.clear();
	holdingTank.insert(T(x, y, z));
	holdingTank.insert(T(x, z, y));
	holdingTank.insert(T(y, x, z));
	holdingTank.insert(T(y, z, x));
	holdingTank.insert(T(z, x, y));
	holdingTank.insert(T(z, y, x));
	std::set<T>::iterator itr = holdingTank.begin();
	while(itr != holdingTank.end())
     { 
     if(myfile.is_open())
     {
     	std::cout << *itr;
     	myfile << *itr;
     }
       itr++;
       //coefList.push_back(*itr);       
     }
holdingTank.clear();
myfile.close();
return;
}
/*
int CoefTable::size()
{
return coefList.size();
}


T CoefTable::guessCoef()
{
T Q= coefList.at(coCount);
coCount++;
return Q;
}
*/


void GenTable::makeGenTable(int genBound)
{
std::ofstream myfile ("gentable.txt");
for(int i=3; i < genBound; i++)
{
	for(int j=1; j < i; j++)
	{
	T A = (1,j,i);
		if(myfile.is_open())
     {
     	std::cout << A;
     	myfile << A;
     }
	}
}
//genCount=0;
return;
}
/*
int GenTable::size()
{
return genList.size();
}

T GenTable::guessGen()
{
T A= genList.at(genCount);
genCount++;
return A;
}
*/
