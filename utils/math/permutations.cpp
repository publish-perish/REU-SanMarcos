#include "../basic/permutations.h"





void CoefTable::makeCoTable(int diam)
{
cotSize =0;
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
  		   	//std::cout << *itr;
  		   	colist << boost::tuples::set_delimiter(',') << *itr << " ";
  		   	cotSize++;
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


int CoefTable::getCotSize()
{
return cotSize;
}


int CoefTable::getMtSize()
{
return mtSize;
}

void CoefTable::makeMcoTable(int coefBound)
{
mtSize =0;
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
  		   	//std::cout << *itr;
  		   	mcolist << boost::tuples::set_delimiter(',') << *itr << " ";
  		   	mtSize++;
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
gSize =0;
std::ofstream myfile ("gentable.txt");
for(int i=3; i < genBound; i++)
{
	for(int j=2; j < i; j++)
	{
	T A = T(1,j,i);
		if(myfile.is_open())
     {
     	//std::cout << A;
     	myfile << boost::tuples::set_delimiter(',') << A << " ";
     	gSize++;
     }
	}
}
//genCount=0;
myfile.close();
return;
}


int GenTable::getGsize()
{
return gSize;
}
/*
T GenTable::guessGen()
{
T A= genList.at(genCount);
genCount++;
return A;
}
*/



T getGens()
{
T A;
cin >> A;
return A;
}
