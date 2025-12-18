#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于使用to_string等字符串操作
#include <algorithm> // 引入算法库

using namespace std; // 使用标准命名空间std

int main() { // 主函数入口
    int n; // 定义整型变量n，用于存储输入的范围上限
    while (cin >> n) { // 循环读取输入，直到输入结束
        int count = 0; // 定义整型变量count，用于统计自守数的个数，初始化为0
        for (int i = 0; i <= n; ++i) { // 从0循环遍历到n，依次判断每个数是否为自守数
            long long square = (long long)i * i; // 计算当前数i的平方，使用long long防止溢出
            string s_num = to_string(i); // 将当前数i转换为字符串
            string s_square = to_string(square); // 将平方数转换为字符串
            
            // 判断平方数的末尾是否正好等于原数
            // 如果平方数长度大于等于原数长度，且平方数的末尾子串等于原数
            if (s_square.size() >= s_num.size() && // 检查长度合法性
                s_square.substr(s_square.size() - s_num.size()) == s_num) { // 截取末尾并比较
                count++; // 如果条件满足，则是自守数，计数器加1
            }
        }
        cout << count << endl; // 输出统计到的自守数总个数
    }
    return 0; // 返回0，表示程序正常执行完毕
}
