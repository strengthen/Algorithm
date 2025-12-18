#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <vector>   // 引入向量容器库，用于存储动态数组
#include <algorithm> // 引入算法库，用于使用sort排序函数

using namespace std; // 使用标准命名空间，避免每次调用标准库函数时都要加std::

// 主函数，程序的入口
int main() {
    int n, k; // 定义两个整型变量，n表示输入的整数个数，k表示需要输出的最小整数个数
    
    // 使用while循环读取输入，以支持多组测试数据（如果题目有此要求），或者是单组数据的标准读取方式
    // cin >> n >> k 会尝试读取两个整数，如果读取成功则返回true，否则（如遇到文件结束符）返回false
    while (cin >> n >> k) {
        vector<int> nums(n); // 创建一个大小为n的整型向量nums，用于存储输入的n个整数
        
        // 使用for循环读取n个整数
        for (int i = 0; i < n; ++i) {
            cin >> nums[i]; // 从标准输入读取第i个整数，并存储到向量nums的第i个位置
        }
        
        // 使用标准库的sort函数对向量nums进行升序排序
        // nums.begin()是指向向量第一个元素的迭代器
        // nums.end()是指向向量最后一个元素之后位置的迭代器
        sort(nums.begin(), nums.end());
        
        // 输出排序后最小的k个整数
        // 因为已经进行了升序排序，所以前k个元素即为最小的k个元素
        for (int i = 0; i < k; ++i) {
            cout << nums[i]; // 输出当前的整数
            
            // 为了格式美观，在数字之间输出空格
            // 如果不是最后一个要输出的数字，就在后面加一个空格
            if (i != k - 1) {
                cout << " "; 
            }
        }
        
        cout << endl; // 输出完k个数字后，输出一个换行符，以便下一组输出或程序结束
    }
    
    return 0; // 返回0，表示程序正常执行结束
}
