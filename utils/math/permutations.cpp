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
			for(int l = k; l >= 0; --l)
			{
				if(i+j+k <= diam - 4) //k
				{
				holdingTank.clear();
				holdingTank.insert(TP(i, j, k, l));
				holdingTank.insert(TP(i, k, j, l));
				holdingTank.insert(TP(j, i, k, l));
				holdingTank.insert(TP(j, k, i, l));
				holdingTank.insert(TP(k, i, j, l));
				holdingTank.insert(TP(k, j, i, l));
				holdingTank.insert(TP(i, j, l, k));
				holdingTank.insert(TP(i, k, l, j));
				holdingTank.insert(TP(j, i, l, k));
				holdingTank.insert(TP(j, k, l, i));
				holdingTank.insert(TP(k, i, l, j));
				holdingTank.insert(TP(k, j, l, i));
				holdingTank.insert(TP(i, l, j, k));
				holdingTank.insert(TP(i, l, k, j));
				holdingTank.insert(TP(j, l, i, k));
				holdingTank.insert(TP(j, l, k, i));
				holdingTank.insert(TP(k, l, i, j));
				holdingTank.insert(TP(k, l, j, i));
				holdingTank.insert(TP(l, i, j, k));
				holdingTank.insert(TP(l, i, k, j));
				holdingTank.insert(TP(l, j, i, k));
				holdingTank.insert(TP(l, j, k, i));
				holdingTank.insert(TP(l, k, i, j));
				holdingTank.insert(TP(l, k, j, i));

				std::set<TP>::iterator itr = holdingTank.begin();
				while(itr != holdingTank.end())
 		   			{ 
 		   			if(colist.is_open())
 		    		{
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
}

//coCount =0;
colist << endl;
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

void CoefTable::makeMcoTable(int diam, int d, int c, int b)
{
mtSize =0;
std::ofstream mcolist ("./permutationtables/mcotable.txt");
for(int i=1; i < (diam*diam*diam*diam / (d*c*b)); ++i)
{
	for(int j=1; j < (d/c); ++j)
	{
		for(int k=1; k < (c/b); ++k) //filter them in holding tank, then add to file
		{
			for(int l=1; l < b; ++l)
			{
 		    { 
 		    if(mcolist.is_open())
  		   	//std::cout << *itr;
  		   	mcolist << boost::tuples::set_delimiter(',') << TP(i, j, k, l) << " ";
  		   	mtSize++;
  		   	}
  		   	}
		}
	}
}
//coCount =0;
mcolist << endl;
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
for(int i=2; i < (diam*diam*diam*diam/24); i++)
{
	for(int j=2; j < (diam*diam*diam*diam/24); j++)
	{
      for(int k=2; k < (diam*diam*diam*diam/24); k++)
      {
	   TP A(i*j*k, j*k, j, 1);
		if(myfile.is_open() && i*j*k < (diam*diam*diam*diam/24) ) 
      {
     	//std::cout << A;
     	myfile << boost::tuples::set_delimiter(',') << A << " ";
     	gSize++;
      }
      }
	}
}
//genCount=0;
myfile << endl;
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
