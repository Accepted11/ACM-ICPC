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
//template<class T>   inline T min(T a, T b) {return a > b ? b : a;}
//template<class T>   inline T max(T a, T b) {return a > b ? a : b;}
const int INF = 2e9 + 7;
const int N = 1e5 + 7;
const int M = 2e6 + 7;
int n, m, S, T, tot;
int head[N], cnt, d[N];
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

struct node
{
    int u, v;
    node(int u = 0, int v = 0) : u(u), v(v){}
}a[N];

int color[N];
void dfs(int u)
{
    color[u] = 1;
    for(int i = head[u]; i; i = e[i].nex)
    {
        int v = e[i].to;
        if(color[v] || e[i].w <= 0) continue;
        dfs(v);
    }
}

void buildGraph()
{
    mem(head); cnt = 1; tot = 0;
    S = 1, T = 2;
    for(int i = 1; i <= m; i++)
    {
        int u, v, w;
        read(u); read(v); read(w);
        addedge(u, v, w);
        a[++tot] = node(u, v);
    }
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

void Dinic()
{
    buildGraph();
    int flow = 0, maxflow = 0;
    while(bfs())
        while(flow = dfs(S, INF))
            maxflow += flow;
//    printf("%d\n", maxflow);
}

signed main()
{
    while(~scanf("%d%d", &n, &m))
    {
        if(n == 0 && m == 0) break;
        Dinic();
        mem(color);
        dfs(S);
//        cout << "tot = " << tot << endl;
        for(int i = 1; i <= tot; i++)
        {
            int u = a[i].u, v = a[i].v;
            if(color[u] ^ color[v])
                printf("%d %d\n", u, v);
        }
        puts("");
    }
    return 0;
}
