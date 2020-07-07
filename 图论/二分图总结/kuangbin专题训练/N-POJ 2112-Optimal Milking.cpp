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
const int INF = 1e5 + 7;
const int N = 300 + 7;
const int M = 300 + 7;
const double eps = 1e-8;

int vis[N], dfn;
int dp[N][N];
//int dir[2][4] = {{0, 0, 1, -1}, {1, -1, 0, 0}};
//vector<int> G[N];
vector<int> match[N];

int k, c, m, n;

void init()
{
    n = k + c;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
        {
            read(dp[i][j]);
            if(dp[i][j] == 0) dp[i][j] = INF;
        }

    //Floyed
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                if(dp[i][j] > dp[i][k] + dp[k][j])
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
}

bool dfs(int u, int mid)
{
    for(int i = 1; i <= k; i++)
    {
        if(dp[i][u] <= mid && vis[i] != dfn)
        {
            vis[i] = dfn;
            if(match[i].size() < m)
            {
                match[i].pb(u);
                return true;
            }
            for(int k = 0; k < match[i].size(); k++)
            {
                if(dfs(match[i][k], mid))
                {
                    match[i][k] = u;
                    return true;
                }
            }
        }
    }
    return false;
}

bool judge(int mid)
{
    dfn = 0;
    for(int i = 0; i < N; i++)
    {
        match[i].clear();
        vis[i] = 0;
    }

    for(int i = k + 1; i <= k + c; i++)
    {
        dfn++;
        if(!dfs(i, mid)) return false;
    }
    return true;
}

void work()
{
    init();

//    cout << judge(2) << endl;
    int L = 0, R = 1e5 + 7, mid;
    while(L < R)
    {
        mid = (L + R) >> 1;
        if(judge(mid)) R = mid;
        else           L = mid + 1;
    }

    printf("%d\n", R);
}

signed main()
{
    while(~scanf("%d%d%d", &k, &c, &m))
        work();
    return 0;
}

// 一对多的匹配， 考虑 对 match 进行扩展
