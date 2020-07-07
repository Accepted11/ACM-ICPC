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
const ll INF = 1e16 + 7;
const int N = 2e5 + 7;
const int M = 1e6 + 7;
ll dis[N], flow[N];
int head[N], cnt, Inq[N], pre[N];
int S, T, n, d1, d2;
ll p, f, s;
struct edge
{
    int to, nex;
    ll w, cost;
    edge(int _to = 0, ll _w = 0, ll _cost = 0, int _nex = 0)
    {
        to = _to; nex = _nex;
        w = _w; cost = _cost;
    }
}e[M];

void addedge(int u, int v, ll w, ll cost)
{
    e[++cnt] = edge(v, w, cost, head[u]); head[u] = cnt;
    e[++cnt] = edge(u, 0ll, -cost, head[v]); head[v] = cnt;
}

queue<int> q;
bool SPAF()
{
    while(q.size()) q.pop();
    for(int i = 0; i < N; i++)
    {
        dis[i] = INF;
        Inq[i] = 0;
    }
    q.push(S); dis[S] = 0; Inq[S] = 1; flow[S] = INF;
    int u, v;
    ll cost;
    while(q.size())
    {
        u = q.front(); q.pop(); Inq[u] = 0;
        for(int i = head[u]; i; i = e[i].nex)
        {
            if(!e[i].w) continue;
            v = e[i].to; cost = dis[u] + e[i].cost;
            if(dis[v] > cost)
            {
                dis[v] = cost;
                flow[v] = min(flow[u], e[i].w);
                pre[v] = i;
                if(!Inq[v])
                {
                    q.push(v);
                    Inq[v] = 1;
                }
            }
        }
    }
    return dis[T] != INF;
}

ll maxFlow, minCost;
void update()
{
    int u = T, i;
    while(u != S)
    {
        i = pre[u];
        e[i].w -= flow[T];
        e[i ^ 1].w += flow[T];
        u = e[i ^ 1].to;
    }
    maxFlow += flow[T];
    minCost += flow[T] * dis[T];
}

void EK()
{
    maxFlow = minCost = 0ll;
    while(SPAF())
        update();
    printf("%lld\n", minCost);
}
void buildGraph()
{
    read(n); readl(p);
    read(d1); readl(f);
    read(d2); readl(s);
    mem(head); cnt = 1;
    S = 0; T = n << 1 | 1;

    for(int i = 1; i <= n; i++)
    {
        ll r; readl(r);
        addedge(S, i, r, p);
        addedge(S, i + n, r, 0ll);
        addedge(i, T, r, 0ll);
        if(i + 1 <= n)
            addedge(i + n, i + 1 + n, INF, 0ll);
        if(i + d1 <= n)
            addedge(i + n, i + d1, INF, f);
        if(i + d2 <= n)
            addedge(i + n, i + d2, INF, s);
    }
}
signed main()
{
    buildGraph();
    EK();
    return 0;
}
