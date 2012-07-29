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


struct tuple{
    int u;
    int v;
    int w;
    int x;
    int y;
    int z;
  };

struct Poly{
    tuple A;
    tuple Y;
};

//MPI Datatypes
MPI_Datatype MPI_Tuple;
MPI_Datatype MPI_Polynomial;

void master(int, int, Polynomial&, int&);
void slave(int, int);
void construct_MPI_DataTypes();
void check_cover(T6, int, int, Polynomial&);
void clear_cover(int[], int);
void print_cover(vector<bool>, int);

int main (int argc, char *argv[]) {
  if(argc<2)
  {
     printf("Usage: ./executables/average_case diameter (lowerbound) \n");
     return 0;
  }

  int rank, numprocs, i, err=0, numgens=0;
  const int diam = atoi(argv[1]);
  const int d_cubed = diam*diam*diam; 
  const double lowerbound = (argv[2]) ? atoi(argv[2]) : (d_cubed/16.0);
  clock_t start, end;
  Polynomial mbest;

  start = clock();

  // Init MPI & get numprocs and rank 
  MPI_Init(&argc,&argv);
  err = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  err = MPI_Comm_size(MPI_COMM_WORLD, &numprocs); 
  if(err){
      fprintf(stderr,"Catastrophic MPI problem.\n");
      MPI_Abort(MPI_COMM_WORLD,1);
  }

  construct_MPI_DataTypes();
  
printf("I am process %d in main\n", rank);
    if(rank == 0)
    {
       master(diam, numprocs, mbest, numgens);
    }
   // MPI_Barrier(MPI_COMM_WORLD);
    if(rank != 0){ 
        slave(diam, numprocs);
    }

    
    MPI_Barrier(MPI_COMM_WORLD);

printf("I am process %d leaving main \n",rank);
 
    // Free memory
    MPI_Type_free(&MPI_Tuple);
    MPI_Type_free(&MPI_Polynomial);

    MPI_Finalize();
   
    end = clock();
    if(mbest != 0){
        printf("\nDiameter: %d \nGenerators: (%d, %d, %d, %d, %d, %d), Location: (%d, %d, %d, %d, %d)\n", diam, mbest.A[0], mbest.A[1], mbest.A[2], mbest.A[3], mbest.A[4], mbest.A[5], mbest.Y[0], mbest.Y[1], mbest.Y[2], mbest.Y[3], mbest.A[4], mbest.Y[5]); 
    }else if(rank == 0){printf("\nProcesses did not find a cover \n");
        printf("\nProgram ran for %f seconds \n\n",(double)(end - start)/(double)CLOCKS_PER_SEC);}
    
    return 0;
}


