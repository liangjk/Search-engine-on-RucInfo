#include"getinfo.h"
#ifndef regex_h
	#define regex_h
	#include<regex>
	typedef basic_regex<char> regex;
#endif
#ifndef iostream_h
	#define iostream_h
	#include<iostream>
#endif
#include"lock.h"
#include"getpages.h"
#ifndef pthread_h
	#define pthread_h
	#include<pthread.h>
#endif
#ifndef fstream_h
	#define fstream_h
	#include<fstream>
#endif
#ifndef unistd_h
	#define unistd_h
	#include<unistd.h>
#endif

CMutex set_lock;
CMutex queue_lock;
CMutex cnt_lock;

unordered_set<string> visited;
queue<string> url;
int cnt;

ofstream address("address.txt");
#ifdef DEBUG
	ofstream debug("output.txt");
#endif

page::page(string&in_name,string add):address(add)
{
	file.open(in_name);
	while(file.bad())
		file.open(in_name);
	string tmp;
	while(getline(file,tmp))
		html+=tmp;
	while(address[address.length()-1]!='/')address=address.substr(0,address.length()-1);
	address=address.substr(0,address.length()-1);
	return;
}

page::~page()
{
	file.close();
	return;
}

void page::get_url()
{
	regex pattern("a href=\".*?\"");
	string ans;
	string tmp;
	for(sregex_iterator it(html.begin(),html.end(),pattern),end;it!=end;++it)
		{
		tmp=it->str();
		ans="";
		int flag=1;
		if(tmp.find("userfiles")!=string::npos)flag=0;
		if(tmp.length()==9)flag=0;
		else if(tmp[tmp.length()-2]==':')flag=0;
		else
			for(int i=8;i<tmp.length()-1;++i)
				{
				if(tmp[i]=='@'||tmp[i]==' '||tmp[i]=='\n'||tmp[i]==';'||tmp[i]=='#')
					{
					flag=0;
					break;
					}
				if(tmp[i]==':'&&i<tmp.length()-3)
					if(tmp[i+1]=='/'&&tmp[i+2]=='/')
						flag=2;
				ans+=tmp[i];
				}
		if(flag==1)
			{
			if(ans[0]=='/')ans=address+ans;
			else ans=address+'/'+ans;
			}
		if(flag)
			{
			set_lock.Lock();
			if(visited.count(ans))
				{
				set_lock.Unlock();
				continue;
				}
			visited.insert(ans);
			set_lock.Unlock();
			queue_lock.Lock();
			url.push(ans);
			#ifdef DEBUG
				debug<<ans<<endl;
			#endif
			queue_lock.Unlock();
			}
		}
	return;
}

void* crawler(void* args)
{
	cout<<"Thread "<<*((int*)args)<<" is running."<<endl;
	string tmp,path;
	string pattern="info.ruc.edu.cn";
	int now;
	queue_lock.Lock();
	while(true)
		{
		if(url.empty())
			{
			queue_lock.Unlock();
			cout<<"Thread "<<*((int*)args)<<" is sleeping."<<endl;
			sleep(10);
			cout<<"Thread "<<*((int*)args)<<" wakes up."<<endl;
			queue_lock.Lock();
			if(url.empty())break;
			}		
		tmp=url.front();
		url.pop();
		queue_lock.Unlock();
		if(tmp.find(pattern)==string::npos)
			{
			queue_lock.Lock();
			continue;
			}
		cnt_lock.Lock();
		now=++cnt;
		address<<tmp<<endl;
		cnt_lock.Unlock();
		path="./download/"+to_string(now)+".html";
		system(("wget \""+tmp+"\" -q -O "+path).c_str());
		page*webpage=new page(path,tmp);
		webpage->get_url();
		delete webpage;
		queue_lock.Lock();
		}
	queue_lock.Unlock();
	cout<<"Thread "<<*((int*)args)<<" is over."<<endl;
	pthread_exit(NULL);
}
		
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
