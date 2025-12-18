#include <iostream> // 引入输入输出流库
#include <vector>   // 引入向量容器库
#include <algorithm> // 引入算法库，用于排序
#include <cmath>    // 引入数学库，用于向下取整

using namespace std; // 使用标准命名空间

// 定义选手结构体
struct Applicant {
    int id;    // 报名号
    int score; // 笔试成绩
};

// 自定义排序比较函数
// 规则：成绩从高到低；成绩相同，报名号从小到大
bool compare(const Applicant &a, const Applicant &b) {
    if (a.score != b.score) { // 如果成绩不相等
        return a.score > b.score; // 按成绩降序排列
    }
    return a.id < b.id; // 成绩相等时，按报名号升序排列
}

int main() {
    int n, m; // 定义变量n（报名人数）和m（计划录取人数）
    if (!(cin >> n >> m)) return 0; // 读取n和m，如果读取失败则结束

    vector<Applicant> applicants(n); // 创建一个大小为n的选手向量

    // 循环读取每一位选手的信息
    for (int i = 0; i < n; ++i) {
        cin >> applicants[i].id >> applicants[i].score; // 读取报名号和成绩
    }

    // 计算面试名额 t = m * 150%，向下取整
    int t = floor(m * 1.5); 

    // 对选手进行排序
    sort(applicants.begin(), applicants.end(), compare);

    // 确保 t 不超过总人数 n (虽然题目通常保证 m 较小，但为了稳健性)
    if (t > n) t = n;

    // 获取第 t 名选手的成绩作为面试分数线 (数组下标为 t-1)
    // 注意：如果 n=0 这种情况需要处理，但题目保证 n>=5
    int line = applicants[t - 1].score; 

    // 统计实际进入面试的人数
    // 所有成绩大于等于分数线的选手都进入面试
    int count = 0; // 初始化计数器
    for (int i = 0; i < n; ++i) {
        if (applicants[i].score >= line) { // 如果当前选手成绩达标
            count++; // 计数加一
        } else {
            break; // 因为已排序，一旦不满足即可停止循环
        }
    }

    // 输出面试分数线和进入面试的总人数
    cout << line << " " << count << endl;

    // 按排序后的顺序输出进入面试的选手信息
    for (int i = 0; i < count; ++i) {
        cout << applicants[i].id << " " << applicants[i].score << endl; // 输出报名号和成绩
    }

    return 0; // 程序正常结束
}

