#include <iostream> // 引入输入输出流库
#include <vector> // 引入向量容器库
#include <algorithm> // 引入算法库
#include <cmath> // 引入数学库

using namespace std; // 使用标准命名空间

// 定义结构体存储通道的信息
struct Channel {
    int id; // 通道的编号，即行号或列号
    int count; // 该通道能隔开的交头接耳的同学对数
};

// 比较函数，用于按count降序排序
bool compareCount(const Channel& a, const Channel& b) {
    return a.count > b.count; // 如果a的count大于b的count，返回true
}

// 比较函数，用于按id升序排序
bool compareId(const Channel& a, const Channel& b) {
    return a.id < b.id; // 如果a的id小于b的id，返回true
}

int main() {
    int n, m, k, l, d; // 定义变量n行，m列，k条横向通道，l条纵向通道，d对同学
    cin >> n >> m >> k >> l >> d; // 从标准输入读取n, m, k, l, d

    // 定义存储行通道信息的vector，大小为n
    // 行通道i表示第i行和第i+1行之间的通道，有效范围1到n-1
    vector<Channel> rows(n); 
    // 定义存储列通道信息的vector，大小为m
    // 列通道i表示第i列和第i+1列之间的通道，有效范围1到m-1
    vector<Channel> cols(m); 

    // 初始化行通道的id
    for (int i = 1; i < n; ++i) {
        rows[i].id = i; // 设置行通道编号
        rows[i].count = 0; // 初始化计数为0
    }

    // 初始化列通道的id
    for (int i = 1; i < m; ++i) {
        cols[i].id = i; // 设置列通道编号
        cols[i].count = 0; // 初始化计数为0
    }

    // 读取d对同学的坐标并统计
    for (int i = 0; i < d; ++i) {
        int x1, y1, x2, y2; // 定义两个同学的坐标(x为行，y为列)
        cin >> x1 >> y1 >> x2 >> y2; // 读取坐标输入
        
        if (x1 == x2) { // 如果行号相同，说明是左右相邻
            int c = min(y1, y2); // 隔开它们的纵向通道在列号较小值之后
            cols[c].count++; // 对应列通道计数加1
        } else { // 如果列号相同，说明是上下相邻
            int r = min(x1, x2); // 隔开它们的横向通道在行号较小值之后
            rows[r].count++; // 对应行通道计数加1
        }
    }

    // 将有效的行通道数据放入新的vector以便排序
    vector<Channel> validRows; // 存储有效行通道
    for (int i = 1; i < n; ++i) {
        validRows.push_back(rows[i]); // 将行通道加入列表
    }

    // 将有效的列通道数据放入新的vector以便排序
    vector<Channel> validCols; // 存储有效列通道
    for (int i = 1; i < m; ++i) {
        validCols.push_back(cols[i]); // 将列通道加入列表
    }

    // 按能隔开的同学对数降序排序，找出效果最好的通道
    sort(validRows.begin(), validRows.end(), compareCount);
    sort(validCols.begin(), validCols.end(), compareCount);

    // 取出前k个最好的行通道
    vector<Channel> resultRows; // 存储最终选择的行通道
    for (int i = 0; i < k; ++i) {
        resultRows.push_back(validRows[i]); // 添加到结果列表
    }

    // 取出前l个最好的列通道
    vector<Channel> resultCols; // 存储最终选择的列通道
    for (int i = 0; i < l; ++i) {
        resultCols.push_back(validCols[i]); // 添加到结果列表
    }

    // 题目要求输出按通道编号从小到大排序
    sort(resultRows.begin(), resultRows.end(), compareId);
    sort(resultCols.begin(), resultCols.end(), compareId);

    // 输出选定的横向通道编号
    for (int i = 0; i < k; ++i) {
        cout << resultRows[i].id; // 输出通道ID
        if (i < k - 1) cout << " "; // 两个数字之间用空格分隔
    }
    cout << endl; // 换行

    // 输出选定的纵向通道编号
    for (int i = 0; i < l; ++i) {
        cout << resultCols[i].id; // 输出通道ID
        if (i < l - 1) cout << " "; // 两个数字之间用空格分隔
    }
    cout << endl; // 换行

    return 0; // 程序正常结束
}
