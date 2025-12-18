#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 定义全局变量，方便在递归函数中访问
// n: 输入的整数，表示排列数字的范围 1 到 n
int n;
// path: 用于存储当前生成的排列
vector<int> path;
// used: 用于标记数字是否已经被使用过，索引 i 对应数字 i
// st: 状态数组，true表示已使用，false表示未使用
// 由于 n 最大为 9，数组大小开到 10 即可
bool st[10];

// 深度优先搜索函数，u 表示当前枚举到第几位（从 0 开始计数）
void dfs(int u) {
    // 递归边界：如果当前已经填满了 n 位数字
    if (u == n) {
        // 遍历 path 数组，输出当前排列
        for (int i = 0; i < n; i++) {
            // 输出当前位置的数字，并在后面加上空格
            cout << path[i] << " ";
        }
        // 每输出完一个排列后换行
        cout << endl;
        // 结束当前递归分支
        return;
    }

    // 从 1 到 n 遍历所有可能的数字
    for (int i = 1; i <= n; i++) {
        // 如果数字 i 还没有被使用过
        if (!st[i]) {
            // 将数字 i 放入当前排列的末尾
            path.push_back(i);
            // 标记数字 i 为已使用
            st[i] = true;
            
            // 递归处理下一位
            dfs(u + 1);
            
            // 回溯：恢复现场
            // 将数字 i 标记为未使用
            st[i] = false;
            // 将数字 i 从当前排列末尾移除
            path.pop_back();
        }
    }
}

int main() {
    // 优化输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    // 读取输入整数 n
    while(cin >> n) {
        // 初始化状态数组，确保所有数字初始都未被使用
        // 虽然全局变量默认初始化为 false，但多组数据时需要重置（题目虽未明确多组，但习惯性处理）
        for(int i = 1; i <= 9; i++) st[i] = false;
        path.clear();

        // 从第 0 位开始进行深度优先搜索
        dfs(0);
    }

    return 0;
}
