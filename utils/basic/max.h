#ifndef H_H
#define H_H

#include "boost/tuple/tuple.hpp"


typedef boost::tuples::tuple<double, double, double> tuple;

class max{

   public:

      max();
      max(tuple, tuple);

      tuple m_best;
      tuple M[];

};



#endif
