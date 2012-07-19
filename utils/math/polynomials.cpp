#include "../basic/polynomials.h"


Polynomial::Polynomial()
{
   A = T4(0, 0, 0, 0);
   Y = T4(0, 0, 0, 0);
   s = 0;
}

Polynomial::Polynomial(T4 a, T4 y)
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
   return (A[0]*Y[0]);
}

int Polynomial::sum()const
{
   return((A[0]*Y[0]) + (A[1]*Y[1])+ (A[2]*Y[2]) + (A[3]*Y[3]));
}

bool Polynomial::wellFormed()const
{
   return (Y[3] < A[2] && (Y[2] < (float)(A[1] /A[2]) ) && ( Y[1] < (float)( A[0] / A[1]) ) );
}

bool Polynomial::operator==(const Polynomial &p)
{
   return((p.Y[0]==Y[0]) && (p.Y[1]==Y[1]) && (p.Y[2]==Y[2]) && (p.Y[3]==Y[3]));
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
    return *this;
}


Polynomial Polynomial::operator-(Polynomial m) 
{
    loop:
    while( Y > m.Y )
    {
        ++this->s.m_subtracted;
        this->Y = T4(Y[0] - m.Y[0], Y[1] - m.Y[1], Y[2] - m.Y[2], Y[3] - m.Y[3]);

    }
    while( Y[1] < 0 )
    {
          ++this->s.d_borrowed;
          this->Y = T4(Y[0], Y[1]+(float)(A[0]/A[1]), Y[2], Y[3] );
    }
    while( Y[2] < 0 )
    {
          ++this->s.c_borrowed;
          this->Y = T4(Y[0], Y[1], Y[2] +(float)(A[1]/A[2]), Y[3] );
    }
    while( Y[3] < 0 )
    {
          ++this->s.b_borrowed;
          this->Y = T4(Y[0], Y[1], Y[2], Y[3]+(float)(A[2]/A[3]) );

    }
    if( Y > m.Y ){ goto loop; } 


    return *this;
}

std::ostream& operator<<(std::ostream& ostr, const Polynomial &p)
{
    ostr << p.Y[0]<< "d + " << p.Y[1] << "c + " << p.Y[2] << "b + " << p.Y[3] <<"a \n";
}

std::ofstream& operator<<(std::ofstream& ofstr, const Polynomial &p)
{
    ofstr << p.Y[0]<< "d + " << p.Y[1] << "c + " << p.Y[2] << "b + " << p.Y[3] <<"a \n";
}


