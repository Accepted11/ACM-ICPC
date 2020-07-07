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
const int N = 1e5 + 7;
const int M = 1e5 + 7;
int S, T, n, m, cnt;
int head[N], d[N];

struct edge
{
    int to, nex, w;
    edge(int to = 0, int w  = 0, int nex = 0):to(to),w(w),nex(nex){}
}e[M << 1];
void addedge(int u, int v, int w)
{
    e[++cnt] = edge(v, w, head[u]); head[u] = cnt;
    e[++cnt] = edge(u, w, head[v]); head[v] = cnt;
}

int dfs(int u, int flow)
{
    if(u == T) return flow;
    int rest = flow, k, v;
    for(int i = head[u]; i && rest; i = e[i].nex)
    {
        v = e[i].to;
        if(!e[i].w || d[v] != d[u] + 1) continue;
        k = dfs(v, min(rest, e[i].w));
        if(!k) d[v] = 0;
        e[i].w -= k;
        e[i ^ 1].w += k;
        rest -= k;
    }
    return flow - rest;
}

int q[N << 1];
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
void buildGraph()
{
    mem(head); cnt = 1;
    int minX = INF, maxX = -INF;
    read(n); read(m);
    for(int i = 1; i <= n; i++)
    {
        int x, y;
        read(x); read(y);
        if(x < minX)
        {
            minX = x; S = i;
        }
        if(x > maxX)
        {
            maxX = x; T = i;
        }
    }
    for(int i = 1; i <= m; i++)
    {
        int u, v, w;
        read(u); read(v); read(w);
        addedge(u, v, w);
    }
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
    int t; read(t);
    while(t--) printf("%d\n", Dinic());
    return 0;
}
