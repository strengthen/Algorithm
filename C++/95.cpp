#include <iostream> // 引入输入输出流库
#include <vector>   // 引入向量容器库
#include <string>   // 引入字符串库
#include <algorithm> // 引入算法库

using namespace std; // 使用标准命名空间

// 读取n*m的矩阵并将其转换为64位整数掩码
// 输入中'1'对应掩码中的1，'0'对应掩码中的0
unsigned long long readGrid(int n, int m) {
    unsigned long long mask = 0; // 初始化掩码为0
    for (int i = 0; i < n; ++i) { // 遍历行
        for (int j = 0; j < m; ++j) { // 遍历列
            char c; // 定义字符变量用于读取输入
            cin >> c; // 从输入流读取字符
            if (c == '1') { // 如果字符是'1'
                // 将二维坐标映射到一维位位置并设置对应位为1
                mask |= (1ULL << (i * m + j)); 
            }
        }
    }
    return mask; // 返回生成的掩码
}

int main() {
    // 优化I/O操作，提高读写速度
    ios_base::sync_with_stdio(false); // 关闭stdio同步
    cin.tie(NULL); // 解除cin与cout的绑定

    int n, m, q; // 定义变量n, m, q
    // 读取草地长、宽、计划数量
    if (cin >> n >> m >> q) { // 如果读取成功
        // 读取草地初始状态，生成障碍物掩码
        unsigned long long obstacle_mask = readGrid(n, m);

        // 计算全1掩码，用于后续取反操作时的位运算范围限制
        // 如果n*m=64，直接使用全1；否则计算对应位数的掩码
        unsigned long long full_mask = (n * m == 64) ? ~0ULL : ((1ULL << (n * m)) - 1);
        
        // 计算目标掩码：
        // 草地上为'1'（杂物）的位置，在目标中应为'0'（不放烟花）
        // 草地上为'0'（空地）的位置，在目标中应为'1'（放烟花）
        // 因此目标掩码是障碍物掩码按位取反后与全掩码做与运算
        unsigned long long target_mask = (~obstacle_mask) & full_mask;

        // 创建一个向量存储所有计划的掩码
        vector<unsigned long long> plans(q); 
        for (int i = 0; i < q; ++i) { // 遍历每一个计划
            plans[i] = readGrid(n, m); // 读取计划并转换为掩码
        }

        int min_plans = q + 1; // 初始化最少计划数量为q+1（一个不可能的大值）
        int best_subset = -1; // 初始化最佳子集状态为-1（未找到）

        // 遍历所有可能的计划组合（子集），用二进制位表示
        for (int i = 0; i < (1 << q); ++i) { 
            unsigned long long current_combined = 0; // 初始化当前组合的叠加效果为0
            int plan_cnt = 0; // 初始化当前组合使用的计划数量为0
            
            // 遍历每一位，检查对应计划是否被选中
            for (int j = 0; j < q; ++j) {
                if ((i >> j) & 1) { // 如果第j位是1，说明选择了第j个计划
                    current_combined |= plans[j]; // 将该计划的掩码叠加到当前效果中
                    plan_cnt++; // 增加计划计数
                }
            }

            // 检查叠加效果是否完全符合目标掩码
            if (current_combined == target_mask) {
                // 如果符合目标，且使用的计划数量比当前记录的最小值更少
                if (plan_cnt < min_plans) {
                    min_plans = plan_cnt; // 更新最少计划数量
                    best_subset = i; // 记录当前最佳子集状态
                }
            }
        }

        // 根据结果输出
        if (best_subset == -1) { // 如果没有找到符合条件的方案
            cout << -1 << endl; // 输出-1
        } else { // 如果找到了方案
            cout << min_plans << endl; // 输出使用的计划数量
            bool first = true; // 标记是否是输出的第一个编号
            for (int j = 0; j < q; ++j) { // 遍历每一位
                if ((best_subset >> j) & 1) { // 如果该计划在最佳方案中被选中
                    if (!first) cout << " "; // 如果不是第一个，先输出空格
                    cout << (j + 1); // 输出计划编号（从1开始）
                    first = false; // 标记不再是第一个
                }
            }
            cout << endl; // 输出换行
        }
    }
    return 0; // 程序正常结束
}
