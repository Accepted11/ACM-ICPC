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
const int N = 2e4 + 7;
const int M = 1e6 + 7;
int S, T, n, m;
int head[N], cnt, d[N];
int dis1[N], dis2[N], inq[N];

struct edge
{
    int to, nex, w;
    edge(int to = 0, int w = 0, int nex = 0):
        to(to), w(w), nex(nex){}
}e[M];
void addedge(int u, int v, int w)
{
    e[++cnt] = edge(v, w, head[u]); head[u] = cnt;
    e[++cnt] = edge(u, 0, head[v]); head[v] = cnt;
}

struct Edge
{
    int to, w;
    Edge(int to = 0, int w = 0):to(to), w(w){}
};
vector<Edge> G1[N], G2[N];

int q[M << 1];
void SPAF(int st, int* dis, vector<Edge> G[N])
{
    int Head = 0, Tail = 0;
    for(int i = 0; i <= n; i++)
    {
        dis[i] = INF;
        inq[i] = 0;
    }
    dis[st] = 0;
    q[Tail++] = st; inq[st] = 1;
    int u, v, cost;
    while(Head < Tail)
    {
        u = q[Head++]; inq[u] = 0;
        for(int i = 0; i < G[u].size(); i++)
        {
            v = G[u][i].to; cost = G[u][i].w + dis[u];
            if(dis[v] > cost)
            {
                dis[v] = cost;
                if(!inq[v])
                {
                    q[Tail++] = v;
                    inq[v] = 1;
                }
            }
        }
    }
}
void buildGraph()
{
    read(n); read(m);

    for(int i = 0; i <= n; i++)
        G1[i].clear(), G2[i].clear();
    for(int i = 1, u, v, w; i <= m; i++)
    {
        read(u); read(v); read(w);
        G1[u].pb(Edge(v, w)); G2[v].pb(Edge(u, w));
    }
    read(S); read(T);
    SPAF(S, dis1, G1);
//    SPAF(T, dis2, G2);
    mem(head); cnt = 1;
    for(int u = 1; u <= n; u++)
        for(int i = 0; i < G1[u].size(); i++)
        {
            int v = G1[u][i].to, w = G1[u][i].w;
            if(dis1[u] + w == dis1[v])
                addedge(u, v, 1);
        }
//    for(int i = 2; i <= cnt; i += 2)
//    {
//        cout << e[i ^ 1].to << " -- " << e[i].to << " " << e[i].w << endl;
//    }
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

bool bfs()
{
    mem(d);
    int Head = 0, Tail = 0, u, v;
    d[S] = 1; q[Tail++] = S;
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
int Dinic()
{
    int Flow = 0, maxFlow = 0;
    while(bfs())
        while(Flow = dfs(S, INF))
            maxFlow += Flow;
    return maxFlow;
}
signed main()
{
    int t; read(t);
    while(t--)
    {
        buildGraph();
        printf("%d\n", Dinic());
    }
    return 0;
}

