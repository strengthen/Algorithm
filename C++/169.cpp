#include <iostream> // 引入输入输出流头文件
#include <algorithm> // 引入算法库头文件
#include <climits> // 引入climits头文件以使用INT_MAX

using namespace std; // 使用标准命名空间

int main() { // 主函数开始
    int n; // 声明一个整型变量n，用于存储输入的数字个数
    if (!(cin >> n)) return 0; // 从标准输入读取n的值，如果读取失败则退出

    long long total_sum = 0; // 声明一个长整型变量total_sum，用于存储所有数字的和，初始化为0
    int min_odd = INT_MAX; // 声明一个整型变量min_odd，用于存储最小的奇数，初始化为最大整数

    for (int i = 0; i < n; ++i) { // 开始一个循环，从0遍历到n-1
        int num; // 声明一个整型变量num，用于存储当前输入的数字
        cin >> num; // 从标准输入读取当前数字
        total_sum += num; // 将读取的数字累加到total_sum中

        if (num % 2 != 0) { // 判断当前数字是否为奇数
            if (num < min_odd) { // 如果当前奇数小于已记录的最小奇数
                min_odd = num; // 更新最小奇数为当前数字
            }
        }
    }

    if (total_sum % 2 == 0) { // 判断总和是否为偶数
        cout << total_sum << endl; // 如果是偶数，直接输出总和
    } else { // 如果总和是奇数
        cout << total_sum - min_odd << endl; // 减去最小的奇数使结果变为最大的偶数并输出
    }

    return 0; // 返回0，表示程序正常结束
}
