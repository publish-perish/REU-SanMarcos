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
       ifstream Slist, Ilist, Tlist;
       ofstream out, archive;
       T5 s; 
       T5 i; 
       T5 t; 
       


       clock_t start, end;
       start = clock();
       makeTables(&table);
       archive.open("./ms.txt");
       Ilist.open("./permutationtables/ITable.txt");
       if(Ilist){
	    while(Ilist >> i)
       {
       	//cout << i << endl;
          Slist.open("./permutationtables/STable.txt");
          if(Slist){
          while(Slist >> s)
          {
             Tlist.open("./permutationtables/TTable.txt");
             if(Tlist){
             while(Tlist >>  t)
                {
   
                for(int a = 0; a < 150; a++) // reset cover
                {
                cover[a] = 0;
                }
                if(i[4] + t[3] > 60)
                {
                for(int a =0; a < 5; a++) // I +S : 
                {
                	for(int b =0; b < 5; b++)
                	{
                	cover[(i[a] +s[b]) ] = 1;
                	}
                }
                
                for(int a =0; a < 5; a++) // I + T: 
                {
                	for(int b =0; b < 4; b++)
                	{
                	cover[(i[a] +t[b]) ] = 1;
                	}
                }
               
  
                 for(int a =0; a < 4; a++) // T+S : 
                {
                	for(int b =1; b <5; b++)
                	{
                	cover[(t[a] +s[1]) ] = 1;
                	cover[(t[a] +s[2]) ] = 1;                	
                	
                	}
				}
	
           
				covered = true;
				counter = 0;
				for(int d =0; d < 95; ++d) //size of bitarray
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
				archive <<"value " << best << i <<  s  << t << endl;
				
				}

				}
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


for(double limit = 5; limit < 17; limit++)
{
for(double a =0; a < limit; a++)
{
	for(double b =0; b < limit - (a); b++)
	{
		for(double c =0; c < limit - (a+b); c++)
		{
			
					if((a*(b+c) + (b-1)*(c) ) / ((limit-1)*(limit-1)) > best)
					{
					best =( (a*(b+c) + (b-1)*(c))  / ((limit-1)*(limit-1)) ) ;
					abest = a;
					bbest = b;
					cbest = c;
					limbest = limit-1;
					}

		}
	}
}
}
cout << "best: " << best << " limit: " << limbest << " a: " << abest << " b: " << bbest << " c: " << cbest << endl;
return 0;
}

*/
















