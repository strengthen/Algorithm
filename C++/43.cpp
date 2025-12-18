#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <vector>   // 引入向量容器库，用于存储迷宫和路径
#include <utility>  // 引入工具库，用于使用pair结构

using namespace std; // 使用标准命名空间，避免每次写std::

int h, w; // 定义全局变量h和w，分别表示迷宫的行数和列数
vector<vector<int>> maze; // 定义二维向量maze，用于存储迷宫的布局（0为空，1为墙）
vector<pair<int, int>> path; // 定义路径向量，存储从起点到终点的坐标对

// 深度优先搜索（DFS）函数，参数x和y为当前所在的坐标
bool dfs(int x, int y) {
    path.push_back(make_pair(x, y)); // 将当前坐标(x, y)加入到路径记录中
    maze[x][y] = 1; // 将当前位置标记为1（视为墙），防止走回头路（标记已访问）

    // 判断是否到达终点：坐标为(h-1, w-1)
    if (x == h - 1 && y == w - 1) {
        return true; // 如果到达终点，返回true表示找到路径
    }

    // 定义四个移动方向的偏移量：上(-1,0), 下(1,0), 左(0,-1), 右(0,1)
    int dx[4] = {-1, 1, 0, 0}; // 行坐标的变化量
    int dy[4] = {0, 0, -1, 1}; // 列坐标的变化量

    // 尝试向四个方向移动
    for (int i = 0; i < 4; ++i) { // 遍历四个方向
        int nx = x + dx[i]; // 计算下一个位置的行坐标
        int ny = y + dy[i]; // 计算下一个位置的列坐标

        // 检查下一个位置是否在迷宫范围内，且是否为空方格（0）
        if (nx >= 0 && nx < h && ny >= 0 && ny < w && maze[nx][ny] == 0) {
            if (dfs(nx, ny)) return true; // 递归调用DFS，如果后续路径能到达终点，则返回true
        }
    }

    path.pop_back(); // 如果四个方向都走不通，进行回溯：从路径中移除当前点
    return false; // 返回false表示从当前点出发无法到达终点
}

int main() {
    // 循环读取输入，直到没有更多输入（处理可能的多组测试数据）
    while (cin >> h >> w) {
        maze.assign(h, vector<int>(w)); // 根据输入的h和w调整迷宫的大小
        path.clear(); // 清空上一组数据的路径记录

        // 双重循环读取迷宫的布局数据
        for (int i = 0; i < h; ++i) { // 遍历每一行
            for (int j = 0; j < w; ++j) { // 遍历每一列
                cin >> maze[i][j]; // 输入当前格子的值（0或1）
            }
        }

        dfs(0, 0); // 从起点(0, 0)开始执行深度优先搜索

        // 遍历并输出找到的路径
        for (const auto& p : path) { // 遍历path向量中的每一个坐标对p
            cout << "(" << p.first << "," << p.second << ")" << endl; // 按照题目要求的格式输出坐标，如(0,0)
        }
    }
    return 0; // 程序正常结束
}

