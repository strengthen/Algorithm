#include <iostream> // 引入输入输出流头文件，用于控制台输入输出
#include <algorithm> // 引入算法头文件，用于使用min函数

using namespace std; // 使用标准命名空间，以便直接使用cin、cout等

int main() { // 主函数，程序的执行入口
    long long min_val; // 定义一个长整型变量min_val，用于存储最小的糖果数量
    long long temp; // 定义一个长整型变量temp，用于临时存储输入的糖果数量
    
    // 读取第一个糖果数量作为初始的最小值
    if (cin >> min_val) { // 尝试从标准输入读取第一个数，并存储在min_val中
        for (int i = 1; i < 7; ++i) { // 循环读取剩余的6个数（总共7种颜色）
            cin >> temp; // 从标准输入读取下一个颜色的糖果数量
            if (temp < min_val) { // 检查当前读取的数量是否小于当前的最小值
                min_val = temp; // 如果当前数量更小，则更新最小值为当前数量
            } // 结束if判断
        } // 结束for循环
    } // 结束if判断

    cout << min_val << endl; // 将计算出的最小值（即最多能分给的小朋友数）输出到控制台

    return 0; // 返回0，表示程序正常执行结束
}
