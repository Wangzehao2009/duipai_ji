#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;
inline void compout()
{
    printf("Compare the outputs? (y or n) : ");
    char ask;
    cin>>ask;
    if(ask=='y') system("vimdiff ans.txt my.txt");
    system("killall ans make_data my");
    printf("all processes have been killed.\n\n");
}
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
#define compans (system("g++ ans.cpp -w -std=c++11 -O2 -O3 -Ofast -o ans"))
#define compmy (system("g++ my.cpp -w -std=c++11 -O2 -O3 -Ofast -o my"))
#define compmk (system("g++ make_data.cpp -std=c++11 -w -O2 -O3 -Ofast -o make_data"))
#define compall (compans,compmy,compmk)
inline void qcomp()
{
    printf("Which documents do you want to compile? (all or make_data or ans or my) : ");
    vector <string> s;
    while(true)
    {
        string ask;
        cin>>ask;
        if(ask=="all") compall;
        else if(ask=="ans") compans;
        else if(ask=="my") compmy;
        else if(ask=="make_data" || ask=="mk") compmk;
        else
        {
            for(string i:s) cout<<"\033[1;31m"<<i<<"\033[0m ";
            if(s.size()>1) printf("are");
            else printf("is");
            printf(" \033[32mcompiled\033[0m.\n\n");
            return ;
        }
        s.push_back(ask);
    }
}
inline void queryq()
{
    printf("Do you want to quit duipai_ji? (y or n) : ");
    char ask;
    cin>>ask;
    if(ask=='y') exit(0);
}
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
int main()
{
    printf("Welcome to use \033[1;31mduipai_ji\033[0m by wzh.\n\n");
    compall;
    while(true)
    {
        printf("\033[32m(ji) \033[0m");
        string ask;
        cin>>ask;
        if(ask=="r" || ask=="run") test();
        else if(ask=="c" || ask=="comp") qcomp(); 
        else if(ask=="q" || ask=="quit") queryq();
        else if(ask=="t" || ask=="test") querytest();
        else if(ask=="clear") system("clear");
    }
    return 0;
}