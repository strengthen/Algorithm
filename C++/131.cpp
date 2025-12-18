#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <vector>   // 引入向量库，用于使用 vector 容器

using namespace std; // 使用标准命名空间，简化 std::cout 等的写法

int main() { // 主函数入口
    int n; // 声明一个整型变量 n，用于存储数组元素的数量
    // 读取数组长度 n，如果读取成功则继续执行
    if (cin >> n) {
        vector<int> counts(10, 0); // 创建一个大小为 10 的整型向量 counts，初始值全为 0，用于统计 1-9 各个数字出现的次数
        int val; // 声明一个整型变量 val，用于临时存储读取的数组元素

        // 循环 n 次，读取数组中的每一个元素
        for (int i = 0; i < n; ++i) {
            cin >> val; // 从标准输入读取一个整数赋值给 val
            // 判断输入的数字是否在 1 到 9 之间（包含 1 和 9）
            if (val >= 1 && val <= 9) {
                counts[val]++; // 如果是 1-9 之间的数字，将其对应的计数加 1
            }
        }

        // 计算基准出现次数 k
        // 数独数组要求每连续 9 个数字包含 1-9，因此数组必定以 9 为周期重复
        // n 个元素中包含 n / 9 个完整的 1-9 周期
        int k = n / 9;

        bool possible = true; // 声明布尔变量 possible，用于标记是否可能重排成数独数组，初始化为 true

        // 遍历数字 1 到 9，检查每个数字的出现频率
        for (int i = 1; i <= 9; ++i) {
            // 在长度为 n 的数独数组中，每个数字 1-9 出现的次数必须是 k 次或 k+1 次
            // 因为 n = 9 * k + r (0 <= r < 9)，多出的 r 个位置会分配给 r 个不同的数字
            // 如果某个数字的出现次数小于 k 或者大于 k + 1，则不符合要求
            if (counts[i] < k || counts[i] > k + 1) {
                possible = false; // 将 possible 标记为 false
                break; // 跳出循环，不再检查其他数字
            }
        }

        // 根据检查结果输出 YES 或 NO
        if (possible) { // 如果 possible 为 true
            cout << "YES" << endl; // 输出 YES 并换行
        } else { // 如果 possible 为 false
            cout << "NO" << endl; // 输出 NO 并换行
        }
    }
    return 0; // 程序执行成功，返回 0
}
