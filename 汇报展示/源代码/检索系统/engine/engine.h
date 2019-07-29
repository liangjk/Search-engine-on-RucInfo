#ifndef engine_h
#define engine_h

#include<cmath>
#include<iostream>
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
		double w;
		node(int d,int t):id(d),next(0){w=1+log10(t);return;}
	public:
		node*next;
	friend class word;
	friend bool query(string&);
};

class word{
	private:
		node*begin=0;
		node*back=0;
		double w;
	public:
		word(int d=0){w=log10(page_number/double(d));return;}
		void insert(int,int);
	friend bool query(string&);
};

#endif