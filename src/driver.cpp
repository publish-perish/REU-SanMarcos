#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#define diamCubed 1000
#define xSize 286
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
/*
int main()
{
CoefTable C;
GenTable G;
//std::cout << "Coefficients:";
C.makeCoTable(10); // takes diameter
C.makeMcoTable(10); //takes an arbitrary? bound
//std::cout << "\n Generators: \n";
G.makeGenTable(10); //arbitrary? bound
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
///*
int main()
{
const int diam = 10; //make sure this matches the diam used to generate the tables
const double lowerbound = (1000 / 16); // diam cubed over 16
Subtractions best[xSize]; //holds the xcos table's size many subtractions: gives the complete history
Subtractions temp[xSize];
bool cover[diamCubed]; // diam cubed: larger than needed, but hard to make sharp
bool covered =false;
int counter = 0; //index for the temp array
ifstream gens; // c, b, a
ifstream mcos; // gamma, beta, alpha
ifstream xcos; // x3, x2, x1
T A; //generators
T Q; //m coefs
T x; //x coefs
Polynomial M; //the bound itself
int m; //holds sum of M
int mbest = 0; //holds the highest valid m
gens.open("gentable.txt");
if(gens)
{
	while(!gens.eof())
	{
		gens >> A;
		mcos.open("mcotable.txt");
		if(mcos)
		{
			while(!mcos.eof())
			{
				mcos >> Q;
				M = Polynomial(A, Q);
				m = M.sum();
				memset(cover[],false,diamCubed);
				if( m >= mbest)
				{
					xcos.open("cotable.txt");
					counter = 0;
					if(xcos)
					{
						while(!xcos.eof())
						{
							xcos >> x;
							subtract(x, M, temp[counter]);
							cover[x.sum()] = true;							
							++counter;
							
						}
					xcos.close();
					covered = true;
					for(int i=0, i < m, ++i) //only check the first m of them
					{
						if(!cover[i]) //we are not covered
						{
							covered =false;
							break;
						}
					}
					if(covered)
					{
					best = temp;
					mbest =m;
					}
					}
				}
						
			}
			mcos.close();			
		}
	}
gens.close();
}
	
return 0;
}
//*/
