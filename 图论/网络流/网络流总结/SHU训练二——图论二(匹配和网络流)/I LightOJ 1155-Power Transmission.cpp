#include<stdio.h>
#include<string.h>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;
#define MAXM 300
#define MAXN 50000
#define INF 0x3f3f3f
int dis[MAXM],vis[MAXM],cur[MAXM],head[MAXM];
int n,top,need[MAXM];
struct node
{
	int u,v,cap,flow,next;
}edge[MAXN];
void init()
{
	top=0;
	memset(head,-1,sizeof(head));
}
void add(int a,int b,int c)
{
	node E1={a,b,c,0,head[a]};
	edge[top]=E1;
	head[a]=top++;
	node E2={b,a,0,0,head[b]};
	edge[top]=E2;
	head[b]=top++;
}
void getmap()
{
	scanf("%d",&n);
	memset(need,0,sizeof(need));
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&need[i]);
		add(i,i+n,need[i]);
	}
	int m;
	scanf("%d",&m);
	while(m--)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add(a+n,b,c);
	}
	int b,d;
	scanf("%d%d",&b,&d);
	while(b--)
	{
		int c;
		scanf("%d",&c);
		add(0,c,need[c]);
	}
	while(d--)
	{
		int c;
		scanf("%d",&c);
		add(c+n,2*n+1,need[c]);
	}
}
bool bfs(int s,int t)
{
	queue<int>q;
	memset(vis,0,sizeof(vis));
	memset(dis,-1,sizeof(dis));
	q.push(s);
	vis[s]=1;
	dis[s]=0;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u];i!=-1;i=edge[i].next)
		{
			node E=edge[i];
			if(E.cap>E.flow&&!vis[E.v])
			{
				vis[E.v]=1;
				dis[E.v]=dis[E.u]+1;
				if(E.v==t) return true;
				q.push(E.v);
			}
		}
	}
	return false;
}
int dfs(int x,int a,int e)
{
	if(x==e||a==0)
	return a;
	int flow=0,f;
	for(int i=cur[x];i!=-1;i=edge[i].next)
	{
		node &E=edge[i];
		if(dis[E.v]==dis[E.u]+1&&(f=dfs(E.v,min(a,E.cap-E.flow),e))>0)
		{
			E.flow+=f;
			edge[i^1].flow-=f;
			a-=f;
			flow+=f;
			if(a==0) break;
		}
	}
	return flow;
}
int MAXflow(int s,int t)
{
	int flow=0;
	while(bfs(s,t))
	{
		memcpy(cur,head,sizeof(head));
		flow+=dfs(s,INF,t);
	}
	return flow;
}
int main()
{
	int t;
	int k=1;
	scanf("%d",&t);
	while(t--)
	{
		init();
		getmap();
		printf("Case %d: %d\n",k++,MAXflow(0,2*n+1));
	}
	return 0;
}
