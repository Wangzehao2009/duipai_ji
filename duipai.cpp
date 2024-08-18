#include <bits/stdc++.h>
#include <sys/time.h>
#include <readline/readline.h>
#include <readline/history.h>
using namespace std;
string author="wzh jzq";
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
inline vector<string> aka(const string &x,const string &suf)
{
    vector <string> ret;
    if(match(x,"all",suf))
    {
        ret.push_back("my"+suf),ret.push_back("ans"+suf);
        if(suf==".txt") ret.push_back("data"+suf);
        else ret.push_back("make_data"+suf);
    }
    else if(match(x,"ans",suf) || match(x,"a",suf)) ret.push_back("ans"+suf);
    else if(match(x,"make_data",suf) || match(x,"mk",suf)) ret.push_back("make_data"+suf);
    else if(match(x,"data",suf) || match(x,"d",suf)) ret.push_back("data"+suf);
    else if(match(x,"my",suf) || match(x,"m",suf)) ret.push_back("my"+suf);
    else ret.push_back("NULL");
    return ret;
}
//readline
inline void getLine(const string &prompt,string &s){
    char* buffer=readline(prompt.c_str());
    if(buffer&&*buffer) add_history(buffer);
    s=buffer;
    free(buffer);
}
// get arguments
inline void getArg(const string &prompt,vector<string> &arg){
    string s,t="";
    getLine(prompt,s);
    // getline(cin,s);
    arg.clear();
    for(int i=0;i<s.size();i++){
        if(s[i]==' '||s[i]=='\n'||s[i]=='\r'){
            if(!t.empty()) arg.push_back(t),t="";
        }
        else t+=s[i];
    }
    if(!t.empty()) arg.push_back(t);
}
// compare the outputs
inline void compout()
{
    vector<string> ask;
    getArg("Compare the outputs? (y or n) : ",ask);
    if(ask[0]=="y") system("vimdiff ans.txt my.txt");
}
//diff
inline void diff()
{
    if(system("diff -w ans.txt my.txt"))
    {
        printf("\033[1;31mWrong answer\033[0m.\n\n");
        compout();
        return ;
    }
    printf("\033[32mAccept\033[0m.\n\n");
}
// duipai
inline void test()
{
    system("clear");
    long long cnt=0;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    unsigned long long noww,now;
    noww=now=tv.tv_sec*1000+tv.tv_usec/1000;
    while(cnt<=500 && (noww-now)*1.0/1000<=45)
    {
        ++cnt;
        printf("\033[1;32mRunning\033[0m on test \033[34m%lld\033[0m.\n\n",cnt);
        struct timeval tv1;
        gettimeofday(&tv1,NULL);
        noww=tv1.tv_sec*1000+tv1.tv_usec/1000;
        printf("\033[34m%.3lfs\033[0m have been used.\n\n",(noww-now)*1.0/1000);
        system("./make_data > data.txt");
        system("./ans < data.txt > ans.txt");
        system("./my < data.txt > my.txt");
        if(system("diff -w ans.txt my.txt"))
        {
            system("clear");
            printf("\033[1;31mWrong answer\033[0m on test \033[34m%lld\033[0m.\n\n",cnt);
            compout();
            return ;
        }
        system("clear");
    }
    printf("\033[32mAccept\033[0m.\n\n");
}
// compile
vector<string> default_comp_arg={"","-w","-std=c++14","-O2","-O3","-Ofast"};
inline void comp(const string &file,const vector<string> &arg){
    if(file=="NULL") return ;
    string cmd="g++ "+file+".cpp -o "+file;
    for(int i=1;i<arg.size();i++) cmd+=" "+arg[i];
    system(cmd.c_str());
}
#define compall(arg) (comp("ans",arg),comp("my",arg),comp("make_data",arg))
inline void qcomp(vector<string> &arg)
{
    int cnt=0;
    vector <string> opt,files;
    for(int i=1;i<arg.size();++i) 
    {
        if(arg[i][0]=='-') opt.push_back(arg[i]);
        else files.push_back(arg[i]);
    }
    if(opt.empty()) arg=default_comp_arg;
    else arg=opt;
    if(files.empty()) files.push_back("all");
    for(string &ask:files)
    {
        vector <string> file=aka(ask,"");
        for(string &comp_file:file) 
        {
            if(comp_file=="NULL") continue;
            printf("\033[1;31m%s\033[0m ",comp_file.c_str());
            ++cnt;
            comp(comp_file,arg);
        }
    }
    if(!cnt)
    {
        printf("\033[1;31merror: \033[0minvalid compile file\n");
        return ;   
    }
    if(cnt>1) printf("are");
    else printf("is");
    printf(" \033[32mcompiled\033[0m.\n");
}
// quit
inline void queryq()
{
    vector<string> ask;
    getArg("Do you want to quit duipai_ji? (y or n) : ",ask);
    if(ask[0]=="y") exit(0);
}
// help
inline void help(){
    printf("\033[34mcomp (c)\033[0m -- recompile\n");
    printf("\033[34mhelp (h)\033[0m -- help\n");
    printf("\033[34mrun (r)\033[0m  -- start checking\n");
    printf("\033[34mquit (q)\033[0m -- quit\n");
    printf("\033[34mtest (t)\033[0m -- test \033[1;31mdata.txt\033[0m\n");
    printf("\033[34mclear\033[0m    -- clear the terminal screen\n");
    printf("\033[34mcat\033[0m      -- concatenate and print files\n");
}
// cat
inline void catfile(string file)
{
    printf("\033[1;31m%s\033[0m\n",file.c_str());
    system(("cat "+file).c_str());
    printf("\n\n");
}
inline void cat(vector<string> &files){
    if(files.size()==1) files.push_back("all");
    for(int i=1;i<files.size();i++)
    {
        vector <string> file=aka(files[i],".txt");
        for(string &cat_file:file) if(cat_file!="NULL") catfile(cat_file);
    }
}
// test
inline void querytest(vector<string> &arg)
{
    system("./ans < data.txt > ans.txt");
    system("./my < data.txt > my.txt");
    for(int i=1;i<arg.size();++i)
    {
        if(arg[i]=="-d" || arg[i]=="-diff") diff();
        if(arg[i]=="-c")
        {
            vector <string> files;
            files.push_back("");
            while(i+1<arg.size()) 
            {
                if(arg[i+1][0]!='-') files.push_back(arg[++i]);
                else break;
            }
            if(files.empty()) files.push_back("all");
            cat(files);
        }
    }
}
// console
int main()
{
    printf("Welcome to use \033[1;31mduipai_ji\033[0m by %s.\n\n",author.c_str());
    compall(default_comp_arg);
    while(true)
    {
        vector<string> cmd;
        printf("\e[32m(ji)$ \e[0m");
        getArg("\033[D\033[C",cmd);
        if(cmd.empty()) continue;
        string ask=cmd[0];
        if(ask=="r" || ask=="run") test();
        else if(ask=="c" || ask=="comp") qcomp(cmd);
        else if(ask=="q" || ask=="quit") queryq();
        else if(ask=="t" || ask=="test") querytest(cmd);
        else if(ask=="h" || ask=="help") help();
        else if(ask=="clear") system("clear");
        else if(ask=="cat") cat(cmd);
    }
    return 0;
}
