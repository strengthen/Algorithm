#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 主函数
int main() {
    // 优化输入输出效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    // 读取行数n和列数m
    if (!(cin >> n >> m)) return 0;

    // 存储每一列的字符串。共有m列，每列长度为n。
    // 使用vector存储，方便后续排序
    vector<string> cols(m);
    
    // 预分配内存以提高效率
    for (int j = 0; j < m; ++j) {
        cols[j].reserve(n);
    }

    // 读取矩阵数据
    // 我们逐行读取，将每一行的字符追加到对应的列字符串中
    for (int i = 0; i < n; ++i) {
        string row;
        cin >> row;
        for (int j = 0; j < m; ++j) {
            cols[j].push_back(row[j]);
        }
    }

    // 对所有列进行排序
    // 排序后，相同的列会相邻排列
    sort(cols.begin(), cols.end());

    int max_count = 0;
    int current_count = 0;

    // 遍历排序后的列，统计出现次数最多的列模式
    // 因为只有初始状态完全相同的列，才能通过相同的行变换同时变为全'1'
    if (m > 0) {
        current_count = 1;
        max_count = 1;
        for (int j = 1; j < m; ++j) {
            // 如果当前列与前一列相同，计数加1
            if (cols[j] == cols[j-1]) {
                current_count++;
            } else {
                // 如果不同，更新最大计数，并重置当前计数
                max_count = max(max_count, current_count);
                current_count = 1;
            }
        }
        // 处理最后一组列的计数
        max_count = max(max_count, current_count);
    }

    // 输出最大值
    cout << max_count << endl;

    return 0;
}
