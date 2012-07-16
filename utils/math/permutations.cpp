#include "../basic/permutations.h"
// 4 3 4
int Table::makeITable()
{
ofstream out;
out.open("./permutationtables/ITable.txt");
Isize = 0;
T5 t;
if(out.is_open())
{
for(int a =5; a < 67; a++)
{
	for(int b =a+1; b < 68; b++)
	{
		for(int c =b+1; c < 69; c++)
		{
			for(int d =c+1; d < 70; d++)
			{
			t[0] =0;
			t[1] =a;
			t[2] =b;
			t[3] =c;
			t[4] =d;			
			out << t;
			Isize++;
			}
		}

	}
}
}
out << endl; out.close();
return Isize;
}
int Table::makeSTable()
{
ofstream out;
out.open("./permutationtables/STable.txt");
Ssize = 0;
T5 t;
if(out.is_open())
{
//for(int a =4; a < 35; a++)
//{
	//for(int b =a+1; b < 36; b++)
	//{
		//for(int c = b+1; c < 37; c++)
		//{
		t[0] =0;
		t[1] =1;
		t[2] =2;
		t[3] =3;
		t[4] =4;
		out <<  t;
		Ssize++;
		//}
	//}

//}
}
out << endl; out.close();
return Ssize;
}

int Table::makeTTable()
{
T5 t;
ofstream out;
out.open("./permutationtables/TTable.txt");
Tsize = 0;
if(out.is_open())
{
for(int a =6; a < 66; a++)
{
	for(int b =a+2; b < 67; b++)
	{
		for(int c =b+1; c < 68; c++)
		{
			for(int d =c+1; d < 69; d++)
			{
				for(int e =d+1; e < 70; e++)
				{
				t[0] =a;
				t[1] =b;
				t[2] =c;
				t[3] =d;
				t[4] =e;	
				out << t;
				Tsize++;
				}
			}
		}
	}
}
}
return Tsize;
} 

/*
int Table::makeLTable()
{
ofstream out;
out.open("./permutationtables/LTable.txt");
Lsize = 0;
if(out.is_open())
{
//for(int a =0; a < 44; a++)
//{
	//for(int b =a+2; b < 25; b++)
	//{
		//for(int c =b+1; c < 29; c++)
		//{
			//for(int d =c+1; c < 30; c++)
			//{
			out << boost::tuples::set_delimiter(',') << T(3, 4, 0, 0) << ' ';
			Lsize++;
			//}
		//}
	//}
//}
}
return Lsize;
}
*/
