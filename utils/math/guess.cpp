#include guess.h //can the complier find guess.h?
#include "boost/tuple/tuple.hpp"
typedef boost::tuple<int, int, int> tuple
typedef vector< tuple<int,int, int> > tuple_list;





int CoefTable::makeCoefTable()
{

for(int i=0; i < genBound; i++)
{
	for(int j=0; j <= (genBound-i); j++)
	{
		for(int k=0; k <= (genBound -i -j); k++)
		{
			coefList.push_back(tuple(i, j, k);
		}	
	}
}
count =0;
return 0;
}

int CoefTable::size()
{
return coefList.size();
}


tuple CoefTable::guessCoef()
{
tuple Q= coefList.at(count);
count++;
return Q;
}




int GenTable::makeGenTable()
{
for(int i=2; i < genBound); i++)
{
	for(int j=1; j < i; j++)
	{
		genList.push_back(tuple(1, i, j));
	}
}
count=0;
return 0;
}

int GenTable::size()
{
return genList.size();
}

tuple GenTable::guessGen()
{
tuple A= genList.at(count);
count++;
return A;
}

