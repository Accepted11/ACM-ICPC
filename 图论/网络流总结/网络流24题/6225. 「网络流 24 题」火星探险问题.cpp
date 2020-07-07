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
int S, T, n, m, cars;
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

int mp[_N][_N], id[_N][_N], tot, base;
void buildGraph()
{
    read(cars); read(m); read(n);
    cnt = 1; mem(head);
    S = 0; T = n * m * 2 + 1;
    tot = 0;    base = n * m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
        {
            read(mp[i][j]);
            id[i][j] = ++tot;
        }
    addedge(S, id[1][1], cars, 0);
    addedge(id[n][m] + base, T, cars, 0);

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
        {
            if(mp[i][j] == 1)   continue;
            addedge(id[i][j], id[i][j] + base, INF, 0);
            if(mp[i][j] == 2)
                addedge(id[i][j], id[i][j] + base, 1, 1);
            if(i != n && mp[i + 1][j] != 1)
                addedge(id[i][j] + base, id[i + 1][j], INF, 0);
            if(j != m && mp[i][j + 1] != 1)
                addedge(id[i][j] + base, id[i][j + 1], INF, 0);
        }
}

// i --- > j µÄ ·½Ê½
inline int getTurn(int i, int j)
{
    return (i % m != j % m);
}
void show(int u, int x)
{
    if(u == id[n][m]) return;
    for(int i = head[u + base]; i; i = e[i].nex)
    {
        if(i&1 || !e[i ^ 1].w) continue;
        int v = e[i].to;
        printf("%d %d\n", x, getTurn(u, v));
        e[i ^ 1].w--;
        show(v, x);
        return;
    }
}
signed main()
{
    buildGraph();

    maxFlow = maxCost = 0;
    while(SPAF())   update();
    for(int i = 1; i <= cars; i++)
        show(1, i);
    return 0;
}

