#pragma GCC optimize(3)
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
const int N = 5 * 5;
const int M = 1e6 + 7;
const double eps = 1e-8;
char mp[N][N];
int flagx[N][N], flagy[N][N];
int vis[N], match[N];
int n, m, cntx, cnty;

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
void work()
{
    mem(flagx); mem(flagy); mem(match);
    for(int i = 0; i < N; i++)
        G[i].clear();
    cntx = cnty = 0;

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            cin >> mp[i][j];

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
//            if(mp[i][j] == 'X') continue;
            if(mp[i][j] == '.')
            {
                if(j == 1) flagx[i][j] = ++cntx;
                else       flagx[i][j] = mp[i][j - 1] == '.' ? flagx[i][j - 1] : ++cntx;
            }

            if(mp[j][i] == '.')
            {
                if(j == 1) flagy[j][i] = ++cnty;
                else       flagy[j][i] = mp[j - 1][i] == '.' ? flagy[j - 1][i] : ++cnty;
            }
        }
    }

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            G[flagx[i][j]].pb(flagy[i][j]);

    int ans = 0;
    for(int i = 1; i <= cntx; i++)
    {
        mem(vis);
        ans += dfs(i);
    }
    cout << ans << endl;
}
signed main()
{
    Buff;
    while(cin >> n)
        if(n) work();
        else  break;
//        work();
    return 0;
}
