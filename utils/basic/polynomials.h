#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "tuple.h"
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include "subtraction.h"










//typedef boost::tuples::tuple<int, int, int, int, int> TP;


typedef std::vector<T5> Vec;



class Subtractions;

class Polynomial{

   public:

      Polynomial();

      //Polynomial(T &a, T &y);
      //Polynomial(T a, int, int, int);
      Polynomial(T5 a, T5 y);
      Polynomial(T5 a, int, int, int, int, int);
      Polynomial(const Polynomial&);

      T5 A;
      T5 Y;
      Subtractions s;


      int value()const;
      int sum()const;
      bool wellFormed()const;

      bool operator==(const Polynomial&);
      bool operator>=(const Polynomial&);
      bool operator!=(const Polynomial&);
      bool operator!=(int);
      Polynomial operator=(const Polynomial&);

      Polynomial operator-(Polynomial);
      Polynomial borrowB(Polynomial);
      Polynomial borrowC(Polynomial);

      friend std::ostream& operator<<(std::ostream&, const Polynomial&);
      friend std::ofstream& operator<<(std::ofstream&, const Polynomial&);
};


#endif
