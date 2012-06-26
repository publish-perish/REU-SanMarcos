#include "../basic/polynomials.h"



Polynomial::Polynomial()
{
}

Polynomial::Polynomial(T a, T y)
{
   A = a;
   Y = y;
   s = 0;
}

Polynomial::Polynomial(const Polynomial &p)
{
    A = p.A;
    Y = p.Y;
    s = p.s;
}

T Polynomial::value()const
{
   return T(get<0>(A)*get<0>(Y), get<1>(A)*get<1>(Y), get<2>(A)*get<2>(Y));
}

int Polynomial::sum()const
{
   return((get<0>(A)*get<0>(Y)) + (get<1>(A)*get<1>(Y)) +(get<2>(A)*get<2>(Y)));
}

bool Polynomial::wellFormed()const
{
   return ((get<2>(Y) < get<1>(A)) && (get<2>(Y) < get<0>(A)));
}

bool Polynomial::operator==(const Polynomial &p)
{
   return((get<0>(p.Y)==get<0>(Y)) && (get<1>(p.Y)==get<1>(Y)) && (get<2>(p.Y)==get<2>(Y)));
}

Polynomial Polynomial::operator=(const Polynomial &p)
{
    A = p.A;
    Y = p.Y;
    s = p.s;
}

Polynomial Polynomial::borrowC(Polynomial p)
{
   //std::cout<<"In borrowC "<<p;
   if( get<1>(p.Y) < 0 )
   {
         ++p.s.c_borrowed;
         // add a 'c' to the second degree term
         Polynomial temp(p.A, T(get<0>(p.Y), get<1>(p.Y)+get<0>(p.A), get<2>(p.Y)));
         p = borrowC(temp);
   }
   //std::cout<<"Returned to borrowC "<<p;
   return p;
}

Polynomial Polynomial::borrowB(Polynomial p)
{
    //std::cout<<"In borrowB "<<p;
    if( get<2>(p.Y) < 0 )
    {
         ++p.s.b_borrowed;
         // add a 'b' to the first degree term
         Polynomial temp(p.A, T(get<0>(p.Y), get<1>(p.Y), get<2>(p.Y)+get<1>(p.A)));
         p = (borrowB(temp));
    }
    else if( get<1>(p.Y) < 0 )
    {
        p = borrowC(p);
    }
    //    std::cout<<"Returned to borrowB "<<p;
    return p;
}


Polynomial Polynomial::operator-(Polynomial m)
{
    Polynomial value = *this;
    //std::cout<<"Testing: \n"<<"   "<<*this<<" - "<<m<<std::endl;

    if( (Y) > (m.Y) )
    {
        ++m.s.m_subtracted;
        // subtract m from x
        Polynomial temp(A, T(get<0>(Y) - get<0>(m.Y), get<1>(Y) - get<1>(m.Y), get<2>(Y) - get<2>(m.Y)));
        value = temp - m; // recursive call
        //std::cout<< "Subtracted "<< m.s.m_subtracted<<" times. \n";
    }
    else if( get<2>(Y) < 0 )
    {
          value = borrowB(value);
          //std::cout<<"Returned to main subtract "<<value;
    }
    return value;
}

std::ostream& operator<<(std::ostream& ostr, const Polynomial &p)
{
    ostr << get<2>(p.Y) << "a + " << get<1>(p.Y) << "b + " << get<0>(p.Y) <<"c \n";
    ostr << p.s;
    return ostr;
}

std::ofstream& operator<<(std::ofstream& ofstr, const Polynomial &p)
{
    ofstr << get<2>(p.Y) << "a + " << get<1>(p.Y) << "b + " << get<0>(p.Y) <<"c \n";
    ofstr << p.s;
    return ofstr;
}



