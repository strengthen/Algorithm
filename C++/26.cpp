#include <iostream> // 包含输入输出流库
#include <string>   // 包含字符串处理库
#include <vector>   // 包含向量容器库
#include <algorithm> // 包含算法库，用于排序
#include <cctype>   // 包含字符处理库，用于判断字母和转换大小写

using namespace std; // 使用标准命名空间

// 自定义比较函数，用于忽略大小写比较两个字符
bool compareIgnoreCase(char a, char b) {
    return tolower(a) < tolower(b); // 将字符转换为小写后进行比较
}

int main() {
    string s; // 定义字符串变量用于存储输入
    // 循环读取每一行输入，直到输入结束
    while (getline(cin, s)) {
        vector<char> letters; // 定义一个字符向量，用于存储字符串中的所有字母
        
        // 第一步：遍历输入字符串，提取所有英文字母
        for (char c : s) { // 范围for循环遍历字符串中的每个字符
            if (isalpha(c)) { // 检查当前字符是否为英文字母
                letters.push_back(c); // 如果是字母，将其添加到向量中
            }
        }

        // 第二步：对提取出的字母进行排序
        // 使用 stable_sort 保证排序的稳定性
        // 题目要求：同一字母的大小写同时存在时，按照输入顺序排列
        // 比如输入 "aA"，排序后仍然是 "aA"，而不是 "Aa"（如果用普通 sort 可能无法保证）
        stable_sort(letters.begin(), letters.end(), compareIgnoreCase);

        // 第三步：将排序后的字母填回原字符串的对应位置
        // 非字母字符的位置保持不变
        int k = 0; // 定义索引 k，指向排序后字母向量的当前位置
        for (int i = 0; i < s.length(); ++i) { // 遍历原字符串的每一个位置
            if (isalpha(s[i])) { // 如果原位置是字母
                s[i] = letters[k]; // 将该位置替换为排序后的当前字母
                k++; // 字母向量索引后移
            }
            // 如果原位置是非字母字符，则不做处理，保持原样
        }

        // 输出最终处理后的字符串
        cout << s << endl; 
    }
    return 0; // 程序正常结束
}

