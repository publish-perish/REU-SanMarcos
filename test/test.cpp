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

MPI_Datatype MPI_Tuple;
MPI_Datatype MPI_Polynomial;

void master(int, int);
void slave(int);
void construct_MPI_DataTypes();
void clear_Poly(Poly&);



int main (int argc, char *argv[]) {
  if(argc<2)
  {
     cout<<"Usage: ./executables/average_case diameter (lowerbound) \n";
     return 0;
  }

  int rank, size, i, err=0;
  const int diam = atoi(argv[1]);
  const int d_cubed = diam*diam*diam; 
  const double lowerbound = (argv[2]) ? atoi(argv[2]) : (d_cubed/16.0);
  clock_t start, end;
  
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
   
    if(rank == 0)
    {
       master(diam, size);
    }else slave(diam);

    MPI_Finalize();

    return 0;
}


void master(int diam, int size)
{
   int i;
   Poly out, in;
   T A, m;
   MPI_Request request;
   MPI_Status status;
   ifstream gens;
   PolyVec results;
   Polynomial mbest, M;

   clear_Poly(out);
   clear_Poly(in);

   gens.open("./permutationtables/GenTable.txt");if(gens){
   // Assign generators to each process.
   for(i=1; i<size; i++)
   {
       cout<<"sending to "<<i<<endl;
      gens >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> A;
      out.A.x = get<2>(A);
      out.A.y = get<1>(A);
      out.A.z = get<0>(A);
      MPI_Send(&out,sizeof(out),MPI_Polynomial,i,WORKTAG,MPI_COMM_WORLD);
   }

   // As processes finish, assign them new generators.
   //while(!gens.eof())
   //{
      //MPI_Recv(&M,1,MPI_Polynomial,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
    
      // Put into results
      //M = Polynomial(T(in.A.z,in.A.y,in.A.x),T(in.Y.z,in.Y.y,in.Y.z));
      if(M.value() > mbest.value()){mbest = M;}
      //results.push_back(M);
     // cout<<"Testing "<<M.A <<" generators, returned location "<<M.Y;

      //gens >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> A;
      //out.A.x = get<2>(A);
      //out.A.y = get<1>(A);
      //out.A.z = get<0>(A);

      //MPI_Send(&A,sizeof(A),MPI_Polynomial,status.MPI_SOURCE,WORKTAG,MPI_COMM_WORLD);
   //}gens.close();

   // No more generators, wait for processes to finish.
   for(i=1; i<size; i++)
   {
	   MPI_Recv(&in,1,MPI_Polynomial,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
   cout<<status.MPI_SOURCE<<" returned.\n";
   }
     
   // Exit all slaves.
   for(i=0; i<size; i++)
   {
      MPI_Send(0,0,MPI_INT,i,DIETAG,MPI_COMM_WORLD);
   }}else{
      fprintf(stderr,"Could not read GenTable \n");
      MPI_Abort(MPI_COMM_WORLD,2);
   }
   

   printf("Diameter: %d \n Generators: (%d, %d, %d), Location: (%d, %d, %d)", diam, get<0>(mbest.A), get<1>(mbest.A), get<2>(mbest.A), get<0>(mbest.Y), get<1>(mbest.Y), get<2>(mbest.Y)); 

    return;
}


void slave(int diam)
{
   T Q, x, A;
   struct Poly in, out;
   MPI_Status status;
   ifstream mcoeffs, xcoeffs;
   Polynomial X, X_prime, mbest, M;
   double c1;
   boost::dynamic_bitset<> cover(diam*diam*diam);
   bool covered = false;
   MCoTable QTable;
   int rank;
   string fmcoeff = "./permutationtables/MTable.txt";
   string fxcoeff = "./permutationtables/XTable.txt";

   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   string s = boost::lexical_cast<string>(rank);
   clear_Poly(in);
   clear_Poly(out);

   while(1)
   {
      MPI_Recv(&in,sizeof(in),MPI_Polynomial,0,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
cout<<"Recieved ("<<in.A.x<<" "<<in.A.y<<" "<<in.A.z<<")\n";
      if(status.MPI_TAG == DIETAG) return;
/*
      A = T(in.A.x, in.A.y, in.A.z);  
      c1 = in.A.z/in.A.y;
      QTable.makeMCoTable(diam, in.A.y, c1, rank);
      mcoeffs.open((fmcoeff.insert(fmcoeff.length()-4, s)).c_str());if(mcoeffs){
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

      out[0].x = get<2>(M.A);
      out[0].y = get<1>(M.A);
      out[0].z = get<0>(M.A);
      out[1].x = get<2>(M.Y);
      out[1].y = get<1>(M.Y);
      out[1].z = get<0>(M.Y);
*/
      MPI_Send(&in, 1, MPI_Polynomial, 0, 0, MPI_COMM_WORLD);
   }

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

