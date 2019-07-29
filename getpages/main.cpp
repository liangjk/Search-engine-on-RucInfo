#include"getpages.h"
#ifndef pthread_h
	#define pthread_h
	#include<pthread.h>
#endif
#ifndef iostream_h
	#define iostream_h
	#include<iostream>
#endif

int main()
{
	string homepage="http://info.ruc.edu.cn/index.php";
	extern queue<string> url;
	url.push(homepage);
	extern unordered_set<string> visited;
	visited.insert(homepage);
	int num=5;
	int index[num];
	pthread_t threads[num];
	for(int i=0;i<num;++i)
		{
		index[i]=i;
		int ret=pthread_create(&threads[i],NULL,crawler,(void*)&index[i]);
		if (ret != 0)
			cerr << "pthread_create error: error_code=" << ret << endl;
		}
	pthread_exit(NULL);
}	
