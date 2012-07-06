#include "../basic/polynomials.h"



Polynomial::Polynomial()
{
   A = TP(0, 0, 0, 0);
   Y = TP(0, 0, 0, 0);
   s = 0;
}

Polynomial::Polynomial(TP a, TP y)
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

int Polynomial::value()const
{
   return (get<0>(A)*get<0>(Y));
}

int Polynomial::sum()const
{
   return((get<0>(A)*get<0>(Y)) + (get<1>(A)*get<1>(Y))+ (get<2>(A)*get<2>(Y)) + (get<3>(A)*get<3>(Y)));
}

bool Polynomial::wellFormed()const
{
   return (get<3>(Y) < get<2>(A) && (get<2>(Y) < (float)(get<1>(A) / get<2>(A)) ) && ( get<1>(Y) < (float)( get<0>(A) / get<1>(A)) ) );
}

bool Polynomial::operator==(const Polynomial &p)
{
   return((get<0>(p.Y)==get<0>(Y)) && (get<1>(p.Y)==get<1>(Y)) && (get<2>(p.Y)==get<2>(Y)) && (get<3>(p.Y)==get<3>(Y)));
}

bool Polynomial::operator>=(const Polynomial &p)
{
   return(sum()>=p.sum());
}

Polynomial Polynomial::operator=(const Polynomial &p)
{
    A = p.A;
    Y = p.Y;
    s = p.s;
}


Polynomial Polynomial::operator-(Polynomial m) // needs updating for k=4
{
    loop:
    while( Y > m.Y )
    {
        ++this->s.m_subtracted;
        this->Y = TP(get<0>(Y) - get<0>(m.Y), get<1>(Y) - get<1>(m.Y), get<2>(Y) - get<2>(m.Y), get<3>(Y) - get<3>(m.Y));

    }
    while( get<1>(Y) < 0 )
    {
          ++this->s.d_borrowed;
          this->Y = TP(get<0>(Y), get<1>(Y)+(float)(get<0>(A)/get<1>(A)), get<2>(Y), get<3>(Y) );
    }
    while( get<2>(Y) < 0 )
    {
          ++this->s.c_borrowed;
          this->Y = TP(get<0>(Y), get<1>(Y), get<2>(Y) + (float)((get<1>(A)/get<2>(A))), get<3>(Y) );
    }
    while( get<3>(Y) < 0 )
    {
          ++this->s.b_borrowed;
          this->Y = TP(get<0>(Y), get<1>(Y), get<2>(Y), get<3>(Y) + (float)(get<2>(A)/get<3>(A)));

    }
    if( Y > m.Y ){ goto loop; } 
    return *this;
}

std::ostream& operator<<(std::ostream& ostr, const Polynomial &p)
{
    ostr << get<0>(p.Y)<< "d + " << get<1>(p.Y) << "c + " << get<2>(p.Y) << "b + " << get<3>(p.Y) <<"a \n";
}

std::ofstream& operator<<(std::ofstream& ofstr, const Polynomial &p)
{
    ofstr << get<0>(p.Y)<< "d + " << get<1>(p.Y) << "c + " << get<2>(p.Y) << "b + " << get<3>(p.Y) <<"a \n";
}


