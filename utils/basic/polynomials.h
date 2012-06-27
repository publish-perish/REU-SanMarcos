#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include "../basic/subtraction.h"
#include "boost/tuple/tuple.hpp"


typedef boost::tuples::tuple<int, int, int> T;
typedef std::vector<T> Vec;

using namespace boost::tuples;

class Subtractions;

class Polynomial{

   public:

      Polynomial();
      Polynomial(T a, T y);
      Polynomial(T a, int, int, int);
      Polynomial(const Polynomial&);

      T A, Y;
      Subtractions s;

      T value()const;
      int sum()const;
      bool wellFormed()const;

      bool operator==(const Polynomial&);
      bool operator>=(const Polynomial&);
      Polynomial operator=(const Polynomial&);

      Polynomial operator-(Polynomial);
      Polynomial borrowB(Polynomial);
      Polynomial borrowC(Polynomial);

      friend std::ostream& operator<<(std::ostream&, const Polynomial&);
      friend std::ofstream& operator<<(std::ofstream&, const Polynomial&);
};

#endif
