#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <vector>   // 引入向量容器库，用于存储动态数组
#include <cmath>    // 引入数学库，用于使用abs绝对值函数
#include <algorithm> // 引入算法库，用于使用max函数

using namespace std; // 使用标准命名空间，避免每次调用标准库函数时加std::前缀

int main() { // 主函数入口，程序从这里开始执行
    int n; // 定义一个整型变量n，用于存储数组的长度
    if (!(cin >> n)) return 0; // 从标准输入读取n的值，如果读取失败则退出程序

    if (n == 0) { // 如果数组长度为0
        cout << 0 << endl; // 输出0，表示最长稳定子数组长度为0
        return 0; // 结束程序
    }

    vector<long long> a(n); // 定义一个大小为n的长整型向量a，用于存储数组元素，使用long long防止溢出
    for (int i = 0; i < n; i++) { // 循环n次，读取数组的每一个元素
        cin >> a[i]; // 将输入的整数读入向量a的第i个位置
    }

    int max_len = 1; // 定义变量max_len记录最长稳定子数组的长度，初始化为1
    int current_len = 1; // 定义变量current_len记录当前连续稳定子数组的长度，初始化为1

    for (int i = 1; i < n; i++) { // 从数组的第二个元素开始遍历（下标为1）
        if (abs(a[i] - a[i - 1]) <= 1) { // 判断当前元素与前一个元素的差的绝对值是否小于等于1
            current_len++; // 如果满足条件，说明当前稳定子数组延续，长度加1
        } else { // 如果不满足条件，说明当前稳定子数组中断
            if (current_len > max_len) { // 检查当前累积的长度是否大于已知的最大长度
                max_len = current_len; // 如果是，更新最大长度
            }
            current_len = 1; // 重置当前长度为1，从当前元素开始新的计数
        }
    }

    if (current_len > max_len) { // 遍历结束后，再次检查最后一段子数组的长度是否是最大的
        max_len = current_len; // 如果是，更新最大长度
    }

    cout << max_len << endl; // 输出最终计算得到的最长稳定子数组的长度
    return 0; // 返回0，表示程序成功执行完毕
}
