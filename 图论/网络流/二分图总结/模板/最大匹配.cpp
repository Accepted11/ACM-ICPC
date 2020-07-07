#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define read(a) scanf("%d", &a)
#define readl(a) scanf("%lld", &a)
#define reads(a) scanf("%s", a)
#define readc(a) scanf("%c", &a)
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
const int INF = 1e9 + 7;
const int N = 2e5 + 7;
const int M = 1e6 + 7;
int vis[N], match[N];
int n, m;
vector<int> G[N];

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
signed main()
{
#ifndef ONLINE_JUDGE
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	long _begin_time = clock();
#endif
    Buff;

    cin >> n >> m;

    for(int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        G[u].pb(v);
        G[v].pb(u);
    }

    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        mem(vis);
        ans += dfs(i);
    }

    for(int i = 1; i <= n; i++)
    {
        if(match[i])
            printf("match[%d] = %d \n", i, match[i]);
    }
#ifndef ONLINE_JUDGE
	long _end_time = clock();
	cout << "time= " <<  _end_time - _begin_time;
#endif
    return 0;
}
