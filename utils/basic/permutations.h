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


typedef boost::tuples::tuple<int, int, int, int> TP;



class MCoTable{
   
   public:

      void makeMCoTable(const int, int, int, int);
      //int getMtsize();

      //Vec MCoeffs;
      int size;
};

class XCoTable{

   public:


      void makeXCoTable(int);
      //int getXsize();
      int size;
};



class GenTable{

   public:

      void makeGenTable(int);
      //int getGsize();

     // Vec Generators;
      int size;
};
#endif
