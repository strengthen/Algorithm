#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <algorithm> // 引入算法库，用于使用 max 和 min 函数

using namespace std; // 使用标准命名空间，避免每次调用标准库函数时都需要加 std::

int main() { // 主函数，程序的入口点
    int a, b; // 声明两个整型变量 a 和 b，用于存储输入的两个整数
    
    // 从标准输入读取两个整数 a 和 b
    if (cin >> a >> b) { // 使用 cin 读取输入，并检查读取是否成功
        // 计算 a 和 b 中的最大值
        int max_val = max(a, b); // 使用 max 函数获取两数中的较大值
        
        // 计算 a 和 b 中的最小值
        int min_val = min(a, b); // 使用 min 函数获取两数中的较小值
        
        // 计算公差，即最大值减去最小值
        int diff = max_val - min_val; // 等差数列的公差可以是两数之差的绝对值
        
        // 计算第三个整数 c，使得 min_val, max_val, c 构成等差数列
        // 这里的 c 是数列中的下一项，即最大值加上公差
        int c = max_val + diff; // c = max_val + (max_val - min_val) = 2 * max_val - min_val
        
        // 将计算得到的第三个整数 c 输出到标准输出
        cout << c << endl; // 输出 c 并换行
    }
    
    return 0; // 程序正常结束，返回 0
}

