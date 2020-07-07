#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define read(a) scanf("%d", &a)
#define readf(a) scanf("%lf", &a)
#define pb push_back
#define mem(a) memset(a, 0, sizeof(a))
#define Buff ios::sync_with_stdio(false)
typedef long long ll;
using namespace std;
const int INF = 1e9 + 7;
const int N = 2e4 + 7;
const int M = 1e6 + 7;
const double eps = 1e-8;
int n, m, tot;
double T1, T2, V;
vector<int> G[N];
int match[N], vis[N];
struct Point
{
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y){}
}p1[N], p2[N];

struct node
{
    int id;
    double t;
}a[N];

double getDis(const Point& A, const Point& B)
{
    double x = A.x - B.x;
    double y = A.y - B.y;
    return sqrt(x * x + y * y);
}

void init()
{
    mem(match);
    for(int i = 0; i <= m; i++)
        G[i].clear();
}

bool dfs(int u)
{
    for(int v : G[u])
    {
        if(vis[v]) continue;
        vis[v] = 1;
        if(!match[v] || dfs(match[v]))
        {
            match[v] = u;
            return true;
        }
    }
    return false;
}

bool judge(double mid)
{
    init();

    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= tot; j++)
            if(a[j].t + getDis(p1[a[j].id], p2[i]) / V <= mid)
                G[i].pb(j);


    for(int i = 1; i <= m; i++)
    {
        mem(vis);
        if(!dfs(i)) return false;
    }
    return true;
}

signed main()
{
    read(n); read(m); readf(T1); readf(T2);readf(V);
    T1 /= 60.00;
    for(int i = 1; i <= m; i++)
    {
        readf(p2[i].x); readf(p2[i].y);
    }
    for(int i = 1; i <= n; i++)
    {
        readf(p1[i].x); readf(p1[i].y);
    }

    tot = n * m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
        {
            a[(i - 1) * m + j].id = i;
            a[(i - 1) * m + j].t = (j - 1) * (T1 + T2) + T1;
        }

    double l = T1, r = 1e5, mid, ans = 0.00;
    while(r - l >= eps)
    {
        mid = (l + r) / 2;
        if(judge(mid)) r = mid - eps, ans = mid;
        else           l = mid + eps;
    }
    printf("%.6lf\n", ans);
    return 0;
}
