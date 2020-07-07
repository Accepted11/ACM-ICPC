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
const int N = 1000 + 7;
const int M = 20 + 7;
const double eps = 1e-8;

int vis[N], dfn;
//int dir[2][4] = {{0, 0, 1, -1}, {1, -1, 0, 0}};
//vector<int> G[N];
int mp[N][M], limit[M];
vector<int> match[N];

int n, m;

void init()
{
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            read(mp[i][j]);
    for(int i = 1; i <= m; i++) read(limit[i]);
}

bool dfs(int u, int l, int r)
{
    for(int i = l, v; i <= r; i++)
    {
        v = mp[u][i];
        if(vis[v] == dfn) continue;
        vis[v] = dfn;
        if(match[v].size() < limit[v])
        {
            match[v].pb(u);
            return true;
        }
        for(int k = 0; k < match[v].size(); k++)
            if(dfs(match[v][k], l, r))
            {
                match[v][k] = u;
                return true;
            }
    }
    return false;
}

bool OK(int l, int r)
{
    dfn = 0;
    for(int i = 0; i <= m; i++)
    {
        match[i].clear();
        vis[i] = 0;
    }
    for(int i = 1; i <= n; i++)
    {
        dfn++;
        if(!dfs(i, l, r)) return false;
    }
    return true;
}

bool judge(int x)
{

    for(int k = 1; k + x - 1 <= m; k++)
        if(OK(k, k + x - 1)) return true;

    return false;
}

int work()
{
    init();

    for(int i = 1; i <= m; i++)
        if(judge(i)) return i;
}

signed main()
{
    while(~scanf("%d%d", &n, &m))
        printf("%d\n", work());

    return 0;
}
