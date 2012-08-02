#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#include "string.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;


int main(int argc, char *argv[])
{
    clock_t start, end;

    int list1[] = {1,2,1,3,1,1,1,1,1,1,1,1,1,1,1,1};
    int list2[] = {1,2,1,1,5,1,1,1,1,1,1,1,1,1,1,1};
    int base[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    vector<int> vec1(list1, list1+(sizeof(list1)/sizeof(list1[0])));
    vector<int> vec2(list2, list2+(sizeof(list2)/sizeof(list2[0])));
    vector<int> bvec(base, base+(sizeof(base)/sizeof(base[0])));

    cout<<"first "<<vec1[0];

    T A1(vec1);
    T A2(vec2);
    T B(bvec);

    T Array1[6], Array2[6];

    Array1[0] = A1;
    Array2[0] = A2;

    Polynomial X(Array1, B);
    cout<<"X "<<X;

    Polynomial M(Array2, B);
    cout<<"M "<<M;

    Polynomial sub(X-M);
    cout<<"sub "<<sub;

       
       return 0;


}
