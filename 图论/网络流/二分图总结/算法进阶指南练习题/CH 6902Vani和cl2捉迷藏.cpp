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
const int N = 200 + 7;
const int M = 1e6 + 7;
const double eps = 1e-8;
vector<int> G[N];
int n, m;
int dp[N][N], match[N], vis[N];

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

signed main()
{
    read(n); read(m);
    for(int i = 1; i <= n; i++)
        dp[i][i] = 1;
    for(int i = 1; i <= m; i++)
    {
        int u, v;
        read(u); read(v);
        dp[u][v] = 1;
    }

    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                dp[i][j] |= dp[i][k] && dp[k][j];
    for(int i = 1; i <= n; i++) dp[i][i] = 0;

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(dp[i][j]) G[i].pb(j);

    int ans = n;
    for(int i = 1; i <= n; i++)
    {
        mem(vis);
        ans -= dfs(i);
    }
    printf("%d\n", ans);

    return 0;
}
