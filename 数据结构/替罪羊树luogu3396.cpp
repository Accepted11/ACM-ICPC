#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
const double alpha = 0.75;
struct node {
    int l, r, val;
    int fact, size;
    bool exist;
}tree[maxn];
int cnt,root,n;
void newnode(int &now,int val) {
    now = ++cnt;
    tree[now].val = val;
    tree[now].size = tree[now].fact = tree[now].exist = 1;
}
bool imbalence(int now) {
    return (max(tree[tree[now].l].size, tree[tree[now].r].size) > tree[now].size * alpha ||
            tree[now].size * 0.3 < tree[now].size - tree[now].fact);
}
vector<int>v;
void Inorder(int now) {
    if (!now) return;
    Inorder(tree[now].l);
    if (tree[now].exist) v.push_back(now);
    Inorder(tree[now].r);
}
void updata(int now,int end) {
    if (!now) return;
    if (tree[end].val < tree[now].val)
        updata(tree[now].l, end);
    else updata(tree[now].r, end);
    tree[now].size = tree[tree[now].l].size + tree[tree[now].r].size + 1;
}
void lift(int l,int r,int &now) {
    if (l == r) {
        now = v[l];
        tree[now].l = tree[now].r = 0;
        tree[now].size = tree[now].fact = 1;
        return;
    }
    int mid = (l + r) >> 1;
    while (l < mid && tree[v[mid]].val == tree[v[mid - 1]].val) mid--;
    now=v[mid];
    if (l < mid) lift(l, mid - 1, tree[now].l);
    else tree[now].l = 0;
    lift(mid + 1, r, tree[now].r);
    tree[now].size = tree[tree[now].l].size + tree[tree[now].r].size + 1;
    tree[now].fact = tree[tree[now].l].fact + tree[tree[now].r].fact + 1;
}
void rebuild(int &now) {
    v.clear();
    Inorder(now);
    if (v.empty()) {
        now = 0;
        return;
    }
    lift(0, v.size() - 1, now);
}
void check(int &now,int end) {
    if (now == end) return;
    if (imbalence(now)) {
        rebuild(now);
        updata(root, now);
        return;
    }
    if (tree[end].val < tree[now].val)
        check(tree[now].l, end);
    else check(tree[now].r, end);
}
void insert(int &now,int val) {
    if (!now) {
        newnode(now, val);
        check(root, now);
        return;
    }
    tree[now].fact++;
    tree[now].size++;
    if (val < tree[now].val)
        insert(tree[now].l, val);
    else insert(tree[now].r, val);
}
void del(int now,int val) {
    if (tree[now].exist && tree[now].val == val) {
        tree[now].exist = 0;
        tree[now].fact--;
        check(root, now);
        return;
    }
    tree[now].fact--;
    if (val < tree[now].val)
        del(tree[now].l, val);
    else del(tree[now].r, val);
}
int getrank(int val) {
    int now = root, rank = 1;
    while (now) {
        if (val <= tree[now].val)
            now = tree[now].l;
        else {
            rank += tree[now].exist + tree[tree[now].l].fact;
            now = tree[now].r;
        }
    }
    return rank;
}
int getnum(int rank) {
    int now = root;
    while (now) {
        if (tree[now].exist && tree[now].exist + tree[tree[now].l].fact == rank) break;
        if (tree[tree[now].l].fact >= rank)
            now = tree[now].l;
        else {
            rank -= tree[now].exist + tree[tree[now].l].fact;
            now = tree[now].r;
        }
    }
    return tree[now].val;
}
int main() {
    scanf("%d", &n);
    for (int i = 1, op, x; i <= n; i++) {
        scanf("%d%d", &op, &x);
        switch (op) {
            case 1:
                insert(root, x);
                break;
            case 2:
                del(root, x);
                break;
            case 3:
                printf("%d\n", getrank(x));
                break;
            case 4:
                printf("%d\n", getnum(x));
                break;
            case 5:
                printf("%d\n", getnum(getrank(x) - 1));
                break;
            case 6:
                printf("%d\n", getnum(getrank(x+1)));
                break;
        }
    }
}
