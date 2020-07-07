#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 220*220
#define MAXM 220*220*5
#define INF 0x3f3f3f3f
int u[MAXN],v[MAXN],c[MAXN],n,m,k;
int head[MAXN],dis[MAXN],cnt,cur[MAXN],vis[MAXN];
struct node
{
	int u,v,cap,flow,next;
}edge[MAXM];
void init()
{
	memset(head,-1,sizeof(head));
	cnt=0;
}
void add(int a,int b,int w)
{
	node E={a,b,w,0,head[a]};
	edge[cnt]=E;
	head[a]=cnt++;
	node E1={b,a,0,0,head[b]};
	edge[cnt]=E1;
	head[b]=cnt++;
}
bool BFS(int s,int t)
{
	queue<int>q;
	memset(vis,0,sizeof(vis));
	memset(dis,-1,sizeof(dis));
	q.push(s);
	dis[s]=0;
	vis[s]=1;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u];i!=-1;i=edge[i].next)
		{
			node E=edge[i];
			if(E.cap>E.flow&&!vis[E.v])
			{
				dis[E.v]=dis[E.u]+1;
				vis[E.v]=1;
				if(E.v==t) return true;
				q.push(E.v);
			}
		}
	}
	return false;
}
int DFS(int x,int a,int e)
{
	if(a==0||e==x) return a;
	int flow=0,f;
	for(int &i=cur[x];i!=-1;i=edge[i].next)
	{
		node &E=edge[i];
		if(dis[E.v]==dis[E.u]+1&&(f=DFS(E.v,min(E.cap-E.flow,a),e))>0)
		{
			flow+=f;
			a-=f;
			edge[i].flow+=f;
			edge[i^1].flow-=f;
			if(a==0) break;
		}
	}
	return flow;
}
int MAXflow(int s,int t)
{
	int flow=0;
	while(BFS(s,t))
	{
		memcpy(cur,head,sizeof(head));
		flow+=DFS(s,INF,t);
	}
	return flow;
}
bool judge(int x)
{
	init();
	for(int i=0;i<m;i++)
	{
		if(c[i]<=x)
		{
			if(u[i]==0)
			add(u[i],v[i],1);
			else
			add(u[i]+1+n,v[i],1);
		}
	}
	for(int i=1;i<=n+1;i++)
	add(i,i+1+n,1);
	return MAXflow(0,n+1)>=k;
}
int main()
{
	int Case=1;
	int t; scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d",&n, &m);
		memset(u,0,sizeof(u));
		memset(v,0,sizeof(v));
		memset(c,0,sizeof(c));
		int r=0;
		for(int i=0;i<m;i++)
		{
			scanf("%d%d%d",&u[i],&v[i],&c[i]);
			r=max(c[i],r);
			if(u[i]>v[i])
			swap(u[i],v[i]);
		}
		scanf("%d",&k);
		int l=0,ans=0;
		while(r>=l)
		{
			int mid=(l+r)/2;
			if(judge(mid))
			{
				ans=mid;
				r=mid-1;
			}
			else
			l=mid+1;
		}
		printf("Case %d: ",Case++);
		if(ans==0)
			printf("no solution\n");
		else
			printf("%d\n",ans);
	}
	return 0;
}
