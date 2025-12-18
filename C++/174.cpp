#include <iostream> // 引入输入输出流库
#include <string> // 引入字符串库
#include <vector> // 引入向量库
#include <algorithm> // 引入算法库

using namespace std; // 使用标准命名空间

// 解决单个测试用例的函数
void solve() {
    string s; // 定义字符串变量s存储输入
    cin >> s; // 从标准输入读取字符串s
    
    vector<int> buf; // 定义整数向量buf作为缓冲区
    int n = s.length(); // 获取字符串s的长度
    int next_idx = 0; // 定义next_idx指向原字符串中下一个待读入的字符索引
    
    // 初始化缓冲区，最多读入10个字符，因为大于10的索引无法移动到首位（数字最大为9）
    while (next_idx < n && buf.size() < 11) { // 保持缓冲区大小略大于10即可
        buf.push_back(s[next_idx] - '0'); // 将字符转换为数字并加入缓冲区
        next_idx++; // 移动索引
    }
    
    string res = ""; // 定义结果字符串
    // 循环n次，每次确定结果字符串的一位
    for (int k = 0; k < n; ++k) {
        int best_val = -1; // 初始化最佳值为-1
        int best_i = -1; // 初始化最佳索引为-1
        
        // 遍历缓冲区寻找最佳字符
        // 只需检查前10个，因为索引大于9时，消耗大于9，而数字最大为9，减去消耗后必小于0
        int limit = buf.size(); // 获取当前缓冲区大小
        if (limit > 10) limit = 10; // 限制最大检查范围为10
        
        for (int i = 0; i < limit; ++i) { // 遍历缓冲区前limit个元素
            // 只有当字符值大于等于移动距离时，才能移动到首位（题目要求操作数不为0）
            if (buf[i] >= i) {
                int val = buf[i] - i; // 计算移动到首位后的值
                // 贪心策略：选择移动后数值最大的；若数值相同，选择索引最小的（已经在循环顺序中隐含）
                if (val > best_val) { // 如果当前值大于已知最佳值
                    best_val = val; // 更新最佳值
                    best_i = i; // 更新最佳索引
                }
            }
        }
        
        // 题目保证一定能进行操作（最坏情况选第0个，消耗为0）
        // best_i 必定会被赋值，因为 i=0 时 buf[0] >= 0 恒成立
        res += to_string(best_val); // 将最佳值拼接到结果字符串
        
        // 从缓冲区中移除选中的元素
        buf.erase(buf.begin() + best_i); 
        
        // 如果原字符串还有剩余字符，补充进入缓冲区
        if (next_idx < n) { // 检查是否还有未读入字符
            buf.push_back(s[next_idx] - '0'); // 读入下一个字符
            next_idx++; // 索引后移
        }
    }
    cout << res << endl; // 输出最终结果字符串
}

int main() {
    // 优化输入输出效率
    ios::sync_with_stdio(false); // 关闭stdio同步
    cin.tie(nullptr); // 解绑cin和cout
    
    int t; // 定义变量t存储测试用例数量
    if (cin >> t) { // 读取t
        while (t--) { // 循环t次
            solve(); // 处理每个测试用例
        }
    }
    return 0; // 程序正常结束
}
