#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#include "string.h"
#include <bitset>
#include "boost/dynamic_bitset.hpp"
#include <time.h>

typedef std::vector<Polynomial> PolyVec;
typedef std::vector< std::vector<Polynomial> > MultiVec;

using namespace std;

int main(int argc, char *argv[])
{
    if(argc<8)
    {
       cout<<"Usage: ./executables/average_case diameter (generators) (m-coefficients) \n";
       return 0;
    }
       const int diam = atoi(argv[1]);
       const double d_cubed = diam*diam*diam;
       MultiVec best(d_cubed, std::vector<Polynomial>(0)); //holds the xcos table's size many polynomial: gives the history
       MultiVec temp(d_cubed, std::vector<Polynomial>(0));
       boost::dynamic_bitset<> cover(d_cubed); // diam cubed: larger than needed, but hard to make sharp
       bool covered =false;
       int counter = 0; //index for the bit array
       ofstream out; //output
       T A = T(atoi(argv[2]), atoi(argv[3]), atoi(argv[4])); //generators
       T Q = T(atoi(argv[5]), atoi(argv[6]), atoi(argv[7])); //m coefs
       T x; //x coefs
       Polynomial X;
       Polynomial M; //the bound itself
       Polynomial Adj;
       Polynomial mbest = Polynomial(T(0,0,0), T(0,0,0)); //holds the highest valid m
       clock_t start, end;

    
    start = clock();
    M = Polynomial(A, Q);
    cout<< "A "<<A<<"Q "<< Q;
    cout << M <<endl;
       ifstream xcos("./permutationtables/cotable.txt");
int n=0;
       if(xcos)
       {
             while(xcos >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> x)
             {
cout<< "x "<<x<<endl<<endl;
                X = Polynomial(A, x);
                      if(X.wellFormed())
                      {
                       Adj = X-M;
                      // cout<< Adj;
                       
                           temp[Adj.sum()].push_back(Adj);
                           cover[Adj.sum()] = 1;	
                           cout<<"Adj"<<endl;
                           /*for(int i=0; i<temp[Adj.sum()].size();++i)
                           {
                           cout<< temp[Adj.sum()][i];
                           }*/
                      }else n++;
             }// end xcos loop
          xcos.close();
          covered = true;
          cout<<"M sum "<<M.sum()<<endl;
          for(int i=0; i < M.sum(); ++i) //only check the first m of them
          {
             if(cover[i]==0) //we are not covered
             {
               //cout << "uncovered: " << i << endl;
                covered = false;cout<< "not covering "<<i<<endl;
                break;
             }
             //cout<<"i "<<i<<endl;
          }
          if(covered)
          {cout<<"covering "<<endl;
             mbest=M;
             for(int j =0; j < mbest.sum(); ++j)
                {
                      for(int k=0; k < temp[j].size(); ++k)
                      {
                        best[j].push_back(temp[j][k]);
                      }
                }
          }
       }
 
    end = clock();cout<<n<<" not well formed"<<endl;
    cout<< "Program ran for "<< (double)(end - start)/(double)CLOCKS_PER_SEC <<" seconds. \n";

out.open("./analysis.txt");
if(out)
	{
      int n = 0;
		out << "d: " << argv[1] << endl;
		out << "modulus: " << mbest << endl;
		out << "generators: " << mbest.A << endl<<endl;

		for(int i=0; i < mbest.sum(); ++i)
		{
         out << "The best of "<< best[i].size() <<" from the "<<best[i][0].Y <<" coeffs" <<endl;
         for(int j=0; j< best[i].size(); ++j)
         {  
            out << best[i][j].s<<endl;
            n++;
         }
         out<<endl;
		}
	   out<< "Program ran for "<< (double)(end - start)/(double)CLOCKS_PER_SEC <<" seconds. \n";
      out<< "With "<<n<<" x values"<<endl;
   }
out.close();
return 0;
}
