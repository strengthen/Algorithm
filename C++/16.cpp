#include <iostream> // 引入输入输出流库
#include <vector> // 引入向量库，用于动态数组
#include <algorithm> // 引入算法库，用于max函数

using namespace std; // 使用标准命名空间

// 定义物品结构体，用于存储每个物品的信息
struct Item {
    int v; // 物品的价格（花费）
    int p; // 物品的重要度
    int val; // 物品的满意度（计算方式：价格 * 重要度）
};

int main() {
    int N, m; // 定义总预算N和物品总数m
    cin >> N >> m; // 从标准输入读取N和m

    // 题目指出所有价格都是10的倍数，因此将预算除以10
    // 这样做可以减小DP数组的大小，优化空间和时间复杂度
    N /= 10;

    // main_items数组存储主件信息，索引对应物品编号（1到m）
    Item main_items[65];
    // servs数组存储每个主件对应的附件列表，索引对应主件编号
    vector<Item> servs[65];

    // 初始化主件数组，将所有主件的价格置为0，作为是否存在的标记
    for (int i = 1; i <= m; ++i) main_items[i].v = 0;

    // 循环读取m个物品的详细信息
    for (int i = 1; i <= m; ++i) {
        int v, p, q; // 定义临时变量：价格v，重要度p，依赖关系q
        cin >> v >> p >> q; // 读取当前物品的v, p, q

        // 将价格除以10，与预算的处理保持一致
        int cost = v / 10;
        // 计算当前物品的满意度 = 价格 * 重要度
        int val = v * p;

        // 判断q的值来确定是主件还是附件
        if (q == 0) {
            // 如果q等于0，表示这是一个主件
            main_items[i].v = cost; // 记录主件价格
            main_items[i].p = p;    // 记录主件重要度
            main_items[i].val = val;// 记录主件满意度
        } else {
            // 如果q大于0，表示这是一个附件，q是其所属主件的编号
            // 将附件信息存入对应主件的附件列表中
            servs[q].push_back({cost, p, val});
        }
    }

    // 定义动态规划数组dp，dp[j]表示在预算为j时的最大满意度
    // 大小为N+1，初始值全为0
    vector<int> dp(N + 1, 0);

    // 遍历每一个物品编号，将其作为潜在的一组（主件+附件）进行处理
    for (int i = 1; i <= m; ++i) {
        // 如果当前编号不是主件（价格为0说明未被标记为主件），则跳过
        if (main_items[i].v == 0) continue;

        // 获取当前主件的信息
        Item master = main_items[i];
        // 获取当前主件的附件数量
        int s_size = servs[i].size();

        // 使用0-1背包问题的倒序遍历，防止同一组物品在同一轮预算中被重复使用
        // 只需要遍历到能买得起主件的预算即可
        for (int j = N; j >= master.v; --j) {
            // 每一个主件组有四种购买策略（互斥），我们需要在当前预算j下选择最优的一种

            // 策略1：只购买主件
            // 尝试更新dp[j]，比较当前值和（买主件后的剩余预算价值 + 主件价值）
            dp[j] = max(dp[j], dp[j - master.v] + master.val);

            // 策略2：购买主件 + 第1个附件（如果存在）
            if (s_size >= 1) {
                // 计算主件 + 第1个附件的总花费
                int cost1 = master.v + servs[i][0].v;
                // 计算主件 + 第1个附件的总满意度
                int val1 = master.val + servs[i][0].val;
                // 如果当前预算j足够购买主件和第1个附件
                if (j >= cost1) {
                    // 更新dp[j]取最大值
                    dp[j] = max(dp[j], dp[j - cost1] + val1);
                }
            }

            // 策略3：购买主件 + 第2个附件（如果存在）
            if (s_size >= 2) {
                // 计算主件 + 第2个附件的总花费
                int cost2 = master.v + servs[i][1].v;
                // 计算主件 + 第2个附件的总满意度
                int val2 = master.val + servs[i][1].val;
                // 如果当前预算j足够购买主件和第2个附件
                if (j >= cost2) {
                    // 更新dp[j]取最大值
                    dp[j] = max(dp[j], dp[j - cost2] + val2);
                }
            }

            // 策略4：购买主件 + 第1个附件 + 第2个附件（如果存在两个附件）
            if (s_size >= 2) {
                // 计算主件 + 两个附件的总花费
                int cost3 = master.v + servs[i][0].v + servs[i][1].v;
                // 计算主件 + 两个附件的总满意度
                int val3 = master.val + servs[i][0].val + servs[i][1].val;
                // 如果当前预算j足够购买全部
                if (j >= cost3) {
                    // 更新dp[j]取最大值
                    dp[j] = max(dp[j], dp[j - cost3] + val3);
                }
            }
        }
    }

    // 输出在预算N下的最大满意度
    cout << dp[N] << endl;

    return 0; // 程序结束
}




