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
const int N = 660;
const int M = 1e6 + 7;
const double eps = 1e-8;
int n;
ll dfn, vis[N * N];
vector<int> G[N * N];
int match[N * N];
char mp[N][N];
int dir[2][4] = {{1, -1, 0, 0}, {0, 0, 1, -1}};

int ID(int x, int y)
{
    if(x < 1 || x > n || y < 1 || y > n || mp[x][y] == '.') return -1;
    return n * (x - 1) + y;
}

void init()
{
    for(int i = 0; i <= n * n; i++)
    {
        vis[i] = 0;
        match[i] = 0;
        G[i].clear();
    }
    dfn = 0;
}

int dfs(int u)
{
    for(int v : G[u])
    {
        if(vis[v] == dfn) continue;
        vis[v] = dfn;
        if(!match[v] || dfs(match[v]))
        {
            match[v] = u;
            return 1;
        }
    }
    return 0;
}

int work()
{
    init();
    int ans = 0;

    cin >> n;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            cin >> mp[i][j];

    for(int x = 1; x <= n; x++)
    {
        int id1, id2;
        for(int y = 1; y <= n; y++)
        {
            id1 = ID(x, y);
            if(id1 == -1 || (x + y) % 2) continue;
            for(int i = 0; i < 4; i++)
            {
                int lx = x + dir[0][i];
                int ly = y + dir[1][i];
                id2 = ID(lx, ly);
                if(id2 != -1 && (lx + ly) % 2)
                    G[id1].pb(id2);
            }
        }
    }

    for(int x = 1; x <= n; x++)
    {
        for(int y = 1; y <= n; y++)
        {
            int id = ID(x, y);
            if(id != -1 && (x + y) % 2 == 0)
            {
                ++dfn;
                ans += dfs(id);
            }
        }
    }
    return ans;
}


signed main()
{
    Buff;
    int t;
    cin >> t;
    for(int i = 1; i <= t; i++)
        cout << "Case " << i << ": " << work() << endl;
    return 0;
}
