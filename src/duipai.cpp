#include <bits/stdc++.h>
#include <sys/time.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "run.hpp"
#include "base.hpp"
#include "autoComplete.hpp"
using namespace std;
string author="wzh jzq";
// compile
vector<string> default_comp_arg={"","-w","-std=c++14","-O2","-O3","-Ofast"};
inline void comp(const string &file,const vector<string> &arg)
{
    if(access("exe",0)==-1) system("mkdir exe");
    if(file=="NULL") return ;
    string cmd="g++ "+file+".cpp -o "+file;
    for(int i=0;i<arg.size();i++) cmd+=" "+arg[i];
    system(cmd.c_str()),system(("mv "+file+" exe").c_str());
}
#define compall(arg) (comp("ans",arg),comp("my",arg),comp("make_data",arg),comp("spj",arg))
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
    printf("help (h) -- help\n");
    printf("\n");
    printf("init [ file ... ] -- initialize files\n");
    printf("\n");
    printf("comp (c) [ file ... ] -- compile\n");
    printf("    [ compile_option ... ] - customize compile\n");
    printf("\n");
    printf("cat [ file ... ] -- concatenate and print files\n");
    printf("\n");
    printf("test (t) [ file ... ] -- test current data\n");
    printf("    [ --diff | -d ] - check differences\n");
    printf("    [ --cat | -c ] - cat\n");
    printf("    [ --spj | -s ] - compare by special judge\n");
    printf("    [ --timelimit | -t ] [ time ] - set [ time ] (integer) as time (in second) limit for each testcase\n");
    printf("    [ --memlimit | -m ] [ mem ] - set [ mem ] (integer) as memory (in MB) limit for each testcase\n");
    printf("\n");
    printf("clean -- delete all files in the folder except system files\n");
    printf("\n");
    printf("run (r)  -- start duipaiing\n");
    printf("    [ --cores | -c ] [ thread_count ] - run by using [ thread_count ] threads\n");
    printf("    [ --spj | -s ] - compare by special judge\n");
    printf("    [ --Timelimit | -T ] [ time ] - set [ time ] as running time limit\n");
    printf("    [ --Caselimit | -C ] [ case ] - set [ case ] as running case limit\n");
    printf("    [ --timelimit | -t ] [ time ] - set [ time ] (integer) as time (in second) limit for each testcase\n");
    printf("    [ --memlimit | -m ] [ mem ] - set [ mem ] (integer) as memory (in MB) limit for each testcase\n");
    printf("\n");
    printf("clear -- clear the screen\n");
    printf("\n");
    printf("quit (q) -- quit\n");
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
//clean
inline void clean()
{
    vector <string> q;
    getArg("Confirm to clean? (y or n) : ",q);
    if(q[0]=="n") return ;
    system("ls | grep -Ev 'duipai|ans.cpp|my.cpp|make_data.cpp|README.md|install.sh|src|library|spj.cpp|exe|.gitignore|license' | xargs rm -r");
}
//rm
inline void rm(const vector <string> &arg)
{
    vector <string> q;
    getArg("Confirm to remove? (y or n) : ",q);
    string c="";
    for(string i:arg) c+=i,c+=" ";
    system(c.c_str());
}
//initialize
inline void Init(vector <string> &arg)
{
    arg.erase(arg.begin());
    vector <string> q;
    getArg("Confirm to initialize? (y or n) : ",q);
    if(q[0]=="n") return ;
    vector <string> init;
    if(arg.empty()) arg.push_back("all");
    for(string file:arg) aka(init,file,"");
    int cnt=0;
    for(string file:init) if(file!="NULL") cnt++,system(("cp src/"+file+"_init.cpp "+file+".cpp").c_str()),printf("\033[1;31m%s\033[0m ",file.c_str());;
    if(!cnt)
    {
        printf("\033[1;31merror: \033[0minvalid initialization file\n");
        return ;   
    }
    if(cnt>1) printf("are");
    else printf("is");
    printf(" \033[32minitialized\033[0m.\n");
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
        else if(ask=="rm") rm(cmd);
        else if(ask=="init") Init(cmd);
        else if(ask=="retest" || ask=="rt") retest(cmd);
        else help();
    }
    return 0;
}
