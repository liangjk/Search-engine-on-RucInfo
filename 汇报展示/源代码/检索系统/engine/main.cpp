#include<iostream>
#include<fstream>
#include<ctime>
#include<vector>
#include<algorithm>
#include<windows.h>
#include"engine.h"

vector<pair<pair<double,double>,int> >result;
clock_t s_start,s_end;

int main()
{
string qry,tmp;
ifstream in;
ofstream out;
init();
while(true)
	{
	do
		{
		Sleep(100);
		in.open("input.in");
		}
	while(!in);
	cout<<"Querying."<<endl;
	getline(in,qry);
	in.close();
	bool flag=query(qry);
	#ifdef DEBUG
		out.open("output.html");
	#else
		out.open("../../htdocs/result.html");
	#endif
	if(flag)
		{
		sort(result.begin(),result.end());
		output(out);
		result.clear();
		}
	else blank(out);
	out.close();
	Sleep(1500);
	}
return 0;
}
