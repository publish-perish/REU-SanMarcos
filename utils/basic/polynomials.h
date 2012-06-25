#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include "../basic/subtraction.h"
#include "boost/tuple/tuple.hpp"

//typedef Tuple<double, 3> T;
using namespace boost::tuples;

typedef boost::tuples::tuple<int, int, int> T;
typedef std::vector<T> Vec;

using namespace boost::tuples;

class Subtractions;

class Polynomial{

   public:

      Polynomial();
      Polynomial(T a, T y);
      Polynomial(const Polynomial&);

      T A, Y;
      Subtractions s;

      T value()const;
      int sum()const;

      bool operator==(const Polynomial&);
      Polynomial operator=(Polynomial);

      Polynomial operator-(Polynomial);
      void borrowB(Polynomial&);
      void borrowC(Polynomial&);

      friend std::ostream& operator<<(std::ostream&, const Polynomial&);
      friend std::ofstream& operator<<(std::ofstream&, const Polynomial&);
};

#endif
