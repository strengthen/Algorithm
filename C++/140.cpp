#include <iostream>
#include <cmath>

using namespace std;

// 判断一个数是否为合数
// 合数定义：大于1的整数，且不是质数（即除了1和它本身外还有其他因数）
bool isComposite(int n) {
    // 小于等于3的数都不是合数（1不是质数也不是合数，2和3是质数）
    if (n <= 3) return false;
    
    // 如果是偶数（大于2），则是合数
    if (n % 2 == 0) return true;
    
    // 检查是否有大于1的奇数因子
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return true; // 找到了因子，是合数
        }
    }
    
    // 没有找到因子，是质数
    return false;
}

int main() {
    int x;
    // 读取输入
    while (cin >> x) {
        bool found = false;
        // 在区间 [x, 2*x] 内寻找合数
        for (int i = x; i <= 2 * x; ++i) {
            if (isComposite(i)) {
                cout << i << endl; // 输出找到的合数
                found = true;
                break; // 题目只需要输出任意一个，找到后即可退出
            }
        }
        
        // 如果没有找到符合条件的合数，输出 -1
        if (!found) {
            cout << -1 << endl;
        }
    }
    return 0;
}
