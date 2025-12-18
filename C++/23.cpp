#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于处理字符串
#include <map>      // 引入map容器库，用于存储字符及其出现次数
#include <climits>  // 引入climits库，用于使用INT_MAX常量

using namespace std; // 使用标准命名空间std，避免每次调用标准库时都需要加std::前缀

int main() { // 主函数，程序的入口
    string str; // 定义一个字符串变量str，用于存储输入的字符串
    while (cin >> str) { // 循环读取标准输入中的字符串，直到读取结束
        map<char, int> countMap; // 定义一个map容器countMap，键为字符char，值为整数int，用于统计字符频次
        
        for (char c : str) { // 使用范围for循环遍历输入字符串中的每一个字符
            countMap[c]++; // 将当前字符c在map中的计数加1
        }

        int minCount = INT_MAX; // 定义变量minCount存储最小出现次数，初始化为整型最大值
        for (auto it = countMap.begin(); it != countMap.end(); ++it) { // 遍历map容器中的所有元素
            if (it->second < minCount) { // 如果当前字符的出现次数小于当前的最小次数
                minCount = it->second; // 更新最小次数minCount为当前字符的出现次数
            }
        }

        for (char c : str) { // 再次遍历原字符串中的每一个字符，保持原顺序
            if (countMap[c] > minCount) { // 检查当前字符的出现次数是否大于最小出现次数
                cout << c; // 如果大于最小次数，说明不是出现次数最少的字符，输出该字符
            }
        }
        cout << endl; // 处理完一个字符串后，输出一个换行符
    }
    return 0; // 返回0，表示程序正常执行结束
}

