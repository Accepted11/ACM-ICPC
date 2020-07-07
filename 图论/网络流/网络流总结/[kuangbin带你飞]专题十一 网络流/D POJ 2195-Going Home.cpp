/*
真不敢相信
   addedge() 又 打错了
        e[++cnt] = edge(u, 1ll, -cost, head[v]); head[v] = cnt;
不应该是               ( , 0ll,      ,        );              ;
*/
#pragma GCC optimize(2)
//#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<cstring>
#include<queue>
#include<algorithm>

#define read(a) scanf("%d", &a)
#define readl(a) scanf("%lld", &a)
#define reads(a) scanf("%s", a)
#define readc(a) scanf("%c", &a)
#define pb push_back
#define mem(a) memset(a, 0, sizeof(a))
#define Buff ios::sync_with_stdio(false)
typedef long long ll;
using namespace std;
const ll INF = 1e9 + 7;
const int N = 1e3 + 7;
const int M = 1e5 + 7;

ll dis[N], flow[N];
int head[N], Inq[N], pre[N];
int S, T, n, m, cnt;
char mp[N][N];
ll maxFlow, minCost;

inline int Abs(int x){return x > 0 ? x : -x;}
struct point
{
    int x, y;
    point(int x = 0, int y = 0) : x(x), y(y) {}
}A[N], B[N];

struct cmp
{
    bool operator()(int a, int b)
    {
        return dis[a] > dis[b];
    }
};
priority_queue<int,vector<int>,cmp> q;
struct edge
{
    int to, nex;
    ll w, cost;
    edge(int _to = 0, ll _w = 0, ll _cost = 0, int _nex = 0)
    {
        to = _to; w = _w;
        cost = _cost; nex = _nex;
    }
}e[M];
void addedge(int u, int v, ll w, ll cost)
{
    e[++cnt] = edge(v, w, cost, head[u]); head[u] = cnt;
//    printf("\ncnt = %d\nu = %d, v = %d, w = %lld, cost = %lld\n",
//                    cnt,     u,      v,      w,             cost);
    e[++cnt] = edge(u, 0ll, -cost, head[v]); head[v] = cnt;
}

void buildGraph()
{
    maxFlow = minCost = 0ll;
    cnt = 1; mem(head);
    int cnt1 = 0, cnt2 = 0;

    for(int i = 0; i < n; i++)  reads(mp[i]);
    for(int x = 0; x < n; x++)
        for(int y = 0; y < m; y++)
        {
            if(mp[x][y] == 'H') A[++cnt1] = point(x + 1, y + 1);
            if(mp[x][y] == 'm') B[++cnt2] = point(x + 1, y + 1);
        }

    S = 0, T = cnt1 + cnt2 + 1;
    for(int i = 1; i <= cnt1; i++) addedge(S, i, 1, 0);
    for(int i = cnt1 + 1; i <= cnt1 + cnt2; i++) addedge(i, T, 1, 0);
    for(int i = 1; i <= cnt1; i++)
        for(int j = 1; j <= cnt2; j++)
            addedge(i, j + cnt1, 1, Abs(A[i].x - B[j].x) + Abs(A[i].y - B[j].y));
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
    while(q.size())
    {
        u = q.top(); q.pop(); Inq[u] = 0;
        for(int i = head[u]; i; i = e[i].nex)
        {
            if(!e[i].w) continue;
            v = e[i].to;
//            cout << u << " " << v << endl;
            if(dis[v] > dis[u] + e[i].cost)
            {
                dis[v] = dis[u] + e[i].cost;
                flow[v] = min(flow[u], e[i].w);
                pre[v] = i;
                if(!Inq[v])
                {
                    q.push(v);
                    Inq[v] = 1;
//                    printf("dis[%d] = %lld\n", v, dis[v]);
//                    cout << v << " is pushed in queue\n";
                }
            }
        }
    }
//    cout << "YES\n";
    return dis[T] != INF;
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
//    cout << "YES\n";
}

signed main()
{
    while(~scanf("%d%d", &n, &m))
        if(n == 0 || m == 0) break;
        else
        {
            buildGraph();
            while(SPAF()) update();
            printf("%lld\n", minCost);
        }
    return 0;
}

