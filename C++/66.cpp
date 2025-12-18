#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于处理字符串
#include <vector>   // 引入向量库，用于存储命令列表
#include <sstream>  // 引入字符串流库，用于分割输入字符串

using namespace std; // 使用标准命名空间

// 定义命令结构体，存储命令的关键字和对应的执行结果
struct Command {
    string key1;    // 命令的第一个关键字
    string key2;    // 命令的第二个关键字（如果是单关键字命令，此项为空字符串）
    string result;  // 命令对应的执行结果输出
};

// 辅助函数：判断 str1 是否是 str2 的前缀
// 参数 s: 输入的短字符串
// 参数 t: 目标匹配的长字符串（命令关键字）
bool isPrefix(const string& s, const string& t) {
    if (s.size() > t.size()) return false; // 如果输入比目标长，肯定不是前缀
    return t.substr(0, s.size()) == s;     // 截取目标字符串的前s.size()个字符与s比较
}

int main() {
    // 初始化命令列表，根据题目描述硬编码所有6条命令
    // 注意：单关键字命令 "reset" 的 key2 设为空字符串
    vector<Command> cmds = {
        {"reset", "", "reset what"},
        {"reset", "board", "board fault"},
        {"board", "add", "where to add"},
        {"board", "delete", "no board at all"},
        {"reboot", "backplane", "impossible"},
        {"backplane", "abort", "install first"}
    };

    string line; // 用于存储每一行输入
    // 使用 getline 循环读取每一行输入，直到输入结束
    while (getline(cin, line)) {
        stringstream ss(line); // 使用 stringstream 处理当前行，方便按空格分割单词
        string s1, s2; // 用于存储分割后的两个单词
        vector<string> inputs; // 存储分割后的单词列表
        string temp; 
        
        // 将当前行按空格拆分为单词存入 inputs 向量
        while (ss >> temp) {
            inputs.push_back(temp);
        }

        vector<string> matches; // 用于存储匹配到的结果字符串

        // 遍历所有定义的命令，寻找匹配项
        for (const auto& cmd : cmds) {
            // 情况1：输入只有一个单词
            if (inputs.size() == 1) {
                // 规则：只输入一字串，则只匹配一个关键字的命令行
                // 所以必须要求当前命令的 key2 为空，且输入是 key1 的前缀
                if (cmd.key2 == "" && isPrefix(inputs[0], cmd.key1)) {
                    matches.push_back(cmd.result); // 记录匹配到的结果
                }
            }
            // 情况2：输入有两个单词
            else if (inputs.size() == 2) {
                // 规则：输入两字串，则先匹配第一关键字，如果有匹配，继续匹配第二关键字
                // 必须要求当前命令是双关键字（key2不为空）
                // 且第一个输入是 key1 的前缀，第二个输入是 key2 的前缀
                if (cmd.key2 != "" && isPrefix(inputs[0], cmd.key1) && isPrefix(inputs[1], cmd.key2)) {
                    matches.push_back(cmd.result); // 记录匹配到的结果
                }
            }
            // 如果输入单词数不是1也不是2，则不匹配任何命令
        }

        // 根据匹配到的数量输出结果
        if (matches.size() == 1) {
            // 如果只有唯一一个匹配项，输出该结果
            cout << matches[0] << endl;
        } else {
            // 如果没有匹配项，或者匹配项多于1个（不唯一），输出 unknown command
            cout << "unknown command" << endl;
        }
    }

    return 0; // 程序正常结束
}
