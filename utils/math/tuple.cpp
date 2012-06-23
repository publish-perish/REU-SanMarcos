

template<typename TP, int N>
Tuple Tuple::operator-(const Tuple &t)
{
   double a, b, c; // temp variables for polynomial ax + bx^2 + cx^3
   bool flag = true;
   vector<TP> list;

   for(int i; i<sizeof(t); i++)
   {
      if( data.at(i) < t.data.at(i))
      {
         flag = false;
      }
      else
      {
         list.push_back(data.at(i)-t.data.at(i));
      }

   }
   if(flag)
   {
      return Tuple<TP, N>(list);
   }
}
