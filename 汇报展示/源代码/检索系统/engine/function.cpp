#include"engine.h"
#include"include/thulac.h"
#include<fstream>
#include<unordered_map>
#include<algorithm>
#include<vector>
#include<cmath>
#include<ctime>

THULAC cut_tool;

unordered_map<string,word> index;
vector<pair<string,string> > page_data;

void init()
{
	cut_tool.init("models/",NULL,1,0,0,' ');
	string tmp1;
	string tmp2;
	ifstream input;
	input.open("page_data.txt");
	for(int i=0;i<page_number;++i)
		{
		getline(input,tmp1);
		getline(input,tmp2);
		page_data.push_back(make_pair(tmp1,tmp2));
		}
	input.close();
	input.open("index_data.txt");
	while(getline(input,tmp1))
		{
		long d,t;
		input>>d;
		word&now=index[tmp1]=word(d);
		while(input>>d>>t,~d)
			now.insert(d,t);
		getline(input,tmp1);
		}
	input.close();	
	return;
}

void word::insert(int id,int t)
{
	if(back)back=back->next=new node(id,t);
	else begin=back=new node(id,t);
	return;
}

extern vector<pair<pair<double,double>,int> >result;
extern clock_t s_start,s_end;

bool query(string&input)
{
	s_start=clock();
	vector<pair<double,node*> >pointer;
	vector<pair<string,int> >query_vector;
	vector<pair<string,string> >cut_result;
	cut_tool.cut(input,cut_result);
	for(vector<pair<string,string> >::iterator cut_it=cut_result.begin();cut_it!=cut_result.end();++cut_it)
		{
		string tmp=cut_it->first;
		if(tmp[0]=='\n')continue;
		if(tmp[0]==' ')continue;
		if(tmp[0]=='\t')continue;
		if(tmp[0]=='.')continue;
		if(tmp[0]=='-')continue;
		// cout<<tmp<<endl<<1<<endl;
		int flag=1;
		for(vector<pair<string,int> >::iterator query_it=query_vector.begin();query_it!=query_vector.end();++query_it)
			if(query_it->first==tmp)
				{
				++query_it->second;
				flag=0;
				break;
				}
		if(flag)query_vector.push_back(make_pair(tmp,1));
		}
	int size=0;
	for(vector<pair<string,int> >::iterator query_it=query_vector.begin();query_it!=query_vector.end();++query_it)	
		{
		if(index.find(query_it->first)==index.end())
			{
			s_start=s_end=clock();
			return true;
			}
		pointer.push_back(make_pair(index[query_it->first].w,index[query_it->first].begin));
		++size;
		}
	if(size==0)return false;
	while(true)
		{
		if(pointer[0].second==0)break;
		int min=pointer[0].second->id;
		int cnt=1;
		int flag=0;
		for(int i=1;i<size;++i)
			{
			if(pointer[i].second==0)
				{
				flag=1;
				break;
				}
			if(pointer[i].second->id<min)
				{
				min=pointer[i].second->id;
				cnt=1;
				}
			else if(pointer[i].second->id==min)++cnt;
			}
		if(flag)break;
		if(cnt==size)
			{
			double inner=0,qlen=0,dlen=0,qry,doc;
			for(int i=0;i<size;++i)
				{
				qry=pointer[i].first*(1+log10(query_vector[i].second));
				doc=pointer[i].first*pointer[i].second->w;
				inner+=qry*doc;
				qlen+=qry*qry;
				dlen+=doc*doc;
				pointer[i].second=pointer[i].second->next;
				}
			result.push_back(make_pair(make_pair(acos(inner/sqrt(qlen*dlen)),100.0/inner),min));
			}
		else
			for(int i=0;i<size;++i)
				if(pointer[i].second->id==min)pointer[i].second=pointer[i].second->next;
		}
	s_end=clock();
	return true;
}

void output(ostream&out)
{
	int num=result.size();
	out<<"<!DOCTYPE html>\n<html>\n<head>\n\t<meta http-equiv = \"content-type\" content = \"text/html; charset = utf-8\"/>\n\t<meta name=\"author\" content=\"Search Engine by 梁钧凯\"/>\n\t<title>搜索结果</title>\n\t<link rel=\"shortcut icon\" href=\"index/logo.ico\" >\n</head>\n<body background=\"index/result_background.jpg\">\n\t<h1 style=\"margin-left:250px;margin-top:50px;font-size:50px\"><img src=\"index/logo.png\" width=\"40\" height=\"40\">搜索结果</h1>\n\t<p style=\"padding-left:250px\">共为您找到";
	out<<num<<"个相关网页，用时"<<s_end-s_start<<"ms。</p>\n";
	if(num>10)num=10;
	for(int i=0;i<num;++i)
		{
		out<<"\t<p style=\"padding-left:250px;font-size:25px\">"<<i+1<<"、<a href=\""<<page_data[result[i].second].first<<"\">"<<page_data[result[i].second].second<<"</a></p>\n";
		out<<"\t<p style=\"padding-left:250px;font-size:18px\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"<<page_data[result[i].second].first<<"</p>\n\t<br/>\n";
		}
	for(;num<5;++num)
		{
		out<<"\t<p style=\"padding-left:250px;font-size:25px\"></p>\n";
		out<<"\t<p style=\"padding-left:250px;font-size:18px\"></p>\n\t<br/>\n";
		}
	out<<"\t<p style=\"text-align:center\"><a href=\"index.html\"><button type=\"button\" style=\"font-size:20px\">回到搜索页面</button></a></p>\n</body>\n</html>\n";
	return;
}

void blank(ostream&out)
{
	out<<"<!DOCTYPE html>\n<html>\n<head>\n\t<meta http-equiv = \"content-type\" content = \"text/html; charset = utf-8\"/>\n\t<meta name=\"author\" content=\"Search Engine by 梁钧凯\"/>\n\t<title>搜索结果</title>\n\t<link rel=\"shortcut icon\" href=\"index/logo.ico\" >\n</head>\n<body background=\"index/result_background.jpg\">\n\t<h1 style=\"margin-left:250px;margin-top:50px;font-size:50px\"><img src=\"index/logo.png\" width=\"40\" height=\"40\">搜索内容不能为空！</h1>\n";
	for(int i=1;i<=5;++i)
		{
		out<<"\t<p style=\"padding-left:250px;font-size:25px\"></p>\n";
		out<<"\t<p style=\"padding-left:250px;font-size:18px\"></p>\n\t<br/>\n";
		}
	out<<"\t<p style=\"text-align:center\"><a href=\"index.html\"><button type=\"button\" style=\"font-size:20px\">回到搜索页面</button></a></p>\n</body>\n</html>\n";
	return;
}