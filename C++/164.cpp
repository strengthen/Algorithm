#include <iostream> // 引入输入输出流库，用于标准输入输出
#include <vector>   // 引入向量容器库，用于存储距离信息
#include <queue>    // 引入队列容器库，用于BFS广度优先搜索
#include <algorithm> // 引入算法库，用于使用min等函数

using namespace std; // 使用标准命名空间

int main() {
    // 优化C++标准流的I/O性能，加快输入输出速度
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k, a, b, x, y; // 声明变量：行星总数n，最大传送次数k，起点a，终点b，顺时针步长x，逆时针步长y
    // 循环读取输入数据，直到输入结束
    while (cin >> n >> k >> a >> b >> x >> y) {
        // 将1-based（从1开始）的编号转换为0-based（从0开始）
        a--; 
        b--;
        
        // 创建距离数组，初始化为-1，表示尚未到达（相当于无穷大）
        vector<int> dist(n, -1);
        queue<int> q; // 创建BFS队列
        
        dist[a] = 0; // 起点到自身的距离为0
        q.push(a);   // 将起点加入队列
        
        // 开始广度优先搜索
        while (!q.empty()) {
            int u = q.front(); // 获取队首元素
            q.pop(); // 弹出队首元素
            
            // 尝试顺时针移动x
            int v1 = (u + x) % n; // 计算顺时针移动后的位置
            if (dist[v1] == -1) { // 如果该位置未被访问
                dist[v1] = dist[u] + 1; // 更新距离
                q.push(v1); // 入队
            }
            
            // 尝试逆时针移动y
            // (u - y) 可能为负数，加上 n 确保取模结果为正
            int v2 = (u - y + n) % n; 
            if (dist[v2] == -1) { // 如果该位置未被访问
                dist[v2] = dist[u] + 1; // 更新距离
                q.push(v2); // 入队
            }
        }
        
        int ans = dist[b]; // 初始答案为不使用传送技能到达终点的最短距离
        
        // 如果允许使用传送技能（k > 0）
        // 由于传送操作（+n/2）与普通移动操作（+x, -y）在模n下是可交换的，
        // 且使用2次传送相当于原地不动（但消耗2单位时间），因此最优路径最多使用1次传送。
        // 我们只需比较“直接到达b”和“到达b的对面位置再传送一次”这两种情况。
        if (k > 0) {
            // 计算终点b关于圆心的对称点位置（即传送前的目标位置）
            int opposite = (b + n / 2) % n; 
            
            // 如果能到达对称点
            if (dist[opposite] != -1) {
                int tele_dist = dist[opposite] + 1; // 计算使用传送的总耗时（到达对称点时间 + 1次传送）
                // 如果不使用传送无法到达，或者使用传送更优，则更新答案
                if (ans == -1 || tele_dist < ans) {
                    ans = tele_dist;
                }
            }
        }
        
        cout << ans << endl; // 输出最终的最少时间
    }
    return 0; // 程序正常结束
}
