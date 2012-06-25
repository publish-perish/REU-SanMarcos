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
}

T Polynomial::value()const
{
   return T(get<0>(A)*get<0>(Y), get<1>(A)*get<1>(Y), get<2>(A)*get<2>(Y));
}

int Polynomial::sum()const
{
   return((get<0>(A)*get<0>(Y)) + (get<1>(A)*get<1>(Y)) +(get<2>(A)*get<2>(Y)));
}

bool Polynomial::operator==(const Polynomial &p)
{
   return((get<0>(A)==get<0>(Y)) && (get<1>(A)==get<1>(Y)) && (get<2>(A)==get<2>(Y)));
}

Polynomial Polynomial::operator=(Polynomial p)
{
    Polynomial temp(p.A, p.Y);
    temp.s = p.s;
    return temp;
}

void Polynomial::borrowC(Polynomial &p)
{
   std::cout<<p;
   if( get<1>(p.Y) < 0 )
   {
         ++p.s.c_borrowed;
         Polynomial temp(p.A, T(get<0>(p.Y), get<1>(p.Y)+get<0>(p.A), get<2>(p.Y)));
         p = temp;
         (borrowC(temp));
   }
         std::cout<<"Returned to borrowC "<<p;
}

void Polynomial::borrowB(Polynomial &p)
{
    std::cout<<p;
    if( get<2>(p.Y) < 0 )
    {
         ++p.s.b_borrowed;
         Polynomial temp(p.A, T(get<0>(p.Y), get<1>(p.Y), get<2>(p.Y)+get<1>(p.A)));
         p = temp;
         (borrowB(temp));
    }
    else if( get<1>(p.Y) < 0 )
    {
        std::cout<<"Borrowing from C \n";
        borrowC(p);
    }
        std::cout<<"Returned to borrowB "<<p;
}


Polynomial Polynomial::operator-(Polynomial m)
{
    Polynomial value = *this;
    std::cout<<"Testing: \n"<<"   "<<*this<<" - "<<m<<std::endl;

    if( (get<0>(Y) > get<0>(m.Y)) )
    {
        ++m.s.m_subtracted;
        Polynomial temp(A, T(get<0>(Y) - get<0>(m.Y), get<1>(Y) - get<1>(m.Y), get<2>(Y) - get<2>(m.Y)));
        value = temp;
        temp = temp - m;
        std::cout<< "Subtracted "<< m.s.m_subtracted<<" times. \n";
        std::cout<< temp<<std::endl;
    }
    else if( get<2>(Y) < 0 )
    {
          std::cout<<"Borrowing from B \n";
          borrowB(value);
          std::cout<<"Returned to main subtract "<<value;
    }
    std::cout<<"end subtract \n";
    return value;
}

std::ostream& operator<<(std::ostream& ostr, const Polynomial &p)
{
    ostr << get<2>(p.Y) << "a + " << get<1>(p.Y) << "b + " << get<0>(p.Y) <<"c \n";
    return ostr;
}

std::ofstream& operator<<(std::ofstream& ofstr, const Polynomial &p)
{
    ofstr << get<2>(p.Y) << "a + " << get<1>(p.Y) << "b + " << get<0>(p.Y) <<"c \n";
    return ofstr;
}



