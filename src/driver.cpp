#include "../utils/basic/tuple.h"
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#include "string.h"
#include <time.h>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <numeric>

#define WORKTAG 1
#define DIETAG 2

typedef std::vector<Polynomial> PolyVec;


void master(int, int&, Polynomial&);
void slave(int, T6&, Polynomial&);
void check_cover(int, T6&, Polynomial&);
void print_cover(vector<bool>, int);

int main (int argc, char *argv[]) {
  if(argc<2)
  {
     printf("Usage: ./executables/average_case diameter (lowerbound) \n");
     return 0;
  }

  int i, numgens=0;
  const int diam = atoi(argv[1]);
  clock_t start, end;
  Polynomial mbest;

  start = clock();

  master(diam, numgens, mbest);

 
    end = clock();

    if(mbest != 0)
    {
        printf("\nDiameter: %d \nGenerators: (%d, %d, %d, %d, %d, %d), Location: (%d, %d, %d, %d, %d)\n", diam, mbest.A[0], mbest.A[1], mbest.A[2], mbest.A[3], mbest.A[4], mbest.A[5], mbest.Y[0], mbest.Y[1], mbest.Y[2], mbest.Y[3], mbest.A[4], mbest.Y[5]); 
    }
    else
    {
        printf("\nProcesses did not find a cover \n");
        printf("\nProgram ran for %f seconds \n\n",(double)(end - start)/(double)CLOCKS_PER_SEC);
    }
    
    return 0;
}


void master(int diam, int &numgens, Polynomial &mbest)
{
   Polynomial M;
   vector<int> list;
   int i, j, I1=2, J1=2, K1=2, L1=2, N=2;
   int I2=0, I3=0, I4=0, I5=0, I6=0;
   int J2=0, J3=0, J4=0, J5=0;
   int K2=0, K3=0, K4=0;
   int L2=0, L3=0;
   
   // As processes finish, assign them new generators.
   while(I < diam*diam*diam*diam*diam*diam/(720*2*2*2*2))
   {
          if(M.value() > mbest.value())
          {
              mbest.A = M.A; mbest.Y = M.Y;
          }
          //results.push_back(M);
          //cout<<"Testing "<<M.A <<" generators, returned location "<<M.Y;
          
          T6 A(I*J*K*L*N, I*J*K*L, J*K*L, K*L, L, 1);
          ++numgens;
          if(N + 1 < diam*diam*diam*diam*diam*diam/(720*L*I*J*K)){ ++N;}
          else{ N=2;
          if(L + 1 < diam*diam*diam*diam*diam*diam/(720*I*J*K*N)){ ++L;}
          else{ L=2;
          if(K + 1 < diam*diam*diam*diam*diam*diam/(720*I*J*L*N)){ ++K;} 
          else{ K=2; 
          if(J + 1 < diam*diam*diam*diam*diam*diam/(720*I*L*K*N)){ ++J;}
          else{ J=2; 
          if(I + 1 < diam*diam*diam*diam*diam*diam/(720*L*J*K*N)){ ++I;}
          else break;}}}}

          slave(diam, A, mbest);

   }

    return;
}


void slave(int diam, T6 &A, Polynomial &mbest)
{
    check_cover(diam, A, mbest);
}

void check_cover(int diam, T6 &A, Polynomial &mbest)
{
   int i,j,k;
   T6 x;
   Polynomial M;
   vector<bool> cover;
   bool covered = false;

   // Loop over m and xcoeffs
   for(int i=1; i < (float)(diam*diam*diam*diam*diam*diam / (720*A[0])); ++i)
   {
      for(int j=1; j < (float)(A[0] / A[1]); ++j)
      {
         for(int k=1; k < (float)(A[1] / A[2]); ++k)
         {
         	for(int l=1; l < (float)(A[2] / A[3]); ++l)
         	{	
				for(int m=1; m < (float)(A[3] / A[4]); ++m)
         		{
         			for(int n=1; n < A[4]; ++n)
         			{
            		   T6 Q(i, j, k, l, m, n);
                     //cout<<"Q "<<Q;
                       Polynomial M(A, Q);
                     //cout<<"M "<<M;
                       cover.clear();
                       cover.resize(diam*diam*diam*diam*diam*diam);
                       //clear_cover(cover);
                   //  print_cover(cover, diam);
                     if((M.value() > mbest.value()) && M.wellFormed()) //ignore M that are too small, or badly formed
                     {
                     for(int i=0; i <= diam-6; i++)
                     {
                      for(int j=0; j <= diam - (6+i); ++j)
                      {
                         for(int k=0;k <= diam - (6+i+j); ++k)
                         {
                            for(int l=0; l <= diam - (6 +i +j +k); ++l)
                            {
                                for(int m=0; m <= diam - (6 +i +j +k +l); ++m)
                                {
                                    for(int n=0; n <= diam - (6 +i +j +k +l+ m); ++n)
                                    {
                                         T6 x(n, m, l, k, j, i);
                                         //cout << "x "<<x<<endl;
                                         Polynomial X(A, x);
                                         //cout<<"X "<<X;
                                         Polynomial X_prime(X-M);
                                         //cout<<"X_prime "<<X_prime;
                                         if(X_prime.wellFormed())
                                         { 
                                            //cover.push_back(1);
                                            cover[X_prime.sum()] = 1;
                                         }//print_cover(cover, diam);
                                    }
                                }
                            }
                         }
                      }
                     }
                         // check covering
                         covered = true;
                         for(int i=0; i < M.sum(); ++i) //only check the first m of them
                         {
                            if(cover[i]==0) //we are not covered
                            {
                              covered = false;
                              break;
                            }
                         }
                         if(covered)//(accumulate(cover.begin(),cover.end(),0) == M.sum())
                         {
                            mbest.A = M.A; mbest.Y = M.Y;
                         }
                      }
                   }
                }
             }
          }
       }
   }
  return;

}

void print_cover(vector<bool> cover, int diam)
{cout<<"cover ";
    for(int i=0; i<diam*diam*diam; ++i)
    {
        cout<<cover[i];
    }
    cout<<endl;
    return;
}


