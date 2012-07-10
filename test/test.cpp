#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#include "string.h"
#include "boost/dynamic_bitset.hpp"
#include <time.h>
#include <iterator>
#include <fstream>
#include <boost/lexical_cast.hpp>

#define WORKTAG 1
#define DIETAG 2

typedef std::vector<Polynomial> PolyVec;


struct Tuple{
    int x;
    int y;
    int z;
  };

struct Poly{
    Tuple A;
    Tuple Y;
};

//MPI Datatypes
MPI_Datatype MPI_Tuple;
MPI_Datatype MPI_Polynomial;

void master(int, int, Polynomial&);
void slave(int);
void construct_MPI_DataTypes();
void clear_Poly(Poly&);


int main (int argc, char *argv[]) {
  if(argc<2)
  {
     printf("Usage: ./executables/average_case diameter (lowerbound) \n");
     return 0;
  }

  int rank, size, i, err=0;
  const int diam = atoi(argv[1]);
  const int d_cubed = diam*diam*diam; 
  const double lowerbound = (argv[2]) ? atoi(argv[2]) : (d_cubed/16.0);
  clock_t start, end;
  Polynomial mbest;

  start = clock();
  //makeTables(diam);

  // Init MPI & get size and rank 
  MPI_Init(&argc,&argv);
  err = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  err = MPI_Comm_size(MPI_COMM_WORLD, &size); 
  if(err){
      fprintf(stderr,"Catastrophic MPI problem.\n");
      MPI_Abort(MPI_COMM_WORLD,1);
  }
  
    construct_MPI_DataTypes();
    
    printf("I am process %d \n", rank);
    if(rank == 0)
    {
       master(diam, size, mbest);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if(rank != 0){ 
        slave(diam);
    }

    printf("I am process %d \n",rank);
    
    MPI_Type_free(&MPI_Tuple);
    MPI_Type_free(&MPI_Polynomial);

    MPI_Finalize();

//cout<<"mbest "<<mbest;
//cout<<"(c b a) "<<  get<0>(mbest.A)<< get<1>(mbest.A)<< get<2>(mbest.A)<<endl;
//printf("Diameter: %d \n Generators: (%d, %d, %d), Location: (%d, %d, %d)\n", diam, get<0>(mbest.A), get<1>(mbest.A), get<2>(mbest.A), get<0>(mbest.Y), get<1>(mbest.Y), get<2>(mbest.Y)); 

 
    return 0;
    exit(1);    
}


void master(int diam, int size, Polynomial &mbest)
{
   // Buffers
   Poly sendbuf[size], recvbuf[size], send, recv;
   //MPI_Alloc_mem(sizeof(struct Poly)*size, MPI_INFO_NULL, &out);
   //MPI_Alloc_mem(sizeof(struct Poly)*size, MPI_INFO_NULL, &in);

   int i;
   T A, m;
   MPI_Request request;
   MPI_Status status;
   ifstream gens;
   PolyVec results;
   Polynomial M;

   gens.open("./permutationtables/GenTable.txt");if(gens){
   // Assign generators to each process.
   for(i=1; i<size; ++i)
   {
      gens >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> A;
      sendbuf[i-1].A.x = get<2>(A);
      sendbuf[i-1].A.y = get<1>(A);
      sendbuf[i-1].A.z = get<0>(A);
   printf("sending ( %d %d %d ) to %d \n",sendbuf[i-1].A.x, sendbuf[i-1].A.y, sendbuf[i-1].A.z, i);
      MPI_Send(&sendbuf[i-1],1, MPI_Polynomial,i,WORKTAG,MPI_COMM_WORLD);
   }
//   MPI_Scatter(&sendbuf[0],1,MPI_Polynomial,&recvbuf[0],1,MPI_Polynomial,0,MPI_COMM_WORLD);
   //for(i=1; i<size; ++i)
  // {
  // cout<<"getting ("<<out[i-1]->A.x<<" "<<out[i-1]->A.y<<" "<<out[i-1]->A.z<<") from "<<i<<endl;
  // }
   // As processes finish, assign them new generators.
   //while(!gens.eof())
   //{
      //MPI_Recv(&M,1,MPI_Polynomial,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
    
      // Put into results
      //M = Polynomial(T(in.A.z,in.A.y,in.A.x),T(in.Y.z,in.Y.y,in.Y.z));
//      if(M.value() > mbest.value()){mbest = M;}
      //results.push_back(M);
     // cout<<"Testing "<<M.A <<" generators, returned location "<<M.Y;

      //gens >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> A;
      //out.A.x = get<2>(A);
      //out.A.y = get<1>(A);
      //out.A.z = get<0>(A);

      //MPI_Send(&A,sizeof(A),MPI_Polynomial,status.MPI_SOURCE,WORKTAG,MPI_COMM_WORLD);
   //}gens.close();
printf("Size: %d \n", size);
   // No more generators, wait for processes to finish.
   for(i=1; i<size; ++i)
   {
//      MPI_Recv(&recv,sizeof(struct Poly),MPI_Polynomial,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
  // cout<<status.MPI_SOURCE<<" returned with A ("<<recv.A.x<<" "<<recv.A.y<<" "<<recv.A.z<<")\n";
   }

   // Exit all slaves.
   for(i=1; i<size; ++i)
   {printf("Exiting slave %d \n",i);
      MPI_Send(0,0,MPI_INT,i,DIETAG,MPI_COMM_WORLD);
   }}else{
      fprintf(stderr,"Could not read GenTable \n");
      MPI_Abort(MPI_COMM_WORLD,2);
   }
  

   // MPI_Free_mem(out);
    //MPI_Free_mem(in);

    return;
}


void slave(int diam)
{
   T Q, x, A;
   struct Poly in, out;
   MPI_Status status;
   MPI_Request request;
   ifstream mcoeffs, xcoeffs;
   Polynomial X, X_prime, mbest, M;
   double c1;
   boost::dynamic_bitset<> cover(diam*diam*diam);
   bool covered = false;
   MCoTable QTable;
   int rank, die;
   string fmcoeff = "./permutationtables/MTable.txt";
   string fxcoeff = "./permutationtables/XTable.txt";


//   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  // string s = boost::lexical_cast<string>(rank);
   //clear_Poly(in);
   //clear_Poly(out);
   
   //while(1)
   //{
       MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    string s = boost::lexical_cast<string>(rank);
   printf("I am slave %d \n",rank);
      MPI_Recv(&in,sizeof(struct Poly),MPI_Polynomial,0,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
      if(status.MPI_TAG == DIETAG){ return;}
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
printf("Process %d recieved (%d %d %d) \n",rank, in.A.x, in.A.y, in.A.z);
/*
      A = T(in.A.x, in.A.y, in.A.z);  
      c1 = in.A.z/in.A.y;
      QTable.makeMCoTable(diam, in.A.y, c1, 1);
      cout<<"made MTable"<<rank<<".txt\n";
      mcoeffs.open((fmcoeff.insert(fmcoeff.length()-4, s)).c_str());cout<<"opening "<<(fmcoeff.insert(fmcoeff.length()-4, s)).c_str()<<endl;if(mcoeffs){
      while(mcoeffs >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> Q)
      {
         M = Polynomial(A, Q);
         cover.reset();
         if((M.value() > mbest.value()) && M.wellFormed() && (M.sum() < (diam*diam*diam))) //ignore M that are too small, or badly formed
         {
            xcoeffs.open((fxcoeff.insert(fxcoeff.length()-4, s).c_str()));if(xcoeffs){
            while(xcoeffs >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> x)
            {
               X = Polynomial(A, x);
               X_prime = X-M;
               if(X_prime.wellFormed()){ 
               cover[X_prime.sum()] = 1;	
            }xcoeffs.close();
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
            }}else{
            fprintf(stderr,"Could not read XTable%d", rank);
            MPI_Abort(MPI_COMM_WORLD,2);
            }

         }
      }}else{
      fprintf(stderr,"Could not read MTable%d", rank);
      MPI_Abort(MPI_COMM_WORLD,2);
      }

      out.A.x = get<2>(M.A);
      out.A.y = get<1>(M.A);
      out.A.z = get<0>(M.A);
      out.Y.x = get<2>(M.Y);
      out.Y.y = get<1>(M.Y);
      out.Y.z = get<0>(M.Y);
*/
      MPI_Send(&in,sizeof(struct Poly),MPI_Polynomial,0,WORKTAG,MPI_COMM_WORLD);
    printf("Sent back from %d\n", rank);
    //}
}


void construct_MPI_DataTypes()
{
  int i, err = 0;

  // Construct MPI Tuple
  MPI_Type_contiguous(3, MPI_INT, &MPI_Tuple);
  MPI_Type_commit(&MPI_Tuple);

  // Construct MPI Polynomial
  struct Poly aPoly;
  MPI_Datatype ptype[2] = {MPI_Tuple, MPI_Tuple};
  MPI_Aint pdisp[2];
  int pbase;
  int pblocklen[3] = {12, 12};

  // MPI description of Tuple
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


void clear_Poly(Poly &p)
{     
     p.Y.x = 0;
     p.Y.y = 0;
     p.Y.z = 0;
     p.A.x = 0;
     p.A.y = 0;
     p.A.z = 0;

     return;
}


/*
int makeTables(int diam)
{
    XCoTable X;
    GenTable A;
    clock_t start, end;
    start = clock();
    X.makeXCoTable(diam);
    std::cout <<"Size of X-Coefficient Table = " << X.size;
    A.makeGenTable(diam);
    std::cout <<"\nSize of Generator Table = " << A.size;
    end = clock();
    std::cout<<"\nTables were generated in "<<(double)(end - start)/(double)CLOCKS_PER_SEC<<" seconds.\n";
    return 0;
}
*/

