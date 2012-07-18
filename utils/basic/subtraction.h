#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "tuple.h"
#include "boost/tuple/tuple.hpp"
#include <vector>
#include <iostream>
#include <fstream>

using namespace boost::tuples;

//typedef boost::tuples::tuple<int, int, int> T;

class Subtractions{

    public:

    Subtractions();
    Subtractions(int);
    Subtractions(int, int, int, int);
    Subtractions(const Subtractions&);

    void clear();
   
    int d_borrowed;
    int c_borrowed;
    int b_borrowed;
    int m_subtracted;

    Subtractions operator=(const Subtractions&);
    Subtractions operator=(int);
    Subtractions operator==(const Subtractions&);


    friend std::ostream& operator<<(std::ostream&, const Subtractions&);
    friend std::ofstream& operator<<(std::ofstream&, const Subtractions&);

};


#endif


