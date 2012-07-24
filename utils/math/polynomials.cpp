#include "../basic/polynomials.h"

Polynomial::Polynomial()
{

   A = T5(0, 0, 0, 0, 0);
   Y = T5(0, 0, 0, 0, 0);
   s = 0;
}


Polynomial::Polynomial(T5 a, T5 y)

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
   return((A[0]*Y[0]) + (A[1]*Y[1]) +(A[2]*Y[2]) + (A[3]*Y[3]) + (A[4]*Y[4]));
}

bool Polynomial::wellFormed()const
{
return ((Y[4] < A[3]) && ( Y[3] < (float)( A[2] / A[3]) ) && ( Y[2] < (float)( A[1] / A[2]) ) && ( Y[1] < (float)( A[0] / A[1]) ) );

}

bool Polynomial::operator==(const Polynomial &p)
{
   return((p.Y[0]==Y[0]) && (p.Y[1]==Y[1]) && (p.Y[2]==Y[2]) && (p.Y[3]==Y[3]) && (p.Y[4]==Y[4]) );
}

bool Polynomial::operator>=(const Polynomial &p)
{
return(
(p.Y[0]>=Y[0]) || 
((p.Y[0]==Y[0]) && (p.Y[1]>=Y[1])) ||
((p.Y[0]==Y[0]) && (p.Y[1]==Y[1]) &&(p.Y[2]>=Y[2])) ||
((p.Y[0]==Y[0]) && (p.Y[1]==Y[1]) &&(p.Y[2]==Y[2]) && (p.Y[3]>=Y[3])) ||
((p.Y[0]==Y[0]) && (p.Y[1]==Y[1]) &&(p.Y[2]==Y[2]) && (p.Y[3]==Y[3])&& (p.Y[4]>=Y[4]) )
);
}

bool Polynomial::operator!=(const Polynomial &p)
{
   return((p.Y[0]!=Y[0]) || (p.Y[1]!=Y[1]) || (p.Y[2]!=Y[2]) || (p.Y[3]!=Y[3]) || (p.Y[4]!=Y[4]));
}

bool Polynomial::operator!=(int num) //incomplete
{
   return((Y[0]!=num) || (Y[1]!=num) || (Y[2]!=num) || (Y[3]!=num) || (Y[4]!=num));
}

Polynomial Polynomial::operator=(const Polynomial &p)
{
	//cout << "polynomial assignment...";
    A = p.A;
    Y = p.Y;
    s = p.s;
	//cout << "polynomial assignment complete" << endl;
	return *this;
}


Polynomial Polynomial::operator-(Polynomial m) 
{
	//cout << "trying to compare" << endl;
    loop:
    while( Y > m.Y )
    {
    	//cout << "Y " << Y << endl;
    	//cout << "m.Y " << m.Y << endl;
        ++this->s.m_subtracted;
        //std::cout<<"m subtracted: "<<this->s.m_subtracted<<std::endl;;
        // subtract m from x
        this->Y = T5(Y[0] - m.Y[0], Y[1] - m.Y[1], Y[2] - m.Y[2], Y[3] - m.Y[3], Y[4] - m.Y[4]);
        //std::cout<<"result from m subtraction # "<<n<<": "<<temp;++n;
        //*this = temp - m; // recursive call

    }
	 while( Y[4] < 0 ) // borrow b
    {
          ++this->s.b_borrowed;
          this->Y = T5(Y[0], Y[1], Y[2], Y[3], Y[4]+A[3]);  
    }
	while( Y[3] < 0 ) //borrow c
    {
          ++this->s.c_borrowed;
          this->Y = T5(Y[0], Y[1], Y[2], Y[3]+(A[2]/A[3]), Y[4]); 

    }
    
    while( Y[2] < 0 ) //borrow d
    {
          ++this->s.d_borrowed;
		  this->Y = T5(Y[0], Y[1], Y[2]+(A[1]/A[2]), Y[3], Y[4]);

    }
    while( Y[1] < 0 ) //borrow e
    {
          ++this->s.e_borrowed;
          this->Y = T5(Y[0], Y[1]+(A[0] / A[1]), Y[2], Y[3], Y[4]);

    }

    if( Y > m.Y ){ goto loop; } 


	//cout << "calling the return" << endl;
    return *this;
}

std::ostream& operator<<(std::ostream& ostr, const Polynomial &p)
{

ostr << "Coefficients : ("<<p.Y[0] << " " << p.Y[1] << " " << p.Y[2] <<" " << p.Y[3] << " " << p.Y[4] <<"), and Generators : (" << p.A[0] << " " << p.A[1] << " " << p.A[2] <<" " << p.A[3] << " " << p.A[4] <<") \n";


}

std::ofstream& operator<<(std::ofstream& ofstr, const Polynomial &p)
{

ofstr << "Coefficients : ("<<p.Y[0] << " " << p.Y[1] << " " << p.Y[2] <<" " << p.Y[3] << " " << p.Y[4] <<"), and Generators : (" << p.A[0] << " " << p.A[1] << " " << p.A[2] <<" " << p.A[3] << " " << p.A[4] <<") \n";

}


