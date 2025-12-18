#include <iostream> // 引入输入输出流库，用于控制台输入输出

using namespace std; // 使用标准命名空间std

// 定义一个函数用于计算最大公约数（Greatest Common Divisor）
// 使用欧几里得算法（辗转相除法）
int gcd(int a, int b) { // 函数接受两个整数参数a和b
    if (b == 0) // 如果b等于0
        return a; // 则a就是最大公约数，返回a
    return gcd(b, a % b); // 否则递归调用gcd函数，参数为b和a除以b的余数
}

int main() { // 主函数入口
    int a, b; // 定义两个整型变量a和b，用于存储输入的两个正整数
    while (cin >> a >> b) { // 循环从标准输入读取两个整数，直到输入结束
        // 计算最小公倍数（Least Common Multiple）
        // 公式为：lcm(a, b) = (a * b) / gcd(a, b)
        // 为了防止a * b的结果溢出int类型的范围（最大约20亿），这里先强制转换为long long类型
        long long lcm = (long long)a * b / gcd(a, b); // 计算最小公倍数并存储在long long类型的变量lcm中
        cout << lcm << endl; // 将计算结果输出到标准输出，并换行
    }
    return 0; // 返回0，表示程序正常执行完毕
}
