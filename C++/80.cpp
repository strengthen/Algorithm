#include <iostream> // 引入输入输出流库
#include <set>      // 引入set容器库，用于自动排序和去重
#include <algorithm> // 引入算法库

using namespace std; // 使用标准命名空间

int main() { // 主函数入口
    int n, m; // 定义变量n和m，分别用于存储两个数组的长度
    
    // 循环读取第一个数组的长度n，处理多组输入的情况
    while (cin >> n) {
        set<int> result_set; // 定义一个int类型的set容器，set会自动对插入的元素进行排序和去重
        int temp; // 定义临时变量用于存储读取的数组元素
        
        // 循环n次，读取第一个数组的元素
        for (int i = 0; i < n; ++i) {
            cin >> temp; // 从标准输入读取一个整数
            result_set.insert(temp); // 将读取的整数插入到set中
        }
        
        // 读取第二个数组的长度m
        cin >> m;
        
        // 循环m次，读取第二个数组的元素
        for (int i = 0; i < m; ++i) {
            cin >> temp; // 从标准输入读取一个整数
            result_set.insert(temp); // 将读取的整数插入到set中
        }
        
        // 遍历set容器，输出合并、排序且去重后的结果
        for (auto it = result_set.begin(); it != result_set.end(); ++it) {
            cout << *it; // 输出当前元素，题目要求元素间不需要输出空格
        }
        
        cout << endl; // 输出完一组结果后换行
    }
    
    return 0; // 程序正常结束
}
