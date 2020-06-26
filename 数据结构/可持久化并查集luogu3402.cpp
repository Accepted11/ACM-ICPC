using namespace std;
const int maxn=2e5+10;
int n,m,rootfa[maxn],rootdep[maxn];
vector<int>v;
struct node{
    int l,r,val;
}t[maxn*40*2];
int cnt,tot;
void build(int l,int r,int &now) {
    now = ++cnt;
    if (l == r) {
        t[now].val = ++tot;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, t[now].l);
    build(mid + 1, r, t[now].r);
}
void modify(int l,int r,int pre,int &now,int pos,int val) {
    t[now = ++cnt] = t[pre];
    if (l == r) {
        t[now].val = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) modify(l, mid, t[pre].l, t[now].l, pos,val);
    else modify(mid + 1, r, t[pre].r, t[now].r, pos, val);
}
int query(int l,int r,int now,int pos) {
    if (l == r) return t[now].val;
    int mid = (l + r) >> 1;
    if (pos <= mid) return query(l, mid, t[now].l, pos);
    else return query(mid + 1, r, t[now].r, pos);
}
int find(int pre,int x) {
    int fx = query(1, n, rootfa[pre], x);
    return fx == x ? x : find(pre, fx);
}
int merge(int pre,int x,int y) {
    x = find(pre - 1, x);
    y = find(pre - 1, y);
    if (x == y) {
        rootfa[pre] = rootfa[pre - 1];
        rootdep[pre] = rootdep[pre];
    } else {
        int depx = query(1, n, rootdep[pre - 1], x);
        int depy = query(1, n, rootdep[pre - 1], y);
        if (depx < depy) {
            modify(1, n, rootfa[pre - 1], rootfa[pre], x, y);
            rootdep[pre] = rootdep[pre - 1];
        } else if (depx > depy) {
            modify(1, n, rootfa[pre - 1], rootfa[pre], y, x);
            rootdep[pre] = rootdep[pre - 1];
        } else {
            modify(1, n, rootfa[pre - 1], rootfa[pre], x, y);
            modify(1, n, rootdep[pre - 1], rootdep[pre], y, depy + 1);
        }
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
    //freopen("2.txt", "w", stdout);
#endif
    read(n, m);
    build(1, n, rootfa[0]);
    for (int i = 1; i <= m; i++) {
        int pre, op, x, y;
        read(op);
        switch (op) {
            case 1:
                read(x, y);
                merge(i,x,y);
                break;
            case 2:
                read(x);
                rootfa[i] = rootfa[x];
                rootdep[i] = rootdep[x];
                break;
            case 3:
                read(x, y);
                rootfa[i] = rootfa[i - 1];
                rootdep[i] = rootdep[i - 1];
                if (find(i, x) == find(i, y))
                    print(1);
                else
                    print(0);
                break;
        }
    }
    FastIO::flush();
    return 0;
}
