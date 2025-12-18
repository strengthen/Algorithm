#include <iostream> // 引入输入输出流库
#include <string>   // 引入字符串库
#include <unordered_set> // 引入无序集合库，用于存储已记住的单词
#include <unordered_map> // 引入无序映射库，用于记录每个未记住单词的背诵次数

using namespace std; // 使用标准命名空间

int main() { // 主函数入口
    int n; // 定义整数n，用于存储背单词的总记录数
    if (!(cin >> n)) return 0; // 从标准输入读取n，如果读取失败则直接返回

    unordered_set<string> memorized; // 定义一个哈希集合，用来存放已经完全记住的单词
    unordered_map<string, int> counts; // 定义一个哈希映射，用来记录未记住单词当前的背诵次数

    string word; // 定义一个字符串变量，用于临时存储每次输入的单词
    for (int i = 0; i < n; ++i) { // 循环n次，依次处理每一个输入的单词
        cin >> word; // 读取当前的单词字符串

        // 如果这个单词已经在已记住的集合中，则不需要再次背诵
        if (memorized.count(word)) { // 检查memorized集合中是否包含当前单词
            continue; // 如果包含，跳过本次循环，处理下一个单词
        }

        counts[word]++; // 如果单词未被记住，将其对应的背诵次数加1

        // 判断当前单词的背诵次数是否达到了记住该单词所需的次数
        // 根据题目描述：如果已经记住了i个单词，记一个新单词需要背i+1次
        // 这里 memorized.size() 就是题目中的 i
        if (counts[word] == memorized.size() + 1) { // 如果背诵次数等于已记住单词数 + 1
            memorized.insert(word); // 将该单词插入到已记住的集合中，表示成功记住
            // 注意：一旦记住，下次遇到该单词会在前面的 if (memorized.count(word)) 处被跳过
        }
    }

    cout << memorized.size() << endl; // 输出最终记住的单词总数

    return 0; // 程序执行成功，返回0
}
