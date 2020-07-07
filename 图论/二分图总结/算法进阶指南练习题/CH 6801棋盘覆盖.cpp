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
const int N = 4e4 + 7;
const int M = 1e6 + 7;
int n, m;
vector<int> G[N];
int mp[N];
int dir[2][4] = {{1, -1, 0, 0}, {0, 0, 1, -1}};
int vis[N], match[N];

int Id(int x, int y)
{
    int id = n * (x - 1) + y;
    if(mp[id] || x < 1 || x > n || y < 1 || y > n)
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

signed main()
{
#ifndef ONLINE_JUDGE
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	long _begin_time = clock();
#endif
    read(n); read(m);

    for(int i = 1; i <= m; i++)
    {
        int x, y;
        read(x); read(y);
        mp[(x - 1) * n + y] = 1;
    }

    for(int x = 1; x <= n; x++)
    {
       for(int y = 1; y <= n; y++)
       {
           int u = Id(x, y);
           if(u == -1) continue;
           for(int i = 0; i < 4; i++)
           {
               int lx = x + dir[0][i], ly = y + dir[1][i];
               int v = Id(lx, ly);
               if(v != -1 && (lx + ly) % 2) G[u].pb(v);
           }
       }
    }

    int ans = 0;
    for(int i = 1; i <= n * n; i++)
    {
        mem(vis);
        if(dfs(i)) ans++;
    }

    printf("%d\n", ans);
#ifndef ONLINE_JUDGE
	long _end_time = clock();
	cout << "time= " <<  _end_time - _begin_time;
#endif
    return 0;
}
