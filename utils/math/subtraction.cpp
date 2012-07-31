#include "../basic/subtraction.h"

Subtractions::Subtractions()
{
   int i;
   m = 0;
   for(i=0; i<5; ++i)
   {
        b[i] = 0;
        c[i] = 0;
        d[i] = 0;
        e[i] = 0;
   }
}

Subtractions::Subtractions(int x)
{
   int i;
   m = x;
   for(i=0; i<5; ++i)
   {
        b[i] = x;
        c[i] = x;
        d[i] = x;
        e[i] = x;
   }
}

Subtractions::Subtractions(int f, int e, int d, int c, int b, int m)
{
}

Subtractions::Subtractions(const Subtractions &s)
{
   int i;
   m = s.m;
   for(i=0; i<5; ++i)
   {
        b[i] = s.b[i];
        c[i] = s.c[i];
        d[i] = s.d[i];
        e[i] = s.e[i];
   }
}

Subtractions Subtractions::operator=(const Subtractions &s)
{
   int i;
   m = s.m;
   for(i=0; i<5; ++i)
   {
        b[i] = s.b[i];
        c[i] = s.c[i];
        d[i] = s.d[i];
        e[i] = s.e[i];
   }
}

Subtractions Subtractions::operator=(int x)
{
   int i;
   m = x;
   for(i=0; i<5; ++i)
   {
        b[i] = x;
        c[i] = x;
        d[i] = x;
        e[i] = x;
   }
}

Subtractions Subtractions::operator==(const Subtractions &s)
{
   int i;
   if(m != s.m) return false;
   for(i=0; i<5; ++i)
   {
        if(b[i] != s.b[i] || c[i] != s.c[i] || d[i] != s.d[i] || e[i] != s.e[i]) return false;
   }
  return true;
}
void Subtractions::clear()
{
   int i;
   m = 0;
   for(i=0; i<5; ++i)
   {
        b[i] = 0;
        c[i] = 0;
        d[i] = 0;
        e[i] = 0;
   }
}

std::ostream& operator<<(std::ostream& ostr, const Subtractions &s)
{
    ostr << "Subtracted "<<s.m<<" M, ";
    ostr << "Borrowed "  <<s.e<<" e, " <<s.d<<" d, " <<s.c<<" c, "<<s.b<<" b\n";
    return ostr;
}

std::ofstream& operator<<(std::ofstream& ofstr, const Subtractions &s)
{
    ofstr << "Subtracted "<<s.m<<" M, ";
    ofstr << "Borrowed "  <<s.e<<" e, " <<s.d<<" d, " <<s.c<<" c, "<<s.b<<" b\n";
    return ofstr;
}

