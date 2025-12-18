#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 处理单个测试用例的函数
void solve() {
    int n, m;
    // 读取数组长度 n 和需要取出的元素数量 m
    cin >> n >> m;

    vector<int> a(n);
    // 读取数组元素
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // 创建一个副本以检查重复元素并计算排名
    vector<int> b = a;
    // 对副本进行排序以确定元素的顺序
    sort(b.begin(), b.end());

    // 从排序后的副本中移除重复元素以获取唯一元素
    auto last = unique(b.begin(), b.end());
    // 调整向量大小以移除未定义的元素
    b.erase(last, b.end());

    // 如果存在重复元素，数组大小将会减小
    // 严格递增或递减要求所有元素都是唯一的
    if (b.size() < n) {
        // 如果存在重复元素，输出 NO
        cout << "NO" << endl;
        return;
    }

    // 如果 m 为 1，我们选择 1 个元素。其余 n-1 个元素被排序。
    // 我们总是可以将 1 个元素插入到由唯一元素组成的排序数组中以保持顺序。
    if (m == 1) {
        cout << "YES" << endl;
        return;
    }

    // 将原始值转换为它们的排名（0 到 n-1）
    // 这简化了检查排序顺序中连续值的过程
    for (int i = 0; i < n; ++i) {
        // 在排序后的唯一数组中查找元素的位置
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    }

    // 我们需要找到一个长度至少为 m 的子数组，其具有连续的排名
    // 这是因为选定的子数组保持不变，而其余部分被排序。
    // 为了使最终数组严格递增，子数组必须严格递增
    // 并且其值必须填充所有值集合中的一个连续范围。

    int max_inc = 1; 
    // 连续递增排名的最大长度
    int max_dec = 1; 
    // 连续递减排名的最大长度

    int current_inc = 1;
    // 当前连续递增长度
    int current_dec = 1;
    // 当前连续递减长度

    // 遍历数组以查找最长的连续段
    for (int i = 1; i < n; ++i) {
        // 检查递增的连续排名（例如 1, 2, 3）
        if (a[i] == a[i - 1] + 1) {
            current_inc++;
        } else {
            current_inc = 1;
        }
        // 更新目前发现的最大递增长度
        max_inc = max(max_inc, current_inc);

        // 检查递减的连续排名（例如 3, 2, 1）
        if (a[i] == a[i - 1] - 1) {
            current_dec++;
        } else {
            current_dec = 1;
        }
        // 更新目前发现的最大递减长度
        max_dec = max(max_dec, current_dec);
    }

    // 如果我们找到了长度至少为 m 的有效子数组
    if (max_inc >= m || max_dec >= m) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    // 优化标准 I/O 操作以提高速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    // 读取测试用例数量
    cin >> t;
    // 处理每个测试用例
    while (t--) {
        solve();
    }
    return 0;
}
