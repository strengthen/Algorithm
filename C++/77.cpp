#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <vector>   // 引入向量库，用于存储动态数组
#include <stack>    // 引入栈库，用于模拟火车站
#include <algorithm> // 引入算法库，用于排序

using namespace std; // 使用标准命名空间

int n; // 定义全局变量n，表示火车的数量
vector<int> nums; // 定义向量nums，用于存储火车入站的顺序
vector<vector<int>> result; // 定义二维向量result，用于存储所有合法的出站顺序

// 深度优先搜索函数，用于寻找所有可能的出站顺序
// idx: 当前准备入站的火车在nums数组中的下标
// st: 当前火车站（栈）的状态，存储已入站但未出站的火车
// out: 当前已经出站的火车序列
void dfs(int idx, stack<int> st, vector<int> out) {
    // 递归终止条件：当已经出站的火车数量等于总数量n时
    if (out.size() == n) {
        result.push_back(out); // 将当前生成的完整出站序列添加到结果集中
        return; // 结束当前递归分支
    }

    // 搜索分支1：让火车出站
    // 如果车站（栈）不为空，可以选择让栈顶的火车出站
    if (!st.empty()) {
        stack<int> next_st = st; // 复制当前栈的状态，避免修改原栈
        vector<int> next_out = out; // 复制当前出站序列
        next_out.push_back(next_st.top()); // 将栈顶火车编号加入到出站序列中
        next_st.pop(); // 将该火车从栈中移除
        dfs(idx, next_st, next_out); // 递归调用，继续探索后续步骤
    }

    // 搜索分支2：让火车入站
    // 如果还有火车未入站（idx小于n），可以选择让下一辆火车入站
    if (idx < n) {
        stack<int> next_st = st; // 复制当前栈的状态
        next_st.push(nums[idx]); // 将下一辆火车压入栈中
        dfs(idx + 1, next_st, out); // 递归调用，入站下标加1，继续探索
    }
}

int main() { // 主函数
    // 使用while循环读取输入，以支持可能的连续多组输入
    while (cin >> n) { 
        nums.resize(n); // 根据输入的n调整存储入站顺序的数组大小
        for (int i = 0; i < n; i++) { // 循环读取每辆火车的编号
            cin >> nums[i]; // 将输入的编号存入nums数组
        }

        result.clear(); // 清空上一组数据的结果，确保本次计算不受影响
        stack<int> st; // 定义一个空栈，表示初始时车站为空
        vector<int> out; // 定义一个空向量，表示初始时没有火车出站
        
        // 从第0个火车开始，传入空栈和空的出站序列进行深度优先搜索
        dfs(0, st, out); 

        // 对所有找到的出站顺序进行排序，以满足题目要求的字典序输出
        sort(result.begin(), result.end()); 

        // 遍历结果集，输出每一个合法的出站顺序
        for (const auto& res : result) { // 使用范围for循环遍历result中的每一行
            for (int i = 0; i < n; i++) { // 遍历当前行中的每一个火车编号
                // 输出火车编号，如果是当前行最后一个数字则不加空格，否则加空格
                cout << res[i] << (i == n - 1 ? "" : " "); 
            }
            cout << endl; // 当前出站顺序输出完毕后换行
        }
    }
    return 0; // 程序正常结束
}

