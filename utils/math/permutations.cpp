#include "../basic/permutations.h"
#include "boost/tuple/tuple.hpp"
#include <iterator>
#include "boost/tuple/tuple_io.hpp"
#include "boost/tuple/tuple_comparison.hpp"




void CoefTable::makeCoTable(int diam)
{
std::ofstream colist ("cotable.txt");
for(int i=0; i <= diam; i++)
{
	for(int j=0; j <= i; j++)
	{
		for(int k=0; k <= j; k++) //filter them in holding tank, then add to file
		{
		if(i+j+k <= diam)
		{
			holdingTank.clear();
			holdingTank.insert(T(i, j, k));
			holdingTank.insert(T(i, k, j));
			holdingTank.insert(T(j, i, k));
			holdingTank.insert(T(j, k, i));
			holdingTank.insert(T(k, i, j));
			holdingTank.insert(T(k, j, i));
			std::set<T>::iterator itr = holdingTank.begin();
			while(itr != holdingTank.end())
 		    { 
 		    if(colist.is_open())
 		    {
  		   	std::cout << *itr;
  		   	colist << *itr;
  		  	}
 		    itr++;     
	    	}	
			holdingTank.clear();
		}			
		}	
	}
}
//coCount =0;
colist.close();
return;
}


void CoefTable::makeMcoTable(int coefBound)
{
std::ofstream mcolist ("mcotable.txt");
for(int i=0; i < coefBound; i++)
{
	for(int j=0; j <= i; j++)
	{
		for(int k=0; k <= j; k++) //filter them in holding tank, then add to file
		{
			holdingTank.clear();
			holdingTank.insert(T(i, j, k));
			holdingTank.insert(T(i, k, j));
			holdingTank.insert(T(j, i, k));
			holdingTank.insert(T(j, k, i));
			holdingTank.insert(T(k, i, j));
			holdingTank.insert(T(k, j, i));
			std::set<T>::iterator itr = holdingTank.begin();
			while(itr != holdingTank.end())
 		    { 
 		    if(mcolist.is_open())
 		    {
  		   	std::cout << *itr;
  		   	mcolist << *itr;
  		  	}
 		    itr++;     
	    	}	
			holdingTank.clear();			
		}	
	}
}
//coCount =0;
mcolist.close();
return;
}
/*
void CoefTable::filter(int x, int y, int z)
{
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
     if(colist.is_open())
     {
     	std::cout << *itr;
     	colist << *itr;
     }
       itr++;
       //coefList.push_back(*itr);       
     }
holdingTank.clear();
return;
}
*/
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
	for(int j=2; j < i; j++)
	{
	T A = T(1,j,i);
		if(myfile.is_open())
     {
     	std::cout << A;
     	myfile << A;
     }
	}
}
//genCount=0;
myfile.close();
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
