#include <iostream> // 引入输入输出流库
using namespace std; // 使用标准命名空间

int main() { // 主函数入口
    long long n, k, x; // 定义长整型变量n, k, x，用于存储输入
    if (cin >> n >> k >> x) { // 从标准输入读取n, k, x，并检查读取是否成功
        long long q = k / x; // 计算区间长度k中至少包含的x的倍数个数，即商
        if (n == q) { // 如果需要的倍数个数n等于最小倍数个数q
            cout << 1 << " " << k << endl; // 输出区间[1, k]，这个区间恰好包含q个x的倍数
        } else if (n == q + 1 && k % x != 0) { // 如果需要的倍数个数n等于q+1，且k不是x的倍数（存在余数）
            // 构造区间[l, r]，使得右端点r是第n个x的倍数
            // r = n * x
            // l = r - k + 1
            cout << (n * x - k + 1) << " " << (n * x) << endl; // 输出计算得到的l和r
        } else { // 其他情况（n既不是q也不是q+1，或者n是q+1但k是x的倍数无法达成）
            cout << -1 << endl; // 此时无解，输出-1
        }
    }
    return 0; // 程序正常结束
}
