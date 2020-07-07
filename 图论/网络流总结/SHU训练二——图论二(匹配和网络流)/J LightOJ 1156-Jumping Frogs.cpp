#include<stdio.h>
#include<string.h>
#include<vector>
#define INF 1<<31-1
#define min(x,y)(x<y?x:y)
using namespace std;
struct Edge
{
	int to;
	int cap;
	int rev;
};
struct Point
{
	int dis;
	int state;
}p[210];
vector<Edge>g[210];
int used[210];
int left,right;
void add_edge(int from,int to,int cap)
{
	g[from].push_back((Edge){to,cap,g[to].size()});
	g[to].push_back((Edge){from,0,g[from].size()-1});
}
int dfs(int u,int t,int f)
{
	if(u==t)
	  return f;
	  used[u]=1;
	for(int i=0;i<g[u].size();i++)
	{
		Edge &e=g[u][i];
		int v=e.to;
		if(!used[v]&&e.cap>0)
		{
			int d=dfs(v,t,min(e.cap,f));
			if(d>0)
			{
				e.cap-=d;
				g[e.to][e.rev].cap+=d;
				return d;
			}
		}
	}
	return 0;
}
bool max_flow(int s,int t)
{
	int res=0;
	while(1)
	{
		memset(used,0,sizeof(used));
		int d=dfs(s,t,INF);
		if(d<=0)
			break;
		res+=d;
		if(res>=2)
			break;
	}
	if(res>=2)                   //如果能走2次就没必要在继续判断了
		return true;
	return false;
}
bool judge(Point p1,Point p2,int d)   //判断两个石头的距离是否小于能跳的最远距离
{
	int res=p1.dis-p2.dis;
	if(res<0) res=-res;
	if(res<=d)
		return true;
	return false;
}
void makeNew(int s,int t,int n,int d)
{
	int i,j;
	for(i=s;i<=t;i++)
		g[i].clear();
	for(i=1;i<=n;i++)            //拆点自身与自身建一条边，如果是大石头流量就2，否则1
		{
			if(p[i].state==1)
			{
				add_edge(i,i+n,2);
			}
			else
			{
				add_edge(i,i+n,1);
			}
		}
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
			{
				if(i!=j&&judge(p[i],p[j],d))
					add_edge(i+n,j,2);
			}
		for(i=1;i<=n;i++)
		{
			if(judge(p[s],p[i],d))
			add_edge(s,i,2);
			if(judge(p[t],p[i],d))
			add_edge(i+n,t,2);
		}
		if(judge(p[s],p[t],d))
			add_edge(s,t,2);
}
int solve(int s,int t,int n)
{
	while(left<right-1)            //用二分枚举每次能跳的最大的距离
	{
		int mid=(left+right)/2;
		 makeNew(s,t,n,mid);
		 if(max_flow(s,t))
		 	right=mid;
		else
			left=mid;
	}
	return right;
}
int main()
{
	int c,s,t,n,d,i,k=0,x;
	char ch;
	scanf("%d",&c);
	while(c--)
	{
		scanf("%d%d",&n,&d);
		right=INF;
		left=0;
		s=0; t=n*2+1;
		p[s].dis=0;
		p[t].dis=d;
		for(i=1;i<=n;i++)
		{
			scanf(" %c-%d",&ch,&x);
			if(ch=='B')
				p[i].state=1;
			else
				p[i].state=0;
			p[i].dis=x;
		}
		int res=solve(s,t,n);
		printf("Case %d: %d\n",++k,res);
	}
	return 0;
}
