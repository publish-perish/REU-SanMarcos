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

void Subtractions::clear()
{
   c_borrowed = b_borrowed = m_subtracted = 0;
}

std::ostream& operator<<(std::ostream& ostr, const Subtractions &s)
{
    ostr << "M subtracted "<<s.m_subtracted<<" times. \n";
    ostr << "Borrowed from c "<<s.c_borrowed<<" times. \n";
    ostr << "Borrowed from b "<<s.b_borrowed<<" times. \n";
    return ostr;
}

std::ofstream& operator<<(std::ofstream& ofstr, const Subtractions &s)
{
    ofstr << "M subtracted "<<s.m_subtracted<<" times. \n";
    ofstr << "Borrowed from c "<<s.c_borrowed<<" times. \n";
    ofstr << "Borrowed from b "<<s.b_borrowed<<" times. \n";
    return ofstr;
}

