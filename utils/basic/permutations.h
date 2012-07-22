#ifndef P_H
#define P_H
#include "tuple.h"
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <iterator>


using namespace std;


typedef Tuple<int, 5> T5;


class MCoTable{
   
   public:

      void makeMCoTable(const int, int, int, int, int);
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
