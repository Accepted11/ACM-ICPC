#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define read(a) scanf("%d", &a)
#define pb push_back
#define mem(a) memset(a, 0, sizeof(a))
#define Buff ios::sync_with_stdio(false)
typedef long long ll;
using namespace std;
const int INF = 2e9 + 7;
const int N = 44;
const int M = 11;
const double eps = 1e-8;

char mp[N][M];
int match[N * M], vis[N * M], dfn;
int n, m, ans;
int dir[2][4] = {{0, 0, 1, -1}, {1, -1, 0, 0}};
int ID(int x, int y)
{
    if(x < 1 || x > n || y < 1 || y > m || mp[x][y] == 'o')
        return -1;
    return m * (x - 1) + y;
}

vector<int> G[N * M];

void init()
{
    read(n); read(m);

    ans = dfn = 0;
    for(int i = 0; i <= n * m; i++)
    {
        match[i] = vis[i] = 0;
        G[i].clear();
    }

    for(int i = 1; i <= n; i++) reads(mp[i] + 1);
    for(int x = 1; x <= n; x++)
    {
        int id1, id2, lx, ly;
        for(int y = 1; y <= m; y++)
        {
            if(mp[x][y] == 'o') continue;
            id1 = ID(x, y);
            ans++;
            for(int i = 0; i < 4; i++)
            {
                lx = x + dir[0][i];
                ly = y + dir[1][i];
                id2 = ID(lx, ly);
                if(id2 != -1) G[id1].pb(id2);
            }
        }
    }
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

    int cnt = 0;
    for(int i = 1; i <= n * m; i++)
    {
        dfn++;
        if(dfs(i)) cnt++;
    }
    printf("%d\n", ans - cnt / 2);
}
signed main()
{
    int t; read(t);
    while(t--)
        work();
    return 0;
}
