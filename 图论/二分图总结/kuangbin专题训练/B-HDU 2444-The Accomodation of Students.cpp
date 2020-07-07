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
int color[N], match[N], vis[N];
vector<int> G[N];
int n, m, dfn;
// 二分图判定
bool dfs(int u, int col)
{
    color[u] = col;
    for(int v : G[u])
    {
        if(!color[v] && !dfs(v, 3 - col)) return false;
        if(color[v] == col)               return false;
    }
    return true;
}

//匈牙利算法
bool dfs(int u)
{
    for(int v : G[u])
    {
        if(vis[v]) continue;
        vis[v] = 1;
        if(!match[v] || dfs(match[v]))
        {
            match[v] = u;
            return true;
        }
    }
    return false;
}

void init()
{
    for(int i = 0; i <= n; i++)
    {
        G[i].clear();
        match[i] = 0; color[i] = 0;
    }
}
int work()
{
    init();
    for(int i = 1; i <= m; i++)
    {
        int u, v;
        read(u); read(v);
        G[u].pb(v); G[v].pb(u);
    }

    for(int i = 1; i <= n; i++)
        if(!color[i] && !dfs(i, 1)) return -1;

    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        if(color[i] != 1) continue;
        mem(vis);
        ans += dfs(i);
    }

    return ans;
}
signed main()
{
    while(~scanf("%d%d", &n, &m))
    {
        int ans = work();
        if(ans == -1) puts("No");
        else          printf("%d\n", ans);
    }

    return 0;
}
