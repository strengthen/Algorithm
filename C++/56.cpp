#include <iostream>
#include <cmath>

using namespace std;

/**
 * 判断一个数是否为完全数
 * 完全数：所有的真因子（即除了自身以外的约数）之和恰好等于它本身
 */
bool isPerfect(int n) {
    // 1 不是完全数，因为它的真因子和为 0
    if (n <= 1) return false;

    // 初始化因子和为 1，因为 1 是所有正整数（>1）的真因子
    int sum = 1;

    // 只需要遍历到 sqrt(n) 即可找到所有因子
    // 这样做的时间复杂度是 O(sqrt(n))
    for (int i = 2; i * i <= n; ++i) {
        // 如果 i 能整除 n，说明 i 是 n 的因子
        if (n % i == 0) {
            sum += i; // 加上因子 i
            // 如果 i 不等于 n/i，说明还有另一个不同的因子 n/i
            // 比如 28 的因子 2，对应的就是 14 (2 * 14 = 28)
            if (i * i != n) {
                sum += n / i; // 加上成对的另一个因子
            }
        }
    }

    // 判断真因子之和是否等于原数
    return sum == n;
}

int main() {
    int n;
    // 循环读取输入，处理可能的多组测试数据
    // 输入一个整数 n (1 <= n <= 500000)
    while (cin >> n) {
        int count = 0; // 用于统计完全数的个数
        
        // 遍历从 1 到 n 的所有整数
        for (int i = 1; i <= n; ++i) {
            // 如果当前数 i 是完全数
            if (isPerfect(i)) {
                count++; // 计数器加 1
            }
        }
        
        // 输出区间 [1, n] 内完全数的总个数
        cout << count << endl;
    }
    return 0;
}
