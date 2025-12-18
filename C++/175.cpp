#include <iostream> // 引入输入输出流库
#include <vector> // 引入向量容器库
#include <algorithm> // 引入算法库，用于排序

using namespace std; // 使用标准命名空间

int main() { // 主函数入口
    int n, k; // 定义整数变量n和k，分别表示数组长度和差值限制
    if (!(cin >> n >> k)) return 0; // 输入n和k，如果输入失败则退出
    
    vector<int> a(n); // 定义一个大小为n的整数向量a
    for (int i = 0; i < n; ++i) { // 循环读取数组元素
        cin >> a[i]; // 输入每个整数
    } // 循环结束
    
    sort(a.begin(), a.end(), greater<int>()); // 将数组从大到小排序
    
    long long max_score = 0; // 定义长整型变量max_score用于存储最大得分，初始化为0
    for (int i = 0; i < n - 1; ++i) { // 遍历数组，尝试配对相邻元素
        if (a[i] - a[i+1] <= k) { // 如果当前元素与下一个元素的差值小于等于k
            max_score += (long long)a[i] * a[i+1]; // 将两个数的乘积累加到总分中，注意强制转换为long long防止溢出
            i++; // 跳过下一个元素，因为已经配对使用了
        } // 条件判断结束
    } // 循环结束
    
    cout << max_score << endl; // 输出计算得到的最大得分
    
    return 0; // 程序正常结束
} // 主函数结束
