#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;
string author="wzh jzq";
// get arguments
void getArg(vector<string> &arg){
    string s,t="";
    getline(cin,s);
    arg.clear();
    for(int i=0;i<s.size();i++){
        if(s[i]==' '||s[i]=='\n'||s[i]=='\r'){
            if(t.size()) arg.push_back(t),t="";
        }
        else t+=s[i];
    }
    arg.push_back(t);
}
// compare the outputs
inline void compout()
{
    printf("Compare the outputs? (y or n) : ");
    vector<string> ask;
    getArg(ask);
    if(ask[0]=="y") system("vimdiff ans.txt my.txt");
    system("killall ans make_data my");
    printf("all processes have been killed.\n\n");
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
    system("killall ans make_data my");
    printf("all processes have been killed.\n\n");
}
// compile
vector<string> default_comp_arg={"","-w","-std=c++11","-O2","-O3","-Ofast"};
void comp(const string &file,const vector<string> &arg){
    string cmd="g++ "+file+".cpp -o "+file;
    for(int i=1;i<arg.size();i++) cmd+=" "+arg[i];
    system(cmd.c_str());
}
#define compall(arg) (comp("ans",arg),comp("my",arg),comp("make_data",arg))
inline void qcomp(vector<string> &arg)
{
    if(arg.size()==1) arg=default_comp_arg;
    printf("Which documents do you want to compile? (all or make_data or ans or my) : ");
    vector <string> s,ss;
    getArg(s);
    for(string ask:s){
        ss.push_back(ask);
        if(ask=="all") compall(arg);
        else if(ask=="ans") comp("ans",arg);
        else if(ask=="my") comp("my",arg);
        else if(ask=="make_data" || ask=="mk") comp("make_data",arg);
        else ss.pop_back();
    }
    for(string i:ss) printf("\033[1;31m%s\033[0m ",i.c_str());
    if(ss.size()>1) printf("are");
    else printf("is");
    printf(" \033[32mcompiled\033[0m.\n\n");
}
// quit
inline void queryq()
{
    printf("Do you want to quit duipai_ji? (y or n) : ");
    vector<string> ask;
    getArg(ask);
    if(ask[0]=="y") exit(0);
}
// test
inline void querytest()
{
    system("./ans < data.txt > ans.txt");
    system("./my < data.txt > my.txt");
    if(system("diff -w ans.txt my.txt"))
    {
        printf("\033[1;31mWrong answer\033[0m.\n\n");
        compout();
        return ;
    }
    printf("\033[32mAccept\033[0m.\n\n");
}
// help
void help(){
    printf("\033[34mcomp (c)\033[0m -- recompile\n");
    printf("\033[34mhelp (h)\033[0m -- help\n");
    printf("\033[34mrun (r)\033[0m  -- start checking\n");
    printf("\033[34mquit (q)\033[0m -- quit\n");
    printf("\033[34mtest (t)\033[0m -- test \033[1;31mdata.txt\033[0m\n");
    printf("\033[34mclear\033[0m    -- clear the screen\n");
}
// console
int main()
{
    printf("Welcome to use \033[1;31mduipai_ji\033[0m by %s.\n\n",author.c_str());
    compall(default_comp_arg);
    while(true)
    {
        printf("\033[32m(ji) \033[0m");
        vector<string> cmd;
        getArg(cmd);
        string ask=cmd[0];
        if(ask=="r" || ask=="run") test();
        else if(ask=="c" || ask=="comp") qcomp(cmd);
        else if(ask=="q" || ask=="quit") queryq();
        else if(ask=="t" || ask=="test") querytest();
        else if(ask=="h" || ask=="help") help();
        else if(ask=="clear") system("clear");
    }
    return 0;
}
