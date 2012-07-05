#ifndef P_H
#define P_H


//#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <iterator>
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_io.hpp"
#include "boost/tuple/tuple_comparison.hpp"

using namespace std;

typedef boost::tuples::tuple<int, int, int> T;
typedef boost::tuples::tuple<int, int, int, int> TP;


class CoefTable
{
public:
void makeCoTable(int diam);
void makeMcoTable(int diam, int b, int c1);
//T getNextCoefs();
//T getNextMco();
int getCotSize();
int getMtSize();
private:
//void filter(int x, int y, int z);
set<T> holdingTank;
int cotSize;
int mtSize;
};

class GenTable
{
public:
void makeGenTable(int diam);
//T getNextGen();
int getGsize();
set<TP> holdingTank;
private:
int gSize;
};



T getNextGens(int index);


#endif
