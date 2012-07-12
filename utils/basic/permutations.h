#ifndef P_H
#define P_H
#include "env.h"
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <iterator>
#include "string.h"

using namespace std;

typedef boost::tuples::tuple<int, int, int> T;
typedef std::vector<T> Vec;

class MCoTable{
   
   public:

      bool makeMCoTable(const int, int, double, int);

      Vec MCoeffs;
      int size;
};

class XCoTable{

   public:

      void makeXCoTable(int, int);

      Vec XCoeffs;
      set<T> holdingTank;
      int size;
};

class GenTable{

   public:

      void makeGenTable(int);

      Vec Generators;
      int size;
};
#endif
