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
const int N = 500 + 7;
const int M = 500 + 7;
const double eps = 1e-8;

int match[N], vis[N], dfn;
//int dir[2][4] = {{0, 0, 1, -1}, {1, -1, 0, 0}};
vector<int> G[N];

int cntA, cntB, n, m, k;

struct people
{
    string like, dis;
}A[N], B[N];

void init()
{
    cntA = cntB = dfn = 0;
    for(int i = 0; i < N; i++)
    {
        match[i] = vis[i] = 0;
        G[i].clear();
    }

    string str1, str2;
    for(int i = 1; i <= k; i++)
    {
        cin >> str1 >> str2;
        if(str1[0] == 'C')
        {
            A[++cntA].like = str1;
            A[cntA].dis = str2;
        }
        else
        {
            B[++cntB].like = str1;
            B[cntB].dis = str2;
        }
    }

    for(int i = 1; i <= cntA; i++)
        for(int j = 1; j <= cntB; j++)
            if(A[i].like == B[j].dis || A[i].dis == B[j].like)
                G[i].pb(j);
}

bool dfs(int u)
{
    for(int i = 0, v; i < G[u].size(); i++)
    {
        v = G[u][i];
        if(vis[v] == dfn) continue;
        vis[v] = dfn;
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
    init();

    int ans = k;
    for(int i = 1; i <= cntA; i++)
    {
        dfn++;
        if(dfs(i)) ans--;
    }

    cout << ans << endl;
}

signed main()
{
    Buff;
    while(cin >> n >> m >> k)
        work();
    return 0;
}


// 二分图的问题 在于 找矛盾与不矛盾，即找 X 部 与 Y 部;
