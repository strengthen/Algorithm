#include <iostream> // 引入输入输出流库
#include <vector>   // 引入向量容器库
#include <algorithm> // 引入算法库，用于使用 max 函数

using namespace std; // 使用标准命名空间

int main() {
    int n; // 定义变量 n，用于存储梅花桩的数量
    // 读取输入，循环读取直到输入结束，虽然题目通常只有一组数据，但这样写更通用
    while (cin >> n) {
        vector<int> heights(n); // 创建一个大小为 n 的向量，存储梅花桩的高度
        // 循环读取每一个梅花桩的高度
        for (int i = 0; i < n; ++i) {
            cin >> heights[i]; // 将输入的高度值存入向量中
        }

        // 创建一个大小为 n 的向量 dp，用于动态规划
        // dp[i] 表示以第 i 个梅花桩为结尾的最长上升子序列的长度
        // 初始化每个位置的值为 1，因为每个桩自身至少构成长度为 1 的序列
        vector<int> dp(n, 1);
        
        int result = 0; // 用于存储最终的最大步数
        if (n > 0) result = 1; // 如果有梅花桩，初始结果至少为 1

        // 外层循环：遍历每一个梅花桩，计算以该桩结尾的最长上升子序列长度
        for (int i = 0; i < n; ++i) {
            // 内层循环：遍历当前桩 i 之前的所有桩 j
            for (int j = 0; j < i; ++j) {
                // 如果当前桩 i 的高度严格大于之前桩 j 的高度
                // 说明可以从桩 j 跳到桩 i
                if (heights[i] > heights[j]) {
                    // 状态转移方程：尝试将 i 接在 j 后面
                    // 如果接在 j 后面能得到更长的序列，则更新 dp[i]
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            // 每次计算完 dp[i] 后，更新全局最大值 result
            // result 记录的是所有 dp[i] 中的最大值
            if (dp[i] > result) {
                result = dp[i]; // 更新最大步数
            }
        }

        // 输出 Redraiment 最多可以跳过的梅花桩数
        cout << result << endl;
    }
    return 0; // 程序正常结束
}
