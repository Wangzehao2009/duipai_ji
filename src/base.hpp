#ifndef __BASE_HPP__
#define __BASE_HPP__
#include <bits/stdc++.h>
#include <readline/readline.h>
#include <readline/history.h>
using namespace std;
//check find
inline bool fd(const string &x,const string &y)
{
    return x.find(y)!=string::npos;
}
//aka
inline bool match(const string&x,const string&y,const string&suf)
{
    return (x==y || x==y+suf);
}
inline void aka(vector <string> &ret,const string &x,const string &suf)
{
    if(match(x,"all",suf))
    {
        ret.push_back("my"+suf),ret.push_back("ans"+suf);
        if(suf==".txt") ret.push_back("data"+suf);
        else ret.push_back("make_data"+suf),ret.push_back("spj"+suf);
    }
    else if(match(x,"ans",suf) || match(x,"a",suf)) ret.push_back("ans"+suf);
    else if(match(x,"make_data",suf) || match(x,"mk",suf)) ret.push_back("make_data"+suf);
    else if(match(x,"data",suf) || match(x,"d",suf)) ret.push_back("data"+suf);
    else if(match(x,"my",suf) || match(x,"m",suf)) ret.push_back("my"+suf);
    else if(match(x,"spj",suf) || match(x,"s",suf)) ret.push_back("spj"+suf);
    else ret.push_back("NULL");
}
// split string to vector
inline void split(const string &s,vector<string> &arg)
{
    string t="";
    arg.clear();
    for(int i=0;i<s.size();i++)
    {
        if(s[i]==' '||s[i]=='\n'||s[i]=='\r') 
        {
            if(!t.empty()) arg.push_back(t),t="";
        }
        else t+=s[i];
    }
    if(!t.empty()) arg.push_back(t);
}
// readline
inline void getLine(const string &prompt,string &s)
{
    char* buffer=readline(prompt.c_str());
    if(buffer&&*buffer) add_history(buffer);
    s=buffer;
    free(buffer);
}
// get arguments
inline void getArg(const string &prompt,vector<string> &arg)
{
    string s;
    getLine(prompt,s);
    split(s,arg);
}
// compare the outputs
inline void compout()
{
    vector<string> ask;
    printf("Compare the outputs? (y or n) : ");
    fflush(stdout);
    string s;
    getline(cin,s);
    split(s,ask);
    if(ask[0]=="y") system("vimdiff ans.txt my.txt");
}
#endif