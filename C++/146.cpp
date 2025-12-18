#include <iostream> // 包含输入输出流头文件
#include <vector> // 包含向量容器头文件
#include <unordered_map> // 包含无序映射容器头文件

using namespace std; // 使用标准命名空间

int main() { // 主函数入口
    int n; // 定义变量n用于存储数组长度
    if (!(cin >> n)) return 0; // 读取数组长度，如果读取失败则退出程序

    unordered_map<int, int> countMap; // 定义哈希表用于存储特征值出现的次数
    long long ans = 0; // 定义变量ans用于存储谐距下标对的数量，使用long long防止溢出

    for (int i = 1; i <= n; ++i) { // 循环遍历输入的每个整数，下标从1开始
        int val; // 定义变量val用于存储当前输入的整数
        cin >> val; // 读取当前整数
        
        int diff = val - i; // 计算当前元素的特征值：数值减去下标
        
        // 如果之前出现过相同的特征值，则这些之前的元素都可以与当前元素构成谐距下标对
        // 因此将该特征值之前的出现次数累加到结果中
        ans += countMap[diff]; // 累加符合条件的对数
        
        countMap[diff]++; // 更新当前特征值的出现次数，将其加1
    } // 结束循环

    cout << ans << endl; // 输出最终计算得到的谐距下标对数量

    return 0; // 程序正常结束
} // 主函数结束
