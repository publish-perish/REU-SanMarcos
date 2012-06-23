#include "../basic/polynomials.h"


Polynomial::Polynomial()
{
   value = T(0,0,0);
}

Polynomial::Polynomial(T &X, T &Y)
{
   value = T(Y.data.at(0)*X.data.at(0), Y.data.at(1)*X.data.at(1), Y.data.at(2)*X.data.at(2));
}

