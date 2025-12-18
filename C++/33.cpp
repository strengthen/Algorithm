#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于处理字符串
#include <sstream>  // 引入字符串流库，用于字符串的分割操作
#include <vector>   // 引入向量容器（虽然本解法主要用流，但习惯性包含）

using namespace std; // 使用标准命名空间，避免每次调用标准库函数都要加std::

// 主函数，程序的入口
int main() {
    string ip_str; // 定义字符串变量，用于存储输入的IP地址（如 10.0.3.193）
    long long ip_num_input; // 定义长整型变量，用于存储输入的十进制IP数值

    // 循环读取输入，假设输入数据成对出现：先是一个IP字符串，然后是一个整数
    // cin 会自动跳过空白字符（空格、换行等），所以可以正确读取两行输入
    while (cin >> ip_str >> ip_num_input) {
        
        // ---------------- IP地址转十进制整数 ----------------
        stringstream ss(ip_str); // 创建字符串流对象，用输入的IP字符串初始化
        string segment; // 用于存储按点号分割出来的每一段数字字符串
        unsigned int ip_val = 0; // 用于存储最终转换后的32位整数结果

        // 使用getline函数，以'.'为分隔符，循环读取每一段
        while (getline(ss, segment, '.')) {
            unsigned int seg_int = stoi(segment); // 将分割出来的字符串转换为整数
            // 将当前结果左移8位，腾出低8位空间，然后通过按位或运算将当前段的值放入低8位
            // 比如第一段10进来，变为 0...00001010
            // 第二段0进来，先左移变为 0...00001010 00000000，再或上0
            // 依此类推，最终拼成完整的32位整数
            ip_val = (ip_val << 8) | seg_int;
        }
        cout << ip_val << endl; // 输出转换得到的十进制整数

        // ---------------- 十进制整数转IP地址 ----------------
        // 将输入的数值转换为无符号32位整数，方便进行位运算
        unsigned int num = (unsigned int)ip_num_input; 

        // 依次提取32位整数的每8位，还原为IP地址的4段
        // (num >> 24) & 0xFF: 右移24位，将最高8位移到最低位，并用0xFF掩码确保只取这8位
        cout << ((num >> 24) & 0xFF) << "." 
             << ((num >> 16) & 0xFF) << "." // 右移16位，提取次高8位
             << ((num >> 8) & 0xFF) << "."  // 右移8位，提取次低8位
             << (num & 0xFF) << endl;       // 不移动，直接提取最低8位
    }

    return 0; // 程序正常结束，返回0
}

