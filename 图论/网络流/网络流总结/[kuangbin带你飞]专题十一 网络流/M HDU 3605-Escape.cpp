#pragma GCC optimize(2)
//#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<cstring>
#include<queue>
#include<algorithm>

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
const int N = 2e5 + 7;
const int M = 2e6 + 7;
const int base = 2046;
int n, m, S, T;
int head[N], cnt, d[N], temp[12];
int num[1 << 11];
//int pp[11] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
//queue<int> q;
struct edge
{
    int to, nex, w;
    edge(int to = 0, int w = 0, int nex = 0):to(to), w(w), nex(nex){}
}e[M];

inline void addedge(int u, int v, int w)
{
    e[++cnt] = edge(v, w, head[u]); head[u] = cnt;
    e[++cnt] = edge(u, w, head[v]); head[v] = cnt;
}

void buildGraph()
{
    mem(head); mem(num); cnt = 1;

    S = 1; T = base + m + 1;
    for(int i = 1; i <= n; i++)
    {
        int x = 0;
        for(int j = 1; j <= m; j++)
        {
            read(temp[j]);
            x += temp[j] * (1 << j);
        }
        num[x]++;
        if(num[x] == 1)
        {
            for(int j = 1; j <= m; j++)
                if(temp[j]) addedge(x, j + base, INF);
        }
    }
    for(int i = 1; i <= m; i++)
    {
        int x; read(x);
        addedge(i + base, T, x);
    }
    for(int i = 2; i <= base; i++)
        if(num[i]) addedge(S, i, num[i]);
}

int q[M << 1];
bool bfs()
{
    mem(d);
    int u, v, Head = 0, Tail = 0;
    q[Tail++] = S; d[S] = 1;
    while(Head < Tail)
    {
        u = q[Head++];
        for(int i = head[u]; i; i = e[i].nex)
        {
            v = e[i].to;
            if(e[i].w <= 0 || d[v]) continue;
            d[v] = d[u] + 1;
            q[Tail++] = v;
            if(v == T) return 1;
        }
    }
    return 0;
}

int dfs(int u, int flow)
{
    if(u == T) return flow;
    int rest = flow, k, v, w;
    for(int i = head[u]; i && rest; i = e[i].nex)
    {
        v = e[i].to, w = e[i].w;
        if(!w || d[v] != d[u] + 1) continue;
        k = dfs(v, min(rest, e[i].w));
        if(!k) d[v] = 0;
        e[i].w -= k;
        e[i ^ 1].w += k;
        rest -= k;
    }
    return flow - rest;
}

int Dinic()
{
    buildGraph();
    int Flow = 0, maxFlow = 0;
    while(bfs())
        while(Flow = dfs(S, INF))
            maxFlow += Flow;
    return maxFlow;
}

signed main()
{
    while(~scanf("%d%d", &n, &m))
        if(Dinic() == n) puts("YES");
        else             puts("NO");
    return 0;
}
