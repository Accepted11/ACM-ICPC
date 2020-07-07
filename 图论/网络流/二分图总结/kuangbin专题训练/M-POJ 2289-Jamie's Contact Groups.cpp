#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define pb push_back
#define mem(a) memset(a, 0, sizeof(a))
#define Buff ios::sync_with_stdio(false)
#define reads(s) scanf("%s", s)
#define read(a)  scanf("%d", &a)
#define readc(a) scanf("%c", &a)
typedef long long ll;
using namespace std;
const int INF = 2e9 + 7;
const int N = 1010;
const int M = 1001;
const double eps = 1e-8;

int vis[N], dfn;

struct node
{
    int cnt;
    int kid[N];
}match[N];

//int dir[2][4] = {{0, 0, 1, -1}, {1, -1, 0, 0}};
vector<int> G[N];
int n, m;

void init()
{
    dfn = 0;
    for(int i = 0; i <= n; i++) G[i].clear();

    char str[20], op;
    for(int i = 1, x; i <= n; i++)
    {
        reads(str);
        while(1)
        {
            read(x); readc(op);
            G[i].pb(x + 1);
            if(op == '\n') break;
        }
    }
}

bool dfs(int u, int mid)
{
    for(int i = 0, v; i < G[u].size(); i++)
    {
        v = G[u][i];
        if(vis[v] == dfn) continue;
        vis[v] = dfn;
        if(match[v].cnt < mid)
        {
            match[v].kid[++match[v].cnt] = u;
            return true;
        }
        for(int j = 1; j <= match[v].cnt; j++)
        {
            if(dfs(match[v].kid[j], mid))
            {
                match[v].kid[j] = u;
                return true;
            }
        }
    }
    return false;
}

bool judge(int mid)
{
    mem(match);
    mem(vis); dfn = 0;
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        dfn++;
        if(!dfs(i, mid)) return false;
    }
    return 1;
}

void work()
{
    init();

    int L = 1, R = n, mid;
    while(L < R)
    {
        mid = (L + R) >> 1;
        if(judge(mid)) R = mid;
        else           L = mid + 1;
    }

    printf("%d\n", R);
}

signed main()
{
    while(~scanf("%d%d", &n, &m), n + m)
        work();
    return 0;
}


// 一对多的多重匹配问题，可以对match 的容量进行扩展
