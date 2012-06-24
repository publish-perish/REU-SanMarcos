#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <map>
//#include "../basic/tuple.h"
#include "boost/tuple/tuple.hpp"

//typedef Tuple<double, 3> T;
typedef boost::tuples::tuple<double, double, double> T;
typedef std::vector<T> Vec; 

class Polynomial{

   public:

      Polynomial(T &a, T &m, T &q): A(a), Q(q), M(m){}

      T A;
      T M;
      T Q;

};


#endif
