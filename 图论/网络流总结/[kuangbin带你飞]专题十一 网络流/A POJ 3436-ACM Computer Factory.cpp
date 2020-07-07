/*
    ���⣺��P��������n̨������ÿ̨��������ܽ���val[i]̨���ԣ������У�
ÿ̨���������루ǰP���������������P������
ÿ������������0,1,2��ʾ��0��ʾ�����н��ܵĵ��Զ�Ӧ�Ĳ���ûװ��,1��ʾװ�ã�2��ʾ����ν��
��ÿ̨�����ܶԵ��Խ��мӹ���ǰ�����������ǵ����ڼӹ�֮ǰ�����еĲ�������
ÿ�����������0,1��ʾ��0��ʾ������Զ�Ӧ�Ĳ���ûװ�ã�1��ʾװ�ã������ӹ�����õ��Ժ󣬸õ��ԵĲ�����ɣ�
����ΰ���������ʹ��ÿСʱ�ܰ�װ�����ĵ��ԣ������һ�ַ�����
��װ��ɵĳ�Ҫ���������������������װ�ϣ������������ȫΪ1
    ˼·���� A ������������� B �� ���룬 ������ A ---> B (val[A]);
          �� ���� ���� Դ�� S, �� A ������ ���� 1, �� ���� S ---> A (val[A])
          �� ���� ���� ��� T, �� A ����� ֻ�� 1, �� ���� A ---> T (val[A])
    ���ǵ�ÿһ������һ�� val[i], ����Ҫ���ֳ� val[i], ����Ҫ�� ÿһ������в��
    ��Ϊ��� i , ���� i' = i + n;
    ���⻹Ҫ���һ�ַ���
    �����õ���dinic����ô�ͱ���Ҫ��һ��vis�����¼ԭͼ�л���i�����j֮��������ˣ��������dinic�㷨��
    ���ǹ۲���Щ��vis��ǹ��Ļ�����ϣ�������������ˣ�����Ȼ����̨����֮�����д���ģ�������ɡ�
ʧ��㣺Dinic ���Ӵ���ˣ����µ��˺ܾ�
�ջ������������������Ҫ���ֳ�������Ҫ���ǲ�㣬��������Ա����ڱ���
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

