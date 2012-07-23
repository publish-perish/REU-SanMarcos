#include "../basic/subtraction.h"

Subtractions::Subtractions()
{
   f_borrowed = e_borrowed = d_borrowed = c_borrowed = b_borrowed = m_subtracted = 0;
}

Subtractions::Subtractions(int x)
{
   f_borrowed = e_borrowed = d_borrowed = c_borrowed = b_borrowed = m_subtracted = x;
}

Subtractions::Subtractions(int f, int e, int d, int c, int b, int m)
{
  f_borrowed = f;
  e_borrowed = e;	
  d_borrowed = d;
  c_borrowed = c;
  b_borrowed = b;
  m_subtracted = m;
}

Subtractions::Subtractions(const Subtractions &s)
{
	f_borrowed = s.f_borrowed;
   e_borrowed = s.e_borrowed;
   d_borrowed = s.d_borrowed;
   c_borrowed = s.c_borrowed;
   b_borrowed = s.b_borrowed;
   m_subtracted = s.m_subtracted;
}

Subtractions Subtractions::operator=(const Subtractions &s)
{
	f_borrowed = s.f_borrowed;
   e_borrowed = s.e_borrowed;
   d_borrowed = s.d_borrowed;
   c_borrowed = s.c_borrowed;
   b_borrowed = s.b_borrowed;
   m_subtracted = s.m_subtracted;
}

Subtractions Subtractions::operator=(int x)
{
   f_borrowed = e_borrowed = d_borrowed = c_borrowed = b_borrowed = m_subtracted = x;
}

Subtractions Subtractions::operator==(const Subtractions &s)
{
   return((f_borrowed == s.f_borrowed) && (e_borrowed == s.e_borrowed) && (d_borrowed == s.d_borrowed) && (c_borrowed == s.c_borrowed) && (b_borrowed == s.b_borrowed) && (m_subtracted == s.m_subtracted));
}
void Subtractions::clear()
{
  f_borrowed = e_borrowed = d_borrowed = c_borrowed = b_borrowed = m_subtracted = 0;
}

std::ostream& operator<<(std::ostream& ostr, const Subtractions &s)
{
    ostr << "Subtracted "<<s.m_subtracted<<" M, ";
    ostr << "Borrowed "  <<s.f_borrowed<<" f, "<<s.e_borrowed<<" e, " <<s.d_borrowed<<" d, " <<s.c_borrowed<<" c, "<<s.b_borrowed<<" b\n";
    return ostr;
}

std::ofstream& operator<<(std::ofstream& ofstr, const Subtractions &s)
{
    ofstr << "Subtracted "<<s.m_subtracted<<" M, ";
    ofstr << "Borrowed "  <<s.f_borrowed<<" f, "<<s.e_borrowed<<" e, " <<s.d_borrowed<<" d, " <<s.c_borrowed<<" c, "<<s.b_borrowed<<" b\n";
    return ofstr;
}

