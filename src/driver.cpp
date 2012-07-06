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
	   CoefTable C;
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
       ofstream archive;
       T A; //generators
       T Q; //m coefs
       T x; //x coefs
       Polynomial X;
       Polynomial M; //the bound itself
       Polynomial Adj;
       Polynomial null;
       Polynomial mbest = Polynomial(T(0,0,0), T(0,0,0)); //holds the highest valid m
       clock_t start, end;

    
    start = clock();
 	 best.resize(d_cubed);
	 temp.resize(d_cubed);
    gens.open("./permutationtables/gentable.txt");
    archive.open("./ms.txt");
    if(gens)
    {
	    while(gens >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> A)
       {
		    //cout << A << endl;
		    C.makeMcoTable(atoi(argv[1]), get<1>(A), (float)(get<0>(A) / get<1>(A)));
		    mcos.open("./permutationtables/mcotable.txt");
		    if(mcos)
		    {
			    while(mcos >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> Q)
             {
				    M = Polynomial(A, Q);
				    //cout << M <<endl;
               		cover.reset();
				    if( (M.value() > mbest.value()) && M.wellFormed() && (M.sum() < d_cubed)) //ignore M that are too small, or badly formed (M.value() > lowerbound)
				    {
					    xcos.open("./permutationtables/cotable.txt");
					    if(xcos)
					    {
							    while(xcos >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> x)
                         {
								    X = Polynomial(A, x);


                          	 		 
                          		     Adj = X-M;
                          		     if(Adj.wellFormed())
                          		     {
                          		     temp.at(Adj.sum()) = Adj;
                          		     cover[Adj.sum()] = 1;	
                          		     //cout << Adj << endl;
                          			 }

							    }// end xcos loop
						    xcos.close();
						    covered = true;
						    for(int i=0; i < M.sum(); ++i) //only check the first m of them
						    {
							    if(cover[i]==0) //we are not covered
							    {
							    	//cout << "uncovered: " << i << endl;
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
								archive << mbest << mbest.A << endl;
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
		out << "d: " << argv[1] << endl;
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
out.close();
archive.close();
return 0;
}
