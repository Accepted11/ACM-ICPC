#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n,m;
struct node{
    int l,r;
    int key,val,size;
    bool reserve;
}tree[maxn];
int root,cnt;
inline int newnode(int val) {
    tree[++cnt].val = val;
    tree[cnt].key = rand();
    tree[cnt].size = 1;
    return cnt;
}
inline void pushdown(int now) {
    swap(tree[now].l, tree[now].r);
    tree[tree[now].l].reserve ^= 1;
    tree[tree[now].r].reserve ^= 1;
    tree[now].reserve = 0;
}
inline void update(int now) {
    tree[now].size = tree[tree[now].l].size + tree[tree[now].r].size + 1;
}
void split(int now,int size,int &x,int &y) {
    if (!now) x = y = 0;
    else {
        if (tree[now].reserve) pushdown(now);
        if (tree[tree[now].l].size < size) {
            x = now;
            split(tree[now].r, size - tree[tree[now].l].size - 1, tree[now].r, y);
        } else {
            y = now;
            split(tree[now].l, size, x, tree[now].l);
        }
        update(now);
    }
}
int merge(int x,int y) {
    if (!x || !y) return x + y;
    if (tree[x].key < tree[y].key) {
        if (tree[x].reserve) pushdown(x);
        tree[x].r = merge(tree[x].r, y);
        update(x);
        return x;
    } else {
        if (tree[y].reserve) pushdown(y);
        tree[y].l = merge(x, tree[y].l);
        update(y);
        return y;
    }
}
void reserve(int l,int r) {
    int x, y, z;
    split(root, l - 1, x, y);
    split(y, r - l + 1, y, z);
    tree[y].reserve ^= 1;
    root = merge(merge(x, y), z);
}
void Inorder(int now) {
    if (!now) return;
    if (tree[now].reserve) pushdown(now);
    Inorder(tree[now].l);
    printf("%d ", tree[now].val);
    Inorder(tree[now].r);
}
int main() {
    srand(time(0));
    scanf("%d%d", &n,&m);
    for (int i = 1; i <= n; i++) {
        root = merge(root, newnode(i));
    }
    for (int i = 1, l, r; i <= m; i++) {
        scanf("%d%d", &l, &r);
        reserve(l, r);
    }
    Inorder(root);
}
