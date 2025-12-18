#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <vector>   // 引入向量库，用于存储动态数组
#include <algorithm> // 引入算法库，用于使用排序函数 sort

using namespace std; // 使用标准命名空间，避免每次调用标准库函数时都要加 std::

int main() { // 主函数，程序的入口
    int n; // 定义整型变量 n，用于存储数组的长度
    // 优化输入输出效率
    ios_base::sync_with_stdio(false); // 关闭 C++ 标准流与 C 标准流的同步，提高 I/O 速度
    cin.tie(NULL); // 解除 cin 与 cout 的绑定，避免每次输入前都刷新输出缓冲区

    if (cin >> n) { // 从标准输入读取数组长度 n，并判断读取是否成功
        vector<int> a(n); // 定义一个大小为 n 的整型向量 a，用于存储输入的整数
        for (int i = 0; i < n; ++i) { // 循环 n 次，用于读取数组的每一个元素
            cin >> a[i]; // 从标准输入读取第 i 个整数，并存入向量 a 的第 i 个位置
        } // 结束读取循环
        
        sort(a.begin(), a.end()); // 使用标准库的 sort 函数对向量 a 进行升序排序
        
        for (int i = 0; i < n; ++i) { // 循环 n 次，用于输出排序后的数组元素
            cout << a[i]; // 输出当前元素 a[i]
            if (i < n - 1) { // 如果当前元素不是最后一个元素
                cout << " "; // 输出一个空格作为分隔符
            } // 结束条件判断
        } // 结束输出循环
        cout << endl; // 输出换行符，表示一行输出结束
    } // 结束输入判断
    return 0; // 程序正常结束，返回 0
} // 主函数结束
