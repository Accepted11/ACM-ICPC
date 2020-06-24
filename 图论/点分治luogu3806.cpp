#include <bits/stdc++.h>
using namespace std;
inline void read(int &x) {  //读入优化
    x = 0;
    static int p;
    p = 1;
    static char c;
    c = getchar();
    while (!isdigit(c)) {
        if (c == '-')p = -1;
        c = getchar();
    }
    while (isdigit(c)) {
        x = (x << 1) + (x << 3) + (c - 48);
        c = getchar();
    }
    x *= p;
}
inline void print(int x) {   //输出优化
    static int cnt;
    static int a[30];
    cnt = 0;
    do {
        a[++cnt] = x % 10;
        x /= 10;
    } while (x);
    for (int i = cnt; i >= 1; i--)putchar(a[i] + '0');
    //putchar(' ');
    puts("");
}
const int maxn=2e4+10;
int n,m;
struct node{
    int v,w,nxt;
}e[maxn];
int t,head[maxn];
inline void add(int u,int v,int w) {
    t++;
    e[t].v = v;
    e[t].w = w;
    e[t].nxt = head[u];
    head[u] = t;
}
int mx[maxn],sum,tmp[maxn],ans[maxn],a[maxn],dis[maxn],vis[maxn],rt,size[maxn];
void getrt(int u,int fa) {
    mx[u] = 0;
    size[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (v == fa || vis[v]) continue;
        getrt(v, u);
        size[u] += size[v];
        mx[u] = max(mx[u], size[v]);
    }
    mx[u] = max(mx[u], sum - size[u]);
    if (mx[u] < mx[rt]) rt = u;
}
int cnt;
void dfs(int u,int fa) {
    tmp[cnt++] = dis[u];
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (v == fa || vis[v])continue;
        dis[v] = dis[u] + e[i].w;
        dfs(v, u);
    }
}
set<int>s;
void query(int x) {
    for (int i = 1; i <= m; i++) {
        if (!ans[i]) {
            if (*s.lower_bound(a[i] - x) == a[i] - x) {
                ans[i] = 1;
            }
        }
    }
}
void solve(int u) {
    vis[u] = 1;
    s.clear();
    s.insert(0);
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (vis[v]) continue;
        cnt = 0;
        dis[v] = e[i].w;
        dfs(v, u);
        for (int j = 0; j < cnt; j++) query(tmp[j]);
        for (int j = 0; j < cnt; j++) s.insert(tmp[j]);
    }
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (vis[v]) continue;
        rt = 0;
        mx[rt] = sum = size[v];
        getrt(v, 0);
        solve(rt);
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
    //freopen("2.txt", "w", stdout);
#endif
    read(n);
    read(m);
    for (int i = 2, u, v, w; i <= n; i++) {
        read(u);
        read(v);
        read(w);
        add(u,v,w);
        add(v,u,w);
    }
    for (int i = 1; i <= m; i++) {
        read(a[i]);
    }
    mx[0] = sum = n;
    getrt(1, 0);
    solve(rt);
    for (int i = 1; i <= m; i++) {
        if(ans[i])puts("AYE");
        else puts("NAY");
    }
    return 0;
}