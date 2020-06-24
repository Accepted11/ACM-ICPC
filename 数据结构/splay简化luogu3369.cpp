#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
struct Node {
    int fa, ch[2], val, cnt, size;  //ch[0]是左儿子，ch[1]是右儿子
}tree[maxn];
int cnt,root;
inline void update(int x) {
    tree[x].size = tree[tree[x].ch[0]].size + tree[tree[x].ch[1]].size + tree[x].cnt;
}
inline bool ident(int x,int f) {
    return tree[f].ch[1] == x;
} //查询父子关系
inline void connect(int x,int f,int s) {        //建立父子关系
    tree[f].ch[s] = x;
    tree[x].fa = f;
}
void rotate(int x) {     //合二为一的旋转
    int f = tree[x].fa, ff = tree[f].fa, k = ident(x, f);
    connect(tree[x].ch[k ^ 1], f, k);        //三次建立父子关系
    connect(x, ff, ident(f, ff));
    connect(f, x, k ^ 1);
    update(f), update(x);                //别忘了更新大小信息
}
void splaying(int x,int top) {//代表把x转到top的儿子，top为0则转到根结点
    if (!top) root = x;
    while (tree[x].fa != top) {
        int f = tree[x].fa, ff = tree[f].fa;
        if (ff != top) ident(f, ff) ^ ident(x, f) ? rotate(x) : rotate(f);
        rotate(x);      //最后一次都是旋转x
    }
}
void newnode(int &now,int fa,int val) {  //新建节点，要注意fa指针的初始化
    tree[now = ++cnt].val = val;
    tree[now].fa = fa;
    tree[now].size = tree[now].cnt = 1;
}
void delnode(int x) {             //删除结点，要注意fa指针的维护
    splaying(x, 0);
    if (tree[x].cnt > 1) tree[x].cnt--;
    else if (tree[x].ch[1]) {
        int p = tree[x].ch[1];
        while (tree[p].ch[0]) p = tree[p].ch[0];
        splaying(p, x);
        connect(tree[x].ch[0], p, 0);
        root = p;
        tree[p].fa = 0;
        update(root);
    } else {
        root = tree[x].ch[0];
        tree[root].fa = 0;
    }
}
void insert(int val,int &now=root,int fa=0) {
    if (!now) {
        newnode(now, fa, val);
        splaying(now, 0);
    } else if (val < tree[now].val) insert(val, tree[now].ch[0], now);
    else if (val > tree[now].val) insert(val, tree[now].ch[1], now);
    else {
        tree[now].cnt++;
        splaying(now, 0);
    }
}
void del(int val,int now=root)              //同上
{
    if(val==tree[now].val) delnode(now);
    else if(val<tree[now].val) del(val,tree[now].ch[0]);
    else del(val,tree[now].ch[1]);
}
inline int getrank(int val) {
    int now = root, rank = 1;
    while (1) {
        if (val == tree[now].val) {  //找到了要的结点，这个之前的没有
            rank += tree[tree[now].ch[0]].size;
            splaying(now,0);
            break;
        }
        if (!now) break;
        if (val <= tree[now].val)
            now = tree[now].ch[0];
        else {
            rank += tree[now].cnt + tree[tree[now].ch[0]].size;
            now = tree[now].ch[1];
        }
    }
    return rank;
}
void inorder(int now){
    if (!now) return;
    inorder(tree[now].ch[0]);
    printf("%d\n",tree[now].val);
    inorder(tree[now].ch[1]);
}
inline int getnum(int rank) {
    int now = root;
    while (now) {
        int lsize = tree[tree[now].ch[0]].size;
        if (lsize + 1 <= rank && rank <= lsize + tree[now].cnt) { //如果在这个范围内，那就是当前结点
            splaying(now, 0);
            break;
        } else if (lsize >= rank)
            now = tree[now].ch[0];
        else {
            rank -= tree[now].cnt + lsize;
            now = tree[now].ch[1];
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
                insert(x);
                break;
            case 2:
                del(x);
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
