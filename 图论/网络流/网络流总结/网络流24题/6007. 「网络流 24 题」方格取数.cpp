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
const int INF = 2e9 + 7;
const int N = 2e4 + 7;
const int M = 2e5 + 7;
const int base = 100;

struct edge
{
    int to, nex, cap;
    edge(int to = 0, int nex = 0, int cap = 0) : to(to), nex(nex), cap(cap){}
};

class ISAP
{
public:
    int S, T, n, m, cnt, sum;
    int head[N], d[N], cur[N], gap[N];
    edge e[M];

    void addedge(int u, int v, int cap)
    {
        e[++cnt] = edge(v, head[u], cap);
        head[u] = cnt;

        e[++cnt] = edge(u, head[v], 0);
        head[v] = cnt;
    }

    // 建图
    void buildGraph(int _n, int _m, int _S, int _T)
    {
        // 初始化部分
        n = _n; m = _m;
        S = _S; T = _T;
        mem(head);
        cnt = 1; sum = 0;

        // 构图部分
        int ntot = 0, cap;
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                read(cap);
                ++ntot; sum += cap;
                if((i + j) % 2)
                {
                    addedge(S, ntot, cap);
                    if(i - 1 > 0)  addedge(ntot, ntot - m, INF);
                    if(i + 1 <= n) addedge(ntot, ntot + m, INF);
                    if(j - 1 > 0) addedge(ntot, ntot - 1, INF);
                    if(j + 1 <= m) addedge(ntot, ntot + 1, INF);
                }
                else    addedge(ntot, T, cap);
            }
        }
    }

    // 找增广路
    void bfs()
    {
        mem(d); mem(gap);
        queue<int> q;
        q.push(T);
        d[T] = gap[1] = 1;

        int u, v;
        while(q.size())
        {
            u = q.front(); q.pop();
            for(int i = head[u]; i; i = e[i].nex)
            {
                v = e[i].to;
                if(d[v]) continue;
                q.push(v);
                d[v] = d[u] + 1;
                ++gap[d[v]];
            }
        }

        for(int i = 0; i <= T; i++) cur[i] = head[i];
    }

    int dfs(int u, int flow)
    {
        if(u == T) return flow;

        int delta = 0, tmp;
        for(int& i = cur[u]; i; i = e[i].nex)
        {
//            cur[u] = i;
            int v = e[i].to;
            if(d[u] != d[v] + 1 || e[i].cap <= 0) continue;

            int tmp = dfs(v, min(flow - delta, e[i].cap));
            if(tmp <= 0) continue;

            e[i].cap -= tmp;
            e[i^1].cap += tmp;
            delta += tmp;

            if(delta == flow) return delta;
        }

        if(--gap[d[u]] == 0) d[S] = T + 1;
        ++gap[++d[u]];
        cur[u] = head[u];

        return delta;
    }

    int get_maxFlow()
    {
        bfs();

        int maxFlow = 0;
        while(d[S] <= T) maxFlow += dfs(S, INF);

        return sum - maxFlow;
    }
};

ISAP ways;
signed main()
{
    int n, m, S, T;

    while(~scanf("%d%d", &n, &m))
    {
        ways.buildGraph(n, m, 0, n * m + 1);
        printf("%d\n", ways.get_maxFlow());
    }

    return 0;
}
