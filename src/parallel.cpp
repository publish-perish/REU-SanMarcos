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

#define WORKTAG 1
#define DIETAG 2

typedef std::vector<Polynomial> PolyVec;


struct tuple{
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

void master(int, int, Polynomial&);
void slave(int, int);
void construct_MPI_DataTypes();
void check_cover(T, int, int, Polynomial&);
void clear_cover(int[]);

int main (int argc, char *argv[]) {
  if(argc<2)
  {
     printf("Usage: ./executables/average_case diameter (lowerbound) \n");
     return 0;
  }

  int rank, numprocs, i, err=0;
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
       master(diam, numprocs, mbest);
    }
   // MPI_Barrier(MPI_COMM_WORLD);
    if(rank != 0){ 
        slave(diam, numprocs);
    }

//printf("I am process %d leaving main \n",rank);
    
    MPI_Barrier(MPI_COMM_WORLD);

    // Free memory
    MPI_Type_free(&MPI_Tuple);
    MPI_Type_free(&MPI_Polynomial);

    MPI_Finalize();
   
    end = clock();
    if(mbest != 0){
        printf("\nDiameter: %d \nGenerators: (%d, %d, %d), Location: (%d, %d, %d)\n", diam, mbest.A[0], mbest.A[1], mbest.A[2], mbest.Y[0], mbest.Y[1], mbest.Y[2]); 
    }else if(rank == 0){printf("\nProcesses did not find a cover \n");
        printf("\nProgram ran for %f seconds \n\n",(double)(end - start)/(double)CLOCKS_PER_SEC);}
    
    return 0;
}


void master(int diam, int numprocs, Polynomial &mbest)
{
   // Buffers
   Poly sendbuf[numprocs], recvbuf[numprocs];
   MPI_Request request[numprocs];
   MPI_Status status[numprocs];

   T A, m;
   int i;
   double c1;
   ifstream gens;
   PolyVec results;
   Polynomial M;

   gens.open("./permutationtables/GenTable.txt");if(gens){
   // Assign generators to each process.
   for(i=0; i<numprocs-1; ++i)
   {
      gens >> A;
      
      sendbuf[i].A.z = A[0];
      sendbuf[i].A.y = A[1];
      sendbuf[i].A.x = A[2];
//printf("Master Sending ( %d %d %d ) to %d \n",sendbuf[i].A.z, sendbuf[i].A.y, sendbuf[i].A.x, i+1);
      MPI_Send(&sendbuf[i],1, MPI_Polynomial,i+1,WORKTAG,MPI_COMM_WORLD);
   }
   
   // As processes finish, assign them new generators.
   while(!gens.eof())
   {
      for(i=0; i<numprocs-1; ++i)
      {
//printf("Waiting for return from slave %d \n", i+1);
          MPI_Recv(&recvbuf[i],1,MPI_Polynomial,i+1,WORKTAG,MPI_COMM_WORLD,&status[i]);
          
          // Put into results
          M = Polynomial(T(recvbuf[i].A.z,recvbuf[i].A.y,recvbuf[i].A.x),T(recvbuf[i].Y.z,recvbuf[i].Y.y,recvbuf[i].Y.z));
//printf("Process %d in slave returned (%d %d %d) as generators ",status[i].MPI_SOURCE, recvbuf[i].A.z, recvbuf[i].A.y, recvbuf[i].A.x);
//printf("and (%d %d %d) as M-coeffs \n",status[i].MPI_SOURCE, recvbuf[i].Y.z, recvbuf[i].Y.y, recvbuf[i].Y.x);
//cout<<"Master recieved M "<<M;
          if(M.value() > mbest.value()){mbest = M;}
          //results.push_back(M);
          //cout<<"Testing "<<M.A <<" generators, returned location "<<M.Y;

          gens >> A;
                
          sendbuf[i].A.x = A[2];
          sendbuf[i].A.y = A[1];
          sendbuf[i].A.z = A[0];

          MPI_Send(&sendbuf[i],1,MPI_Polynomial,status[i].MPI_SOURCE,WORKTAG,MPI_COMM_WORLD);
      }
   }gens.close();

   // No more generators, wait for processes to finish.
   for(i=0; i<numprocs-1; ++i)
   { 
//printf("Waiting in master for return from %d \n", i+1);
      MPI_Recv(&recvbuf[i],1,MPI_Polynomial,i+1,WORKTAG,MPI_COMM_WORLD,&status[i]);
//printf("GOTIT! Process %d returned (%d %d %d) to master \n",status[i].MPI_SOURCE, recvbuf[i].A.z, recvbuf[i].A.y, recvbuf[i].A.x);
  }

   // Exit all slaves.
   for(i=0; i<numprocs-1; ++i)
   {    
//printf("Exiting slave %d \n",i+1);
      MPI_Send(0,0,MPI_INT,i+1,DIETAG,MPI_COMM_WORLD);
   }
   }else{
      fprintf(stderr,"Could not read GenTable \n");
      MPI_Abort(MPI_COMM_WORLD,2);
   }
  

    return;
}


