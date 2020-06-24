#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
const double alpha = 0.75;
struct node {
    int l, r;
    int val,key;
    int size;
}tree[maxn];
int cnt,root,n;
inline int newnode(int val) {
    tree[++cnt].val = val;
    tree[cnt].key = rand();
    tree[cnt].size = 1;
    return cnt;
}
inline void update(int now) {
    tree[now].size = tree[tree[now].l].size + tree[tree[now].r].size+1;
}
void spilt(int now,int val,int &x,int &y) {
    if (!now) x = y = 0;
    else {
        if (tree[now].val <= val) {
            x = now;
            spilt(tree[now].r, val, tree[now].r, y);
        } else {
            y = now;
            spilt(tree[now].l, val, x, tree[now].l);
        }
        update(now);
    }
}
int merge(int x,int y) {
    if (!x || !y) return x + y;
    if (tree[x].key > tree[y].key) {
        tree[x].r = merge(tree[x].r, y);
        update(x);
        return x;
    } else {
        tree[y].l = merge(x, tree[y].l);
        update(y);
        return y;
    }
}
int x,y,z;
inline void insert(int val) {
    spilt(root, val, x, y);
    root = merge(merge(x, newnode(val)), y);
}
inline void Delete(int val) {
    spilt(root, val, x, z);
    spilt(x, val - 1, x, y);
    y = merge(tree[y].l, tree[y].r);
    root = merge(merge(x, y), z);
}
inline void getrank(int val) {
    spilt(root, val - 1, x, y);
    printf("%d\n", tree[x].size + 1);
    root = merge(x, y);
}
inline void getnum(int rank) {
    int now = root;
    while (now) {
        if (tree[tree[now].l].size + 1 == rank)break;
        if (tree[tree[now].l].size >= rank)
            now = tree[now].l;
        else {
            rank -= tree[tree[now].l].size + 1;
            now = tree[now].r;
        }
    }
    printf("%d\n",tree[now].val);
}
inline void pre(int val) {
    spilt(root, val - 1, x, y);
    int now = x;
    while (tree[now].r) now = tree[now].r;
    printf("%d\n", tree[now].val);
    root = merge(x, y);
}
inline void nxt(int val) {
    spilt(root, val, x, y);
    int now = y;
    while (tree[now].l) now = tree[now].l;
    printf("%d\n", tree[now].val);
    root = merge(x, y);
}
int main() {
    srand(time(0));
    scanf("%d", &n);
    for (int i = 1, op, x; i <= n; i++) {
        scanf("%d%d", &op, &x);
        switch (op) {
            case 1:
                insert(x);
                break;
            case 2:
                Delete(x);
                break;
            case 3:
                getrank(x);
                break;
            case 4:
                getnum(x);
                break;
            case 5:
                pre(x);
                break;
            case 6:
                nxt(x);
                break;
        }
    }
}
