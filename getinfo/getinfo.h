#ifndef string_h
	#define string_h
	#include<string>
#endif
#ifndef iostream_h
	#define iostream_h
	#include<iostream>
#endif
#ifndef set_h
	#define set_h
	#include<set>
#endif
#ifndef vector_h
	#define vector_h
	#include<vector>
#endif
#ifndef algorithm_h
	#define algorithm_h
	#include<algorithm>
#endif
#ifndef fstream_h
	#define fstream_h
	#include<fstream>
#endif

using namespace std;

class page{
	private:
		ifstream file;
		string address;
		string html;
		string title;
		string content;
		set<string> url;
		vector<pair<string,string> >cut_title;
		vector<pair<string,string> >cut_content;
	public:
		page(string&,string add="http://info.ruc.edu.cn/");
		void get_title();
		void get_content();
		void get_url();
		void get_info();
		void output(ofstream&);
		~page();
};
		
void tool_init();
