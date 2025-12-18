#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 定义线段树节点结构体，用于维护区间信息
struct Node {
    long long cnt;      // 区间内全'0'子串的总数量
    int len;            // 区间覆盖的长度
    int l0;             // 从区间左端点开始连续'0'的长度
    int r0;             // 从区间右端点开始连续'0'的长度
    bool is_all_0;      // 标记该区间是否全部由'0'组成
};

const int MAXN = 200005; // 最大字符串长度 + 缓冲
Node tree[MAXN * 4];     // 线段树数组，大小为4倍n
string s;                // 存储输入的二进制字符串
int n, q;                // n为字符串长度，q为询问次数

// 合并两个子节点的信息，生成父节点信息
Node merge(const Node& left, const Node& right) {
    Node res;
    res.len = left.len + right.len; // 父节点长度为左右子节点长度之和
    res.is_all_0 = left.is_all_0 && right.is_all_0; // 只有左右都全为0，父节点才全为0

    // 计算合并后的全'0'子串总数量
    // 包含三部分：
    // 1. 左子区间内部的全'0'子串数量
    // 2. 右子区间内部的全'0'子串数量
    // 3. 跨越左右子区间分界线的全'0'子串数量
    // 跨越分界线的部分必定由左区间的后缀'0'和右区间的前缀'0'拼接而成
    // 根据组合原理，数量为 (左后缀0长度) * (右前缀0长度)
    res.cnt = left.cnt + right.cnt + (long long)left.r0 * right.l0;

    // 计算合并后的左端连续'0'长度
    if (left.is_all_0) {
        // 如果左区间全为0，则左端连续0长度 = 左区间长度 + 右区间左端连续0长度
        res.l0 = left.len + right.l0;
    } else {
        // 否则，仅取决于左区间本身的左端连续0长度
        res.l0 = left.l0;
    }

    // 计算合并后的右端连续'0'长度
    if (right.is_all_0) {
        // 如果右区间全为0，则右端连续0长度 = 右区间长度 + 左区间右端连续0长度
        res.r0 = right.len + left.r0;
    } else {
        // 否则，仅取决于右区间本身的右端连续0长度
        res.r0 = right.r0;
    }

    return res;
}

// 构建线段树
// node: 当前节点索引, start: 当前区间起始位置, end: 当前区间结束位置
void build(int node, int start, int end) {
    if (start == end) {
        // 叶子节点初始化
        tree[node].len = 1;
        if (s[start - 1] == '0') { // 注意字符串下标从0开始，题目下标从1开始
            tree[node].cnt = 1;
            tree[node].l0 = 1;
            tree[node].r0 = 1;
            tree[node].is_all_0 = true;
        } else {
            tree[node].cnt = 0;
            tree[node].l0 = 0;
            tree[node].r0 = 0;
            tree[node].is_all_0 = false;
        }
        return;
    }
    int mid = (start + end) / 2;
    build(node * 2, start, mid);       // 递归构建左子树
    build(node * 2 + 1, mid + 1, end); // 递归构建右子树
    tree[node] = merge(tree[node * 2], tree[node * 2 + 1]); // 合并子节点信息
}

// 区间查询函数
// node: 当前节点索引, start/end: 当前节点覆盖的区间
// l/r: 询问的目标区间
Node query(int node, int start, int end, int l, int r) {
    // 如果当前区间完全包含在询问区间内，直接返回当前节点信息
    if (l <= start && end <= r) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    // 如果询问区间完全在左半部分
    if (r <= mid) {
        return query(node * 2, start, mid, l, r);
    } 
    // 如果询问区间完全在右半部分
    else if (l > mid) {
        return query(node * 2 + 1, mid + 1, end, l, r);
    } 
    // 如果询问区间跨越左右两部分，需要分别查询并合并结果
    else {
        Node left_res = query(node * 2, start, mid, l, mid);
        Node right_res = query(node * 2 + 1, mid + 1, end, mid + 1, r);
        return merge(left_res, right_res);
    }
}

int main() {
    // 优化输入输出效率，防止超时
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;
    cin >> s;
    cin >> q;

    // 构建线段树，根节点索引为1，区间为[1, n]
    build(1, 1, n);

    while (q--) {
        int l, r;
        cin >> l >> r;
        
        // 查询区间[l, r]的全'0'子串信息
        Node res = query(1, 1, n, l, r);
        
        long long len = r - l + 1;
        // 计算区间内所有可能的连续子串总数：L*(L+1)/2
        long long total_substrings = len * (len + 1) / 2;
        
        // 答案 = 总子串数 - 全'0'子串数
        // 解释：
        // 只要子串中包含至少一个'1'，其“自审值”（OR运算和）就是1。
        // 只有当子串全为'0'时，“自审值”才是0。
        // 题目要求所有子串“自审值”之和，即求有多少个子串包含至少一个'1'。
        cout << total_substrings - res.cnt << "\n";
    }

    return 0;
}
