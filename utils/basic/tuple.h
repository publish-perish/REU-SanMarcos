#ifndef TUPLE_H
#define TUPLE_H

#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>

#define null_type *int NULL

using namespace std;

template<typename TP, int N>
class Tuple {
    
    public:

    vector<TP> data;

    Tuple<TP, N>()
    {
        data.resize(N);
        for( size_t i=0; i<N; i++)
            data[i] = 0;
    }

    Tuple<TP, N>(vector<TP> list)
    {
        if( list.size() > N )
            throw string("Error: Invalid input size");
        
        data.resize(list.size());
        for(size_t i=0; i<list.size(); i++)
            data[i] = list[i];
    }

    Tuple<TP, N>(const Tuple<TP, N> &t)
    {
        data.resize(N);
        for(size_t i=0; i<t.size(); i++)
            data[i] = t[i];
    }

    Tuple<TP, N>(const TP& a, const TP& b, const TP& c)
    {
        data.resize(N);
        data[0] = a;
        data[1] = b;
        data[2] = c;
    }
 
    Tuple<TP, N>(TP& a, TP& b, TP& c )
    {
        data.resize(N);
        data[0] = a;
        data[1] = b;
        data[2] = c;
    }
    
    Tuple<TP, N>(const TP& a, const TP& b, const TP& c, const TP& d)
    {
        data.resize(N);
        data[0] = a;
        data[1] = b;
        data[2] = c;
        data[3] = d;
    }
 
