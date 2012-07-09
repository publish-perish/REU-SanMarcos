#include "../utils/basic/permutations.h"
#include "../utils/basic/tuple.h"
#include "string.h"
#include <bitset>
#include "boost/dynamic_bitset.hpp"
#include <time.h>
#include <iterator>



using namespace std;


int makeTables( SITable *SI, TTable *T)
{cout<<"making tables "<<endl;
    clock_t start, end;
    start = clock();
    
    cout <<"\nSize of SI Table = " << SI->makeSITables() << endl << endl;
    cout <<"\nSize of T Table = " << T->makeTTable() << endl;
    end = clock();
    cout<<"Tables were generated in "<<(double)(end - start)/(double)CLOCKS_PER_SEC<<" seconds.\n";
    return 0;
}


int main()
{
 
	   SITable SItab;
       TTable Ttab;

       boost::dynamic_bitset<> cover(64); //a squared
       int counter = 0; //counts the size of the cover
       int best = 0;
       bool covered;
       ifstream Slist, Ilist, Tlist;
       ofstream out, archive;
       T s; 
       T i; 
       T t; 
       clock_t start, end;
       start = clock();
       makeTables( &SItab, &Ttab);
       archive.open("./ms.txt");
       Slist.open("./permutationtables/STable.txt");
       if(Slist){
	    while(Slist >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> s)
       {
          Ilist.open("./permutationtables/ITable.txt");
          if(Ilist){
          while(Ilist >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> i)
          {
             Tlist.open("./permutationtables/TTable.txt");
             if(Tlist){
                while(Tlist >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> t)
                {
                cover.reset();
                int m = 19;
                cover[(boost::tuples::get<0>(s) + boost::tuples::get<0>(i))%m] = 1;
                cover[(boost::tuples::get<0>(s) + boost::tuples::get<1>(i))%m] = 1;
                cover[(boost::tuples::get<0>(s) + boost::tuples::get<2>(i))%m] = 1;
                //cover[(boost::tuples::get<0>(s) + boost::tuples::get<3>(i))%m] = 1;
                cover[(boost::tuples::get<1>(s) + boost::tuples::get<0>(i))%m] = 1;
                cover[(boost::tuples::get<1>(s) + boost::tuples::get<1>(i))%m] = 1;
                cover[(boost::tuples::get<1>(s) + boost::tuples::get<2>(i))%m] = 1;
                //cover[(boost::tuples::get<1>(s) + boost::tuples::get<3>(i))%m] = 1;
                cover[(boost::tuples::get<2>(s) + boost::tuples::get<0>(i))%m] = 1;
                cover[(boost::tuples::get<2>(s) + boost::tuples::get<1>(i))%m] = 1;
                cover[(boost::tuples::get<2>(s) + boost::tuples::get<2>(i))%m] = 1;
                //cover[(boost::tuples::get<2>(s) + boost::tuples::get<3>(i))%m] = 1;
                //cover[(boost::tuples::get<3>(s) + boost::tuples::get<0>(i))%m] = 1;
                //cover[(boost::tuples::get<3>(s) + boost::tuples::get<1>(i))%m] = 1;
                //cover[(boost::tuples::get<3>(s) + boost::tuples::get<2>(i))%m] = 1;
                //cover[(boost::tuples::get<3>(s) + boost::tuples::get<3>(i))%m] = 1;
                
                cover[(boost::tuples::get<0>(t) + boost::tuples::get<0>(i))%m] = 1;
                cover[(boost::tuples::get<0>(t) + boost::tuples::get<1>(i))%m] = 1;
                cover[(boost::tuples::get<0>(t) + boost::tuples::get<2>(i))%m] = 1;
                //cover[(boost::tuples::get<0>(t) + boost::tuples::get<3>(i))%m] = 1;
                cover[(boost::tuples::get<1>(t) + boost::tuples::get<0>(i))%m] = 1;
                cover[(boost::tuples::get<1>(t) + boost::tuples::get<1>(i))%m] = 1;
                cover[(boost::tuples::get<1>(t) + boost::tuples::get<2>(i))%m] = 1;
                //cover[(boost::tuples::get<1>(t) + boost::tuples::get<3>(i))%m] = 1;
                //cover[(boost::tuples::get<2>(t) + boost::tuples::get<0>(i))%m] = 1;
                //cover[(boost::tuples::get<2>(t) + boost::tuples::get<1>(i))%m] = 1;
                //cover[(boost::tuples::get<2>(t) + boost::tuples::get<2>(i))%m] = 1;
                //cover[(boost::tuples::get<2>(t) + boost::tuples::get<3>(i))%m] = 1;
                //cover[(boost::tuples::get<3>(t) + boost::tuples::get<0>(i))%m] = 1;
                //cover[(boost::tuples::get<3>(t) + boost::tuples::get<1>(i))%m] = 1;
                //cover[(boost::tuples::get<3>(t) + boost::tuples::get<2>(i))%m] = 1;
                //cover[(boost::tuples::get<3>(t) + boost::tuples::get<3>(i))%m] = 1;
                
                //cover[(boost::tuples::get<0>(s) + boost::tuples::get<0>(t))%m ] = 1;
                //cover[(boost::tuples::get<0>(s) + boost::tuples::get<1>(t))%m ] = 1;
                //cover[(boost::tuples::get<0>(s) + boost::tuples::get<2>(t))%m ] = 1;
                //cover[(boost::tuples::get<0>(s) + boost::tuples::get<3>(t))%m ] = 1;
                cover[(boost::tuples::get<1>(s) + boost::tuples::get<0>(t))%m ] = 1;
                cover[(boost::tuples::get<1>(s) + boost::tuples::get<1>(t))%m ] = 1;
                //cover[(boost::tuples::get<1>(s) + boost::tuples::get<2>(t))%m ] = 1;
                //cover[(boost::tuples::get<1>(s) + boost::tuples::get<3>(t))%m ] = 1;
                cover[(boost::tuples::get<2>(s) + boost::tuples::get<0>(t))%m ] = 1;
                cover[(boost::tuples::get<2>(s) + boost::tuples::get<1>(t))%m ] = 1;
                //cover[(boost::tuples::get<2>(s) + boost::tuples::get<2>(t))%m ] = 1;
                //cover[(boost::tuples::get<2>(s) + boost::tuples::get<3>(i))%m ] = 1;
                //cover[(boost::tuples::get<3>(s) + boost::tuples::get<0>(t))%m ] = 1;
                //cover[(boost::tuples::get<3>(s) + boost::tuples::get<1>(t))%m ] = 1;
                //cover[(boost::tuples::get<3>(s) + boost::tuples::get<2>(t))%m ] = 1;
                //cover[(boost::tuples::get<3>(s) + boost::tuples::get<3>(i))%m ] = 1;
                
                
				covered = true;
				counter = 0;
				for(int d =0; d < 64; ++d) //size of bitarray
				{
					if(cover[d] == 1)
					{
						counter++;
						
					}
					else
					{
					covered = false;
					break;
					}
				}
				if( counter > best )
				{
				best = counter;
				archive <<"value " << best << s <<  i  << t << endl;
				}
                }
                }Tlist.close();
          }
          }Ilist.close();
       }
       }Slist.close();
   end = clock();

   out.open("./results.txt");
   if(out)
      {
        //output your best value
        out<< "Program ran for "<< (double)(end - start)/(double)CLOCKS_PER_SEC <<" seconds. \n";
      }
   out.close();
   archive.close();
   cout<< "Program ran for "<< (double)(end - start)/(double)CLOCKS_PER_SEC <<" seconds. \n";
 
   return 0;
}
