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
const int _N = 1e3 + 7;
const int M = 1e6 + 7;
ll dis[N], flow[N];;
int head[N], cnt, Inq[N], pre[N];
int S, T, SS, n, m;
ll maxFlow, maxCost;
struct cmp
{
    bool operator()(int a,int b)
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
        to = _to; nex = _nex;
        w = _w; cost = _cost;
    }
}e[M];

void addedge(int u, int v, ll w, ll cost)
{
    e[++cnt] = edge(v, w, cost, head[u]); head[u] = cnt;
//    cout << u << " " << v << " " << w << endl;
    e[++cnt] = edge(u, 0ll, -cost, head[v]); head[v] = cnt;
}

bool SPAF()
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
    maxCost += flow[T] * dis[T];
}

struct Line
{
    int x, y;
    Line(int x = 0, int y = 0):x(x),y(y){}
    bool operator<(const Line L)const{
        return x < L.x || (x == L.x && y < L.y);
    }
}a[_N];

//½¨Í¼Ò» O(n^2)
//void buildGraph()
//{
//    maxFlow = maxCost = 0;
//    cnt = 1; mem(head);
//    int K;
//    read(n); read(K);
//    S = 0; SS = 2 * n + 1; T = SS + 1;
//    addedge(S, SS, K, 0);
//    for(int i = 1; i <= n; i++)
//    {
//        read(a[i].x); read(a[i].y);
//        if(a[i].x > a[i].y) swap(a[i].x, a[i].y);
//        addedge(SS, i, INF, 0);
//        addedge(i + n, T, INF, 0);
//    }
//    sort(a + 1, a + n + 1);
//    for(int i = 1; i <= n; i++)
//    {
//        addedge(i, i + n, 1, a[i].y - a[i].x);
//        for(int j = i + 1; j <= n; j++)
//            if(a[i].y <= a[j].x) addedge(i + n, j, INF, 0);
//    }
//}

// ½¨Í¼2 O(n)
int L[_N], R[_N], X[_N];
void buildGraph()
{
    int K = 0;
    mem(head); cnt = 1;
    read(n); read(K);
    for(int i = 1; i <= n; i++)
    {
        read(L[i]); read(R[i]);
        if(L[i] > R[i]) swap(L[i], R[i]);
        X[++X[0]] = L[i];
        X[++X[0]] = R[i];
    }
    sort(X + 1, X + X[0] + 1);
    X[0] = unique(X + 1, X + X[0] + 1) - X - 1;
    S = 0; T = X[0] + 1;
    addedge(S, 1, K, 0);
    for(int i = 1; i < X[0]; i++)
        addedge(i, i + 1, K, 0);
    addedge(X[0], T, K, 0);
    for(int i = 1; i <= n; i++)
    {
        int l = lower_bound(X + 1, X + X[0] + 1, L[i]) - X;
        int r = lower_bound(X + 1, X + X[0] + 1, R[i]) - X;
//        cout << R[i] - L[i] << endl;
        addedge(l, r, 1ll, R[i] - L[i]);
    }
}
signed main()
{
    buildGraph();
    while(SPAF())   update();
    printf("%lld\n", maxCost);
    return 0;
}

