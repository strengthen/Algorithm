#include <iostream> // 引入输入输出流库，用于控制台输入输出

using namespace std; // 使用标准命名空间std，方便直接使用cin和cout

int main() { // 主函数入口
    int n; // 定义整型变量n，用于存储项数
    while (cin >> n) { // 循环读取输入，直到输入结束
        if (n < 1) continue; // 如果输入不合法（小于1），跳过本次循环
        
        // 等差数列求和公式: Sn = n*a1 + n*(n-1)*d/2
        // 已知首项 a1 = 2，公差 d = 3
        int a1 = 2; // 定义首项为2
        int d = 3;  // 定义公差为3
        
        // 使用求和公式计算前n项和
        // sum = 2*n + 3*n*(n-1)/2
        int sum = a1 * n + (n * (n - 1) * d) / 2; // 计算等差数列前n项和
        
        cout << sum << endl; // 输出计算结果并换行
    }
    return 0; // 返回0，表示程序正常执行完毕
}
