#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n,m;
struct node {
    int l, r;
    int val,size;
    int cnt;//当前节点重复次数
}tree[maxn];
int cnt,root;
inline void newnode(int &now,int val) {
    tree[++cnt].val = val;
    tree[cnt].size++;
    tree[cnt].cnt++;
    now = cnt;
}
inline void update(int now) {
    tree[now].size = tree[tree[now].l].size + tree[tree[now].r].size + tree[now].cnt;
}
inline void zag(int &now) {
    int r = tree[now].r;
    tree[now].r = tree[r].l;
    tree[r].l = now;
    now = r;
    update(tree[now].l);
    update(now);
}
inline void zig(int &now) {
    int l = tree[now].l;
    tree[now].l = tree[l].r;
    tree[l].r = now;
    now = l;
    update(tree[now].r);
    update(now);
}
inline void splaying(int  x,int &y) { //我要把x伸展到y那个位置！
    if (x == y)return;  //如果到了终点，return
    int &l = tree[y].l, &r = tree[y].r;
    if (x == l) zig(y);   //如果左儿子是终点，那就单旋
    else if (x == r) zag(y);     //右儿子是终点也是单旋
    else {   //否则就一定是双旋
        if (tree[x].val < tree[y].val) {
            if (tree[x].val < tree[l].val) {
                splaying(x, tree[l].l);
                zig(y); //zigzig情况
                zig(y);
            } else {
                splaying(x, tree[l].r);
                zag(l);//zagzig情况
                zig(y);
            }
        } else {
            if (tree[x].val > tree[r].val) {
                splaying(x, tree[r].r);
                zag(y);
                zag(y);//zagzag情况
            } else {
                splaying(x, tree[r].l);
                zig(r);//zigzag情况
                zag(y);
            }
        }
    }
}
inline void insert(int &now,int val) {
    if (!now) {
        newnode(now, val); //到了一个不存在的点，新建它
        splaying(now, root);
    } else if (val < tree[now].val) insert(tree[now].l, val);
    else if (val > tree[now].val) insert(tree[now].r, val);
    else {
        tree[now].size++;
        tree[now].cnt++;
        splaying(now, root);
    }
}

inline int getrank(int val) {
    int now = root, rank = 1;
    while (now) {
        if (val == tree[now].val) {  //找到了要的结点，这个之前的没有
            rank += tree[tree[now].l].size;
            splaying(now, root);
            break;
        } else if (val <= tree[now].val)
            now = tree[now].l;
        else {
            rank += tree[now].cnt + tree[tree[now].l].size;
            now = tree[now].r;
        }
    }
    return rank;
}
inline void delnode(int now) {
    splaying(now, root); //将要删除的结点伸展至根结点
    if (tree[now].cnt > 1) { //如果有重复，令重复次数--
        tree[now].cnt--;
        tree[now].size--;
    } else if (tree[root].r) {  //否则如果当前结点有后继
        int p = tree[root].r;
        while (tree[p].l) p = tree[p].l;//找到后继
        splaying(p, tree[root].r);//将其伸展至根结点右儿子
        tree[tree[root].r].l = tree[root].l;//右儿子左儿子变为根结点
        root = tree[root].r; //根结点变为根结点右儿子
        update(root);  //更新一下size信息
    } else root = tree[root].l; //伸展之后没有后继，说明它是最大的了，那就直接删除
}
inline void Delete(int now,int &val) {
    if (tree[now].val == val) delnode(now);
    else if (val < tree[now].val) Delete(tree[now].l, val);
    else Delete(tree[now].r, val);
}
inline int getnum(int rank) {
    int now = root;
    while (now) {
        int lsize = tree[tree[now].l].size;
        if (lsize + 1 <= rank && rank <= lsize + tree[now].cnt) { //如果在这个范围内，那就是当前结点
            splaying(now, root);
            break;
        } else if (lsize >= rank)
            now = tree[now].l;
        else {
            rank -= tree[now].cnt + lsize;
            now = tree[now].r;
        }
    }
    return tree[now].val;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
    //freopen("2.txt", "w", stdout);
#endif
    int _;
    scanf("%d", &_);
    while (_--) {
        int op, x;
        scanf("%d%d", &op, &x);
        switch (op) {
            case 1:
                insert(root, x);
                break;
            case 2:
                Delete(root, x);
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
                printf("%d\n", getnum(getrank(x + 1)));
                break;
        }
    }
    return 0;
}
