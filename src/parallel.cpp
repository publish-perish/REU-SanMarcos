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
    int x;
    int y;
    int z2;
    int z1;
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
void check_cover(T4, int, int, Polynomial&);
void print_cover(vector<bool>, int);

int main (int argc, char *argv[]) {
  if(argc<2)
  {
     printf("Usage: ./executables/average_case diameter (lowerbound) \n");
     return 0;
  }

  int rank, numprocs, i, err=0, numgens=0;
  const int diam = atoi(argv[1]);
  const int d_4 = diam*diam*diam*diam;
  const double lowerbound = (argv[2]) ? atoi(argv[2]) : (d_4/16.0);
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
    if(rank == 0){
        printf("%d Generators checked. \n", numgens);}
    if(mbest.A[0] != 0 && rank == 0){
        printf("\nDiameter: %d \nGenerators: (%d, %d, %d, %d), Location: (%d, %d, %d)\n", diam, mbest.A[0], mbest.A[1], mbest.A[2], mbest.A[3], mbest.Y[0], mbest.Y[1], mbest.Y[2]);
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

   int i, err=0, I=2, J=2, K=0;
   clock_t start, end;
   // Assign generators to each process.
   for(i=0; i<numprocs-1; ++i)
   {
      ++numgens;
      T4 A_init(I*J, K, J, 1);
 
      sendbuf[i].A.z1 = A_init[0];
      sendbuf[i].A.z2 = A_init[1];
      sendbuf[i].A.y = A_init[2];
      sendbuf[i].A.x = A_init[3];

      if((K + 1 < J && K + 1 < I )){ ++K;}
      else{ K=0;
      if(J + 1 < diam*diam*diam/(6*I) && J < diam){ ++J;}
      else{ J=2;
      if(I < diam*diam*diam/(6*J)&& I < diam){ ++I;}
      else break; }}

//printf("Master Sending (%d %d %d %d) to %d \n",sendbuf[i].A.z1, sendbuf[i].A.z2, sendbuf[i].A.y, sendbuf[i].A.x, i+1);
      err = MPI_Send(&sendbuf[i],1, MPI_Polynomial,i+1,WORKTAG,MPI_COMM_WORLD);
      if(err){
        fprintf(stderr,"Failed to send.\n");
        MPI_Abort(MPI_COMM_WORLD,1);
      }
   }
   
   // As processes finish, assign them new generators.
      while(I < diam*diam*diam/(2*6) && I < diam){//cout<<"Stuck in while loop\n";
      for(i=0; i<numprocs-1; ++i)
      {
//printf("Waiting for return from slave %d \n", i+1);
          err = MPI_Recv(&recvbuf[i],1,MPI_Polynomial,i+1,WORKTAG,MPI_COMM_WORLD,&status);
          if(err){
            fprintf(stderr,"Failed to recieve.\n");
            MPI_Abort(MPI_COMM_WORLD,1);
          }
         
          // Put into results
          T4 a(recvbuf[i].A.z1,recvbuf[i].A.z2,recvbuf[i].A.y,recvbuf[i].A.x);
          T y(recvbuf[i].Y.z1,recvbuf[i].Y.y,recvbuf[i].Y.x);
          Polynomial M(a,y);
//printf("Process %d in slave returned (%d %d %d %d) as generators ",status.MPI_SOURCE, recvbuf[i].A.z1, recvbuf[i].A.z2, recvbuf[i].A.y, recvbuf[i].A.x);
//printf("and (%d %d %d) as M-coeffs \n", recvbuf[i].Y.z1, recvbuf[i].Y.y, recvbuf[i].Y.x);
          if(M.value() > mbest.value())
          {
              mbest.A = M.A; mbest.Y = M.Y;
              printf("New M found by slave %d : Generators : (%d %d %d %d), Coeffs : (%d %d %d %d)", status.MPI_SOURCE, recvbuf[i].A.z1, recvbuf[i].A.z2, recvbuf[i].A.y, recvbuf[i].A.x, recvbuf[i].Y.z1, recvbuf[i].Y.z2, recvbuf[i].Y.y, recvbuf[i].Y.x);

              end = clock();
              printf("\nProgram has checked %d generators in %f seconds \n\n", numgens, (double)(end - start)/(double)CLOCKS_PER_SEC);
          
          }
          //results.push_back(M);
          //cout<<"Testing "<<M.A <<" generators, returned location "<<M.Y;

          T4 A(I*J, K, J, 1);
          ++numgens;
          sendbuf[i].A.x = A[3];
          sendbuf[i].A.y = A[2];
          sendbuf[i].A.z2 = A[1];
          sendbuf[i].A.z1 = A[0];
          if((K + 1 < J && K + 1 < I ) ){ ++K;}
          else{ K=0;
          if(J + 1 < diam*diam*diam/(6*I) && J < diam){ ++J;}
          else{ J=2;
          if(I < diam*diam*diam/(6*J) && I < diam){ ++I;}
          else break; }}


//printf("Master Sending (%d %d %d %d) to %d \n",sendbuf[i].A.z1, sendbuf[i].A.z2, sendbuf[i].A.y, sendbuf[i].A.x, i+1);
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
      err = MPI_Recv(&recvbuf[i],1,MPI_Polynomial,MPI_ANY_SOURCE,WORKTAG,MPI_COMM_WORLD,&status);
      if(err){
         fprintf(stderr,"Failed to recieve.\n");
         MPI_Abort(MPI_COMM_WORLD,1);
      }
//printf("GOTIT! Process %d returned (%d %d %d) to master \n",status.MPI_SOURCE, recvbuf[i].A.z1, recvbuf[i].A.y, recvbuf[i].A.x);
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

   T A_best, Y_best;
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
//printf("Process %d in slave recieved (%d %d %d %d) \n",rank, recvbuf[rank-1].A.z1, recvbuf[rank-1].A.z2, recvbuf[rank-1].A.y, recvbuf[rank-1].A.x);
    
    // Check cover
    T4 A(recvbuf[rank-1].A.z1, recvbuf[rank-1].A.z2, recvbuf[rank-1].A.y, recvbuf[rank-1].A.x);
    Polynomial mbest;
    check_cover(A, rank, diam, mbest);
   
    sendbuf[rank-1].Y.x = mbest.Y[2];
    sendbuf[rank-1].Y.y = mbest.Y[1];
    sendbuf[rank-1].Y.z2 = 0;
    sendbuf[rank-1].Y.z1 = mbest.Y[0];
    sendbuf[rank-1].A.x = mbest.A[3];
    sendbuf[rank-1].A.y = mbest.A[2];
    sendbuf[rank-1].A.z2 = mbest.A[1];
    sendbuf[rank-1].A.z1 = mbest.A[0];
//printf("Process %d returning X = (%d %d %d) from slave",rank, sendbuf[rank-1].Y.z1, sendbuf[rank-1].Y.y, sendbuf[rank-1].Y.x);
//printf(" and A = (%d %d %d %d) from slave \n", sendbuf[rank-1].A.z1, sendbuf[rank-1].A.z2, sendbuf[rank-1].A.y, sendbuf[rank-1].A.x);
    
    err = MPI_Send(&sendbuf[rank-1],1,MPI_Polynomial,0,WORKTAG,MPI_COMM_WORLD);
    if(err){
      fprintf(stderr,"Failed to send.\n");
      MPI_Abort(MPI_COMM_WORLD,1);
    }
  }
}

void check_cover(T4 A, int rank, int diam, Polynomial &mbest)
{
   int i,j,k;
   T x;
   ifstream xcoeffs;
   Polynomial M;
   vector<bool> cover;
   bool covered = false;
   MCoTable QTable;
   double c1 = (float)A[0]/A[2];
   stringstream s;
   string fxcoeffs = "./permutationtables/XTable.txt";
   s << rank;
   fxcoeffs = (fxcoeffs.insert(fxcoeffs.length()-4, s.str())).c_str();
   mbest.A = A;

   // Loop over m and xcoeffs
   for(i=1; i < (float)(diam*diam*diam / (A[0] * 6)) && i < diam; ++i)
   {
    for(j=1; j <= c1 && j < diam; ++j)
    {
     for(k=1; k < A[2] && k < diam; ++k) 
     {
         T Q(i, j, k);
         //cout<<"Q "<<Q;
         Polynomial M(A, Q);
         //cout<<"M "<<M;
           cover.clear();
           cover.resize(diam*diam*diam*diam);
         //print_cover(cover, diam);
         if(M.value() > mbest.value()) //&& M.wellFormed()) //ignore M that are too small, or badly formed
         {
            for(int i=diam; i >= 0; --i)
            {
for(int j=diam-i; j >= 0; --j)
{
for(int k=diam-j-i;k >= 0; --k) //filter them in holding tank, then add to file
{
if(i+j+k <= diam - 3)
{
           T x(i,j,k);
                         //cout << "x "<<x<<endl;
                         Polynomial X(A, x);
                         //cout<<"X "<<X;
                         Polynomial X_prime(X-M);
                         //cout<<"X_prime "<<X_prime;
                         if(true)   //X_prime.wellFormed())
                         {
                            //cover.push_back(1);
                            cover[X_prime.sum()] = 1;
                         }}//print_cover(cover, diam);
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
  return;

}

void print_cover(vector<bool> cover, int diam)
{
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
  MPI_Type_contiguous(4, MPI_INT, &MPI_Tuple);
  MPI_Type_commit(&MPI_Tuple);

  // Construct MPI Polynomial
  struct Poly aPoly;
  MPI_Type_contiguous(2, MPI_Tuple, &MPI_Polynomial);
  MPI_Type_commit(&MPI_Polynomial);

  return;
}
