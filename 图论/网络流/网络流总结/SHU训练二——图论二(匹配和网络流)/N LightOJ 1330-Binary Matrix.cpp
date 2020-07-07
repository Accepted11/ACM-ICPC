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
int dis[maxn];
int row[maxn];
int col[maxn];
int edge_index[110][110];
void init()
{
    memset(head,-1,sizeof(head));
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
        int sum_row=0;
        int sum_col=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&row[i]);
            sum_row+=row[i];
        }
        for(int i=1;i<=m;i++)
        {
            scanf("%d",&col[i]);
            sum_col+=col[i];
        }
        if(sum_row!=sum_col)
        {
            printf("Case %d: impossible\n",cas);
        }
        else
        {
            source=0;
            sink=n+m+1;
            for(int i=1;i<=n;i++)
            {
                add(source,i,row[i]);
                edge_index[source][i]=cnt-1;
            }
            for(int i=1;i<=m;i++)
            {
                add(n+i,sink,col[i]);
                edge_index[n+i][sink]=cnt-1;
            }
            for(int i=1;i<=n;i++)
            {
                for(int j=1;j<=m;j++)
                {
                    add(i,n+j,1);
                    edge_index[i][n+j]=cnt-1;
                }
            }
            int res=dinic();
            if(res==sum_col)
            {
                printf("Case %d:\n",cas);
                for(int i=1;i<=n;i++)
                {
                    for(int j=1;j<=m;j++)
                    {
                        int flow=edge[edge_index[i][j+n]].capa;
                        edge[edge_index[i][j+n]].capa=edge[edge_index[i][j+n]^1].capa=0;
                        if(flow)
                        {
                            edge[edge_index[source][i]^1].capa=edge[edge_index[j+n][sink]^1].capa=1;
                            if(dinic())
                            {
                                flow=0;
                            }
                            else
                            {
                                edge[edge_index[source][i]^1].capa=edge[edge_index[j+n][sink]^1].capa=0;
                            }
                        }
                        printf("%d",flow);
                        if(j==m) putchar('\n');
                    }
                }
            }
            else
            {
                printf("Case %d: impossible\n",cas);
            }
        }
    }
    return 0;
}
