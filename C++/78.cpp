#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 定义粉丝结构体，存储粉丝的相关信息
struct Fan {
    int id;      // 粉丝编号（从1到n）
    int likes;   // 点赞数
    int favs;    // 收藏数
    long long score; // 支持力度，计算公式：点赞数 + 2 * 收藏数

    // 构造函数，初始化粉丝信息并计算支持力度
    Fan(int _id, int _likes, int _favs) : id(_id), likes(_likes), favs(_favs) {
        // 计算支持力度：每点赞一次+1，每收藏一次+2
        score = (long long)likes + 2LL * favs;
    }
};

// 比较函数1：用于筛选前k名粉丝
// 规则：优先按支持力度降序；若相同，按收藏数降序；若还相同，按编号升序
bool compareForSelection(const Fan& a, const Fan& b) {
    if (a.score != b.score) {
        return a.score > b.score; // 支持力度不同，大的排前面
    }
    if (a.favs != b.favs) {
        return a.favs > b.favs;   // 支持力度相同，收藏数多的排前面
    }
    return a.id < b.id;           // 前两者都相同，编号小的排前面
}

// 比较函数2：用于最后输出结果
// 规则：仅按照编号升序排列
bool compareForOutput(const Fan& a, const Fan& b) {
    return a.id < b.id; // 编号小的排前面
}

int main() {
    // 优化输入输出效率，防止因IO过慢导致超时
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; // n表示粉丝总数，k表示要送礼物的粉丝数
    if (cin >> n >> k) { // 读取n和k
        vector<Fan> fans; // 用于存储所有粉丝的容器
        fans.reserve(n);  // 预分配内存，避免多次重新分配

        // 循环读取每一位粉丝的信息
        for (int i = 1; i <= n; ++i) {
            int x, y; // x为点赞数，y为收藏数
            cin >> x >> y;
            // 将当前粉丝加入列表，编号为当前循环变量i
            fans.emplace_back(i, x, y);
        }

        // 第一步：对所有粉丝进行排序，以选出符合条件的前k名
        // 使用自定义的 compareForSelection 比较规则
        sort(fans.begin(), fans.end(), compareForSelection);

        // 第二步：取出前k名粉丝，存入新的容器
        vector<Fan> selectedFans;
        selectedFans.reserve(k);
        for (int i = 0; i < k; ++i) {
            selectedFans.push_back(fans[i]);
        }

        // 第三步：题目要求输出时按编号升序，所以对选中的k人再次排序
        sort(selectedFans.begin(), selectedFans.end(), compareForOutput);

        // 第四步：输出结果
        for (int i = 0; i < k; ++i) {
            cout << selectedFans[i].id; // 输出粉丝编号
            // 如果不是最后一个，输出空格分隔
            if (i < k - 1) {
                cout << " ";
            }
        }
        cout << endl; // 输出行尾换行符
    }

    return 0;
}