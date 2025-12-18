#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于处理字符串类
#include <algorithm> // 引入算法库，虽然本题主要用string的方法，但swap包含在这里（C++98）或utility中

using namespace std; // 使用标准命名空间

int main() {
    string str1, str2; // 定义两个字符串变量，分别存储输入的两行字符串

    // 从标准输入读取两个字符串
    // 题目描述第一行是字符串s，第二行是字符串t
    if (cin >> str1 >> str2) {
        // 题目要求：如果存在多个答案，输出在“较短串”中最先出现的那个。
        // 因此，我们首先确定哪个是较短的字符串，将其作为外层循环的基准。
        // 如果str1比str2长，交换它们，使得str1始终是较短的那个（或长度相等时保持原序）。
        if (str1.length() > str2.length()) {
            swap(str1, str2); // 交换str1和str2的内容
        }

        bool found = false; // 定义一个布尔变量，标记是否找到了公共子串

        // 外层循环：枚举子串的长度
        // 我们需要找“最长”的公共子串，所以从较短串的最大长度开始递减枚举
        for (int len = str1.length(); len >= 1; --len) {
            
            // 内层循环：枚举长度为len的子串在str1中的起始位置
            // 我们需要找“最先出现”的，所以下标j从0开始递增
            // j + len <= str1.length() 保证子串不越界
            for (int j = 0; j <= str1.length() - len; ++j) {
                
                // 截取子串：从str1的下标j开始，长度为len
                string sub = str1.substr(j, len);
                
                // 在str2（较长串）中查找截取的子串
                // str2.find(sub) 返回子串第一次出现的位置，如果没找到则返回 string::npos
                if (str2.find(sub) != string::npos) {
                    // 如果找到了，因为是从最长长度开始尝试的，且是从左到右遍历的
                    // 所以这一定是满足条件的“最长”且“在较短串中最先出现”的子串
                    cout << sub << endl; // 输出结果
                    found = true; // 标记已找到
                    break; // 跳出内层循环
                }
            }
            if (found) {
                break; // 如果已经找到最长公共子串，跳出外层循环，结束查找
            }
        }
    }

    return 0; // 程序正常结束
}
