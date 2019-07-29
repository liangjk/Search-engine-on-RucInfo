#ifndef engine_h
#define engine_h

#include<cmath>
#include<iostream>
#include<list>
#include<string>

#define page_number 5847

using namespace std;

void init();
bool query(string&);
void output(ostream&);
void blank(ostream&);

class word;

class node{
	private:
		int id;
		list<int> pos;
		node(int t):id(t){}
	public:
		node*next;
		void add(int p){pos.push_back(p);return;}
	friend class word;
	friend bool query(string&);
};

class word{
	private:
		node*begin=0;
	public:
		node*back=0;
		word(int id){begin=back=new node(id);return;}
		word(){}
		void insert(int id){back=back->next=new node(id);return;}
	friend bool query(string&);
};

#endif