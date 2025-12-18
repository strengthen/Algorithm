#include <iostream> // 引入输入输出流库
#include <vector>   // 引入向量容器库
#include <set>      // 引入集合容器库，用于自动去重
#include <algorithm> // 引入算法库

using namespace std; // 使用标准命名空间

int main() {
    int n; // 定义变量n，用于存储砝码的种数
    // 循环读取输入，直到没有更多输入，处理多组测试用例的情况
    while (cin >> n) { 
        vector<int> m(n); // 定义一个大小为n的向量m，存储每种砝码的重量
        vector<int> x(n); // 定义一个大小为n的向量x，存储每种砝码的数量

        // 读取每种砝码的重量
        for (int i = 0; i < n; ++i) {
            cin >> m[i]; // 输入第i种砝码的重量
        }

        // 读取每种砝码的数量
        for (int i = 0; i < n; ++i) {
            cin >> x[i]; // 输入第i种砝码的数量
        }

        set<int> weights; // 定义一个集合weights，用于存储所有可能称出的重量，利用set特性自动去重
        weights.insert(0); // 初始状态下，什么都不放，重量为0，根据题目描述包括0

        // 遍历每一种砝码
        for (int i = 0; i < n; ++i) {
            set<int> temp_weights; // 定义一个临时集合，用于存储当前这一轮新产生的重量
            
            // 遍历当前已经能称出的所有重量
            for (auto it = weights.begin(); it != weights.end(); ++it) {
                int current_weight = *it; // 获取当前已有的重量
                
                // 尝试加上当前种类砝码的1个到全部个数
                for (int k = 1; k <= x[i]; ++k) {
                    // 计算新的重量：已有重量 + k个当前砝码的重量
                    // 并将其插入临时集合中
                    temp_weights.insert(current_weight + k * m[i]);
                }
            }

            // 将本轮新产生的重量合并到总的重量集合中
            for (auto it = temp_weights.begin(); it != temp_weights.end(); ++it) {
                weights.insert(*it); // 插入到主集合中，set会自动处理重复元素
            }
        }

        // 输出最终集合的大小，即能称出的不同重量的数量
        cout << weights.size() << endl; 
    }
    return 0; // 程序正常结束
}

