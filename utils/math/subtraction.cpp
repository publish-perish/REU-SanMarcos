#include "../basic/subtraction.h"

Subtractions::Subtractions()
{
   e_borrowed = d_borrowed = c_borrowed = b_borrowed = m_subtracted = 0;
}

Subtractions::Subtractions(int x)
{
   e_borrowed = d_borrowed = c_borrowed = b_borrowed = m_subtracted = x;
}

Subtractions::Subtractions(int e, int d, int c, int b, int m)
{
  e_borrowed = e;	
  d_borrowed = d;
  c_borrowed = c;
  b_borrowed = b;
  m_subtracted = m;
}

Subtractions::Subtractions(const Subtractions &s)
{
   e_borrowed = s.e_borrowed;
   d_borrowed = s.d_borrowed;
   c_borrowed = s.c_borrowed;
   b_borrowed = s.b_borrowed;
   m_subtracted = s.m_subtracted;
}

Subtractions Subtractions::operator=(const Subtractions &s)
{
   e_borrowed = s.e_borrowed;
   d_borrowed = s.d_borrowed;
   c_borrowed = s.c_borrowed;
   b_borrowed = s.b_borrowed;
   m_subtracted = s.m_subtracted;
}

Subtractions Subtractions::operator=(int x)
{
   e_borrowed = d_borrowed = c_borrowed = b_borrowed = m_subtracted = x;
}

Subtractions Subtractions::operator==(const Subtractions &s)
{
   return((e_borrowed == s.e_borrowed) && (d_borrowed == s.d_borrowed) && (c_borrowed == s.c_borrowed) && (b_borrowed == s.b_borrowed) && (m_subtracted == s.m_subtracted));
}
void Subtractions::clear()
{
   e_borrowed = d_borrowed = c_borrowed = b_borrowed = m_subtracted = 0;
}

std::ostream& operator<<(std::ostream& ostr, const Subtractions &s)
{
    ostr << "Subtracted "<<s.m_subtracted<<" M, ";
    ostr << "Borrowed " <<s.e_borrowed<<" e, " <<s.d_borrowed<<" d, " <<s.c_borrowed<<" c, "<<s.b_borrowed<<" b\n";
    return ostr;
}

std::ofstream& operator<<(std::ofstream& ofstr, const Subtractions &s)
{
    ofstr << "Subtracted "<<s.m_subtracted<<" M, ";
    ofstr << "Borrowed " <<s.e_borrowed<<" e, " <<s.d_borrowed<<" d, "<<s.c_borrowed<<" c, "<<s.b_borrowed<<" b\n";
    return ofstr;
}

