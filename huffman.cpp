#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <stack>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <fstream>
using namespace std;
#define MaxBitL 256;
struct HuffmanTreeNode
{
    unsigned char leafchar;
    bool bit;
    int weight;
    HuffmanTreeNode *left,*right;
    HuffmanTreeNode(unsigned char c,unsigned int w,HuffmanTreeNode *l,HuffmanTreeNode *r):leafchar(c),bit(0),weight(w),left(l),right(r){}
};
struct cmp
{
    bool operator ()(HuffmanTreeNode* &a,HuffmanTreeNode* &b) const
    {
        return a->weight>b->weight;
    }
};
unordered_map<unsigned char,unsigned int> freqTable;//字符频率统计表
unordered_map<unsigned char,string> dictTable;//字符到二进制序列的映射
map<string,unsigned char> RedictTable;//二进制序列到字符的映射
unordered_map<string,char> codeToCharTable;//二进制到字符（压缩）
unordered_map<char,string> charToCodeTable;//二进制到字符（解压）
priority_queue<HuffmanTreeNode*,vector<HuffmanTreeNode*>,cmp> pq;//优先队列
void ComputeFreqTable(const string &text)
{
	for(unsigned char c:text)
		freqTable[c]++;
	cout<<"ComputeFreqTable Finished"<<endl;
}
HuffmanTreeNode * CreatHuffmanTree()
{
    HuffmanTreeNode *root=NULL;
    for(auto &x:freqTable)
    {
    	HuffmanTreeNode *node=new HuffmanTreeNode(x.first,x.second,NULL,NULL);
    	pq.push(node);
    }
    while(!pq.empty())
    {
        HuffmanTreeNode *first=pq.top();
        pq.pop();
        if(pq.empty())
        {
            root=first;
            break;
        }
        HuffmanTreeNode *second=pq.top();
        pq.pop();
        if(first->weight>second->weight) swap(first,second);
        HuffmanTreeNode *s=new HuffmanTreeNode('\0',first->weight+second->weight,first,second);
        s->right->bit=1;
        pq.push(s);
    }
    cout<<"CreatHuffmanTree Finished"<<endl;
    return root;
}
void dictHelp(HuffmanTreeNode *r,string &bin)
{
	if(r)
	{
		bin.push_back(r->bit+'0');
		if(!r->left&&!r->right)
		{
			dictTable[r->leafchar]=bin;
			RedictTable[bin]=r->leafchar;
		}
		dictHelp(r->left,bin);
		dictHelp(r->right,bin);
		bin.pop_back();
	}
}
void ComputeDictTable(HuffmanTreeNode *r)
{
	string bin;
	dictHelp(r,bin);
	cout<<"ComputeDictTable Finished"<<endl;
}
string enCode(const string &Text)
{
	string code;
	for(auto &x:Text)
	{
		code+=dictTable[x];
	}
	cout<<"encode Finished"<<endl;
	return code;
}
string ConvertDecToBinStr(int n,int bitnum)
{
    string bin;
    while(n)
    {
        bin+='0'+n%2;
        n/=2;
    }
    string tail(bitnum-bin.size(),'0');
    return bin+tail;
}
void CreatcodeToCharTable()
{
	for(int i=0;i<256;++i)
	{
		string b=ConvertDecToBinStr(i,8);
		charToCodeTable[i+'\0']=b;
		codeToCharTable[b]=i+'\0';
	}
	cout<<"CreatcodeToCharTable Finished"<<endl;
}
string compressCode(const string &code)
{
	string compressText,codetemp=code;
	int len=0;
	cout<<"try! : ";
	while(!codetemp.empty())
    {
    	//cout<<".";
        string temp;
        if(codetemp.size()>=8)
        {
            temp=codetemp.substr(0,8);
            codetemp=codetemp.substr(8,codetemp.size()-8);
        }
        else 
        {
            len=8-codetemp.size();
            string tail(len,'0');
            codetemp+=tail;
            compressText+=codeToCharTable[codetemp];
            break;
        }
        compressText+=codeToCharTable[temp];
    }
    char head='0'+len;
    compressText=head+compressText;
    cout<<"compressCode Finished"<<endl;
    return compressText;
}
string decompressCode(const string &compressText)
{
	string comTexttemp=compressText,newcode;
	int len=comTexttemp[0]-'0';
	comTexttemp=comTexttemp.substr(1,compressText.size()-1);
	for(unsigned char x:comTexttemp)
	{
		newcode+=charToCodeTable[x-'\0'];
	}
	cout<<"decompressCode Finished"<<endl;
	return newcode.substr(0,newcode.size()-len);
}
string ConvertCodeToText(const string &code)
{
	string newtext,bin;
	for(unsigned char x:code)
	{
		bin+=x;
		auto it=RedictTable.find(bin);
		if(it!=RedictTable.end())
		{
			newtext+=it->second;
			bin.clear();
		}
	}
	cout<<"ConvertCodeToText Finished"<<endl;
	return newtext;
}
void disStr(const string &Text)
{
	cout<<"------------------------"<<endl;
    cout<<Text<<endl;
    cout<<"------------------------"<<endl;
}
void WriteTextByRand(string &Text,unsigned int size)
{
    srand((unsigned)time(NULL));
    for(unsigned int i=0;i<size;++i)
    {
        int r=rand()%(126-33)+33;
        cout<<(char)r;
        Text.push_back((char)r);
    }
}
void WriteTextByFile(string &Text)
{
    ifstream in;
    in.open("1.txt");//文件名
    if(in.is_open())
    {
        std::stringstream buffer;  
        buffer<<in.rdbuf();
        Text=buffer.str();
    }
    else cout<<"can not find this file"<<endl;
    in.close();
    cout<<"WriteTextByFile Finished"<<endl;
}
void prtime(clock_t s)
{
	cout<<"usetime : "<<clock()-s<<" ms"<<endl;
}
char HelpPlus(const string &str,unsigned int &i,HuffmanTreeNode *r)
{
    unsigned int len=str.size();
    while(i<len&&r)
    {
        if(!r->left&&!r->right) {return r->leafchar;}
        int bit=str[++i]-'0';
        if(bit==1) r=r->right;
        else r=r->left;
    }
    return '\0';
}
string DeCodeToText(string &decompressText,HuffmanTreeNode *r)
{
    string NewText="";
    unsigned int i=0;
    while(i<decompressText.size())
    {
        NewText.push_back(HelpPlus(decompressText,i,r));
        ++i;
    }
    return NewText;
}
int main()
{
	clock_t start_time=clock();
    string PreText="";//文本
    //WriteTextByRand(PreText,10000);
    WriteTextByFile(PreText);
    prtime(start_time);
    //disStr(PreText);
    ComputeFreqTable(PreText);prtime(start_time);
    HuffmanTreeNode *huff=CreatHuffmanTree();prtime(start_time);
    ComputeDictTable(huff);prtime(start_time);
    CreatcodeToCharTable();prtime(start_time);
    string code=enCode(PreText);prtime(start_time);
    //cout<<code<<endl;
    string compressText=compressCode(code);prtime(start_time);
    //disStr(compressText);
    string decode=decompressCode(compressText);prtime(start_time);
    //cout<<decode<<endl;
    //string newtext=ConvertCodeToText(decode);//根据打表解码
    string newtext=DeCodeToText(decode,huff);//根据huffman树解码
    prtime(start_time);
    //disStr(newtext);
    if(code==decode) cout<<"Same Code"<<endl;
    else cout<<"Different Code"<<endl;
    if(PreText==newtext) cout<<"Same Text"<<endl;
    else cout<<"Different Text"<<endl;
    cout<<"PreText Length : "<<PreText.size()<<"   ComText Length : "<<compressText.size()<<endl;
    cout<<"Rate : "<<100.0*compressText.size()/PreText.size()<<"%"<<endl;
    ofstream o("compressText.txt");
    o<<compressText<<endl;
    o.close();
    ofstream out("newtext.txt");
    out<<newtext<<endl;
    out.close();
    clock_t end_time=clock();
    cout<<"rt : "<<(end_time-start_time)*1.0/CLOCKS_PER_SEC<<" s"<<endl;
    return 0;
}
