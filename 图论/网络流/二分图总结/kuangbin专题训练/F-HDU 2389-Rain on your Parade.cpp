#pragma GCC optimize(2)
#include<bits/stdc++.h>

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
#define mem(a, b) memset(a, b, sizeof(a))
#define Buff ios::sync_with_stdio(false)
typedef long long ll;
using namespace std;
const int INF = 2e9 + 7;
const int N = 3000 + 7;
const int M = 1000 + 7;
const double eps = 1e-8;

vector<int> G[N];
int dx[N], dy[N];
int lx[N], ly[N];
int vis[N], dis;
int nx;
int n, m;
double T;

struct point
{
    double x, y, v;
    point(double x = 0, double y = 0, double v = 0) : x(x), y(y), v(v) {}
}p1[N], p2[N];

double getDis(const point &A, const point &B)
{
    double x = A.x - B.x;
    double y = A.y - B.y;
    return sqrt(x * x + y * y);
}

void init()
{
    readf(T);
    read(n);
    for(int i = 1; i <= n; i++)
    {
        readf(p1[i].x);
        readf(p1[i].y);
        readf(p1[i].v);
    }
    read(m);
    for(int i = 1; i <= m; i++)
    {
        readf(p2[i].x);
        readf(p2[i].y);
    }

    for(int i = 0; i < N; i++) G[i].clear();
    nx = n;

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
        {
            if(getDis(p1[i], p2[j]) <= p1[i].v * T)
                G[i].pb(j);
        }
}

int bfs()
{
    queue<int> q;
    while(q.size()) q.pop();
    dis = INF;
    mem(dx, -1); mem(dy, -1);
    for(int i = 1; i <= nx; i++)
        if(lx[i] == -1)  q.push(i), dx[i] = 0;

    while(q.size())
    {
        int u = q.front(); q.pop();
        if(dx[u] > dis) break;
        for(int v : G[u])
        {
            if(dy[v] == -1)
            {
                dy[v] = dx[u] + 1;
                if(ly[v] == -1)      dis = dy[v];
                else
                {
                    dx[ly[v]] = dy[v] + 1;
                    q.push(ly[v]);
                }
            }
        }
    }
    return dis != INF;
}

int dfs(int u)
{
    for(int v : G[u])
    {
        if(!vis[v] && dy[v] == dx[u] + 1)
        {
            vis[v] = 1;
            if(ly[v] != -1 && dy[v] == dis) continue;
            if(ly[v] == -1 || dfs(ly[v]))
            {
                lx[u] = v;
                ly[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int HK()
{
    mem(lx, -1); mem(ly, -1);
    int ans = 0;
    int x;
    while(bfs())
    {
        mem(vis, 0);
        for(int i = 1; i <= nx; i++)
            if(lx[i] == -1)
                ans += dfs(i);
    }
    return ans;
}

signed main()
{
    int t; read(t);
    for(int i = 1; i <= t; i++)
    {
        init();
        printf("Scenario #%d:\n%d\n\n",i, HK());
    }


    return 0;
}
