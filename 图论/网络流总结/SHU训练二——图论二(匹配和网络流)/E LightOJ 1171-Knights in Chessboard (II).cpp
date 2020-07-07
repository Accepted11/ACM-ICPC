#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
#define INF (1<<30)
#define MAXN 44444
#define MAXM 44444*22

struct Edge{
    int v,cap,flow,next;
}edge[MAXM];
int vs,vt,NE,NV;
int head[MAXN];

void addEdge(int u,int v,int cap){
    edge[NE].v=v; edge[NE].cap=cap; edge[NE].flow=0;
    edge[NE].next=head[u]; head[u]=NE++;
    edge[NE].v=u; edge[NE].cap=0; edge[NE].flow=0;
    edge[NE].next=head[v]; head[v]=NE++;
}

int level[MAXN];
int gap[MAXN];
void bfs(){
    memset(level,-1,sizeof(level));
    memset(gap,0,sizeof(gap));
    level[vt]=0;
    gap[level[vt]]++;
    queue<int> que;
    que.push(vt);
    while(!que.empty()){
        int u=que.front(); que.pop();
        for(int i=head[u]; i!=-1; i=edge[i].next){
            int v=edge[i].v;
            if(level[v]!=-1) continue;
            level[v]=level[u]+1;
            gap[level[v]]++;
            que.push(v);
        }
    }
}

int pre[MAXN];
int cur[MAXN];
int ISAP(){
    bfs();
    memset(pre,-1,sizeof(pre));
    memcpy(cur,head,sizeof(head));
    int u=pre[vs]=vs,flow=0,aug=INF;
    gap[0]=NV;
    while(level[vs]<NV){
        bool flag=false;
        for(int &i=cur[u]; i!=-1; i=edge[i].next){
            int v=edge[i].v;
            if(edge[i].cap!=edge[i].flow && level[u]==level[v]+1){
                flag=true;
                pre[v]=u;
                u=v;
                //aug=(aug==-1?edge[i].cap:min(aug,edge[i].cap));
                aug=min(aug,edge[i].cap-edge[i].flow);
                if(v==vt){
                    flow+=aug;
                    for(u=pre[v]; v!=vs; v=u,u=pre[u]){
                        edge[cur[u]].flow+=aug;
                        edge[cur[u]^1].flow-=aug;
                    }
                    //aug=-1;
                    aug=INF;
                }
                break;
            }
        }
        if(flag) continue;
        int minlevel=NV;
        for(int i=head[u]; i!=-1; i=edge[i].next){
            int v=edge[i].v;
            if(edge[i].cap!=edge[i].flow && level[v]<minlevel){
                minlevel=level[v];
                cur[u]=i;
            }
        }
        if(--gap[level[u]]==0) break;
        level[u]=minlevel+1;
        gap[level[u]]++;
        u=pre[u];
    }
    return flow;
}

bool map[222][222];
int dx[]={1,1,-1,-1,2,2,-2,-2};
int dy[]={2,-2,2,-2,1,-1,1,-1};
int main(){
	int t,n,m,k;
	scanf("%d",&t);
	for(int cse=1; cse<=t; ++cse){
		scanf("%d%d%d",&n,&m,&k);
		memset(map,0,sizeof(map));
		int a,b,tot=n*m;
		while(k--){
			scanf("%d%d",&a,&b);
			--a; --b;
			map[a][b]=1;
		}
		for(int i=0; i<n; ++i){
			for(int j=0; j<m; ++j){
				if(map[i][j]) --tot;
			}
		}
		vs=n*m; vt=vs+1; NV=vt+1; NE=0;
		memset(head,-1,sizeof(head));
		for(int i=0; i<n*m; ++i){
			int x=i/m,y=i%m;
			if(map[x][y]) continue;
			if(x+y&1) addEdge(i,vt,1);
			else{
				addEdge(vs,i,1);
				for(int j=0; j<8; ++j){
					int nx=x+dx[j],ny=y+dy[j];
					if(nx<0 || nx>=n || ny<0 || ny>=m || map[nx][ny]) continue;
					addEdge(i,nx*m+ny,1);
				}
			}
		}
		printf("Case %d: %d\n",cse,tot-ISAP());
	}
	return 0;
}
