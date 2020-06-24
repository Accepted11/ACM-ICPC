#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n,m;
struct node {
    int l, r;
    int val;
    int height, size;
}tree[maxn];
int cnt,root;
inline void newnode(int &now,int val) {
    tree[++cnt].val = val;
    tree[cnt].size = 1;
    now=cnt;
}
inline void update(int now) {
    tree[now].size = tree[tree[now].l].size + tree[tree[now].r].size + 1;
    tree[now].height = max(tree[tree[now].l].height, tree[tree[now].r].height) + 1;
}
inline int factor(int now) {
    return tree[tree[now].l].height - tree[tree[now].r].height;
}
inline void lrotate(int &now) {
    int r = tree[now].r;
    tree[now].r = tree[r].l;
    tree[r].l = now;
    now = r;
    update(tree[now].l);
    update(now);
}
inline void rrotate(int &now) {
    int l = tree[now].l;
    tree[now].l = tree[l].r;
    tree[l].r = now;
    now = l;
    update(tree[now].r);
    update(now);
}
inline void check(int &now) {
    int nf = factor(now);
    if (nf > 1) {
        int lf = factor(tree[now].l);
        if (lf > 0)
            rrotate(now);   //LL
        else {              //LR
            lrotate(tree[now].l);
            rrotate(now);
        }
    } else if (nf < -1) {
        int rf = factor(tree[now].r);
        if (rf < 0)
            lrotate(now);  //RR
        else {             //RL
            rrotate(tree[now].r);
            lrotate(now);
        }
    } else if (now) update(now); //如果平衡并且非空，那就直接更新
}
void insert(int &now,int val) {
    if (!now) newnode(now, val); //到了一个不存在的点，新建它
    else if (val < tree[now].val) insert(tree[now].l, val);
    else insert(tree[now].r, val);
    check(now);                  //递归回溯检查平衡
}
int Find(int &now,int fa) {
    int res;
    if (!tree[now].l) {//返回值就是你了
        res = now; //返回值就是你了
        tree[fa].l = tree[now].r;//父亲的左儿改成该点的右儿
    } else {  //没找到
        res = Find(tree[now].l, now); //返回值是继续找
        check(now);//递归回溯过程中检查是否需要调整
    }
    return res;
}
void Delete(int &now,int val) {
    if (val == tree[now].val) { //要删除的结点
        int l = tree[now].l, r = tree[now].r;
        if (!l || !r) now = l + r; //如果无儿或单儿，很简单
        else {
            now = Find(r, r);  //找后继，替换当前
            if (now != r)    //如果后继不是原来的右儿
                tree[now].r = r; //右儿改成原来的右儿
            tree[now].l = l; //左儿连上
        }
    } else if (val < tree[now].val) Delete(tree[now].l, val);
    else Delete(tree[now].r, val);
    check(now); //递归回溯检查
}
int getrank(int val) {
    int now = root, rank = 1;
    while (now) {
        if (val <= tree[now].val)
            now = tree[now].l;
        else {
            rank +=1+ tree[tree[now].l].size;
            now = tree[now].r;
        }
    }
    return rank;
}
int getnum(int rank) {
    int now = root;
    while (now) {
        if (1+ tree[tree[now].l].size== rank) break;
        if (tree[tree[now].l].size >= rank)
            now = tree[now].l;
        else {
            rank -= 1 + tree[tree[now].l].size;
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
