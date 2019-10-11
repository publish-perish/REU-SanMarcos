#include "../basic/polynomials.h"

Polynomial::Polynomial()
{
   vector<int> list;
   int i;
   for(i=0; i<Y.size(); i++)
   { 
       list.resize(A[i].size());
       A[i] = T(list);
       s[i] = 0;
   }
   Y = T(list);
}


Polynomial::Polynomial(T a[], T y)
{
   int i;
   for(i=0; i<Y.size(); ++i)
   {
        A[i] = a[i];
        s[i] = 0;
   }
   Y = y;
}

Polynomial::Polynomial(const Polynomial &p)
{
    int i;
    for(i=0; i<Y.size(); ++i)
    {
        A[i] = p.A[i];
        s[i] = p.s[i];
    }
    Y = p.Y;
}

int Polynomial::value()const
{
   return (A[0][0]*Y[0]);
}

int Polynomial::sum()const
{
    int i, j, sum=0;
    for(i=5; i>=0; --i)
    { 
        for(j=0; j<i; ++j)
        {
            sum+= A[i][j]*Y[i];
        }
    }
    return sum;
}

bool Polynomial::wellFormed()const //should just be A[i][i], and start at i = 1
{
   for(int i=0; i<Y.size()-1; ++i)
   {
        if(Y[i] > (A[i][i]/ A[i+1][i+1])) return false;
   }
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
return Y >= p.Y;
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
    int i;
    for(i=0; i<Y.size(); ++i)
    {
        A[i] = p.A[i];
        s[i] = p.s[i];
    }
    Y = p.Y;

	return *this;
}


Polynomial Polynomial::operator-(Polynomial m) 
{
    int i, j;

    loop:
    while( Y > m.Y )
    {
    cout<<"Subtracting m : "<<*this<<" minus "<< m;
        ++s[0];;
        for(i=0; i<Y.size(); ++i)
        {
            Y[i] -= m.Y[i];
        }
    }
    cout<<"Subtracted "<<s[0]<<" M to get "<<*this;
    for(i=0; i<6; ++i)
    {
        while( Y[i] < 0 ) // borrow from first term
        {
              cout<<"Borrowing e\n";
              for(j=i; j<6; ++j)
              {cout<<"Borrowing "<<i<<"th coeff by adding A"<<j-1<<"= "<<A[j-1]<<" from Y"<<j<<"= "<<Y[j]<<endl;
                  Y[i] += A[i][j];
              }
              ++s[i];
        }
        while(Y[i] > A[i][i])
        {
            for(j=i; j<6; ++j)
            {cout<<"Carrying "<<i<<"th coeff by subtracting A"<<j<<"= "<<A[j]<<" from Y"<<j<<"= "<<Y[j]<<endl;
                Y[i] -= A[i][j];
            }
            --s[i];
        }   
    }cout<<"M : "<<*this;
    
    if( Y > m.Y ){ goto loop; } 


    return *this;
}

std::ostream& operator<<(std::ostream& ostr, const Polynomial &p)
{
    int i,j;
    ostr <<"Y: (";
    for(i=0; i<p.Y.size(); ++i)
    {
        ostr << p.Y[i] <<" ";
    }
    ostr<<")\n";
    
    ostr <<"A: \n";
    for(i=0; i<p.Y.size(); ++i)
    {
    	//cout << "printing A's, i= "<< i << endl;
        ostr<<"(";
        ostr << p.A[i];
        ostr<<")\n";
    }
    //cout << "out clean" << endl;
    return ostr;
}

std::ofstream& operator<<(std::ofstream& ofstr, const Polynomial &p)
{
  int i,j;
    ofstr <<"Y: (";
    for(i=0; i<p.Y.size(); ++i)
    {
        ofstr << p.Y[i] <<" ";
    }
    ofstr<<")\n";
    
    ofstr <<"A: \n";
    for(i=0; i<p.Y.size(); ++i)
    {
        ofstr<<"(";
        ofstr << p.A[i];
        ofstr<<")\n";
    }
	return ofstr;
}


