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
void slave(int, T&, Polynomial&);
void check_cover(int, T&, Polynomial&);
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
        cout<<mbest;
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
   int I2=0;
   int J2=0, J3=0;
   int K2=0, K3=0, K4=0;
   int L2=0, L3=0, L4=0, L5=0;
   
   // As processes finish, assign them new generators.
   while(I1 < diam*diam*diam*diam*diam*diam/(720*2*2*2*2))
   {
          if(M.value() > mbest.value())
          {
              for(i=0; i<6; i++)
              {
                    mbest.A[i] = M.A[i];
              }
              mbest.Y = M.Y;
              cout<< "Found new M: "<<M;
          }
 
          list.push_back(I1*J1*K1*L1*N);
          list.push_back(I2*J2*K2*L2);
          list.push_back(J3*K3*L3);
          list.push_back(K4*L4);
          list.push_back(L5);
          list.push_back(I1*J1*K1*L1);
          list.push_back(J2*K2*L2);
          list.push_back(K3*L3);
          list.push_back(L4);
          list.push_back(J1*K1*L1);
          list.push_back(K3*L3);
          list.push_back(L4);
          list.push_back(K1*L1);
          list.push_back(L4);
          list.push_back(L1);
          list.push_back(1);

          T A(list);
          list.clear();

          ++numgens;
          // First coeff.
          if(N + 1 < diam*diam*diam*diam*diam*diam/(720*L1*I1*J1*K1)){ ++N;}
          else{ N=2;
          if(L5 < diam){ ++L5;}
          else{
          if(L4 < diam){ ++L4;}
          else{
          if(L3 < diam){ ++L3;}
          else{
          if(L2 < diam){ ++L2;}
          else{ 
          if(L1 + 1 < diam*diam*diam*diam*diam*diam/(720*I1*J1*K1*N)){ ++L1;}
          else{ L1=2; L2=L3=L4=L5=0;
          if(K4 < diam){ ++K4;} 
          else{ 
          if(K3 < diam){ ++K3;} 
          else{
          if(K2 < diam){ ++K2;} 
          else{ 
          if(K1 + 1 < diam*diam*diam*diam*diam*diam/(720*I1*J1*L1*N)){ ++K1;} 
          else{ K1=2; K2=K3=K4=0;
          if(J3 < diam){ ++J3;}
          else{ 
          if(J2 < diam){ ++J2;}
          else{ 
          if(J1 + 1 < diam*diam*diam*diam*diam*diam/(720*I1*L1*K1*N)){ ++J1;}
          else{ J1=2; J2=J3=0;
          if(I2 < diam){ ++I2;}
          else{ 
          if(I1 + 1 < diam*diam*diam*diam*diam*diam/(720*L1*J1*K1*N)){ ++I1;}
          else break;}}}}}}}}}}}}}}
  
          slave(diam, A, mbest);

   }

    return;
}


void slave(int diam, T &A, Polynomial &mbest)
{
    check_cover(diam, A, mbest);
}

void check_cover(int diam, T &A, Polynomial &mbest)
{
   int i,j,k,l,m,n,p,q,r,s,t,u,v,w;
   Polynomial M;
   vector<bool> cover;
   vector<int> list;
   bool covered = false;
   
   // Loop over m and xcoeffs
   for(i=1; i < (float)(diam*diam*diam*diam*diam*diam / (720*A[0])); ++i)
   {
      for(j=1; j < (float)(A[0] / A[5]); ++j)
      {
         for(k=1; k < (float)(A[5] / A[9]); ++k)
         {
         	for(l=1; l < (float)(A[9] / A[12]); ++l)
         	{	
				for(m=1; m < (float)(A[12] / A[14]); ++m)
         		{
         			for(n=1; n < 12; ++n)
         			{
                       list.push_back(i);
                       list.push_back(j);
                       list.push_back(k);
                       list.push_back(l);
                       list.push_back(m);
                       list.push_back(n);
            		   T Q(list);
                       list.clear();
                     //cout<<"Q "<<Q<<endl;
                       Polynomial M(&A, Q);
                     //cout<<"M "<<M;
                       cover.clear();
                       cover.resize(diam*diam*diam*diam*diam*diam);
                     if((M.sum() > mbest.sum()) && (M.sum() > diam*diam*diam*diam*diam*diam/(6*5*4*3*2))) //ignore M that are too small, or badly formed
                     {cout<<"Found an M\n";
                     for(p=0; p <= diam-6; p++)
                     {
                      for(q=0;  q <= diam - (6+q); ++q)
                      {
                         for(r=0; r <= diam - (6+r+q); ++r)
                         {
                            for(s=0; s <= diam - (6 +s +r +q); ++s)
                            {
                                for(t=0; t <= diam - (6 +t +s +r +q); ++t)
                                {
                                    for(int u=0; u <= diam - (6 +u +t +s +r+ q); ++u)
                                    {
                                         list.push_back(p);
                                         list.push_back(q);
                                         list.push_back(r);
                                         list.push_back(s);
                                         list.push_back(t);
                                         list.push_back(u);
                                         T x(list);
                                         list.clear();
                                         //cout << "x "<<x<<endl;
                                         Polynomial X(&A, x);
                                         cout<<"X "<<X;
                                         Polynomial X_prime(X-M);
                                         cout<<"X_prime "<<X_prime;
                                         if(X_prime.wellFormed())
                                         { 
                                            //cover.push_back(1);
                                            cover[X_prime.sum()] = 1;
                                         print_cover(cover, diam);
                                         }
                                    }
                                }
                            }
                         }
                      }
                     }
                         // check covering
                         covered = true;
                         for(v=0; v < M.sum(); ++v) //only check the first m of them
                         {
                            if(cover[v]==0) //we are not covered
                            {
                              covered = false;
                              break;
                            }
                         }
                         if(covered)//(accumulate(cover.begin(),cover.end(),0) == M.sum())
                         {
                            for(w=0; w<M.Y.size(); ++w)
                            {
                                mbest.A[w] = M.A[w];
                            }
                            mbest.Y = M.Y;
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


