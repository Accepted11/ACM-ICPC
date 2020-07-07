#include<iostream>
#include<cstdio>
#include<cstring>
#include<stack>
#include<queue>
#include<vector>
using namespace std;
const int maxn=2010;
const int maxm=1e6+7;
struct Node
{
	int to;
	int next;
}edge[maxm];
struct Match
{
	int to;
	int next;
}match_edge[maxm];
int match_cnt;
int match_head[maxn];
int cnt;
int iindex;
int scc_cnt;
int head[maxn];
int dfn[maxn];
int low[maxn];
bool vis[maxn];
int belong[maxn];
int match[maxn];
vector<int> G[maxn];
stack<int> sta;
void init()
{
	memset(head,-1,sizeof(head));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(belong,0,sizeof(belong));
	memset(match_head,-1,sizeof(match_head));
	while(!sta.empty()) sta.pop();
	for(int i=0;i<maxn;i++) G[i].clear();
	match_cnt=scc_cnt=cnt=iindex=0;
	return;
}
void add(int u,int v)
{
	edge[cnt].to=v;
	edge[cnt].next=head[u];
	head[u]=cnt++;
	return;
}
void addedge(int u,int v)
{
	match_edge[match_cnt].to=v;
	match_edge[match_cnt].next=match_head[u];
	match_head[u]=match_cnt++;
	return;
}
void tarjan(int node)
{
	dfn[node]=low[node]=++iindex;
	sta.push(node);
	vis[node]=true;
	for(int i=head[node];~i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[node]=min(low[node],low[v]);
		}
		else if(vis[v])
		{
			low[node]=min(low[node],dfn[v]);
		}
	}
	if(dfn[node]==low[node])
	{
		int v=-1;
		++scc_cnt;
		while(node!=v)
		{
			v=sta.top();
			sta.pop();
			vis[v]=false;
			belong[v]=scc_cnt;
		}
	}
	return;
}
void bfs(int node)
{
	queue<int> que;
	int len=G[node].size();
	vis[node]=true;
	for(int i=0;i<len;i++)
	{
		int v=G[node][i];
		if(vis[v]) continue;
		else
		{
			que.push(v);
			vis[v]=true;
			add(node,v);
		}
	}
	while(!que.empty())
	{
		int now=que.front();
		que.pop();
		int now_len=G[now].size();
		for(int i=0;i<now_len;i++)
		{
			int v=G[now][i];
			if(vis[v]) continue;
			else
			{
				vis[v]=true;
				que.push(v);
				add(node,v);
			}
		}
	}
	return;
}
bool dfs(int node)
{
	for(int i=match_head[node];~i;i=match_edge[i].next)
	{
		int v=match_edge[i].to;
		if(!vis[v])
		{
			vis[v]=true;
			if(match[v]==-1||dfs(match[v]))
			{
				match[v]=node;
				return true;
			}
		}
	}
	return false;
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
		for(int i=0;i<m;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			G[u].push_back(v);
		}
		for(int i=1;i<=n;i++)
		{
			memset(vis,false,sizeof(vis));
			bfs(i);
		}
		memset(vis,false,sizeof(vis));
		for(int i=1;i<=n;i++)
		{
			if(!dfn[i])
			{
				tarjan(i);
			}
		}
		for(int node=1;node<=n;node++)
		{
			for(int i=head[node];~i;i=edge[i].next)
			{
				int v=edge[i].to;
				if(belong[node]!=belong[v])
				{
					addedge(belong[node],belong[v]);
				}
			}
		}
		int ans=0;
		memset(match,-1,sizeof(match));
		for(int i=1;i<=scc_cnt;i++)
		{
			memset(vis,false,sizeof(vis));
			if(dfs(i))
			{
				ans++;
			}
		}
		printf("Case %d: %d\n",cas,scc_cnt-ans);
	}
	return 0;
}
