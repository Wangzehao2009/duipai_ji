#include <bits/stdc++.h>
using namespace std;
int main()
{
  mt19937 rd(time(NULL));
  int n=10,m=6,mod=10;
  cout<<n<<" "<<m<<endl;
  for(int i=1;i<=n;++i) cout<<rd()%mod+1<<" ";
  return 0;
}