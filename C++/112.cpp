#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

// 使用 long double 以获得更高的精度，虽然题目允许误差，但在计算过程中保持精度总是好的
// Use long double for higher precision
typedef long double ld;

// 定义棍子结构体，包含长度和数量
struct Stick {
    long long l; // 棍子长度
    long long a; // 棍子数量
};

// 计算等腰三角形面积的函数
// 参数 L 为腰长，B 为底边长
ld get_area(long long L, long long B) {
    // 检查能否构成三角形：底边必须大于0且小于两腰之和 (B < 2L)
    // 根据题意棍子长度均为正整数，所以 B > 0 总是成立（如果从列表中取）
    if (B <= 0 || B >= 2 * L) return -1.0;
    
    // 将长度转换为 long double 进行计算
    ld l_val = (ld)L;
    ld b_val = (ld)B;
    
    // 使用公式：Area = (B / 4) * sqrt(4 * L^2 - B^2)
    // 该公式由海伦公式推导得出，专门用于等腰三角形
    return 0.25 * b_val * sqrt(4.0L * l_val * l_val - b_val * b_val);
}

// 处理每组测试数据的函数
void solve() {
    int n;
    // 读取棍子的种类数量，如果读取失败则返回
    if (!(cin >> n)) return;
    
    // 用于存储输入的临时向量，pair<长度, 数量>
    vector<pair<long long, long long>> input_sticks(n);
    for (int i = 0; i < n; ++i) {
        // 读取每种棍子的长度和数量
        cin >> input_sticks[i].first >> input_sticks[i].second;
    }
    
    // 按照棍子长度进行排序，方便后续处理和二分查找
    sort(input_sticks.begin(), input_sticks.end());
    
    // 合并长度相同的棍子数量
    vector<Stick> sticks;
    if (n > 0) {
        // 初始化第一个元素
        sticks.push_back({input_sticks[0].first, input_sticks[0].second});
        for (int i = 1; i < n; ++i) {
            // 如果当前棍子长度与上一个相同，则累加数量
            if (input_sticks[i].first == sticks.back().l) {
                sticks.back().a += input_sticks[i].second;
            } else {
                // 否则添加新的棍子种类
                sticks.push_back({input_sticks[i].first, input_sticks[i].second});
            }
        }
    }
    
    // 提取所有不重复的长度，用于二分查找寻找最佳底边
    vector<long long> lengths;
    for (const auto& s : sticks) {
        lengths.push_back(s.l);
    }
    
    // 初始化最大面积为 -1.0，表示未找到有效三角形
    ld max_area = -1.0;
    
    // 遍历每一种棍子，尝试将其作为等腰三角形的腰
    for (int i = 0; i < sticks.size(); ++i) {
        long long L = sticks[i].l; // 当前腰长
        long long count = sticks[i].a; // 当前棍子数量
        
        // 只有当棍子数量至少为2时，才能作为腰（需要两根）
        if (count >= 2) {
            // 情况 1: 构成等边三角形 (底边 B = L)
            // 需要该长度的棍子至少有3根
            if (count >= 3) {
                ld area = get_area(L, L);
                // 如果面积更大，则更新最大面积
                if (area > max_area) max_area = area;
            }
            
            // 情况 2: 构成非等边等腰三角形 (底边 B != L)
            // 我们需要找到一个底边 B，使得 B < 2L 且 B != L
            // 使得面积最大化的理想底边长度约为 sqrt(2) * L
            ld target = sqrt(2.0L) * (ld)L;
            
            // 在现有长度中二分查找最接近 target 的位置
            // lower_bound 返回第一个大于等于 target 的元素的迭代器
            auto it = lower_bound(lengths.begin(), lengths.end(), (long long)floor(target));
            
            // 获取该迭代器在向量中的索引
            int idx = distance(lengths.begin(), it);
            
            // 检查 target 附近的几个长度作为底边的候选
            // 我们检查 idx 及其前后的元素，以确保覆盖最接近的值（可能是略小于或略大于 target 的值）
            for (int k = idx - 2; k <= idx + 2; ++k) {
                // 确保索引在有效范围内
                if (k >= 0 && k < lengths.size()) {
                    long long B = lengths[k];
                    
                    // 如果底边太长（>= 2L），则无法构成三角形，跳过
                    if (B >= 2 * L) continue; 
                    
                    // 如果底边长度等于腰长
                    if (B == L) {
                        // 这种情况已经在上面（情况 1）处理过了，这里跳过
                        continue;
                    } else {
                        // 如果底边不等于腰长，因为是从 lengths 中取的，
                        // 所以该长度的棍子数量至少为 1，可以作为底边
                        // 而腰的数量我们在循环外已经判断 >= 2，所以可以构成三角形
                        ld area = get_area(L, B);
                        if (area > max_area) max_area = area;
                    }
                }
            }
        }
    }
    
    // 输出结果
    if (max_area < 0) {
        // 如果没有找到合法的三角形，输出 -1
        cout << "-1" << endl;
    } else {
        // 否则输出最大面积，保留20位小数以确保精度符合题目要求
        cout << fixed << setprecision(20) << max_area << endl;
    }
}

int main() {
    // 优化 I/O 操作速度，因为数据量较大 (T <= 10^6, N 总和 <= 10^6)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    // 读取测试组数
    if (cin >> t) {
        while(t--) {
            solve(); // 处理每一组测试数据
        }
    }
    return 0;
}
