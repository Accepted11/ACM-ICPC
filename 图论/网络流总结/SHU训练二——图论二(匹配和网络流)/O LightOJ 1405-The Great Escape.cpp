#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=2e4+100;
const int maxm=2000010;
const int inf=0x3f3f3f3f;
struct Node
{
    int to;
    int capa;
    int next;
}edge[maxm];
int n,m;
int cnt;
int nv;
int source,sink;
int head[maxn];
char map[110][110];
int dep[maxn];
int dirx[]={0,1,0,-1};
int diry[]={1,0,-1,0};
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
int getIndex(int x,int y)
{
    return (x-1)*m+y;
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
        scanf("%d%d",&n,&m);
        source=0;
        sink=n*m*2+10;
        getchar();
        for(int i=1;i<=n;i++)
        {
            scanf("%s",map[i]+1);
        }
        int sum=0;
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                if(i==1||i==n||j==1||j==m)
                {
                    add(getIndex(i,j)+n*m,sink,1);
                }
                add(getIndex(i,j),getIndex(i,j)+n*m,1);
                for(int k=0;k<4;k++)
                {
                    int x=i+dirx[k];
                    int y=j+diry[k];
                    if(x>=1&&x<=n&&y>=1&&y<=m)
                    {
                        add(getIndex(i,j)+n*m,getIndex(x,y),1);
                    }
                }
                if(map[i][j]=='*')
                {
                    sum++;
                    add(source,getIndex(i,j),1);
                }
            }
        }
        if(dinic()==sum) printf("Case %d: yes\n",cas);
        else printf("Case %d: no\n",cas);
    }
    return 0;
}
