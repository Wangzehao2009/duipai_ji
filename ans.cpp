#include <bits/stdc++.h>
using namespace std;
int const N=1e3+3;
int a[N],n,m;
int ans=0x3f3f3f3f;
bool flag[N];
void dfs(int step,int num)
{
    if(step==n+1)
    {
        if(num!=m) return ;
        vector <int> v;
        for(int i=1;i<=n;++i) if(flag[i]) v.push_back(a[i]);
        int tmp=0;
        for(int i=1;i<v.size();++i) tmp=max(tmp,v[i-1]+v[i]);
        tmp=max(tmp,v[0]+v[v.size()-1]);
        ans=min(ans,tmp);
        return ;
    }
    if(num>m || num+n-step+1<m) return ;
    flag[step]=1,dfs(step+1,num+1);
    flag[step]=0,dfs(step+1,num);
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;++i) cin>>a[i];
    dfs(1,0);
    cout<<ans<<endl;
    return 0;
}