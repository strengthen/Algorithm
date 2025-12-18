#include <iostream> // 引入输入输出流库
#include <vector>   // 引入向量容器库
#include <string>   // 引入字符串库
#include <algorithm> // 引入算法库，用于排序

using namespace std; // 使用标准命名空间

// 判断两个字符串是否为兄弟单词的函数
bool isBrother(string s1, string s2) {
    // 如果两个字符串长度不相等，肯定不是兄弟单词
    if (s1.length() != s2.length()) {
        return false; // 返回假
    }
    // 如果两个字符串完全相同，也不是兄弟单词（题目定义）
    if (s1 == s2) {
        return false; // 返回假
    }
    // 对两个字符串分别进行排序
    sort(s1.begin(), s1.end()); // 排序字符串s1
    sort(s2.begin(), s2.end()); // 排序字符串s2
    // 如果排序后的字符串相同，说明字符构成一致，是兄弟单词
    if (s1 == s2) {
        return true; // 返回真
    }
    return false; // 否则返回假
}

int main() {
    int n; // 定义整数n，用于存储字符串的个数
    while (cin >> n) { // 循环读取输入，直到没有更多输入，首先读取字符串个数n
        vector<string> dict; // 定义一个字符串向量，用于存储输入的字典单词
        for (int i = 0; i < n; ++i) { // 循环n次读取n个单词
            string s; // 定义临时字符串变量
            cin >> s; // 读取一个字符串
            dict.push_back(s); // 将读取的字符串加入向量中
        }
        
        string x; // 定义字符串x，表示要查找兄弟单词的目标单词
        cin >> x; // 读取目标单词x
        
        int k; // 定义整数k，表示要输出第k个兄弟单词
        cin >> k; // 读取k的值
        
        vector<string> brothers; // 定义一个向量，用于存储找到的所有兄弟单词
        for (const auto& word : dict) { // 遍历字典中的每一个单词
            if (isBrother(x, word)) { // 判断当前单词是否是x的兄弟单词
                brothers.push_back(word); // 如果是，将其加入兄弟单词列表
            }
        }
        
        // 输出兄弟单词的总数
        cout << brothers.size() << endl; // 打印兄弟单词的数量并换行
        
        // 题目要求按字典序输出第k个兄弟单词
        // 如果兄弟单词数量足够（即大于等于k）
        if (brothers.size() >= k) {
            sort(brothers.begin(), brothers.end()); // 对兄弟单词列表进行字典序排序
            cout << brothers[k - 1] << endl; // 输出排序后的第k个单词（索引为k-1）
        }
    }
    return 0; // 程序正常结束
}
