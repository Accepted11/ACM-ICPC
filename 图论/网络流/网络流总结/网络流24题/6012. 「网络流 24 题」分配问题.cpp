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
const int N = 1e4 + 7;
const int M = 1e5 + 7;
ll dis[N], flow[N], pre[N];
int head[N], cnt, Inq[N], _head[N], _cnt;
int S, T, n, m;
ll maxFlow, minCost, maxCost;
struct cmp
{
    bool operator()(int a,int b)
    {
        return dis[a] > dis[b];
    }
};
priority_queue<int,vector<int>,cmp> q;
//queue<int> q;
struct edge
{
    int to, nex;
    ll w, cost;
    edge(int _to = 0, ll _w = 0, ll _cost = 0, int _nex = 0)
    {
        to = _to; nex = _nex;
        w = _w; cost = _cost;
    }
}e[M], _e[M];

void addedge(int u, int v, ll w, ll cost)
{
    e[++cnt] = edge(v, w, cost, head[u]); head[u] = cnt;
    e[++cnt] = edge(u, 0ll, -cost, head[v]); head[v] = cnt;
    _e[++_cnt] = edge(v, w, cost, _head[u]); _head[u] = _cnt;
    _e[++_cnt] = edge(u, 0ll, -cost, _head[v]); _head[v] = _cnt;
}
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
        u = q.top(); q.pop(); Inq[u] = 0;
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

bool _SPAF()
{
    while(q.size()) q.pop();
    for(int i = 0; i < N; i++)
    {
        dis[i] = -INF;
        Inq[i] = 0;
    }
    q.push(S); dis[S] = 0; Inq[S] = 1; flow[S] = INF;
    int u, v;
    ll cost;
    while(q.size())
    {
        u = q.top(); q.pop(); Inq[u] = 0;
        for(int i = _head[u]; i; i = _e[i].nex)
        {
            if(!_e[i].w) continue;
            v = _e[i].to; cost = dis[u] + _e[i].cost;
            if(dis[v] < cost)
            {
                dis[v] = cost;
                flow[v] = min(flow[u], _e[i].w);
                pre[v] = i;
                if(!Inq[v])
                {
                    q.push(v);
                    Inq[v] = 1;
                }
            }
        }
    }
    return dis[T] != -INF;
}

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

void _update()
{
    int u = T, i;
    while(u != S)
    {
        i = pre[u];
        _e[i].w -= flow[T];
        _e[i ^ 1].w += flow[T];
        u = _e[i ^ 1].to;
    }
    maxFlow += flow[T];
    maxCost += flow[T] * dis[T];
}

void buildGraph()
{
    read(n);
    S = 0; T = n << 1 | 1;
    ll x;
    mem(head); mem(_head);
    cnt = _cnt = 1;
    for(int i = 1; i <= n; i++)
    {
        addedge(S, i, 1ll, 0ll);
        addedge(i + n, T, 1ll, 0ll);
        for(int j = n + 1; j <= n + n; j++)
        {
            readl(x);
            addedge(i, j , 1ll, x);
        }
    }
}
signed main()
{
    buildGraph();
    maxFlow = minCost = 0;
    while(SPAF()) update();
    printf("%lld\n", minCost);

    maxFlow = maxCost = 0ll;
    while(_SPAF()) _update();
    printf("%lld\n", maxCost);
    return 0;
}

