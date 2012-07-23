#include "../basic/permutations.h"


void GenTable::makeGenTable(int diam)  //order: e, d, c, b, 1
{
size =0;
std::ofstream myfile ("./permutationtables/GenTable.txt");
for(int i=2; i < (diam*diam*diam*diam*diam*diam/720); i++)
{
	for(int j=2; j < (diam*diam*diam*diam*diam*diam/(i*720)); j++)
	{
      for(int k=2; k < (diam*diam*diam*diam*diam*diam/(i*j*720)); k++)
       {
			for(int l=2; l < (diam*diam*diam*diam*diam*diam/(k*i*j*720)); l++)
        	{  	
        	for(int m=42; m < (diam*diam*diam*diam*diam*diam/(l*k*i*j*720)); m++)
        	{ 
				if(myfile.is_open() && i*j*k*l*m < (diam*diam*diam*diam*diam*diam/720) ) 
       			{
     			myfile  << T6(i*j*k*l*m, i*j*k*l, i*j*k, j*k, j, 1);
     			size++;
       			}
       		}
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
                	 out << T6(n, m, l, k, j, i);
                 	++size;
                 	}
           		}
         	}			
         }	
      }
   }out << endl; out.close();}
   return;
}


void MCoTable::makeMCoTable(const int diam, int f, int e, int d, int c, int b)
{
   ofstream out;
   out.open("./permutationtables/MTable.txt");
   size = 0;
   if(out.is_open()){
   for(int i=1; i < (float)(diam*diam*diam*diam*diam / (720*f)); ++i)
   {
      for(int j=1; j < (float)(f / e); ++j)
      {
         for(int k=1; k < (float)(e / d); ++k)
         {
         	for(int l=1; l < (float)(d / c); ++l)
         	{	
				for(int m=1; m < (float)(c / b); ++m)
         		{
         			for(int n=1; n < b; ++n)
         			{
            		out << T6(i, j, k, l, m, n);
            		++size;
            		}
				}

            }
         }
      }
   }out << endl; out.close();}
//cout << size << endl;
   return;
}



