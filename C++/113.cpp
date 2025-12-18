#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

// 定义 long long 类型，用于处理大整数
#define ll long long

// 定义模数常量 10^9 + 7
#define MO 1000000007ll

// 定义数组最大大小（原代码保留，实际主要用到 p 数组）
#define MXN 1000002

// 快速读入函数，优化输入效率
inline void rd(ll& x) {
    x = 0;
    short f = 1;
    char c = getchar();
    while ((c < '0' || c > '9') && c != '-') c = getchar();
    if (c == '-') f = -1, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    x *= f;
}

// 全局变量定义
// T: 测试用例数, n: 数组大小, m: 操作参数, k: 操作次数, ans: 最终答案
ll T = 1, n, m, k, ans;
// p[32] 用于存储操作次数为 0 到 30 次的概率，以及 >= 31 次的概率和
ll p[32]; 

// 快速幂函数：计算 (a^b) % MO
ll ksm(ll a, ll b) {
    ll s = 1;
    while (b) {
        if (b & 1) s = s * a % MO; // 如果 b 是奇数，乘入结果
        a = a * a % MO; // 底数平方
        b >>= 1; // 指数右移一位（除以2）
    }
    return s;
}

// 计算组合数 C(n, m) % MO
// 注意：这里的 n 对应题目中的 k (很大)，m 对应循环变量 i (很小，<=30)
ll cal(ll n, ll m) {
    ll res = 1;
    // C(n, m) = n * (n-1) * ... * (n-m+1) / m!
    // 循环计算分子累乘，并乘以分母的逆元
    for (ll i = 1, j = n - m + 1; i <= m; i++, j++)
        res = res * (j % MO) % MO * ksm(i, MO - 2) % MO;
    return res;
}

void solve() {
    // 读入 n, m, k
    // Read n, m, k
    rd(n), rd(m), rd(k);
    
    // 计算 2^k 的模逆元 (即 1/2^k)，用于计算概率
    ll inv2k = ksm(ksm(2, k), MO - 2);
    
    // 初始化概率数组 p
    for (ll i = 0; i <= 30; i++) {
        // p[i] = C(k, i) * (1/2^k) % MO
        // 计算恰好发生 i 次变化的概率（二项分布 B(k, 0.5)）
        p[i] = cal(k, i) * inv2k % MO;
        
        // p[31] 用于累积计算 "操作次数 >= 31" 的概率
        // 累加 (MO - p[i]) 相当于减去 p[i]
        p[31] = (p[31] + MO - p[i]) % MO;
    }
    // p[31] 目前是 -sum(p[0]...p[30])，加上 1 得到 1 - sum(...)，即 P(次数 >= 31)
    p[31] = (1 + p[31]) % MO;
    
    // 处理数组中的每个元素
    for (ll i = 1; i <= n; i++) {
        ll x;
        rd(x); // 读入当前元素 x
        // 遍历可能的有效操作次数 j (0 到 30 次，以及 31 代表 >=31 次)
        for (ll j = 0; j <= 31; j++) {
            // 累加期望贡献：当前值 x * 概率 p[j]
            // 注意：x 可能很大，先取模再乘，防止 long long 溢出
            ans = (ans + (x % MO) * p[j]) % MO;
            
            // 模拟一次操作：如果硬币为正，x 变为 x + (x & m)
            // 这里的 x 必须保持真实值（不取模），因为 (x & m) 依赖真实比特位
            x += x & m;
        }
    }
    
    // 输出最终答案
    cout << ans << endl;
}

int main() {
    // 执行 solve 函数，T 默认为 1
    while (T--) solve();
    return 0;
}
