#ifndef P_H
#define P_H


//#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include "boost/tuple/tuple.hpp"
#include <iterator>

using namespace std;

typedef boost::tuples::tuple<int, int, int> T;







class CoefTable
{
public:
void makeCoTable(int diam);
void makeMcoTable(int coefBound);
private:
//void filter(int x, int y, int z);
set<T> holdingTank;
};

class GenTable
{
public:
void makeGenTable(int genBound);
};


#endif
