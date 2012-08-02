#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "tuple.h"
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include "subtraction.h"


typedef std::vector<T> Vec;

class Polynomial{

   public:

      Polynomial();

      //Polynomial(T &a, T &y);
      //Polynomial(T a, int, int, int);
      Polynomial(T a[], T y);
      Polynomial(T a[], int, int, int, int, int);
      Polynomial(const Polynomial&);

      Tuple<int, 6> A[6];;
      T Y;
      int s[6];

      int value()const;
      int sum()const;
      bool wellFormed()const;

      bool operator==(const Polynomial&);
      bool operator>=(const Polynomial&);
      bool operator!=(const Polynomial&);
      bool operator!=(int);
      Polynomial operator=(const Polynomial&);

      Polynomial operator-(Polynomial);

      friend std::ostream& operator<<(std::ostream&, const Polynomial&);
      friend std::ofstream& operator<<(std::ofstream&, const Polynomial&);
};


#endif
