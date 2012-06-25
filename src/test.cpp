#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#define diamCubed 1000
#define xSize 286
using namespace std;

int main()
{
   T v = T(4, 2, 3);  
   T a = T(3, 3, 1);
   T q = T(2, 3, 4);
   Subtractions s;

   Polynomial m;
   m = Polynomial(a, q);
   Polynomial x;
   x = Polynomial(a, v);

   Polynomial val = subtract(x, m, s);

   cout<< val.A<<endl;
   cout<< val.Y<<endl;
return 0;
}
