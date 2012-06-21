#include "../basic/max.h"


max::max()
{
}

max::max(tuple A, tuple Q)
{

   M[n] = tuple(get<0>(Q)*get<0>(A), get<1>(Q)*get<1>(A), get<2>(Q)*get<2>(A));

}
