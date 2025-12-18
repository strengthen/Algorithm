#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于处理字符串
#include <vector>   // 引入向量库，用于存储字符位置
#include <algorithm> // 引入算法库，用于使用min等函数
#include <climits>  // 引入limits库，用于使用INT_MAX

using namespace std; // 使用标准命名空间std

// 解决单个测试用例的函数
void solve() {
    int n; // 定义整数n，用于存储手串宝石数量
    cin >> n; // 从标准输入读取n
    string s; // 定义字符串s，用于存储手串的属性
    cin >> s; // 从标准输入读取手串字符串

    vector<int> pos[26]; // 定义一个包含26个vector的数组，分别存储'a'-'z'的索引位置
    for (int i = 0; i < n; ++i) { // 遍历字符串中的每一个字符
        pos[s[i] - 'a'].push_back(i); // 将字符的索引存入对应的vector中
    }

    int min_ops = INT_MAX; // 初始化最小操作次数为最大整数
    bool found_duplicate = false; // 标记是否找到重复的宝石属性

    for (int i = 0; i < 26; ++i) { // 遍历26个小写字母
        if (pos[i].size() >= 2) { // 如果某个字母出现至少两次
            found_duplicate = true; // 标记找到了重复字符
            for (size_t k = 0; k < pos[i].size() - 1; ++k) { // 遍历该字符的所有相邻出现位置（线性顺序）
                // 计算两个相邻相同字符之间的距离（需要移除的宝石数）
                // 距离 = 后一个索引 - 前一个索引 - 1
                int dist = pos[i][k+1] - pos[i][k] - 1; 
                if (dist < min_ops) { // 如果当前距离小于已知的最小操作数
                    min_ops = dist; // 更新最小操作数
                }
            }
            // 计算环形情况下的距离：即最后一个出现位置和第一个出现位置之间的距离
            // 环形距离 = 总长度 - (最后一个索引 - 第一个索引) - 1
            int circular_dist = n - (pos[i].back() - pos[i][0]) - 1;
            if (circular_dist < min_ops) { // 如果环形距离小于已知的最小操作数
                min_ops = circular_dist; // 更新最小操作数
            }
        }
    }

    if (!found_duplicate) { // 如果没有找到任何重复的宝石属性
        cout << -1 << endl; // 无法破坏，输出-1
    } else { // 如果找到了重复属性
        cout << min_ops << endl; // 输出最少需要摘掉的宝石数量
    }
}

int main() { // 主函数入口
    int t; // 定义整数t，用于存储测试数据的组数
    if (cin >> t) { // 读取测试组数，如果读取成功
        while (t--) { // 循环t次，处理每一组测试数据
            solve(); // 调用solve函数处理当前组数据
        }
    }
    return 0; // 程序正常结束，返回0
}
