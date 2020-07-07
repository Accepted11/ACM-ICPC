#include <bits/stdc++.h>

using namespace std;

const int maxn = 4e4 + 5;
const int maxm = 5e5 + 5;
const int inf = 0x3f3f3f3f;

struct Edge
{
    int to, next;
};

bool isnp[maxm];
int prime_num[maxm];
int prm[maxm];
int n;
int Mx[maxn], My[maxn], Nx, Ny;
int dx[maxn], dy[maxn], dis;
bool vst[maxn];
int Ax[maxn], Ay[maxn];
int top;
int head[maxn];
Edge ns[maxm];
int ext[maxm];
int cur;

void cal_prime_number()
{
    int res;
    prime_num[1] = 0;
    for (int i = 2; i < maxm; ++i)
    {
        int t = i;
        res = 0;
        for (int j = 2; j * j <= t; ++j)
        {
            while (t % j == 0)
            {
                ++res;
                t /= j;
            }
        }
        if (t != 1) ++res;
        prime_num[i] = res;
    }
}

void get_prime(int u)
{
    top = 0;
    for (int i = 2; i * i <= u; ++i)
    {
        if (u % i == 0)
        {
            prm[top++] = i;
            while (u % i == 0)
                u /= i;
        }
    }
    if (u != 1) prm[top++] = u;
}

bool searchP()
{
    queue<int> Q;
    dis = inf;
    memset(dx, -1, sizeof dx);
    memset(dy, -1, sizeof dy);
    for (int i = 1; i <= Nx; ++i)
    {
        if (Mx[i] == -1)
        {
            Q.push(i);
            dx[i] = 0;
        }
    }
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        if (dx[u] > dis) break;
        for (int i = head[u]; i != -1; i = ns[i].next)
        {
            int v = ns[i].to;
            if (dy[v] == -1)
            {
                dy[v] = dx[u] + 1;
                if (My[v] == -1) dis = dy[v];
                else
                {
                    dx[My[v]] = dy[v] + 1;
                    Q.push(My[v]);
                }
            }
        }
    }
    return dis != inf;
}

bool DFS(int u)
{
    for (int i = head[u]; i != -1; i = ns[i].next)
    {
        int v = ns[i].to;
        if (!vst[v] && dy[v] == dx[u] + 1)
        {
            vst[v] = 1;
            if (My[v] != -1 && dy[v] == dis) continue;
            if (My[v] == -1 || DFS(My[v]))
            {
                My[v] = u;
                Mx[u] = v;
                return true;
            }
        }
    }
    return false;
}

int MaxMatch()
{
    int res = 0;
    memset(Mx, -1, sizeof Mx);
    memset(My, -1, sizeof My);
    while (true)
    {
        memset(vst, 0 , sizeof vst);
        queue<int> Q;
        dis = inf;
        memset(dx, -1, sizeof dx);
        memset(dy, -1, sizeof dy);
        for (int i = 1; i <= Nx; ++i)
        {
            if (Mx[i] == -1)
            {
                Q.push(i);
                dx[i] = 0;
            }
        }
        while (!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            if (dx[u] > dis) break;
            for (int i = head[u]; i != -1; i = ns[i].next)
            {
                int v = ns[i].to;
                if (dy[v] == -1)
                {
                    dy[v] = dx[u] + 1;
                    if (My[v] == -1) dis = dy[v];
                    else
                    {
                        dx[My[v]] = dy[v] + 1;
                        Q.push(My[v]);
                    }
                }
            }
        }
        if (dis == inf) break;
        for (int i = 1; i <= Nx; ++i)
        {
            if (Mx[i] == -1 && DFS(i))
                ++res;
        }
    }
    return res;
}

void add_edge(int u, int v)
{
    ns[cur].next = head[u];
    ns[cur].to = v;
    head[u] = cur;
    ++cur;
}

int main()
{
    cal_prime_number();
    int t;
    scanf("%d", &t);
    int inp;
    for (int cas = 1; cas <= t; ++cas)
    {
        cur = 0;
        memset(head, -1, sizeof head);
        memset(ext, 0, sizeof ext);
        Nx = Ny = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &inp);
            if (prime_num[inp] & 1)
            {
                Ax[++Nx] = inp;
                ext[inp] = Nx;
            }
            else
            {
                Ay[++Ny] = inp;
                ext[inp] = Ny;
            }
        }
        for (int i = 1; i <= Nx; ++i)
        {
            get_prime(Ax[i]);
            for (int j = 0; j < top; ++j)
            {
                int goal = Ax[i] / prm[j];
                int index = ext[goal];
                if (index == 0) continue;
                add_edge(i, index);
            }
        }
        for (int i = 1; i <= Ny; ++i)
        {
            get_prime(Ay[i]);
            for (int j = 0; j < top; ++j)
            {
                int goal = Ay[i] / prm[j];
                int index = ext[goal];
                if (index == 0) continue;
                add_edge(index, i);
            }
        }
        printf("Case %d: %d\n", cas, n - MaxMatch());
    }
    return 0;
}