void master(int diam, int numprocs, Polynomial &mbest, int &numgens)
{
   // Buffers
   Poly sendbuf[numprocs], recvbuf[numprocs];
   MPI_Request request;
   MPI_Status status;

   T6 A;
   int i, j, err=0, I=2, J=2, K=2, L=2, N=2;
   
   // Assign generators to each process.
   for(i=0; i<numprocs-1; ++i)
   {
      T6 A_init(I*J*K*L*N, I*J*K*L, J*K*L, K*L, L, 1);
      ++numgens;
      sendbuf[i].A.z = A_init[0];
      sendbuf[i].A.y = A_init[1];
      sendbuf[i].A.x = A_init[2];
      sendbuf[i].A.w = A_init[3];
      sendbuf[i].A.v = A_init[4];
      sendbuf[i].A.u = A_init[5];
      if(N + 1 < diam*diam*diam*diam*diam*diam/(720*L*I*J*K)){ ++N;}
      else{ N=2;
      if(L + 1 < diam*diam*diam*diam*diam*diam/(120*I*J*K*N)){ ++L;}
      else{ L=2;
      if(K + 1 < diam*diam*diam*diam*diam*diam/(120*I*J*L*N)){ ++K;} 
      else{ K=2; 
      if(J + 1 < diam*diam*diam*diam*diam*diam/(120*I*L*K*N)){ ++J;}
      else{ J=2; 
      if(I + 1 < diam*diam*diam*diam*diam*diam/(120*L*J*K*N)){ ++I;}
      else break;}}}}

printf("Master Sending (%d %d %d %d %d %d) to %d \n",sendbuf[i].A.z, sendbuf[i].A.y, sendbuf[i].A.x, sendbuf[i].A.w, sendbuf[i].A.v, sendbuf[i].A.u, i+1);
      err = MPI_Send(&sendbuf[i],1, MPI_Polynomial,i+1,WORKTAG,MPI_COMM_WORLD);
      if(err){
        fprintf(stderr,"Failed to send.\n");
        MPI_Abort(MPI_COMM_WORLD,1);
      }
  }
   
   // As processes finish, assign them new generators.
   while(I < diam*diam*diam*diam*diam*diam/(720*2*2*2*2))
   {
      for(i=0; i<numprocs-1; ++i)
      { 
printf("Waiting for return from slave %d \n", i+1);
          err = MPI_Recv(&recvbuf[i],1,MPI_Polynomial,i+1,WORKTAG,MPI_COMM_WORLD,&status);
          if(err){
            fprintf(stderr,"Failed to recieve.\n");
            MPI_Abort(MPI_COMM_WORLD,1);
          }
         
          // Put into results
          T6 a(recvbuf[i].A.z,recvbuf[i].A.y,recvbuf[i].A.x,recvbuf[i].A.w,recvbuf[i].A.v, recvbuf[i].A.u);
          T6 y(recvbuf[i].Y.z,recvbuf[i].Y.y,recvbuf[i].Y.x,recvbuf[i].Y.w,recvbuf[i].Y.v, recvbuf[i].Y.u);
          Polynomial M(a,y);
printf("Process %d in slave returned (%d %d %d %d %d %d) as generators ",status.MPI_SOURCE, recvbuf[i].A.z, recvbuf[i].A.y, recvbuf[i].A.x, recvbuf[i].A.w, recvbuf[i].A.v, recvbuf[i].A.u);
printf("and (%d %d %d %d %d) as M-coeffs \n", recvbuf[i].Y.z, recvbuf[i].Y.y, recvbuf[i].Y.x, recvbuf[i].Y.w, recvbuf[i].Y.v);
          if(M.value() > mbest.value())
          {
              mbest.A = M.A; mbest.Y = M.Y;
          }
          //results.push_back(M);
          //cout<<"Testing "<<M.A <<" generators, returned location "<<M.Y;
          
          T6 A(I*J*K*L*N, I*J*K*L, J*K*L, K*L, L, 1);
          ++numgens;
          sendbuf[i].A.z = A[0];
          sendbuf[i].A.y = A[1];
          sendbuf[i].A.x = A[2];
          sendbuf[i].A.w = A[3];
          sendbuf[i].A.v = A[4];
          sendbuf[i].A.u = A[5];
          if(N + 1 < diam*diam*diam*diam*diam*diam/(720*L*I*J*K)){ ++N;}
          else{ N=2;
          if(L + 1 < diam*diam*diam*diam*diam*diam/(120*I*J*K*N)){ ++L;}
          else{ L=2;
          if(K + 1 < diam*diam*diam*diam*diam*diam/(120*I*J*L*N)){ ++K;} 
          else{ K=2; 
          if(J + 1 < diam*diam*diam*diam*diam*diam/(120*I*L*K*N)){ ++J;}
          else{ J=2; 
          if(I + 1 < diam*diam*diam*diam*diam*diam/(120*L*J*K*N)){ ++I;}
          else break;}}}}

printf("Master Sending (%d %d %d %d %d %d) to %d \n",sendbuf[i].A.z, sendbuf[i].A.y, sendbuf[i].A.x, sendbuf[i].A.w, sendbuf[i].A.v, sendbuf[i].A.u, status.MPI_SOURCE); 
         err = MPI_Send(&sendbuf[i],1,MPI_Polynomial,status.MPI_SOURCE,WORKTAG,MPI_COMM_WORLD);
         if(err){
            fprintf(stderr,"Failed to send.\n");
            MPI_Abort(MPI_COMM_WORLD,1);
         }
      }
   }

   // No more generators, wait for processes to finish.
   for(i=0; i<numprocs-1; ++i)
   { 
printf("Waiting in master for return from %d \n", i+1);
      err = MPI_Recv(&recvbuf[i],1,MPI_Polynomial,i+1,WORKTAG,MPI_COMM_WORLD,&status);
      if(err){
         fprintf(stderr,"Failed to recieve.\n");
         MPI_Abort(MPI_COMM_WORLD,1);
      }
printf("GOTIT! Process %d returned (%d %d %d %d %d %d) to master \n",status.MPI_SOURCE, recvbuf[i].A.z, recvbuf[i].A.y, recvbuf[i].A.x, recvbuf[i].A.w, recvbuf[i].A.v, recvbuf[i].A.u);
   }

   // Exit all slaves.
   for(i=0; i<numprocs-1; ++i)
   {    
      err = MPI_Send(0,0,MPI_INT,i+1,DIETAG,MPI_COMM_WORLD);
      if(err){
        fprintf(stderr,"Catastrophic MPI problem.\n");
        MPI_Abort(MPI_COMM_WORLD,1);
      }
   }
  
    return;
}


