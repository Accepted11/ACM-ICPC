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
const int N = 100 + 7;
const int M = 1e6 + 7;
const double eps = 1e-8;

int n, m, k;
int flag[N][N];
int match[N], vis[N];
vector<int> G[N];
struct point
{
    int x, y;
    point(int x = 0, int y = 0) : x(x), y(y) {}
}p[N * N];
bool dfs(int u)
{
    for(int v : G[u])
    {
        if(!flag[u][v] || vis[v]) continue;
        vis[v] = 1;
        if(!match[v] || dfs(match[v]))
        {
            match[v] = u;
            return true;
        }
    }
    return false;
}

int Count()
{
    int ans = 0;
    mem(match);
    for(int i = 1; i <= n; i++)
    {
        mem(vis);
        if(dfs(i)) ans++;
    }
    return ans;
}

int T = 0;
void init()
{
    mem(flag);
    for(int i = 0; i < N; i++)
        G[i].clear();

    for(int i = 1; i <= k; i++)
    {
        int u, v;
        read(u); read(v);
        flag[u][v] = 1;
        G[u].pb(v);
    }
}

void work()
{
    init();
    int ans1 = 0, ans2 = 0;
    ans1 = Count();
    int cnt = 0;
    for(int i = 1; i <= m; i++)
    {
        if(!match[i]) continue;
        p[++cnt] = point(match[i], i);
    }

    for(int i = 1; i <= ans1; i++)
    {
        int u = p[i].x, v = p[i].y;
        flag[u][v] = 0;
        if(ans1 != Count()) ans2++;
        flag[u][v] = 1;
    }
    printf("Board %d have %d important blanks for %d chessmen.\n", ++T, ans2, ans1);
}
signed main()
{
    while(~scanf("%d%d%d", &n, &m, &k))
        work();
    return 0;
}
