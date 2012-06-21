//should be some header stuff up here?
#include "boost/tuple/tuple.hpp"
typedef typedef boost::tuple<int, int, int> tuple
typedef vector< tuple<int,int, int> > tuple_list;


const int coefBound = 20; //should never be larger than d
const int genBound =20;


class CoefTable
{
public:
int makeCoefTable();
tuple guessCoef();
int size();
private:
tuple_list CoefList;
int coCount;
}

class GenTable
{
public:
int makeGenTable();
tuple guessGen();
int size();
private:
tuple_list GenList;
int genCount;
}
