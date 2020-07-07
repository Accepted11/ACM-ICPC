#pragma GCC optimize(2)
//#include<bits/stdc++.h>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<cmath>

#define read(a) scanf("%d", &a)
#define readl(a) scanf("%lld", &a)
#define reads(a) scanf("%s", a)
#define readc(a) scanf("%c", &a)
#define readf(a) scanf("%lf", &a)
#define debug(a, b) printf("%s = %d\n", a, b)
#define debug1(a, i, b) printf("%s[%d] = %d", a, i, b)
#define debug2(a, c, n) for(int i = 1; i <= n; i++) printf("%s[%d] = %d%c", a, i, c[i], i == n ? '\n':' ')
#define debug3(a, n, m, c) for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) printf("%s[%d][%d] = %d%c", a, i, j, c[i][j], j == m ? '\n' : ' ')
#define show(a) putchar(a)
#define pb push_back
#define _rand mt19937 RAND(time(0))
#define mem(a) memset(a, 0, sizeof(a))
#define Buff ios::sync_with_stdio(false)
typedef long long ll;
using namespace std;
const double INF = 2e9 + 7;
const int N = 100 + 7;
const int M = 1e6 + 7;
const double eps = 1e-8;
double w[N][N], la[N], lb[N];
bool va[N], vb[N];
int match[N];
int n;
double delta;

struct Point
{
    double x, y;
}p1[N], p2[N];

void update()
{
    double a = INF;
    for(int i = 1; i <= n; i++)
        if(va[i])
            for(int j = 1; j <= n; j++)
                if(!vb[j])
                    a = min(a, la[i] + lb[j] - w[i][j]);

    for(int i = 1; i <= n; i++)
    {
        if(va[i])  la[i] -= a;
        if(vb[i])  lb[i] += a;
    }
}
bool dfs(int x)
{
    va[x] = 1;
    for(int y = 1; y <= n; y++)
        if(!vb[y])
            if(fabs(la[x] + lb[y] - w[x][y]) < eps)
            {
                vb[y] = 1;
                if(!match[y] || dfs(match[y]))
                {
                    match[y] = x;
                    return true;
                }
            }
//            else delta = min(delta, la[x] + lb[y] - w[x][y]);
    return false;
}

void KM()
{
    for(int i = 1; i <= n; i++)
    {
        match[i] = 0.00;
        la[i] = 0.00; lb[i] = 0.00;
//        for(int j = 1; j <= n; j++)
//            la[i] = max(la[i], w[i][j]);
    }
    for(int i = 1; i <= n; i++)
        while(1)
        {
            for(int j = 1; j <= n; j++)
                va[j] = vb[j] = 0;
//            delta = INF;
            if(dfs(i)) break;
//            cout << "delta = " <<delta << endl;
            update();
        }

    for(int i = 1; i <= n; i++)
        printf("%d\n", match[i]);
}

double getDis(const Point& A, const Point& B)
{
    double x = A.x - B.x;
    double y = A.y - B.y;
    return sqrt(x * x + y * y);
}

signed main()
{
    while(~scanf("%d", &n))
    {
//        mem(match); mem(_match);
        mem(w);
        for(int i = 1; i <= n; i++)
            readf(p1[i].x), readf(p1[i].y);
        for(int i = 1; i <= n; i++)
            readf(p2[i].x), readf(p2[i].y);
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                w[i][j] = -getDis(p2[i], p1[j]);
        KM();
    }
    return 0;
}

