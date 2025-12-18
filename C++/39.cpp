#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <vector>   // 引入向量容器库，用于存储IP地址的四段数字
#include <string>   // 引入字符串库，用于处理输入的IP字符串
#include <sstream>  // 引入字符串流库，用于分割字符串
#include <algorithm>// 引入算法库
#include <cstdlib>  // 引入标准库，用于atoi函数

using namespace std; // 使用标准命名空间

// 解析IP地址或子网掩码字符串的函数
// 参数：str - 输入的字符串（如 "192.168.0.1"）
// 返回值：存储4段整数的vector，如果格式非法则返回空vector
vector<int> parseIP(string str) {
    vector<int> ip; // 创建一个vector用于存储解析后的4个整数
    stringstream ss(str); // 使用字符串流来处理输入字符串
    string segment; // 用于存储分割出来的每一段字符串
    int dotCount = 0; // 计数器，用于统计'.'出现的次数

    // 遍历字符串统计'.'的数量，合法的IP必须正好包含3个'.'
    for (size_t i = 0; i < str.length(); ++i) { // 遍历字符串中的每个字符
        if (str[i] == '.') dotCount++; // 如果是'.'则计数加1
    }
    if (dotCount != 3) return vector<int>(); // 如果'.'的数量不是3，返回空vector表示格式非法

    // 使用getline以'.'为分隔符分割字符串
    while (getline(ss, segment, '.')) { // 循环读取每一段
        if (segment.empty()) return vector<int>(); // 如果某一段为空（例如连续的..），则格式非法
        
        // 检查该段字符串是否只包含数字
        for (size_t i = 0; i < segment.length(); ++i) { // 遍历段中的每个字符
            if (!isdigit(segment[i])) return vector<int>(); // 如果发现非数字字符，则格式非法
        }
        
        // 转换为整数
        // 在C++98中，使用atoi，需要将string转为C风格字符串
        int val = atoi(segment.c_str()); 
        ip.push_back(val); // 将转换后的整数加入vector
    }

    return ip; // 返回解析出的整数数组
}

// 检查IP地址是否合法
// 参数：ip - 解析后的整数数组
// 返回值：合法返回true，非法返回false
bool isValidIP(const vector<int>& ip) {
    if (ip.size() != 4) return false; // IP地址必须由4部分组成
    for (size_t i = 0; i < ip.size(); ++i) { // 遍历每一部分
        if (ip[i] < 0 || ip[i] > 255) return false; //每一部分的值必须在0到255之间
    }
    return true; // 所有检查通过，返回true
}

// 检查子网掩码是否合法
// 参数：mask - 解析后的子网掩码整数数组
// 返回值：合法返回true，非法返回false
bool isValidMask(const vector<int>& mask) {
    if (!isValidIP(mask)) return false; // 子网掩码首先必须符合IP地址的基本格式

    unsigned int val = 0; // 用于将4段整数合并为一个32位无符号整数
    for (size_t i = 0; i < mask.size(); ++i) { // 遍历掩码的每一段
        val = (val << 8) | mask[i]; // 通过位移和或运算拼接整数
    }

    // 掩码全0或全1在本题中通常被视为非法
    if (val == 0 || val == 0xFFFFFFFF) return false; // 如果是0.0.0.0或255.255.255.255，视为非法

    // 检查掩码二进制是否符合“前面全1，后面全0”的规则
    bool zeroFound = false; // 标记是否已经遇到了0
    for (int i = 31; i >= 0; i--) { // 从最高位（第31位）向最低位（第0位）遍历
        if (((val >> i) & 1) == 0) { // 如果当前位是0
            zeroFound = true; // 标记已经遇到0，之后的所有位都必须是0
        } else { // 如果当前位是1
            if (zeroFound) return false; // 如果之前已经遇到过0，现在又遇到1，说明不连续，非法
        }
    }

    return true; // 符合规则，返回true
}

// 主函数
int main() {
    string maskStr, ip1Str, ip2Str; // 定义变量存储输入的子网掩码和两个IP地址字符串

    // 循环读取输入，每次读取3个字符串（题目描述每组输入3行）
    while (cin >> maskStr >> ip1Str >> ip2Str) { // 使用cin读取标准输入
        vector<int> mask = parseIP(maskStr); // 解析子网掩码
        vector<int> ip1 = parseIP(ip1Str);   // 解析第一个IP地址
        vector<int> ip2 = parseIP(ip2Str);   // 解析第二个IP地址

        bool isError = false; // 用于标记是否出现格式错误

        // 检查解析结果和基本合法性
        if (!isValidMask(mask)) isError = true; // 检查子网掩码是否合法
        if (!isValidIP(ip1)) isError = true;    // 检查IP1是否合法
        if (!isValidIP(ip2)) isError = true;    // 检查IP2是否合法

        if (isError) { // 如果有任何一个格式非法
            cout << 1 << endl; // 输出1
        } else { // 如果格式都合法
            bool sameSubnet = true; // 假设属于同一子网
            // 计算并比较网络号：(IP1 & Mask) == (IP2 & Mask)
            for (int i = 0; i < 4; i++) { // 遍历4个段
                if ((ip1[i] & mask[i]) != (ip2[i] & mask[i])) { // 进行按位与运算并比较
                    sameSubnet = false; // 如果结果不同，则不属于同一子网
                    break; // 退出循环
                }
            }

            if (sameSubnet) { // 如果属于同一子网
                cout << 0 << endl; // 输出0
            } else { // 如果不属于同一子网
                cout << 2 << endl; // 输出2
            }
        }
    }
    return 0; // 程序正常结束
}
