#include <iostream> // 引入输入输出流库
#include <string>   // 引入字符串处理库
#include <algorithm> // 引入算法库，用于reverse函数
#include <vector>   // 引入向量库（虽然本题可以用string代替，但习惯性引入）

using namespace std; // 使用标准命名空间

int main() {
    string str1, str2; // 定义两个字符串用于存储大整数
    // 循环读取两个字符串输入，处理多组测试用例的情况
    while (cin >> str1 >> str2) {
        string result = ""; // 初始化结果字符串，用于存储加法结果
        int i = str1.length() - 1; // 初始化指针i指向str1的最后一位（个位）
        int j = str2.length() - 1; // 初始化指针j指向str2的最后一位（个位）
        int carry = 0; // 初始化进位变量为0

        // 当str1或str2还有未处理的位，或者还有进位时，继续循环
        while (i >= 0 || j >= 0 || carry > 0) {
            // 获取str1当前位的数字，如果i小于0则视为0，字符减'0'转换为整数
            int digit1 = (i >= 0) ? str1[i] - '0' : 0;
            // 获取str2当前位的数字，如果j小于0则视为0，字符减'0'转换为整数
            int digit2 = (j >= 0) ? str2[j] - '0' : 0;

            // 计算当前位的和：digit1 + digit2 + 进位
            int sum = digit1 + digit2 + carry;

            // 将当前位计算结果的个位数转为字符追加到result字符串末尾
            result += to_string(sum % 10);

            // 计算新的进位值，即sum除以10的商
            carry = sum / 10;

            // 将指针i向前移动一位
            i--;
            // 将指针j向前移动一位
            j--;
        }

        // 因为我们是从个位开始计算并追加到result末尾的，所以得到的result是逆序的
        // 使用reverse函数将result字符串反转，得到正确的顺序
        reverse(result.begin(), result.end());

        // 输出最终计算得到的和
        cout << result << endl;
    }
    return 0; // 程序正常结束
}
