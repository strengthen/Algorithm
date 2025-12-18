#include <iostream> // 引入输入输出流库
#include <vector> // 引入向量容器库

using namespace std; // 使用标准命名空间

const int MAX_V = 1000005; // 定义数值范围常数，略大于10^6
int cnt_b[MAX_V]; // 定义全局数组记录数组b中每个数值的出现次数
int cnt_win[MAX_V]; // 定义全局数组记录当前滑动窗口中每个数值的出现次数

void solve() { // 定义处理单个测试用例的函数
    int n, m, k; // 声明整数变量n, m, k
    if (!(cin >> n >> m >> k)) return; // 输入n, m, k，如果输入失败直接返回
    
    vector<int> a(n); // 创建一个大小为n的向量a用来存储数组a
    for (int i = 0; i < n; ++i) { // 遍历数组a的每一个位置
        cin >> a[i]; // 从输入读取数组a的第i个元素
    } // 结束读取数组a的循环

    vector<int> b(m); // 创建一个大小为m的向量b用来存储数组b
    for (int i = 0; i < m; ++i) { // 遍历数组b的每一个位置
        cin >> b[i]; // 从输入读取数组b的第i个元素
        cnt_b[b[i]]++; // 统计b中该元素出现的次数，增加计数
    } // 结束读取数组b并统计的循环

    int match_count = 0; // 初始化当前窗口与数组b的匹配元素个数为0
    for (int i = 0; i < m; ++i) { // 初始化第一个滑动窗口，遍历前m个元素
        int val = a[i]; // 获取当前位置的元素值
        cnt_win[val]++; // 在窗口计数数组中增加该元素的计数
        if (cnt_win[val] <= cnt_b[val]) { // 如果当前窗口中该元素数量未超过b中该元素的总数
            match_count++; // 则该元素对匹配贡献有效，匹配计数加1
        } // 结束计数判断
    } // 结束第一个窗口的初始化循环

    int ans = 0; // 初始化满足条件的子段数量为0
    if (match_count >= k) { // 检查第一个窗口的匹配数是否满足至少k个
        ans++; // 如果满足，答案加1
    } // 结束对第一个窗口的判断

    for (int i = m; i < n; ++i) { // 开始向右滑动窗口，从第m个元素一直到第n-1个
        int out_val = a[i - m]; // 获取即将滑出窗口的元素值（最左侧元素）
        int in_val = a[i]; // 获取即将滑入窗口的元素值（当前元素）

        if (cnt_win[out_val] <= cnt_b[out_val]) { // 检查滑出元素是否贡献了匹配数
            match_count--; // 如果是，则匹配数减1
        } // 结束滑出元素的贡献判断
        cnt_win[out_val]--; // 将滑出元素在窗口计数中减1

        cnt_win[in_val]++; // 将滑入元素在窗口计数中加1
        if (cnt_win[in_val] <= cnt_b[in_val]) { // 检查滑入元素是否贡献了匹配数
            match_count++; // 如果是，则匹配数加1
        } // 结束滑入元素的贡献判断

        if (match_count >= k) { // 检查当前新窗口的匹配数是否满足至少k个
            ans++; // 如果满足，答案加1
        } // 结束对当前窗口的判断
    } // 结束滑动窗口的主循环

    cout << ans << "\n"; // 输出该测试用例的最终答案，并换行

    // 以下为清理全局数组的操作，为下一个测试用例做准备
    for (int x : b) { // 遍历数组b中出现过的所有元素
        cnt_b[x] = 0; // 将cnt_b中对应的计数重置为0
    } // 结束cnt_b的清理循环

    for (int i = n - m; i < n; ++i) { // 遍历当前窗口（即最后一个窗口）的所有元素
        cnt_win[a[i]] = 0; // 将cnt_win中对应的计数重置为0
    } // 结束cnt_win的清理循环
} // 结束solve函数

int main() { // 主程序的入口函数
    ios::sync_with_stdio(false); // 关闭C++标准流与C标准库的同步，提高IO性能
    cin.tie(nullptr); // 解除cin和cout的绑定，避免不必要的flush操作
    int t; // 声明变量t用于存储测试用例的数量
    if (cin >> t) { // 读取测试用例数量，确认读取成功
        while (t--) { // 循环执行t次，处理每一个测试用例
            solve(); // 调用solve函数处理当前测试用例
        } // 结束while循环
    } // 结束输入判断
    return 0; // 程序执行成功，返回0
} // 结束main函数
