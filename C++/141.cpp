#include <iostream> // 引入输入输出流库

using namespace std; // 使用标准命名空间

// 定义模数 10^9 + 7
const long long MOD = 1e9 + 7;

// 快速幂函数，计算 (base^exp) % MOD
long long qpow(long long base, long long exp) {
    long long res = 1; // 初始化结果为 1
    while (exp > 0) { // 当指数大于 0 时循环
        if (exp % 2 == 1) res = (res * base) % MOD; // 如果指数是奇数，将当前底数乘入结果
        base = (base * base) % MOD; // 底数平方
        exp /= 2; // 指数减半
    }
    return res; // 返回结果
}

int main() {
    int n; // 定义变量 n 用于存储二叉树深度
    
    // 循环读入 n（虽然题目描述可能只有一组，但处理多组输入更健壮）
    while (cin >> n) {
        // 如果深度为 1，只有一个节点，无法形成长度为 2 的路径
        if (n == 1) {
            cout << 0 << endl; // 输出 0
        } else {
            // 计算 2^(n-1)
            // Calculate 2^(n-1)
            long long power_of_2 = qpow(2, n - 1);
            
            // 根据推导公式：总路径数 = 3 * 2^(n-1) - 5
            // 第一部分：3 * 2^(n-1)
            long long ans = (3 * power_of_2) % MOD;
            
            // 减去 5，并处理负数取模的情况（加 MOD 再模 MOD）
            ans = (ans - 5 + MOD) % MOD;
            
            // 输出最终结果
            cout << ans << endl;
        }
    }
    return 0; // 程序正常结束
}
