#ifndef getinfo_h
	#define getinfo_h
	#include"getinfo.h"
#endif
#ifndef regex_h
	#define regex_h
	#include<regex>
	typedef basic_regex<char> regex;
#endif
#ifndef iostream_h
	#define iostream_h
	#include<iostream>
#endif
#ifndef thulac_h
	#define thulac_h
	#include"include/thulac.h"
#endif

THULAC cut_tool;

void tool_init()
{
	cut_tool.init("models/",NULL,1,0,0,' ');
	return;
}

page::page(string&in_name,string add):address(add)
{
	file.open(in_name);
	if(file.bad())
		{
		cerr<<"Failed to open file!"<<endl;
		exit(-1);
		}
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

void page::get_title()
{
	regex pattern("<title>.+?</title>");
	smatch result;
	if(!regex_search(html,result,pattern))
		title="No title!";
	else
		{
		string tmp=result.str();
		int t=tmp.find("</title>");
		title="";
		for(int i=7;i<t;++i)title+=tmp[i];
		}
	cut_tool.cut(title,cut_title);
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
		if(flag==2)url.insert(ans);
		else if(flag==1)
			{
			if(ans[0]=='/')url.insert(address+ans);
			else url.insert(address+'/'+ans);
			}
		}
	return;
}

void page::get_content()
{
	int t=html.find("<div class=\"content\">");
	if(t==string::npos)content="No content!\n";
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
			content+=html[i];
			flag=1;
			}
		t=html.find("<div class=\"content\">",t+1);
		}
	cut_tool.cut(content,cut_content);
	return;
}

void page::get_info()
{
get_title();
get_content();
get_url();
return;
}

void page::output(ofstream&out)
{
	out<<"标题："<<title<<endl;
	out<<endl<<"切词结果：";
	for(vector<pair<string,string> >::iterator it=cut_title.begin();it!=cut_title.end();++it)
		if(it->first!="\n"&&it->first!=" ")out<<it->first<<'/';
	out<<endl<<endl<<"正文："<<endl<<content<<endl<<"切词结果："<<endl;
	for(vector<pair<string,string> >::iterator it=cut_content.begin();it!=cut_content.end();++it)
		if(it->first!="\n"&&it->first!=" ")out<<it->first<<'/';
	out<<endl<<endl<<"URL："<<endl;
	for(set<string>::iterator it=url.begin();it!=url.end();++it)
		out<<*it<<endl;
	return;
}

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
