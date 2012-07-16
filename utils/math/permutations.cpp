#include "../basic/permutations.h"
// 5 3 4
int Table::makeITable()
{
ofstream out;
out.open("./permutationtables/ITable.txt");
Isize = 0;
T5 t;
if(out.is_open())
{
for(int a =4; a < 42; a++)
{
	for(int b =a+1; b < 43; b++)
	{
		for(int c =b+1; c < 44; c++)
		{
			//for(int d =c+1; d < 70; d++)
			//{
			t[0] =0;
			t[1] =3;
			t[2] =a;
			t[3] =b;
			t[4] =c;			
			out << t;
			Isize++;
			//}
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
		t[3] =0;
		t[4] =0;
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
for(int a =5; a < 41; a++)
{
	for(int b =a+1; b < 42; b++)
	{
		for(int c =b+1; c < 43; c++)
		{
			for(int d =c+1; d < 44; d++)
			{
				//for(int e =d+1; e < 70; e++)
				//{
				t[0] =a;
				t[1] =b;
				t[2] =c;
				t[3] =d;
				t[4] =0;	
				out << t;
				Tsize++;
				//}
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
