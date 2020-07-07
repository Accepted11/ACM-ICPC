#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=1010;
const int maxm=10010;
const int inf=0x3f3f3f3f;
struct Node
{
    int to;
    int capa;
    int cost;
    int next;
}edge[maxm];
int cnt;
int source,sink;
int head[maxn];
int numa[maxn];
int numb[maxn];
int dis[maxn];
bool vis[maxn];
int rec[maxn];
int pre[maxn];
int ldj;
void init()
{
    memset(head,-1,sizeof(head));
    cnt=0;
    return;
}
void add(int u,int v,int capa,int cost)
{
    edge[cnt].to=v;
    edge[cnt].capa=capa;
    edge[cnt].cost=cost;
    edge[cnt].next=head[u];
    head[u]=cnt++;
    edge[cnt].to=u;
    edge[cnt].capa=0;
    edge[cnt].cost=-cost;
    edge[cnt].next=head[v];
    head[v]=cnt++;
    return;
}
bool spfa()
{
    memset(vis,false,sizeof(vis));
    memset(dis,inf,sizeof(dis));
    memset(rec,-1,sizeof(rec));
    memset(pre,-1,sizeof(pre));
    queue<int> que;
    que.push(source);
    dis[source]=0;
    vis[source]=true;
    while(!que.empty())
    {
        int node=que.front();
        que.pop();
        vis[node]=false;
        for(int i=head[node];~i;i=edge[i].next)
        {
            int v=edge[i].to;
            if(edge[i].capa>0&&dis[v]>dis[node]+edge[i].cost)
            {
                dis[v]=dis[node]+edge[i].cost;
                rec[v]=i;
                pre[v]=node;
                if(!vis[v])
                {
                    vis[v]=true;
                    que.push(v);
                }
            }
        }
    }
    return dis[sink]!=inf;
}
int mcmf()
{
    int maxflow=0;
    int mincost=0;
    while(spfa())
    {
        int node=sink;
        int flow=inf;
        while(node!=source)
        {
            flow=min(flow,edge[rec[node]].capa);
            node=pre[node];
        }
        node=sink;
        while(node!=source)
        {
            mincost+=flow*edge[rec[node]].cost;
            edge[rec[node]].capa-=flow;
            edge[rec[node]^1].capa+=flow;
            node=pre[node];
        }
    }
    return -mincost;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int test;
    scanf("%d",&test);
    for(int cas=1;cas<=test;cas++)
    {
        init();
        int n;
        scanf("%d",&n);
        source=0;
        sink=n*2+1;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&numa[i]);
        }
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&numb[i]);
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(numa[i]<numb[j])
                {
                    add(i,n+j,1,0);
                }
                else if(numa[i]==numb[j])
                {
                    add(i,n+j,1,-1);
                }
                else
                {
                    add(i,n+j,1,-2);
                }
            }
        }
        for(int i=1;i<=n;i++)
        {
            add(source,i,1,0);
            add(n+i,sink,1,0);
        }
        printf("Case %d: %d\n",cas,mcmf());
    }
    return 0;
}
