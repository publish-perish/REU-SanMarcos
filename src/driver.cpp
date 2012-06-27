#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#include "string.h"
#include <bitset>
#include "boost/dynamic_bitset.hpp"
#include <time.h>

typedef std::vector<Polynomial> PolyVec;

using namespace std;

int main(int argc, char *argv[])
{
    if(argc<2)
    {
       cout<<"Usage: ./executables/average_case diameter (lowerbound) \n";
       return 0;
    }

       const int d_cubed = atoi(argv[1])*atoi(argv[1])*atoi(argv[1]); 
       const double lowerbound = (argv[2]) ? atoi(argv[2]) : (d_cubed/16.0);
       PolyVec best; //holds the xcos table's size many polynomial: gives the history
       PolyVec temp;
       boost::dynamic_bitset<> cover(d_cubed); // diam cubed: larger than needed, but hard to make sharp
       bool covered =false;
       int counter = 0; //index for the bit array
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
       Polynomial null;
       Polynomial mbest; //holds the highest valid m
       clock_t start, end;

    
    start = clock();
 	best.resize(d_cubed);
	temp.resize(d_cubed);
    gens.open("./permutationtables/gentable.txt");
    if(gens)
    {
	    while(!gens.eof())
	    {
		    gens >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> A;
		    cout << A << endl;
		    mcos.open("./permutationtables/mcotable.txt");
		    if(mcos)
		    {
			    while(!mcos.eof())
			    {
				    mcos >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> Q;
				    M = Polynomial(A, Q);
				    //cout <<  m << endl;;
				    //memset(cover,false,diamCubed);
                cover.reset();
				    //cout << "memset success" << endl;
				    if( M.sum() > mbest.sum() && M.wellFormed()) //ignore M that are too small, or badly formed
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
                            cout<< "generators: "<<A <<endl;
							    //	cout << x << endl;
								    X = Polynomial(A, x);
								    //cout << "assigned poly" << A << Q << x << endl;
								    //cout << "cleared" << endl;
								    cout <<"X "<< X <<" - "<< "M " << M;
								    Adj = X-M;
								    //cout << "count" << counter << endl;
								    temp.at(counter) = Adj;
                            //best.push_back(null);
								    //cout << "subtraction done" << endl;
                            cout<< "Adj "<<Adj<<Adj.s;
                            cout<< "cover "<<Adj.sum()<<"\n \n";
								    cover[Adj.sum()] = 1;							
								    ++counter;
							    }// end xcos loop
						    //cout << "out of the while" << endl;
						    xcos.close();
					    //	cout << "xcos closed" << endl;
						    covered = true;
						    for(int i=0; i < M.sum(); ++i) //only check the first m of them
						    {
							    if(!cover[i]) //we are not covered
							    {
								    covered = false;
								    break;
							    }
						    }
						    if(covered)
						    {
							    mbest=M;
							    for(int j =0; j < mbest.sum(); ++j)
								    {
									    best[j] = temp[j];
								    }
						    //	cout << m << endl << A  << endl;
						    }
					  }
			    }// done with xcos
		    }   mcos.close();			
	    }// done with mcos
    }  gens.close();
    end = clock();
    cout<< "Program ran for "<< (double)(end - start)/(double)CLOCKS_PER_SEC <<" seconds. \n";
//need to write out mbest and best to a file.	
out.open("./results.txt");
if(out)
	{
		out << "modulus: " << mbest << endl;
		out << "generators: " << best[0].A << endl;
		for(int i=0; i < mbest.sum(); ++i)
		{
			out << best[i];
         out << best[i].s;
		}
	   out<< "Program ran for "<< (double)(end - start)/(double)CLOCKS_PER_SEC <<" seconds. \n";
   }
    }// done with genscos
return 0;
}
