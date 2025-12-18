#include <iostream> // 引入输入输出流库
#include <cmath>    // 引入数学库，用于sqrt和ceil函数
#include <algorithm> // 引入算法库，用于min等函数（虽然这里手动比较了）

using namespace std; // 使用标准命名空间

// 解决单组测试数据的函数
void solve() {
    long long n, m; // 定义长整型变量n和m，分别存储初始数字和操作次数
    // 读取输入数据，如果读取失败直接返回
    if (!(cin >> n >> m)) return;

    // 当操作次数大于0且当前数字n大于0时循环
    while (m > 0 && n > 0) {
        long long next_n = n - 1; // 初始化下一步的数字为n-1（操作2：减1）

        // 计算操作1：开根号并向上取整
        // sqrt函数计算平方根，ceil函数向上取整，结果转为long long
        long long sqrt_n = (long long)ceil(sqrt((double)n));
        
        // 如果开根号的结果比当前最小值还小，则更新下一步的数字
        if (sqrt_n < next_n) {
            next_n = sqrt_n; // 更新下一步数字为开根号的结果
        }

        // 计算操作3：除以2并向上取整
        // (n + 1) / 2 是整数运算中实现向上取整的常用技巧
        long long div2_n = (n + 1) / 2;
        
        // 如果除以2的结果比当前最小值还小，则更新下一步的数字
        if (div2_n < next_n) {
            next_n = div2_n; // 更新下一步数字为除以2的结果
        }

        n = next_n; // 将n更新为三种操作中结果最小的那个
        m--;        // 操作次数减1
    }

    // 循环结束后，如果还有剩余操作次数（此时n必然为0）
    // 说明我们可以继续对0进行减1操作（因为题目暗示非负整数才开根号，负数只能减1）
    if (m > 0) {
        n -= m; // 直接减去剩余的操作次数，即 n = 0 - m
    }

    // 输出最终计算得到的最小数字，并换行
    cout << n << endl;
}

int main() {
    // 关闭stdio同步，提高cin/cout的I/O效率
    ios_base::sync_with_stdio(false);
    // 解除cin和cout的绑定，进一步提高效率
    cin.tie(NULL);

    int t; // 定义变量t，用于存储测试数据的组数
    // 读取测试组数
    if (cin >> t) {
        // 循环处理每一组测试数据
        while (t--) {
            solve(); // 调用求解函数
        }
    }
    return 0; // 程序正常结束
}
