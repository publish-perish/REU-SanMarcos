#include "/boost/tuples/tuple.hpp"
#include "polynomials.h"
#include <vector>

using namespace boost::tuples;


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
