#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
struct TrieNode
{
	vector<TrieNode*> next;
	bool end;
	int cnt;
	TrieNode():end(0),cnt(0){}
};
TrieNode *root=new TrieNode;
map<string,unsigned int> table;
void build(string &str)
{
	TrieNode *p=root;
	for(unsigned int x:str)
	{
		if(x+1>p->next.size()) p->next.resize(x+1);
		if(p->next[x]==NULL)
		{
			TrieNode* s=new TrieNode();
			p->next[x]=s;
		}
		p=p->next[x];
	}
	p->end=true;
	p->cnt++;
}
void searchAllword(TrieNode *p,string word)
{
	if(p->end==true) table[word]=p->cnt;
	for(unsigned int i=0;i<p->next.size();++i)
	{
		TrieNode *xp=p->next[i];
		if(xp)
			searchAllword(xp,word+(char)i);
	}
}
int search(string &str)
{
	TrieNode *p=root;
	for(unsigned int x:str)
	{
		if(x>=p->next.size()||p->next[x]==NULL)
			return 0;
		else p=p->next[x];
	}
	return p->cnt;
}
void disp()
{
	for(auto x:table)
		cout<<x.first<<" "<<x.second<<endl;
}
int main(int argc, char const *argv[])
{
	int n;
	string str;
	cout<<"input word number that you want to creat: ";
	cin>>n;
	while(n--)
	{
		cin>>str;
		build(str);
	}
	cout<<"input word number that you want to search: ";
	cin>>n;
	while(n--)
	{
		cin>>str;
		cout<<str<<" : "<<search(str)<<endl;
	}
	searchAllword(root,string());
	cout<<"all word record\n";
	disp();
	return 0;
}
