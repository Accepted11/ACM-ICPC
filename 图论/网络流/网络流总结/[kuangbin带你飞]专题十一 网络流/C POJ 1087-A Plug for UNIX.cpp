#pragma GCC optimize(2)
//#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<map>
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
const int N = 1e3 + 7;
const int M = 1e6 + 7;

queue<int> q;
int head[N], cnt, d[N];
struct edge
{
    int to, nex, w;
    edge(int to = 0, int w = 0, int nex = 0):to(to), w(w), nex(nex){}
}e[M];
inline void addedge(int u, int v, int w)
{
    e[++cnt] = edge(v, w, head[u]); head[u] = cnt;
//    printf("\n cnt = %d\n u = %d, v = %d, w = %d\n", cnt, u, v, w);
    e[++cnt] = edge(u, 0, head[v]); head[v] = cnt;
};
int n, m, k, S, T, id;
map<string, int> mp;
int ID(string &s)
{
    if(!mp.count(s)) mp[s] = ++id;
    return mp[s];
}
void init()
{
    mem(head); mp.clear();
    cnt = 1; id = 0;
}
int num[4][N][2];
string str1, str2;
void buildGraph()
{
    init();
    for(int i = 1; i <= n; i++)
    {
        cin >> str1;
        num[1][i][0] = ID(str1);
    }
    cin >> m;
    for(int i = 1; i <= m; i++)
    {
        cin >> str1 >> str2;
        num[2][i][0] = ID(str1);
        num[2][i][1] = ID(str2);
    }
    cin >> k;
    for(int i = 1; i <= k; i++)
    {
        cin >> str1 >> str2;
        num[3][i][0] = ID(str1);
        num[3][i][1] = ID(str2);
    }
    S = 0; T = id + 1;
    for(int i = 1; i <= n; i++) addedge(num[1][i][0], T, 1);
    for(int i = 1; i <= m; i++)
    {
        addedge(num[2][i][0], num[2][i][1], 1);
        addedge(S, num[2][i][0], 1);
    }
    for(int i = 1; i <= k; i++) addedge(num[3][i][0], num[3][i][1], INF);
//    for(int i = S; i <= T; i++)
//       for(int i = 0; i <= )
}

bool bfs()
{
    mem(d);
    while(q.size()) q.pop();
    q.push(S); d[S] = 1;
    int u, v, w;
    while(q.size())
    {
        u = q.front(); q.pop();
        for(int i = head[u]; i; i = e[i].nex)
        {
            v = e[i].to; w = e[i].w;
//            cout << u << " " << v << " " << w << endl;
            if(!w || d[v]) continue;
            q.push(v);  d[v] = d[u] + 1;
//            cout << v << " has been pushed in queue\n";
            if(v == T) return 1;
        }
    }
    return 0;
}

int dfs(int u, int flow)
{
    if(u == T) return flow;
    int rest = flow, k, v, w;
    for(int i = head[u]; i; i = e[i].nex)
    {
        v = e[i].to; w = e[i].w;
        if(!w || d[v] != d[u] + 1) continue;
        k = dfs(v, min(rest, w));
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
        if(flow = dfs(S, INF)) maxflow += flow;
    printf("%d\n", m - maxflow);
}

signed main()
{
    Buff;
    while(cin >> n)
    {
        buildGraph();
        Dinic();
    }
    return 0;
}

