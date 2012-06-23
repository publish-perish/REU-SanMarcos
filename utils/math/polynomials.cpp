#include "../basic/polynomials.h"


Polynomial::Polynomial()
{
}

Polynomial::Polynomial(T &X, T &Y)
{
   current = T(get<0>(Y)*get<0>(X), get<1>(Y)*get<1>(X), get<2>(Y)*get<2>(X));
}
