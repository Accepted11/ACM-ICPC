#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define read(a) scanf("%d", &a)
#define mem(a) memset(a, 0, sizeof(a))
#define pb push_back
typedef long long ll;
using namespace std;
const int INF = 2e9 + 7;
const int N = 1e5 + 10;
const int M = 1e6 + 7;
int n, m, k;
int match[N], vis[N], flag[N];
int dir[2][8] = {{-2, -2, 2 , 2, -1, -1, 1, 1},
                 {1, -1, 1, -1, -2, 2, -2 , 2}};
vector<int> G[N];

inline int ID(int x, int y)
{
    int id = (x - 1) * m + y;
    if(x < 1 || x > n || y < 1 || y > m || flag[id])
        return -1;
    return id;
}

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
    for(int i = 1; i <= k; i++)
    {
        int x, y;
        read(x); read(y);
        flag[ID(x, y)] = 1;
    }

    for(int x = 1; x <= n; x++)
    {
        int lx, ly, id1, id2;
        for(int y = 1; y <= m; y++)
        {
            id1 = ID(x, y);
            if(id1 == -1 || (x + y) & 1) continue;
            for(int i = 0; i < 8; i++)
            {
                lx = x + dir[0][i];
                ly = y + dir[1][i];
                id2 = ID(lx, ly);
                if(id2 != -1) G[id1].pb(id2);
            }
        }
    }
}

signed main()
{
    read(n);  read(k);
    m = n;
    init();

    int ans = 0;
    for(int i = 1; i <= n * m; i++)
    {
        mem(vis);
        if(dfs(i)) ans++;
    }

    printf("%d", n * m - ans - k);
    return 0;
}
