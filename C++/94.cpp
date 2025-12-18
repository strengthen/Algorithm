#include <iostream> // 引入输入输出流库
#include <vector>   // 引入向量容器库
#include <string>   // 引入字符串库
#include <map>      // 引入映射容器库

using namespace std; // 使用标准命名空间

int main() { // 主函数入口
    int n; // 定义变量n，用于存储候选人数量
    while (cin >> n) { // 循环读取候选人数量，处理多组输入的情况（虽然题目描述未明确提及多组输入，但这是常见的OJ格式）
        vector<string> candidates(n); // 创建一个字符串向量，用于存储候选人的名字，保持输入顺序
        map<string, int> voteCounts; // 创建一个映射，用于存储每个候选人的得票数，键为名字，值为票数

        for (int i = 0; i < n; ++i) { // 循环读取n个候选人的名字
            cin >> candidates[i]; // 读取第i个候选人的名字
            voteCounts[candidates[i]] = 0; // 初始化该候选人的得票数为0
        }

        int m; // 定义变量m，用于存储投票人数
        cin >> m; // 读取投票人数
        int invalid = 0; // 定义变量invalid，用于统计无效票数，初始化为0

        for (int i = 0; i < m; ++i) { // 循环读取m张选票
            string vote; // 定义字符串变量vote，用于存储选票上的名字
            cin >> vote; // 读取选票上的名字
            if (voteCounts.count(vote)) { // 检查该名字是否在候选人名单中
                voteCounts[vote]++; // 如果在名单中，对应的候选人票数加1
            } else { // 如果不在名单中
                invalid++; // 无效票数加1
            }
        }

        for (const auto& name : candidates) { // 按照候选人输入的顺序遍历
            cout << name << " : " << voteCounts[name] << endl; // 输出候选人名字和对应的票数，注意格式包含空格和冒号
        }
        cout << "Invalid : " << invalid << endl; // 最后输出无效票的数量，注意格式
    }
    return 0; // 程序正常结束返回0
}
