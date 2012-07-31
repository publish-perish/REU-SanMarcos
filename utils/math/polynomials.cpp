#include "../basic/polynomials.h"



Polynomial::Polynomial()
{
   A = T4(0, 0, 0, 0);
   Y = T(0, 0, 0);
   s = 0;
}

Polynomial::Polynomial(T4 a, T y)
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

int Polynomial::sum()const //?
{
   return(  (A[0]*Y[0]) + (A[1]*Y[0]) + (A[2]*Y[1]) +(A[3]*Y[2]) ) ;
}

bool Polynomial::wellFormed()const
{
   return ((Y[2] < A[2]) && ( Y[1] <= (float)( A[0] / A[2]) ) );
}

bool Polynomial::operator==(const Polynomial &p)
{
   return((p.Y[0]==Y[0]) && (p.Y[1]==Y[1]) && (p.Y[2]==Y[2]));
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
int n = 1;

Polynomial Polynomial::operator-(Polynomial m)
{
    loop:
    while( Y > m.Y )
    {
        ++this->s.m_subtracted;
        //std::cout<<"m subtracted: "<<this->s.m_subtracted<<std::endl;;
        // subtract m from x
        this->Y = T(Y[0] - m.Y[0], Y[1] - m.Y[1], Y[2] - m.Y[2]);
        //std::cout<<"result from m subtraction # "<<n<<": "<<*this;++n;
        //*this = temp - m; // recursive call
    }
    while( Y[1] < 0 ) // borrow c
    {
          ++this->s.c_borrowed;
          //std::cout<<"c borrowed: "<<this->s.c_borrowed<<std::endl;
          this->Y = T(Y[0], Y[1]+(A[0]/A[2]), Y[2]+A[1]);
          //std::cout<<"result from C borrow # "<<n<<": "<<*this;++n;
          //*this = temp - m;
    }
    while( Y[1] > (A[0] / A[2]) ) // carry c
    {
          --this->s.c_borrowed;
          //std::cout<<"b borrowed: "<<this->s.b_borrowed<<std::endl;;
          this->Y = T(Y[0], (Y[1] - (A[0] / A[2]) ), (Y[2]- A[1]));
          //std::cout<<"result from B borrow # "<<n<<": "<<*this;++n;
          //*this = temp - m;
    }
    while( Y[2] < 0 ) // borrow b
    {
          ++this->s.b_borrowed;
          //std::cout<<"b borrowed: "<<this->s.b_borrowed<<std::endl;;
          this->Y = T(Y[0], Y[1], (Y[2]+A[2]));
          //std::cout<<"result from B borrow # "<<n<<": "<<*this;++n;
          //*this = temp - m;
    }
    while( Y[2] >= A[2] ) // carry b
    {
          --this->s.b_borrowed;
          //std::cout<<"b borrowed: "<<this->s.b_borrowed<<std::endl;;
          this->Y = T(Y[0], Y[1], (Y[2]-A[2]));
          //std::cout<<"result from B borrow # "<<n<<": "<<*this;++n;
          //*this = temp - m;
    }

    if( Y > m.Y ){goto loop; }
    return *this;
}

std::ostream& operator<<(std::ostream& ostr, const Polynomial &p)
{
    ostr << "Generators: ("<< p.A[0] << ", " << p.A[1] << ", " << p.A[2] <<") Coeffs: ("<< p.Y[0] <<", "<< p.Y[1] <<", "<< p.Y[2] <<")\n";
}

std::ofstream& operator<<(std::ofstream& ofstr, const Polynomial &p)
{
    ofstr << p.Y[0] << "c + " << p.Y[1] << "b + " << p.Y[2] <<"a \n";
}


