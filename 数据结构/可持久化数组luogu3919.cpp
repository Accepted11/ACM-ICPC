#include <bits/stdc++.h>
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
//======================================
using namespace std;
const int maxn=1e6+10;
int n,m,a[maxn],root[maxn];
vector<int>v;
struct node{
    int l,r,val;
}t[maxn*40];
int cnt;
void build(int l,int r,int &now) {
    now = ++cnt;
    if (l == r) {
        t[now].val = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, t[now].l);
    build(mid + 1, r, t[now].r);
}
void modify(int l,int r,int pre,int &now,int pos,int num) {
    t[now = ++cnt] = t[pre];
    if (l == r) {
        t[now].val = num;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) modify(l, mid, t[pre].l, t[now].l, pos, num);
    else modify(mid + 1, r, t[pre].r, t[now].r, pos, num);
}
int query(int l,int r,int now,int pos) {
    if (l == r) return t[now].val;
    int mid = (l + r) >> 1;
    if (pos <= mid) return query(l, mid, t[now].l, pos);
    else return query(mid + 1, r, t[now].r, pos);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
    //freopen("2.txt", "w", stdout);
#endif
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    build(1, n, root[0]);
    for (int i = 1; i <= m; i++) {
        int pre, op, x, y;
        read(pre, op);
        switch (op) {
            case 1:
                read(x, y);
                modify(1, n, root[pre], root[i], x, y);
                break;
            case 2:
                read(x);
                print(query(1, n, root[pre], x));
                root[i] = root[pre];
        }
    }
    FastIO::flush();
    return 0;
}
