#ifndef getinfo_h
	#define getinfo_h
	#include"getinfo.h"
#endif
#ifndef iostream_h
	#define iostream_h
	#include<iostream>
#endif
#ifndef fstream_h
	#define fstream_h
	#include<fstream>
#endif
#ifndef string_h
	#define string_h
	#include<string>
#endif

int main()
{
	tool_init();
	string in_name("1.html");
	page webpage(in_name);
	webpage.get_info();
	ofstream out_name("output.txt");
	webpage.output(out_name);
	return 0;
}
