/*
    题意：有P个部件和n台机器，每台机器最大能接受val[i]台电脑（生产中）
每台机器有输入（前P个数）和输出（后P个数）
每个部件输入用0,1,2表示，0表示不能有接受的电脑对应的部件没装好,1表示装好，2表示无所谓。
（每台机器能对电脑进行加工的前提条件（即是电脑在加工之前必须有的部件））
每个部件输出用0,1表示，0表示输出电脑对应的部件没装好，1表示装好，（即加工完完该电脑后，该电脑的部件组成）
问如何安排生产线使得每小时能安装出最多的电脑？并输出一种方案。
安装完成的充要条件就是所有零件都被安装上，即机器的输出全为1
    思路：若 A 的输出可以满足 B 的 输入， 则连边 A ---> B (val[A]);
          再 建立 超级 源点 S, 若 A 的输入 不含 1, 则 连边 S ---> A (val[A])
          再 建立 超级 汇点 T, 若 A 的输出 只含 1, 则 连边 A ---> T (val[A])
    考虑到每一个点有一个 val[i], 且需要体现出 val[i], 故需要将 每一个点进行拆点
    拆为入点 i , 出点 i' = i + n;
    这题还要输出一种方案
    由于用的是dinic，那么就必须要用一个vis数组记录原图中机器i与机器j之间的容量了，最后跑完dinic算法，
    我们观察那些用vis标记过的机器组合，如果容量减少了，那显然这两台机器之间是有传输的，输出即可。
失误点：Dinic 板子打错了，导致调了很久
收获：若点有特殊的属性需要表现出来，就要考虑拆点，将点的属性表现在边上
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
const int INF = 2e9 + 7;
const int N = 300 + 7;
const int M = 1e5 + 7;

struct edge
{
    int to, nex, w;
    edge(int to = 0, int w = 0, int nex = 0) : to(to), w(w), nex(nex) {}
}e[M];
int head[N], cnt, d[N];
inline void addedge(int u, int v, int w)
{
    e[++cnt] = edge(v, w, head[u]); head[u] = cnt;
    e[++cnt] = edge(u, 0, head[v]); head[v] = cnt;
}

int n, p, S, T;
int val[N], in[N][21], out[N][21], vis[N][N];

bool check(int i, int j)
{
    for(int k = 0; k < p; k++)
        if(out[i][k] != in[j][k] && in[j][k] != 2)
            return false;
    return true;
}

bool judge_S(int i)
{
    for(int k = 0; k < p; k++)
        if(in[i][k] == 1) return false;
    return true;
}

bool judge_T(int i)
{
    for(int k = 0; k < p; k++)
        if(out[i][k] != 1) return false;
    return true;
}

void buildGraph()
{
    for(int i = 1; i <= n; i++)
    {
        read(val[i]);
        for(int j = 0; j < p; j++)
            read(in[i][j]);
        for(int j = 0; j < p; j++)
            read(out[i][j]);
    }
    mem(head); mem(vis); cnt = 1;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
        {
            if(i == j) continue;
            if(check(i, j))
            {
                addedge(i + n, j, val[i]);
                vis[i + n][j] = 1;
            }
        }
     S = 0; T = (n << 1 | 1);
     for(int i = 1; i <= n; i++)
     {
         addedge(i, i + n, val[i]);
         if(judge_T(i)) addedge(i + n, T, val[i]);
         if(judge_S(i)) addedge(S, i, val[i]);
     }
}
queue<int> q;
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

void print()
{
    int tot = 0;
    for(int i = 1; i <= n; i++)
        for(int j = head[i + n]; j; j = e[j].nex)
            tot += (vis[i + n][e[j].to] && e[j].w < val[i]);

    printf("%d\n", tot);
    for(int i = 1; i <= n; i++)
        for(int j = head[i + n]; j; j = e[j].nex)
            if(vis[i + n][e[j].to] && e[j].w < val[i])
                printf("%d %d %d\n", i, e[j].to, val[i] - e[j].w);

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
    while(~scanf("%d%d", &p, &n))
    {
        buildGraph();
        printf("%d ", Dinic());
        print();
    }
    return 0;
}

