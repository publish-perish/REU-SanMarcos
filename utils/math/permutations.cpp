#include "../basic/permutations.h"

void XCoTable::makeXCoTable(int diam)
{
   XCoeffs.clear();
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
               XCoeffs.push_back(*itr);
               itr++;     
            }	
            holdingTank.clear();
         }			
         }	
      }
   }
   return;
}


void MCoTable::makeMCoTable(const int diam, int b, float c)
{
   MCoeffs.clear();
   for(int i=1; i < (diam*diam*diam / (b*c)); ++i)
   {
      for(int j=1; j < (b); ++j)
      {
         for(int k=1; k < (c); ++k) //filter them in holding tank, then add to file
         {
            MCoeffs.push_back(T(i, j, k));
         }
      }
   }
   return;
}


void GenTable::makeGenTable(int diam)  //order: c, b, 1
{
   Generators.clear();
   for(int i=2; i < (diam*diam*diam/6); i++)
   {
      for(int j=2; j < (diam*diam*diam/6); j++)
      {
         Generators.push_back(T(i*j,j,1));
      }
   }
   return;
}

