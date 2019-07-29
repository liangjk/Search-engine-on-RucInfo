#ifndef pre_h
#define pre_h

#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>

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
		int t;
	public:
		node*next;
		node(int a=0):id(a),t(1),next(0){};
		void output(ofstream&);
	friend class word;
};
		

class word{
	private:
		node*begin=0;
		node*back=0;
		int d=0;
	public:
		void add(int);
		void output(ofstream&);
};

void tool_init();

#define page_number 5847
#endif