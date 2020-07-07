#pragma GCC optimize(2)
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
const int N = 100 + 7;
const int M = 1e6 + 7;
const double eps = 1e-8;
int n, m, k;

int mp[N][N], vis[N], match[N];
vector<int> G[N];

bool dfs(int u, int v = 0)
{
    for(int i = 0; i < G[u].size(); i++)
    {
        v = G[u][i];
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

void work()
{
    for(int i = 1; i <= k; i++)
    {
        int x, y, z;
        read(x); read(y); read(z);
        if(y == 0 || z == 0) continue;
        if(!mp[y][z]) G[y].pb(z);
        mp[y][z] = 1;
    }

    int ans = 0;
    for(int i = 1; i < n; i++)
    {
        mem(vis);
        ans += dfs(i);
    }
    printf("%d\n", ans);
    mem(mp); mem(match);
    for(int i = 0; i <= n; i++)
        G[i].clear();
}
signed main()
{
    while(~read(n))
    {
        if(n == 0) break;
        read(m); read(k);
        work();
    }

    return 0;
}
