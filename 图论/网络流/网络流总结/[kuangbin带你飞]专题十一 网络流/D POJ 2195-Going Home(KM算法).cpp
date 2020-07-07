#pragma GCC optimize(2)
//#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<cstring>
#include<queue>
#include<algorithm>

#define read(a) scanf("%d", &a)
#define readl(a) scanf("%lld", &a)
#define reads(a) scanf("%s", a)
#define readc(a) scanf("%c", &a)
#define pb push_back
#define mem(a) memset(a, 0, sizeof(a))
#define Buff ios::sync_with_stdio(false)
typedef long long ll;
using namespace std;
const int INF = 1e9 + 7;
const int N = 5e3 + 7;
const int M = 1e6 + 7;

int vx[N], vy[N];
int lx[N], ly[N];
int match[N];
int w[N][N];
int n, m;
char mp[N][N];
struct point
{
    int x, y;
    point(int x = 0, int y = 0) : x(x), y(y) {}
}A[N], B[N];
int Abs(int x) {return x > 0 ? x : -x;}
bool dfs(int i)
{
    vx[i] = 1;
    for(int j = 1; j <= n; j++)
        if(!vy[j] && lx[i] + ly[j] - w[i][j] == 0)
        {
            vy[j] = 1;
            if(!match[j] || dfs(match[j]))
            {
                match[j] = i;
                return true;
            }
        }

    return false;
}

void update()
{
    int delta = INF;
    for(int i = 1; i <= n; i++)
        if(vx[i])
            for(int j = 1; j <= n; j++)
                if(!vy[j])
                    delta = min(delta, lx[i] + ly[j] - w[i][j]);
    for(int i = 1; i <= n; i++)
    {
        if(vx[i]) lx[i] -= delta;
        if(vy[i]) ly[i] += delta;
    }
}

void buildGraph()
{
    int cnt1 = 0, cnt2 = 0;
    for(int i = 0; i < n; i++)
        reads(mp[i]);
    for(int x = 0; x < n; x++)
        for(int y = 0; y < m; y++)
        {
            if(mp[x][y] == 'H') A[++cnt1] = point(x + 1, y + 1);
            if(mp[x][y] == 'm') B[++cnt2] = point(x + 1, y + 1);
        }
    for(int i = 1; i <= cnt1; i++)
        for(int j = 1; j <= cnt2; j++)
            w[i][j] = -(Abs(A[i].x - B[j].x) + Abs(A[i].y - B[j].y));
    n = cnt1;
}

int KM()
{
    buildGraph();
    for(int i = 1; i <= n; i++)
    {
        match[i] = lx[i] = ly[i] = 0;
        for(int j = 1; j <= n; j++)
            lx[i] = max(lx[i], w[i][j]);
    }

    for(int i = 1; i <= n; i++)
        while(1)
        {
            mem(vx); mem(vy);
            if(dfs(i)) break;
            else       update();
        }

    int ans = 0;
    for(int i = 1; i <= n; i++)
        ans += -w[match[i]][i];
    return ans;
}

signed main()
{
    while(~scanf("%d%d", &n, &m))
        if(n == 0 || m == 0) break;
        else                 printf("%d\n", KM());
    return 0;
}

