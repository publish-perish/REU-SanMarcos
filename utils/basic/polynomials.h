#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include "../basic/subtraction.h"
#include "boost/tuple/tuple.hpp"


typedef boost::tuples::tuple<int, int, int> T;
typedef boost::tuples::tuple<int, int, int, int> TP;

typedef std::vector<T> Vec;

using namespace boost::tuples;

class Subtractions;

class Polynomial{

   public:

      Polynomial();
      Polynomial(TP a, T y);
      Polynomial(TP a, int, int, int, int);
      Polynomial(const Polynomial&);

      TP A;
      T Y;
      Subtractions s;

      int value()const;
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
