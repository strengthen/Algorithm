#include <iostream> // 引入输入输出流库
#include <vector>   // 引入向量容器库
#include <algorithm> // 引入算法库，用于使用 max 和 min 函数

using namespace std; // 使用标准命名空间

int main() { // 主函数入口
    ios_base::sync_with_stdio(false); // 关闭 C++ 标准流与 C 标准流的同步，提高 I/O 效率
    cin.tie(NULL); // 解除 cin 与 cout 的绑定，进一步提高 I/O 效率

    int n, m, k; // 定义变量 n, m, k 分别表示行数、列数和小球数量
    if (!(cin >> n >> m >> k)) return 0; // 输入 n, m, k，如果输入失败则直接返回

    int max_dim = max(n, m); // 计算行数和列数中的较大值
    if (k < max_dim) { // 如果小球数量少于行数和列数中的较大值
        cout << -1 << endl; // 无法满足每行每列至少有一个小球的条件，输出 -1
        return 0; // 结束程序
    }

    // 使用一维 vector 模拟 n * m 的二维矩阵，初始化所有元素为 0
    // 使用 long long 防止索引溢出（虽然题目限制 n*m <= 10^6，int 足够，但习惯上防范一下）
    vector<int> grid(n * m, 0); 

    int min_dim = min(n, m); // 计算行数和列数中的较小值

    // 步骤 1: 沿着主对角线放置小球，覆盖 min_dim 行和 min_dim 列
    for (int i = 0; i < min_dim; ++i) { // 遍历 0 到 min_dim - 1
        grid[i * m + i] = 1; // 在 (i, i) 位置放置 1 个小球
    }

    // 步骤 2: 处理剩余的行或列
    if (n < m) { // 如果行数小于列数，说明还有剩余的列未被覆盖
        for (int j = n; j < m; ++j) { // 遍历剩余的列索引
            grid[0 * m + j] = 1; // 在第 0 行的这些列上放置 1 个小球
        }
    } else if (n > m) { // 如果行数大于列数，说明还有剩余的行未被覆盖
        for (int i = m; i < n; ++i) { // 遍历剩余的行索引
            grid[i * m + 0] = 1; // 在这些行的第 0 列上放置 1 个小球
        }
    }

    // 步骤 3: 将剩余的小球全部分配给第一个格子 (0, 0)
    // 此时已经消耗了 max_dim 个小球
    int remaining = k - max_dim; // 计算剩余的小球数量
    grid[0] += remaining; // 将剩余小球加到 (0, 0) 位置

    // 步骤 4: 输出结果矩阵
    for (int i = 0; i < n; ++i) { // 遍历每一行
        for (int j = 0; j < m; ++j) { // 遍历每一列
            cout << grid[i * m + j] << (j == m - 1 ? "" : " "); // 输出当前格子的小球数量，行末不加空格
        }
        cout << "\n"; // 每一行输出结束后换行
    }

    return 0; // 程序正常结束
}
