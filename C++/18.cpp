#include <iostream> // 引入输入输出流库
#include <string> // 引入字符串处理库
#include <vector> // 引入向量容器库
#include <sstream> // 引入字符串流库
#include <algorithm> // 引入算法库

using namespace std; // 使用标准命名空间

// 解析IP地址或子网掩码，将其转换为4个整数
// 参数s为待解析字符串，parts用于存储解析出的整数
// 返回值表示解析是否成功
bool parseIP(const string &s, vector<int> &parts) {
    parts.clear(); // 清空存储结果的向量
    if (s.empty()) return false; // 如果字符串为空，返回解析失败
    
    // 初始化起始位置和查找点的位置
    size_t start = 0; // 当前段的起始索引
    size_t end = s.find('.'); // 查找第一个点的位置
    
    // 循环处理每一段，直到找不到点为止
    while (end != string::npos) {
        string sub = s.substr(start, end - start); // 截取当前段的子串
        if (sub.empty()) return false; // 如果子串为空（例如连续点），返回失败
        for (char c : sub) { // 遍历子串中的每个字符
            if (!isdigit(c)) return false; // 如果包含非数字字符，返回失败
        }
        try {
            int val = stoi(sub); // 将子串转换为整数
            if (val < 0 || val > 255) return false; // 如果数值不在0-255之间，返回失败
            parts.push_back(val); // 将合法的数值存入向量
        } catch (...) {
            return false; // 如果转换异常，返回失败
        }
        start = end + 1; // 更新起始位置到点之后
        end = s.find('.', start); // 查找下一个点的位置
    }
    
    // 处理最后一段（最后一个点之后的内容）
    string sub = s.substr(start); // 截取最后一段子串
    if (sub.empty()) return false; // 如果最后一段为空（例如以点结尾），返回失败
    for (char c : sub) { // 遍历最后一段的每个字符
        if (!isdigit(c)) return false; // 如果包含非数字字符，返回失败
    }
    try {
        int val = stoi(sub); // 将最后一段转换为整数
        if (val < 0 || val > 255) return false; // 如果数值不在0-255之间，返回失败
        parts.push_back(val); // 将合法的数值存入向量
    } catch (...) {
        return false; // 如果转换异常，返回失败
    }
    
    // 验证是否正好解析出4段数字
    return parts.size() == 4; // 如果是4段则返回成功，否则失败
}

// 检查子网掩码是否合法
// 参数parts为掩码的4段整数
bool isMaskValid(const vector<int> &parts) {
    if (parts.size() != 4) return false; // 如果不是4段，视为非法
    
    unsigned int mask = 0; // 用于存储32位掩码整数
    for (int p : parts) { // 遍历每一段
        mask = (mask << 8) | p; // 将当前段拼接到32位整数中
    }
    
    // 检查是否全为0或全为1（非法掩码）
    if (mask == 0 || mask == 0xFFFFFFFF) return false; // 如果是全0或全1，返回非法
    
    // 检查二进制位是否是连续的1后跟连续的0
    unsigned int inv = ~mask; // 对掩码取反
    unsigned int invPlus1 = inv + 1; // 取反后加1
    
    // 如果掩码合法，invPlus1应该是2的幂次（二进制中只有一位是1）
    // 使用位运算检查是否为2的幂次：x & (x-1) == 0
    return (invPlus1 & (invPlus1 - 1)) == 0; // 返回检查结果
}

int main() {
    string line; // 用于存储每行输入的字符串
    // 初始化各类统计计数器
    int countA = 0; // A类地址计数
    int countB = 0; // B类地址计数
    int countC = 0; // C类地址计数
    int countD = 0; // D类地址计数
    int countE = 0; // E类地址计数
    int countErr = 0; // 错误IP或掩码计数
    int countPriv = 0; // 私有IP计数
    
    // 循环读取每一行输入直到文件结束
    while (cin >> line) {
        size_t tildePos = line.find('~'); // 查找分隔符波浪线的位置
        if (tildePos == string::npos) { // 如果没找到分隔符
            countErr++; // 计入错误
            continue; // 跳过处理下一行
        }
        
        string ipStr = line.substr(0, tildePos); // 提取IP地址部分字符串
        string maskStr = line.substr(tildePos + 1); // 提取子网掩码部分字符串
        
        vector<int> ipParts; // 存储解析后的IP段
        bool ipFormatValid = parseIP(ipStr, ipParts); // 解析IP地址并获取格式有效性
        
        // 检查特殊忽略规则：以0或127开头的IP
        if (ipFormatValid) { // 只有IP格式基本正确时才能判断首段
            if (ipParts[0] == 0 || ipParts[0] == 127) { // 如果首段是0或127
                continue; // 直接忽略该行，不计入任何统计
            }
        }
        
        vector<int> maskParts; // 存储解析后的掩码段
        bool maskFormatValid = parseIP(maskStr, maskParts); // 解析掩码并获取格式有效性
        
        bool maskContentValid = false; // 掩码内容逻辑有效性
        if (maskFormatValid) { // 如果格式正确
            maskContentValid = isMaskValid(maskParts); // 检查逻辑是否正确
        }
        
        // 如果掩码格式错误或逻辑错误
        if (!maskFormatValid || !maskContentValid) {
            countErr++; // 计入错误
            continue; // 跳过处理下一行
        }
        
        // 掩码合法后，检查IP是否合法
        if (!ipFormatValid) { // 如果IP格式错误
            countErr++; // 计入错误
            continue; // 跳过处理下一行
        }
        
        // IP和掩码均合法，进行分类统计
        int first = ipParts[0]; // 获取IP第一段
        int second = ipParts[1]; // 获取IP第二段
        
        // 判断是否为私有IP
        bool isPrivate = false; // 私有IP标志位
        if (first == 10) { // 10.0.0.0 - 10.255.255.255
            isPrivate = true; // 标记为私有
        } else if (first == 172) { // 172.16.0.0 - 172.31.255.255
            if (second >= 16 && second <= 31) isPrivate = true; // 检查第二段范围
        } else if (first == 192) { // 192.168.0.0 - 192.168.255.255
            if (second == 168) isPrivate = true; // 检查第二段是否为168
        }
        
        if (isPrivate) { // 如果是私有IP
            countPriv++; // 私有IP计数加1
        }
        
        // 判断IP类别（A/B/C/D/E）
        if (first >= 1 && first <= 126) { // A类：1-126
            countA++; // A类计数加1
        } else if (first >= 128 && first <= 191) { // B类：128-191
            countB++; // B类计数加1
        } else if (first >= 192 && first <= 223) { // C类：192-223
            countC++; // C类计数加1
        } else if (first >= 224 && first <= 239) { // D类：224-239
            countD++; // D类计数加1
        } else if (first >= 240 && first <= 255) { // E类：240-255
            countE++; // E类计数加1
        }
    }
    
    // 输出所有统计结果，以空格分隔
    cout << countA << " " << countB << " " << countC << " " << countD << " " << countE << " " << countErr << " " << countPriv << endl;
    
    return 0; // 程序正常结束
}
