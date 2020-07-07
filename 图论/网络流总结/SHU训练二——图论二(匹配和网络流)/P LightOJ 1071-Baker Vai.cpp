#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
#define MAXN 30000
#define MAXM 100000
#define INF 0x3f3f3f3f
struct node
{
	int u,v,cap,flow,cost,next;
}edge[MAXM];
int dis[MAXN],head[MAXN],vis[MAXN],pre[MAXN],map[200][200];
int n,m,cnt,sink,source;
void init()
{
	cnt=0;
	memset(head,-1,sizeof(head));
}
int num(int x,int y)
{
	return (x-1)*m+y;
}
void add(int a,int b,int c,int w)
{
	node E={a,b,c,0,w,head[a]};
	edge[cnt]=E;
	head[a]=cnt++;
	node E1={b,a,0,0,-w,head[b]};
	edge[cnt]=E1;
	head[b]=cnt++;
}
void getmap()
{
	int d=n*m;
	source=1,sink=num(n,m)+d;
	memset(map,0,sizeof(map));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&map[i][j]);
			int cap=1;
			if((i==1&&j==1)||(i==n&&j==m))
			cap=2;
			add(num(i,j),num(i,j)+d,cap,map[i][j]);
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(i+1<=n)
				add(num(i,j)+d,num(i+1,j),1,0);
			if(j+1<=m)
				add(num(i,j)+d,num(i,j+1),1,0);
		}
	}
}
bool BFS(int s,int t)
{
	queue<int>q;
	memset(vis,0,sizeof(vis));
	memset(dis,-INF,sizeof(dis));
	memset(pre,-1,sizeof(pre));
	vis[s]=1;
	dis[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=head[u];i!=-1;i=edge[i].next)
		{
			node E=edge[i];
			if(dis[E.v]<dis[E.u]+E.cost&&E.cap>E.flow)
			{
				dis[E.v]=dis[E.u]+E.cost;
				pre[E.v]=i;
				if(!vis[E.v])
				{
					vis[E.v]=1;
					q.push(E.v);
				}
			}
		}
	}
	return pre[t]!=-1;
}
void mcmf(int s,int t,int &cost,int &flow)
{
	flow=cost=0;
	while(BFS(s,t))
	{
		int Min=INF;
		for(int i=pre[t];i!=-1;i=pre[edge[i^1].v])
		{
			node E=edge[i];
			Min=min(Min,E.cap-E.flow);
		}
		for(int i=pre[t];i!=-1;i=pre[edge[i^1].v])
		{
			edge[i].flow+=Min;
			edge[i^1].flow-=Min;
			cost+=edge[i].cost*Min;
		}
		flow+=Min;
	}
}
int main()
{
	int t;
	int k=1;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		init();
		getmap();
		int flow,cost;
		mcmf(source,sink,cost,flow);
		printf("Case %d: %d\n",k++,cost-map[1][1]-map[n][m]);
	}
	return 0;
}
