#include <iostream> // 引入输入输出流库，用于标准输入输出
#include <cstdio>   // 引入C标准输入输出库，用于scanf和printf函数
#include <numeric>  // 引入数值算法库（虽然本例手写了gcd，但保留此头文件是好习惯）

// 定义求最大公约数的函数，用于约分分数
// 参数 a 和 b 分别为两个长整型数值
long long gcd(long long a, long long b) {
    // 使用递归方式实现欧几里得算法
    // 如果 b 为 0，则 a 即为最大公约数；否则继续计算 gcd(b, a % b)
    return b == 0 ? a : gcd(b, a % b);
}

// 主函数，程序的入口
int main() {
    long long a, b; // 定义两个长整型变量，分别存储分数的分子和分母

    // 使用 scanf 按照 "a/b" 的格式读取输入的分子和分母
    // 如果读取成功（返回值不为EOF），则进入处理逻辑
    while (scanf("%lld/%lld", &a, &b) != EOF) {
        
        // 开始循环，直到将分数完全分解为埃及分数之和
        while (true) {
            // 检查当前分母是否能被分子整除
            // 如果能整除，说明当前分数已经是埃及分数（分子为1）
            if (b % a == 0) {
                // 输出最后一个埃及分数，格式为 "1/分母"，并换行
                // b / a 即为该埃及分数的分母
                printf("1/%lld\n", b / a);
                // 分解结束，跳出循环
                break;
            }

            // 如果不能整除，使用贪心算法寻找最大的埃及分数 1/c
            // c 需要满足 1/c <= a/b，即 c >= b/a
            // 取 c 为 b/a 的整数部分加 1，即 ceil(b/a)
            long long c = b / a + 1;

            // 输出找到的埃及分数，后面加上加号
            printf("1/%lld+", c);

            // 更新剩余的分数：原分数 a/b 减去 1/c
            // 通分计算：a/b - 1/c = (a*c - b) / (b*c)
            long long next_a = a * c - b; // 计算新的分子
            long long next_b = b * c;     // 计算新的分母

            // 对新的分数进行约分，以防止数值过大溢出，并保持分数为最简形式
            // 计算新分子和新分母的最大公约数
            long long common = gcd(next_a, next_b);
            
            // 更新分子 a
            a = next_a / common;
            // 更新分母 b
            b = next_b / common;
        }
    }

    // 程序执行完毕，返回 0
    return 0;
}
