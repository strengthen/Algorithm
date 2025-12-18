#include <iostream>   // 引入输入输出流库
#include <vector>     // 引入向量容器库
#include <string>     // 引入字符串库
#include <algorithm>  // 引入算法库

using namespace std;  // 使用标准命名空间

// 定义节点结构体，用于线段树维护区间信息
struct Node {
    long long r;      // 字符'r'的数量
    long long e;      // 字符'e'的数量
    long long d;      // 字符'd'的数量
    long long re;     // 子序列"re"的数量
    long long ed;     // 子序列"ed"的数量
    long long red;    // 子序列"red"的数量

    // 构造函数，初始化所有计数为0
    Node() : r(0), e(0), d(0), re(0), ed(0), red(0) {}
};

// 合并两个节点的信息（左子节点和右子节点）
Node merge(const Node& left, const Node& right) {
    Node res;
    // 合并单个字符的数量，直接相加
    res.r = left.r + right.r;
    res.e = left.e + right.e;
    res.d = left.d + right.d;

    // 合并"re"的数量：左边的"re" + 右边的"re" + 左边的'r'与右边的'e'组合
    res.re = left.re + right.re + left.r * right.e;

    // 合并"ed"的数量：左边的"ed" + 右边的"ed" + 左边的'e'与右边的'd'组合
    res.ed = left.ed + right.ed + left.e * right.d;

    // 合并"red"的数量：
    // 1. 左边完整的"red"
    // 2. 右边完整的"red"
    // 3. 左边的'r'与右边的"ed"组合
    // 4. 左边的"re"与右边的'd'组合
    res.red = left.red + right.red + left.r * right.ed + left.re * right.d;

    return res;
}

// 根据字符创建叶子节点
Node createNode(char c) {
    Node res;
    if (c == 'r') res.r = 1;
    else if (c == 'e') res.e = 1;
    else if (c == 'd') res.d = 1;
    return res;
}

const int MAXN = 200005; // 最大字符串长度
Node treeS[MAXN * 4];    // 字符串s的线段树数组
Node treeT[MAXN * 4];    // 字符串t的线段树数组
string s, t;             // 存储字符串s和t
int n, q;                // 字符串长度和查询次数

// 构建线段树
// node: 当前节点编号, start: 当前区间开始下标, end: 当前区间结束下标
void build(int node, int start, int end) {
    if (start == end) {
        // 叶子节点，根据字符串对应位置的字符初始化
        treeS[node] = createNode(s[start - 1]); // 字符串下标从0开始
        treeT[node] = createNode(t[start - 1]);
        return;
    }
    int mid = (start + end) / 2; // 计算中点
    build(node * 2, start, mid); // 递归构建左子树
    build(node * 2 + 1, mid + 1, end); // 递归构建右子树
    // 合并子节点信息
    treeS[node] = merge(treeS[node * 2], treeS[node * 2 + 1]);
    treeT[node] = merge(treeT[node * 2], treeT[node * 2 + 1]);
}

// 更新线段树单点
// idx: 需要更新的位置, charS: s在该位置的新字符, charT: t在该位置的新字符
void update(int node, int start, int end, int idx, char charS, char charT) {
    if (start == end) {
        // 更新叶子节点
        treeS[node] = createNode(charS);
        treeT[node] = createNode(charT);
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) {
        update(node * 2, start, mid, idx, charS, charT); // 递归更新左子树
    } else {
        update(node * 2 + 1, mid + 1, end, idx, charS, charT); // 递归更新右子树
    }
    // 更新父节点信息
    treeS[node] = merge(treeS[node * 2], treeS[node * 2 + 1]);
    treeT[node] = merge(treeT[node * 2], treeT[node * 2 + 1]);
}

int main() {
    // 优化输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读取字符串长度和操作次数
    if (cin >> n >> q) {
        cin >> s >> t; // 读取两个字符串
        
        build(1, 1, n); // 构建线段树，根节点为1，区间为[1, n]

        for (int i = 0; i < q; ++i) {
            int x;
            cin >> x; // 读取交换位置
            // 交换s和t在x位置的字符（字符串下标x-1）
            swap(s[x - 1], t[x - 1]);
            // 更新线段树
            update(1, 1, n, x, s[x - 1], t[x - 1]);
            // 输出s中"red"数量与t中"red"数量之差
            cout << treeS[1].red - treeT[1].red << "\n";
        }
    }
    return 0;
}
