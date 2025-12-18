#include <iostream> // 引入标准输入输出流库
#include <string> // 引入标准字符串处理库
#include <algorithm> // 引入标准算法库，包含min函数
#include <cmath> // 引入标准数学库，包含abs函数

using namespace std; // 使用标准命名空间std

int main() { // 程序的主函数入口
    string s; // 定义一个字符串变量s用于存储输入数据
    cin >> s; // 从标准输入读取一个字符串赋值给s
    int n = s.length(); // 计算字符串s的长度并存储在变量n中
    long long ans = 0; // 定义一个长整型变量ans用于累加最少操作次数，初始化为0
    for (int i = 0; i < n / 2; i++) { // 循环遍历字符串的前半部分字符
        int left = s[i] - 'a'; // 计算左边字符相对于'a'的偏移值
        int right = s[n - 1 - i] - 'a'; // 计算右边对称位置字符相对于'a'的偏移值
        int diff = abs(left - right); // 计算左右两个字符偏移值之差的绝对值
        int ops = min(diff, 26 - diff); // 取直接距离和环绕距离中的较小值作为最小操作数
        ans += ops; // 将当前对字符需要的最小操作数累加到ans中
    } // for循环结束
    cout << ans << endl; // 输出最终计算得到的最少操作次数
    return 0; // 返回0表示程序正常结束
}
