#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <bitset>   // 引入bitset库，用于处理二进制位操作

using namespace std; // 使用标准命名空间，避免每次调用标准库函数时都需要加std::前缀

int main() { // 主函数，程序的入口点
    int n; // 定义一个整型变量n，用于存储输入的整数

    // 使用while循环从标准输入读取整数
    // 虽然题目描述只提到了n和m两个数，但使用while(cin >> n)可以处理任意数量的输入，包括题目要求的两行输入
    while (cin >> n) { // 当能够成功读取一个整数到n时，执行循环体
        // bitset<32>是一个模板类，用于表示32位的二进制序列
        // 将整数n作为参数传递给构造函数，自动转换为二进制表示
        bitset<32> binary_n(n); 

        // count()是bitset的成员函数，返回二进制序列中设置为1的位的数量
        // 直接输出这个数量，即为题目要求的答案
        cout << binary_n.count() << endl; 
    }

    return 0; // 程序正常结束，返回0
}
