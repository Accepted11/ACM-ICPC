#include<bits/stdc++.h>
using namespace std;

const int N = 150;
const int M = 450000;
const int INF = 100000000;
struct edge
{
    int v, next, cap, flow;
} e[M];
int n, m, id;
int head[N];

int maxflow()
{
    int f = 0, a[N], p[N], r[N];
    while ( 1 )
    {
        queue <int> q;
        int s = 1, t = n, np = n + n - 1;
        q.push(s);
        memset( a, 0, sizeof(a) );
        a[s] = INF;
        while ( !q.empty() )
        {
            int u = q.front();
            q.pop();
            for ( int i = head[u]; i != -1; i = e[i].next )
            {
                int v = e[i].v, cap = e[i].cap, flow = e[i].flow;
                if ( cap > flow && !a[v] )
                {
                    a[v] = min( a[u], cap - flow );
                    p[v] = u;
                    r[v] = i;
                    q.push(v);
                }
            }
        }
        if ( a[t] == 0 ) break;
        for ( int u = t; u != s; u = p[u] )
        {
            int ei = r[u];
            e[ei].flow += a[t];
            e[ei^1].flow -= a[t];
        }
        f += a[t];
    }
    return f;
}
void add( int u, int v, int c )
{
    e[id].next = head[u];
    e[id].v = v, e[id].cap = c, e[id].flow = 0;
    head[u] = id++;

    e[id].next = head[v];
    e[id].v = u, e[id].cap = 0, e[id].flow = 0;
    head[v] = id++;
}
int main()
{
    int t; scanf("%d", &t);
    int cas = 0;
    while (t--)
    {
        scanf("%d%d", &n, &m);
//        cout << "n = " << n << ", m = " << m << endl;
        id = 0;
        for ( int i = 0; i <= 2*n; ++i ) head[i] = -1;
        for ( int node = 2, cost; node < n; ++node)
        {
            scanf("%d", &cost);
            add( node, node + n, cost);
            add( node + n, node, cost);
        }
//        cout << "YES\n";
        for ( int i = 0; i < m; ++i )
        {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            if ( u == 1 && v == n )  add(u, v, c ), add( v, u, c );
            else if ( u == 1 && v != n ) add( u, v, c ), add( v+n, u, c ) ;
            else if ( v == 1 && u == n ) add( v, u, c ), add( u, v, c );
            else add( v + n, u, c ), add( u+n, v, c );
        }
        printf("Case %d: %d\n", ++cas, maxflow());
    }
}
