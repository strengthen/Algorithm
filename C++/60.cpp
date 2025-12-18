#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <cmath>    // 引入数学库，主要用于使用sqrt函数计算平方根

using namespace std; // 使用标准命名空间，避免每次调用标准库函数时都需要加std::前缀

// 定义一个函数，用于判断一个整数是否为素数
bool isPrime(int num) {
    if (num <= 1) return false; // 如果数字小于等于1，它不是素数，直接返回false
    // 遍历从2到num的平方根的所有整数作为可能的因子
    for (int i = 2; i <= sqrt(num); ++i) { 
        if (num % i == 0) return false; // 如果num能被i整除，说明它不是素数，返回false
    }
    return true; // 如果循环结束后没有找到任何因子，说明它是素数，返回true
}

int main() { // 主函数，程序执行的入口点
    int n; // 定义一个整型变量n，用于存储输入的偶数
    
    // 尝试从标准输入读取一个整数到n中
    if (cin >> n) { 
        // 题目要求找到两个素数a和b，使得a+b=n且|a-b|最小
        // 为了使差值最小，这两个素数应该尽可能接近n/2
        // 所以我们从n/2开始向下遍历寻找第一个素数a
        for (int i = n / 2; i >= 2; --i) { // 初始化i为n的一半，每次循环减1，直到2
            if (isPrime(i)) { // 调用isPrime函数判断当前的i是否为素数
                int j = n - i; // 计算与i配对的另一个数j，使得i+j=n
                if (isPrime(j)) { // 再次调用isPrime函数判断j是否也为素数
                    cout << i << endl; // 如果i和j都是素数，输出较小的素数i
                    cout << j << endl; // 输出较大的素数j（因为i是从n/2开始递减的，所以i <= j）
                    break; // 找到第一对满足条件的素数对后，它们的差值一定是最小的，跳出循环
                }
            }
        }
    }
    
    return 0; // 程序正常结束，返回0
}
