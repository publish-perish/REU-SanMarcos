#include "../basic/permutations.h"

void XCoTable::makeXCoTable(int diam)
{
   ofstream out;
   out.open("./permutationtables/XTable.txt");
   size = 0;
   if(out.is_open()){
   for(int i=diam; i >= 0; --i)
   {
      for(int j=i; j >= 0; --j)
      {
         for(int k=j;k >= 0; --k) //filter them in holding tank, then add to file
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
                 out << boost::tuples::set_delimiter(',') << *itr <<" ";
                 ++size;
                 itr++;     
            }	
            holdingTank.clear();
         }			
         }	
      }
   }out << endl; out.close();}
   return;
}


void MCoTable::makeMCoTable(const int diam, int b, double c1)
{
   ofstream out;
   out.open("./permutationtables/MTable.txt");
   size = 0;
   if(out.is_open()){
   for(int i=1; i < (diam*diam*diam / (6 *b*c1)); ++i)
   {
      for(int j=1; j < c1; ++j)
      {
         for(int k=1; k < b; ++k)
         {
            out << boost::tuples::set_delimiter(',') << T(i, j, k) <<" ";
            ++size;
         }
      }
   }out << endl; out.close();}
   return;
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
            out<< boost::tuples::set_delimiter(',') << T(i*j,j,1) <<" ";
            ++size;
         }
      }
   } out<< endl; out.close();}
   return;
}

