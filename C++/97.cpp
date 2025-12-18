#include <iostream> // 引入输入输出流标准库
#include <iomanip>  // 引入输入输出控制符库，用于设置输出精度
#include <vector>   // 引入向量容器库（虽然本题可以直接处理，但为了通用性也可以包含）

using namespace std; // 使用标准命名空间std，避免每次调用标准库函数时加std::前缀

int main() { // 主函数入口
    int n; // 声明一个整型变量n，用于存储输入的整数个数
    while (cin >> n) { // 循环读取输入n，直到输入结束，适用于多组测试用例的情况
        int negative_count = 0; // 声明并初始化负数计数器为0
        int positive_count = 0; // 声明并初始化正数计数器为0
        double positive_sum = 0.0; // 声明并初始化正数累加和为0.0，使用double防止溢出并用于计算平均值

        for (int i = 0; i < n; ++i) { // 循环n次，读取每一个整数
            int val; // 声明一个整型变量val，用于存储当前输入的整数
            cin >> val; // 从标准输入读取一个整数赋值给val

            if (val < 0) { // 判断当前整数是否小于0
                negative_count++; // 如果是负数，负数计数器加1
            } else if (val > 0) { // 判断当前整数是否大于0
                positive_sum += val; // 如果是正数，将其值累加到positive_sum中
                positive_count++; // 同时正数计数器加1
            }
            // 如果是0，既不是正数也不是负数，不做处理
        } // 循环结束

        cout << negative_count << " "; // 输出负数的个数，并在后面跟一个空格

        if (positive_count == 0) { // 判断是否没有正数
            cout << "0.0" << endl; // 如果没有正数，平均值为0.0，直接输出并换行
        } else { // 如果有正数
            // 输出正数的平均值，使用fixed和setprecision(1)保留一位小数
            cout << fixed << setprecision(11) << (positive_sum / positive_count) << endl; // 计算平均值并输出，最后换行
        }
    } // while循环结束
    return 0; // 主函数返回0，表示程序正常退出
} // main函数结束
