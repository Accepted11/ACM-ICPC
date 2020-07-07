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
const int N = 1e3 + 7;
const int M = 1e6 + 7;
int n, m, k;

vector<int> G[N];
int match[N], vis[N];
int mp[N][N];

bool dfs(int u)
{
//    cout << "u = " << u << endl;
    for(int v : G[u])
    {
        if(vis[v]) continue;
        vis[v] = 1;
//        cout << u << "---" << v << endl;
        if(!match[v] || dfs(match[v]))
        {
            match[v] = u;
//            cout << u << "---" << v << "is matched\n";
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

    cin >> n >> m >> k;
    for(int i = 1, x, y; i <= k; i++)
    {
        cin >> x >> y;
        mp[x][y] = 1;
    }

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(mp[i][j] == 0)   G[i].pb(j);
        }
    }


    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        mem(vis);
        ans += dfs(i);
    }
    cout << ans << endl;
#ifndef ONLINE_JUDGE
	long _end_time = clock();
	cout << "time= " <<  _end_time - _begin_time;
#endif
    return 0;
}
