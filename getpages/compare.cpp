#include<unordered_set>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

ifstream input("output.txt");
unordered_set<string> myset;

int main()
{
string tmp;
while(getline(input,tmp))
	{
	if(myset.count(tmp))cout<<"wrong!"<<endl;
	else 
		{
		myset.insert(tmp);
		//cout<<"ok!"<<endl;
		}
	}
cout<<"Ok!"<<endl;
return 0;
}
