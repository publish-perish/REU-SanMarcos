#include "boost/tuple/tuple.hpp"
#include <vector>
#include "polynomials.h"

using namespace boost::tuples;

typedef boost::tuples::tuple<int, int, int> T;

class Subtractions{

    public:

    Subtractions();
    void clear();

    int c_borrowed;
    int b_borrowed;
    int m_subtracted;
};

Subtractions::Subtractions()
{
   c_borrowed = b_borrowed = m_subtracted = 0;
}

void Subtractions::clear()
{
   c_borrowed = b_borrowed = m_subtracted = 0;
}  


Polynomial borrowC(Polynomial p, Subtractions &s)
{
   Polynomial temp = Polynomial();
   Polynomial val = Polynomial();

   if( get<1>(p.value()) < 0 )
   {
         s.c_borrowed++;
         temp.A = p.A;
         temp.Y = T(get<0>(p.Y), get<1>(p.Y)+get<2>(p.A), get<2>(p.Y));
         val = borrowC(temp, s);
   }
   return val;
}

Polynomial borrowB(Polynomial p, Subtractions &s)
{
    Polynomial temp = Polynomial();
    Polynomial val = Polynomial();
    
    if( get<2>(p.value()) < 0 )
    {
         s.b_borrowed++;
         temp.A = p.A;
         temp.Y = T(get<0>(p.Y)+get<1>(p.A), get<1>(p.Y), get<2>(p.Y));
         val = borrowB(temp, s);
    }
    else if( get<1>(p.value()) < 0 )
    {
        val = borrowC(val, s);
    }
    return val;
}


Polynomial subtract(Polynomial x, Polynomial m, Subtractions &s)
{
    Polynomial temp = Polynomial();
    Polynomial val = Polynomial();

    if( x.value() < m.value() )
    {
        s.m_subtracted++;
        temp.A = x.A;
        temp.Y = T(get<0>(x.Y) - get<0>(m.Y), get<1>(x.Y) - get<1>(m.Y), get<2>(x.Y) - get<2>(m.Y));
        val = subtract(temp, m, s);
    }
    else if( get<2>(x.value()) < 0 )
    {
         val = borrowB(val, s);    
    }
    return val;
}
    




