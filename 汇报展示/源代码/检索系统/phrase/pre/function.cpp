#include"pre.h"
#include"hashtable.h"
#include<regex>
typedef basic_regex<char> regex;
#include<iostream>
#include<unordered_map>
#include"include/thulac.h"
#include<set>
#include<fstream>

int cnt_node;
int cnt_tnode;

THULAC cut_tool;

void tool_init()
{
	cut_tool.init("models/",NULL,1,0,0,' ');
	return;
}

void page::open(string in_name,string&add)
{
	address=add;
	file.open(in_name);
	if(file.bad())
		{
		cerr<<"Failed to open file!"<<endl;
		exit(-1);
		}
	string tmp;
	html="";
	while(getline(file,tmp))
		html+=tmp;
	return;
}

void page::close()
{
	file.close();
	cut_title.clear();
	cut_content.clear();
	return;
}

void page::get_title()
{
	regex pattern("<title>.+?</title>");
	smatch result;
	if(!regex_search(html,result,pattern))
		title="";
	else
		{
		string tmp=result.str();
		int t=tmp.find("</title>");
		title="";
		for(int i=7;i<t;++i)
			title+=tmp[i];
		}
	cut_tool.cut(title,cut_title);
	return;
}

void page::get_content()
{
	int t=html.find("<div class=\"content\">");
	content="";
	while(t!=string::npos)
		{
		int flag=0;
		int cnt=1;
		for(int i=t+21;cnt;++i)
			{
			if(html[i]=='<')
				{
				if(flag)
					{
					content+='\n';
					flag=0;
					}
				if(html[i+1]=='d')++cnt;
				if(html[i+1]=='/'&&html[i+2]=='d')--cnt;
				if(html[i+1]=='!')
					{
					while(html[i]!='>'||html[i-1]!='-')++i;
					continue;
					}
				int kh=1;
				while(kh)
					{
					++i;
					if(html[i]=='<')++kh;
					if(html[i]=='>')--kh;
					}
				continue;
				}
			// if(html[i]=='&')
				// {
				// content+=' ';
				// int zy=0;
				// while(html[i]!=';'&&zy<4)
					// {
					// ++i;
					// ++zy;
					// if(html[i]=='&')
						// {
						// if(zy==1)
							// {
							// content+="& ";
							// zy=4;
							// }
						// else zy=0;
						// }
					// if(html[i]=='<')
						// {
						// --i;
						// break;
						// }
					// }
				// if(html[i+1]==';')++i;
				// continue;
				// }
			if(html[i]=='\t')continue;
			// if(html[i]=='$')
				// {
				// content+=' ';
				// do
					// ++i;
				// while(html[i]!='$');
				// continue;
				// }
			if(html[i]=='-')content+=' ';
			else content+=html[i];
			flag=1;
			}
		t=html.find("<div class=\"content\">",t+1);
		}
	cut_tool.cut(content,cut_content);
	return;
}

unordered_map<string,word> index;
extern set<string> stop;
extern int flag;
ofstream page_data("page_data.txt");

void page::insert()
{
	page_data<<address<<endl<<title<<endl;
	vector<pair<string,string> >::iterator it;
	int pos=0;
	for(it=cut_title.begin();it!=cut_title.end();++it)
		{
		++pos;
		string t=it->first;
		if(t.length()==0)continue;
		if(t[0]=='\n')continue;
		if(t[0]=='-')continue;
		if(t[0]==' ')continue;
		if(t[0]=='.')continue;
		if(index.find(t)==index.end())
			{
			index[t]=word();
			index[t].add(flag,pos);
			}
		else index[t].add(flag,pos);
		}
	++pos;
	for(it=cut_content.begin();it!=cut_content.end();++it)
		{
		++pos;
		string t=it->first;
		if(t.length()==0)continue;
		if(t[0]=='\n')continue;
		if(t[0]==' ')continue;
		if(t[0]=='.')continue;
		if(index.find(t)==index.end())
			{
			index[t]=word();
			index[t].add(flag,pos);
			}
		else index[t].add(flag,pos);
		}
}

void word::add(int id,int pos)
{
	if(begin==0)
		{
		begin=back=new node(id,pos);
		++cnt_node;
		}
	else if(back->id==id)back->add(pos);
	else
		{
		back=back->next=new node(id,pos);
		++cnt_node;
		}
	return;
}

void output(){
	ofstream output;
	output.open("index_data.txt");
	for(unordered_map<string,word>::iterator it=index.begin();it!=index.end();++it)
		{
		output<<it->first<<endl;
		it->second.output(output);
		}
	output.close();
	return;
}

void word::output(ofstream&out)
{
for(node*it=begin;it!=back;it=it->next)it->output(out);
back->output(out);
out<<"-1\n";
return;
}

void node::output(ofstream&out)
{
out<<id<<endl;
for(list<int>::iterator it=pos.begin();it!=pos.end();++it)
	out<<*it<<endl;
out<<"-1\n";
return;
}
