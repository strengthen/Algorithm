#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <vector>   // 引入向量容器库，用于存储动态数组
#include <cmath>    // 引入数学库，用于数学函数如abs

using namespace std; // 使用标准命名空间，方便直接使用标准库元素

// 递归函数，用于判断给定的数字集合能否经过运算得到24
// 参数nums为当前剩余的数字列表
bool solve(vector<double> nums) {
    // 递归终止条件：如果列表中只剩下一个数字
    if (nums.size() == 1) {
        // 判断该数字与24的差值是否在误差范围内（处理浮点数精度问题）
        // 如果差值小于1e-6，则认为等于24，返回true
        return abs(nums[0] - 24) < 1e-6;
    }

    // 遍历列表中的任意两个数字进行组合运算
    // 外层循环选择第一个操作数 nums[i]
    for (int i = 0; i < nums.size(); ++i) {
        // 内层循环选择第二个操作数 nums[j]
        for (int j = 0; j < nums.size(); ++j) {
            // 不能选择同一个位置的数字，必须是两个不同的数字
            if (i == j) continue;

            // 创建一个新的列表，用于存储下一轮递归需要的数字
            vector<double> nextNums;
            
            // 将除了当前选中的两个数字(i和j)之外的其他数字加入新列表
            for (int k = 0; k < nums.size(); ++k) {
                if (k != i && k != j) {
                    nextNums.push_back(nums[k]); // 保留未参与运算的数字
                }
            }

            // 对选中的两个数字 nums[i] 和 nums[j] 进行四则运算
            // 结果加入 nextNums，然后递归调用 solve

            // 1. 加法运算: nums[i] + nums[j]
            nextNums.push_back(nums[i] + nums[j]); // 将加法结果放入列表
            if (solve(nextNums)) return true; // 如果递归返回true，说明找到了解，逐层返回true
            nextNums.pop_back(); // 回溯：移除刚才添加的结果，以便尝试下一种运算

            // 2. 减法运算: nums[i] - nums[j]
            // 注意：由于两层循环是全排列遍历，这里只需计算 i - j，下一次循环会计算 j - i
            nextNums.push_back(nums[i] - nums[j]);
            if (solve(nextNums)) return true;
            nextNums.pop_back(); // 回溯

            // 3. 乘法运算: nums[i] * nums[j]
            nextNums.push_back(nums[i] * nums[j]);
            if (solve(nextNums)) return true;
            nextNums.pop_back(); // 回溯

            // 4. 除法运算: nums[i] / nums[j]
            // 需要确保除数不为0（题目范围是正整数，但在递归过程中可能产生0）
            if (abs(nums[j]) > 1e-6) { // 只有除数不接近0时才进行除法
                nextNums.push_back(nums[i] / nums[j]);
                if (solve(nextNums)) return true;
                nextNums.pop_back(); // 回溯
            }
        }
    }
    
    // 如果尝试了所有可能的组合和运算都无法得到24，返回false
    return false;
}

int main() {
    vector<double> nums(4); // 定义一个大小为4的double向量，存储输入的四个数字
    
    // 循环读取输入的四个数字
    for (int i = 0; i < 4; ++i) {
        cin >> nums[i]; // 读取输入
    }
    
    // 调用递归求解函数
    if (solve(nums)) {
        cout << "true" << endl; // 如果能得到24，输出true
    } else {
        cout << "false" << endl; // 否则输出false
    }
    
    return 0; // 程序正常退出
}
