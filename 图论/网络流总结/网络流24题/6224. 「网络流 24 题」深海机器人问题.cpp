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
const int N = 1e5 + 7;
const int M = 1e6 + 7;
const int _N = 100 + 7;
int dis[N], flow[N];;
int head[N], cnt, Inq[N], pre[N];
int S, T, n, m;
int maxFlow, maxCost;

struct edge
{
    int to, nex, w, cost, ww;
    edge(int _to = 0, int _w = 0, int _cost = 0, int _nex = 0)
    {
        to = _to; nex = _nex;
        ww = w = _w; cost = _cost;
    }
}e[M];

void addedge(int u, int v, int w, int cost)
{
    e[++cnt] = edge(v, w, cost, head[u]); head[u] = cnt;
//    cout << u << " " << v << endl;
    e[++cnt] = edge(u, 0ll, -cost, head[v]); head[v] = cnt;
}

queue<int> q;
bool SPAF()
{
    while(q.size()) q.pop();
    for(int i = 0; i < N; i++)
    {
        dis[i] = -INF;
        Inq[i] = 0;
    }
    q.push(S); dis[S] = 0; Inq[S] = 1; flow[S] = INF;
    int u, v, cost;
    while(q.size())
    {
        u = q.front(); q.pop(); Inq[u] = 0;
        for(int i = head[u]; i; i = e[i].nex)
        {
            if(!e[i].w) continue;
            v = e[i].to; cost = dis[u] + e[i].cost;
            if(dis[v] < cost)
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
//    cout << "dis[T] = " << dis[T] << endl;
    maxCost += flow[T] * dis[T];
}

int tot, base;
int getId(int x, int y)
{
//    cout << "id = " << (x - 1) * m + y << endl;
    return (x - 1) * m + y;
}
void buildGraph()
{
    int a, b; read(a); read(b);
    read(n); read(m);
    n++; m++;
    cnt = 1; mem(head);
    S = 0; T = n * m + 1;
    for(int i = 1; i <= n; i++)
        for(int j = 1, x; j < m; j++)
        {
            read(x);
            int id1 = getId(i, j), id2 = getId(i, j + 1);
            addedge(id1, id2, 1, x);
            addedge(id1, id2, INF, 0);
        }
    for(int j = 1; j <= m; j++)
        for(int i = 1, x; i < n; i++)
        {
            read(x);
            int id1 = getId(i, j), id2 = getId(i + 1, j);
            addedge(id1, id2, 1, x);
            addedge(id1, id2, INF, 0);
        }
    for(int i = 1, k, x, y; i <= a; i++)
    {
        read(k); read(x); read(y);
        addedge(S, getId(x + 1, y + 1), k, 0);
    }
    for(int i = 1, k, x, y; i <= b; i++)
    {
        read(k); read(x); read(y);
        addedge(getId(x + 1, y + 1), T, k, 0);
    }
}

signed main()
{
    buildGraph();
//    cout << "cnt = " << cnt << endl;
    maxFlow = maxCost = 0;
    while(SPAF())   update();
    printf("%d\n", maxCost);
    return 0;
}
