using namespace std;
const int maxn=2e5+10;
int n,m,a[maxn],root[maxn];
vector<int>v;
struct node{
    int l,r,sum;
}t[maxn*40];
int cnt;
inline int getid(int x) {
    return lower_bound(v.begin(), v.end(), x) - v.begin()+1;
}
void insert(int l,int r,int pre,int &now,int x) {
    t[++cnt] = t[pre];
    now = cnt;
    t[now].sum++;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid) insert(l, mid, t[pre].l, t[now].l, x);
    else insert(mid + 1, r, t[pre].r, t[now].r, x);
}
int query(int l,int r,int L,int R,int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int tmp = t[t[R].l].sum - t[t[L].l].sum;
    if (k <= tmp) return query(l, mid, t[L].l, t[R].l, k);
    else return query(mid + 1, r, t[L].r, t[R].r, k - tmp);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
    //freopen("2.txt", "w", stdout);
#endif
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        v.push_back(a[i]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 1; i <= n; i++) {
        insert(1, n, root[i - 1], root[i], getid(a[i]));
    }
    while (m--) {
        int l, r, k;
        read(l, r, k);
        print(v[query(1, n, root[l - 1], root[r], k) - 1]);
    }
    FastIO::flush();
    return 0;
}
