#ifndef SUBTRACTION_H
#define SUBTRACTION_H





//#include "polynomials.h"



#include <vector>
#include <iostream>
#include <fstream>


//typedef boost::tuples::tuple<int, int, int> T;

class Subtractions{

    public:

    Subtractions();
    Subtractions(int);
    Subtractions(int, int, int, int, int, int);
    Subtractions(const Subtractions&);

    void clear();
   
	int e[5];
    int d[5];
    int c[5];
    int b[5];
    int m;

    Subtractions operator=(const Subtractions&);
    Subtractions operator=(int);
    Subtractions operator==(const Subtractions&);


    friend std::ostream& operator<<(std::ostream&, const Subtractions&);
    friend std::ofstream& operator<<(std::ofstream&, const Subtractions&);

};


#endif


