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

      Polynomial();
      Polynomial(T &A, T &Y); 

      T value;
};


class m : public Polynomial{

  //    m(T &A, T &Q): Polynomial(A, Q){}

};


class v : public Polynomial{


    //  v(T &A, T &X): Polynomial(A, X){}

};



#endif
