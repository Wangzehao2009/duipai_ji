// duipai
#ifndef __RUN_HPP__
#define __RUN_HPP__
#include <bits/stdc++.h>
#include <sys/time.h>
#include <thread>
#include <mutex>
#include "base.hpp"
#include <unistd.h>
#include <sys/resource.h>
#include <sys/wait.h>
// using namespace std;

bool acc[1000005];
int threadCnt,killed,killtype,testCaseId[1000005];
bool spj=0,limitt=0,limitc=0;
int Caselimit=500,history_data_cnt=countFilesInDirectory("historydata");
double Timelimit=45,timeUsed[1000005];
mutex killedMtx;
thread t[1000005];
unsigned long long t0,t1;
int timelimit,memlimit;

#define Accept 0
#define WrongAnswer 1
#define MakeDataLE 2
#define AnsLE 3
#define MyLE 4

int execute(const char* s,const string &in,const string &out){
    int pid=fork();
    if(pid==0){
        if(in!="") freopen(in.c_str(),"r",stdin);
        if(out!="") freopen(out.c_str(),"w",stdout);
        rlimit nTime,nMem;
        nTime.rlim_cur=nTime.rlim_max=timelimit;
        nMem.rlim_cur=nMem.rlim_max=memlimit*1048576;
        setrlimit(RLIMIT_CPU,&nTime);setrlimit(RLIMIT_AS,&nMem);
        exit(execl(s,s,(char*)NULL));
    }
    else{
        int wstatus = 0;
        waitpid(pid,&wstatus,0);
        return wstatus;
    }
    return 0;
}
inline int diff(const std::string &data,const std::string &ans,const std::string &my)
{
    std::string diff;
    if(!spj) diff="diff -w "+ans+" "+my;
    else diff="exe/spj "+data+" "+my+" "+ans;
    if(system(diff.c_str())) return 1;
    return 0;
}
inline void printType(int type){
    if(type==Accept) printf("\033[32mAccept\033[0m");
    else if(type==WrongAnswer) printf("\033[1;31mWrong Answer\033[0m");
    else if(type==MakeDataLE) printf("\033[35mmake_data Limit Exceeded\033[0m");
    else if(type==AnsLE) printf("\033[35mans Limit Exceeded\033[0m");
    else if(type==MyLE) printf("\033[35mLimit Exceeded\033[0m");
}
unsigned long long gettime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    unsigned long long noww,now;
    return tv.tv_sec*1000+tv.tv_usec/1000;
}
void printStat()
{
    system("clear");
    int tot=0;
    for(int i=1;i<=threadCnt;i++)
    {
        if(!acc[i]) printf("\033[1mthread #%d\033[0m\n\033[1;32mRunning\033[0m on case \033[34m%d\033[0m.\n\033[34m%.3lfs\033[0m have been used.\n\n",i,testCaseId[i],timeUsed[i]),tot+=testCaseId[i];
        else printf("\033[1mthread #%d\033[0m\n\033[32mAccept\033[0m.\n\n",i);
    }
    printf("\033[1mtotal time:\033[0m \033[34m%.3lfs\033[0m\n",(gettime()-t0)*1.0/1000);
    printf("\033[1mtotal case:\033[0m \033[34m%d\033[0m\n\n",tot);
}
inline void threadFunction(int &cnt,int id,bool &accepted,double &tm)
{
    string data="rundata/data"+to_string(id)+".txt",my="rundata/my"+to_string(id)+".txt",ans="rundata/ans"+to_string(id)+".txt";
    unsigned long long noww,now;
    noww=now=gettime();
    while(((!(limitc^limitt) && cnt<=Caselimit && (noww-now)*1.0/1000<=Timelimit) || (limitc && cnt<=Caselimit) || (limitt && (noww-now)*1.0/1000<=Timelimit)) && !killed)
    {
        ++cnt;
        noww=gettime();
        tm=(noww-now)*1.0/1000;
        int type=Accept,ret;
        ret=execute("exe/make_data","",data);
        if(ret!=0) type=MakeDataLE;
        ret=execute("exe/ans",data,ans);
        if(ret!=0) type=AnsLE;
        ret=execute("exe/my",data,my);
        if(ret!=0) type=MyLE;
        if(type==Accept&&diff(data,ans,my)) type=WrongAnswer;
        if(type!=Accept){
            killedMtx.lock();
            accepted=1;
            if(killed){
                killedMtx.unlock();
                return ;
            }
            killed=id;
            killtype=type;
            killedMtx.unlock();
            return;
        }
        if((gettime()-t1)*1.0/1000>0.1) t1=gettime(),printStat();
    }
    accepted=1;
    return ;
}
inline void comp(const std::string &file,const std::vector<std::string> &arg);
inline void test(std::vector<std::string> &arg)
{
    system("mkdir rundata");
    threadCnt=1,spj=0,limitt=limitc=0,Caselimit=500,Timelimit=45,timelimit=1,memlimit=512;
    for(int i=1;i<arg.size();i++)
    {
        if(arg[i]=="-c" || arg[i]=="--cores") threadCnt=stoi(arg[i+1]);
        else if(arg[i]=="-s" || arg[i]=="--spj") spj=1;
        else if(arg[i]=="-T" || arg[i]=="--Timelimit") limitt=1,Timelimit=stod(arg[i+1]);
        else if(arg[i]=="-C" || arg[i]=="--Caselimit") limitc=1,Caselimit=stoi(arg[i+1]);
        else if(arg[i]=="-t" || arg[i]=="--timelimit") timelimit=stoi(arg[i+1]);
        else if(arg[i]=="-m" || arg[i]=="--memlimit") memlimit=stoi(arg[i+1]);
    }
    killed=0,killtype=Accept;
    killedMtx.unlock();
    t0=t1=gettime();
    for(int i=1;i<=threadCnt;i++)
    {
        testCaseId[i]=1;
        acc[i]=0;
        timeUsed[i]=0;
        t[i]=thread(threadFunction,ref(testCaseId[i]),i,ref(acc[i]),ref(timeUsed[i]));
    }
    while(!killed)
    {
        bool flag=true;
        for(int i=1;i<=threadCnt;i++) flag&=acc[i];
        if(flag) break;
    }
    for(int i=1;i<=threadCnt;i++) t[i].join();
    system("clear");
    if(killed)
    {
        printf("thread #%d : ",killed);
        printType(killtype);
        printf(" on case \033[34m%d\033[0m.\n\n",testCaseId[killed]);
        system(("cp rundata/ans"+to_string(killed)+".txt ans.txt").c_str());
        system(("cp rundata/data"+to_string(killed)+".txt data.txt").c_str());
        system(("cp rundata/my"+to_string(killed)+".txt my.txt").c_str());
        if(access("historydata",0)==-1) history_data_cnt=0,system("mkdir historydata");
        history_data_cnt++;
        system(("cp rundata/data"+to_string(killed)+".txt historydata/data"+to_string(history_data_cnt)+".txt").c_str());
        system("rm -r rundata");
        compout();
    }
    else 
    {
        system("rm -r rundata");
        printf("\033[32mAccept\033[0m.\n\n");
    }
}
//retest
inline void retest(std::vector <std::string> &arg)
{
    if(access("historydata",0)==-1)
    {
        printf("\033[1;31merror: \033[0mNo historydata\n");
        return ;
    }
    system("cp -r historydata rundata");
    timelimit=1,memlimit=512;
    for(int i=1;i<arg.size();i++){
        if(arg[i]=="-s" || arg[i]=="--spj") spj=1;
        if(arg[i]=="-t" || arg[i]=="--timelimit") timelimit=stoi(arg[i+1]);
        if(arg[i]=="-m" || arg[i]=="--memlimit") memlimit=stoi(arg[i+1]);
    }
    for(int id=1;id<=history_data_cnt;++id)
    {
        std::string data="rundata/data"+to_string(id)+".txt",my="rundata/my"+to_string(id)+".txt",ans="rundata/ans"+to_string(id)+".txt";
        int type=Accept,ret;
        ret=execute("exe/ans",data,ans);
        if(ret!=0) type=AnsLE;
        ret=execute("exe/my",data,my);
        if(ret!=0) type=MyLE;
        if(diff(data,ans,my)) type=WrongAnswer;
        if(type!=Accept){
            printType(type);
            printf(" on case \033[34m%d\033[0m.\n\n",id);
            system(("cp rundata/ans"+to_string(id)+".txt ans.txt").c_str());
            system(("cp rundata/data"+to_string(id)+".txt data.txt").c_str());
            system(("cp rundata/my"+to_string(id)+".txt my.txt").c_str());
            system("rm -r rundata");
            compout();
            return ;
        }
    }
    system("rm -r rundata");
    printf("\033[32mAccept\033[0m.\n\n");
}
// test
inline void cat(vector<string> &files);
inline void querytest(std::vector<std::string> &arg)
{
    spj=false,timelimit=1,memlimit=512;
    for(int i=1;i<arg.size();++i){
        if(arg[i]=="-s" || arg[i]=="--spj") spj=true;
        if(arg[i]=="-t" || arg[i]=="--timelimit") timelimit=stoi(arg[i+1]);
        if(arg[i]=="-m" || arg[i]=="--memlimit") memlimit=stoi(arg[i+1]);
    }
    int type=Accept,ret;
    ret=execute("exe/ans","data.txt","ans.txt");
    if(ret!=0) type=AnsLE;
    ret=execute("exe/my","data.txt","my.txt");
    if(ret!=0) type=MyLE;
    if(type!=Accept){
        printType(type);
        printf(".\n\n");
        return;
    }
    for(int i=1;i<arg.size();++i)
    {
        if(arg[i]=="-d" || arg[i]=="--diff" || arg[i]=="-s" || arg[i]=="--spj"){
            if(diff("data.txt","ans.txt","my.txt")){
                printf("\033[1;31mWrong answer\033[0m.\n\n");
                compout();
            }
            else{
                printf("\033[32mAccept\033[0m.\n\n");
            }
        }
        if(arg[i]=="-c" || arg[i]=="--cat")
        {
            std::vector<std::string> files;
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
#endif
