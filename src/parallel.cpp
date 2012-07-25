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
    int v;
    int w;
    int x;
    int y;
    int z;
  };

struct Poly{
    tuple A;
    tuple Y;
    int s;
};

//MPI Datatypes
MPI_Datatype MPI_Tuple;
MPI_Datatype MPI_Polynomial;

void master(int, int, Polynomial&, int&);
void slave(int, int);
void construct_MPI_DataTypes();
void check_cover(T5, int, int, Polynomial&);
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
  
//printf("I am process %d in main\n", rank);
    if(rank == 0)
    {
       master(diam, numprocs, mbest, numgens);
    }
   // MPI_Barrier(MPI_COMM_WORLD);
    if(rank != 0){ 
        slave(diam, numprocs);
    }

    
    MPI_Barrier(MPI_COMM_WORLD);

//printf("I am process %d leaving main \n",rank);
 
    // Free memory
    MPI_Type_free(&MPI_Tuple);
    MPI_Type_free(&MPI_Polynomial);

    MPI_Finalize();
   
    end = clock();
    if (rank == 0) {printf("%d generators checked.\n", numgens);}
    if(rank == 0 && mbest.A[0] != 0){
        printf("\nDiameter: %d \nGenerators: (%d, %d, %d, %d, %d), Location: (%d, %d, %d, %d, %d)\n", diam, mbest.A[0], mbest.A[1], mbest.A[2], mbest.A[3], mbest.A[4], mbest.Y[0], mbest.Y[1], mbest.Y[2], mbest.Y[3], mbest.A[4]); 
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

   int i, err=0, I=2, J=2, K=2, L=2;
   ifstream gens;
   bool has_room = true;
   clock_t start, end;

   start = clock();

// Assign generators to each process.
   for(i=0; i<numprocs-1; ++i)
   {
      T5 A_init(I*J*K*L, J*K*L, K*L, L, 1);
      cout<<"A_init "<<A_init<<endl;
      ++numgens;
      sendbuf[i].A.z = A_init[0];
      sendbuf[i].A.y = A_init[1];
      sendbuf[i].A.x = A_init[2];
      sendbuf[i].A.w = A_init[3];
      sendbuf[i].A.v = A_init[4];
      if(L + 1 < diam*diam*diam*diam*diam/(120*I*J*K)){ ++L;}
      else{ L=2;
      if(K + 1 < diam*diam*diam*diam*diam/(120*I*J*L)){ ++K;} 
      else{ K=2; 
      if(J + 1 < diam*diam*diam*diam*diam/(120*I*L*K)){ ++J;}
      else{ J=2; 
      if(I + 1 < diam*diam*diam*diam*diam/(120*L*J*K)){ ++I;}
      else break;}}}
      

//printf("Master Sending (%d %d %d %d %d) to %d \n",sendbuf[i].A.z, sendbuf[i].A.y, sendbuf[i].A.x, sendbuf[i].A.w, sendbuf[i].A.v, i+1);
      err = MPI_Send(&sendbuf[i],1, MPI_Polynomial,i+1,WORKTAG,MPI_COMM_WORLD);
      if(err){
        fprintf(stderr,"Failed to send.\n");
        MPI_Abort(MPI_COMM_WORLD,1);
      }  
   }

    while(I < diam*diam*diam*diam*diam/(120*2*2*2)){
   // As processes finish, assign them new generators.
      for(i=0; i<numprocs-1; ++i)
      { 
//printf("Waiting for return from slave %d \n", i+1);
          
          err = MPI_Recv(&recvbuf[i],1,MPI_Polynomial,i+1,WORKTAG,MPI_COMM_WORLD,&status);
          if(err){
            fprintf(stderr,"Failed to recieve.\n");
            MPI_Abort(MPI_COMM_WORLD,1);
          }
         
          // Put into results
          T5 a(recvbuf[i].A.z,recvbuf[i].A.y,recvbuf[i].A.x,recvbuf[i].A.w,recvbuf[i].A.v);
          T5 y(recvbuf[i].Y.z,recvbuf[i].Y.y,recvbuf[i].Y.x,recvbuf[i].Y.w,recvbuf[i].Y.v);
          Polynomial M(a,y);

//printf("Process %d in slave returned (%d %d %d %d %d) as generators ",status.MPI_SOURCE, recvbuf[i].A.z, recvbuf[i].A.y, recvbuf[i].A.x, recvbuf[i].A.w, recvbuf[i].A.v);
//printf("and (%d %d %d %d %d) as M-coeffs \n", recvbuf[i].Y.z, recvbuf[i].Y.y, recvbuf[i].Y.x, recvbuf[i].Y.w, recvbuf[i].Y.v);

          if(M.value() > mbest.value())
          {
              mbest.A = M.A; mbest.Y = M.Y;

printf("New M found by slave %d : Generators : (%d %d %d %d %d), Coeffs : (%d %d %d %d %d)", status.MPI_SOURCE, recvbuf[i].A.z, recvbuf[i].A.y, recvbuf[i].A.x, recvbuf[i].A.w, recvbuf[i].A.v, recvbuf[i].Y.z, recvbuf[i].Y.y, recvbuf[i].Y.x, recvbuf[i].Y.w, recvbuf[i].Y.v);

              end = clock();
 printf("\nProgram has checked %d generators in %f seconds \n\n", numgens, (double)(end - start)/(double)CLOCKS_PER_SEC);
          }
          //results.push_back(M);
          //cout<<"Testing "<<M.A <<" generators, returned location "<<M.Y;

          T5 A(I*J*K*L, J*K*L, K*L, L, 1);
          ++numgens;
          sendbuf[i].A.z = A[0];
          sendbuf[i].A.y = A[1];
          sendbuf[i].A.x = A[2];
          sendbuf[i].A.w = A[3];
          sendbuf[i].A.v = A[4];
          if(L + 1 < diam*diam*diam*diam*diam/(120*I*J*K)){ ++L;}
          else{ L=2;
          if(K + 1 < diam*diam*diam*diam*diam/(120*I*J*L)){ ++K;} 
          else{ L=2; 
          if(J + 1 < diam*diam*diam*diam*diam/(120*I*L*K)){ ++J;}
          else{ K=2; 
          if(I + 1 < diam*diam*diam*diam*diam/(120*L*J*K)){ ++I;}
          else break;}}}

         err = MPI_Send(&sendbuf[i],1,MPI_Polynomial,status.MPI_SOURCE,WORKTAG,MPI_COMM_WORLD);
         if(err){
            fprintf(stderr,"Failed to send.\n");
            MPI_Abort(MPI_COMM_WORLD,1);
         }
      }}

   // No more generators, wait for processes to finish.
   for(i=0; i<numprocs-1; ++i)
   { 
//printf("Waiting in master for return from %d \n", i+1);
      err = MPI_Recv(&recvbuf[i],1,MPI_Polynomial,i+1,WORKTAG,MPI_COMM_WORLD,&status);
      if(err){
         fprintf(stderr,"Failed to recieve.\n");
         MPI_Abort(MPI_COMM_WORLD,1);
      }
//printf("GOTIT! Process %d returned (%d %d %d %d %d) to master \n",status.MPI_SOURCE, recvbuf[i].A.z, recvbuf[i].A.y, recvbuf[i].A.x, recvbuf[i].A.w, recvbuf[i].A.v);
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
//printf("I am slave %d in slave\n",rank);

    err = MPI_Recv(&recvbuf[rank-1],1,MPI_Polynomial,0,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
    if(err){
       fprintf(stderr,"Failed to receive.\n");
       MPI_Abort(MPI_COMM_WORLD,1);
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(status.MPI_TAG == DIETAG){return;}

//printf("Process %d in slave recieved (%d %d %d %d %d) \n",rank, recvbuf[rank-1].A.z, recvbuf[rank-1].A.y, recvbuf[rank-1].A.x, recvbuf[rank-1].A.w, recvbuf[rank-1].A.v);
    
    // Check cover
    T5 A(recvbuf[rank-1].A.z, recvbuf[rank-1].A.y, recvbuf[rank-1].A.x, recvbuf[rank-1].A.w, recvbuf[rank-1].A.v);  
    Polynomial mbest;
    check_cover(A, rank, diam, mbest);
   
    sendbuf[rank-1].Y.v = mbest.Y[4];
    sendbuf[rank-1].Y.w = mbest.Y[3];
    sendbuf[rank-1].Y.x = mbest.Y[2];
    sendbuf[rank-1].Y.y = mbest.Y[1];
    sendbuf[rank-1].Y.z = mbest.Y[0];
    sendbuf[rank-1].A.v = mbest.A[4];
    sendbuf[rank-1].A.w = mbest.A[3];
    sendbuf[rank-1].A.x = mbest.A[2];
    sendbuf[rank-1].A.y = mbest.A[1];
    sendbuf[rank-1].A.z = mbest.A[0];

printf("Process %d returning (%d %d %d %d %d) generators ",rank, sendbuf[rank-1].A.z, sendbuf[rank-1].A.y, sendbuf[rank-1].A.x, sendbuf[rank-1].A.w, sendbuf[rank-1].A.v);
printf("and (%d %d %d %d %d) coeffs from slave \n", sendbuf[rank-1].Y.z, sendbuf[rank-1].Y.y, sendbuf[rank-1].Y.x, sendbuf[rank-1].Y.w, sendbuf[rank-1].Y.v);
    
    err = MPI_Send(&sendbuf[rank-1],1,MPI_Polynomial,0,WORKTAG,MPI_COMM_WORLD);
    if(err){
      fprintf(stderr,"Failed to send.\n");
      MPI_Abort(MPI_COMM_WORLD,1);
    }
  }
}

void check_cover(T5 A, int rank, int diam, Polynomial &mbest)
{
   int i,j,k;
   T5 x;
   ifstream xcoeffs;
   Polynomial M;
   vector<bool> cover;
   bool covered = false;
   MCoTable QTable;
   stringstream s;
   string fxcoeffs = "./permutationtables/XTable.txt";

   clock_t start, end;

   start = clock();

   // Loop over m and xcoeffs
   for(int i=1; i < (float)(diam*diam*diam*diam*diam / (120*A[0])); ++i)
   {
      for(int j=1; j < (float)(A[0] / A[1]); ++j)
      {
         for(int k=1; k < (float)(A[1] / A[2]); ++k)
         {
         	for(int l=1; l < (float)(A[2] / A[3]); ++l)
         	{	
				for(int m=1; m < A[3]; ++m)
         		{
            	   T5 Q(i, j, k, l, m);
                 //cout<<"Q "<<Q;
                   Polynomial M(A, Q);
                 //cout<<"M "<<M;
                   cover.clear();
                   cover.resize(diam*diam*diam);
                   //clear_cover(cover);
               //  print_cover(cover, diam);
                 if((M.value() > mbest.value()) && M.wellFormed()) //ignore M that are too small, or badly formed
                 {
                   for(int i=0; i <= diam-5; i++)
                   {
                      for(int j=0; j <= diam - (5+i); ++j)
                      {
                         for(int k=0;k <= diam - (5+i+j); ++k)
                         {
                            for(int l=0; l <= diam - (5 +i +j +k); ++l)
                            {
                                for(int m=0; m <= diam - (5 +i +j +k +l); ++m)
                                {
                                     T5 x(m, l, k, j, i);
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
   
   end = clock();

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
  MPI_Type_contiguous(3, MPI_INT, &MPI_Tuple);
  MPI_Type_commit(&MPI_Tuple);

  // Construct MPI Polynomial
  struct Poly aPoly;
  MPI_Datatype ptype[3] = {MPI_Tuple, MPI_Tuple, MPI_INT};
  MPI_Aint pdisp[3];
  int pbase;
  int pblocklen[3] = {12, 12, 4};

  // MPI description of tuple
  err = MPI_Get_address(&aPoly.Y, pdisp); 
  err = MPI_Get_address(&aPoly.A, pdisp+1);
  err = MPI_Get_address(&aPoly.s, pdisp+2);
  if(err){
      fprintf(stderr,"Bad addressing.\n");
      MPI_Abort(MPI_COMM_WORLD,1);
  }
  pbase = pdisp[0]; 
  for (i=0; i <3; i++) pdisp[i] -= pbase; 
  err = MPI_Type_create_struct(3, pblocklen, pdisp, ptype, &MPI_Polynomial);
  if(err){
      fprintf(stderr,"Can't create struct.\n");
      MPI_Abort(MPI_COMM_WORLD,1);
   }
  MPI_Type_commit(&MPI_Polynomial);

  return;
}


