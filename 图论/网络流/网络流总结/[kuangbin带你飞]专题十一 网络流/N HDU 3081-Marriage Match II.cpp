#pragma GCC optimize(2)
#include<bits/stdc++.h>
/*
    这个题一定要保证完备匹配(所有girl都有男朋友)这个条件，
    故，S --> i , i + n --> T 的权值为 mid
*/
#define read(a) scanf("%d", &a)
#define readl(a) scanf("%lld", &a)
#define reads(a) scanf("%s", a)
#define readc(a) scanf("%c", &a)
#define pb push_back
#define mem(a) memset(a, 0, sizeof(a))
#define Buff ios::sync_with_stdio(false)
typedef long long ll;
using namespace std;
const int INF = 1e9 + 7;
const int N = 200 + 7;
const int M = 1e6 + 7;
int S, T, n, m, f, cnt;
int dp[N][N], head[N], d[N];

struct edge
{
    int to, nex, w;
    edge(int to = 0, int w = 0, int nex = 0):
        to(to), w(w), nex(nex){}
}e[M];
inline void addedge(int u, int v, int w)
{
    e[++cnt] = edge(v, w, head[u]); head[u] = cnt;
    e[++cnt] = edge(u, 0, head[v]); head[v] = cnt;
}
void init()
{
    read(n); read(m); read(f);
    mem(dp);
    for(int i = 1, u, v; i <= m; i++)
    {
        read(u); read(v);
        dp[u][v + n] = 1;
    }
    for(int i = 1, u, v; i <= f; i++)
    {
        read(u); read(v);
        dp[u][v] = dp[v][u] = 1;
    }
    for(int k = 1; k <= n + n; k++)
        for(int i = 1; i <= n + n; i++)
            for(int j = 1; j <= n + n; j++)
                dp[i][j] |= (dp[i][k] & dp[k][j]);
    S = 0; T = n << 1 | 1;
}

void buildGraph(int mid)
{
    mem(head); cnt = 1;
    for(int i = 1; i <= n; i++)
    {
        addedge(S, i, mid);
        addedge(i + n, T, mid);
    }
    for(int i = 1; i <= n; i++)
        for(int j = n + 1; j < T; j++)
            if(dp[i][j]) addedge(i, j, 1);
}

int q[M << 1];
bool bfs()
{
    mem(d);
    int Head = 0, Tail = 0, u, v;
    q[Tail++] = S; d[S] = 1;
    while(Head < Tail)
    {
        u = q[Head++];
        for(int i = head[u]; i; i = e[i].nex)
        {
            v = e[i].to;
            if(!e[i].w || d[v]) continue;
            q[Tail++] = v;
            d[v] = d[u] + 1;
            if(v == T) return true;
        }
    }
    return false;
}
int dfs(int u, int flow)
{
    if(u == T) return flow;
    int rest = flow, k, v;
    for(int i = head[u]; i && rest; i = e[i].nex)
    {
        v = e[i].to;
        if(!e[i].w || d[v] != d[u] + 1) continue;
        k = dfs(v, min(rest, e[i].w));
        if(!k) d[v] = 0;
        e[i].w -= k;
        e[i ^ 1].w += k;
        rest -= k;
    }
    return flow - rest;
}
bool Dinic(int mid)
{
    buildGraph(mid);
    int Flow = 0, maxFlow = 0;
    while(bfs())
        while(Flow = dfs(S, INF))   maxFlow += Flow;
    return mid * n == maxFlow;
}
signed main()
{
    int t; read(t);
    while(t--)
    {
        init();
        int l = 0, r = 1000, mid, ans = 0;
        while(l <= r)
        {
            mid = l + r >> 1;
            if(Dinic(mid)) ans = mid, l = mid + 1;
            else           r = mid - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}

