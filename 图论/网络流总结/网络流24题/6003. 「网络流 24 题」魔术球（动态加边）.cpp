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
const int INF = 1e9 + 7;
const int N = 1e5 + 7;
const int M = 1e6 + 7;
const int base = 2e3 + 7;
int S, T, n, m, cnt;
int head[N], q[M << 2], d[N];
struct edge
{
    int to, nex, w;
    edge(int to = 0, int w = 0, int nex = 0) : to(to), w(w), nex(nex) {}
} e[M];
void addedge(int u, int v, int w)
{
    e[++cnt] = edge(v, w, head[u]);
    head[u] = cnt;
    e[++cnt] = edge(u, 0, head[v]);
    head[v] = cnt;
}

bool bfs()
{
    mem(d);
    int Head = 0, Tail = 0, u, v;
    q[Tail++] = S;
    d[S] = 1;
    while (Head < Tail)
    {
        u = q[Head++];
        for (int i = head[u]; i; i = e[i].nex)
        {
            v = e[i].to;
            if (!e[i].w || d[v])
                continue;
            d[v] = d[u] + 1;
            q[Tail++] = v;
            if (v == T)
                return 1;
        }
    }
    return 0;
}
int dfs(int u, int flow)
{
    if (u == T)
        return flow;
    int rest = flow, k, v;
    for (int i = head[u]; i; i = e[i].nex)
    {
        v = e[i].to;
        if (!e[i].w || d[v] != d[u] + 1)
            continue;
        k = dfs(v, min(rest, e[i].w));
        if (!k)
            d[v] = 0;
        e[i].w -= k;
        e[i ^ 1].w += k;
        rest -= k;
    }
    return flow - rest;
}

int Dinic()
{
    int Flow = 0, maxFlow = 0;
    while (bfs())
        while (Flow = dfs(S, INF))
            maxFlow += Flow;
    return maxFlow;
}
bool judge(int x)
{
    int t = int(sqrt((double)x * 1.000) + 1e-9);
    return t * t == x;
}
int solve()
{
    mem(head);
    cnt = 1;
    int MaxFlow = 0;
    S = 0, T = base * 2 + 1;
    for (int i = 1;; i++)
    {
        for (int j = 1; j < i; j++)
            if (judge(i + j))
                addedge(i, j + base, 1);
        addedge(S, i, 1);
        addedge(i + base, T, 1);
        MaxFlow += Dinic();
        if (i - MaxFlow > n)
            return i - 1;
    }
}

int vis[N], son[N];
void show(int u)
{
    vis[u] = 1;
    printf("%d%s", u, u == son[u] ? "\n" : " ");
    if (u != son[u])
        show(son[u]);
}
signed main()
{
    read(n);
    int ans = solve();
    printf("%d\n", ans);
    for (int i = 1; i <= ans; i++)
        son[i] = i;

    for (int i = 2; i <= cnt; i += 2)
        if (!e[i].w && e[i ^ 1].to != S && e[i].to != T)
            son[e[i].to - base] = e[i ^ 1].to;

    mem(vis);
    for (int i = 1; i <= ans; i++)
        if (!vis[i])
            show(i);
    return 0;
}
