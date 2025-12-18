#include <iostream> // 引入输入输出流标准库，用于控制台输入输出
#include <map>      // 引入Map容器头文件，用于存储键值对，会自动根据键（索引）进行排序

using namespace std; // 使用标准命名空间std，避免每次调用标准库函数时都需要加std::前缀

int main() { // 主程序的入口函数，程序从这里开始执行
    int n; // 声明一个整型变量n，用于存储数据表的记录数
    
    // 使用while循环读取输入，只要还能从标准输入读取到整数n，就继续执行循环
    // 这样做可以处理可能存在的多组测试数据
    while (cin >> n) { 
        map<int, int> record; // 定义一个map容器，键(key)是int类型的索引，值(value)是int类型的数值
        
        // 循环n次，用于读取接下来的n行数据
        for (int i = 0; i < n; ++i) { 
            int index; // 声明一个整型变量index，用于存储每一条记录的索引
            int value; // 声明一个整型变量value，用于存储每一条记录的数值
            
            cin >> index >> value; // 从标准输入读取当前行的两个整数：索引和数值
            
            // 将读取到的数值累加到对应索引的记录中
            // map的特性是：如果key不存在，会自动创建一个并初始化为0，然后加上value
            // 如果key已经存在，则直接在原有值的基础上加上value，实现了"相同索引的数值进行求和"
            record[index] += value; 
        }
        
        // 遍历map容器，输出合并后的结果
        // map容器内部是基于红黑树实现的，遍历时会自动按照键（索引）从小到大的顺序进行
        for (auto it = record.begin(); it != record.end(); ++it) { 
            // 输出当前记录的索引（it->first）和累加后的数值（it->second），中间用空格分隔
            cout << it->first << " " << it->second << endl; 
        }
    }
    
    return 0; // 主函数返回0，表示程序正常执行结束
}