    Tuple<TP, N>(TP& a, TP& b, TP& c, TP& d)
    {
        data.resize(N);
        data[0] = a;
        data[1] = b;
        data[2] = c;
        data[3] = d;
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
    Tuple operator=(Tuple&);

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

    Tuple<TP, N> get_tail()const
    {
        Tuple<TP, N> temp(data);
        temp.data.erase(temp.data.begin());
        return temp;
    }
};

typedef Tuple<int, 3> T;
typedef Tuple<int, 4> T4;

template<typename TP, int N>
Tuple<TP, N> operator-(const Tuple<TP, N> &lhs, const Tuple<TP, N> &rhs)
{
   vector<TP> list;

   for(int i; i<N; i++)
   {
       list.push_back(lhs.data.at(i)-rhs.data.at(i));
   }
   return Tuple<TP, N>(list);
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

// Recursive

template<typename TP, int N>
bool operator==(const Tuple<TP, N>& lhs, const Tuple<TP, N>& rhs) {
    if(rhs.size() == lhs.size()) return eq(lhs, rhs);
}

template<typename TP, int N>
bool operator!=(const Tuple<TP, N>& lhs, const Tuple<TP, N>& rhs) {
    if(rhs.size() == lhs.size()) return neq(lhs, rhs);
}

template<typename TP, int N>
bool operator<(const Tuple<TP, N>& lhs, const Tuple<TP, N>& rhs) {
    if((rhs.size() == lhs.size()) && (lhs == rhs)) return false;
    else if(rhs.size() == lhs.size()) return lt(lhs, rhs);
}

template<typename TP, int N>
bool operator>(const Tuple<TP, N>& lhs, const Tuple<TP, N>& rhs) {
    if((rhs.size() == lhs.size()) && (lhs == rhs)) return false;
    else if(rhs.size() == lhs.size()) return gt(lhs, rhs);
}

template<typename TP, int N>
bool operator<=(const Tuple<TP, N>& lhs, const Tuple<TP, N>& rhs) {
    Tuple<TP, N> zero;
    if((rhs.size() == lhs.size()) && (lhs == rhs)) return true;
    else if(rhs.size() == lhs.size()) return lteq(lhs, rhs);
}

template<typename TP, int N>
bool operator>=(const Tuple<TP, N>& lhs, const Tuple<TP, N>& rhs) {
    if((rhs.size() == lhs.size()) && (lhs == rhs)) return true;
    else if(rhs.size() == lhs.size()) return gteq(lhs, rhs);
}

// Comparison

template<typename TP, int N>
bool eq(const Tuple<TP, N>& lhs, const Tuple<TP, N>& rhs) {
  if ((lhs.data.size() == 1)){ return lhs[0] == rhs[0]; }
  else return lhs[0] == rhs[0] && eq(lhs.get_tail(),rhs.get_tail());
}

template<typename TP, int N>
bool neq(const Tuple<TP, N>& lhs, const Tuple<TP, N>& rhs) {
 if (lhs.data.size() == 1){ return lhs[0] != rhs[0]; }
 else return lhs[0] != rhs[0] || neq(lhs.get_tail(), rhs.get_tail());
}

template<typename TP, int N>
bool lt(const Tuple<TP, N>& lhs, const Tuple<TP, N>& rhs) {
    if (lhs.data.size() == 1){ return lhs[0] < rhs[0]; }
    else return lhs[0] < rhs[0] || ( !(rhs[0] < lhs[0]) && lt(lhs.get_tail(), rhs.get_tail()));
}

template<typename TP, int N>
bool gt(const Tuple<TP, N>& lhs, const Tuple<TP, N>& rhs) {
    if (lhs.data.size() == 1){ return lhs[0] > rhs[0]; }
    else return lhs[0] > rhs[0] || ( !(rhs[0] > lhs[0]) && gt(lhs.get_tail(), rhs.get_tail()));
}

template<typename TP, int N>
bool lteq(const Tuple<TP, N>& lhs, const Tuple<TP, N>& rhs) {
  if (lhs.data.size() == 1){ return lhs[0] <= rhs[0]; }
  else return lhs[0] <= rhs[0] && ( !(rhs[0] <= lhs[0]) || lteq(lhs.get_tail(), rhs.get_tail()));
}

template<typename TP, int N>
bool gteq(const Tuple<TP, N>& lhs, const Tuple<TP, N>& rhs) {
  if (lhs.data.size() == 1){ return lhs[0] >= rhs[0]; }
  else return lhs[0] >= rhs[0] && ( !(rhs[0] >= lhs[0]) || gteq(lhs.get_tail(), rhs.get_tail()));
}


// Class Functions

template<typename TP, int N>
Tuple<TP, N> Tuple<TP, N>::operator=(const Tuple<TP, N> &t)
{
   data.resize(N);
   for(int i=0; i<N; i++)
   {
      data[i] = t[i];
   }
   return *this;
}

template<typename TP, int N>
Tuple<TP, N> Tuple<TP, N>::operator=(Tuple<TP, N> &t)
{
   data.resize(N);
   for(int i=0; i<N; i++)
   {
      data[i] = t[i];
   }
   return *this;
}

// Recursive

template<typename TP, int N>
bool Tuple<TP, N>::operator==(const Tuple<TP, N>& rhs) {
    if(size() == rhs.size()) return eq(*this, rhs);
}

template<typename TP, int N>
bool Tuple<TP, N>::operator!=(const Tuple<TP, N>& rhs) {
    if(size() == rhs.size()) return neq(*this, rhs);
}

template<typename TP, int N>
bool Tuple<TP, N>::operator<(const Tuple<TP, N>& rhs){
    if((size() == rhs.size()) && (*this == rhs)) return false;
    else if(size() == rhs.size()) return lt(*this, rhs);
}

template<typename TP, int N>
bool Tuple<TP, N>::operator>(const Tuple<TP, N>& rhs) {
    if((size() == rhs.size()) && (*this == rhs)) return false;
    else if(size() == rhs.size()) return gt(*this, rhs);
}

template<typename TP, int N>
bool Tuple<TP, N>::operator<=(const Tuple<TP, N>& rhs) {
    if((size() == rhs.size()) && (*this == rhs)) return true;
    else if(size() == rhs.size()) return lteq(*this, rhs);
}

template<typename TP, int N>
bool Tuple<TP, N>::operator>=(const Tuple<TP, N>& rhs) {
    if((size() == rhs.size()) && (*this == rhs)) return true;
    else if(size() == rhs.size()) return gteq(*this, rhs);
}



#endif
