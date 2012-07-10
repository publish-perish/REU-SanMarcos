#include "../basic/permutations.h"

int SITable::makeSITables()
{
   ofstream sout;
   ofstream iout;
   iout.open("./permutationtables/ITable.txt");
   sout.open("./permutationtables/STable.txt");
   Isize = 0;
   Ssize = 0;
   if(iout.is_open())
   {
   for(int i=3; i < 44; ++i)
   {
      for(int j=2; j < i; ++j)
      {
 			for(int k=1; k < j; ++k)
      		{
       		iout << boost::tuples::set_delimiter(',') << T(0, k, j, i) << " ";
     
       		++Isize;
       		}
      }
   }
   if(sout.is_open())
   {
   for(int i=0; i < 44; ++i)
   	{
   	//for(int j=1; j < i; ++j)
      //{
     // for(int k=0; k < j; ++k)
      //	{
   	
   		sout << boost::tuples::set_delimiter(',') << T(i, i+1, i+2, i+3) << " ";
   		++Ssize;
   	  	//}
   	  //}
   	}
   }
   sout << endl; sout.close();
   iout << endl; iout.close();
   }
   return Isize * Ssize;
}


int TTable::makeTTable()
{
   ofstream out;
   out.open("./permutationtables/TTable.txt");
   size = 0;
   if(out.is_open()){
   for(int i=3; i < 44; ++i)
   {
      for(int j=2; j < i; ++j)
      {
         for(int k=1; k < j; ++k)
         {
         	for(int l=0; l < k; ++l)
         	{
        	   				
           	 	out << boost::tuples::set_delimiter(',') << T(l, k, j, i) <<" ";
            	++size;
            }
        }
            	
         
      }
   }out << endl; out.close();}
   return size;
}