void slave(int diam, int numprocs)
{
   // Buffers
   Poly recvbuf[numprocs], sendbuf[numprocs];
   MPI_Status status;
   MPI_Request request;

   T A;
   int rank;
   Polynomial mbest;

   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   
   while(1)
   {
//printf("I am slave %d in slave\n",rank);
      MPI_Recv(&recvbuf[rank],1,MPI_Polynomial,0,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
      if(status.MPI_TAG == DIETAG){return;}
      mbest = Polynomial(T(0,0,0), T(0,0,0));
//printf("Process %d in slave recieved (%d %d %d) \n",rank, recvbuf[rank].A.z, recvbuf[rank].A.y, recvbuf[rank].A.x);
    
    // Check cover
    A = T(recvbuf[rank].A.z, recvbuf[rank].A.y, recvbuf[rank].A.x);  
    check_cover(A, rank, diam, mbest);
    
    sendbuf[rank].Y.x = mbest.Y[2];
    sendbuf[rank].Y.y = mbest.Y[1];
    sendbuf[rank].Y.z = mbest.Y[0];
    sendbuf[rank].A.x = mbest.A[2];
    sendbuf[rank].A.y = mbest.A[1];
    sendbuf[rank].A.z = mbest.A[0];
//printf("Process %d returning ( %d %d %d ) from slave \n",rank, sendbuf[rank].A.z, sendbuf[rank].A.y, sendbuf[rank].A.x);
    
    MPI_Send(&sendbuf[rank],1,MPI_Polynomial,0,WORKTAG,MPI_COMM_WORLD);
    }
    return;
}

void check_cover(T A, int rank, int diam, Polynomial &mbest)
{
   T Q, x;
   int i,j,k;
   ifstream xcoeffs;
   Polynomial X, X_prime, M;
   int cover[diam*diam*diam];
   bool covered = false;
   MCoTable QTable;
   double c1 = (float)A[0]/A[1];
   stringstream s;
   string fxcoeffs = "./permutationtables/XTable.txt";
   s << rank;
   fxcoeffs = (fxcoeffs.insert(fxcoeffs.length()-4, s.str())).c_str();
   //clear_cover(cover);

   // Loop over m and xcoeffs
   for(i=1; i < (diam*diam*diam / (A[1]*c1)); ++i)
   {
    for(j=1; j < (c1); ++j)
    {
     for(k=1; k < (A[1]); ++k) //filter them in holding tank, then add to file
     {
         Q = T(i, j, k);
         //cout<<"Q "<<Q;
         M = Polynomial(A, Q);
         //cover = {0};
         if((M.value() > mbest.value()) && M.wellFormed() && (M.sum() < (diam*diam*diam))) //ignore M that are too small, or badly formed
         {
           xcoeffs.open(fxcoeffs.c_str());if(xcoeffs){
            while(xcoeffs >> x)
            {
             //cout << "x "<<x<<endl;
             X = Polynomial(A, x);
             X_prime = X-M;
             if(X_prime.wellFormed())
             { 
                cover[X_prime.sum()] = 1;	
             }}xcoeffs.close();
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
             if(covered){mbest = M;}
             }else{
                fprintf(stderr,"Could not read XCoeffs \n");
                MPI_Abort(MPI_COMM_WORLD,2);
             }
         }
      }
     }
    }
  return;

}

void clear_cover(int cover[])
{
    for(int i=0; i<sizeof(cover); ++i)
    {
        cover[i] = 0;
    }
    return;
}

void construct_MPI_DataTypes()
{
  int i, err = 0;

  // Construct MPI tuple
  MPI_Type_contiguous(3, MPI_INT, &MPI_Tuple);
  MPI_Type_commit(&MPI_Tuple);

  // Construct MPI Polynomial
  struct Poly aPoly;
  MPI_Datatype ptype[2] = {MPI_Tuple, MPI_Tuple};
  MPI_Aint pdisp[2];
  int pbase;
  int pblocklen[3] = {12, 12};

  // MPI description of tuple
  err = MPI_Get_address(&aPoly.Y, pdisp); 
  err = MPI_Get_address(&aPoly.A, pdisp+1); 
  if(err){
      fprintf(stderr,"Bad addressing.\n");
      MPI_Abort(MPI_COMM_WORLD,1);
  }
  pbase = pdisp[0]; 
  for (i=0; i <2; i++) pdisp[i] -= pbase; 
  err = MPI_Type_create_struct(2, pblocklen, pdisp, ptype, &MPI_Polynomial);
  if(err){
      fprintf(stderr,"Can't create struct.\n");
      MPI_Abort(MPI_COMM_WORLD,1);
   }
  MPI_Type_commit(&MPI_Polynomial);

  return;
}


