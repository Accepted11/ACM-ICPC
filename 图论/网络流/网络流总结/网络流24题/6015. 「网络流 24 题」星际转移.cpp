#pragma GCC optimize(2)
#include <bits/stdc++.h>
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
const int N = 1e5 + 7;
const int M = 1e6 + 7;
const int _N = 102;
const int base = 100;
int n, m, S, T;

struct edge
{
    int to, nex, cap;
    edge(int to = 0, int nex = 0, int cap = 0) : to(to), nex(nex), cap(cap) {}
};
int pre[_N], station[_N][_N], r[_N], H[_N];
int head[N], d[N], cur[N], gap[N];
edge e[M];

class ISAP
{
public:
    int S, T, n, m, cnt, K;

    void addedge(int u, int v, int cap)
    {
        e[++cnt] = edge(v, head[u], cap);
        head[u] = cnt;

        e[++cnt] = edge(u, head[v], 0);
        head[v] = cnt;
        //        printf("%d --- %d, %d\n", u, v, cap);
    }

    // 建图
    void buildGraph()
    {
        // 初始化部分
        read(n);
        read(m);
        read(K);
        mem(head);
        cnt = 1;
        S = N - 2;
        T = N - 1;
        for (int i = 1; i <= m; i++)
        {
            read(H[i]);
            read(r[i]);
            for (int j = 1; j <= r[i]; j++)
                read(station[i][j]);
            pre[i] = 1;
        }
        n += 2;
        addedge(S, 0, INF);
        int ans = 0;
        for (int day = 1; day <= 30; day++)
        {
            int today = n * day, yesterday = n * (day - 1), now;
            for (int i = 0; i < n; i++)
                addedge(yesterday + i, today + i, INF);
            addedge(today + n - 1, T, INF);
            for (int i = 1; i <= m; i++)
            {
                now = pre[i] + 1;
                if (now > r[i])
                    now = 1;
                addedge(station[i][pre[i]] + yesterday, station[i][now] + today, H[i]);
                pre[i] = now;
            }
            ans += get_maxFlow();
            if (ans >= K)
            {
                printf("%d\n", day);
                return;
            }
        }
        printf("%d\n", 0);
    }

    // 找增广路
    void bfs()
    {
        queue<int> q;
        for (int i = 0; i <= T; i++)
        {
            cur[i] = head[i];
            d[i] = gap[i] = 0;
        }

        q.push(T);
        d[T] = gap[1] = 1;

        int u, v;
        while (q.size())
        {
            u = q.front();
            q.pop();
            for (int i = head[u]; i; i = e[i].nex)
            {
                v = e[i].to;
                if (d[v])
                    continue;
                d[v] = d[u] + 1;
                ++gap[d[v]];
                q.push(v);
            }
        }
    }

    int dfs(int u, int flow)
    {
        if (u == T)
            return flow;
        int delta = 0, v, temp;
        for (int &i = cur[u]; i; i = e[i].nex)
        {
            v = e[i].to;
            if (d[v] + 1 != d[u])
                continue;
            temp = dfs(v, min(flow - delta, e[i].cap));
            if (temp)
            {
                e[i].cap -= temp;
                e[i ^ 1].cap += temp;
                delta += temp;
            }
            if (flow == delta)
                return flow;
        }
        if (!(--gap[d[u]]))
            d[S] = T + 1;
        ++gap[++d[u]];
        cur[u] = head[u];
        return delta;
    }

    int get_maxFlow()
    {
        bfs();

        int maxFlow = 0;

        while (d[S] <= T)
            maxFlow += dfs(S, INF);

        return maxFlow;
    }
};

ISAP ways;
signed main()
{
    ways.buildGraph();
    return 0;
}
