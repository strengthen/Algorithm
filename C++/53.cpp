#include <iostream> // 引入输入输出流库
using namespace std; // 使用标准命名空间

int main() { // 主函数入口
    long long n; // 定义一个长整型变量n，用于存储输入的行数
    while (cin >> n) { // 循环读取输入，直到没有输入为止
        if (n <= 2) { // 判断n是否小于等于2
            cout << -1 << endl; // 如果是前两行，没有偶数，输出-1
        } else if (n % 2 == 1) { // 判断n是否为奇数
            cout << 2 << endl; // 如果是奇数行，第一个偶数出现在第2位
        } else if (n % 4 == 0) { // 判断n是否能被4整除
            cout << 3 << endl; // 如果能被4整除，第一个偶数出现在第3位
        } else { // 剩下的情况，即n是偶数但不能被4整除（余数为2）
            cout << 4 << endl; // 此时第一个偶数出现在第4位
        }
    }
    return 0; // 程序执行完毕，返回0
}
