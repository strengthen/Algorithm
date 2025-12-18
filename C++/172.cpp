#include <iostream> // 引入输入输出流库
#include <vector>   // 引入向量容器库
#include <string>   // 引入字符串库
#include <algorithm> // 引入算法库，用于排序
#include <numeric>  // 引入数值计算库

using namespace std; // 使用标准命名空间

int main() {
    int n, m; // 定义矩阵的行数和列数
    long long k; // 定义最多可染红的格子数量，使用long long防止溢出
    if (!(cin >> n >> m >> k)) return 0; // 读取n, m, k，如果读取失败则退出

    vector<string> grid(n); // 定义一个字符串向量存储矩阵
    for (int i = 0; i < n; ++i) { // 遍历每一行
        cin >> grid[i]; // 读取每一行的字符串
    }

    vector<int> segments; // 定义一个向量存储所有连续空白段的长度
    long long total_capacity = 0; // 定义总的空白格子数量

    // 遍历每一列，统计连续空白段
    for (int j = 0; j < m; ++j) { // 外层循环遍历列
        int current_len = 0; // 当前连续空白段的长度
        for (int i = 0; i < n; ++i) { // 内层循环遍历行
            if (grid[i][j] == 'o') { // 如果当前格子是空白
                current_len++; // 长度加1
            } else { // 如果当前格子是黑色
                if (current_len > 0) { // 如果之前有累计的空白段
                    segments.push_back(current_len); // 将长度加入segments
                    total_capacity += current_len; // 累加到总容量
                    current_len = 0; // 重置当前长度
                }
            }
        }
        if (current_len > 0) { // 处理列尾的连续空白段
            segments.push_back(current_len); // 将长度加入segments
            total_capacity += current_len; // 累加到总容量
        }
    }

    // 将所有空白段的长度按降序排序，贪心策略：优先使用长段
    sort(segments.rbegin(), segments.rend());

    long long used_k = min(k, total_capacity); // 计算实际能使用的红色格子数量，不能超过总空白数
    long long current_sum = 0; // 当前已覆盖的空白格子总数
    int segments_count = 0; // 使用的空白段数量

    for (int len : segments) { // 遍历排序后的空白段
        if (current_sum >= used_k) break; // 如果已覆盖数量达到需求，则停止
        current_sum += len; // 累加当前段长度
        segments_count++; // 增加使用的段数
    }

    if (used_k == 0) { // 如果不需要染任何格子
        cout << 0 << endl; // 输出0分
    } else {
        // 最大得分 = 实际染色的格子数 - 占用的段数
        // 原理：每占用一个新段，第一个格子不得分（消耗1，收益0），后续格子每个得1分（消耗1，收益1）
        // 设使用了p个段，染了K个格子。得分 = (len1-1) + (len2-1) + ... (对于填满的段) + (last_piece_len - 1)
        // 实际上等于 Total_Cells - Segments_Count
        cout << used_k - segments_count << endl; // 输出计算结果
    }

    return 0; // 程序结束
}
