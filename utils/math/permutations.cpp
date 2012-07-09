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
   for(int i=2; i < 20; ++i)
   {
      for(int j=1; j < i; ++j)
      {
 			//for(int k=1; k < j; ++k)
      		//{
       		iout << boost::tuples::set_delimiter(',') << T(0, j, i) << " ";
     
       		++Isize;
       		//}
      }
   }
   if(sout.is_open())
   {
   for(int i=2; i < 20; ++i)
   	{
   	for(int j=1; j < i; ++j)
      {
      for(int k=0; k < j; ++k)
      	{
   	
   		sout << boost::tuples::set_delimiter(',') << T(k, j, i) << " ";
   		++Ssize;
   	  	}
   	  }
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
   for(int i=2; i < 20; ++i)
   {
      for(int j=1; j < i; ++j)
      {
         for(int k=0; k < j; ++k)
         {
         	//for(int l=0; l < k; ++l)
         	//{
        	   				
           	 	out << boost::tuples::set_delimiter(',') << T( k, j, i) <<" ";
            	++size;
           // }
        }
            	
         
      }
   }out << endl; out.close();}
   return size;
}

