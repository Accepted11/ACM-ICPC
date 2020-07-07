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
const int N = 500 + 7;
const int M = 2e6 + 7;
const int base = 100;

struct edge
{
    int to, nex, cap;
    edge(int to = 0, int nex = 0, int cap = 0) : to(to), nex(nex), cap(cap){}
};
int dir[2][8] = {{-2, -2, 2 , 2, -1, -1, 1, 1},
                 {1, -1, 1, -1, -2, 2, -2 , 2}};
class ISAP
{
public:
    int S, T, n, m, cnt, sum;
    int head[N*N], d[N*N], cur[N*N], gap[N*N];
    bool flag[N*N];
    edge e[M];

    void addedge(int u, int v, int cap)
    {
        e[++cnt] = edge(v, head[u], cap);
        head[u] = cnt;

        e[++cnt] = edge(u, head[v], 0);
        head[v] = cnt;
    }

    inline int ID(int x, int y)
    {
        int id = (x - 1) * n + y;
        if(x < 1 || x > n || y < 1 || y > n || flag[id])
            return -1;
        return id;
    }

    // 建图
    void buildGraph(int _n, int _m, int _S, int _T)
    {
        // 初始化部分
        n = _n; m = _m;
        S = _S; T = _T;
        mem(head); mem(flag);
        cnt = 1; sum = n* n - m;

        // 构图部分
        int ntot = 0;
        for(int i = 1, x, y; i <= m; i++)
        {
            read(x); read(y);
            flag[ID(x, y)] = 1;
        }


        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
            {
                int idx = ID(i, j);
                if(idx == -1) continue;
                if((i + j) % 2 == 0)
                {
                    addedge(idx, T, 1);
                    continue;
                }

                addedge(S, idx, 1);

                for(int k = 0; k < 8; k++)
                {
                    int x = i + dir[0][k], y = j + dir[1][k];
                    int idy = ID(x, y);
                    if(idy != -1) addedge(idx, idy, 1);
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
        ways.buildGraph(n, m, 0, n*n + 1);
        printf("%d\n", ways.get_maxFlow());
    }

    return 0;
}
