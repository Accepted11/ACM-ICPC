#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define MAXN 500
char s[25][25];
int used[MAXN],pipei[MAXN];
int map[25][25],m,n,oddnum,evennum,k=1;
vector<int>G[MAXN];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
void getmap()
{
	memset(map,0,sizeof(0));
	for(int i=0;i<500;i++)
	G[i].clear();
	oddnum=evennum=0;
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)
	{
		map[i][j]=-1;
		if(s[i][j]=='*')
		{
			if((i+j)&1)
			map[i][j]=++oddnum;
			else
			map[i][j]=++evennum;
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(s[i][j]=='*'&&((i+j)&1))
			{
				for(int k=0;k<4;k++)
				{
					int x=i+dx[k];
					int y=j+dy[k];
					if(x<0||x>=n||y<0||y>=m)
					continue;
					if(s[x][y]=='*')
					G[map[i][j]].push_back(map[x][y]);
				}
			}
		}
	}
}
int find(int x)
{
	for(int i=0;i<G[x].size();i++)
	{
		int y=G[x][i];
		if(!used[y])
		{
			used[y]=1;
			if(pipei[y]==-1||find(pipei[y]))
			{
				pipei[y]=x;
				return 1;
			}
		}
	}
	return 0;
}
void solve()
{
	memset(pipei,-1,sizeof(pipei));
	int sum=0;
	for(int i=1;i<=oddnum;i++)
	{
		memset(used,0,sizeof(used));
		sum+=find(i);
	}
	printf("Case %d: %d\n",k++,oddnum+evennum-sum);
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		memset(s,'\0',sizeof(s));
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++)
		scanf("%s",s[i]);
		getmap();
		solve();
	}
	return 0;
}
