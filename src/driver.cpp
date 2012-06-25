#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"

using namespace std;
///*

/*
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
*/
///*
int main()
{
CoefTable C;
GenTable G;
//std::cout << "Coefficients:";
C.makeCoTable(30); // takes diameter
C.makeMcoTable(10); //takes an arbitrary? bound
//std::cout << "\n Generators: \n";
G.makeGenTable(30); //arbitrary? bound
std::cout <<"\n cotSize:" << C.getCotSize() << "\n mtSize:" << C.getMtSize() << "\n gSize:" << G.getGsize() << endl;
return 0;
}
//*/
