#include <iostream> // 引入标准输入输出流库

using namespace std; // 使用标准命名空间std

// 判断一个数字是否包含数字7
bool hasSeven(int num) { // 定义函数hasSeven，参数为整数num
    while (num > 0) { // 当num大于0时循环
        if (num % 10 == 7) { // 如果num的个位数字是7
            return true; // 返回true，表示包含7
        } // 结束if块
        num /= 10; // num除以10，去掉个位数字
    } // 结束while循环
    return false; // 如果循环结束仍未发现7，返回false
} // 结束函数hasSeven

int main() { // 主函数入口
    int n; // 定义整型变量n，用于存储输入的整数
    while (cin >> n) { // 循环读取输入，直到输入结束
        int count = 0; // 定义计数器count，初始化为0
        for (int i = 1; i <= n; ++i) { // 从1遍历到n
            if (i % 7 == 0 || hasSeven(i)) { // 如果i是7的倍数或者i包含数字7
                count++; // 计数器加1
            } // 结束if块
        } // 结束for循环
        cout << count << endl; // 输出统计结果并换行
    } // 结束while循环
    return 0; // 程序正常结束返回0
} // 结束main函数
