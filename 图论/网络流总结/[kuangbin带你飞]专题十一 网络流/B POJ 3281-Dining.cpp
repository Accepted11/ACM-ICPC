/*
几个小错误：
    1. 建图时还是没有注意考虑拆点的问题
    2. addedge 居然打错了
        e[++cnt] = edge(u, 0, head[u]); head[v] = cnt 是什么鬼
                    不应该是  head[v] ?
*/
#pragma GCC optimize(2)
//#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<queue>
#include<vector>
#include<cstring>
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
const int M = 1e6 + 7;
int n, D, F, S, T;
struct edge
{
    int to, w, nex;
    edge(int to = 0, int w = 0, int nex = 0):to(to), w(w), nex(nex){}
}e[M];
int head[N], cnt, d[N];
queue<int> q;
void addedge(int u, int v, int w)
{
    e[++cnt] = edge(v, w, head[u]); head[u] = cnt;
    e[++cnt] = edge(u, 0, head[v]); head[v] = cnt;
}

void buildGraph()
{
    mem(head); cnt = 1;
    S = 0; T = n + n + F + D + 1;
    for(int i = 1; i <= F; i++) addedge(S, i, 1);
    for(int i = F + 1; i <= n + F; i++) addedge(i, i + n, 1);
    for(int i = F + n + n + 1; i < T; i++) addedge(i, T, 1);

    for(int i = 1; i <= n; i++)
    {
        int Di, Fi, x;
        read(Fi); read(Di);
        for(int j = 1; j <= Fi; j++)
        {
            read(x);
            addedge(x, i + F, 1);
        }
        for(int j = 1; j <= Di; j++)
        {
            read(x);
            addedge(i + F + n, x + 2 * n + F, 1);
        }
    }
}

bool bfs()
{
    mem(d);
    while(q.size()) q.pop();
    q.push(S); d[S] = 1;
    int u, v;
    while(q.size())
    {
        u = q.front(); q.pop();
        for(int i = head[u]; i; i = e[i].nex)
        {
            v = e[i].to;
            if(!e[i].w || d[v]) continue;
            q.push(v);
            d[v] = d[u] + 1;
            if(v == T) return 1;
        }
    }
    return 0;
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

int Dinic()
{
    int flow = 0, maxflow = 0;
    while(bfs())
        while(flow = dfs(S, INF))
            maxflow += flow;
    return maxflow;
}

signed main()
{
    while(~scanf("%d%d%d", &n, &F, &D))
    {
        buildGraph();
        printf("%d\n", Dinic());
    }
    return 0;
}
