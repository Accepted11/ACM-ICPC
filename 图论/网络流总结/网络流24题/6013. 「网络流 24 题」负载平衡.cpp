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
    ll a[N], flow[N];
    edge e[M];

    void addedge(int u, int v, ll cap, ll cost)
    {
        e[++cnt] = edge(v, head[u], cap, cost);
        head[u] = cnt;

        e[++cnt] = edge(u, head[v], 0, -cost);
        head[v] = cnt;
    }

    // 建图
    inline ll cal(int i, int j)
    {
        if(i > j) swap(i, j);
        return min(j*1ll - i, i*1ll + n - j);
    }

    void buildGraph(int _n, int _m, int _S, int _T)
    {
        // 初始化部分
        n = _n; m = _m;
        S = _S; T = _T;
        mem(head);
        cnt = 1;

        // 构图部分
        ll sum = 0;
        for(int i = 1; i <= n; i++)
        {
            read(a[i]);
            sum += a[i];
        }

        sum /= 1ll*n;
        for(int i = 1; i <= n; i++)
        {
            if(a[i] > sum)
            {
                addedge(S, i, a[i] - sum, 0ll);
                for(int j = 1; j <= n; j++)
                    if(a[j] <= sum) addedge(i, j, INF, cal(i, j));
            }
            else            addedge(i, T, sum-a[i], 0ll);
        }
    }

    // 找增广路
    bool SPFA()
    {
        priority_queue<int, vector<int>, cmp> q;
        for(int i = 0; i <= T; i++)
        {
            dis[i] = INF;
            Inq[i] = 0;
        }
        dis[S] = 0; Inq[S] = 1; flow[S] = INF;
        q.push(S);

        int u, v; ll cost;
        while(q.size())
        {
            u = q.top(); q.pop(); Inq[u] = 0;
            for(int i = head[u]; i; i = e[i].nex)
            {
                v = e[i].to;
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

    ll get_MCMF()
    {
        ll maxFlow = 0;
        ll minCost = 0ll;

        while(SPFA())
        {
            update();
            maxFlow += flow[T];
            minCost += flow[T] * dis[T];
        }
        return minCost;
    }
};

MCMF ways;
signed main()
{
    int n, m, S, T;

    while(~scanf("%d", &n))
    {
        ways.buildGraph(n, n, 0, n  + 1);

        printf("%lld\n", ways.get_MCMF());
    }

    return 0;
}
