#include <iostream> // 引入输入输出流库
#include <vector>   // 引入向量容器库
#include <cmath>    // 引入数学库，用于sqrt函数
#include <algorithm>// 引入算法库

using namespace std; // 使用标准命名空间

// 判断一个数是否为素数的函数
bool isPrime(int num) { // 定义函数isPrime，参数为整数num
    if (num < 2) return false; // 如果num小于2，不是素数，返回false
    // 遍历从2到num的平方根的所有整数
    for (int i = 2; i <= sqrt(num); ++i) { // 循环变量i从2开始，直到sqrt(num)
        if (num % i == 0) return false; // 如果num能被i整除，说明不是素数，返回false
    }
    return true; // 如果循环结束都没有找到因数，说明是素数，返回true
}

// 匈牙利算法中的深度优先搜索，用于寻找增广路
// u: 当前考虑的奇数在odds数组中的下标
// odds: 存储所有奇数的向量
// evens: 存储所有偶数的向量
// vis: 记录偶数是否在本次查找中被访问过
// match: 记录偶数当前匹配到的奇数的下标
bool find(int u, const vector<int>& odds, const vector<int>& evens, vector<bool>& vis, vector<int>& match) { // 定义find函数
    // 遍历所有偶数
    for (int v = 0; v < evens.size(); ++v) { // 循环遍历evens向量的每一个索引v
        // 如果当前奇数和当前偶数的和是素数，并且该偶数在本次查找中未被访问过
        if (isPrime(odds[u] + evens[v]) && !vis[v]) { // 检查素数伴侣条件和访问状态
            vis[v] = true; // 标记该偶数已被访问，避免重复查找
            // 如果该偶数还没有匹配对象，或者它的匹配对象可以找到其他偶数（增广路）
            if (match[v] == -1 || find(match[v], odds, evens, vis, match)) { // 递归查找增广路
                match[v] = u; // 将该偶数匹配给当前奇数u
                return true; // 找到匹配或增广路，返回true
            }
        }
    }
    return false; // 如果遍历完所有偶数都无法匹配，返回false
}

int main() { // 主函数
    int n; // 定义变量n，用于存储输入的数字个数
    while (cin >> n) { // 循环读取输入，直到没有更多输入，处理多组测试数据
        vector<int> odds; // 定义向量odds，用于存储输入的奇数
        vector<int> evens; // 定义向量evens，用于存储输入的偶数
        for (int i = 0; i < n; ++i) { // 循环n次读取n个整数
            int val; // 定义临时变量val存储当前读取的数
            cin >> val; // 读取一个整数
            if (val % 2 == 1) { // 如果该数是奇数
                odds.push_back(val); // 将其加入奇数向量
            } else { // 否则（是偶数）
                evens.push_back(val); // 将其加入偶数向量
            }
        }

        // 如果奇数或偶数为空，则无法构成素数伴侣（除了1+1的情况，但通常题目数据按奇偶划分）
        if (odds.empty() || evens.empty()) { // 检查是否有一方为空
            cout << 0 << endl; // 输出0
            continue; // 继续处理下一组数据
        }

        // match数组存储每个偶数匹配到的奇数的索引，初始化为-1表示未匹配
        vector<int> match(evens.size(), -1); // 创建大小为偶数个数的match向量，初始值-1
        int count = 0; // 定义计数器，记录最大匹配数

        // 遍历每一个奇数，尝试为其寻找匹配的偶数
        for (int i = 0; i < odds.size(); ++i) { // 循环遍历odds向量
            // vis数组用于在每次寻找增广路时记录访问过的偶数
            vector<bool> vis(evens.size(), false); // 创建大小为偶数个数的vis向量，初始值false
            // 调用find函数尝试寻找匹配
            if (find(i, odds, evens, vis, match)) { // 如果找到了匹配
                count++; // 匹配数加1
            }
        }

        cout << count << endl; // 输出计算得到的最大匹配数
    }
    return 0; // 程序正常结束
}

