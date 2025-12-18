#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int main() {
    // 优化标准 I/O 操作的速度
    // Optimize the speed of standard I/O operations
    ios_base::sync_with_stdio(false);
    // 解除 cin 和 cout 的绑定
    // Untie cin from cout
    cin.tie(NULL);

    int x, y;
    // 从输入读取地图的行数 x 和列数 y
    // Read the number of rows x and columns y of the map from input
    if (!(cin >> x >> y)) return 0;

    // 创建一个字符串向量来存储地图网格，大小为 x 行
    // Create a vector of strings to store the map grid, sized for x rows
    vector<string> grid(x);
    // 循环读取每一行地图数据
    // Loop to read each line of map data
    for (int i = 0; i < x; ++i) {
        // 读取当前行的字符串（包含 '*' 和 '0'）
        // Read the string for the current row (containing '*' and '0')
        cin >> grid[i];
    }

    // 定义一个队列用于广度优先搜索 (BFS)，存储坐标对 (行, 列)
    // Define a queue for Breadth-First Search (BFS), storing coordinate pairs (row, col)
    queue<pair<int, int>> q;
    
    // 遍历整个网格，寻找位于边界的空地 '0'
    // Iterate through the entire grid to find empty spaces '0' on the boundary
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            // 判断当前格子是否位于地图的四个边界上（第一行、最后一行、第一列、最后一列）
            // Check if the current cell is on the four boundaries of the map (first row, last row, first column, last column)
            if (i == 0 || i == x - 1 || j == 0 || j == y - 1) {
                // 如果边界上的格子是空地 '0'，说明洪水可以从此进入
                // If the cell on the boundary is an empty space '0', flood can enter from here
                if (grid[i][j] == '0') {
                    // 将该格子标记为已淹没（修改为 '1'，防止重复访问）
                    // Mark this cell as flooded (change to '1' to prevent revisiting)
                    grid[i][j] = '1';
                    // 将该格子的坐标加入队列，作为 BFS 的起点
                    // Add the coordinates of this cell to the queue as a starting point for BFS
                    q.push({i, j});
                }
            }
        }
    }

    // 定义四个移动方向：上、下、左、右
    // Define four movement directions: up, down, left, right
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    // 当队列不为空时，继续进行 BFS 搜索
    // Continue BFS search while the queue is not empty
    while (!q.empty()) {
        // 获取队首的坐标
        // Get the coordinates from the front of the queue
        pair<int, int> curr = q.front();
        // 将队首元素移出队列
        // Remove the front element from the queue
        q.pop();
        // 获取当前行坐标
        // Get current row coordinate
        int cx = curr.first;
        // 获取当前列坐标
        // Get current column coordinate
        int cy = curr.second;

        // 尝试向四个方向（上、下、左、右）移动
        // Try to move in four directions (up, down, left, right)
        for (int k = 0; k < 4; ++k) {
            // 计算相邻格子的行坐标
            // Calculate adjacent cell's row coordinate
            int nx = cx + dx[k];
            // 计算相邻格子的列坐标
            // Calculate adjacent cell's column coordinate
            int ny = cy + dy[k];

            // 检查相邻格子是否在地图范围内
            // Check if the adjacent cell is within the map boundaries
            if (nx >= 0 && nx < x && ny >= 0 && ny < y) {
                // 如果相邻格子是空地 '0'，说明洪水可以流到这里
                // If the adjacent cell is an empty space '0', flood can flow here
                if (grid[nx][ny] == '0') {
                    // 将该格子标记为已淹没（修改为 '1'）
                    // Mark this cell as flooded (change to '1')
                    grid[nx][ny] = '1';
                    // 将新淹没的格子坐标加入队列
                    // Add the newly flooded cell coordinates to the queue
                    q.push({nx, ny});
                }
            }
        }
    }

    // 初始化安全空地计数器
    // Initialize safe empty space counter
    int safe_count = 0;
    // 再次遍历整个网格
    // Iterate through the entire grid again
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            // 如果格子仍然是 '0'，说明它没有被洪水淹没
            // If the cell is still '0', it means it was not flooded
            if (grid[i][j] == '0') {
                // 安全空地数量加一
                // Increment the safe empty space count
                safe_count++;
            }
        }
    }

    // 输出最终计算的安全空地总数
    // Output the final calculated total number of safe empty spaces
    cout << safe_count << endl;

    // 程序正常结束
    // Program ends successfully
    return 0;
}
