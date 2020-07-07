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

class Dinic
{
public:
    int S, T, n, m, cnt;
    int head[N], d[N], cur[N], nex[N], pre[N];
    edge e[M];

    void addedge(int u, int v, int cap)
    {
        e[++cnt] = edge(v, head[u], cap);
        head[u] = cnt;
    }

    // 建图
    void buildGraph(int _n, int _m)
    {
        // 初始化部分
        n = _n; m = _m;
        S = 0; T = 2*n + 1;
        mem(head);
        cnt = 1;

        // 构图部分
        int u, v, cap = 1;
        for(int i = 1; i <= m; i++)
        {
            read(u); read(v);
            addedge(u, v + n, cap);
            addedge(v + n, u, 0);
        }

        for(int i = 1; i <= n; i++)
        {
            addedge(S, i, 1);
            addedge(i, S, 0);
        }
        for(int i = n + 1; i < T; i++)
        {
            addedge(i, T , 1);
            addedge(T, i, 0);
        }
    }

    // 找增广路
    bool bfs()
    {
        mem(d);
        queue<int> q;
        q.push(S);  d[S] = 1;

        int u, v;
        while(q.size())
        {
            u = q.front(); q.pop();
            for(int i = head[u]; i; i = e[i].nex)
            {
                v = e[i].to;
                if(d[v] || e[i].cap <= 0) continue;
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
        for(int i = 0; i <= T; i++) cur[i] = head[i];
        return d[T];
    }

    int dfs(int u, int flow)
    {
        if(u == T) return flow;

        for(int& i = cur[u], v; i ; i = e[i].nex)
        {
            v = e[i].to;

            if(d[v] != d[u] + 1 || e[i].cap <= 0) continue;
            int delta = dfs(v, min(flow, e[i].cap));

            if(delta <= 0) continue;
            e[i].cap -= delta;
            e[i^1].cap += delta;

            return delta;
        }
        return 0;
    }

    int get_maxFlow()
    {
        int maxFlow = 0, tmp;
        while(bfs())
            while(tmp = dfs(S, INF))
                maxFlow += tmp;
        printPath();
        return maxFlow;
    }

    void printPath()
    {
        for(int i = 1; i <= n; i++) nex[i] = pre[i] = i;

        for(int i = 2; i <= cnt; i += 2)
            if(e[i].cap == 0 && e[i^1].to != S && e[i].to != T)
            {
                int u = e[i^1].to, v = e[i].to - n;
                nex[u] = v,
                pre[v] = u;
            }

        for(int i = 1; i <= n; i++)
        {
            if(pre[i] != i) continue;
            printf("%d", i);
            int u = i;
            while(u != nex[u])
            {
                printf(" %d", nex[u]);
                u = nex[u];
            }
            puts("");
        }
    }

};

Dinic ways;
signed main()
{
    int n, m, S, T;

    while(~scanf("%d%d", &n, &m))
    {
        ways.buildGraph(n, m);

        printf("%d\n", n - ways.get_maxFlow());
    }

    return 0;
}

/**
4 4
1 2
1 3
2 4
3 4
**/
