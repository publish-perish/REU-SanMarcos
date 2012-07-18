#include "../basic/polynomials.h"

Polynomial::Polynomial()
{
    A = T(0, 0, 0);
    Y = T(0, 0, 0);
    s = 0;
}

Polynomial::Polynomial(T &a, T &y)
{   
   A = TP(0, 0, 0, 0, 0);
   Y = TP(0, 0, 0, 0, 0);
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
   return (A[0]*Y[0]);
}

int Polynomial::sum()const
{
   //return((A[0]*Y[0]) + (A[1]*Y[1]) +(A[2]*Y[2]));
   return((get<0>(A)*get<0>(Y)) + (get<1>(A)*get<1>(Y))+ (get<2>(A)*get<2>(Y)) + (get<3>(A)*get<3>(Y)) + (get<4>(A)*get<4>(Y)));
}

bool Polynomial::wellFormed()const
{
   //return ((Y[2] < A[1]) && ( Y[1] <= (float)( A[0] / A[1]) ) );
   return (get<4>(Y) < get<3>(A) && (get<3>(Y) < (float)(get<2>(A) / get<1>(A)) ) && ( get<2>(Y) < (float)( get<1>(A) / get<0>(A)) ) && (get<1>(Y) < get<0>(A)) );
}

bool Polynomial::operator==(const Polynomial &p)
{
//   return((p.Y[0]==Y[0]) && (p.Y[1]==Y[1]) && (p.Y[2]==Y[2]));
   return((get<0>(p.Y)==get<0>(Y)) && (get<1>(p.Y)==get<1>(Y)) && (get<2>(p.Y)==get<2>(Y)) && (get<3>(p.Y)==get<3>(Y)) && (get<4>(p.Y)==get<4>(Y)));
}

bool Polynomial::operator>=(const Polynomial &p)
{
   return((p.Y[0]>=Y[0]) && (p.Y[1]>=Y[1]) && (p.Y[2]>=Y[2]));
}

bool Polynomial::operator!=(const Polynomial &p)
{
   return((p.Y[0]!=Y[0]) && (p.Y[1]!=Y[1]) && (p.Y[2]!=Y[2]));
}

bool Polynomial::operator!=(int num)
{
   return((Y[0]!=num) && (Y[1]!=num) && (Y[2]!=num));
}

Polynomial Polynomial::operator=(const Polynomial &p)
{
    A = p.A;
    Y = p.Y;
    s = p.s;
}


Polynomial Polynomial::operator-(Polynomial m) 
{
    loop:
    while( Y > m.Y )
    {
        ++this->s.m_subtracted;
        //std::cout<<"m subtracted: "<<this->s.m_subtracted<<std::endl;;
        // subtract m from x
        //this->Y = T(Y[0] - m.Y[0], Y[1] - m.Y[1], Y[2] - m.Y[2]);
        //std::cout<<"result from m subtraction # "<<n<<": "<<temp;++n;
        //*this = temp - m; // recursive call
        this->Y = TP(get<0>(Y) - get<0>(m.Y), get<1>(Y) - get<1>(m.Y), get<2>(Y) - get<2>(m.Y), get<3>(Y) - get<3>(m.Y), get<4>(Y) - get<4>(m.Y));

    }
    while( get<1>(Y) < 0 )
    {
          ++this->s.e_borrowed;
          this->Y = TP(get<0>(Y), get<1>(Y)+(float)(get<0>(A)/get<1>(A)), get<2>(Y), get<3>(Y) );
    }/*
    while( Y[2] < 0 )
    {
          ++this->s.b_borrowed;
          //std::cout<<"b borrowed: "<<this->s.b_borrowed<<std::endl;;
          this->Y = T(Y[0], Y[1], Y[2]+A[1]);
          //std::cout<<"result from B borrow # "<<n<<": "<<temp;++n;
          //*this = temp - m;
    }
    while( Y[1] < 0 )
    {
          ++this->s.c_borrowed;
          //std::cout<<"c borrowed: "<<this->s.c_borrowed<<std::endl;
          this->Y = T(Y[0], Y[1]+ (float)(A[0]/A[1]), Y[2]);
          //std::cout<<"result from C borrow # "<<n<<": "<<temp;++n;
          //*this = temp - m;
          ++this->s.d_borrowed;
          this->Y = TP(get<0>(Y), get<1>(Y), get<2>(Y) + (float)((get<1>(A)/get<2>(A))), get<3>(Y) );
    }*/
    while( get<3>(Y) < 0 )
    {
          ++this->s.c_borrowed;
          this->Y = TP(get<0>(Y), get<1>(Y), get<2>(Y), get<3>(Y) + (float)(get<2>(A)/get<3>(A)));

    }
    while( get<4>(Y) < 0 )
    {
          ++this->s.b_borrowed;
          this->Y = TP(get<0>(Y), get<1>(Y), get<2>(Y), get<3>(Y), (get<4>(Y) + (float)(get<3>(A)));

    }
    if( Y > m.Y ){ goto loop; } 


    return *this;
}

std::ostream& operator<<(std::ostream& ostr, const Polynomial &p)
{
  //  ostr << p.Y[2] << "a + " << p.Y[1] << "b + " << p.Y[0] <<"c \n";
    ostr << get<0>(p.Y)<< "e + " << get<1>(p.Y) << "d + " << get<2>(p.Y) << "c + " << get<3>(p.Y) <<"b + " << get<4>(p.Y) << " a \n";
}

std::ofstream& operator<<(std::ofstream& ofstr, const Polynomial &p)
{
//    ofstr << p.Y[2] << "a + " << p.Y[1] << "b + " << p.Y[0] <<"c \n";
    ofstr << get<0>(p.Y)<< "e + " << get<1>(p.Y) << "d + " << get<2>(p.Y) << "c + " << get<3>(p.Y) <<"b + " << get<4>(p.Y) << " a \n";
}


