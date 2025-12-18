#include <iostream> // 引入输入输出流库
#include <vector>   // 引入向量库
#include <algorithm> // 引入算法库，用于min函数

using namespace std; // 使用标准命名空间

int main() {
    // 优化输入输出效率
    ios_base::sync_with_stdio(false); // 关闭stdio同步
    cin.tie(NULL); // 解除cin与cout的绑定

    int n; // 定义变量n，表示货物种类数量
    long long x; // 定义变量x，表示网购平台一次性购买全部货物的花费，使用long long防止溢出
    
    // 使用while循环读取输入，以支持可能的多个测试用例
    while (cin >> n >> x) { 
        vector<int> a(n); // 定义向量a，存储供应商A的报价
        for (int i = 0; i < n; ++i) { // 循环读取供应商A对每种货物的报价
            cin >> a[i]; // 读取第i种货物在供应商A的价格
        }

        vector<int> b(n); // 定义向量b，存储供应商B的报价
        for (int i = 0; i < n; ++i) { // 循环读取供应商B对每种货物的报价
            cin >> b[i]; // 读取第i种货物在供应商B的价格
        }

        long long sum_individual = 0; // 定义变量sum_individual，用于累加分别购买每种货物的最小花费，使用long long防止溢出
        for (int i = 0; i < n; ++i) { // 遍历每种货物
            sum_individual += min(a[i], b[i]); // 选取供应商A和B中较便宜的价格累加到总花费中
        }

        // 比较分别购买的总花费和网购平台一次性购买的花费，取较小值
        // 注意：题目描述网购是一次性购买全部n种，所以直接比较sum_individual和x即可
        long long ans = min(sum_individual, x); // 计算最终的最小花费

        cout << ans << endl; // 输出最小花费
    }

    return 0; // 程序结束，返回0
}
