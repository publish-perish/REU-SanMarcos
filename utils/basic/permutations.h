#ifndef P_H
#define P_H
#include "tuple.h"
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <iterator>
#include "string.h"
#include <sstream>

using namespace std;

typedef std::vector<T> Vec;
typedef std::vector<T4> Vec4;

class MCoTable{
   
   public:

      void makeMCoTable(const int, int, int, int);

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

      Vec4 Generators;
      int size;
};
#endif
