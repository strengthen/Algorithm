#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <vector>   // 引入向量容器库，用于存储字符串数组
#include <string>   // 引入字符串库，用于处理字符串
#include <algorithm> // 引入算法库，包含排序函数 sort

using namespace std; // 使用标准命名空间 std，避免每次调用标准库需加 std::

int main() { // 主函数入口
    int n; // 定义一个整型变量 n，用于存储输入的单词个数
    while (cin >> n) { // 循环读取单词个数 n，直到输入结束（虽然题目通常只给一组数据，但这样写更健壮）
        vector<string> words(n); // 定义一个字符串向量 words，大小为 n，用于存储所有单词
        for (int i = 0; i < n; ++i) { // 使用 for 循环，从 0 到 n-1 遍历
            cin >> words[i]; // 从标准输入读取第 i 个单词，存入向量对应的位置
        } // 读取循环结束

        sort(words.begin(), words.end()); // 调用 sort 函数，对 words 向量从头到尾进行字典序升序排序

        for (int i = 0; i < n; ++i) { // 使用 for 循环，遍历排序后的单词向量
            cout << words[i] << endl; // 输出当前的单词，并输出换行符
        } // 输出循环结束
    } // while 循环结束
    return 0; // 程序执行成功，返回 0
} // main 函数结束

