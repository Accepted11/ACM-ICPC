#pragma GCC optimize(2)
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
const int INF = 1e9 + 7;
const int N = 1e3 + 7;
const int M = 1e6 + 7;
int S, T, cnt, n, F, D;
int d[N], head[N], q[M << 1];
char mp[N][N];
struct edge
{
    int to, nex, w;
    edge(int to = 0, int w = 0, int nex = 0):to(to), nex(nex), w(w){}
}e[M];
inline void addedge(int u, int v, int w)
{
    e[++cnt] = edge(v, w, head[u]); head[u] = cnt;
//    cout << "\ncnt = " << cnt << endl;
//    cout << u << " " << v << " " << w << endl;
    e[++cnt] = edge(u, 0, head[v]); head[v] = cnt;
}

int dfs(int u, int flow)
{
    if(u == T) return flow;
    int rest = flow, v, k;
    for(int i = head[u]; i && rest; i = e[i].nex)
    {
        v = e[i].to;
        if(!e[i].w || d[v] != d[u] + 1) continue;
        k = dfs(v, min(rest, e[i].w));
        if(!k)  d[v] = 0;
        e[i].w -= k;
        e[i ^ 1].w += k;
        rest -= k;
    }
    return flow - rest;
}

bool bfs()
{
    mem(d);
    int Head = 0, Tail = 0, v, u;
    q[Tail++] = S; d[S] = 1;
    while(Head < Tail)
    {
        u = q[Head++];
        for(int i = head[u]; i; i = e[i].nex)
        {
            v = e[i].to;
            if(!e[i].w || d[v]) continue;
            d[v] = d[u] + 1;
            q[Tail++] = v;
            if(v == T) return 1;
        }
    }
    return 0;
}
void buildGraph()
{
    mem(head); cnt = 1;
    S = 0, T = F + n + n + D + 1;
    for(int i = 1; i <= F; i++)
    {
        int x; read(x);
        addedge(S, i, x);
    }
    for(int i = F + n + n + 1; i < T; i++)
    {
        int x; read(x);
        addedge(i, T, x);
    }
    for(int i = F + 1; i <= F + n; i++) addedge(i, i + n, 1);

    for(int i = 1; i <= n; i++)
    {
        reads(mp[i] + 1);
        for(int j = 1; j <= F; j++)
            if(mp[i][j] == 'Y') addedge(j, i + F, 1);
    }
    for(int i = 1; i <= n; i++)
    {
        reads(mp[i] + 1);
        for(int j = 1; j <= D; j++)
            if(mp[i][j] == 'Y')
                addedge(i + F + n, j + F + n + n, 1);
    }
}

int Dinic()
{
    buildGraph();
    int Flow = 0, maxFlow = 0;
    while(bfs())
        while(Flow = dfs(S, INF))
            maxFlow += Flow;
    return maxFlow;
}
signed main()
{
    while(~scanf("%d%d%d", &n, &F, &D))
        printf("%d\n", Dinic());
    return 0;
}


