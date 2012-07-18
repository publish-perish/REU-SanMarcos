#include "../basic/permutations.h"


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
   out.open("./permutationtables/MTable.txt");
   size = 0;
   if(out.is_open()){
   for(int i=1; i < (float)(diam*diam*diam*diam*diam / (120*d)); ++i)
   {
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

   return;
}


