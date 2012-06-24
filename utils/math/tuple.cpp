#include "../basic/tuple.h"

template<typename TP, int N>
Tuple<TP, N>::Tuple()
{
    data.resize(N);
    for( size_t i=0; i<N; i++)
        data[i] = 0;
}

template<typename TP, int N>
Tuple<TP, N>::Tuple(vector<TP> list)
{
    if( list.size() > N )
        throw string("Error: Invalid input size");
    
    data.resize(N);
    for(size_t i=0; i<list.size(); i++)
        data[i] = list[i];
}

template<typename TP, int N>
Tuple<TP, N>::Tuple( const TP& a, const TP& b, const TP& c )
{
    data.resize(N);
    data[0] = a;
    data[1] = b;
    data[2] = c;
}

template<typename TP, int N>
TP Tuple<TP, N>::operator[](const size_t& idx)const
{
    if( idx >= N )
        throw string("Error: invalid index");
    
    return data[idx];
}

template<typename TP, int N>
TP& Tuple<TP, N>::operator[](const size_t& idx)
{
    return data[idx];
}

template<typename TP, int N>
size_t Tuple<TP, N>::size()const
{
    return N;
}

template<typename TP, int N>
Tuple<TP, N> Tuple<TP, N>::operator-(const Tuple<TP, N> &t)
{
   double a, b, c; // temp variables for polynomial ax + bx^2 + cx^3
   bool flag = true;
   vector<TP> list;

   for(int i; i<sizeof(t); i++)
   {
      if( data.at(i) < t.data.at(i))
      {
         flag = false;
      }
      else
      {
         list.push_back(data.at(i)-t.data.at(i));
      }

   }
   if(flag)
   {
      return Tuple<TP, N>(list);
   }
}

template<typename TP, int N>
bool Tuple<TP, N>::operator==(const Tuple<TP, N> &t)
{
   for(int i; i<sizeof(t); i++)
   {
      if(data.at(i) != t.data.at(i))
      {
         return false;
      }
   }
   return true;
}

template<typename TP, int N>
bool Tuple<TP, N>::operator>(const Tuple<TP, N> &t)
{
   for(int i; i<sizeof(t); i++)
   {
      if(data.at(i) <= t.data.at(i))
      {
         return false;
      }
   }
   return true;
}

template<typename TP, int N>
bool Tuple<TP, N>::operator<(const Tuple<TP, N> &t)
{
   for(int i; i<sizeof(t); i++)
   {
      if(data.at(i) >= t.data.at(i))
      {
         return false;
      }
   }
   return true;
}

template<typename TP, int N>
bool Tuple<TP, N>::operator>=(const Tuple<TP, N> &t)
{
   for(int i; i<sizeof(t); i++)
   {
      if(data.at(i) < t.data.at(i))
      {
         return false;
      }
   }
   return true;
}

template<typename TP, int N>
bool Tuple<TP, N>::operator<=(const Tuple<TP, N> &t)
{
   for(int i; i<sizeof(t); i++)
   {
      if(data.at(i) > t.data.at(i))
      {
         return false;
      }
   }
   return true;
}

template<typename TP, int N>
ostream& operator<<(ostream& ostr, const Tuple<TP,N>& t)
{
    ostr << "( ";
    for(size_t i=0; i<N; i++){
        ostr << t[i];
        if( i+1 < N)
            ostr << ", ";
    }
    ostr << " )";
    return ostr;
}

template<typename TP, int N>
ofstream& operator<<(ofstream& ofstr, const Tuple<TP,N>& t)
{
    ofstr << "( ";
    for(size_t i=0; i<N; i++){
        ofstr << t[i];
        if( i+1 < N)
            ofstr << ", ";
    }
    ofstr << " )";
    return ofstr;
}
