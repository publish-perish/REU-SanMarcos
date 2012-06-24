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
    
    Tuple();
    Tuple(vector<TP> list);
    Tuple( const TP& a, const TP& b, const TP& c);
    
    size_t size()const;
    
    TP operator[](const size_t& idx)const;
    TP& operator[](const size_t& idx);
 
    Tuple operator-(const Tuple&);
    bool operator==(const Tuple&);
    bool operator<(const Tuple&);
    bool operator>(const Tuple&);
    bool operator>=(const Tuple&);
    bool operator<=(const Tuple&);

/*
    ostream& operator<<(ostream& ostr, const Tuple<TP,N>& t);
    ofstream& operator<<(ofstream& fstr, const Tuple<TP,N>& t);
*/

};

#endif
