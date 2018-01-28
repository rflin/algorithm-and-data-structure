#include <iostream>
#include <string>
#include <stack>
#include <cctype>
using namespace std;

double cptNum(char op,double a,double b)
{
    double ret=0.0;
    switch(op)
    {
        case '+':ret=a+b;break;
        case '-':ret=a-b;break;
        case '*':ret=a*b;break;
        case '/':ret=a/b;break;
    }
    return ret;
}
void cpt(stack<double> &numstk,stack<char> &opstk)
{
    char op=opstk.top();
    opstk.pop();
    double b=numstk.top();
    numstk.pop();
    double a=numstk.top();
    numstk.pop();
    numstk.push(cptNum(op,a,b));
}
bool precedence(char op1,char op2)
{
    if(op2=='('||op2==')')return false;
    if((op1=='*'||op1=='/')&&(op2=='+'||op2=='-'))return false;
    return true;
}
int main()
{
    stack<double> numstk;
    stack<char> opstk;
    string Exps;
    cin>>Exps;
    int explen=Exps.length();
    for(int i=0;i<explen;++i)
    {
        char x=Exps[i];
        if(isdigit(x))
        {
            double num=x-'0';
            while(i<explen-1&&isdigit(Exps[i+1]))
            {
                num=num*10+Exps[i+1]-'0';
                ++i;
            }
            numstk.push(num);
        }
        else if(x=='(') opstk.push(x);
        else if(x==')')
        {
            while(opstk.top()!='(') cpt(numstk,opstk);
            opstk.pop();
        }
        else
        {
            while(!opstk.empty()&&precedence(x,opstk.top())) cpt(numstk,opstk);
            opstk.push(x);
        }
    }
    while(!opstk.empty()) cpt(numstk,opstk);
    cout<<numstk.top();
    return 0;
}
