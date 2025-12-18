#include <iostream> // 引入输入输出流库，用于标准输入输出
#include <vector> // 引入向量库，用于存储动态数组
#include <string> // 引入字符串库，用于处理字符串数据
#include <algorithm> // 引入算法库，用于使用排序函数

using namespace std; // 使用标准命名空间std，避免每次调用标准库需加std::

int main() { // 主函数入口，程序从这里开始执行
    int n, m, k; // 声明三个整数变量：n为行数，m为列数，k为最大染色数
    if (!(cin >> n >> m >> k)) return 0; // 从标准输入读取n, m, k，若读取失败则退出程序

    vector<string> grid(n); // 创建一个大小为n的字符串向量grid，用于存储矩阵每一行
    for (int i = 0; i < n; ++i) { // 循环i从0到n-1，遍历矩阵的每一行
        cin >> grid[i]; // 读取当前行的字符串，存入grid[i]
    } // 结束读取矩阵的循环

    vector<int> segments; // 创建一个整数向量segments，用于存储所有竖向连续白色格子的长度
    for (int j = 0; j < m; ++j) { // 循环j从0到m-1，遍历矩阵的每一列
        int current_len = 0; // 初始化当前列当前连续白色段的长度为0
        for (int i = 0; i < n; ++i) { // 循环i从0到n-1，遍历当前列的每一行
            if (grid[i][j] == 'o') { // 判断当前位置(i, j)的字符是否为白色格子'o'
                current_len++; // 如果是白色格子，当前连续长度加1
            } else { // 如果当前位置不是白色格子（即为黑色格子'*'）
                if (current_len > 0) { // 如果之前的连续白色段长度大于0
                    segments.push_back(current_len); // 将该段长度存入segments向量中
                } // 结束长度大于0的判断
                current_len = 0; // 重置当前连续长度为0，准备统计下一段
            } // 结束字符判断
        } // 结束当前列的行遍历
        if (current_len > 0) { // 检查该列最后一段是否为连续白色格子且长度大于0
            segments.push_back(current_len); // 将最后一段的长度存入segments向量中
        } // 结束列尾段的判断
    } // 结束列遍历

    sort(segments.rbegin(), segments.rend()); // 对segments向量进行降序排序，优先处理长段

    long long score = 0; // 声明长整型变量score并初始化为0，用于累加总分
    for (int len : segments) { // 使用范围for循环遍历排序后的每一个段长度len
        if (k <= 0) break; // 如果剩余可用染色数k小于等于0，结束循环

        if (len < 2) continue; // 如果当前段长度小于2，无法产生得分（至少需2个相邻），跳过

        int take = min(k, len); // 计算当前段实际染色的数量，取k和len中的较小值
        if (take >= 2) { // 如果实际染色的数量至少为2，才能形成相邻红色对
            score += (take - 1); // 增加得分为染色数量减1（n个连续红色产生n-1个分数）
        } // 结束得分计算
        k -= take; // 从剩余总染色数k中减去当前段消耗的数量
    } // 结束所有段的遍历

    cout << score << endl; // 将计算出的最大总分输出到标准输出

    return 0; // 主函数返回0，表示程序正常结束
} // 结束主函数
