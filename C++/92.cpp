#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于使用string类型
#include <vector>   // 引入向量容器库，用于存储多个结果子串
#include <cctype>   // 引入字符处理库，包含isdigit等函数

using namespace std; // 使用标准命名空间std，避免每次调用标准库需加std::前缀

int main() { // 主函数入口
    string str; // 定义一个字符串变量str，用于存储输入的字符串
    while (cin >> str) { // 循环读取输入，直到没有更多输入为止（处理多组测试用例）
        vector<string> max_strs; // 定义一个字符串向量，用于存储当前找到的最长数字子串
        int max_len = 0; // 定义整型变量，记录目前找到的最长数字子串的长度，初始化为0
        int current_len = 0; // 定义整型变量，记录当前正在遍历的连续数字子串的长度，初始化为0
        int len = str.length(); // 获取字符串的长度

        for (int i = 0; i <= len; ++i) { // 遍历字符串中的每一个字符，循环条件包含len是为了处理字符串末尾是数字的情况
             if (i < len && isdigit(str[i])) { // 如果当前索引在字符串范围内且当前字符是数字
                 current_len++; // 当前连续数字长度加1
             } else { // 如果当前字符不是数字，或者已经遍历到字符串末尾
                 if (current_len >= 1) { // 如果刚才结束的一段是数字子串（长度至少为1）
                     if (current_len > max_len) { // 如果当前数字子串的长度大于之前记录的最长长度
                         max_len = current_len; // 更新最长长度为当前长度
                         max_strs.clear(); // 清空之前存储的最长子串列表，因为找到了更长的
                         max_strs.push_back(str.substr(i - current_len, current_len)); // 将当前子串截取并保存到列表中
                     } else if (current_len == max_len) { // 如果当前数字子串的长度等于之前记录的最长长度
                         max_strs.push_back(str.substr(i - current_len, current_len)); // 将当前子串也添加到最长子串列表中
                     }
                     current_len = 0; // 重置当前连续数字长度为0，为下一次计数做准备
                 }
             }
        }
        
        for (const string& s : max_strs) { // 遍历保存的所有最长数字子串
            cout << s; // 输出当前的数字子串
        }
        cout << "," << max_len << endl; // 输出逗号和最长长度，然后换行
    }
    return 0; // 程序执行成功，返回0
}
