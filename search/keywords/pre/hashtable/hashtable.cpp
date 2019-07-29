#include"hashtable.h"

int hashstr(string&str)
{
	long long ans=0;
	for(int i=0;i<str.length();++i)
		{
		ans*=997;
		ans%=(long long)Mod;
		ans+=(unsigned char)str[i];
		ans%=(long long)Mod;
		}
	return int(ans);
}