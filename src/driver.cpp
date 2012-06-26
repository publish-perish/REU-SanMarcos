#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#include "string.h"

#define diamCubed 125
#define xSize 60
using namespace std;

int main()
{
    const int diam = 5; //make sure this matches the diam used to generate the tables
    const double lowerbound = (1); // diam cubed over 16
    Polynomial best[xSize]; //holds the xcos table's size many polynomial: gives the history
    Polynomial temp[xSize];
    bool cover[diamCubed]; // diam cubed: larger than needed, but hard to make sharp
    bool covered =false;
    int counter = 0; //index for the temp array
    ifstream gens; // c, b, a
    ifstream mcos; // gamma, beta, alpha
    ifstream xcos; // x3, x2, x1
    ofstream out; //output
    T A; //generators
    T Q; //m coefs
    T x; //x coefs
    Polynomial X;
    Polynomial M; //the bound itself
    Polynomial Adj;
    int m; //holds sum of M
    int mbest = 0; //holds the highest valid m
    gens.open("./permutationtables/gentable.txt");
    if(gens)
    {
	    while(!gens.eof())
	    {
		    gens >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> A;
		    //cout << A << endl;
		    mcos.open("./permutationtables/mcotable.txt");
		    if(mcos)
		    {
			    while(!mcos.eof())
			    {
				    mcos >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> Q;
				    M = Polynomial(A, Q);
				    m = M.sum();
				    //cout <<  m << endl;;
				    memset(cover,false,diamCubed);
				    //cout << "memset success" << endl;
				    if( m >= mbest && M.wellFormed()) //ignore M that are too small, or badly formed
				    {
					    xcos.open("./permutationtables/cotable.txt");
					    counter = 0;
					    if(xcos)
					    {
							    while(!xcos.eof())
							    {
							    //cout << "in the while loop" << endl;
							    xcos >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> x;
							    //cout<< "read in"  << endl;
							    //	cout << x << endl;
								    X = Polynomial(A, x);
								    cout << "assigned poly" << A << Q << x << endl;
							    //	temp[counter].clear();
								    cout << "cleared" << endl;
								    cout << X << endl << M <<endl;
								    Adj = X-M;
								    cout << "count" << counter << endl;
								    temp[counter] = Adj;
								    cout << "subtraction done" << endl;
								    cover[Adj.sum()] = true;							
								    ++counter;
							    }
						    //cout << "out of the while" << endl;
						    xcos.close();
					    //	cout << "xcos closed" << endl;
						    covered = true;
						    for(int i=0; i < m; ++i) //only check the first m of them
						    {
							    if(!cover[i]) //we are not covered
							    {
								    covered = false;
								    break;
							    }
						    }
						    if(covered)
						    {
							    mbest=m;
							    for(int j =0; j < xSize; ++j)
								    {
									    best[j] = temp[j];
								    }
						    //	cout << m << endl << A  << endl;
						    }
					    }
				    }
						
			    }
			    mcos.close();			
		    }
	    }
    gens.close();
    }
//need to write out mbest and best to a file.	
out.open("./results.txt");
if(out)
	{
		out << "modulus: " << mbest << endl;
		out << "generators: " << best[0].A << endl;
		for(int i=0; i < mbest; ++i)
		{
			out << best[i];
		}
	}

return 0;
}
