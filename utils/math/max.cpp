#include "../basic/max.h"


max::max()
{
}

max::max(tuple A, tuple Q)
{

   M[0] = tuple(boost::tuples::get<0>(Q)*boost::tuples::get<0>(A), boost::tuples::get<1>(Q)*boost::tuples::get<1>(A), boost::tuples::get<2>(Q)*boost::tuples::get<2>(A));

}
