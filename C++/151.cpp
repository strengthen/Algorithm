#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 全局变量用于存储输入数据 n 和 m
// Global variables to store input data n and m
int n;
long long m;

// 用于存储输入的数组 a
// Vector to store input array a
vector<long long> a;

// 用于存储最大模和的结果
// Variable to store the maximum modulo sum result
long long max_mod_sum = 0;

// 深度优先搜索函数，遍历所有可能的子序列
// DFS function to traverse all possible subsequences
// index: 当前考虑到的数组元素下标
// index: Current index of array element being considered
// current_sum: 当前子序列的和对 m 取模后的值
// current_sum: Current subsequence sum modulo m
void dfs(int index, long long current_sum) {
    // 递归终止条件：如果已经考虑完所有元素
    // Base case: if all elements have been considered
    if (index == n) {
        // 更新最大模和
        // Update the maximum modulo sum
        max_mod_sum = max(max_mod_sum, current_sum);
        return;
    }

    // 选项1：不选择当前元素 a[index]，直接处理下一个元素
    // Option 1: Do not select current element a[index], proceed to next
    dfs(index + 1, current_sum);

    // 选项2：选择当前元素 a[index]
    // Option 2: Select current element a[index]
    // 计算新的和并对 m 取模。注意：(A + B) % m = ((A % m) + (B % m)) % m
    // Calculate new sum modulo m. Note: (A + B) % m = ((A % m) + (B % m)) % m
    // current_sum 已经是模 m 的值，所以直接相加后再取模即可
    // current_sum is already modulo m, so just add and take modulo
    dfs(index + 1, (current_sum + a[index]) % m);
}

int main() {
    // 优化标准输入输出流的速度
    // Optimize standard I/O operations speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 读取 n 和 m
    // Read n and m
    if (cin >> n >> m) {
        // 调整数组大小以容纳 n 个元素
        // Resize vector to hold n elements
        a.resize(n);
        
        // 读取数组中的 n 个整数
        // Read n integers into the array
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        // 从第 0 个元素开始进行深度优先搜索，初始和为 0
        // Start DFS from index 0 with initial sum 0
        dfs(0, 0);

        // 输出最终计算得到的最大模和
        // Output the final calculated maximum modulo sum
        cout << max_mod_sum << endl;
    }

    return 0;
}
