#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<queue>
using namespace std;
const int maxn=1010;
const int maxm=10010;
const int inf=0x3f3f3f3f;
struct Node
{
    int to;
    int capa;
    int next;
}edge[maxm];
int source,sink;
int cnt;
int head[maxn];
bool vis[maxn];
int num[maxn];
int dep[maxn];
map<string,int> ma;
void init()
{
    memset(head,-1,sizeof(head));
    ma["XS"]=1;
    ma["S"]=2;
    ma["M"]=3;
    ma["L"]=4;
    ma["XL"]=5;
    ma["XXL"]=6;
    cnt=0;
    return;
}
void add(int u,int v,int capa)
{
    edge[cnt].to=v;
    edge[cnt].capa=capa;
    edge[cnt].next=head[u];
    head[u]=cnt++;
    edge[cnt].to=u;
    edge[cnt].capa=0;
    edge[cnt].next=head[v];
    head[v]=cnt++;
    return;
}
bool bfs()
{
    queue<int> que;
    que.push(source);
    memset(dep,-1,sizeof(dep));
    dep[source]=0;
    while(!que.empty())
    {
        int node=que.front();
        que.pop();
        for(int i=head[node];~i;i=edge[i].next)
        {
            int v=edge[i].to;
            if(edge[i].capa>0&&dep[v]==-1)
            {
                dep[v]=dep[node]+1;
                if(v==sink) return true;
                que.push(v);
            }
        }
    }
    return dep[sink]!=-1;
}
int dfs(int node,int minn)
{
    if(node==sink||minn==0)
    {
        return minn;
    }
    int r=0;
    for(int i=head[node];~i;i=edge[i].next)
    {
        int v=edge[i].to;
        if(dep[v]==dep[node]+1&&edge[i].capa>0)
        {
            int tmp=dfs(v,min(edge[i].capa,minn));
            if(tmp>0)
            {
                edge[i].capa-=tmp;
                edge[i^1].capa+=tmp;
                r+=tmp;
                minn-=tmp;
                if(!minn) break;
            }
        }
    }
    if(!r) dep[node]=-1;
    return r;
}
int dinic()
{
    int maxflow=0;
    while(bfs())
    {
        maxflow+=dfs(source,inf);
    }
    return maxflow;
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
        int n,m;
        scanf("%d%d",&n,&m);
        source=0;
        sink=m+10;
        for(int i=1;i<=m;i++)
        {
            string a,b;
            cin>>a>>b;
            add(source,i,1);
            add(i,ma[a]+m,1);
            add(i,ma[b]+m,1);
        }
        for(int i=1;i<=6;i++)
        {
            add(m+i,sink,n);
        }
        printf("Case %d: %s\n",cas,dinic()==m?"YES":"NO");
    }
    return 0;
}
