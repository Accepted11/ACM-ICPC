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
const int INF = 1e9 + 7;
const int N = 1e3 + 7;
const int M = 1e6 + 7;
const int base = 400;
int S, T, D, n, m, cnt, tot;
int head[N], d[N];
char mp1[21][21], mp2[21][21];
inline int ID(int x, int y)
{
    int id = (x - 1) * m + y;
    return id >= 1 && id <= n * m ? id : -1;
}
struct edge
{
    int to, nex, w;
    edge(int to = 0, int w = 0, int nex = 0):
         to(to), w(w), nex(nex){}
}e[M];
void addedge(int u, int v, int w)
{
    e[++cnt] = edge(v, w, head[u]); head[u] = cnt;
    e[++cnt] = edge(u, 0, head[v]); head[v] = cnt;
}

void buildGraph()
{
    mem(head); tot = 0; cnt = 1;
    read(n); read(D);
    for(int i = 1; i <= n; i++)
        reads(mp1[i] + 1);
    for(int i = 1; i <= n; i++)
        reads(mp2[i] + 1);
    m = strlen(mp1[n] + 1);
    S = 0; T = n * m + base + 1;
//    cout << "S = " << S << ", T = " << T << endl;
    for(int x = 1; x <= n; x++)
    {
//        int id1, id2;
        for(int y = 1; y <= m; y++)
        {
            if(mp1[x][y] == '0') continue;

            int id1 = ID(x, y), id2;
            addedge(id1, id1 + base, mp1[x][y] - '0');

            if(mp2[x][y] == 'L')
            {
                addedge(S, id1, 1);
                tot++;
            }
            if(x <= D || x > n - D || y <= D || y > m - D)
                addedge(id1 + base, T, INF);
            for(int xd = -D; xd <= D; xd++)
                for(int yd = abs(xd) - D; yd <= D - abs(xd); yd++)
                {
                    if(mp1[x + xd][y + yd] == '0') continue;
                    id2 = ID(x + xd, y + yd);
                    if(id2 != -1)
                        addedge(id1 + base, id2, INF);
                }
        }
    }
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

void Dinic()
{
    int flow = 0, maxflow = 0;
    while(bfs())
        while(flow = dfs(S, INF))
            maxflow += flow;
    int ans = tot - maxflow;
    if(ans == 0) printf("no lizard was left behind.\n");
    else if(ans == 1) printf("1 lizard was left behind.\n");
    else printf("%d lizards were left behind.\n", ans);
}

signed main()
{
    int t; read(t);
    for(int i = 1; i <= t; i++)
    {
        buildGraph();
        printf("Case #%d: ", i);
        Dinic();
    }
    return 0;
}

