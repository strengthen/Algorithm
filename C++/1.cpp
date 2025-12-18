#include <iostream> // 引入标准输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于使用 string 类型

using namespace std; // 使用标准命名空间 std，方便直接使用 string, cin, cout 等

int main() {
    string word; // 声明一个字符串变量 word，用于临时存储每次读取的单词
    
    // 使用 while 循环通过 cin 读取输入
    // cin >> word 会自动跳过空格和换行符，每次读取一个以空白分隔的单词
    // 当输入流结束（EOF）时，循环条件变为假，循环终止
    while (cin >> word) {
        // 循环体为空，因为我们的目的是读取所有的单词
        // 每次读取新单词都会覆盖 word 变量
        // 循环结束时，word 中存储的就是最后一个单词
    }
    
    // 输出最后一个单词的长度
    // word.length() 返回字符串的长度，也可以使用 word.size()
    cout << word.length() << endl;
    
    return 0; // 返回 0 表示程序执行成功
}

