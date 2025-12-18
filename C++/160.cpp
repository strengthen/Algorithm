#include <iostream> // 引入输入输出流库
using namespace std; // 使用标准命名空间
#include <queue> // 引入队列库
int n, m; // 定义变量n, m分别表示迷宫的行数和列数
char maze[1005][1005]; // 定义二维字符数组存储迷宫地图，大小略大于1000
bool keda[2][1005]; // 定义数组记录行列的可达性，keda[0]记录行，keda[1]记录列
void print(){ // 定义辅助打印函数
    for(int i=1;i<=n;++i){ // 遍历每一行
        for(int j=1;j<=m;++j) // 遍历每一列
            cout << maze[i][j]; // 输出当前位置字符
        cout << endl; // 换行
    }
}
#define _(a) a.first*1001+a.second // 定义宏，将坐标对(row, col)压缩为一个整数
pair<int, int> sou, des; // 定义起点sou和终点des
inline bool judge(int x, int y) { // 定义内联函数判断坐标是否合法且不为障碍物
    return x >= 1 && x <= n && y >= 1 && y <= m && maze[x][y] != '#'; // 检查边界及是否为障碍
}
int main() { // 主函数
    cin >> n >> m; // 输入行数和列数
    for (int i = 1; i <= n; ++i) { // 遍历行
        getchar(); // 读取行末换行符（或前一行的结束符）
        for (int j = 1; j <= m; ++j) { // 遍历列
            maze[i][j] = getchar(); // 读取迷宫字符
            if (maze[i][j] == 'S') // 如果是起点
                sou = {i, j}; // 记录起点坐标
            if (maze[i][j] == 'E') // 如果是终点
                des = {i, j}; // 记录终点坐标
        }
    }
    queue<int> q; // 定义队列用于BFS
    q.push(_(des)); // 将终点压缩后入队（反向BFS，从终点开始）
    keda[0][des.first] = true; // 标记终点所在行可达
    keda[1][des.second] = true; // 标记终点所在列可达
    maze[des.first][des.second] = '#'; // 将终点标记为障碍，避免重复访问
    while (!q.empty()) { // 当队列不为空
        int x = q.front() / 1001; // 获取当前点行坐标
        int y = q.front() % 1001; // 获取当前点列坐标
        if (x == sou.first || y == sou.second) { // 如果当前点与起点同在一行或同在一列
            cout << "YES" << endl; // 说明起点可以直接发射激光到达该连通块
            return 0; // 结束程序
        }
        keda[0][x] = true; // 标记当前行包含可达点
        keda[1][y] = true; // 标记当前列包含可达点
        q.pop(); // 弹出队首元素
        // 尝试向四个方向扩展，如果合法则入队并标记
        if (judge(x + 1, y)) // 下
            q.push((x + 1) * 1001 + y),maze[x+1][y]='#';
        if (judge(x - 1, y)) // 上
            q.push((x - 1) * 1001 + y),maze[x-1][y]='#';
        if (judge(x, y + 1)) // 右
            q.push(1001 * x + y + 1),maze[x][y+1]='#';
        if (judge(x, y - 1)) // 左
            q.push(1001 * x + y - 1),maze[x][y-1]='#';
    }
    q.push(_(sou)); // 将起点入队（正向BFS，从起点开始）
    maze[sou.first][sou.second] = '#'; // 标记起点已访问
    bool find = false; // 标记是否找到路径
    while (!q.empty()) { // 当队列不为空
        int x = q.front() / 1001; // 获取当前点行坐标
        int y = q.front() % 1001; // 获取当前点列坐标
        // 检查当前行或相邻行是否有终点可达点
        if ((keda[0][x]) || (x - 1 >= 1 && keda[0][x - 1]) || (x + 1 <= n &&
                keda[0][x + 1])) {
            cout << "YES" << endl; // 找到可行路径
            find = true; // 标记找到
            break; // 退出循环
        }
        // 检查当前列或相邻列是否有终点可达点
        if ((keda[1][y]) || (y - 1 >= 1 && keda[1][y - 1]) || (y + 1 <= m &&
                keda[1][y + 1])) {
            cout << "YES" << endl; // 找到可行路径
            find = true; // 标记找到
            break; // 退出循环
        }
        q.pop(); // 弹出队首元素
        // 尝试向四个方向扩展，如果合法则入队并标记
        if (judge(x + 1, y)) // 下
            q.push((x + 1) * 1001 + y),maze[x+1][y]='#';
        if (judge(x - 1, y)) // 上
            q.push((x - 1) * 1001 + y),maze[x-1][y]='#';
        if (judge(x, y + 1)) // 右
            q.push(1001 * x + y + 1),maze[x][y+1]='#';
        if (judge(x, y - 1)) // 左
            q.push(1001 * x + y - 1),maze[x][y-1]='#';
    }
    //print();
    if (find == false) // 如果未找到路径
        cout << "NO" << endl; // 输出NO
    return 0; // 程序结束
}
// 64 位输出请用 printf("%lld")
