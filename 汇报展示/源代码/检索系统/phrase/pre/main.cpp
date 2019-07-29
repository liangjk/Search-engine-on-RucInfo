#include"pre.h"
#include<set>
#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include"hashtable.h"

set<string> stop;
int flag;

int main()
{
string tmp;
ifstream input;
input.open("stop.txt");
while(getline(input,tmp))stop.insert(tmp);
input.close();
input.open("address.txt");
page webpage;
tool_init();
for(flag=0;flag<page_number;++flag)
	{
	getline(input,tmp);
	webpage.open("./download/"+to_string(flag+1)+".html",tmp);
	webpage.get_title();
	webpage.get_content();
	webpage.insert();
	webpage.close();
	cout<<flag<<endl;
	}
output();
return 0;
}

