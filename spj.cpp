#include<bits/stdc++.h>
using namespace std;

int a[100000];

inline int lowbit(int x){return x&(-x);}
inline int cnt(int x){int res=0;while(x){res++;x-=lowbit(x);}return res;}
inline int hdis(int x,int y){return cnt(x^y);}
// inline int mxdis(int x=s,int y=t){return ((1<<n)-1-(hdis(x,y)%2==0))*(x!=y);}


int main(){
    int n;
    cin>>n;
    n++;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=2;i<=n;i++){
        if(cnt(a[i-1]^a[i])!=1){
            return 1;
        }
    }
    return 0;
}