#ifndef H_H
#define H_H

#include "boost/tuple/tuple.hpp"

using namespace boost::tuples;

typedef tuple<double, double, double> T;

class max{

   public:

      max();
      max(T, T);

      T m_best;
      T M[];

};



#endif
