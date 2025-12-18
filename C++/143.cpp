#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <vector>   // 引入向量库，虽然本题主要用数组，但作为常用库引入

using namespace std; // 使用标准命名空间，避免每次调用std::

const int MOD = 1e9 + 7; // 定义全局常量MOD，表示模数 10^9 + 7
const int MAXN = 1000005; // 定义最大数组大小，稍微超过 10^6 以防越界

long long fact[MAXN]; // 定义全局数组 fact，用于存储阶乘值
long long invFact[MAXN]; // 定义全局数组 invFact，用于存储阶乘的逆元

// 快速幂函数，计算 base 的 exp 次方对 MOD 取模的结果
long long power(long long base, long long exp) {
    long long res = 1; // 初始化结果为 1
    base %= MOD; // 对底数取模，防止溢出
    while (exp > 0) { // 当指数大于 0 时循环
        if (exp % 2 == 1) // 如果指数是奇数
            res = (res * base) % MOD; // 将当前底数乘入结果，并取模
        base = (base * base) % MOD; // 底数自乘，准备下一位
        exp /= 2; // 指数右移一位（除以 2）
    }
    return res; // 返回计算结果
}

// 初始化函数，预处理阶乘和逆元
void init() {
    fact[0] = 1; // 0 的阶乘定义为 1
    invFact[0] = 1; // 0 的阶乘逆元定义为 1
    for (int i = 1; i < MAXN; i++) { // 从 1 循环到 MAXN-1
        fact[i] = (fact[i - 1] * i) % MOD; // 计算 i 的阶乘：(i-1)! * i % MOD
        invFact[i] = power(fact[i], MOD - 2); // 根据费马小定理计算逆元：fact[i]^(MOD-2) % MOD
    }
}

// 计算排列数 A(n, m) = n! / (n-m)!
long long A(int n, int m) {
    if (m < 0 || m > n) // 如果选取个数 m 小于 0 或大于总数 n
        return 0; // 不合法的情况，返回 0
    return (fact[n] * invFact[n - m]) % MOD; // 返回排列数计算结果，注意取模
}

// 计算组合数 C(n, m) = n! / (m! * (n-m)!)
long long C(int n, int m) {
    if (m < 0 || m > n) // 如果选取个数 m 小于 0 或大于总数 n
        return 0; // 不合法的情况，返回 0
    // 组合数公式：n! * inv(m!) * inv((n-m)!) % MOD
    return (((fact[n] * invFact[m]) % MOD) * invFact[n - m]) % MOD; 
}

int main() {
    // 优化 I/O 操作速度，虽非必须但在竞赛中常用
    ios::sync_with_stdio(false); 
    cin.tie(0); 

    init(); // 调用初始化函数，预处理阶乘和逆元

    int n; // 定义整数变量 n，存储排列长度
    if (!(cin >> n)) return 0; // 从标准输入读取 n，读取失败则退出

    // 根据题目要求，我们需要恰好 n/2 个索引 i 使得 a_i * i 是 3 的倍数
    // 这等价于：恰好 n/2 个索引 i 使得 a_i * i 不是 3 的倍数
    // 乘积不是 3 的倍数，意味着 i 和 a_i 都不能是 3 的倍数

    int k = n / 3; // 计算 1 到 n 中 3 的倍数的个数 (k)
    int m = n - k; // 计算 1 到 n 中非 3 的倍数的个数 (m)
    int target = n / 2; // 我们需要凑出的“非 3 倍数乘积”对的数量

    // 如果非 3 倍数的数字总数 m 小于我们需要的目标数量 target
    // 那么无法凑出足够的非 3 倍数乘积，情况不可能发生
    if (m < target) {
        cout << 0 << endl; // 输出 0
        return 0; // 结束程序
    }

    // 计算方案数：
    // 1. 选位置：从 m 个“非 3 倍数下标”中选出 target 个位置
    //    这些位置将用来放置“非 3 倍数值”，使得乘积不是 3 的倍数
    long long ways = C(m, target); // 计算组合数 C(m, target)

    // 2. 填数值：从 m 个“非 3 倍数值”中选出 target 个，填入上述选定的位置
    //    这些数之间有顺序，所以是排列数
    ways = (ways * A(m, target)) % MOD; // 乘上排列数 A(m, target) 并取模

    // 3. 处理剩余的“非 3 倍数下标”：
    //    剩下的 (m - target) 个“非 3 倍数下标”必须填入“3 的倍数值”
    //    否则如果填入非 3 倍数值，会增加“非 3 倍数乘积”的数量，超过 target
    //    我们有 k 个“3 的倍数值”可用
    int rem_indices = m - target; // 剩余需要填充的下标数量
    ways = (ways * A(k, rem_indices)) % MOD; // 乘上排列数 A(k, rem_indices) 并取模

    // 4. 处理剩下的所有位置：
    //    此时剩下的位置全是“3 的倍数下标”（共 k 个）
    //    剩下的数值也有 k 个（包含剩下的非 3 倍数值和剩下的 3 倍数值）
    //    因为下标是 3 的倍数，无论填入什么数，乘积都是 3 的倍数，不影响计数
    //    所以剩下的 k 个数值可以任意排列填入这 k 个位置
    ways = (ways * fact[k]) % MOD; // 乘上 k! 并取模

    cout << ways << endl; // 输出最终计算出的方案数

    return 0; // 程序结束
}
