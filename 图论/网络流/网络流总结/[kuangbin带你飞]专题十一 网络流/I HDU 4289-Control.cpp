#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define read(a) scanf("%d", &a)
#define readl(a) scanf("%lld", &a)
#define reads(a) scanf("%s", a)
#define readc(a) scanf("%c", &a)
#define pb push_back
#define mem(a) memset(a, 0, sizeof(a))
#define Buff ios::sync_with_stdio(false)
typedef long long ll;
using namespace std;
//template<class T>   inline T min(T a, T b) {return a > b ? b : a;}
//template<class T>   inline T max(T a, T b) {return a > b ? a : b;}
const int INF = 2e9 + 7;
const int N = 1e5 + 7;
const int M = 2e6 + 7;
int n, m, S, T;
int head[N], cnt, d[N];
//queue<int> q;
struct edge
{
    int to, nex, w;
    edge(int to = 0, int w = 0, int nex = 0):to(to), w(w), nex(nex){}
}e[M];

inline void addedge(int u, int v, int w)
{
    e[++cnt] = edge(v, w, head[u]); head[u] = cnt;
    e[++cnt] = edge(u, 0, head[v]); head[v] = cnt;
}

void buildGraph()
{
    mem(head); cnt = 1;

    int u, v, x;
    S = 0, T = n << 1 | 1;
    read(u); read(v);
    addedge(S, u, INF);
    addedge(v + n, T, INF);

    for(int i = 1; i <= n; i++)
    {
        read(x);
        addedge(i, i + n, x);
    }
    for(int i = 1; i <= m; i++)
    {
        read(u); read(v);
        addedge(u + n, v, INF);
        addedge(v + n, u, INF);
    }
}

int q[N << 1];
bool bfs()
{
    mem(d);
    int u, v, Head = 0, Tail = 0;
    q[Tail++] = S; d[S] = 1;
    while(Head < Tail)
    {
        u = q[Head++];
        for(int i = head[u]; i; i = e[i].nex)
        {
            v = e[i].to;
            if(e[i].w <= 0 || d[v]) continue;
            d[v] = d[u] + 1;
            q[Tail++] = v;
            if(v == T) return 1;
        }
    }
    return 0;
}

int dfs(int u, int flow)
{
    if(u == T) return flow;
    int rest = flow, k, v, w;
    for(int i = head[u]; i && rest; i = e[i].nex)
    {
        v = e[i].to, w = e[i].w;
        if(!w || d[v] != d[u] + 1) continue;
        k = dfs(v, min(rest, e[i].w));
        if(!k) d[v] = 0;
        e[i].w -= k;
        e[i ^ 1].w += k;
        rest -= k;
    }
    return flow - rest;
}

void Dinic()
{
    buildGraph();
    int flow = 0, maxflow = 0;
    while(bfs())
        while(flow = dfs(S, INF))
            maxflow += flow;
    printf("%d\n", maxflow);
}

int main()
{
    while(~scanf("%d%d", &n, &m))
        Dinic();
    return 0;
}
