#include "../basic/polynomials.h"



Polynomial::Polynomial()
{
   A = Y  = T(0,0,0);
}

Polynomial::Polynomial(T &a, T &y)
{
   A = a;
   Y = y;
}

T Polynomial::value()const
{
   return T(get<0>(A)*get<0>(Y), get<1>(A)*get<1>(Y), get<2>(A)*get<2>(Y));
}



