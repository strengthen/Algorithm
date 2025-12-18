#include <iostream> // 引入输入输出流库
#include <vector>   // 引入向量容器库
#include <algorithm> // 引入算法库，用于max函数

using namespace std; // 使用标准命名空间

int main() {
    int n; // 定义变量n，用于存储同学的数量
    // 循环读取输入，处理可能的多组测试数据
    while (cin >> n) { 
        vector<int> h(n); // 定义一个大小为n的向量h，用于存储身高
        // 遍历输入所有的身高数据
        for (int i = 0; i < n; ++i) {
            cin >> h[i]; // 读取第i个同学的身高
        }

        // 如果没有同学，直接输出0（防御性编程，虽然题目范围n>=1）
        if (n == 0) {
            cout << 0 << endl; // 输出0
            continue; // 继续下一次循环
        }

        // dp_inc[i]表示以第i个同学结尾的最长递增子序列的长度
        vector<int> dp_inc(n, 1); // 初始化数组，默认长度为1（自身）
        // 从左向右遍历每一位同学
        for (int i = 0; i < n; ++i) {
            // 遍历i之前的所有同学j
            for (int j = 0; j < i; ++j) {
                // 如果第j个同学比第i个同学矮，说明可以构成递增序列
                if (h[j] < h[i]) {
                    // 更新dp_inc[i]，取当前值和dp_inc[j]+1的较大值
                    dp_inc[i] = max(dp_inc[i], dp_inc[j] + 1);
                }
            }
        }

        // dp_dec[i]表示以第i个同学结尾（从右向左看）的最长递增子序列长度
        // 也就是从左向右看的以i开始的最长递减子序列长度
        vector<int> dp_dec(n, 1); // 初始化数组，默认长度为1
        // 从右向左遍历每一位同学
        for (int i = n - 1; i >= 0; --i) {
            // 遍历i之后的所有同学j
            for (int j = n - 1; j > i; --j) {
                // 如果第j个同学比第i个同学矮，说明从i到j是递减的
                if (h[j] < h[i]) {
                    // 更新dp_dec[i]，取当前值和dp_dec[j]+1的较大值
                    dp_dec[i] = max(dp_dec[i], dp_dec[j] + 1);
                }
            }
        }

        int max_len = 0; // 用于记录合唱队形的最大长度
        // 遍历每个位置，将其作为合唱队的“山峰”
        for (int i = 0; i < n; ++i) {
            // 当前合唱队形长度 = 左侧递增长度 + 右侧递减长度 - 1
            // 减1是因为“山峰”位置在两个序列中都算了一次
            int current_len = dp_inc[i] + dp_dec[i] - 1;
            // 更新最大长度
            if (current_len > max_len) {
                max_len = current_len;
            }
        }

        // 最少出列人数 = 总人数 - 合唱队形最大长度
        cout << n - max_len << endl; // 输出结果
    }
    return 0; // 程序正常结束
}

