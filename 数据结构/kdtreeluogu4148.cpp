#include <bits/stdc++.h>
using namespace std;
namespace FastIO {
    char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = '\n';
    int p, p3 = -1;

    void read() {}

    void print() {}

    inline int getc() {
        return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;
    }

    inline void flush() {
        fwrite(buf2, 1, p3 + 1, stdout), p3 = -1;
    }

    template<typename T, typename... T2>
    inline void read(T &x, T2 &... oth) {
        int f = 0;
        x = 0;
        char ch = getc();
        while (!isdigit(ch)) {
            if (ch == '-')
                f = 1;
            ch = getc();
        }
        while (isdigit(ch)) {
            x = x * 10 + ch - 48;
            ch = getc();
        }
        x = f ? -x : x;
        read(oth...);
    }

    template<typename T, typename... T2>
    inline void print(T x, T2... oth) {
        if (p3 > 1 << 20)
            flush();
        if (x < 0)
            buf2[++p3] = 45, x = -x;
        do {
            a[++p] = x % 10 + 48;
        } while (x /= 10);
        do {
            buf2[++p3] = a[p];
        } while (--p);
        buf2[++p3] = hh;
        print(oth...);
    }
} // namespace FastIO
#define read FastIO::read
#define print FastIO::print
typedef long long ll;
const int maxn=1e6+10;
int K;
struct Point {
    int x[2], mx[2], mi[2], v, l, r;
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
bool in(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2) {
    return x1 <= X1 && X2 <= x2 && y1 <= Y1 && Y2 <= y2;
}
bool out(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2) {
    return x1 > X2 || x2 < X1 || y1 > Y2 || y2 < Y1;
}
Point tree[maxn], now;
int rt,cnt;
void update(int k) {
    int l = tree[k].l, r = tree[k].r;
    for (int i = 0; i < 2; i++) {
        tree[k].mi[i] = tree[k].mx[i] = tree[k][i];
        if (l) tree[k].mi[i] = min(tree[k].mi[i], tree[l].mi[i]);
        if (l) tree[k].mx[i] = max(tree[k].mx[i], tree[l].mx[i]);
        if (r) tree[k].mi[i] = min(tree[k].mi[i], tree[r].mi[i]);
        if (r) tree[k].mx[i] = max(tree[k].mx[i], tree[r].mx[i]);
    }
    tree[k].sum = tree[k].v + tree[l].sum + tree[r].sum;
    //tree[k].size = tree[r].size + tree[l].size + 1;
}

int rebuild(int l, int r, int k) {
    if (l > r) return 0;
    int mid = l + r >> 1;
    K = k;
    nth_element(p + l, p + mid, p + r + 1);
    tree[mid] = p[mid];
    tree[mid].l = rebuild(l, mid - 1, k ^ 1);
    tree[mid].r = rebuild(mid + 1, r, k ^ 1);
    update(mid);
    return mid;
}

ll query(int k,int x1,int y1,int x2,int y2) {
    if (!k) return 0;
    ll res = 0;
    if (in(x1, y1, x2, y2, tree[k].mi[0], tree[k].mi[1], tree[k].mx[0], tree[k].mx[1])) {
        return tree[k].sum;
    }
    if (out(x1, y1, x2, y2, tree[k].mi[0], tree[k].mi[1], tree[k].mx[0], tree[k].mx[1])) return 0;
    if (in(x1, y1, x2, y2, tree[k][0], tree[k][1], tree[k][0], tree[k][1])) {
        res += tree[k].v;
    }
    res += query(tree[k].l, x1, y1, x2, y2) + query(tree[k].r, x1, y1, x2, y2);
    return res;
}
void insert(int &k, bool D) {
    if (!k) {
        k = ++cnt;
        tree[k][0] = tree[k].mi[0] = tree[k].mx[0] = now[0];
        tree[k][1] = tree[k].mi[1] = tree[k].mx[1] = now[1];
    }
    if (now == tree[k]) {
        tree[k].v += now.v;
        tree[k].sum += now.v;
        return;
    }
    if (now[D] < tree[k][D]) insert(tree[k].l, D ^ 1);
    else insert(tree[k].r, D ^ 1);
    update(k);
}
int n,x,y,ans,A,x2,y2;
int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
    //freopen("2.txt", "w", stdout);
#endif
    int m = 10000;
    read(n);
    while (1) {
        int op;
        read(op);
        if (op == 3) break;
        read(x, y);
        x ^= ans;
        y ^= ans;
        if (op == 1) {
            read(A);
            A ^= ans;
            now[0] = x;
            now[1] = y;
            now.v = now.sum = A;
            insert(rt, 0);
            if (cnt == m) {
                for (int i = 1; i <= cnt; i++) p[i] = tree[i];
                rt = rebuild(1, cnt, 0);
                m += 10000;
            }
        }
        if (op == 2) {
            read(x2, y2);
            x2 ^= ans;
            y2 ^= ans;
            ans = query(rt, x, y, x2, y2);
            print(ans);
        }
    }
    FastIO::flush();
    return 0;
}
