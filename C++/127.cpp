#include <iostream> // 引入输入输出流库
#include <string>   // 引入字符串库
#include <vector>   // 引入向量库
#include <algorithm> // 引入算法库

using namespace std; // 使用标准命名空间

int main() {
    string s; // 定义一个字符串变量s用于存储输入
    if (cin >> s) { // 读取输入的字符串
        int n = s.length(); // 获取字符串的长度
        int half = n / 2; // 计算字符串长度的一半

        // 定义两个大小为26的整数向量，分别用于统计前半部分和后半部分字符出现的频率
        // 初始化所有计数为0
        vector<int> count1(26, 0); 
        vector<int> count2(26, 0);

        // 遍历字符串的前半部分
        for (int i = 0; i < half; ++i) {
            count1[s[i] - 'a']++; // 统计前半部分每个字符出现的次数
        }

        // 遍历字符串的后半部分
        for (int i = half; i < n; ++i) {
            count2[s[i] - 'a']++; // 统计后半部分每个字符出现的次数
        }

        int max1 = 0; // 用于存储前半部分出现次数最多的字符的次数
        int max2 = 0; // 用于存储后半部分出现次数最多的字符的次数

        // 遍历计数数组，找出前半部分的最大频率
        for (int i = 0; i < 26; ++i) {
            if (count1[i] > max1) { // 如果当前字符的频率大于max1
                max1 = count1[i]; // 更新max1
            }
        }

        // 遍历计数数组，找出后半部分的最大频率
        for (int i = 0; i < 26; ++i) {
            if (count2[i] > max2) { // 如果当前字符的频率大于max2
                max2 = count2[i]; // 更新max2
            }
        }

        // 计算最小修改次数
        // 总长度 - 前半部分保留的字符数 - 后半部分保留的字符数
        // 也就是 (half - max1) + (half - max2) = n - max1 - max2
        int min_changes = n - max1 - max2;

        cout << min_changes << endl; // 输出最小修改次数
    }
    return 0; // 程序正常结束
}
