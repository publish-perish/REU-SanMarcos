#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include "../basic/subtraction.h"
#include "boost/tuple/tuple.hpp"

<<<<<<< HEAD

typedef boost::tuples::tuple<int, int, int> T;
typedef std::vector<T> Vec;
=======
//typedef Tuple<double, 3> T;
typedef boost::tuples::tuple<double, double, double> T;
typedef std::vector<T> Vec; 
>>>>>>> 0618ae94dd968919865d43b487264a0d230ff5c6

using namespace boost::tuples;

class Subtractions;

class Polynomial{

   public:

<<<<<<< HEAD
      Polynomial();
      Polynomial(T a, T y);
      Polynomial(T a, int, int, int);
      Polynomial(const Polynomial&);

      T A, Y;
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

=======
      Polynomial(T &a, T &m, T &q): A(a), Q(q), M(m){}

      T A;
      T M;
      T Q;

};


>>>>>>> 0618ae94dd968919865d43b487264a0d230ff5c6
#endif
