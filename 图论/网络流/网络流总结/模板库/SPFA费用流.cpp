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
const ll INF = 1e18 + 7;
const int N = 2e4 + 7;
const int M = 2e5 + 7;
const int base = 100;
ll dis[N];
struct edge
{
    int to, nex;
    ll cap, cost;
    edge(int to = 0, int nex = 0, ll cap = 0, ll cost = 0) : to(to), nex(nex), cap(cap), cost(cost){}
};
struct cmp
{
    bool operator()(int a, int b)
    {
        return dis[a] > dis[b];
    }
};
class MCMF  // MinCostMaxFlow
{
public:
    int S, T, n, m, cnt;
    int head[N], Inq[N], pre[N];
    ll flow[N];
    edge e[M];

    void addedge(int u, int v, ll cap, ll cost)
    {
        e[++cnt] = edge(v, head[u], cap, cost);
        head[u] = cnt;
    }

    // 建图
    void buildGraph(int _n, int _m, int _S, int _T)
    {
        // 初始化部分
        n = _n; m = _m;
        S = _S; T = _T;
        mem(head);
        cnt = 1;

        // 构图部分
        for(int i = 1; i <= m; i++)
        {
            int u, v;
            ll cap, cost;
            read(u); read(v);
            readl(cap); readl(cost);

            addedge(u, v, cap, cost);
            addedge(v, u, 0ll, -cost);
        }
    }

    // 找增广路
    bool SPFA()
    {
        priority_queue<int, vector<int>, cmp> q;
        for(int i = 0; i <= n; i++)
        {
            dis[i] = INF;
            Inq[i] = 0;
        }
        dis[S] = 0; Inq[S] = 1; flow[S] = INF;
//        q.push(make_pair(-dis[S], S));
        q.push(S);

        int u, v; ll cost;
//        pair<ll, int> tmp;
        while(q.size())
        {
            u = q.top(); q.pop(); Inq[u] = 0;
//            u = tmp.second; cost = -tmp.first;
            for(int i = head[u]; i; i = e[i].nex)
            {
                v = e[i].to;
//                cout << "u = " << u << " , v = " << v << "\n";
                if(!e[i].cap) continue;
                cost = dis[u] + e[i].cost;
                if(dis[v] > cost)
                {
                    dis[v] = cost;
                    flow[v] = min(flow[u], e[i].cap);
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

    void  update()
    {
        int u = T;
        while(u != S)
        {
            int i = pre[u];
            e[i].cap -= flow[T];
            e[i^1].cap += flow[T];
            u = e[i^1].to;
        }
    }

    pair<ll, ll> get_MCMF()
    {
        ll maxFlow = 0;
        ll minCost = 0ll;

        while(SPFA())
        {
            update();
            maxFlow += flow[T];
            minCost += flow[T] * dis[T];
        }
        return make_pair(minCost, maxFlow);
    }
};

MCMF ways;
signed main()
{
    int n, m, S, T;

    while(~scanf("%d%d%d%d", &n, &m, &S, &T))
    {
        ways.buildGraph(n, m, S, T);
        pair<ll, ll> tmp = ways.get_MCMF();

        printf("%lld %lld\n", tmp.second, tmp.first);
    }

    return 0;
}
