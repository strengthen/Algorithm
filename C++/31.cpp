#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于处理字符串对象
#include <vector>   // 引入向量库，用于存储动态数组
#include <cctype>   // 引入字符处理库，包含isalpha等函数

using namespace std; // 使用标准命名空间，避免每次都要写std::

int main() { // 主函数的开始，程序执行的入口
    string input; // 定义一个字符串变量input，用于存储读取的一整行输入
    getline(cin, input); // 从标准输入读取一行字符，存入input中

    vector<string> words; // 定义一个字符串向量words，用于按顺序存储提取出的单词
    string current_word = ""; // 定义一个临时字符串current_word，用于构建当前正在解析的单词

    for (int i = 0; i < input.length(); ++i) { // 使用for循环遍历输入字符串的每一个字符
        if (isalpha(input[i])) { // 使用isalpha函数判断当前字符是否为字母（a-z或A-Z）
            current_word += input[i]; // 如果是字母，则将其追加到当前构建的单词末尾
        } else { // 如果当前字符不是字母（即遇到了分隔符，如空格、标点等）
            if (!current_word.empty()) { // 检查当前构建的单词是否为空（防止连续分隔符导致存入空串）
                words.push_back(current_word); // 如果不为空，将构建好的单词添加到words向量中
                current_word = ""; // 清空current_word，准备构建下一个单词
            }
        }
    }

    if (!current_word.empty()) { // 循环结束后，检查是否还有最后一个单词未被添加（例如字符串以字母结尾）
        words.push_back(current_word); // 如果有，将最后一个单词添加到words向量中
    }

    for (int i = words.size() - 1; i >= 0; --i) { // 使用for循环逆序遍历words向量，从最后一个单词开始
        cout << words[i]; // 输出当前索引位置的单词
        if (i != 0) { // 判断当前是否为倒序输出的最后一个单词（即原句的第一个单词）
            cout << " "; // 如果不是最后一个，则在单词后面输出一个空格作为分隔
        }
    }
    cout << endl; // 输出所有单词后，输出一个换行符，保持格式整洁

    return 0; // 返回0，表示程序成功执行完毕
}

