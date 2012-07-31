#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#include <iostream>

int main()
{
   T v = T(1, 0, 1);
// T a = T(3, 3, 1);
   T q = T(1, 0, 0);
   std::cout<<v;
// std::cout<<a;
   std::cout<<q;
   //Polynomial m(a, q);
   //std::cout<<"m "<< m;
   //std::cout<<m.A<<std::endl;
   //std::cout<<m.Y<<std::endl;
   //std::cout<<m.value()<<std::endl;
   //Polynomial x(a, v);
   //std::cout<<"x "<<x;
   //std::cout<< x.A<<std::endl;
   //std::cout<<x.Y<<std::endl;
   //std::cout<<x.value()<<std::endl;

  // Polynomial test;
   //test = m;
   //std::cout<<"'test = m' "<<test;
   //Polynomial val(x - m);

   //std::cout<< "Final value "<<val;
  // std::cout<< val.A<<std::endl;
   //std::cout<< val.Y<<std::endl;

bool b = v>q;
   std::cout<<(v>q)<<" "<<(v<q)<<endl;

return 0;
}
