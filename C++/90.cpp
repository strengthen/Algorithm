#include <iostream> // 引入输入输出流库
#include <string>   // 引入字符串库
#include <vector>   // 引入向量容器库
#include <sstream>  // 引入字符串流库

using namespace std; // 使用标准命名空间

/**
 * 检查IP地址的每一部分是否合法
 * @param s IP地址的一个片段字符串
 * @return 如果合法返回true，否则返回false
 */
bool isValidPart(const string& s) {
    // 检查字符串是否为空，空字符串是不合法的（例如连续的点 .. 产生的情况）
    if (s.empty()) return false; 
    
    // 检查是否有前导0。如果长度大于1且第一位是'0'，则不合法（如 "01"）
    // 注意：单个 "0" 是合法的
    if (s.size() > 1 && s[0] == '0') return false; 
    
    // 简单的长度检查，超过3位的数字肯定大于255
    if (s.size() > 3) return false;

    // 检查是否包含非数字字符
    for (char c : s) {
        if (!isdigit(c)) return false; 
    }
    
    // 将字符串转换为整数进行数值范围检查
    int num = stoi(s);
    // IP地址的每部分必须在 0 到 255 之间
    return num >= 0 && num <= 255; 
}

/**
 * 验证IP地址是否合法的主要逻辑函数
 * @param ip 输入的IP地址字符串
 * @return 合法返回 "YES"，不合法返回 "NO"
 */
string checkIP(string ip) {
    int dotCount = 0; // 用于统计点号的数量
    // 遍历字符串统计点号
    for (char c : ip) {
        if (c == '.') {
            dotCount++;
        }
    }
    
    // 合法的IPv4地址必须正好包含3个点
    if (dotCount != 3) return "NO";

    stringstream ss(ip); // 使用stringstream处理字符串分割
    string segment;      // 存储分割出来的每一段
    vector<string> parts; // 存储所有段的容器
    
    // 使用getline按点号'.'分割字符串
    while (getline(ss, segment, '.')) {
        parts.push_back(segment);
    }

    // 如果分割出来的部分不是4部分，说明格式不对
    // 例如 "1.2.3." 会被分割成3部分（getline特性），但我们通过dotCount=3排除了部分情况
    // 这里再次确认分割后的数量
    if (parts.size() != 4) return "NO";

    // 遍历每一部分进行详细检查
    for (const string& part : parts) {
        if (!isValidPart(part)) {
            return "NO"; // 只要有一部分不合法，整体就不合法
        }
    }
    
    return "YES"; // 所有检查通过
}

int main() {
    string ip;
    // 循环读取输入，直到没有更多输入
    // 题目描述中可能会有多组数据
    while (cin >> ip) {
        cout << checkIP(ip) << endl; // 输出判断结果
    }
    return 0;
}
