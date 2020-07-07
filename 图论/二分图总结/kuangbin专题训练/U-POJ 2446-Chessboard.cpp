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
const int N = 40 * 40;
const int M = 1e6 + 7;
const double eps = 1e-8;
int n, m, k, dfn;
int dir[2][4] = {{0, 0, 1, -1}, {1, -1, 0, 0}};
int flag[N], vis[N], match[N];
vector<int> G[N];

inline int ID(int x, int y)
{
    int id = (x - 1) * m + y;
    if(x < 1 || x > n || y < 1 || y > m || flag[id]) return -1;
    return id;
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

bool work()
{
    mem(flag);

    for(int i = 1; i <= k; i++)
    {
        int x, y;
        read(x); read(y);
        flag[ID(y, x)] = 1;
    }
    int ans = n * m - k;
    if(ans & 1) return false;

    for(int i = 0; i <= n * m; i++)
    {
        G[i].clear(); match[i] = 0;
    }

    for(int x = 1; x <= n; x++)
    {
        int id1, id2, lx, ly;
        for(int y = 1; y <= m; y++)
        {
            id1 = ID(x, y);
            if(id1 == -1 || (x + y) & 1) continue;
            for(int i = 0; i < 4; i++)
            {
                lx = x + dir[0][i];
                ly = y + dir[1][i];
                id2 = ID(lx, ly);
                if(id2 != -1 && (lx + ly) & 1) G[id1].pb(id2);
            }
        }
    }

    for(int i = 1; i <= n * m; i++)
    {
        dfn++;
        if(dfs(i)) ans -= 2;
    }

    return ans == 0;
}
signed main()
{
    while(~scanf("%d%d%d", &n, &m, &k))
        if(work()) puts("YES");
        else       puts("NO");
    return 0;
}
