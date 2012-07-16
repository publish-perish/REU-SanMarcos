#include "../utils/basic/permutations.h"
#include "../utils/basic/tuple.h"
#include "string.h"
#include <bitset>
#include <time.h>
#include <iterator>



using namespace std;


int makeTables(Table *table)
{cout<<"making tables "<<endl;
    clock_t start, end;
    start = clock();
    
    cout <<"\nSize of S Table = " << table->makeSTable() << endl;
    cout <<"\nSize of I Table = " << table->makeITable() << endl;
    cout <<"\nSize of T Table = " << table->makeTTable() << endl;
    //cout <<"\nSize of L Table = " << T->makeLTable() << endl;
    end = clock();
    cout<<"Tables were generated in "<<(double)(end - start)/(double)CLOCKS_PER_SEC<<" seconds.\n";
    return 0;
}


int main()
{
 
	   Table table;

       int cover[150]; //about twice the size of the largest thing we expect
       int counter = 0; //counts the size of the cover
       int best = 0;
       bool covered;
       ifstream Slist, Ilist, Tlist /*, Llist*/;
       ofstream out, archive;
       T5 s; 
       T5 i; 
       T5 t; 
       //T l;
       //int tierS [5];
       //int tierT [5];
       //int tierL [4];
       //int tierI [5];

       clock_t start, end;
       start = clock();
       makeTables(&table);
       archive.open("./ms.txt");
       Ilist.open("./permutationtables/ITable.txt");
       if(Ilist){
	    while(Ilist >> i)
       {
          Slist.open("./permutationtables/STable.txt");
          if(Slist){
          while(Slist >> s)
          {
             Tlist.open("./permutationtables/TTable.txt");
             if(Tlist){
             while(Tlist >>  t)
                {
                //Llist.open("./permutationtables/LTable.txt");
             ///if(Llist){
             //while(Llist >> boost::tuples::set_open('(') >> boost::tuples::set_close(')') >> boost::tuples::set_delimiter(',') >> l)
             //{
                //cover.reset();     
                //int m = 45;
   				/*
                tierI [0] = boost::tuples::get<0>(i);
                tierI [1] = boost::tuples::get<1>(i);
                tierI [2] = boost::tuples::get<2>(i);
                tierI [3] = boost::tuples::get<3>(i);
                tierI [4] = boost::tuples::get<4>(i);
                
                tierS [0] = boost::tuples::get<0>(s);;
                tierS [1] = boost::tuples::get<1>(s);;
                tierS [2] = boost::tuples::get<2>(s);;
                tierS [3] = boost::tuples::get<3>(s);;
                tierS [4] = boost::tuples::get<4>(s);;
                
                tierT [0] = boost::tuples::get<0>(t); 
                tierT [1] = boost::tuples::get<1>(t);
                tierT [2] = boost::tuples::get<2>(t);
                tierT [3] = boost::tuples::get<3>(t);
                tierT [4] = boost::tuples::get<3>(t);
                
                //tierL [0] = boost::tuples::get<0>(l);
                //tierL [1] = boost::tuples::get<1>(l);
                //tierL [2] = boost::tuples::get<2>(l);
                //tierL [3] = boost::tuples::get<3>(l);
				*/
                

                //if(tierI[0] == 0 /*|| tierS[0] == 0*/)
                	//cout << (tierI[0] +tierS[0]) << endl;
                for(int a = 0; a < 150; a++) // reset cover
                {
                cover[a] = 0;
                }
                
                for(int a =0; a < 5; a++) // I +S : 25
                {
                	for(int b =0; b < 5; b++)
                	{
                	cover[(i[a] +s[b]) ] = 1;
                	}
                }
                
                for(int a =0; a < 5; a++) // I + T: 25
                {
                	for(int b =0; b < 5; b++)
                	{
                	cover[(i[a] +t[b]) ] = 1;
                	}
                }
               
  
                 for(int a =0; a < 5; a++) // T+S : 20
                {
                	for(int b =1; b <5; b++)
                	{
                	cover[(t[a] +s[b]) ] = 1;                	
                	
                	}
				}
           
				covered = true;
				counter = 0;
				for(int d =0; d < 70; ++d) //size of bitarray
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
				archive <<"value " << best << i <<  s  << t << /*l <<*/ endl;
				
				}
				
				//}
				//}Llist.close();
				
                }
                }Tlist.close();
          }
          }Slist.close();
       }
       }Ilist.close();
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


/*
int main()
{

double best = 0;
double limbest =0;
double abest = 0;
double bbest = 0;
double cbest =0;
double dbest =0;
double ebest =0;
for(double limit = 7; limit < 19; limit++)
{
for(double a =1; a < limit; a++)
{
	for(double b =1; b < limit - (a); b++)
	{
		for(double c =1; c < limit - (a+b); c++)
		{
			for(double d =1; d < limit - (a+b+c); d++)
			{
				for(double e =1; e < limit - (a+b+c+d); e++)
				{
					if((a*(b+c)*(d+e) + (d+e)*(b-1)*(c) + (d-1)*e*a ) / ((limit-1)*(limit-1)*(limit-1)) > best)
					{
					best =(a*(b+c)*(d+e) + (d+e)*(b-1)*(c) + (d-1)*e*a ) / ((limit-1)*(limit-1)*(limit-1)) ;
					abest = a;
					bbest = b;
					cbest =c;
					dbest =d;
					ebest =e;
					limbest = limit-1;
					}
				}
			}
		}
	}
}
}
cout << "best: " << best << " limit: " << limbest << " a: " << abest << " b: " << bbest << " c: " << cbest << " d: " << dbest << " e: " << ebest << endl;
}
*/
/*
int main()
{

double best = 0;
double limbest =0;
double abest = 0;
double bbest = 0;
double cbest =0;
double dbest =0;

for(double limit = 5; limit < 12; limit++)
{
for(double a =0; a < limit; a++)
{
	for(double b =0; b < limit - (a); b++)
	{
		for(double c =0; c < limit - (a+b); c++)
		{
			for(double d =0; d < limit - (a+b+c); d++)
			{
		
					if((a*(b+c+d) + (c+d-2)*(b) + 2*(c-1)*(d-1) ) / ((limit-1)*(limit-1)) > best)
					{
					best =((a*(b+c+d) + (c/2+d-1)*(b) + 2*(c/2)*(d-1) ) / ((limit-1)*(limit-1))) ;
					abest = a;
					bbest = b;
					cbest = c;
					dbest = d;
					limbest = limit-1;
					}
			}

		}
	}
}
}
cout << "best: " << best << " limit: " << limbest << " a: " << abest << " b: " << bbest << " c: " << cbest << " d: " << dbest << endl;
return 0;
}
*/

















