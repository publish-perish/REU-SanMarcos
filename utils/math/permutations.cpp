#include "../basic/permutations.h"





void CoefTable::makeCoTable(int diam)
{
cotSize =0;
std::ofstream colist ("./permutationtables/cotable.txt");
for(int i=diam; i >= 0; --i)
{
	for(int j=i; j >= 0; --j)
	{
		for(int k=j;k >= 0; --k) //filter them in holding tank, then add to file
		{
		if(i+j+k <= diam - 3)
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
/*
void CoefTable::makeCoTable(int diam)
{
cotSize =0;
std::ofstream colist ("./permutationtables/cotable.txt");
for(int i=0; i <= diam; i++)
{
	for(int j=0; j <= diam - i; j++)
	{
		for(int k=0; k <= diam - i -j; k++) //filter them in holding tank, then add to file
		{
		colist << boost::tuples::set_delimiter(',') << T(k, j, i) << " ";
  		cotSize++;
			
		}	
	}
}
return; 

}
*/
int CoefTable::getCotSize()
{
return cotSize;
}


int CoefTable::getMtSize()
{
return mtSize;
}

void CoefTable::makeMcoTable(int diam, int b, int c1, int c2)
{
mtSize =0;
std::ofstream mcolist ("./permutationtables/mcotable.txt");
for(int i=1; i < (diam*diam*diam / (b*c1)); ++i)
{
	for(int j=1; j < (b); ++j)
	{
		for(int k=1; k < (c1); ++k) //filter them in holding tank, then add to file
		{
			
 		    { 
 		    if(mcolist.is_open())
  		   	//std::cout << *itr;
  		   	mcolist << boost::tuples::set_delimiter(',') << T(i, j, k) << " ";
  		   	mtSize++;
  		   	}
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


void GenTable::makeGenTable(int diam)  //order: c, b, 1
{
gSize =0;
std::ofstream myfile ("./permutationtables/gentable.txt");
for(int i=2; i < (diam*diam*diam/6); i++)
{
	for(int j=2; j < (diam*diam*diam/6); j++)
	{
//      for(int k=2; k< (diam*diam*diam/6); k++)
  //    {
      holdingTank.clear();
	   holdingTank.insert(TP(i*j, i, j, 1));
		holdingTank.insert(TP(i*j, j, i, 1));
		if(myfile.is_open() && i*j < (diam*diam*diam/6) )
      {
 		std::set<T>::iterator itr = holdingTank.begin();
			while(itr != holdingTank.end())
 		    { 
 		    if(myfile.is_open())
 		    {
  		   	//std::cout << *itr;
  		   	myfile << boost::tuples::set_delimiter(',') << *itr << " ";
  		   	gSize++;
  		  	}
 		    itr++;     
	    	}	
			holdingTank.clear();
		    	//std::cout << A;
  //   	myfile << boost::tuples::set_delimiter(',') << A << " ";
     	//gSize++;
    //  }
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
