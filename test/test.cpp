#include <mpi.h>
#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#include "string.h"
#include <bitset>
#include "boost/dynamic_bitset.hpp"
#include <time.h>
#include <iterator>

typedef std::vector<Polynomial> PolyVec;

#define WORKTAG 1
#define DIETAG 2


/* Local functions */

static void master(void);
static void slave(void);
static unit_of_work_t get_next_work_item(void);
static void process_results(unit_result_t result);
static unit_result_t do_work(unit_of_work_t work);


int genPosition;
int mCoeffPosition;
ofstream gens, xcoeffs;


int MPI_Type_create_struct(){



};

MPI_Datatype MPI_Polynomial;
MPI_Datatype MPI_Tuple = {MPI_INT, MPI_INT, MPI_INT};
   


int makeTables(int diam, XCoTable *X, GenTable *A)
{
    clock_t start, end;
    start = clock();
    X->makeXCoTable(diam);
    cout <<"Size of X-Coefficient Table = " << X->size;
    A->makeGenTable(diam);
    cout <<"\nSize of Generator Table = " << A->size;
    end = clock();
    cout<<"\nTables were generated in "<<(double)(end - start)/(double)CLOCKS_PER_SEC<<" seconds.\n";
    return 0;
}


int main(int argc, char **argv)
{
  int myrank;  
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
    gens.open("../permutationtables/GenTable.txt");
    xcoeffs.open("../permutationtables/XTable.txt");
    if(!gens || !xcoeffs){ return 0;}

  /* Initialize MPI */

  MPI_Init(&argc, &argv);

  /* Find out my identity in the default communicator */

  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  if (myrank == 0) {
    master(diam);
  } else {
    slave();
  }

  /* Shut down MPI */

  MPI_Finalize();
  end = clock();
  return 0;
}


static void master(int diam)
{
  int ntasks, rank;
  unit_of_work_t work;
  unit_result_t result;
  MPI_Status status;

  /* Find out how many processes there are in the default
     communicator */

  MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

  /* Seed the slaves; send one unit of work to each slave. */

  for (rank = 1; rank < ntasks; ++rank) {

    /* Find the next item of work to do */

    work = get_next_work_item(T &A);

    /* Send it to each rank */

    MPI_Send(&work,             /* message buffer */
             1,                 /* one data item */
             MPI_INT,           /* data item is an integer */
             rank,              /* destination process rank */
             WORKTAG,           /* user chosen message tag */
             MPI_COMM_WORLD);   /* default communicator */
  }

  /* Loop over getting new work requests until there is no more work
     to be done */

  work = get_next_work_item(T &A);
  while (work != NULL) {

    /* Receive results from a slave */

    MPI_Recv(&result,           /* message buffer */
             1,                 /* one data item */
             MPI_DOUBLE,        /* of type double real */
             MPI_ANY_SOURCE,    /* receive from any sender */
             MPI_ANY_TAG,       /* any type of message */
             MPI_COMM_WORLD,    /* default communicator */
             &status);          /* info about the received message */

    /* Send the slave a new work unit */

    MPI_Send(&work,             /* message buffer */
             1,                 /* one data item */
             MPI_INT,           /* data item is an integer */
             status.MPI_SOURCE, /* to who we just received from */
             WORKTAG,           /* user chosen message tag */
             MPI_COMM_WORLD);   /* default communicator */

    /* Get the next unit of work to be done */

    work = get_next_work_item(T &A);
  }

  /* There's no more work to be done, so receive all the outstanding
     results from the slaves. */

  for (rank = 1; rank < ntasks; ++rank) {
    MPI_Recv(&result, 1, MPI_DOUBLE, MPI_ANY_SOURCE,
             MPI_ANY_TAG, MPI_COMM_WORLD, &status);
  }

  /* Tell all the slaves to exit by sending an empty message with the
     DIETAG. */

  for (rank = 1; rank < ntasks; ++rank) {
    MPI_Send(0, 0, MPI_INT, rank, DIETAG, MPI_COMM_WORLD);
  }
}


static void slave(void)
{
  unit_of_work_t work;
  unit_result_t results;
  MPI_Status status;

  while (1) {

    /* Receive a message from the master */

    MPI_Recv(&work, 1, MPI_INT, 0, MPI_ANY_TAG,
             MPI_COMM_WORLD, &status);

    /* Check the tag of the received message. */

    if (status.MPI_TAG == DIETAG) {
      return;
    }

    /* Do the work */

    result = do_work(work);

    /* Send the result back */

    MPI_Send(&result, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  }
}


static void unit_of_work_t get_next_work_item(T &A)
{
	gens >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> A;
}


static void 
process_results(unit_result_t result)
{

}


static unit_result_t
do_work(unit_of_work_t work)
{

}
