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
const int N = 100 + 7;
const int M = 1e5 + 7;
int n, np, nc, m;
int S, T, cnt;
int head[N], d[N];
queue<int> q;
struct edge
{
    int to, nex, w;
    edge(int to = 0, int w = 0, int nex = 0):
        to(to), w(w), nex(nex){}
}e[M];
inline void addedge(int u, int v, int w)
{
    e[++cnt] = edge(v, w, head[u]); head[u] = cnt;
    e[++cnt] = edge(u, 0, head[v]); head[v] = cnt;
}
void buildGraph()
{
    mem(head); cnt = 1;
    S = 0, T = n + 1;
    for(int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf(" (%d,%d)%d", &u, &v, &w);
        u++; v++;
//        printf("u = %d, v = %d, w = %d\n", u, v, w);
        addedge(u, v, w);
    }
    for(int i = 1; i <= np; i++)
    {
//        cout << "YES\n";
        int v, w;
        scanf(" (%d)%d", &v, &w);
        v++;
//        printf("u = %d, v = %d, w = %d\n", S, v, w);
        addedge(S, v, w);
    }
    for(int i = 1; i <= nc; i++)
    {
        int u, w;
        scanf(" (%d)%d", &u, &w);
        u++;
//        printf("u = %d, v = %d, w = %d\n", u, T, w);
        addedge(u, T, w);
    }
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
        rest -= k;
        e[i].w -= k;
        e[i ^ 1].w += k;
    }
    return flow - rest;
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
            q.push(v); d[v] = d[u] + 1;
            if(v == T) return 1;
        }
    }
    return 0;
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
    while(~scanf("%d%d%d%d", &n, &np, &nc, &m))
        printf("%d\n", Dinic());
    return 0;
}

