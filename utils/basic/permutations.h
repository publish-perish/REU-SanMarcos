#ifndef P_H
#define P_H
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <iterator>
#include "../basic/tuple.h"
using namespace std;

//typedef boost::tuples::tuple <int, int, int, int, int> T;

class Table{
   
   public:

      int makeSTable();
      int makeITable();
      int makeTTable();
      int makeLTable();

      int Ssize;
      int Isize;
      int Tsize;
      int Lsize;
};

#endif
