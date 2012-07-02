#include "../basic/subtraction.h"

Subtractions::Subtractions()
{
   c_borrowed = b_borrowed = m_subtracted = 0;
}

Subtractions::Subtractions(int x)
{
   c_borrowed = b_borrowed = m_subtracted = x;
}

Subtractions::Subtractions(int c, int b, int m)
{
  c_borrowed = c;
  b_borrowed = b;
  m_subtracted = m;
}

Subtractions::Subtractions(const Subtractions &s)
{
   c_borrowed = s.c_borrowed;
   b_borrowed = s.b_borrowed;
   m_subtracted = s.m_subtracted;
}

Subtractions Subtractions::operator=(const Subtractions &s)
{
   c_borrowed = s.c_borrowed;
   b_borrowed = s.b_borrowed;
   m_subtracted = s.m_subtracted;
}

Subtractions Subtractions::operator=(int x)
{
   c_borrowed = b_borrowed = m_subtracted = x;
}

Subtractions Subtractions::operator==(const Subtractions &s)
{
   return((c_borrowed == s.c_borrowed) && (b_borrowed == s.b_borrowed) && (m_subtracted == s.m_subtracted));
}
void Subtractions::clear()
{
   c_borrowed = b_borrowed = m_subtracted = 0;
}

std::ostream& operator<<(std::ostream& ostr, const Subtractions &s)
{
    ostr << "Subtracted "<<s.m_subtracted<<" M, ";
    ostr << "Borrowed "<<s.c_borrowed<<" c, "<<s.b_borrowed<<" b\n";
    return ostr;
}

std::ofstream& operator<<(std::ofstream& ofstr, const Subtractions &s)
{
    ofstr << "Subtracted "<<s.m_subtracted<<" M, ";
    ofstr << "Borrowed "<<s.c_borrowed<<" c, "<<s.b_borrowed<<" b\n";
    return ofstr;
}

