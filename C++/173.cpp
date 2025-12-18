#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // 优化输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    // 读取药剂种类数量
    if (!(cin >> n)) return 0;

    // 使用vector存储每种红色药剂的价格，下标从1开始，使用long long防止溢出（虽然题目范围int可能够用）
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        // 读取第i种红色药剂的价格
        cin >> a[i];
    }

    long long total_cost = 0;
    // 接下来n行，依次读取每种药剂的合成配方
    for (int i = 1; i <= n; ++i) {
        int b, c;
        // 读取合成蓝色版本第i种药剂所需的两种红色药剂编号b和c
        cin >> b >> c;
        
        // 方案一：直接购买红色版本的第i种药剂
        long long cost_red = a[i];
        
        // 方案二：合成蓝色版本的第i种药剂
        // 规则：消耗一瓶红色b和一瓶红色c。因为红色药剂只能购买，所以成本是 a[b] + a[c]
        long long cost_blue = a[b] + a[c];
        
        // 或者是红色的，或者是蓝色的，只要拥有其中一种即可，取最小代价
        total_cost += min(cost_red, cost_blue);
    }

    // 输出获得n种不同药剂所需支付的最小金币数
    cout << total_cost << endl;

    return 0;
}
