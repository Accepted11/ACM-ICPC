#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=400;
const int maxm=10010;
const int inf=0x3f3f3f3f;
typedef pair<int,int> P;
struct Node
{
    int to;
    int capa;
    int cost;
    int next;
}edge[maxm];
int n,k,m;
int cnt;
int source,sink;
int head[maxn];
char map[maxn][maxn];
int dis[maxn];
bool vis[maxn];
int pre[maxn];
int rec[maxn];
int num[maxn];
bool vis_map[maxn][maxn];
int diss[maxn][maxn];
int dirx[]={0,1,0,-1};
int diry[]={1,0,-1,0};
int mill[50][50];
void init()
{
	cnt=0;
	memset(head,-1,sizeof(head));
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
	queue<int> que;
	que.push(source);
	memset(dis,inf,sizeof(dis));
	memset(vis,false,sizeof(vis));
	memset(rec,-1,sizeof(rec));
	memset(pre,-1,sizeof(pre));
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
	return mincost;
}
int getIndex(int x,int y)
{
    return (x-1)*n+y;
}
void bfs(int x,int y)
{
    queue<P> que;
    que.push(make_pair(x,y));
    memset(vis_map,false,sizeof(vis_map));
    diss[x][y]=0;
    while(!que.empty())
    {
        P now=que.front();
        que.pop();
        int tmpx=now.first;
        int tmpy=now.second;
        for(int i=0;i<4;i++)
        {
            int nx=tmpx+dirx[i];
            int ny=tmpy+diry[i];
            if(nx>=1&&nx<=n&&ny>=1&&ny<=n&&!vis_map[nx][ny]&&map[nx][ny]!='#')
            {
                que.push(make_pair(nx,ny));
                vis_map[nx][ny]=true;
                diss[nx][ny]=diss[tmpx][tmpy]+1;
                if(map[nx][ny]=='m')
                {
                    add(map[x][y]-'A'+1,mill[nx][ny]+k,1,diss[nx][ny]);
                }
            }
        }
    }
    return;
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
        scanf("%d%d%d",&n,&k,&m);
        getchar();
        source=0;
        sink=k+m+1;
        for(int i=1;i<=n;i++)
        {
            scanf("%s",map[i]);
        }
        for(int i=1;i<=k;i++)
        {
            scanf("%d",&num[i]);
            add(source,i,num[i],0);
        }
        for(int i=1;i<=m;i++)
        {
            add(k+i,sink,1,0);
        }
        int mill_index=1;
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(map[i][j]=='m')
                {
                    mill[i][j]=mill_index++;
                }
            }
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(map[i][j]>='A'&&map[i][j]<='Z')
                {
                    bfs(i,j);
                }
            }
        }
        printf("Case %d: %d\n",cas,mcmf());
    }
    return 0;
}
