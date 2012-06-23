#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "boost/tuple/tuple.hpp"
#include <vector>
#include <map>

using namespace boost::tuples;

typedef tuple<double, double, double> T;
typedef std::vector<T> Vec;

class Polynomial{

   public:

      Polynomial();
      Polynomial(T &x, T &y); 

      Polynomial operator-(const Polynomial&);

      Vec list;
      T current;

};


class m : public Polynomial{

      m(T &A, T &Q): Polynomial(A, Q){}

};


class v : public Polynomial{

      v(T &A, T &X): Polynomial(A, X){}

};



#endif
