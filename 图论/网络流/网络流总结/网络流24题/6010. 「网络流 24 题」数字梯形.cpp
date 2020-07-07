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
int a[30][30], id[30][30];

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
        return dis[a] < dis[b];
    }
};
class MCMF  // MinCostMaxFlow
{
public:
    int S, T, n, m, cnt, ntot;
    int head[N], Inq[N], pre[N];
    ll flow[N];
    edge e[M];

    void addedge(int u, int v, ll cap, ll cost)
    {
        e[++cnt] = edge(v, head[u], cap, cost);
        head[u] = cnt;

        e[++cnt] = edge(u, head[v], 0ll, -cost);
        head[v] = cnt;
    }

    // 建图
    void buildGraph(int _n, int _m)
    {
        // 初始化部分
        n = _n; m = _m;

        // 构图部分
        ntot = 0;
        for(int j = 1; j <= m; j++)
            for(int i = 1; i < n + j; i++)
                read(a[j][i]), id[j][i] = ++ntot;


        /** Pro 1 **/
        mem(head); cnt = 1;
        S = 0; T = ntot<<1|1;
        for(int i = 1; i <= m; i++)
            for(int j = 1; j < n + i; j++)
            {
                addedge(id[i][j], id[i][j] + ntot, 1ll, 0ll);   // 拆点

                if(i == 1) addedge(S, id[i][j], 1ll, 0ll);
                else
                {
                    if(i == m) addedge(id[i][j] + ntot, T, 1ll,  a[i][j]);
                    if(j != n + i - 1) addedge(id[i-1][j]+ntot, id[i][j], 1ll, a[i-1][j]);
                    if(j != 1)  addedge(id[i-1][j-1]+ntot, id[i][j], 1ll, a[i-1][j-1]);
                }
            }
        printf("%lld\n", get_MCMF());
        /** Pro 2 **/
        mem(head); cnt = 1;
        S = 0; T = ntot + 1;
        for(int i = 1; i <= m; i++)
            for(int j = 1; j < n + i; j++)
            {
                if(i == 1) addedge(S, id[i][j], 1ll, 0ll);
                else
                {
                    if(i == m) addedge(id[i][j], T, INF,  a[i][j]);
                    if(j != n + i - 1) addedge(id[i-1][j], id[i][j], 1ll, a[i-1][j]);
                    if(j != 1)  addedge(id[i-1][j-1], id[i][j], 1ll, a[i-1][j-1]);
                }
            }
        printf("%lld\n", get_MCMF());
        /** Pro 3 **/
        mem(head); cnt = 1;
        S = 0; T = ntot + 1;
        for(int i = 1; i <= m; i++)
            for(int j = 1; j < n + i; j++)
            {
                if(i == 1) addedge(S, id[i][j], 1ll, 0ll);
                else
                {
                    if(i == m) addedge(id[i][j], T, INF,  a[i][j]);
                    if(j != n + i - 1) addedge(id[i-1][j], id[i][j], INF, a[i-1][j]);
                    if(j != 1)  addedge(id[i-1][j-1], id[i][j], INF, a[i-1][j-1]);
                }
            }
        printf("%lld\n", get_MCMF());
    }

    // 找增广路
    bool SPFA()
    {
        priority_queue<int, vector<int>, cmp> q;
        for(int i = 0; i <= T; i++)
        {
            dis[i] = -INF;
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
                if(!e[i].cap) continue;
                cost = dis[u] + e[i].cost;
                if(dis[v] < cost)
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
        return dis[T] != -INF;
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
        ll maxCost = 0ll;

        while(SPFA())
        {
            update();
            maxFlow += flow[T];
            maxCost += flow[T] * dis[T];
        }

        return maxCost;
    }
};

MCMF ways;
signed main()
{
    int n, m, S, T;

    while(~scanf("%d%d", &n, &m))
    {
        ways.buildGraph(n, m);
    }

    return 0;
}
