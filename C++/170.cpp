#include <iostream> // 引入输入输出流库
#include <vector>   // 引入向量容器库

using namespace std; // 使用标准命名空间

int main() { // 主函数入口
    int m; // 定义变量m，用于存储数组长度
    if (cin >> m) { // 读取数组长度m
        vector<int> matrix(m); // 定义一个大小为m的整型向量matrix
        for (int i = 0; i < m; ++i) { // 循环读取数组元素
            cin >> matrix[i]; // 读取第i个元素
        } // 循环结束

        int n; // 定义变量n，表示需要填入1的个数
        cin >> n; // 读取n的值

        int count = 0; // 定义计数器count，记录能填入1的最大数量
        for (int i = 0; i < m; ++i) { // 遍历数组的每一个位置
            if (matrix[i] == 1) { // 如果当前位置已经是1
                continue; // 跳过当前循环，继续下一个位置
            } // 条件判断结束

            // 判断左边是否允许填1（是第一个元素或者左边元素为0）
            bool left_ok = (i == 0 || matrix[i - 1] == 0); 
            // 判断右边是否允许填1（是最后一个元素或者右边元素为0）
            bool right_ok = (i == m - 1 || matrix[i + 1] == 0); 

            if (left_ok && right_ok) { // 如果左右两边都允许
                matrix[i] = 1; // 将当前位置设置为1（贪心策略）
                count++; // 增加能填入1的计数
            } // 条件判断结束
        } // 遍历结束

        if (count >= n) { // 如果能填入的数量满足或超过要求的n
            cout << "true" << endl; // 输出true
        } else { // 否则
            cout << "false" << endl; // 输出false
        } // 条件判断结束
    } // 输入判断结束
    return 0; // 程序正常结束
} // 主函数结束
