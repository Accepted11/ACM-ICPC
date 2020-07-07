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
ll dis[N], flow[N];;
int head[N], cnt, Inq[N], pre[N];
int S, T, n, m;
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
    ll w, cost, ww;
    edge(int _to = 0, ll _w = 0, ll _cost = 0, int _nex = 0)
    {
        to = _to; nex = _nex;
        ww = w = _w; cost = _cost;
    }
}e[M];

void addedge(int u, int v, ll w, ll cost)
{
    e[++cnt] = edge(v, w, cost, head[u]); head[u] = cnt;
//    cout << u << " " << v << " " << w << "/" << cost << endl;
    e[++cnt] = edge(u, 0ll, -cost, head[v]); head[v] = cnt;

}

bool SPAF()
{
//    cout << S << " " << T << endl;
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

string name[101];
map<string, int> id;
void buildGraph()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        cin >> name[i];
        id[name[i]] = i;
        name[i + n] = name[i];
    }
    mem(head); cnt = 1;
    S = 1; T = n + n;
    string s1, s2;
    int id1, id2;
    for(int i = 1; i <= m; i++)
    {
        cin >> s1 >> s2;
        id1 = id[s1]; id2 = id[s2];
        if(id1 > id2) swap(id1, id2);
        if(id1 == 1 && id2 == n)
            addedge(id1 + n, id2, 2ll, 1ll);
        else
            addedge(id1 + n, id2, 1ll, 1ll);
    }
    for(int i = 1; i <= n; i++)
    {
        if(i == 1 || i == n)
            addedge(i, i + n, 2ll, 0ll);
        else
            addedge(i, i + n, 1ll, 0ll);
    }
}

int vis[N];
void show(int u, int flag)
{
    if(flag == 1)
    {
        if(u <= n)
            cout << name[u] << endl;
    }

    for(int i = head[u]; i; i = e[i].nex)
    {
        int v = e[i].to;
        if(e[i].w < e[i].ww && e[i].ww)
        {
            show(v, flag);
            ++e[i].w;
            break;
        }
    }
    if(flag == 2)
    {
        if(u < n)
            cout << name[u] << endl;
    }
}

signed main()
{
    Buff;
    buildGraph();

    maxFlow = maxCost = 0ll;
    while(SPAF())   update();
    if(maxFlow != 2ll)
        cout << "No Solution!\n";
    else
    {
        cout << maxCost << endl;
        show(S, 1);
        show(S, 2);
    }
    return 0;
}

