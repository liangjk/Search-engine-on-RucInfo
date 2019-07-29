#ifndef hashtable_h
#define hashtable_h

#include"pre.h"
#include<cstring>
#define Mod 9999991

template<typename T>
class hashtable;

template<typename T>
class tablenode{
	private:
		string key;
		T data;
		tablenode* next;
		tablenode():next(0){};
		tablenode(string&str):key(str),next(0){}
		~tablenode(){if(next)delete(next);return;}
	friend class hashtable<T>;
};

int hashstr(string&);

template<typename T>
class hashtable{
	private:
		tablenode<T>*bucket[Mod];
	public:
		hashtable(){memset(bucket,0,sizeof(bucket));return;}
		bool has(string&) const;
		T& find(string&);
		void add(string&);
		void output(ofstream&);
		~hashtable();
};

template<typename T>
bool hashtable<T>::has(string&key) const
{
	int buk_num=hashstr(key)%Mod;
	for(tablenode<T>*now=bucket[buk_num];now;now=now->next)
		if(now->key==key)return true;
	return false;
}

template<typename T>
T& hashtable<T>::find(string&key)
{
	int buk_num=hashstr(key)%Mod;
	for(tablenode<T>*now=bucket[buk_num];now;now=now->next)
		if(now->key==key)return now->data;
	cerr<<"Not found!!!"<<endl;
	exit(-1);
}

template<typename T>
void hashtable<T>::add(string&key)
{
	int buk_num=hashstr(key)%Mod;
	if(bucket[buk_num])
		{
		tablenode<T>*now=bucket[buk_num];
		while(now->next)now=now->next;
		now->next=new tablenode<T>(key);
		}
	else
		bucket[buk_num]=new tablenode<T>(key);
	return;
}

template<typename T>
void hashtable<T>::output(ofstream&out)
{
	for(int i=0;i<Mod;++i)
		for(tablenode<T>*now=bucket[i];now;now=now->next)
			{
			out<<now->key<<endl;
			now->data.output(out);
			}
	return;
}

template<typename T>
hashtable<T>::~hashtable()
{
	for(int i=0;i<Mod;++i)
		if(bucket[i])delete(bucket[i]);
	return;
}

#endif