#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// 全局变量存储最小和，初始化为最大长整型
// Global variable to store the minimum sum, initialized to LLONG_MAX
long long min_sum = LLONG_MAX;

// 标记素数是否被使用过，数组大小足够覆盖1000以内的素数
// Mark whether a prime has been used, size sufficient for primes up to 1000
bool used_prime[1001] = {false};

// 存储每个数的素因子列表
// Store the list of prime factors for each number
vector<vector<int>> all_factors;

// 获取一个数的所有去重素因子
// Function to get all distinct prime factors of a number
vector<int> get_prime_factors(int num) {
    vector<int> f; // 存储素因子的向量 // Vector to store prime factors
    // 从2开始遍历到sqrt(num)
    // Iterate from 2 up to sqrt(num)
    for (int i = 2; i * i <= num; ++i) {
        // 如果i是num的因子
        // If i is a factor of num
        if (num % i == 0) {
            f.push_back(i); // 将i加入素因子列表 // Add i to the list
            // 除尽num中的i因子
            // Divide num by i until it's no longer divisible
            while (num % i == 0) num /= i;
        }
    }
    // 如果num大于1，说明剩下的num本身就是一个素数
    // If num > 1, the remaining num is a prime itself
    if (num > 1) f.push_back(num);
    return f; // 返回素因子列表 // Return the list
}

// 深度优先搜索函数
// Depth First Search function
// idx: 当前处理到第几个数 (Current index of number being processed)
// current_sum: 当前已选素因子的和 (Sum of selected prime factors so far)
void dfs(int idx, long long current_sum) {
    // 剪枝：如果当前和已经超过已知的最小和，停止搜索
    // Pruning: if current sum exceeds the known minimum, stop
    if (current_sum >= min_sum) return;

    // 基本情况：所有数都处理完毕
    // Base case: all numbers processed
    if (idx == all_factors.size()) {
        // 更新最小和
        // Update the minimum sum
        min_sum = current_sum;
        return;
    }

    // 遍历当前数的所有可选素因子
    // Iterate through all possible prime factors of the current number
    // 使用引用避免拷贝，const保证不修改
    // Use reference to avoid copy, const to ensure no modification
    const vector<int>& factors = all_factors[idx];
    for (size_t i = 0; i < factors.size(); ++i) {
        int p = factors[i]; // 当前尝试的素因子 // Current prime factor to try
        // 如果该素因子未被使用
        // If this prime factor has not been used
        if (!used_prime[p]) {
            used_prime[p] = true; // 标记为已使用 // Mark as used
            // 递归处理下一个数
            // Recursively process the next number
            dfs(idx + 1, current_sum + p);
            used_prime[p] = false; // 回溯：取消标记 // Backtrack: unmark
        }
    }
}

int main() {
    int n; // 输入的数字个数 // Number of integers
    // 读取n
    // Read n
    if (!(cin >> n)) return 0;

    // 读取n个整数
    // Read n integers
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i]; // 读取每个整数 // Read each integer
    }

    // 预处理每个数的素因子
    // Precompute prime factors for each number
    for (int i = 0; i < n; ++i) {
        all_factors.push_back(get_prime_factors(a[i]));
    }

    // 优化：按照素因子个数从小到大排序
    // Optimization: Sort by the number of prime factors in ascending order
    // 这样也就是优先处理选择少的数（最小剩余值启发式），有助于剪枝
    // This prioritizes numbers with fewer choices (MRV heuristic), helping pruning
    sort(all_factors.begin(), all_factors.end(), [](const vector<int>& a, const vector<int>& b) {
        return a.size() < b.size();
    });

    // 开始深度优先搜索，从第0个数开始，初始和为0
    // Start DFS from index 0 with initial sum 0
    dfs(0, 0);

    // 输出结果
    // Output the result
    if (min_sum == LLONG_MAX) {
        // 如果min_sum没有被更新，说明无解，输出-1
        // If min_sum was not updated, no solution found, output -1
        cout << -1 << endl;
    } else {
        // 否则输出找到的最小和
        // Otherwise output the minimum sum found
        cout << min_sum << endl;
    }

    return 0;
}
