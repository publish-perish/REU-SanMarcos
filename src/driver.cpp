#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#include "string.h"
#include <bitset>
#include "boost/dynamic_bitset.hpp"
#include <time.h>
#include <iterator>

typedef std::vector<Polynomial> PolyVec;

using namespace std;


int makeTables(int diam, XCoTable *X, GenTable *A)
{
    clock_t start, end;
    start = clock();
    X->makeXCoTable(diam, 1);
    cout <<"Size of X-Coefficient Table = " << X->size;
    A->makeGenTable(diam);
    cout <<"\nSize of Generator Table = " << A->size;
    end = clock();
    cout<<"\nTables were generated in "<<(double)(end - start)/(double)CLOCKS_PER_SEC<<" seconds.\n";
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
       const int d_cubed = diam*diam*diam; 
       const double lowerbound = (argv[2]) ? atoi(argv[2]) : (d_cubed/16.0);
       PolyVec best(d_cubed); //holds the xcos table's size many polynomial: gives the history
       PolyVec temp(d_cubed);
       boost::dynamic_bitset<> cover(d_cubed); // diam cubed: larger than needed, but hard to make sharp
       bool covered =false;
       int counter = 0; //index for the bit array
       ifstream gens, xcoeffs, mcoeffs;
       ofstream out, archive;
       T A; //generators
       T Q; //m coefs
       T x; //x coefs
       Polynomial X;
       Polynomial M; //the bound itself
       Polynomial X_prime;
       Polynomial null;
       Polynomial mbest = Polynomial(T(0,0,0), T(0,0,0)); //holds the highest valid m
       
       clock_t start, end;
       start = clock();
       makeTables(diam, &XTable, &ATable);
       gens.open("./permutationtables/GenTable.txt");
       if(gens){
       archive.open("./ms.txt");
	    while(gens >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> A)
       {
          double c1 = get<0>(A)/get<1>(A);
		    QTable.makeMCoTable(diam, get<1>(A), c1, 1);
          mcoeffs.open("./permutationtables/MTable.txt");
          if(mcoeffs){
          while(mcoeffs >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> Q)
          {
             M = Polynomial(A, Q);
             cover.reset();
             if((M.value() > mbest.value())/* && M.wellFormed()*/ && (M.sum() < d_cubed)) //ignore M that are too small, or badly formed
             {
                xcoeffs.open("./permutationtables/XTable.txt");
                if(xcoeffs){
                while(xcoeffs >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> x)
                {
                   X = Polynomial(A, x);
                   X_prime = X-M;
                   if(true)//X_prime.wellFormed()){ 
                   temp.at(X_prime.sum()) = X_prime;
                   cover[X_prime.sum()] = 1;	
                }xcoeffs.close();
                // check covering
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
            }}
          }}mcoeffs.close();
       }}gens.close();
   end = clock();
//need to write out mbest and best to a file.	
   out.open("./results.txt");
   if(out)
      {
         out << "d: " << diam << endl;
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
   cout<< "Program ran for "<< (double)(end - start)/(double)CLOCKS_PER_SEC <<" seconds. \n";
 
   return 0;
}
