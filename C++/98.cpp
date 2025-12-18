#include <iostream> // 引入输入输出流库
#include <vector>   // 引入向量容器库
#include <numeric>  // 引入数值算法库

using namespace std; // 使用标准命名空间

int main() {
    // 优化输入输出效率，取消cin与stdin的同步
    ios_base::sync_with_stdio(false);
    // 取消cin与cout的绑定，进一步加快执行速度
    cin.tie(NULL);

    int n; // 定义变量n，用于存储数组长度
    // 读取数组长度，如果读取失败则退出程序
    if (!(cin >> n)) return 0;

    vector<long long> a(n); // 定义一个long long类型的向量a，大小为n
    long long total_sum = 0; // 定义total_sum变量，用于存储数组元素的总和
    int total_pos = 0; // 定义total_pos变量，用于统计数组中正数的个数

    // 循环读取数组元素
    for (int i = 0; i < n; ++i) {
        cin >> a[i]; // 读取第i个元素
        total_sum += a[i]; // 将元素值累加到总和
        if (a[i] > 0) { // 如果当前元素是正数
            total_pos++; // 正数计数加1
        }
    }

    // 如果总和不能被3整除，无法分成三个和相等的部分
    if (total_sum % 3 != 0) {
        cout << 0 << endl; // 输出0
        return 0; // 结束程序
    }
    
    // 如果正数总数少于3个，无法满足每个子数组至少有一个正数的条件
    if (total_pos < 3) {
        cout << 0 << endl; // 输出0
        return 0; // 结束程序
    }

    long long target = total_sum / 3; // 计算每个子数组的目标和
    long long ans = 0; // 初始化答案变量，用于记录方案数
    
    long long current_sum = 0; // 初始化当前前缀和
    int current_pos = 0; // 初始化当前前缀中正数的个数
    
    // tot_valid_first: 记录目前为止遇到的符合条件的“第一刀”切分点的数量
    // 符合条件的“第一刀”意味着：前缀和等于target，且前缀中包含至少一个正数
    long long tot_valid_first = 0;
    
    // bad_first: 记录在当前位置看来，那些“后面还没有出现正数”的合法第一刀的数量
    // 当我们在寻找第二刀时，中间那一段必须包含正数。
    // 如果从某个第一刀位置到当前第二刀位置之间没有正数，那么这个第一刀对当前第二刀来说是无效的（中间段无正数）。
    long long bad_first = 0;

    // 遍历数组寻找切分点。j代表第二刀的位置（即第二段的结束位置）。
    // 循环范围到n-2，保证第三段至少有一个元素（下标n-1）。
    for (int j = 0; j < n - 1; ++j) {
        current_sum += a[j]; // 更新当前前缀和
        if (a[j] > 0) { // 如果当前元素是正数
            current_pos++; // 更新当前前缀正数计数
            // 如果当前元素是正数，说明对于之前所有的第一刀切分点，
            // 它们的中间段（从第一刀后到当前j）现在都至少包含这一个正数了（即当前元素）。
            // 所以之前的那些暂时没有遇到正数的第一刀，现在都变成了有效的（对于当前的第二刀来说），
            // 因此“坏”的第一刀数量重置为0。
            bad_first = 0;
        }

        // 检查当前位置是否可以作为第二刀的切分点
        // 条件1: 前缀和等于2倍的目标和 (意味着前两段和为2*target，且总和是3*target，所以第三段和也是target)
        // 条件2: 剩余部分（第三段）必须包含至少一个正数 (总正数 - 当前正数 > 0)
        if (current_sum == 2 * target) {
            if (total_pos - current_pos > 0) {
                // 如果满足条件，则累加合法的方案数
                // 合法方案数 = 总的合法第一刀数量 - 中间段没有正数的第一刀数量
                ans += (tot_valid_first - bad_first);
            }
        }

        // 检查当前位置是否可以作为第一刀的切分点
        // 条件1: 前缀和等于目标和
        // 条件2: 第一段必须包含至少一个正数
        if (current_sum == target) {
            if (current_pos > 0) {
                tot_valid_first++; // 增加合法第一刀的计数
                bad_first++; // 新增加的这个第一刀，它的后面还没有出现正数（它是刚加进来的），所以暂时归为“坏”的
            }
        }
    }

    cout << ans << endl; // 输出最终的方案数

    return 0; // 程序结束
}
