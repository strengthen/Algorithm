#include <iostream> // 引入输入输出流库
#include <vector> // 引入向量容器库
#include <algorithm> // 引入算法库

using namespace std; // 使用标准命名空间

const int MAXN = 200005; // 定义最大数组大小，根据题目范围设定
int a[MAXN]; // 定义数组a用于存储输入的整数序列
int cnt[MAXN]; // 定义计数数组cnt用于记录当前区间内每个数字出现的次数

int main() { // 主函数入口
    ios::sync_with_stdio(false); // 关闭stdio同步，提高cin/cout速度
    cin.tie(0); // 解除cin和cout的绑定，进一步提高输入输出效率

    int n; // 定义变量n，表示数组元素数量
    cin >> n; // 从标准输入读取n

    for (int i = 1; i <= n; ++i) { // 循环读取n个整数
        cin >> a[i]; // 将输入的整数存入数组a，下标从1开始
    }

    int l = 1; // 定义左指针l，初始化为1
    int maxLen = 0; // 定义最大区间长度maxLen，初始化为0
    vector<pair<int, int>> ans; // 定义向量ans用于存储结果区间（左端点和右端点）

    for (int r = 1; r <= n; ++r) { // 使用右指针r从1遍历到n
        cnt[a[r]]++; // 将当前右指针指向的元素加入区间，该元素计数加1
        
        while (cnt[a[r]] > 1) { // 如果当前元素在区间内出现次数大于1，说明有重复
            cnt[a[l]]--; // 将左指针指向的元素移出区间，该元素计数减1
            l++; // 左指针向右移动一位，缩小窗口直到没有重复
        }

        int curLen = r - l + 1; // 计算当前满足条件的（无重复元素）区间长度
        if (curLen > maxLen) { // 如果当前长度大于已记录的最大长度
            maxLen = curLen; // 更新最大长度
            ans.clear(); // 清空之前的解，因为找到了更长的区间
            ans.push_back({l, r}); // 将当前区间加入结果列表
        } else if (curLen == maxLen) { // 如果当前长度等于最大长度
            ans.push_back({l, r}); // 将当前区间加入结果列表
        }
    }

    cout << ans.size() << "\n"; // 输出满足条件的区间数量
    for (const auto& p : ans) { // 遍历结果列表
        cout << p.first << " " << p.second << "\n"; // 输出每个区间的左端点和右端点
    }

    return 0; // 程序正常结束
}
