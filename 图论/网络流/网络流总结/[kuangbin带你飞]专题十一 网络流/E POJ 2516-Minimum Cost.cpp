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
int n, m, k, A[N][N], B[N][N], sumA[N], sumB[N];
int dis[N], flow[N], pre[N], head[N], Inq[N];
int S, T, cnt, maxFlow, minCost;

struct edge
{
    int to, nex, w, cost;
    edge(int to = 0, int w = 0, int cost = 0, int nex = 0):
         to(to), w(w), cost(cost), nex(nex) {}
}e[M];
void addedge(int u, int v, int w, int cost)
{
    e[++cnt] = edge(v, w, cost, head[u]); head[u] = cnt;
//    printf("\ncnt = %d\nu = %d, v = %d, w = %d, cost = %d\n"
//             ,cnt,        u,      v,      w,      cost);
    e[++cnt] = edge(u, 0, -cost, head[v]); head[v] = cnt;
}
queue<int> q;
bool SPAF()
{
    while(q.size()) q.pop();
    for(int i = 0; i < N; i++)
    {
        dis[i] = INF;
        Inq[i] = 0;
    }
    q.push(S); dis[S] = 0; Inq[S] = 1; flow[S] = INF;
    int u, v, cost;
    while(q.size())
    {
        u = q.front(); q.pop(); Inq[u] = 0;
        for(int i = head[u]; i; i = e[i].nex)
        {
            if(e[i].w == 0) continue;
            v = e[i].to;
            cost = dis[u] + e[i].cost;
            if(dis[v] > cost)
            {
                dis[v] = cost;
                flow[v] = min(flow[u], e[i].w);
                pre[v] = i;
                if(!Inq[v])
                {
                    Inq[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return dis[T] != INF;
}

void update()
{
    int u = T, i;
    while(u != S)
    {
        i = pre[u];
        e[i].w -= flow[T];
        e[i ^ 1].w += flow[T];
        u = e[i ^ 1].to;
    }
    maxFlow += flow[T];
    minCost += flow[T] * dis[T];
}

void work()
{
    bool flag = 1;
    int ans = 0, x;
    mem(sumA); mem(sumB);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= k; j++)
        {
            read(B[i][j]);
            sumB[j] += B[i][j];
        }
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= k; j++)
        {
            read(A[i][j]);
            sumA[j] += A[i][j];
        }

    for(int i = 1; i <= k; i++)
        if(sumA[i] < sumB[i])
        {
//            cout << "i = " << i << endl;
            flag = 0;
            break;
        }
    for(int t = 1; t <= k; t++)
    {
        mem(head); cnt = 1;
        for(int i = m + 1; i <= m + n; i++)
            for(int j = 1; j <= m; j++)
            {
                read(x);
                addedge(j, i, A[j][t], x);
            }
        if(!flag) continue;
        S = 0, T = n + m + 1;
        for(int i = 1; i <= m; i++)
            addedge(S, i, A[i][t], 0);
        for(int i = m + 1; i <= m + n; i++)
            addedge(i, T, B[i - m][t], 0);

        maxFlow = minCost = 0;
        while(SPAF())   update();
        ans += minCost;
//        cout << "minCost = " << minCost << endl;
    }
    if(flag) printf("%d\n", ans);
    else     puts("-1");
}

signed main()
{
    while(~scanf("%d%d%d", &n, &m, &k))
        if(n + m + k == 0) break;
        else               work();
    return 0;
}

