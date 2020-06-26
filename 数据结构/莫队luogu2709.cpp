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
const int maxn=5e4+10;
typedef long long ll;
int a[maxn],pos[maxn],cnt[maxn],n,m,size,k;
struct node{
    int l,r,k;
}q[maxn];
ll ans[maxn],res;
bool cmp(const node &a,const node &b) {
    if (pos[a.l] == pos[b.l]) return a.r < b.r;
    return pos[a.l] < pos[b.l];
}
void add(int i) {
    cnt[a[i]]++;
    res += cnt[a[i]] * cnt[a[i]] - (cnt[a[i]] - 1) * (cnt[a[i]] - 1);
}
void sub(int i) {
    cnt[a[i]]--;
    res += cnt[a[i]] * cnt[a[i]] - (cnt[a[i]] + 1) * (cnt[a[i]] + 1);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
    //freopen("2.txt", "w", stdout);
#endif
    //======================================
    read(n, m,k);
    size = sqrt(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        pos[i] = i / size;
    }
    for (int i = 1; i <= m; i++) {
        read(q[i].l, q[i].r);
        q[i].k = i;
    }
    int l = 1, r = 0;
    sort(q + 1, q + m + 1, cmp);
    for (int i = 1; i <= m; i++) {
        while (q[i].l < l) add(--l);
        while (q[i].r > r) add(++r);
        while (q[i].l > l) sub(l++);
        while (q[i].r < r) sub(r--);
        ans[q[i].k] = res;
    }
    for (int i = 1; i <= m; i++) {
        print(ans[i]);
    }
    //======================================
    FastIO::flush();
    return 0;
}
