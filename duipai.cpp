#include <bits/stdc++.h>
#include <sys/time.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "run.hpp"
#include "base.hpp"
#include "autoComplete.hpp"
using namespace std;
string author="wzh jzq";
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
        vector <string> file;
        aka(file,ask,"");
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
inline void help()
{
    putchar('\n');
    printf("\033[34mhelp (h)\033[0m -- help\n");
    putchar('\n');
    printf("\033[34mcomp (c) [ file ... ]\033[0m -- compile\n");
    printf("\033[34m    [ compile_option ... ]\033[0m - customize compile\n");
    putchar('\n');
    printf("\033[34mcat [ file ... ]\033[0m  -- concatenate and print files\n");
    putchar('\n');
    printf("\033[34mtest (t) [ file ...]\033[0m -- test current data\n");
    printf("\033[34m    [ -d ]\033[0m - check differences\n");
    printf("\033[34m    [ -c ]\033[0m - cat\n");
    putchar('\n');
    printf("\033[34mclean\033[0m -- delete all files in the folder except system files\n");
    putchar('\n');
    printf("\033[34mrun (r)\033[0m -- start duipaiing\n");
    printf("\033[34m    [ -c ] [ thread_count ]\033[0m - duipaiing by using [ thread_count ] threads\n");
    putchar('\n');
    printf("\033[34mclear\033[0m -- clear the screen\n");
    putchar('\n');
    printf("\033[34mquit (q)\033[0m -- quit\n");
    putchar('\n');
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
        vector <string> file;
        aka(file,files[i],".txt");
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
//clean
inline void clean()
{
    system("ls | grep -Ev 'duipai|ans|my|make_data|README.md|install.sh|base.hpp|run.hpp|data' | xargs rm -r");
}
// console
int main()
{
    init();
    printf("Welcome to use \033[1;31mduipai_ji\033[0m by %s.\n\n",author.c_str());
    compall(default_comp_arg);
    while(true)
    {
        vector<string> cmd;
        // printf("\e[32m(ji)$ \e[0m");
        // getArg("\033[D\033[C",cmd);
        getArg("\001\033[32m\002(ji)$ \001\033[0m\002",cmd);
        if(cmd.empty()) continue;
        string ask=cmd[0];
        if(ask=="r" || ask=="run") test(cmd);
        else if(ask=="c" || ask=="comp") qcomp(cmd);
        else if(ask=="q" || ask=="quit") queryq();
        else if(ask=="t" || ask=="test") querytest(cmd);
        else if(ask=="h" || ask=="help") help();
        else if(ask=="clear") system("clear");
        else if(ask=="cat") cat(cmd);
        else if(ask=="clean") clean();
    }
    return 0;
}
