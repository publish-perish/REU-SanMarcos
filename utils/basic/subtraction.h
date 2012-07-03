<<<<<<< HEAD
#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_comparison.hpp"

#include "polynomials.h"

#include <vector>
#include <iostream>
#include <fstream>

using namespace boost::tuples;

typedef boost::tuples::tuple<int, int, int> T;

class Subtractions{

    public:

    Subtractions();
    Subtractions(int);
    Subtractions(int, int, int);
    Subtractions(const Subtractions&);

    void clear();
   
    int c_borrowed;
    int b_borrowed;
    int m_subtracted;

    Subtractions operator=(const Subtractions&);
    Subtractions operator=(int);
    Subtractions operator==(const Subtractions&);


    friend std::ostream& operator<<(std::ostream&, const Subtractions&);
    friend std::ofstream& operator<<(std::ofstream&, const Subtractions&);

};


#endif



subtract(const Tuple<double, double, double> &t)
{
   double a, b, c; // temp variables for polynomial ax + bx^2 + cx^3
   bool flag = true;
   Tuple<double, double, double> val = 0;

   for(int i; i<sizeof(t); i++)
   {
      if( data.at(i) < t.data.at(i))
      {
         break;
      }
      else
      {
         get<i>(val) = t.data.at(i) - data.at(i);
      }

   }
   if(flag)
   {
         return val;
   }
}
