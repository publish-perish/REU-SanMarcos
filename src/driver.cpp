#include "../utils/basic/permutations.h"
using namespace std;
///*
int main()
{
T next;
ifstream cot;
cot.open("cotable.txt");
if(!cot)
	cout << "Couldn't open" << endl;
else
{
while(!cot.eof())
{
	cot >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> next;
	cout <<next;
}
}

}
//*/
/*
int main()
{
CoefTable C;
GenTable G;
//std::cout << "Coefficients:";
C.makeCoTable(30); // takes diameter
C.makeMcoTable(30); //takes an arbitrary? bound
//std::cout << "\n Generators: \n";
G.makeGenTable(30); //arbitrary? bound
std::cout <<"\n cotSize:" << C.getCotSize() << "\n mtSize:" << C.getMtSize() << "\n gSize:" << G.getGsize() << endl;
return 0;
#include "../utils/basic/subtraction.h"

int main()
{
T A = T(2,12,12);
T B = T(0,3,2);
A.subtract(B);

}
*/
