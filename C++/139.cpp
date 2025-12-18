#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 定义模数 10^9 + 7
// Define modulo 10^9 + 7
long long MOD = 1e9 + 7;

// 计算模意义下的逆元 (使用费马小定理)
// Calculate modular inverse (using Fermat's Little Theorem)
long long modInverse(long long n) {
    long long m = MOD - 2;
    long long y = 1;
    while (m > 0) {
        if (m % 2 == 1) y = (y * n) % MOD;
        n = (n * n) % MOD;
        m /= 2;
    }
    return y;
}

int main() {
    // 优化标准I/O操作的速度
    // Optimize standard I/O operations speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    // 读取字符串的长度
    // Read the length of the string
    if (!(cin >> n)) return 0;

    string s;
    // 读取由'0'和'1'组成的字符串
    // Read the string consisting of '0' and '1'
    cin >> s;

    // 预处理所有'0'的统计信息
    // Precompute statistics for all '0's
    long long total_count0 = 0; // '0'的总个数 (Total count of '0')
    long long total_sum0 = 0;   // '0'的下标之和 (Sum of indices of '0')
    long long total_sq_sum0 = 0; // '0'的下标平方之和 (Sum of squared indices of '0')

    // 遍历字符串统计'0'的信息
    // Iterate through the string to gather '0' statistics
    for (int i = 0; i < n; ++i) {
        if (s[i] == '0') {
            total_count0++;
            total_sum0 = (total_sum0 + i) % MOD;
            total_sq_sum0 = (total_sq_sum0 + 1LL * i * i) % MOD;
        }
    }

    // 如果字符串中没有'0'，则无法形成"01"子序列，答案为0
    // If there are no '0's in the string, no "01" subsequence can be formed, answer is 0
    if (total_count0 == 0) {
        cout << 0 << endl;
        return 0;
    }

    // 累积变量，用于存储所有有效对的 d^2, d, 1 的和
    // Accumulators for sum of d^2, d, and count of pairs (1)
    long long sum_d2 = 0;
    long long sum_d = 0;
    long long sum_count = 0;

    // 当前遍历过程中遇到的'0'的统计信息
    // Statistics of '0's encountered so far during iteration
    long long cur_count0 = 0;
    long long cur_sum0 = 0;
    long long cur_sq_sum0 = 0;

    // 遍历字符串，计算每个'1'与所有'0'组成的对的贡献
    // Iterate through the string, calculating the contribution of each '1' paired with all '0's
    for (int j = 0; j < n; ++j) {
        if (s[j] == '0') {
            // 如果当前字符是'0'，更新当前'0'的统计信息
            // If current char is '0', update current '0' statistics
            cur_count0++;
            cur_sum0 = (cur_sum0 + j) % MOD;
            cur_sq_sum0 = (cur_sq_sum0 + 1LL * j * j) % MOD;
        } else {
            // 如果当前字符是'1'，计算它与所有'0'形成的对的距离贡献
            // If current char is '1', calculate distance contribution with all '0's
            
            // Case 1: i < j (即'0'在'1'之前出现)
            // d = j - i
            // 我们需要计算 sum((j-i)^k) for k=0,1,2
            // We need to calculate sum((j-i)^k) for k=0,1,2

            long long term1_count = cur_count0;
            // sum(j - i) = j * count - sum(i)
            long long term1_d = (j * cur_count0 % MOD - cur_sum0 + MOD) % MOD;
            // sum((j - i)^2) = j^2 * count - 2*j*sum(i) + sum(i^2)
            long long term1_d2 = (1LL * j * j % MOD * cur_count0 % MOD - 2LL * j * cur_sum0 % MOD + cur_sq_sum0 + MOD) % MOD;
            term1_d2 = (term1_d2 + MOD) % MOD; // 再次取模以防负数 (Mod again to prevent negative)

            // Case 2: i > j (即'0'在'1'之后出现，在环形中视为绕了一圈)
            // d = n + j - i
            // 此时考虑的是尚未遍历到的'0' (Suffix '0's)
            // Consider '0's not yet traversed (Suffix '0's)

            long long suf_count0 = total_count0 - cur_count0;
            long long suf_sum0 = (total_sum0 - cur_sum0 + MOD) % MOD;
            long long suf_sq_sum0 = (total_sq_sum0 - cur_sq_sum0 + MOD) % MOD;

            long long nj = n + j;
            long long term2_count = suf_count0;
            // sum(n + j - i) = (n + j) * count - sum(i)
            long long term2_d = (nj * suf_count0 % MOD - suf_sum0 + MOD) % MOD;
            // sum((n + j - i)^2) = (n + j)^2 * count - 2*(n + j)*sum(i) + sum(i^2)
            long long term2_d2 = (nj % MOD * nj % MOD * suf_count0 % MOD - 2LL * nj % MOD * suf_sum0 % MOD + suf_sq_sum0 + MOD) % MOD;
            term2_d2 = (term2_d2 + MOD) % MOD; // 再次取模以防负数 (Mod again to prevent negative)

            // 将当前'1'产生的贡献累加到总和中
            // Accumulate contributions from current '1' to totals
            sum_count = (sum_count + term1_count + term2_count) % MOD;
            sum_d = (sum_d + term1_d + term2_d) % MOD;
            sum_d2 = (sum_d2 + term1_d2 + term2_d2) % MOD;
        }
    }

    // 根据推导公式计算最终答案
    // Calculate final answer based on derived formula
    // 每一对 (i, j) 的贡献为 F(d) = ( (n-d)*(n-d+1) ) / 2
    // Contribution of each pair is F(d) = ( (n-d)*(n-d+1) ) / 2
    // 展开后 F(d) = 1/2 * ( d^2 - (2n+1)d + n(n+1) )
    // Expanded: F(d) = 1/2 * ( d^2 - (2n+1)d + n(n+1) )
    // 总和 Ans = 1/2 * ( sum_d2 - (2n+1)sum_d + n(n+1)sum_count )
    // Total Sum Ans = 1/2 * ( sum_d2 - (2n+1)sum_d + n(n+1)sum_count )

    long long inv2 = modInverse(2); // 2的模逆元 (Modular inverse of 2)
    long long term_sq = sum_d2;
    long long term_lin = (2LL * n + 1) % MOD * sum_d % MOD;
    long long term_const = 1LL * n * (n + 1) % MOD * sum_count % MOD;

    // 组合各项并取模
    // Combine terms and take modulo
    long long ans = (term_sq - term_lin + MOD) % MOD;
    ans = (ans + term_const) % MOD;
    ans = (ans * inv2) % MOD;

    // 输出最终结果
    // Output final result
    cout << ans << endl;

    return 0;
}
