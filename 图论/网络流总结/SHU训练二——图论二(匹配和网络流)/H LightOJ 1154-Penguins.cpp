#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <stack>
#include <string>
#include <math.h>
#include <bitset>
#include <ctype.h>
using namespace std;
typedef pair<int,int> P;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double eps = 1e-9;
const int N = 5000 + 5;
const int mod = 1e9 + 7;

int t, kase = 0;
int n, S, T, m;
int sum = 0;
double dist;
struct Node
{
    int x,y,cnt,cap;
}p[N];

double getdist(int i, int j)
{
    return sqrt((p[i].x - p[j].x)*(p[i].x - p[j].x) +
                (p[i].y - p[j].y)*(p[i].y - p[j].y));
}

struct Edge
{
    int u, v, flow, cap;
    Edge(){}
    Edge(int a, int b, int c, int d):u(a), v(b), cap(c), flow(d){}
};
struct Dinic
{
    int n;
    vector<int> G[N];
    vector<Edge> edges;
    int cur[N], vis[N], d[N];
    void init(int n)
    {
        this->n = n;
        for(int i = 0; i <= n; i++) G[i].clear();
        edges.clear();
    }
    void addEdge(int u, int v, int cap)
    {
        edges.push_back(Edge(u, v, cap, 0));
        edges.push_back(Edge(v, u,   0, 0));
        int m = edges.size();
        G[u].push_back(m-2);
        G[v].push_back(m-1);
    }

    bool BFS(int s, int t)
    {
        queue<int> Q;
        Q.push(s);
        memset(vis, 0, sizeof(vis));
        d[s] = 0;
        vis[s] = 1;
        while(!Q.empty())
        {
            int u = Q.front(); Q.pop();
            for(int i = 0; i < (int)G[u].size(); i++)
            {
                Edge &e = edges[G[u][i]];
                int v = e.v;
                if(vis[v]) continue;
                if(e.cap > e.flow)
                {
                    vis[v] = 1;
                    d[v] = d[u] + 1;
                    Q.push(v);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x, int a, int t)
    {
        if(x == t || a == 0) return a;
        int f, flow = 0;
        for(int &i = cur[x]; i < G[x].size(); i++)
        {
            Edge &e = edges[G[x][i]];
            int v = e.v;
            if(d[v] == d[x] + 1 && (f = DFS(v, min(e.cap-e.flow, a), t)) > 0)
            {
                e.flow += f;
                edges[G[x][i]^1].flow -= f;
                flow += f;
                a -= f;
                if(a <= 0) break;
            }
        }
        return flow;
    }

    int MaxFlow(int s, int t)
    {
        int flow = 0;
        while(BFS(s, t))
        {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF, t);
        }
        return flow;
    }

}dinic;

int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%lf", &n, &dist);
        vector<int> ans;
        sum = 0;
        for(int i = 0; i < n; i++)
        {
            scanf("%d%d%d%d", &p[i].x, &p[i].y, &p[i].cnt, &p[i].cap);
            sum += p[i].cnt;
        }
        for(int k = 0; k < n; k++)
        {
            dinic.init(2*n+2);
            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    if(i == j) continue;
                    if(getdist(i,j) <= dist)
                    {
                        dinic.addEdge(i+n, j, p[i].cap);
                    }
                }
            }
            for(int i = 0; i < n; i++)
                dinic.addEdge(i, i+n, p[i].cap);
            int S = n*2, T = k;
            for(int i = 0; i < n; i++)
                dinic.addEdge(S, i, p[i].cnt);
            if(sum == dinic.MaxFlow(S,T)) ans.push_back(k);
        }

        printf("Case %d:", ++kase);
        if(ans.size() == 0)
            printf(" %d", -1);
        else
            for(int i = 0; i < ans.size(); i++)
                printf(" %d", ans[i]);
        printf("\n");
    }
    return 0;
}
