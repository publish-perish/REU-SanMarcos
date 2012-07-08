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

typedef boost::tuples::tuple<int, int, int, int> T;

class SITable{
   
   public:

      int makeSITables();

      int Ssize;
      int Isize;
};
class TTable{
   
   public:

      int makeTTable();

      int size;
};

#endif
