#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <map>
//#include "../basic/tuple.h"
#include "boost/tuple/tuple.hpp"

//typedef Tuple<double, 3> T;
typedef boost::tuples::tuple<int, int, int> T;
typedef std::vector<T> Vec;

using namespace boost::tuples;

class Polynomial{

   public:

      Polynomial();
      Polynomial(T &a, T &y); 

      T A, Y;

      T value()const;
      int sum()const;
};

#endif
