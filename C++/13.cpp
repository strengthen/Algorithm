#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <vector>   // 引入向量容器库，用于存储单词
#include <string>   // 引入字符串库，用于处理文本

using namespace std; // 使用标准命名空间，方便直接使用 string, vector, cout 等

int main() {
    vector<string> words; // 定义一个字符串类型的向量，用来存储输入的所有单词
    string word;          // 定义一个临时字符串变量，用于接收每次输入的单词

    // 循环读取输入，cin >> word 会自动跳过空格和换行符，每次读取一个单词
    // 当输入结束（遇到 EOF）时，循环终止
    while (cin >> word) {
        words.push_back(word); // 将读取到的单词添加到向量 words 的末尾
    }

    // 从向量的最后一个元素开始向前遍历，实现逆序输出
    for (int i = words.size() - 1; i >= 0; --i) {
        cout << words[i]; // 输出当前索引对应的单词
        
        // 如果不是最后一个要输出的单词（即不是原句子的第一个单词），则输出一个空格
        if (i > 0) {
            cout << " "; 
        }
    }
    
    cout << endl; // 输出换行符，保持输出格式整洁

    return 0; // 程序正常结束，返回 0
}

