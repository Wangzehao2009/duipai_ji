#include <bits/stdc++.h>
using namespace std;
int const N=1e5+3;
long long f[N][10],g[N][10],a[N];
int h[N][10],n,m;
long long ans=0x3f3f3f3f3f3f3f3f;
int main()
{
    memset(f,0x3f,sizeof(f)),memset(g,0x3f,sizeof(g));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        g[i][1]=a[i],f[i][1]=a[i],h[i][1]=i;
        for(int j=2;j<=min(i,m);++j)
        {
            for(int k=1;k<i;++k)
            {
                if(f[i][j]>max(f[k][j-1],+a[i]))
                {
                    f[i][j]=max(f[k][j-1],a[k]+a[i]);
                    h[i][j]=h[k][j-1];
                }
                g[i][j]=min(g[i][j],max(f[k][j-1],max(a[k]+a[i],a[i]+a[h[k][j-1]])));
            }
        }
        ans=min(ans,g[i][m]);
    }
    printf("%lld\n",ans);
    return 0;
}