#include <iostream> // 包含输入输出流库
#include <vector>   // 包含向量容器库
#include <algorithm> // 包含算法库，用于排序

using namespace std; // 使用标准命名空间

int main() {
    int n, k; // 定义变量n和k，分别表示数组长度和最大允许差值
    if (cin >> n >> k) { // 从标准输入读取n和k，如果读取成功则继续
        vector<int> a(n); // 创建一个大小为n的整数向量a
        for (int i = 0; i < n; ++i) { // 循环读取n个整数
            cin >> a[i]; // 将输入的整数存入向量a中
        }

        sort(a.begin(), a.end()); // 对向量a进行升序排序

        int max_count = 0; // 初始化最大元素个数为0
        int left = 0; // 初始化滑动窗口的左边界为0
        
        // 使用滑动窗口遍历数组
        for (int right = 0; right < n; ++right) { // 右边界从0开始向右移动
            // 如果当前窗口内的最大差值（a[right] - a[left]）超过了k
            while (a[right] - a[left] > k) { 
                left++; // 左边界向右移动，缩小窗口
            }
            // 更新最大元素个数，当前窗口大小为 right - left + 1
            if (right - left + 1 > max_count) { // 如果当前窗口大小大于最大计数
                max_count = right - left + 1; // 更新最大计数
            }
        }

        cout << max_count << endl; // 输出满足条件的最多可选元素数量
    }
    return 0; // 程序正常结束
}
