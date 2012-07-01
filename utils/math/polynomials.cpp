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

int Polynomial::value()const
{
   return (get<0>(A)*get<0>(Y));
}

int Polynomial::sum()const
{
   return((get<0>(A)*get<0>(Y)) + (get<1>(A)*get<1>(Y)) +(get<2>(A)*get<2>(Y)));
}

bool Polynomial::wellFormed()const
{
   return ((get<2>(Y) < get<1>(A)) && (get<1>(Y) < get<0>(A) / get<1>(A)));
}

bool Polynomial::operator==(const Polynomial &p)
{
   return((get<0>(p.Y)==get<0>(Y)) && (get<1>(p.Y)==get<1>(Y)) && (get<2>(p.Y)==get<2>(Y)));
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

int n=1;

Polynomial Polynomial::operator-(Polynomial m)
{
    loop:
    while( Y > m.Y )
    {
        ++this->s.m_subtracted;
        //std::cout<<"m subtracted: "<<this->s.m_subtracted<<std::endl;;
        // subtract m from x
        this->Y = T(get<0>(Y) - get<0>(m.Y), get<1>(Y) - get<1>(m.Y), get<2>(Y) - get<2>(m.Y));
        //std::cout<<"result from m subtraction # "<<n<<": "<<temp;++n;
        //*this = temp - m; // recursive call
    }
    while( get<2>(Y) < 0 )
    {
          ++this->s.b_borrowed;
          //std::cout<<"b borrowed: "<<this->s.b_borrowed<<std::endl;;
          this->Y = T(get<0>(Y), get<1>(Y), get<2>(Y)+get<1>(A));
          //std::cout<<"result from B borrow # "<<n<<": "<<temp;++n;
          //*this = temp - m;
    }
    while( get<1>(Y) < 0 )
    {
          ++this->s.c_borrowed;
          //std::cout<<"c borrowed: "<<this->s.c_borrowed<<std::endl;
          this->Y = T(get<0>(Y), get<1>(Y)+(get<0>(A)/get<1>(A)), get<2>(Y));
          //std::cout<<"result from C borrow # "<<n<<": "<<temp;++n;
          //*this = temp - m;
    }
    if( Y > m.Y ){ goto loop; }
    return *this;
}

std::ostream& operator<<(std::ostream& ostr, const Polynomial &p)
{
    ostr << get<2>(p.Y) << "a + " << get<1>(p.Y) << "b + " << get<0>(p.Y) <<"c \n";
}

std::ofstream& operator<<(std::ofstream& ofstr, const Polynomial &p)
{
    ofstr << get<2>(p.Y) << "a + " << get<1>(p.Y) << "b + " << get<0>(p.Y) <<"c \n";
}



