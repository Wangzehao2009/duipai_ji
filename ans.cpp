#include<bits/stdc++.h>
using namespace std;
int n,ans=0,nxt[500005],len[500005];
string s;
void kmp(){
    nxt[1]=0;
    for(int i=2;i<=n;i++){
        int j=nxt[i-1];
        while(j&&s[j+1]!=s[i]) j=nxt[j];
        if(s[j+1]==s[i]) nxt[i]=j+1;
        else nxt[i]=0;
    }
}
int calc(){
    kmp();
    int mx=0;
    len[n+1]=0;
    for(int i=n;i>=1;i--){
        int j=len[i+1];
        while(j&&s[i]!=s[j+1]) j=nxt[j];
        if(s[i]==s[j+1]) len[i]=j+1;
        else len[i]=0;
        mx=max(mx,min(len[i],(i+len[i]-1)/2));
    }
    return mx;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>s;
    n=s.size();
    s=" "+s;
    int l=1,r=n;
    while(s[l]==s[r]&&l<r) l++,r--,ans++;
    if(l>=r){
        cout<<ans;
        return 0;
    }
    n=r-l+1;
    string t=" ";
    for(int i=l;i<=r;i++) t+=s[i];
    s=t;
    int mx=0;
    mx=max(mx,calc());
    t=" ";
    for(int i=n;i>=1;i--) t+=s[i];
    s=t;
    mx=max(mx,calc());
    cout<<ans+mx;
    return 0;
}