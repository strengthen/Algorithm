#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 最大可能的各位数字之和约为 9 * 100,000 = 900,000。
// 我们使用 1,000,005 以确保安全。
const int MAX_SUM = 1000005;
vector<bool> is_prime(MAX_SUM, true);

// 使用埃拉托斯特尼筛法预计算质数
void sieve() {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i < MAX_SUM; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j < MAX_SUM; j += i)
                is_prime[j] = false;
        }
    }
}

void solve() {
    string x;
    if (!(cin >> x)) return;

    // 计算x的各位数字之和
    int current_sum = 0;
    for (char c : x) {
        current_sum += c - '0';
    }

    // 我们寻找第一个 >= x 且各位数字之和为质数的数。
    // 由于质数很密集，我们不需要搜索很远。
    // 即使 x 很大，下一个满足条件的数通常也很近。
    // 区间 [x, 2x] 很大，所以我们保证结果在区间内。
    while (true) {
        if (is_prime[current_sum]) {
            cout << x << "\n";
            return;
        }

        // 将 x 加 1 并高效更新 current_sum
        int n = x.size();
        int i = n - 1;
        while (i >= 0) {
            if (x[i] < '9') {
                x[i]++;
                current_sum++; // 数字增加了 1
                break;
            } else {
                x[i] = '0';
                current_sum -= 9; // 数字从 9 变为 0，和减少 9
                i--;
            }
        }

        if (i < 0) {
            // x 全是 9 的情况，例如 999 -> 1000
            x.insert(0, "1");
            // 新的数字和是 1 (首位的 1) + 0 + ... + 0
            current_sum = 1;
        }
    }
}

int main() {
    // 优化 I/O 操作
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
