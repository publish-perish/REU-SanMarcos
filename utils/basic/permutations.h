#ifndef P_H
#define P_H
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <iterator>
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_io.hpp"
#include "boost/tuple/tuple_comparison.hpp"

using namespace std;

typedef boost::tuples::tuple<int, int, int> T;
typedef std::vector<T> Vec;

class MCoTable{
   
   public:

      void makeMCoTable(const int, int, float);

      Vec MCoeffs;
      size_t MTableSize()const {return MCoeffs.size();};
};

class XCoTable{

   public:

      void makeXCoTable(int);

      Vec XCoeffs;
      set<T> holdingTank;
      size_t XTableSize()const {return XCoeffs.size();};
};

class GenTable{

   public:

      void makeGenTable(int);

      Vec Generators;
      size_t GenTableSize()const {return Generators.size();};
};
#endif
