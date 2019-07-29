#ifndef pre_h
#define pre_h

#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<list>

using namespace std;

void output();

class page{
	private:
		ifstream file;
		string address;
		string html;
		string title;
		string content;
		vector<pair<string,string> >cut_title;
		vector<pair<string,string> >cut_content;
	public:
		void open(string ,string&);
		void get_title();
		void get_content();
		void insert();
		void close();
};

class word;

class node{
	private:
		int id;
		list<int> pos;
	public:
		node*next;
		node(int a,int p):id(a){pos.push_back(p);return;}
		void add(int p){pos.push_back(p);return;}
		void output(ofstream&);
	friend class word;
};
		
class word{
	private:
		node*begin=0;
		node*back=0;
	public:
		void add(int id,int pos);
		void output(ofstream&);
};

void tool_init();

#define page_number 5847
#endif