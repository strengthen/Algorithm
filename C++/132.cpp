#include <iostream> // 引入输入输出流头文件
#include <numeric>  // 引入数值算法头文件

using namespace std; // 使用标准命名空间

// 定义计算最大公约数的函数
long long calculate_gcd(long long a, long long b) { // 定义函数calculate_gcd，接收两个长整型参数
    return b == 0 ? a : calculate_gcd(b, a % b); // 使用递归算法计算最大公约数
}

int main() { // 主函数开始
    int t; // 定义测试用例组数变量t
    cin >> t; // 输入测试组数
    while (t--) { // 循环处理每一组测试数据
        long long x, y, a, b, c, d; // 定义目标坐标x,y和四个方向的步长a,b,c,d
        cin >> x >> y >> a >> b >> c >> d; // 输入x, y, a, b, c, d的值

        // 分析：
        // x轴方向移动由向左(c)和向右(d)决定，即 x = k1*d - k2*c
        // 根据裴蜀定理，x必须是gcd(c, d)的倍数才能到达
        long long gcd_x = calculate_gcd(c, d); // 计算x轴方向步长c和d的最大公约数

        // y轴方向移动由向上(a)和向下(b)决定，即 y = m1*a - m2*b
        // 同理，y必须是gcd(a, b)的倍数才能到达
        long long gcd_y = calculate_gcd(a, b); // 计算y轴方向步长a和b的最大公约数

        // 判断是否满足可达条件
        if (x % gcd_x == 0 && y % gcd_y == 0) { // 如果x能被gcd_x整除 并且 y能被gcd_y整除
            cout << "YES" << endl; // 输出YES
        } else { // 否则
            cout << "NO" << endl; // 输出NO
        }
    }
    return 0; // 返回0，表示程序正常结束
}
