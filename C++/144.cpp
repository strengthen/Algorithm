#include <iostream> // 包含输入输出流库
#include <string>   // 包含字符串处理库
#include <vector>   // 包含向量容器库
#include <map>      // 包含映射容器库
#include <sstream>  // 包含字符串流库
#include <algorithm> // 包含算法库，用于排序

using namespace std; // 使用标准命名空间

// 定义比较函数，用于排序
// 参数是两个 pair，分别包含单词（string）和频次（int）
bool cmp(const pair<string, int>& a, const pair<string, int>& b) {
    if (a.second != b.second) { // 如果频次不相同
        return a.second > b.second; // 按频次从高到低排序（降序）
    }
    return a.first < b.first; // 如果频次相同，按单词字典序升序排序
}

int main() {
    string line; // 用于存储输入的一行字符串
    
    // 读取一行输入，处理可能包含空格的整行字符串
    // 使用 while 循环是为了处理可能的多组输入，虽然题目描述说“一行”，但在OJ中通常建议处理到EOF
    while (getline(cin, line)) {
        stringstream ss(line); // 使用 stringstream 将字符串转换为流，方便按空格分割单词
        string word; // 用于存储分割出的每个单词
        map<string, int> word_counts; // 使用 map 统计每个单词的出现次数，key为单词，value为频次
        
        // 从字符串流中依次读取单词
        while (ss >> word) {
            word_counts[word]++; // 对应单词的频次加1
        }
        
        // 注意：在旧版C++标准中，连续的右尖括号之间需要空格，即 > > 
        vector<pair<string, int> > keywords; // 用于存储筛选后的关键词及其频次
        
        // 遍历 map，筛选出频次不少于 3 次的单词
        // 使用显式迭代器类型以兼容旧版 C++ 标准
        // 或for (auto it = word_counts.begin(); it != word_counts.end(); ++it) 
        for (map<string, int>::iterator it = word_counts.begin(); it != word_counts.end(); ++it) {
            if (it->second >= 3) { // 如果该单词出现次数大于等于 3
                keywords.push_back(*it); // 将该单词及其频次加入 vector
            }
        }
        
        // 对筛选出的关键词进行排序
        // 使用自定义的 cmp 函数
        sort(keywords.begin(), keywords.end(), cmp);
        
        // 输出结果
        // 使用下标遍历 vector 以兼容旧版 C++ 标准
        for (size_t i = 0; i < keywords.size(); ++i) {
            cout << keywords[i].first << endl; // 每行输出一个关键词
        }
    }
    
    return 0; // 程序结束
}
