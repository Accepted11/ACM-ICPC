#pragma GCC optimize(2)
#include<bits/stdc++.h>

#define pb push_back
#define mem(a, b) memset(a, b, sizeof(a))

typedef long long ll;
using namespace std;
const int INF = 2e9 + 7;
const int N = 3000 + 7;
const int M = 1000 + 7;

vector<int> G[N];
int dx[N], dy[N];
int lx[N], ly[N];
int vis[N], dis;
int nx, ny;
int n, m;

void builGraph()
{
    for(int i = 0; i < N; i++)
        G[i].clear();
    cin >> n >> m;
    nx = ny = n;

    for(int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        G[u].pb(v);
    }
}

int bfs()
{
    queue<int> q;
    while(q.size()) q.pop();
    dis = INF;
    mem(dx, -1); mem(dy, -1);
    for(int i = 1; i <= nx; i++)
        if(lx[i] == -1)  q.push(i), dx[i] = 0;

    while(q.size())
    {
        int u = q.front(); q.pop();
        if(dx[u] > dis) break;
        for(int v : G[u])
        {
            if(dy[v] == -1)
            {
                dy[v] = dx[u] + 1;
                if(ly[v] == -1)      dis = dy[v];
                else
                {
                    dx[ly[v]] = dy[v] + 1;
                    q.push(ly[v]);
                }
            }
        }
    }
    return dis != INF;
}

int dfs(int u)
{
    for(int v : G[u])
    {
        if(!vis[v] && dy[v] == dx[u] + 1)
        {
            vis[v] = 1;
            if(ly[v] != -1 && dy[v] == dis) continue;
            if(ly[v] == -1 || dfs(ly[v]))
            {
                lx[u] = v;
                ly[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int HK()
{
    int ans = 0;
    mem(lx, -1); mem(ly, -1);
    while(bfs())
    {
        mem(vis, 0);
        for(int i = 1; i <= nx; i++)
            if(lx[i] == -1)
                ans += dfs(i);
    }
    return ans;
}

signed main()
{
    builGraph();
    cout << HK() << endl;
    return 0;
}
