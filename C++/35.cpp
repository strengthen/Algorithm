#include <iostream> // 引入输入输出流库

using namespace std; // 使用标准命名空间

int main() {
    int n; // 定义变量n用于存储输入的矩阵大小
    // 循环读取输入，处理可能的测试用例
    while (cin >> n) {
        // 外层循环控制行数，从第1行到第n行
        for (int i = 1; i <= n; ++i) {
            // 计算当前行的第一个元素
            // 规律：第i行第一个元素 = 1 + (i-1)*i/2
            int current = 1 + (i - 1) * i / 2;
            
            // 输出当前行的第一个元素
            cout << current;
            
            // 内层循环控制列数，输出该行剩余的元素
            // 第i行有 n-i+1 个元素，这里从第2个元素开始处理
            for (int j = 2; j <= n - i + 1; ++j) {
                // 计算下一个元素的值
                // 规律：当前行第j个元素 = 前一个元素 + (i + j - 1)
                // 其中 (i + j - 1) 是两个相邻元素之间的差值
                current += (i + j - 1);
                
                // 输出空格和当前元素
                cout << " " << current;
            }
            // 每行输出结束后换行
            cout << endl;
        }
    }
    return 0; // 程序正常结束
}

