#include <iostream> // 引入输入输出流库
#include <string>   // 引入字符串库
#include <vector>   // 引入向量库
#include <algorithm> // 引入算法库，用于排序
#include <map>      // 引入映射库

using namespace std; // 使用标准命名空间

// 自定义比较函数，用于指定排序规则
bool cmp(const pair<char, int>& a, const pair<char, int>& b) {
    if (a.second != b.second) { // 如果出现次数不同
        return a.second > b.second; // 按照出现次数从多到少排序（降序）
    }
    return a.first < b.first; // 如果出现次数相同，按照ASCII码由小到大排序（升序）
}

int main() {
    string s; // 定义字符串变量用于存储输入
    while (cin >> s) { // 循环读取输入字符串，直到输入结束
        map<char, int> counts; // 定义map用于统计每个字符出现的次数
        for (char c : s) { // 遍历输入字符串中的每一个字符
            counts[c]++; // 将当前字符的计数加1
        }

        vector<pair<char, int>> vec; // 定义vector用于存储字符及其出现次数，以便排序
        for (auto it = counts.begin(); it != counts.end(); ++it) { // 遍历map中的所有元素
            vec.push_back(*it); // 将字符和次数对存入vector中
        }

        sort(vec.begin(), vec.end(), cmp); // 使用自定义的比较函数对vector进行排序

        for (auto it = vec.begin(); it != vec.end(); ++it) { // 遍历排序后的vector
            cout << it->first; // 输出字符
        }
        cout << endl; // 输出换行符，结束当前行的输出
    }
    return 0; // 程序正常结束
}
