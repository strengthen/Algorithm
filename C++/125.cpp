#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <vector>   // 引入向量容器库，用于存储图的邻接表
#include <queue>    // 引入队列容器库，用于BFS搜索

using namespace std; // 使用标准命名空间，避免每次调用std::

// 定义最大节点数量常量，根据题目限制 5*10^5，稍微大一点防止越界
const int MAXN = 500005; 

// 全局变量定义
int n; // 存储节点的总数
long long a, b; // 存储给定的上下限a和b，使用long long类型以防溢出
int w[MAXN]; // 数组存储每个节点的权值，下标从1开始
vector<int> adj[MAXN]; // 邻接表，adj[i]存储与节点i相连的所有节点
bool visited[MAXN]; // 访问标记数组，用于在BFS/DFS遍历时防止重复访问

// 定义一个模板函数，用于计算满足特定条件的路径总数
// Func是一个函数对象（如lambda表达式），用于判断节点权值是否满足条件
template<typename Func>
long long countPaths(Func condition) {
    // 每次计算前，将visited数组重置为false，确保遍历状态正确
    for(int i = 1; i <= n; ++i) visited[i] = false;
    
    long long totalPairs = 0; // 用于累计满足条件的路径数（包括单点路径）
    
    // 遍历每一个节点，寻找未访问过的满足条件的连通分量
    for(int i = 1; i <= n; ++i) {
        // 如果当前节点未被访问，且该节点的权值满足传入的条件
        if (!visited[i] && condition(w[i])) {
            long long cnt = 0; // 用于记录当前连通分量中的节点数量
            queue<int> q; // 定义一个队列用于广度优先搜索(BFS)
            q.push(i); // 将当前起始节点加入队列
            visited[i] = true; // 标记当前节点为已访问
            cnt++; // 连通分量节点数加1
            
            // 当队列不为空时，继续搜索连通分量中的其他节点
            while(!q.empty()) {
                int u = q.front(); // 获取队首节点
                q.pop(); // 弹出队首节点
                
                // 遍历当前节点u的所有相邻节点v
                for(int v : adj[u]) {
                    // 如果相邻节点v未被访问，且其权值也满足条件
                    if(!visited[v] && condition(w[v])) {
                        visited[v] = true; // 标记相邻节点为已访问
                        cnt++; // 连通分量节点数加1
                        q.push(v); // 将相邻节点加入队列继续搜索
                    }
                }
            }
            // 对于一个包含cnt个节点的连通分量，其内部的所有路径数量为 cnt*(cnt+1)/2
            // 这里计算的是无向点对(u, v)的数量，其中u可以等于v
            // 虽然题目要求简单路径（通常u!=v），但我们在后续的容斥原理计算中，
            // 单点路径（不满足条件的情况）会被相互抵消，因此可以直接使用此公式简化计算
            totalPairs += cnt * (cnt + 1) / 2;
        }
    }
    return totalPairs; // 返回满足该条件的路径总数
}

int main() {
    // 关闭C++标准流与C标准流的同步，提高I/O效率
    ios::sync_with_stdio(false);
    cin.tie(0); // 解除cin与cout的绑定，进一步提高速度
    
    // 从标准输入读取节点数n，以及界限a和b
    // 如果读取失败则退出程序
    if (!(cin >> n >> a >> b)) return 0;
    
    // 循环读取n个节点的权值
    for(int i = 1; i <= n; ++i) {
        cin >> w[i]; // 读取第i个节点的权值
    }
    
    // 循环读取n-1条边，构建树的结构
    for(int i = 0; i < n - 1; ++i) {
        int u, v; // 定义边的两个端点变量
        cin >> u >> v; // 读取边的端点u和v
        adj[u].push_back(v); // 在u的邻接表中添加v
        adj[v].push_back(u); // 在v的邻接表中添加u（因为是无向图）
    }
    
    // 计算树中所有可能的路径总数（包含单点路径）
    // 对于n个节点的树，任意两点（包括自身）的组合数为 n*(n+1)/2
    long long totalAll = (long long)n * (n + 1) / 2;

    // 计算违反条件1的路径数：即路径上所有节点的权值都 > a
    // 这样的路径最小权值肯定 > a，所以不满足“最小权值 <= a”
    long long countA = countPaths([&](int val){ return val > a; });
    
    // 计算违反条件2的路径数：即路径上所有节点的权值都 < b
    // 这样的路径最大权值肯定 < b，所以不满足“最大权值 >= b”
    long long countB = countPaths([&](int val){ return val < b; });
    
    // 计算同时违反条件1和条件2的路径数：即路径上所有节点的权值 > a 且 < b
    // 这些路径在countA和countB中都被计算过，需要通过容斥原理减去重复部分
    long long countAB = countPaths([&](int val){ return val > a && val < b; });
    
    // 根据容斥原理计算所有“坏”路径（不满足题目条件的路径）的数量
    // BadPaths = |集合A| + |集合B| - |集合A ∩ 集合B|
    long long badPaths = countA + countB - countAB;
    
    // 最终结果 = 总路径数 - 坏路径数
    // 好路径的定义是：路径上最小权值 <= a 且 最大权值 >= b
    long long result = totalAll - badPaths;
    
    // 输出最终计算出的好路径条数
    cout << result << endl;
    
    return 0; // 程序正常结束
}
