#include <iostream>
#include <vector>
#include <numeric>
#include <string>

using namespace std;

/**
 * 深度优先搜索函数，用于判断是否能从剩余数字中凑出目标和
 * @param nums 剩余的可选数字列表
 * @param index 当前处理到的数字索引
 * @param currentSum 当前累加的和
 * @param targetSum 目标和
 * @return 如果能凑出目标和返回true，否则返回false
 */
bool dfs(const vector<int>& nums, int index, int currentSum, int targetSum) {
    // 如果已经处理完所有数字
    if (index == nums.size()) {
        // 判断当前和是否等于目标和
        return currentSum == targetSum;
    }

    // 两种选择：
    // 1. 将当前数字加入到累加和中（相当于分配给第一组）
    if (dfs(nums, index + 1, currentSum + nums[index], targetSum)) {
        return true;
    }

    // 2. 不将当前数字加入到累加和中（相当于分配给第二组，或者说这个数字的贡献由另一组承担，
    //    但在我们的简化模型中，我们只需要凑够一个特定的偏移量，
    //    这里的逻辑其实是：我们在寻找一个子集，使其和加上sum5等于总和的一半。
    //    或者更直观地理解：我们将others里的数分配给A组或B组。
    //    currentSum表示分配给A组的部分的和。
    //    如果分配给B组，currentSum不变。
    //    只要最终 sum5 + currentSum == (totalSum / 2)，就说明找到了解。
    if (dfs(nums, index + 1, currentSum, targetSum)) {
        return true;
    }

    return false;
}

int main() {
    int n;
    // 循环读取输入，处理多组测试用例（虽然题目描述暗示可能只有一组，但通常这类题目会有多组）
    while (cin >> n) {
        vector<int> others; // 存放既不是5的倍数也不是3的倍数的数字
        int sum5 = 0;       // 5的倍数的和
        int sum3 = 0;       // 3的倍数（且不是5的倍数）的和
        int totalSum = 0;   // 所有数字的总和

        for (int i = 0; i < n; ++i) {
            int num;
            cin >> num;
            totalSum += num;

            if (num % 5 == 0) {
                // 5的倍数归入第一组
                sum5 += num;
            } else if (num % 3 == 0) {
                // 3的倍数（不含5的倍数）归入第二组
                sum3 += num;
            } else {
                // 其他数字待分配
                others.push_back(num);
            }
        }

        // 如果总和是奇数，无法分成两个和相等的整数部分
        if (totalSum % 2 != 0) {
            cout << "false" << endl;
            continue;
        }

        // 目标是让两组的和相等，即每一组的和都应该是 totalSum / 2
        // 设第一组（包含sum5的那组）最终还需要从others中获取的和为 x
        // 则有: sum5 + x = totalSum / 2
        // 所以我们需要在 others 中找到一个子集，其和为 (totalSum / 2) - sum5
        int target = totalSum / 2 - sum5;

        // 使用DFS查找是否存在这样的子集
        if (dfs(others, 0, 0, target)) {
            cout << "true" << endl;
        } else {
            cout << "false" << endl;
        }
    }
    return 0;
}
