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
const int N = 500 + 7;
//const int M = 1e6 + 7;
const double eps = 1e-8;

int Abs(int x)
{
    return x < 0 ? -x : x;
}
struct people
{
    int h;
    char music[110];
    char sport[110];
    bool judge(people A)
    {
        if(Abs(h - A.h) > 40) return 0;
        if(strcmp(music, A.music)) return 0;
        if(strcmp(sport, A.sport) == 0) return 0;
        return 1;
    }
}F[N], M[N];

int n, match[N], vis[N], dfn;
int cntF, cntM;

vector<int> G[N];

void init()
{
    read(n);
    dfn = cntF = cntM = 0;
    for(int i = 0; i <= n; i++)
    {
        G[i].clear();
        match[i] = vis[i] = 0;
    }

    int h;
    char str[101];
    for(int i = 1; i <= n; i++)
    {
        read(h); reads(str);
        if(str[0] == 'M')
        {
            M[++cntM].h = h;
            reads(M[cntM].music);
            reads(M[cntM].sport);

        }
        else if(str[0] == 'F')
        {
            F[++cntF].h = h;
            reads(F[cntF].music);
            reads(F[cntF].sport);
        }
    }

    for(int i = 1; i <= cntM; i++)
        for(int j = 1; j <= cntF; j++)
            if(M[i].judge(F[j])) G[i].pb(j);
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
    int ans = n;
    for(int i = 1; i <= cntM; i++)
    {
        ++dfn;
        if(dfs(i)) ans--;
    }
    printf("%d\n", ans);
}
signed main()
{
    int t; read(t);
    while(t--)
        work();
    return 0;
}