void slave(int diam, int numprocs)
{
   // Buffers
   Poly recvbuf[numprocs], sendbuf[numprocs];
   MPI_Status status;
   MPI_Request request;

   int rank, err=0;

   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   
   while(1)
   {
printf("I am slave %d in slave\n",rank);
    err = MPI_Recv(&recvbuf[rank-1],1,MPI_Polynomial,0,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
    if(err){
       fprintf(stderr,"Failed to receive.\n");
       MPI_Abort(MPI_COMM_WORLD,1);
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(status.MPI_TAG == DIETAG){return;}
printf("Process %d in slave recieved (%d %d %d %d %d %d) \n",rank, recvbuf[rank-1].A.z, recvbuf[rank-1].A.y, recvbuf[rank-1].A.x, recvbuf[rank-1].A.w, recvbuf[rank-1].A.v, recvbuf[rank-1].A.u);
    
    // Check cover
    T6 A(recvbuf[rank-1].A.z, recvbuf[rank-1].A.y, recvbuf[rank-1].A.x, recvbuf[rank-1].A.w, recvbuf[rank-1].A.v, recvbuf[rank-1].A.u);  
    Polynomial mbest;
    check_cover(A, rank, diam, mbest);
   
    sendbuf[rank-1].Y.u = mbest.Y[5]; 
    sendbuf[rank-1].Y.v = mbest.Y[4];
    sendbuf[rank-1].Y.w = mbest.Y[3];
    sendbuf[rank-1].Y.x = mbest.Y[2];
    sendbuf[rank-1].Y.y = mbest.Y[1];
    sendbuf[rank-1].Y.z = mbest.Y[0];
    sendbuf[rank-1].A.u = mbest.A[5];
    sendbuf[rank-1].A.v = mbest.A[4];
    sendbuf[rank-1].A.w = mbest.A[3];
    sendbuf[rank-1].A.x = mbest.A[2];
    sendbuf[rank-1].A.y = mbest.A[1];
    sendbuf[rank-1].A.z = mbest.A[0];

printf("Process %d returning (%d %d %d %d %d %d) from slave \n",rank, sendbuf[rank-1].A.z, sendbuf[rank-1].A.y, sendbuf[rank-1].A.x, sendbuf[rank-1].A.w, sendbuf[rank-1].A.v, sendbuf[rank-1].A.u);
    
    err = MPI_Send(&sendbuf[rank-1],1,MPI_Polynomial,0,WORKTAG,MPI_COMM_WORLD);
    if(err){
      fprintf(stderr,"Failed to send.\n");
      MPI_Abort(MPI_COMM_WORLD,1);
    }
  }
}

void check_cover(T6 A, int rank, int diam, Polynomial &mbest)
{
   int i,j,k;
   T6 x;
   ifstream xcoeffs;
   Polynomial M;
   vector<bool> cover;
   bool covered = false;
   MCoTable QTable;
   stringstream s;
   string fxcoeffs = "./permutationtables/XTable.txt";

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

void clear_cover(int cover[], int diam)
{
    for(int i=0; i<diam*diam*diam; ++i)
    {
        cover[i] = 0;
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
void construct_MPI_DataTypes()
{
  int i, err = 0;

  // Construct MPI tuple
  struct tuple atuple;
  MPI_Type_contiguous(6, MPI_INT, &MPI_Tuple);
  MPI_Type_commit(&MPI_Tuple);

  // Construct MPI Polynomial
  struct Poly aPoly;
  MPI_Type_contiguous(2, MPI_Tuple, &MPI_Polynomial);
  MPI_Type_commit(&MPI_Polynomial);

  return;
}


