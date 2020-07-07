//#pragma GCC optimize(2)
//#include<bits/stdc++.h>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<cmath>

#define read(a) scanf("%d", &a)
#define readl(a) scanf("%lld", &a)
#define reads(a) scanf("%s", a)
#define readc(a) scanf("%c", &a)
#define readf(a) scanf("%lf", &a)
#define debug(a, b) printf("%s = %d\n", a, b)
#define debug1(a, i, b) printf("%s[%d] = %d", a, i, b)
#define debug2(a, c, n) for(int i = 1; i <= n; i++) printf("%s[%d] = %d%c", a, i, c[i], i == n ? '\n':' ')
#define debug3(a, n, m, c) for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) printf("%s[%d][%d] = %d%c", a, i, j, c[i][j], j == m ? '\n' : ' ')
#define show(a) putchar(a)
#define pb push_back
#define _rand mt19937 RAND(time(0))
#define mem(a) memset(a, 0, sizeof(a))
#define Buff ios::sync_with_stdio(false)
typedef long long ll;
using namespace std;
const int INF = 2e9 + 7;
const int N = 300 + 7;
const int M = 1e6 + 7;
const double eps = 1e-8;
vector<int> G[N];
int match[N], vis[N];
int n, m;

int dfs(int u)
{
    for(int v : G[u])
    {
        if(vis[v]) continue;
        vis[v] = 1;
        if(!match[v] || dfs(match[v]))
        {
            match[v] = u;
            return 1;
        }
    }
    return 0;
}

bool work()
{
    read(m); read(n);

    for(int i = 0; i < N; i++)
    {
        match[i] = 0;
        G[i].clear();
    }

    for(int u = 1; u <= m; u++)
    {
        int k, v;
        read(k);
        while(k--)
        {
            read(v);
            G[u].pb(v);
        }
    }

    int ans = m;
    for(int i = 1; i <= m; i++)
    {
        mem(vis);
        ans -= dfs(i);
    }

    return ans == 0;
}
signed main()
{
    int t; read(t);

    while(t--)
        if(work()) puts("YES");
        else       puts("NO");
    return 0;
}
