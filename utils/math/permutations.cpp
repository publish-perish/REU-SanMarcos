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
	    for(int j=i; j >= 0; --j)
	    {
		    for(int k=j;k >= 0; --k) //filter them in holding tank, then add to file
		    {
		    if(i+j+k <= diam - 3)
		    {cout<<"making tuple\n";
			    holdingTank.clear();
			    holdingTank.insert(T(i, j, k));
			    holdingTank.insert(T(i, k, j));
			    holdingTank.insert(T(j, i, k));
			    holdingTank.insert(T(j, k, i));
			    holdingTank.insert(T(k, i, j));
			    holdingTank.insert(T(k, j, i));
                cout<<"done making a set\n";
			   /* std::set<T>::iterator itr = holdingTank.begin();
			    while(itr != holdingTank.end())
     		    { 
          		   	out << *itr;
          		   	++size;
         		    itr++;     
	        	}	
			    holdingTank.clear();
		   */ }			
		    }	
	    }
        }}

    out << endl;
    out.close();
   }
    return;
}


void MCoTable::makeMCoTable(int diam, int b, int c1, int rank)
{
   ofstream out;
   stringstream s;
   string fname = "./permutationtables/MTable.txt";
   s << rank;
   out.open((fname.insert(fname.length()-4, s.str())).c_str());
   size = 0;
   if(out.is_open()){
    for(int i=1; i < (diam*diam*diam / (b*c1)); ++i)
    {
	    for(int j=1; j < (b); ++j)
	    {
		    for(int k=1; k < (c1); ++k) //filter them in holding tank, then add to file
		    {
      		   	out << T(i, j, k);
      		   	++size;
		    }
	    }
    }}
    out << endl;
    out.close();
    return;
}


void GenTable::makeGenTable(int diam)  //order: c, b, 1
{
    size =0;
    std::ofstream out("./permutationtables/GenTable.txt");
    if(out.is_open()){
    for(int i=2; i < (diam*diam*diam/6); i++)
    {
	    for(int j=2; j < (diam*diam*diam/6); j++)
	    {
          for(int k=0; k < j && k < i; k++)
          {
	       T4 A(i*j, k, j, 1);
		    if(i*j < (diam*diam*diam/6) ) 
            {
         	    out << A;
         	    size++;
            }
         }
        }
    }}
    out << endl;
    out.close();
    return;
}
