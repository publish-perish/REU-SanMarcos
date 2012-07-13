#ifndef TUPLE_H
#define TUPLE_H

#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

template<typename TP, int N>
class Tuple {
    
    public:

    vector<TP> data;

    explicit Tuple<TP, N>()
    {
        data.resize(N);
        for( size_t i=0; i<N; i++)
            data[i] = 0;
    }

    explicit Tuple<TP, N>(vector<TP> list)
    {
        if( list.size() > N )
            throw string("Error: Invalid input size");
        
        data.resize(N);
        for(size_t i=0; i<list.size(); i++)
            data[i] = list[i];
    }

    explicit Tuple<TP, N>(const Tuple<TP, N> &t)
    {
        data.resize(N);
        for(size_t i=0; i<t.size(); i++)
            data[i] = t[i];
    }

    explicit Tuple<TP, N>( const TP& a, const TP& b, const TP& c )
    {
        data.resize(N);
        data[0] = a;
        data[1] = b;
        data[2] = c;
    }
    
    Tuple(Tuple<TP, N> &t)
    {
        data.resize(N);
        for(size_t i=0; i<t.size(); i++)
        {
            data[i] = t[i];
        }
    }


    size_t size()const
    {
        return N;
    }


    Tuple operator-(const Tuple&);
    bool operator==(const Tuple&);
    bool operator<(const Tuple&);
    bool operator>(const Tuple&);
    bool operator>=(const Tuple&);
    bool operator<=(const Tuple&);
    bool operator!=(const Tuple&);
    Tuple operator=(const Tuple&);

    ostream& operator<<(ostream& ostr);
    ofstream& operator<<(ofstream& ofstr);
    istream& operator>>(istream& istr);
    ifstream& operator>>(ifstream& ifstrt);

    TP operator[](const size_t& idx)const
    {
        if( idx >= N )
            throw string("Error: invalid index");
        
        return data[idx];
    }

    TP& operator[](const size_t& idx)
    {
        return data[idx];
    }
};

typedef Tuple<int, 3> T;

template<typename TP, int N>
Tuple<TP, N> operator-(const Tuple<TP, N> &t1, const Tuple<TP, N> &t2)
{
   vector<TP> list;

   for(int i; i<sizeof(t1); i++)
   {
       list.push_back(t1.data.at(i)-t2.data.at(i));
   }
   return Tuple<TP, N>(list);
}

template<typename TP, int N>
bool operator==(const Tuple<TP, N> &t1, const Tuple<TP, N> &t2)
{
   for(int i=0; i<sizeof(t1); i++)
   {
      if(t1.data.at(i) != t2.data.at(i))
      {
         return false;
      }
   }
   return true;
}

template<typename TP, int N>
bool operator>(const Tuple<TP, N> &t1, const Tuple<TP, N> &t2)
{
   for(int i=0; i<sizeof(t1); i++)
   {
      if(t1.data.at(i) <= t2.data.at(i))
      {
         return false;
      }
   }
   return true;
}

template<typename TP, int N>
bool operator<(const Tuple<TP, N> &t1, const Tuple<TP, N> &t2)
{
   for(int i=0; i<sizeof(t1); i++)
   {
      if(t1.data.at(i) >= t2.data.at(i))
      {
         return false;
      }
   }
   return true;
}

template<typename TP, int N>
bool operator>=(const Tuple<TP, N> &t1, const Tuple<TP, N> &t2)
{
   for(int i=0; i<sizeof(t1); i++)
   {
      if(t1.data.at(i) < t2.data.at(i))
      {
         return false;
      }
   }
   return true;
}

template<typename TP, int N>
bool operator<=(const Tuple<TP, N> &t1, const Tuple<TP, N> &t2)
{
   for(int i=0; i<sizeof(t1); i++)
   {
      if(t1.data.at(i) > t2.data.at(i))
      {
         return false;
      }
   }
   return true;
}

template<typename TP, int N>
bool operator!=(const Tuple<TP, N> &t1, const Tuple<TP, N> &t2)
{
   for(int i=0; i<sizeof(t1); i++)
   {
      if(t1.data.at(i) != t2.data.at(i))
      {
         return false;
      }
   }
   return true;
}

template<typename TP, int N>
ostream& operator<<(ostream& ostr, const Tuple<TP, N> &t)
{
    ostr << "(";
    for(size_t i=0; i<N; i++){
        ostr << t.data[i];
        if( i+1 < N)
            ostr << ",";
    }
    ostr << ")";
    return ostr;
}

template<typename TP, int N>
ofstream& operator<<(ofstream& ofstr, const Tuple<TP, N> &t)
{
    ofstr << "(";
    for(size_t i=0; i<N; i++){
        ofstr << t.data[i];
        if( i+1 < N)
            ofstr << ",";
    }
    ofstr << ")";
    return ofstr;
}

template<typename TP, int N>
istream& operator>>(istream& istr, Tuple<TP, N> &t)
{
    char d;
    istr >> d;
    for(size_t i=0; i<N; i++){
        istr >> t.data[i];
        if( i+1 < N)
            istr >> d;
    }
    istr >> d;
    return istr;
}

template<typename TP, int N>
ifstream& operator>>(ifstream& ifstr, Tuple<TP, N> &t)
{
    char d;
    ifstr >> d;
    for(size_t i=0; i<N; i++){
        ifstr >> t.data[i];
        if( i+1 < N)
            ifstr >> d;
    }
    ifstr >> d;
    return ifstr;
}

// Class Functions

template<typename TP, int N>
Tuple<TP, N> Tuple<TP, N>::operator=(const Tuple<TP, N> &t)
{
   Tuple<TP, N> out;

   for(int i=0; i<N; i++)
   {
      out[i] = t[i];
   }
   return out;
}

template<typename TP, int N>
bool Tuple<TP, N>::operator>(const Tuple<TP, N> &t)
{
   for(int i=0; i<sizeof(t); i++)
   {
      if(data.at(i) <= t.data.at(i))
      {
         return false;
      }
   }
   return true;
}


#endif
