#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#include "string.h"
#include <bitset>
#include <time.h>
#include <iterator>

typedef std::vector<Polynomial> PolyVec;

using namespace std;



int makeTables(int diam, XCoTable *X, GenTable *A)
{cout<<"making tables "<<endl;
    clock_t start, end;
    start = clock();
    X->makeXCoTable(diam);
    cout <<"\nSize of X-Coefficient Table = " << X->size << endl << endl;
    A->makeGenTable(diam);
    cout <<"\nSize of Generator Table = " << A->size << endl;
    end = clock();
    cout<<"Tables were generated in "<<(double)(end - start)/(double)CLOCKS_PER_SEC<<" seconds.\n";
    return 0;
}


int main(int argc, char *argv[])
{
    if(argc<2)
    {
       cout<<"Usage: ./executables/average_case diameter (lowerbound) \n";
       return 0;
    }
	   XCoTable XTable;
       MCoTable QTable;
       GenTable ATable;
       const int diam = atoi(argv[1]);
       //const int d_cubed = diam*diam*diam; 
       //const double lowerbound = (argv[2]) ? atoi(argv[2]) : (d_cubed/16.0);
       PolyVec best(diam*diam*diam*diam); //holds the xcos table's size many polynomial: gives the history
       PolyVec temp(diam*diam*diam*diam);
       vector<bool> cover; 
       bool covered =false;
       int counter = 0; //index 
       ifstream gens; // d, c, b, a
       ifstream mcos; // gamma, beta, alpha
       ifstream xcos; // x3, x2, x1
       ofstream out; //output
       ofstream archive;
       T4 A; //generators
       T4 Q; //m coefs
       T4 x; //x coefs
       Polynomial X;
       Polynomial M; //the bound itself
       Polynomial X_Prime;
       Polynomial mbest; //holds the highest valid m
       clock_t start, end;

    makeTables(diam, &XTable, &ATable);
    start = clock();
    gens.open("./permutationtables/gentable.txt");
    archive.open("./ms.txt");
    if(gens)
    {
	    while(gens >> A)
       {
          	//cout<< "A "<<A << endl;
		    QTable.makeMCoTable(diam, A[0], A[1], A[2]);
		    mcos.open("./permutationtables/MTable.txt");
		    if(mcos)
		    {
			    while(mcos >>  Q)
             {
				    M = Polynomial(A, Q);
				    //cout <<"M "<< M <<endl;
               		cover.clear();
               		cover.resize(diam*diam*diam*diam);
				    if( (M.value() > mbest.value())) /*&& M.wellFormed()) //*&& (M.sum() < d_cubed)*/ //ignore M that are too small, or badly formed (M.value() > lowerbound)
				    {
					    xcos.open("./permutationtables/XTable.txt");
					    if(xcos)
					    {
							while(xcos >> x)
                        	{
							X = Polynomial(A, x);
                           	X_Prime =  X-M;
                          	if(X_Prime.wellFormed())
                          	{
                          	temp.at(X_Prime.sum()) = X_Prime;
                          	cover[X_Prime.sum()] = true;	
                          	}
							}

						}// end xcos loop
						    xcos.close();
						    covered = true;
						    for(int i=0; i < M.sum(); ++i) //only check the first m of them
						    {
							    if(cover[i]==0) //we are not covered
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
								archive << mbest << mbest.A << endl;
						    }
				
					}// done with xcos
		    }  }mcos.close();// done with mcos
    }  }
    gens.close();
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
out.close();
archive.close();
return 0;

}
