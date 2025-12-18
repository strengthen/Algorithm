#include <iostream> // 引入输入输出流库
#include <vector>   // 引入向量容器库
#include <queue>    // 引入队列容器库
#include <string>   // 引入字符串库

using namespace std; // 使用标准命名空间

// 定义一个结构体来表示迷宫中的坐标点
struct Point {
    int x; // 行坐标
    int y; // 列坐标
};

int main() {
    int n, m; // 定义两个整型变量n和m，分别表示迷宫的行数和列数
    
    // 从标准输入读取n和m的值
    if (cin >> n >> m) { 
        // 创建一个字符串向量来存储迷宫的地图，大小为n
        vector<string> maze(n);
        
        // 循环读取每一行的迷宫地图数据
        for (int i = 0; i < n; ++i) {
            cin >> maze[i]; // 读取一行字符串，包含'.'和'#'
        }

        // 创建一个二维布尔向量visited，用于记录每个格子是否被访问过
        // 初始化大小为n行m列，所有值为false（未访问）
        vector<vector<bool>> visited(n, vector<bool>(m, false));

        // 定义方向数组，分别表示上、下、左、右四个移动方向
        // dx表示行坐标的变化，dy表示列坐标的变化
        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        // 创建一个队列用于广度优先搜索（BFS）
        queue<Point> q;

        // 将起点坐标(0, 0)加入队列，对应题目中的(1, 1)
        q.push({0, 0});
        // 将起点标记为已访问
        visited[0][0] = true;

        // 定义一个布尔变量flag，标记是否能够到达终点，初始为false
        bool canReach = false;

        // 当队列不为空时，继续循环进行搜索
        while (!q.empty()) {
            // 获取队首元素，即当前所在的坐标点
            Point curr = q.front();
            // 将队首元素出队
            q.pop();

            // 判断当前坐标是否为终点坐标(n-1, m-1)
            // 题目中的终点是(n, m)，对应数组下标(n-1, m-1)
            if (curr.x == n - 1 && curr.y == m - 1) {
                canReach = true; // 标记已找到路径
                break; // 跳出循环
            }

            // 尝试向四个方向移动
            for (int i = 0; i < 4; ++i) {
                // 计算移动后的新行坐标
                int nx = curr.x + dx[i];
                // 计算移动后的新列坐标
                int ny = curr.y + dy[i];

                // 检查新坐标是否在迷宫范围内
                // 行坐标需在[0, n-1]之间，列坐标需在[0, m-1]之间
                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    // 检查新坐标是否是空地（'.'）且未被访问过
                    if (maze[nx][ny] == '.' && !visited[nx][ny]) {
                        // 将新坐标标记为已访问，防止重复处理
                        visited[nx][ny] = true;
                        // 将新坐标加入队列，作为下一步搜索的起点
                        q.push({nx, ny});
                    }
                }
            }
        }

        // 根据搜索结果输出相应的信息
        if (canReach) {
            cout << "Yes" << endl; // 如果能到达终点，输出Yes
        } else {
            cout << "No" << endl; // 如果不能到达终点，输出No
        }
    }
    
    return 0; // 程序正常结束
}
