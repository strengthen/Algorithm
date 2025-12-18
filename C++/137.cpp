#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <climits>

using namespace std;

// 定义无穷大常量，用于初始化最小值和最大值
// Define infinity constants for initializing min and max values
const long long INF_LL = 1e18;

void solve() {
    int n;
    long long k;
    if (!(cin >> n >> k)) return;

    vector<long long> a(n + 1);
    long long total_sum = 0;
    // 读取数组元素，使用1-based索引
    // Read array elements, using 1-based indexing
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        total_sum += a[i];
    }

    // 如果k为1，总和不变，直接输出
    // If k is 1, the total sum doesn't change, output directly
    if (k == 1) {
        cout << total_sum << endl;
        return;
    }

    // 计算前缀和
    // Calculate prefix sums
    vector<long long> P(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        P[i] = P[i - 1] + a[i];
    }

    // 预处理数组
    // Precompute arrays
    // L_max[i]: 1..i 范围内的最大子数组和
    // L_max[i]: Max subarray sum in range 1..i
    // L_min[i]: 1..i 范围内的最小子数组和
    // L_min[i]: Min subarray sum in range 1..i
    // R_max[i]: i..n 范围内的最大子数组和
    // R_max[i]: Max subarray sum in range i..n
    // R_min[i]: i..n 范围内的最小子数组和
    // R_min[i]: Min subarray sum in range i..n
    
    vector<long long> L_max(n + 2, -INF_LL), L_min(n + 2, INF_LL);
    vector<long long> R_max(n + 2, -INF_LL), R_min(n + 2, INF_LL);

    // 计算 L_max 和 L_min
    // Calculate L_max and L_min
    long long cur_max = -INF_LL, cur_min = INF_LL;
    long long running_max = 0, running_min = 0; // Kadane's current sums
    
    // 注意：Kadane算法中，如果之前的sum<0，则丢弃。对于最小sum，如果之前的sum>0则丢弃。
    // Note: In Kadane's, if previous sum < 0, discard. For min sum, if previous sum > 0 discard.
    // 但这里我们需要的是1..i范围内的最优值，所以是一个前缀最值问题。
    // But here we need the optimal value in range 1..i, so it's a prefix extrema problem.
    
    long long temp_max = -INF_LL; // 当前以此元素结尾的最大子数组和
    long long temp_min = INF_LL;  // 当前以此元素结尾的最小子数组和
    
    for (int i = 1; i <= n; ++i) {
        // 更新以此元素结尾的最大/最小子数组和
        temp_max = max(a[i], temp_max + a[i]);
        temp_min = min(a[i], temp_min + a[i]);
        
        // 更新前缀最大/最小子数组和
        cur_max = max(cur_max, temp_max);
        cur_min = min(cur_min, temp_min);
        
        L_max[i] = cur_max;
        L_min[i] = cur_min;
    }

    // 计算 R_max 和 R_min
    // Calculate R_max and R_min
    cur_max = -INF_LL; cur_min = INF_LL;
    temp_max = -INF_LL; temp_min = INF_LL;
    
    for (int i = n; i >= 1; --i) {
        temp_max = max(a[i], temp_max + a[i]);
        temp_min = min(a[i], temp_min + a[i]);
        
        cur_max = max(cur_max, temp_max);
        cur_min = min(cur_min, temp_min);
        
        R_max[i] = cur_max;
        R_min[i] = cur_min;
    }

    // L_suf_max[i]: 以i结尾的最大后缀和
    // L_suf_max[i]: Max suffix sum ending at i
    // R_pre_max[i]: 以i开始的最大前缀和
    // R_pre_max[i]: Max prefix sum starting at i
    vector<long long> L_suf_max(n + 2, -INF_LL), L_suf_min(n + 2, INF_LL);
    vector<long long> R_pre_max(n + 2, -INF_LL), R_pre_min(n + 2, INF_LL);
    
    // 初始化边界，用于空扩展的情况（如果不选扩展，相当于值为0）
    // Initialize boundaries for empty extension cases (value 0 if no extension chosen)
    L_suf_max[0] = 0; L_suf_min[0] = 0;
    R_pre_max[n + 1] = 0; R_pre_min[n + 1] = 0;
    
    // 实际上 L_suf_max[i] 并不需要包含0..i的扫描，它只是以i结尾的一个非空区间。
    // Actually L_suf_max[i] just needs to be a non-empty interval ending at i.
    // L_suf[i] = P[i] - min(P[0]...P[i-1]) for max
    
    long long min_P = 0; // min P[j] for 0 <= j < i
    long long max_P = 0; // max P[j] for 0 <= j < i
    
    for (int i = 1; i <= n; ++i) {
        L_suf_max[i] = P[i] - min_P;
        L_suf_min[i] = P[i] - max_P;
        
        min_P = min(min_P, P[i]);
        max_P = max(max_P, P[i]);
    }
    
    // 对于右侧前缀和
    // For right-side prefix sums
    // R_pre[i] is sum(i..j) = P[j] - P[i-1].
    // We need max/min over j >= i.
    vector<long long> suff_max_P(n + 2, -INF_LL);
    vector<long long> suff_min_P(n + 2, INF_LL);
    
    suff_max_P[n] = P[n];
    suff_min_P[n] = P[n];
    for(int i = n - 1; i >= 1; --i) {
        suff_max_P[i] = max(suff_max_P[i+1], P[i]);
        suff_min_P[i] = min(suff_min_P[i+1], P[i]);
    }
    
    for (int i = 1; i <= n; ++i) {
        // Range i..j, max j >= i. suff_max_P[i] covers P[i]...P[n]
        R_pre_max[i] = suff_max_P[i] - P[i-1];
        R_pre_min[i] = suff_min_P[i] - P[i-1];
    }

    long long best_val = (k > 1) ? -INF_LL : INF_LL;

    if (k > 1) {
        // 小龙想最大化，小蛇想最小化
        // Dragon wants to maximize, Snake wants to minimize
        
        // 情况A：不相交区间
        // Case A: Disjoint intervals
        // 1. Dragon在左，Snake在右
        // 1. Dragon Left, Snake Right
        for (int i = 1; i < n; ++i) {
            long long snake_part = min(0LL, R_min[i+1]);
            long long dragon_part = L_max[i];
            best_val = max(best_val, dragon_part + snake_part);
        }
        // 2. Snake在左，Dragon在右
        // 2. Snake Left, Dragon Right
        for (int i = 1; i < n; ++i) {
            long long snake_part = min(0LL, L_min[i]);
            long long dragon_part = R_max[i+1];
            best_val = max(best_val, dragon_part + snake_part);
        }
        
        // 情况B：重叠/包围区间
        // Case B: Overlapping/Enclosing intervals
        // Maximize: (P[b] + min(0, R_pre_min[b+1])) - (P[a-1] - min(0, L_suf_min[a-1]))
        // iterate b, keep track of min termA
        
        long long min_termA = INF_LL;
        // termA[a] depends on a-1. let's iterate j = a-1 from 0 to n-1.
        // But b starts at a. So for a fixed b, we need min termA for 1 <= a <= b => 0 <= a-1 <= b-1.
        
        min_termA = P[0] - min(0LL, L_suf_min[0]); // For a=1, a-1=0.
        
        for (int b = 1; b <= n; ++b) {
            long long termB = P[b] + min(0LL, R_pre_min[b+1]);
            
            best_val = max(best_val, termB - min_termA);
            
            // Prepare min_termA for next step (b+1 can accept a up to b+1)
            // So we update min_termA with a=b+1 case, i.e., index b
            long long current_termA_candidate = P[b] - min(0LL, L_suf_min[b]);
            min_termA = min(min_termA, current_termA_candidate);
        }

    } else {
        // k < 1
        // 小龙想最大化结果 -> 需要最小化 Union Sum
        // Dragon wants to maximize result -> Needs to minimize Union Sum
        // 小蛇想最小化结果 -> 需要最大化 Union Sum
        // Snake wants to minimize result -> Needs to maximize Union Sum
        // 目标：Find min (Union Sum) where Snake plays Maximize.
        
        // 情况A：不相交
        // Case A: Disjoint
        // 1. Dragon Left, Snake Right
        for (int i = 1; i < n; ++i) {
            long long snake_part = max(0LL, R_max[i+1]);
            long long dragon_part = L_min[i];
            best_val = min(best_val, dragon_part + snake_part);
        }
        // 2. Snake Left, Dragon Right
        for (int i = 1; i < n; ++i) {
            long long snake_part = max(0LL, L_max[i]);
            long long dragon_part = R_min[i+1];
            best_val = min(best_val, dragon_part + snake_part);
        }
        
        // 情况B：重叠/包围
        // Case B: Overlap
        // Minimize: (P[b] + max(0, R_pre_max[b+1])) - (P[a-1] - max(0, L_suf_max[a-1]))
        
        long long max_termA = -INF_LL;
        
        max_termA = P[0] - max(0LL, L_suf_max[0]); // For a=1
        
        for (int b = 1; b <= n; ++b) {
            long long termB = P[b] + max(0LL, R_pre_max[b+1]);
            
            best_val = min(best_val, termB - max_termA);
            
            long long current_termA_candidate = P[b] - max(0LL, L_suf_max[b]);
            max_termA = max(max_termA, current_termA_candidate);
        }
    }

    // 最终结果 = S + (k-1) * best_val
    // Final result = S + (k-1) * best_val
    cout << total_sum + (k - 1) * best_val << endl;
}

int main() {
    // 提高IO效率
    // Improve IO efficiency
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
