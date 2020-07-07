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
int val1[N], val2[N];
struct edge
{
    int to, nex, cap;
    edge(int to = 0, int nex = 0, int cap = 0) : to(to), nex(nex), cap(cap){}
};

class Dinic
{
public:
    int S, T, n, m, cnt, sum;
    int head[N], d[N], cur[N], vis[N];
    vector<int> G[N];
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
        S = 0; T = n + m + 1;
        mem(head);
        cnt = 1;
        sum = 0;

        // 构图部分
        int u, v, cap = 1;
        char op;
        for(int i = 1; i <= n; i++)
        {
            scanf("%d%c", &cap, &op);
            addedge(S, i, cap);
            addedge(i, S, 0);
            sum += cap;
            val1[i] = cap;

            while(1)
            {
                scanf("%d%c", &v, &op);
                addedge(i, v + n, INF);
                addedge(v + n, i, 0);
                G[i].pb(v);
                if(op == '\r') break;
            }
        }

        for(int i = n + 1; i <= m + n; i++)
        {
            read(cap);
            val2[i - n] = cap;
            addedge(i, T, cap);
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
        int tmp, maxFlow = 0;
        while(bfs())
            while(tmp = dfs(S, INF))
                maxFlow += tmp;

        printPath();
        return sum - maxFlow;
    }

    void printPath()
    {
        vector<int> ansE, ansI;
        queue<int> q;
        q.push(S);
        mem(vis);

//        cout << "YES" << "\n";
        while(q.size())
        {
            int u = q.front(); q.pop();
            for(int i = head[u]; i; i = e[i].nex)
            {
                int v = e[i].to;
                if(!e[i].cap || vis[v]) continue;
//                cout << "u = " << u << " ,v = " << v << "\n";
                vis[v] = 1;
                q.push(v);
            }
        }

        for(int i = 1; i < T; i++)
            if(vis[i])
            {
                if(i <= n) ansE.pb(i);
                else       ansI.pb(i - n);
            }

        printf("%d", ansE[0]);
        for(int i = 1; i < ansE.size(); i++) printf(" %d", ansE[i]);

        printf("\n%d", ansI[0]);
        for(int i = 1; i < ansI.size(); i++) printf(" %d", ansI[i]);

        printf("\n");
    }

};

Dinic ways;
signed main()
{
    int n, m, S, T;

    while(~scanf("%d%d", &n, &m))
    {
        ways.buildGraph(n, m);

        printf("%d\n", ways.get_maxFlow());
    }

    return 0;
}
/**
3 3
100 1 2
100 2 3
100 2 3
1 1 1
**/
