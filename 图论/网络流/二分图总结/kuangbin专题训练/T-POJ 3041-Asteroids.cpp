#pragma GCC optimize(2)
#include<bits/stdc++.h>

#define read(a) scanf("%d", &a)

#define pb push_back
#define mem(a) memset(a, 0, sizeof(a))
#define Buff ios::sync_with_stdio(false)
typedef long long ll;
using namespace std;
const int INF = 2e9 + 7;
const int N = 500 + 7;
const int M = 1e6 + 7;
const double eps = 1e-8;
int n, k, dfn;
int match[N], vis[N];
vector<int> G[N];
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
    for(int i = 0; i <= n; i++) G[i].clear(), match[i] = 0;

    while(k--)
    {
        int x, y;
        read(x); read(y);
        G[x].pb(y);
    }

    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        dfn++;
        if(dfs(i)) ans++;
    }

    printf("%d\n", ans);
}
signed main()
{
    while(~scanf("%d%d", &n, &k))
        work();
    return 0;
}
