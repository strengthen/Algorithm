#include <iostream> // 引入输入输出流库，用于标准输入输出操作
#include <vector>   // 引入向量容器头文件，用于存储动态数组
#include <string>   // 引入字符串头文件，用于处理每一行的地图数据
#include <queue>    // 引入队列头文件，用于广度优先搜索算法

using namespace std; // 使用标准命名空间，方便直接使用标准库元素

// 定义一个结构体Point用来保存坐标位置
struct Point {      // 结构体Point定义开始
    int x;          // 成员变量x，表示行坐标
    int y;          // 成员变量y，表示列坐标
};                  // 结构体Point定义结束

int main() {        // 主函数程序的入口点
    int N;          // 定义一个整型变量N，表示地图的边长
    while (cin >> N) { // 循环读取N的值，直到输入结束
        vector<string> grid(N); // 创建一个大小为N的字符串向量，存储地图
        for (int i = 0; i < N; ++i) { // 循环遍历每一行
            cin >> grid[i]; // 读取每一行的地图字符数据
        }                   // 读取循环结束

        // 创建一个二维布尔数组visited，标记格子是否被访问过，注意尖括号间有空格
        vector<vector<bool> > visited(N, vector<bool>(N, false)); // 初始化全为false
        int ans = 0; // 定义变量ans，用于统计完全被淹没的区域数量

        for (int i = 0; i < N; ++i) { // 外层循环，遍历地图的每一行
            for (int j = 0; j < N; ++j) { // 内层循环，遍历地图的每一列
                // 如果当前格子是陆地('#')并且没有被访问过
                if (grid[i][j] == '#' && !visited[i][j]) { // 发现一个新的陆地连通区域
                    bool is_survived = false; // 标记该区域是否能幸存，初始化为false
                    queue<Point> q; // 创建一个队列用于BFS搜索，注意尖括号间有空格
                    Point start; // 定义起始点变量
                    start.x = i; // 设置起始点的行坐标
                    start.y = j; // 设置起始点的列坐标
                    q.push(start); // 将起始点加入队列
                    visited[i][j] = true; // 标记起始点为已访问

                    while (!q.empty()) { // 当队列不为空时，继续搜索
                        Point cur = q.front(); // 获取队列头部的元素
                        q.pop(); // 将队列头部的元素弹出

                        bool cell_safe = true; // 标记当前格子是否安全（不会被淹没）
                        int dx[] = {-1, 1, 0, 0}; // 定义行方向的偏移量数组
                        int dy[] = {0, 0, -1, 1}; // 定义列方向的偏移量数组

                        for (int k = 0; k < 4; ++k) { // 遍历上、下、左、右四个方向
                            int nx = cur.x + dx[k]; // 计算相邻格子的行坐标
                            int ny = cur.y + dy[k]; // 计算相邻格子的列坐标

                            // 检查相邻格子是否是水。题目保证边界是水，所以陆地周围一定有坐标
                            // 如果相邻格子是水('.')，则当前格子会被淹没
                            if (grid[nx][ny] == '.') { // 判断邻居是否为水
                                cell_safe = false; // 当前格子标记为不安全
                            } // 结束水域判断

                            // 接下来处理连通性，将相邻的陆地加入队列
                            if (nx >= 0 && nx < N && ny >= 0 && ny < N) { // 检查坐标是否在合法范围内
                                if (grid[nx][ny] == '#' && !visited[nx][ny]) { // 如果是陆地且未被访问
                                    visited[nx][ny] = true; // 标记为已访问
                                    Point next_p; // 定义下一个点
                                    next_p.x = nx; // 设置行坐标
                                    next_p.y = ny; // 设置列坐标
                                    q.push(next_p); // 加入队列
                                } // 结束陆地判断
                            } // 结束边界判断
                        } // 结束方向遍历循环

                        if (cell_safe) { // 如果当前格子是安全的（四周都是陆地）
                            is_survived = true; // 则整个区域被判定为幸存
                        } // 结束幸存判断
                    } // 结束while循环，当前连通区域搜索完毕

                    if (!is_survived) { // 如果该区域没有幸存（所有格子都被淹没）
                        ans++; // 计数器加1
                    } // 结束统计判断
                } // 结束新区域判断
            } // 结束列遍历
        } // 结束行遍历
        cout << ans << endl; // 输出最终的统计结果
    } // 结束输入循环
    return 0; // 程序正常退出
} // 主函数结束
