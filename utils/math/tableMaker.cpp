"../basic/permutations.h"
#include "boost/tuple/tuple.hpp"
#include <iterator>
int main()
{
ofstream myfile ("cotable.txt");
  if (myfile.is_open())
  {
    myfile << "This is a line.\n";
    myfile << "This is another line.\n";
    myfile.close();
  }
  else cout << "Unable to open file";

return 0;
}
