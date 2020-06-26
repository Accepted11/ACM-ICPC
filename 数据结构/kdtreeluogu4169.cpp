typedef long long ll;
const int inf=0x3f3f3f3f;
const int maxn=6e5+10;
int K;
struct Point {
    int x[2], mx[2], mi[2], l, r;
    int sum,size;

    int &operator[](int i) {
        return x[i];
    }

    friend bool operator==(Point a, Point b) {
        return a.x[0] == b.x[0] && a.x[1] == b.x[1];
    }

    friend bool operator<(Point a, Point b) {
        return a[K] < b[K];
    }
}p[maxn];
Point tree[maxn], now;
int rt,cnt,st[maxn],top;
inline void update(int k) {
    int l = tree[k].l, r = tree[k].r;
    for (int i = 0; i < 2; i++) {
        tree[k].mi[i] = tree[k].mx[i] = tree[k][i];
        if (l) {
            tree[k].mi[i] = min(tree[k].mi[i], tree[l].mi[i]);
            tree[k].mx[i] = max(tree[k].mx[i], tree[l].mx[i]);
        }
        if (r) {
            tree[k].mi[i] = min(tree[k].mi[i], tree[r].mi[i]);
            tree[k].mx[i] = max(tree[k].mx[i], tree[r].mx[i]);
        }
    }
    //tree[k].sum = tree[k].v + tree[l].sum + tree[r].sum;
    tree[k].size = tree[r].size + tree[l].size + 1;
}

inline void rebuild(int &rt,int l, int r, int k) {
    if (l > r) return;
    int mid = l + r >> 1;
    K = k;
    rt = st[top--];
    nth_element(p + l, p + mid, p + r + 1);
    p[mid].size=1;
    p[mid].l=p[mid].r=0;
    tree[rt] = p[mid];
    rebuild(tree[rt].l, l, mid - 1, k ^ 1);
    rebuild(tree[rt].r, mid + 1, r, k ^ 1);
    update(rt);
}
inline int dis(Point a,Point b) {
    return abs(a[0] - b[0]) + abs(a[1] - b[1]);
}
inline int get(int k,Point p) {
    int tmp = 0;
    for (int i = 0; i < 2; i++) {
        tmp += max(0, tree[k].mi[i] - p[i]);
    }
    for (int i = 0; i < 2; i++) {
        tmp += max(0, p[i] - tree[k].mx[i]);
    }
    return tmp;
}
int n,m,x,y,ans;
inline void query(int k,int D) {
    int d = dis(tree[k], now), dl = inf, dr = inf;
    ans = min(ans, d);
    if (tree[k].l) dl = get(tree[k].l, now);
    if (tree[k].r) dr = get(tree[k].r, now);
    if (dl < dr) {
        if (dl < ans) query(tree[k].l, D ^ 1);
        if (dr < ans) query(tree[k].r, D ^ 1);
    } else {
        if (dr < ans) query(tree[k].r, D ^ 1);
        if (dl < ans) query(tree[k].l, D ^ 1);
    }
}
const double alpha=0.75;
void Ping(int u) {
    if (!u) return;
    Ping(tree[u].l);
    st[++top] = u;
    p[top] = tree[u];
    Ping(tree[u].r);
}
inline void check(int &u,int type) {
    top = 0;
    if (max(tree[tree[u].l].size, tree[tree[u].r].size) > tree[u].size * alpha) {
        Ping(u);
        u = 0;
        rebuild(u,1, top, type);
    }
}
inline void insert(int &k, bool D) {
    if (!k) {
        k = ++n;
        tree[k][0] = tree[k].mi[0] = tree[k].mx[0] = now[0];
        tree[k][1] = tree[k].mi[1] = tree[k].mx[1] = now[1];
        tree[k].size=1;
        return;
    }
    if (now[D] < tree[k][D]) insert(tree[k].l, D ^ 1);
    else insert(tree[k].r, D ^ 1);
    update(k);
    check(k,D);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
    //freopen("2.txt", "w", stdout);
#endif
    read(n, m);
    top= n;
    for (int i = 1; i <= n; i++) {
        read(p[i].x[0], p[i].x[1]);
        st[i]=n-i+1;
    }
    rebuild(rt,1, n, 0);
    //cout<<rt<<endl;
    while (m--) {
        int op;
        read(op, x, y);
        now[0] = x;
        now[1] = y;
        if (op == 1) {
            insert(rt, 0);
        } else {
            ans = inf;
            query(rt, 0);
            print(ans);
        }
    }
   // print(rt);
    FastIO::flush();
    return 0;
}
