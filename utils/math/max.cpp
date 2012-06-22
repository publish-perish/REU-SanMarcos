#include "../basic/max.h"


max::max()
{
}

max::max(T A, T Q)
{

   M[0] = T(get<0>(Q)*get<0>(A), get<1>(Q)*get<1>(A), get<2>(Q)*get<2>(A));

}
