#include <bits/stdc++.h>
using namespace std;
string s;
int main()
{
    srand(time(NULL));
    int n=100000;
    for(int i=1;i<=n;++i) cout<<char(rand()%2+'a');
    return 0;
}