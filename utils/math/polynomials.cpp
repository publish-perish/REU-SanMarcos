#include "../basic/polynomials.h"

Polynomial::Polynomial()
{

   A = T6(0, 0, 0, 0, 0, 0);
   Y = T6(0, 0, 0, 0, 0, 0);
   s = 0;
}


Polynomial::Polynomial(T6 a, T6 y)

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
   return((A[0]*Y[0]) + (A[1]*Y[1]) +(A[2]*Y[2]) + (A[3]*Y[3]) +(A[4]*Y[4]) +(A[5]*Y[5]));
}

bool Polynomial::wellFormed()const
{
return ( ( Y[5] < A[4] ) && (Y[4] < (A[3]/ A[4])) && ( Y[3] < (float)( A[2] / A[3]) ) && ( Y[2] < (float)( A[1] / A[2]) ) && ( Y[1] < (float)( A[0] / A[1]) ) );

}

bool Polynomial::operator==(const Polynomial &p)
{
   return((p.Y[0]==Y[0]) && (p.Y[1]==Y[1]) && (p.Y[2]==Y[2]) && (p.Y[3]==Y[3]) && (p.Y[4]==Y[4]) && (p.Y[5]==Y[5]) );
}

bool Polynomial::operator>=(const Polynomial &p)
{
return(
(p.Y[0]>=Y[0]) || 
((p.Y[0]==Y[0]) && (p.Y[1]>=Y[1])) ||
((p.Y[0]==Y[0]) && (p.Y[1]==Y[1]) &&(p.Y[2]>=Y[2])) ||
((p.Y[0]==Y[0]) && (p.Y[1]==Y[1]) &&(p.Y[2]==Y[2]) && (p.Y[3]>=Y[3])) ||
((p.Y[0]==Y[0]) && (p.Y[1]==Y[1]) &&(p.Y[2]==Y[2]) && (p.Y[3]==Y[3]) && (p.Y[4]>=Y[4]) ) ||
((p.Y[0]==Y[0]) && (p.Y[1]==Y[1]) &&(p.Y[2]==Y[2]) && (p.Y[3]==Y[3]) && (p.Y[4]==Y[4]) && (p.Y[5]>=Y[5]) )
);
}

bool Polynomial::operator!=(const Polynomial &p)
{
   return((p.Y[0]!=Y[0]) || (p.Y[1]!=Y[1]) || (p.Y[2]!=Y[2]) || (p.Y[3]!=Y[3]) || (p.Y[4]!=Y[4]) || (p.Y[5]!=Y[5]));
}

bool Polynomial::operator!=(int num) 
{
   return((Y[0]!=num) || (Y[1]!=num) || (Y[2]!=num) || (Y[3]!=num) || (Y[4]!=num) || (Y[5]!=num));
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
        this->Y = T6(Y[0] - m.Y[0], Y[1] - m.Y[1], Y[2] - m.Y[2], Y[3] - m.Y[3], Y[4] - m.Y[4], Y[5] - m.Y[5] );
    }
	while( Y[5] < 0 ) // borrow b
    {
          ++this->s.b_borrowed;
          this->Y = T6(Y[0], Y[1], Y[2], Y[3], Y[4], Y[5] + A[4]);  
    }
	while( Y[4] < 0 ) //borrow c
    {
          ++this->s.c_borrowed;
          this->Y = T6(Y[0], Y[1], Y[2], Y[3], Y[4] + A[3], Y[5]); 
    }
    while( Y[3] < 0 ) //borrow d
    {
          ++this->s.d_borrowed;
		  this->Y = T6(Y[0], Y[1], Y[2], Y[3] +A[2], Y[4], Y[5]);
    }
    while( Y[2] < 0 ) //borrow e
    {
          ++this->s.e_borrowed;
          this->Y = T6(Y[0], Y[1], Y[2] + A[1], Y[3], Y[4], Y[5]);

    }
    while( Y[1] < 0 ) //borrow f
    {
          ++this->s.f_borrowed;
          this->Y = T6(Y[0], Y[1]+A[0], Y[2], Y[3], Y[4], Y[5]);
    }
    
    if( Y > m.Y ){ goto loop; } 


    return *this;
}

std::ostream& operator<<(std::ostream& ostr, const Polynomial &p)
{

ostr << p.Y[0] << "f + " << p.Y[1] << "e + " << p.Y[2] <<"d + " << p.Y[3] << "c + " << p.Y[4] <<"b + " << p.Y[5] << "a \n";

}

std::ofstream& operator<<(std::ofstream& ofstr, const Polynomial &p)
{

ofstr << p.Y[0] << "f + " << p.Y[1] << "e + " << p.Y[2] <<"d + " << p.Y[3] << "c + " << p.Y[4] <<"b + " << p.Y[5] << "a \n";

}


