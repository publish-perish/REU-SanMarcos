#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#include "string.h"
#include <bitset>
#include "boost/dynamic_bitset.hpp"
#include <time.h>
#include <iterator>
#include <fstream>

#define WORKTAG 1
#define DIETAG 2

typedef std::vector<Polynomial> PolyVec;

static void master(int, int);
static void slave(int);
int makeTables(int);

struct Tuple {
    int x;
    int y;
    int z;
  };

struct Poly {
     Tuple Y;
     Tuple A;
  };

MPI_Datatype MPI_Tuple;
MPI_Datatype MPI_Polynomial;


int main (int argc, char *argv[]) {
  if(argc<2)
  {
     cout<<"Usage: ./executables/average_case diameter (lowerbound) \n";
     return 0;
  }

  int rank, size, i;
  const int diam = atoi(argv[1]);
  const int d_cubed = diam*diam*diam; 
  const double lowerbound = (argv[2]) ? atoi(argv[2]) : (d_cubed/16.0);
  clock_t start, end;
  
  start = clock();
  makeTables(diam);

  // Construct MPI Tuple
  struct Tuple aTuple;
  MPI_Datatype type[3] = {MPI_INT, MPI_INT, MPI_INT};
  MPI_Aint disp[3];
  int base;
  int blocklen[3] = {1, 1, 1};
  MPI_Datatype MPI_Tuple;

  // Construct MPI Polynomial
  struct Poly aPoly;
  MPI_Datatype typePoly[2] = {MPI_Tuple, MPI_Tuple};
  MPI_Aint dispPoly[2];
  int basePoly;
  int blocklenPoly[2] = {1, 1};
  MPI_Datatype MPI_Polynomial;

  // Init MPI & get size and rank 
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size); 

  // MPI description of Tuple
  MPI_Address(&aTuple.x, disp); 
  MPI_Address(&aTuple.y, disp+1); 
  MPI_Address(&aTuple.z, disp+2); 
  base = disp[0]; 
  for (i=0; i <3; i++) disp[i] -= base; 
  MPI_Type_create_struct(3, blocklen, disp, type, &MPI_Tuple);
  MPI_Type_commit(&MPI_Tuple);

  // MPI description of Polynomial
  MPI_Address(&aPoly.Y, dispPoly);
  MPI_Address(&aPoly.A, dispPoly+1);
  basePoly = dispPoly[0];
  for(i=0; i<2; i++) dispPoly[i] -= basePoly;
  MPI_Type_create_struct(2, blocklenPoly, dispPoly, typePoly, &MPI_Polynomial);


  if(rank == 0){
     master(diam, size);
  }
  else slave(diam);

  MPI_Finalize();
  return 0;
}


static void master(int size, int diam)
{
   struct Poly out, in;
   T A;
   int i;
   MPI_Request request;
   MPI_Status status;
   ifstream gens;
   PolyVec results;
   Polynomial mbest, M;

   gens.open("../permutationtables/GenTable.txt");if(gens){
   // Assign generators to each process.
   for(i=0; i<=size; i++)
   {
      gens >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> A;
      out.A.x = get<2>(A);
      out.A.y = get<1>(A);
      out.A.z = get<0>(A);
   
      MPI_Send(&out,1,MPI_Polynomial,i,WORKTAG,MPI_COMM_WORLD);
   }

   // As processes finish, assign them new generators.
   while(!gens.eof())
   {
	   MPI_Recv(&in,1,MPI_Polynomial,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
    
      // Put into results
      M = Polynomial(T(in.A.z,in.A.y,in.A.x),T(in.Y.z,in.Y.y,in.Y.z));
      if(M.value() > mbest.value()){mbest = M;}
      results.push_back(M);

      gens >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> A;
      out.A.x = get<2>(A);
      out.A.y = get<1>(A);
      out.A.z = get<0>(A);
   
      MPI_Send(&out,1,MPI_Polynomial,status.MPI_SOURCE,WORKTAG,MPI_COMM_WORLD);
   }gens.close();

   // No more generators, wait for processes to finish.
   for(i=0; i<=size; i++)
   {
	   MPI_Recv(&in,1,MPI_Polynomial,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
   }
     
   // Exit all slaves.
   for(i=0; i<=size; i++)
   {
      MPI_Send(0,0,MPI_INT,i,DIETAG,MPI_COMM_WORLD);
   }}

 
}

static void slave(int diam)
{
   T Q, x, A;
   Poly in, out;
   MPI_Status status;
   ifstream mcoeffs, xcoeffs;
   Polynomial X, X_prime, mbest, M;
   double c1;
   boost::dynamic_bitset<> cover(diam*diam*diam);
   bool covered = false;
   MCoTable QTable;

   while(1)
   {
      MPI_Recv(&in,1,MPI_Polynomial,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);

      if(status.MPI_TAG == DIETAG) return;

      A = T(in.A.x, in.A.y, in.A.z);  
      c1 = in.A.z/in.A.y;
      QTable.makeMCoTable(diam, in.A.y, c1);
      mcoeffs.open("./permutationtables/MTable.txt");if(mcoeffs){
      while(mcoeffs >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> Q)
      {
         M = Polynomial(A, Q);
         cover.reset();
         if((M.value() > mbest.value()) && M.wellFormed() && (M.sum() < (diam*diam*diam))) //ignore M that are too small, or badly formed
         {
            xcoeffs.open("./permutationtables/XTable.txt");if(xcoeffs){
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
            }}
         }
      }}
      out.A.x = get<2>(M.A);
      out.A.y = get<1>(M.A);
      out.A.z = get<0>(M.A);
      out.Y.x = get<2>(M.Y);
      out.Y.y = get<1>(M.Y);
      out.Y.z = get<0>(M.Y);

      MPI_Send(&out, 1, MPI_Polynomial, 0, 0, MPI_COMM_WORLD);
   }
}



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


