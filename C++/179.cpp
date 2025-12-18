#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于处理字符串操作
#include <vector>   // 引入向量库，虽然本题主要用string，但作为常用容器引入
#include <algorithm> // 引入算法库，提供常用算法支持

using namespace std; // 使用标准命名空间，避免每次调用std::

int main() { // 主函数入口，程序从这里开始执行
    ios::sync_with_stdio(false); // 关闭C++标准流与C标准流的同步，显著提高I/O速度
    cin.tie(nullptr); // 解除cin与cout的绑定，避免不必要的缓冲区刷新，提高速度

    int n, k; // 定义整型变量n和k，分别表示初始字符串长度和操作次数
    if (!(cin >> n >> k)) return 0; // 从标准输入读取n和k，如果读取失败则直接退出程序

    string s; // 定义字符串变量s，用于存储初始的括号串
    cin >> s; // 从标准输入读取初始字符串s

    string left_s; // 定义字符串left_s，用于作为栈存储光标左侧的字符
    string right_s; // 定义字符串right_s，用于作为栈存储光标右侧的字符（逆序存储）

    int pos = -1; // 定义整型变量pos，用于记录光标'I'在字符串中的索引，初始化为-1
    for (int i = 0; i < n; ++i) { // 遍历输入的字符串s，寻找光标位置
        if (s[i] == 'I') { // 如果当前字符是光标'I'
            pos = i; // 记录光标'I'的当前下标
            break; // 找到光标后，跳出循环
        } // if语句结束
    } // for循环结束

    // 初始化左右两部分的栈
    if (pos != -1) { // 如果成功找到了光标位置
        left_s = s.substr(0, pos); // 将光标左侧的所有字符截取并赋值给left_s
        // 将光标右侧的字符逆序压入right_s栈中，以便在末尾进行O(1)的操作
        for (int i = n - 1; i > pos; --i) { // 从字符串末尾开始向前遍历直到光标位置右侧
            right_s.push_back(s[i]); // 将字符压入right_s，这样right_s.back()就是紧邻光标右侧的字符
        } // for循环结束
    } // if语句结束

    string op; // 定义字符串变量op，用于存储每次输入的操作指令
    while (k--) { // 循环k次，处理每一次操作指令
        cin >> op; // 从标准输入读取当前的操作指令
        if (op == "backspace") { // 如果当前操作是backspace（退格）
            // 判断是否满足特殊消除条件：左侧紧邻'('且右侧紧邻')'
            if (!left_s.empty() && !right_s.empty() && left_s.back() == '(' && right_s.back() == ')') { // 检查左栈非空、右栈非空，且匹配成对括号
                left_s.pop_back(); // 删除光标左侧的'('
                right_s.pop_back(); // 删除光标右侧的')'
            } else if (!left_s.empty()) { // 如果不满足上述特殊条件，但左侧还有字符
                left_s.pop_back(); // 普通退格，删除光标左侧的一个字符
            } // else if结束
        } else if (op == "delete") { // 如果当前操作是delete（删除）
            if (!right_s.empty()) { // 如果光标右侧还有字符
                right_s.pop_back(); // 删除光标右侧的一个字符
            } // if结束
        } // else if结束
    } // while循环结束

    cout << left_s; // 输出光标左侧剩余的字符串
    cout << 'I'; // 输出光标字符'I'本身
    // 因为right_s是逆序存储的，输出时需要反向遍历以恢复正确顺序
    for (int i = right_s.length() - 1; i >= 0; --i) { // 从right_s的末尾（即原字符串的左侧）开始遍历
        cout << right_s[i]; // 依次输出右侧部分的字符
    } // for循环结束
    cout << endl; // 输出换行符，标志输出结束

    return 0; // 主函数返回0，表示程序正常结束
} // main函数结束
