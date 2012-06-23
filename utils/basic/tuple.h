#ifndef TUPLE_H
#define TUPLE_H

#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

template<typename TP, int N>
class Tuple {
    
    public:

    vector<TP> data;
    
    explicit Tuple(){
        data.resize(N);
        for( size_t i=0; i<N; i++)
            data[i] = 0;
    }
    
    explicit Tuple(vector<TP> list){
        if( list.size() > N )
            throw string("Error: Invalid input size");
        
        data.resize(N);
        for(size_t i=0; i<list.size(); i++)
            data[i] = list[i];
    }
    
    explicit Tuple( const TP& a, const TP& b, const TP& c ){
        data.resize(N);
        data[0] = a;
        data[1] = b;
        data[2] = c;
    }

    Tuple operator-(const Tuple&);

};

#endif
