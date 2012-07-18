#include "../basic/permutations.h"

void XCoTable::makeXCoTable(int diam, int numprocs)
{
   ofstream out;
   for(int rank=1; rank <= numprocs; rank++)
   {
       stringstream s;
       string fname = "./permutationtables/XTable.txt";
       s << rank;
       out.open((fname.insert(fname.length()-4, s.str())).c_str());
       size = 0;
       if(out.is_open()){
       for(int i=diam; i >= 0; --i)
       {
          for(int j=diam-i; j >= 0; --j)
          {
             for(int k=diam-i-j;k >= 0; --k) //filter them in holding tank, then add to file
             {
             if(i+j+k <= diam - 3)
             {
                holdingTank.clear();
                holdingTank.insert(T(i, j, k));
                holdingTank.insert(T(i, k, j));
                holdingTank.insert(T(j, i, k));
                holdingTank.insert(T(j, k, i));
                holdingTank.insert(T(k, i, j));
                holdingTank.insert(T(k, j, i));
                std::set<T>::iterator itr = holdingTank.begin();
                while(itr != holdingTank.end())
                {
                     out << *itr;
                     ++size;
                     itr++;     
                }	
                holdingTank.clear();
             }			
             }	
          }
       }out << endl; out.close();}
   }

void GenTable::makeGenTable(int diam)  //order: c, b, 1
{
size =0;
std::ofstream myfile ("./permutationtables/gentable.txt");
for(int i=2; i < (diam*diam*diam*diam*diam*120); i++)
{
	for(int j=2; j < (diam*diam*diam*diam*diam/(i*120)); j++)
	{
      for(int k=2; k < (diam*diam*diam*diam*diam/(i*j*120)); k++)
      {
	   TP A(i*j*k, j*k, j, 1);
		if(myfile.is_open() && i*j*k < (diam*diam*diam*diam/120) ) 
      {
     	//std::cout << A;
     	myfile << boost::tuples::set_delimiter(',') << A << " ";
     	size++;
      }
      }
	}
}
//genCount=0;
myfile << endl;
myfile.close();
return;
}


void XCoTable::makeXCoTable(int diam)
{
   ofstream out;
   out.open("./permutationtables/XTable.txt");
   size = 0;
   if(out.is_open()){
   for(int i=0; i <= diam-5; i++)
   {
      for(int j=0; j <= diam - (5+i); ++j)
      {
         for(int k=0;k <= diam - (5+i+j); ++k) //filter them in holding tank, then add to file
         {
         	for(int l=0; l <= diam - (5 +i +j +k); ++l)
      		{

                 out << boost::tuples::set_delimiter(',') << TP(l, k, j, i) <<" ";
                 ++size;

            
         	}			
         }	
      }
   }out << endl; out.close();}
   return;
}


void MCoTable::makeMCoTable(const int diam, int e, int d, int c, int b)
{
   ofstream out;
   stringstream s;
   string fname = "./permutationtables/MTable.txt";
   s << rank;
   out.open((fname.insert(fname.length()-4, s.str())).c_str());
   size = 0;
   if(out.is_open()){
   for(int i=1; i < (float)(diam*diam*diam*diam*diam / (120*d)); ++i)
   {
      for(int j=1; j < (c1); ++j)
      {
         for(int k=1; k < (b); ++k) //filter them in holding tank, then add to file
         {
            out << T(i, j, k) ;
      for(int j=1; j < (float)(e/d); ++j)
      {
         for(int k=1; k < (float)(d/c); ++k)
         {
         	for(int l=1; l < (float)(c/b); ++l)
         	{	
			for(int p=1; p < (float)(b); p++)
			{
         		  TP Q(i, j, k, l, p);
            out << boost::tuples::set_delimiter(',') << Q <<" ";
            ++size;
			}
           	 }
         }
      }
   }out << endl; out.close();}
   return true;
}


void GenTable::makeGenTable(int diam)  //order: c, b, 1
{
   ofstream out;
   out.open("./permutationtables/GenTable.txt");
   size = 0;
   if(out.is_open()){
   for(int i=2; i < (diam*diam*diam/6); i++)
   {
      for(int j=2; j < (diam*diam*diam/6); j++)
      {
         if(i*j < diam*diam*diam/6)
         {
            out<< T(i*j,j,1) ;
            ++size;
         }
      }
   } out<< endl; out.close();}

   return;
}


