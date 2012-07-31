#include "../basic/polynomials.h"

Polynomial::Polynomial()
{
   vector<int> list;
   list.resize(A.size());
   A = T(list);
   Y = T(list);
   s = 0;
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
   return (A[0]*Y[0]);
}

int Polynomial::sum()const
{
   int sum=0, i;
   for(i=0; i<Y.size(); ++i)
   {
       sum += A[i]*Y[i];
   }
   return sum;
}

bool Polynomial::wellFormed()const
{
   if(Y[5] < (float)(A[0]/A[5])) return false;
   else if(Y[9] < (float)(A[5]/A[9])) return false;
   else if(Y[12] < (float)(A[9]/A[12])) return false;
   else if(Y[14] < (float)(A[12]/A[14])) return false;
   return true;
}

bool Polynomial::operator==(const Polynomial &p)
{
    int i;
    for(i=0; i<Y.size(); ++i)
    {
        if(Y[i] != p.Y[i]) return false;
    }
    return true;
}

bool Polynomial::operator>=(const Polynomial &p)
{
}

bool Polynomial::operator!=(const Polynomial &p)
{
    int i;
    for(i=0; i<Y.size(); ++i)
    {
        if(Y[i] == p.Y[i]) return false;
    }
    return true;
}

bool Polynomial::operator!=(int num) 
{
    int i;
    for(i=0; i<Y.size(); ++i)
    {
        if(Y[i] == num) return false;
    }
    return true;
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
    int i, j, offset[4] = {5, 9, 12, 14};
    loop:
    while( Y > m.Y )
    {
    cout<<"Subtracting m : "<<*this<<" minus "<< m<< " with generators "<<A;
        ++s.m;
        for(i=0; i<Y.size(); ++i)
        {
            Y[i] -= m.Y[i];
        }
    }
    cout<<"Subtracted "<<s.m<<" M to get "<<*this;
    for(i=1; i<5; ++i) // carry from first term
    {
        while(Y[i] >= A[offset[i-1]])
        {
            cout<<"Carrying b"<<i<<" by subtracting A"<<j<<"= "<<A[j]<<" from Y"<<j<<"= "<<Y[j]<<endl;
            for(j=i; j<(offset[i]-offset[i-1]); ++j)
            {cout<<"A"<<j<<"="<<A[j]<<" Y"<<j<<"="<<Y[j]<<"\n";
                Y[j] -= A[j];
                --s.b[j];
            }
        }
    }cout<<"M : "<<*this;
	while( Y[5] < 0 ) // borrow from first term
    {
          cout<<"Borrowing b\n";
          for(i=5; i<17; ++i)
          {
              Y[i] += A[i-1];
              ++s.b[i];
          }
    }cout<<"M : "<<*this;
    for(i=6; i<9; ++i) // carry from second term
    {
        while(Y[i] >= A[offset[i-6]])
        {
            cout<<"Carrying c"<<i<<"\n";
            for(j=i; j<(offset[i]-offset[i-6]); ++j)
            {
                Y[j] -=A[j];
                --s.c[i];
            }
        }
    }
	while( Y[9] < 0 ) // borrow from second term
    {
          cout<<"Borrowing c\n";
          for(i=9; i<17; ++i)
          {
              Y[i] += A[i-1];
              ++s.c[i];
          }
    }
    for(i=10; i<12; ++i) // carry from third term
    {
        while(Y[i] >= A[offset[i-10]])
        {
            cout<<"Carrying d\n";
            for(j=i; j<(offset[i]-offset[i-10]); ++j)
            {
                Y[j] -= A[j];
                --s.d[j];
            }
        }
    }
    while( Y[13] < 0 ) //borrow from third term
    {
          cout<<"Borrowing d\n";
          for(i=13; i<17; ++i)
          {
              Y[i] += A[i-1];
              ++s.d[i];
          }
    }
    for(i=13; i<15; ++i) // carry from first term
    {
        while(Y[i] >= A[offset[i-13]])
        {
            cout<<"Carrying e"<<i<<"\n";
            for(j=i; j<(offset[i]-offset[i-13]); ++j)
            {
                Y[j] -= A[j];
                --s.d[j];
            }
        }
    }
    while( Y[15] < 0 ) //borrow from fourth term
    {
          cout<<"Borrowing e\n";
          for(i=15; i<17; ++i)
          {
              ++s.e[i];
              Y[i] += A[i-1];
          }
    }
    if( Y > m.Y ){ goto loop; } 


    return *this;
}

std::ostream& operator<<(std::ostream& ostr, const Polynomial &p)
{

ostr <<"A : ("<< p.Y[0] <<" " << p.Y[1] << " " << p.Y[2] <<" " << p.Y[3] << " " << p.Y[4] <<")\n";
ostr <<"B : ("<< p.Y[5] << " "<< p.Y[6]<< " "<< p.Y[7] <<" "<< p.Y[8] <<")\n";
ostr <<"C : ("<< p.Y[9] <<" "<<p.Y[10] <<" " <<p.Y[11] <<")\n";
ostr <<"D : ("<< p.Y[12] <<" "<<p.Y[13]<<")\n";
ostr <<"E : "<<p.Y[14]<<"\n";
ostr <<"F : "<< p.Y[15] <<"\n";

}

std::ofstream& operator<<(std::ofstream& ofstr, const Polynomial &p)
{

ofstr <<"A : ("<< p.Y[0] <<" " << p.Y[1] << " " << p.Y[2] <<" " << p.Y[3] << " " << p.Y[4] <<")\n";
ofstr <<"B : ("<< p.Y[5] << " "<< p.Y[6]<< " "<< p.Y[7]<< " "<< p.Y[8] <<")\n";
ofstr <<"C : ("<< p.Y[9] <<" "<<p.Y[10] <<" " <<p.Y[11] <<")\n";
ofstr <<"D : ("<< p.Y[12] <<" "<<p.Y[13]<<")\n";
ofstr <<"E : "<<p.Y[14]<<"\n";
ofstr <<"F : "<< p.Y[15] <<"\n";

}


