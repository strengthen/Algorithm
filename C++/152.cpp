#include <iostream> // 引入输入输出流库
#include <vector>   // 引入向量容器库
#include <algorithm> // 引入算法库，如 max 函数
#include <cstring>   // 引入 C 风格字符串库，用于 memset

using namespace std; // 使用标准命名空间

// 全局变量定义
int T; // 数据组数
int N, M; // 矩阵的行数和列数
int matrix[10][10]; // 存储矩阵数据，大小开到 10x10 足够容纳 6x6
int dp[10][1 << 6]; // 动态规划数组，dp[i][mask] 表示第 i 行状态为 mask 时的最大和

// 判断行内状态是否合法（没有相邻的 1）
bool isValidRow(int mask) {
    // 如果 mask 与左移一位后的自己按位与不为 0，说明有相邻的 1
    return (mask & (mask << 1)) == 0; 
}

// 判断两行状态是否兼容（检查 8 邻域）
bool isCompatible(int currentMask, int prevMask) {
    if (currentMask & prevMask) return false; // 检查垂直方向是否有重叠
    if (currentMask & (prevMask << 1)) return false; // 检查左上/右下方向是否有相邻
    if (currentMask & (prevMask >> 1)) return false; // 检查右上/左下方向是否有相邻
    return true; // 如果都没有冲突，则返回真
}

// 计算当前行在特定状态下的数值之和
int calculateSum(int row, int mask) {
    int sum = 0; // 初始化和为 0
    for (int j = 0; j < M; ++j) { // 遍历每一列
        if (mask & (1 << j)) { // 如果当前位被选中（为 1）
            sum += matrix[row][j]; // 累加对应的矩阵元素值
        }
    }
    return sum; // 返回计算的总和
}

// 处理单组数据的函数
void solve() {
    cin >> N >> M; // 读取行数和列数
    for (int i = 0; i < N; ++i) { // 遍历每一行
        for (int j = 0; j < M; ++j) { // 遍历每一列
            cin >> matrix[i][j]; // 读取矩阵元素
        }
    }

    // 初始化 dp 数组为 0
    memset(dp, 0, sizeof(dp)); // 将 dp 数组的所有元素重置为 0

    // 初始化第一行的状态
    for (int mask = 0; mask < (1 << M); ++mask) { // 遍历第一行所有可能的状态
        if (isValidRow(mask)) { // 如果行内状态合法
            dp[0][mask] = calculateSum(0, mask); // 计算第一行的值作为初始 dp 值
        }
    }

    // 动态规划过程，从第二行开始
    for (int i = 1; i < N; ++i) { // 遍历第 1 行到第 N-1 行
        for (int mask = 0; mask < (1 << M); ++mask) { // 遍历当前行的所有状态
            if (!isValidRow(mask)) continue; // 如果当前行状态不合法，跳过

            int currentSum = calculateSum(i, mask); // 计算当前行该状态下的数值和
            int maxPrev = 0; // 用于记录上一行兼容状态中的最大值

            for (int prevMask = 0; prevMask < (1 << M); ++prevMask) { // 遍历上一行的所有状态
                if (!isValidRow(prevMask)) continue; // 如果上一行状态不合法，跳过
                
                if (isCompatible(mask, prevMask)) { // 如果当前行状态和上一行状态兼容
                    maxPrev = max(maxPrev, dp[i-1][prevMask]); // 更新最大前驱值
                }
            }
            dp[i][mask] = maxPrev + currentSum; // 状态转移：当前最大值 = 前驱最大值 + 当前行值
        }
    }

    // 计算最终结果
    int ans = 0; // 初始化答案为 0
    for (int mask = 0; mask < (1 << M); ++mask) { // 遍历最后一行所有状态
        if (isValidRow(mask)) { // 如果状态合法
            ans = max(ans, dp[N-1][mask]); // 更新全局最大值
        }
    }
    cout << ans << endl; // 输出该组数据的答案
}

// 主函数
int main() {
    cin >> T; // 读取数据组数
    while (T--) { // 循环处理每一组数据
        solve(); // 调用解决函数
    }
    return 0; // 程序正常结束
}
