#include <iostream> // 引入输入输出流库
#include <vector>   // 引入向量容器库
#include <algorithm> // 引入算法库

using namespace std; // 使用标准命名空间

const int MAXN = 100005; // 定义最大节点数常量，根据题目范围设定
vector<int> adj[MAXN];   // 定义邻接表存储树结构，adj[i]存储节点i的邻居
bool inV[MAXN];          // 定义布尔数组标记节点是否在集合V中
long long S[MAXN];       // S[i]数组表示以i为根的子树中包含集合V中节点的数量
long long ans[MAXN];     // ans[i]数组表示以i为最近公共祖先(LCA)的点对数量

// 深度优先搜索函数，用于计算子树信息和最终答案
// u: 当前遍历的节点
// p: u的父节点，防止遍历回父节点
void dfs(int u, int p) {
    S[u] = inV[u] ? 1 : 0; // 初始化S[u]，如果当前节点u在集合V中则初始为1，否则为0
    long long sum_sq = 0;  // 用于累加所有子节点子树中V节点数量的平方和，即sum(S[v]^2)

    // 遍历当前节点u的所有邻接节点
    for (int v : adj[u]) {
        if (v == p) continue; // 如果邻接节点v是父节点p，则跳过以避免死循环
        dfs(v, u);            // 递归调用dfs处理子节点v
        S[u] += S[v];         // 回溯时，将子节点v的S[v]累加到当前节点S[u]
        sum_sq += S[v] * S[v]; // 累加子节点S[v]的平方到sum_sq
    }

    // 计算以当前节点u为LCA的点对数量
    // 核心逻辑：
    // 以u为根的子树中，所有来自集合V的节点两两组合（包括自己对自己）的总对数为 S[u] * S[u]
    // 其中，LCA位于u的某个子节点v的子树内部的点对数为 S[v] * S[v]
    // 因此，LCA正好是u的点对数 = 总对数 - 所有子树内部的点对数之和
    ans[u] = S[u] * S[u] - sum_sq; 
}

int main() {
    // 优化标准输入输出流的速度，关闭同步
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); // 解除cin与cout的绑定

    int n; // 定义变量n存储树的节点数
    if (!(cin >> n)) return 0; // 从输入读取n，如果读取失败则结束程序

    // 循环读取n-1条边，构建树
    for (int i = 0; i < n - 1; ++i) {
        int u, v; // 定义变量u和v存储边的两个端点
        cin >> u >> v; // 读取一条边的两个端点
        adj[u].push_back(v); // 将v添加到u的邻接表中
        adj[v].push_back(u); // 将u添加到v的邻接表中（无向边）
    }

    int k; // 定义变量k存储集合V的大小
    cin >> k; // 读取k的值

    // 循环读取集合V中的k个节点
    for (int i = 0; i < k; ++i) {
        int a; // 定义变量a存储节点编号
        cin >> a; // 读取节点编号
        inV[a] = true; // 在inV数组中标记节点a存在于集合V中
    }

    // 从根节点1开始进行深度优先搜索，父节点设为0（表示无父节点）
    dfs(1, 0);

    // 循环输出每个节点的计算结果
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << (i == n ? "" : " "); // 输出ans[i]，如果是最后一个数则不加空格，否则加空格
    }
    cout << endl; // 输出换行符，结束输出

    return 0; // 程序正常结束，返回0
}
