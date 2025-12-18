#include <iostream> // 引入输入输出流库，用于处理输入输出
#include <vector>   // 引入向量库，用于存储动态数组
#include <algorithm> // 引入算法库，用于使用排序函数sort
#include <functional> // 引入功能库，用于使用greater<int>()

using namespace std; // 使用标准命名空间std，避免每次都写std::

int main() { // 主函数入口
    int n; // 定义整型变量n，用于存储数组元素的个数
    // 使用while循环处理多组输入的情况，虽然题目可能只是一组，但在OJ中通常需要考虑多组输入
    while (cin >> n) { // 读取数组元素个数n，如果读取失败（如文件结束）则退出循环
        vector<int> nums(n); // 定义一个大小为n的整型向量nums，用于存储输入的整数
        for (int i = 0; i < n; ++i) { // 循环n次，读取数组中的每个元素
            cin >> nums[i]; // 读取第i个元素并存入向量
        }
        
        int op; // 定义整型变量op，用于存储排序方式
        cin >> op; // 读取排序方式op，0表示升序，1表示降序
        
        if (op == 0) { // 如果op为0，表示需要升序排序
            sort(nums.begin(), nums.end()); // 使用sort函数对nums进行升序排序（默认是升序）
        } else if (op == 1) { // 如果op为1，表示需要降序排序
            sort(nums.begin(), nums.end(), greater<int>()); // 使用sort函数配合greater<int>()对nums进行降序排序
        }
        
        for (int i = 0; i < n; ++i) { // 循环遍历排序后的向量，输出结果
            cout << nums[i]; // 输出当前元素
            if (i < n - 1) { // 如果不是最后一个元素
                cout << " "; // 输出一个空格作为分隔符
            }
        }
        cout << endl; // 输出换行符，结束当前测试用例的输出
    }
    return 0; // 返回0，表示程序正常结束
}
