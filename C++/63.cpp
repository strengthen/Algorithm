#include <iostream> // 引入输入输出流库，用于标准输入输出操作
#include <string>   // 引入字符串库，用于处理字符串类型
#include <vector>   // 引入向量容器库（虽然本题主要用string，但作为常用库一并引入）

using namespace std; // 使用标准命名空间，以便直接使用cin, cout, string等标识符

int main() { // 主函数，程序的执行入口
    string dna; // 定义一个字符串变量dna，用于存储输入的DNA序列
    int n; // 定义一个整型变量n，用于存储需要查找的子串长度

    // 使用while循环读取输入，支持处理多组测试数据，cin >> dna >> n 会跳过空白字符读取
    while (cin >> dna >> n) {
        int len = dna.length(); // 获取输入DNA字符串的总长度，并转换为int类型
        
        // 如果要求的子串长度大于字符串本身的长度，则无法截取，直接进行下一次循环或退出
        if (n > len) { // 检查子串长度是否合法
            continue; // 如果不合法（通常题目保证合法），则跳过本次处理
        }

        int maxGCCount = 0; // 定义maxGCCount变量，记录当前发现的子串中G和C的最大总数，初始化为0
        int bestStart = 0;  // 定义bestStart变量，记录GC比例最高的子串的起始索引，初始化为0

        // 步骤1：先计算第一个窗口（从索引0开始，长度为n）的GC数量
        for (int i = 0; i < n; ++i) { // 遍历子串的前n个字符
            if (dna[i] == 'G' || dna[i] == 'C') { // 判断当前字符是否为 'G' 或 'C'
                maxGCCount++; // 如果是，计数器加1
            }
        }

        int currentGCCount = maxGCCount; // 定义currentGCCount保存当前滑动窗口的GC数量，初始值设为第一个窗口的数量

        // 步骤2：使用滑动窗口法遍历后续所有可能的子串
        // i 代表当前子串的起始位置，从索引1开始，直到 len - n
        for (int i = 1; i <= len - n; ++i) { // 循环移动窗口，每次向右移动一位
            // 移出窗口最左侧的字符：该字符位置为 i - 1
            if (dna[i - 1] == 'G' || dna[i - 1] == 'C') { // 检查移出的字符是否为G或C
                currentGCCount--; // 如果是，当前窗口的GC数量减1
            }
            
            // 移入窗口最右侧的字符：该字符位置为 i + n - 1
            if (dna[i + n - 1] == 'G' || dna[i + n - 1] == 'C') { // 检查新移入的字符是否为G或C
                currentGCCount++; // 如果是，当前窗口的GC数量加1
            }

            // 比较当前窗口的GC数量是否超过了之前的最大值
            // 题目要求找出“第一个”满足条件的子串，所以只有严格大于 (>) 时才更新
            if (currentGCCount > maxGCCount) { // 如果当前GC数量更高
                maxGCCount = currentGCCount; // 更新最大GC数量记录
                bestStart = i; // 更新最佳子串的起始位置为当前位置 i
            }
        }

        // 步骤3：输出结果
        // substr(pos, len) 函数返回从 pos 开始长度为 len 的子串
        cout << dna.substr(bestStart, n) << endl; // 打印GC比例最高的第一个子串，并换行
    }

    return 0; // 程序正常结束，返回状态码0
}
