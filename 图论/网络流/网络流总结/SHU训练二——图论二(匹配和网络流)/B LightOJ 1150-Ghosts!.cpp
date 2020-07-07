#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 1010;

char map[N][N];
int human[N], ghost[N], left[N];
int n, cntG, cntH, cas = 1, cnt;
bool vis[N];
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
bool g[N][N], visH[N];

struct Node
{
    int g, h, dis;
    Node() {}
    Node(int h, int g, int dis): h(h), g(g), dis(dis) {}
} node[N * N];

struct Que
{
    int pos, step;
    Que() {}
    Que(int pos, int step): pos(pos), step(step) {}
};

bool cmp(const Node &a, const Node &b)
{
    return a.dis < b.dis;
}

void bfs(int num, int cur)
{
    memset(vis, 0, sizeof(vis));
    queue<Que> Q;
    Q.push(Que(cur, 0));
    vis[cur] = true;
    while (!Q.empty())
    {
        int pos = Q.front().pos;
        int step = Q.front().step;
        Q.pop();
        for (int i = 0; i < 4; i++)
        {
            int x = pos / n + dir[i][0];
            int y = pos % n + dir[i][1];
            if (x < 0 || y < 0 || x >= n || y >= n || vis[x * n + y] || map[x][y] == '#') continue;
            vis[x * n + y] = true;
            if (map[x][y] == 'H')  node[cnt++] = Node(human[x * n + y], num, step + 2);
            Q.push(Que(x * n + y, step + 1));
        }
    }
}

bool dfs(int u)
{
    for (int i = 1; i <= cntG; i++)
    {
        if (g[u][i] && !vis[i])
        {
            vis[i] = true;
            if (!left[i] || dfs(left[i]))
            {
                left[i] = u;
                return true;
            }
        }
    }
    return false;
}

bool judge()
{

    memset(left, 0, sizeof(left));
    for (int i = 1; i <= cntH; i++)
    {
        memset(vis, 0, sizeof(vis));
        if (!dfs(i)) return false;
    }
    return true;
}

void solve()
{
    memset(ghost, 0, sizeof(ghost));
    memset(human, 0, sizeof(human));
    //刚开始都是数量都是0
    cntG = cntH = cnt = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", map[i]);
        for (int j = 0; j < n; j++)
        {
            if (map[i][j] == 'G')
                ghost[i * n + j] = ++cntG;
            else if (map[i][j] == 'H')
                human[i * n + j] = ++cntH;
        }
    }

    //因为每只鬼只能干掉一个人
    if (cntH > cntG)
    {
        printf("Case %d: Vuter Dol Kupokat\n", cas++);
        return ;
    }

    //bfs找出每个鬼和人的距离
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (ghost[i * n + j])
                bfs(ghost[i * n + j], i * n + j);

    memset(g, 0, sizeof(g));
    memset(visH, 0, sizeof(visH));
    sort(node, node + cnt, cmp);

    int tmp = 0, i;
    //处理左边的点集，也就是人
    for (i = 0; i < cnt; i++)
    {
        g[node[i].h][node[i].g] = true;
        if (!visH[node[i].h])
        {
            visH[node[i].h] = true;
            tmp++;
            if (tmp == cntH) break;
        }
    }

    //依此加大，如果都没能匹配，表示失败
    for (; i < cnt; i++)
    {
        g[node[i].h][node[i].g] = true;
        if (judge())
        {
            printf("Case %d: %d\n", cas++, node[i].dis * 2);
            return ;
        }
    }
    printf("Case %d: Vuter Dol Kupokat\n", cas++);
}

int main()
{
    int test;
    scanf("%d", &test);
    while (test--) solve();
    return 0;
}
