/*
����ͼ���ƥ�䣺Kuhn-Munkers�㷨�����еı�Ҫ�����Ǳ������һ���걸ƥ��
    �����һ�����Ȩƥ��(��һ���걸)���԰Ѳ����ڵı�Ȩֵ��Ϊ0��
pro1:
    �����ͼ�����ƥ�䣨�����Ȩ�걸ƥ�䣩
pro2:
    �����ͼ����СȨ�걸ƥ��
    ˼·��ֻ�轫���еı�Ȩֵȡ���෴���������Ȩ�걸ƥ�䣬ƥ���ֵ��ȡ�෴������
pro3:
    �����ͼ�ĳ˻�����걸ƥ��
    ˼·����ÿ����Ȩȡ��Ȼ������Ȼ��������Ȩƥ�䣬��õĽ��a�����e^a��������ƥ��
*/

#pragma GCC optimize(2)
#include<bits/stdc++.h>
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
const int INF = 1e9 + 7;
const int N = 300 + 7;
const int M = 1000 + 7;
const double eps = 1e-6;
int vx[N], vy[N];
int lx[N], ly[N];
int match[N];
int w[N][N];
int n, m;

bool dfs(int i)
{
    vx[i] = 1;
    for(int j = 1; j <= n; j++)
        // ��pro1, pro2
        if(!vy[j] && lx[i] + ly[j] - w == 0)
        //��pro3
//        if(!vy[j] && lx[i] + ly[j] - w[i][j] < eps)
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
    // �� pro3 ע��Ҫ��double
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

double KM()
{
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
    //��pro1, pro3(ע����double)
    for(int i = 1; i <= n; i++)
        ans += w[match[i]][i];
    // ��pro2,
//    for(int i = 1; i <= n; i++)
//        ans += -w[match[i]][i];

    // ��pro1, pro2;
    return ans;
    //��pro3
//    return exp(ans);
}

void init()
{
    cin >> n >> m;

    // ��ʼ��, ����pro1, pro2, pro3����������ʼ��
    for(int i = 1; i <= n; i++)
        for(int i = 1; i <= n; i++)
            w[i][j] = -INF;

    for(int i = 1; i <= m; i++)
    {
        int u, v, cost;
        cin >> u >> v >> cost;

        // ��pro1
        cost = cost;
        // ��pro2
        cost = -cost;
        // ��pro3
        cost = log(cost);
        // ȥ�ر�
        w[u][v] = max(m[u][v], cost);
    }
}

signed main()
{
    while(1)
    {
        init();
        cout << KM() << endl;
    }
    return 0;
}
