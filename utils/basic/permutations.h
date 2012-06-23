#ifndef P_H
#define P_H

#include "boost/tuple/tuple_comparison.hpp"
#include "boost/tuple/tuple.hpp"
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include "boost/tuple/tuple_io.hpp"
using namespace boost::tuples;

typedef tuple<double, double, double> T;



 //should never be larger than d



class CoefTable
{
public:
void makeCoefTable(int coefBound);
private:
void filter(int x, int y, int z);
std::set<T> holdingTank;
};

class GenTable
{
public:
void makeGenTable(int genBound);
};


#endif
