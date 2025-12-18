#include <iostream> // 引入输入输出流库
#include <vector> // 引入向量容器库
#include <numeric> // 引入数值算法库

using namespace std; // 使用标准命名空间

int main() { // 主函数入口
    ios_base::sync_with_stdio(false); // 关闭stdio同步，加速IO
    cin.tie(NULL); // 解除cin与cout的绑定

    int n; // 定义变量n用于存储节点数量
    if (!(cin >> n)) return 0; // 读取n，如果读取失败则退出

    vector<int> d(n + 1); // 定义向量d存储每个节点的度数，下标从1开始
    long long sum = 0; // 定义sum存储所有度数的总和
    for (int i = 1; i <= n; ++i) { // 循环读取每个节点的度数
        cin >> d[i]; // 读取第i个节点的度数
        sum += d[i]; // 累加度数到sum
    } // 循环结束

    if (sum % 2 != 0) { // 如果总度数为奇数
        cout << -1 << endl; // 根据握手定理，图的总度数必须为偶数，输出-1
        return 0; // 程序结束
    } // if结束

    int target = sum / 2; // 计算二分图每一侧的度数和，即总和的一半
    // 定义二维DP数组，dp[i][j]表示前i个节点能否凑出度数和为j
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false)); 
    dp[0][0] = true; // 初始化，前0个节点凑出和为0是可能的

    for (int i = 1; i <= n; ++i) { // 遍历每个节点
        for (int j = 0; j <= target; ++j) { // 遍历每个可能的目标和
            dp[i][j] = dp[i-1][j]; // 情况1：不选第i个节点放入集合A（即放入集合B），状态继承自i-1
            if (j >= d[i] && dp[i-1][j - d[i]]) { // 情况2：选第i个节点放入集合A
                dp[i][j] = true; // 如果前i-1个能凑出j-d[i]，则标记为真
            } // if结束
        } // 内层循环结束
    } // 外层循环结束

    if (!dp[n][target]) { // 如果前n个节点无法凑出目标和target
        cout << -1 << endl; // 无法构成二分图，输出-1
        return 0; // 程序结束
    } // if结束

    vector<int> setA; // 定义集合A，存储第一部分节点的编号
    vector<int> setB; // 定义集合B，存储第二部分节点的编号
    int current_sum = target; // 当前需要回溯凑出的剩余和

    for (int i = n; i >= 1; --i) { // 从最后一个节点开始回溯
        if (dp[i-1][current_sum]) { // 如果不选第i个节点也能凑出current_sum
            setB.push_back(i); // 将第i个节点放入集合B
        } else { // 否则必须选第i个节点
            setA.push_back(i); // 将第i个节点放入集合A
            current_sum -= d[i]; // 更新剩余需要凑出的和
        } // else结束
    } // 循环结束

    vector<pair<int, int>> edges; // 定义向量存储生成的边
    int idxA = 0; // 集合A的当前节点指针
    int idxB = 0; // 集合B的当前节点指针

    // 当集合A和集合B都还有未处理完的节点时循环
    while (idxA < setA.size() && idxB < setB.size()) { 
        int u = setA[idxA]; // 获取集合A当前节点编号
        int v = setB[idxB]; // 获取集合B当前节点编号

        edges.push_back({u, v}); // 在u和v之间添加一条边
        d[u]--; // 减少节点u的剩余度数
        d[v]--; // 减少节点v的剩余度数

        if (d[u] == 0) idxA++; // 如果节点u的度数已满足，指针后移
        if (d[v] == 0) idxB++; // 如果节点v的度数已满足，指针后移
    } // while循环结束

    cout << edges.size() << endl; // 输出边的总数量
    for (const auto& edge : edges) { // 遍历每一条边
        cout << edge.first << " " << edge.second << endl; // 输出边的两个端点
    } // 循环结束

    return 0; // 返回0，程序正常结束
} // main函数结束
