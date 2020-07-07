#pragma GCC optimize(2)
#include<bits/stdc++.h>

#define read(a) scanf("%d", &a)
#define pb push_back
#define mem(a) memset(a, 0, sizeof(a))
#define Buff ios::sync_with_stdio(false)
typedef long long ll;
using namespace std;
const int INF = 2e9 + 7;
const int N = 100 + 7;
int match[N], vis[N], dfn;
int _match[N], a[N], b[N];
vector<int> G[N];
int n;

void init()
{
    dfn = 0;
    for(int i = 0; i <= n; i++)
    {
        match[i] = vis[i] = 0;
        G[i].clear();
    }
    for(int u = 1; u <= n; u++)
        for(int v = 1; v <= n; v++)
        {
            int x; read(x);
            if(x)  G[u].pb(v);
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
            _match[u] = v;
            return true;
        }
    }
    return false;
}

void work()
{
    init();

    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        dfn++;
        if(dfs(i)) ans++;
    }

    if(ans < n)
    {
        printf("-1\n");
        return ;
    }

    int cnt = 0;

    for(int i = 1; i <= n; i++)
    {
        int j = 1;
        while(j <= n && match[j] != i) j++;
        if(i != j)
        {
            a[++cnt] = i; b[cnt] = j;
            swap(match[i], match[j]);
        }
    }

    printf("%d\n", cnt);
    for(int i = 1; i <= cnt; i++)
        printf("C %d %d\n", a[i], b[i]);
}

signed main()
{
    while(~read(n))
        work();
    return 0;
}
