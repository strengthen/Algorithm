#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于处理字符串操作
#include <vector>   // 引入向量容器，用于存储解析出的参数

using namespace std; // 使用标准命名空间

int main() { // 主函数
    string line; // 定义字符串变量存储输入的一行命令
    
    // 使用getline从标准输入读取整行数据，因为命令参数中包含空格
    // while循环是为了处理可能的多个测试用例，虽然题目描述是一行，但这样更稳健
    while (getline(cin, line)) { 
        vector<string> args; // 用于存储解析后的参数列表
        string currentArg = ""; // 用于构建当前正在解析的参数
        bool inQuotes = false; // 标记当前是否处于双引号内部，初始化为false
        
        // 遍历输入字符串的每一个字符
        for (int i = 0; i < line.length(); ++i) {
            if (line[i] == '"') { 
                // 如果遇到双引号，切换inQuotes状态
                // 题目要求输出时去掉引号，所以这里不将引号加入currentArg
                inQuotes = !inQuotes; 
            } else if (line[i] == ' ' && !inQuotes) {
                // 如果遇到空格，且当前不在引号内，说明一个参数结束了
                // 判断currentArg是否为空，避免将连续空格解析为空参数
                if (!currentArg.empty()) {
                    args.push_back(currentArg); // 将当前参数加入列表
                    currentArg.clear(); // 清空currentArg，准备解析下一个参数
                }
            } else {
                // 其他情况（普通字符，或者引号内的空格），直接加入当前参数
                currentArg += line[i];
            }
        }
        
        // 循环结束后，最后一个参数可能还没加入列表（因为最后没有空格）
        if (!currentArg.empty()) {
            args.push_back(currentArg);
        }
        
        // 输出参数个数
        cout << args.size() << endl;
        
        // 依次输出每个参数，每个参数占一行
        for (const string& arg : args) {
            cout << arg << endl;
        }
    }
    
    return 0; // 程序结束
}
