#include <iostream> // 引入输入输出流库，用于处理控制台的输入和输出操作
#include <vector>   // 引入向量容器库，用于存储动态大小的数组（如I序列和结果集）
#include <string>   // 引入字符串库，用于将整数转换为字符串以及进行子串查找
#include <algorithm>// 引入算法库，提供各类算法支持（虽然set已自动排序，但此库常用）
#include <set>      // 引入集合容器库，set容器会自动对元素进行排序并去除重复项

using namespace std; // 使用标准命名空间std，避免在调用标准库函数时重复写std::前缀

int main() { // 主函数的开始，程序执行的入口点
    int n; // 定义一个整型变量n，用于存储输入数据序列I中元素的个数
    while (cin >> n) { // 使用while循环读取n，支持多组测试用例的连续输入，直到输入结束
        vector<long long> I(n); // 定义一个long long类型的向量I，大小为n，用于存储数据序列
        for (int i = 0; i < n; ++i) { // 使用for循环遍历n次，读取数据序列中的每一个整数
            cin >> I[i]; // 从输入流中读取第i个整数并存入向量I的第i个位置
        } // 数据序列I读取循环结束

        int m; // 定义一个整型变量m，用于存储规则集R中规则的个数
        cin >> m; // 从输入流中读取m的值
        set<int> R; // 定义一个整型集合R，利用set特性自动对规则进行排序和去重
        for (int i = 0; i < m; ++i) { // 使用for循环遍历m次，读取规则集中的每一个整数
            int temp; // 定义一个临时变量temp，用于暂存读取到的规则值
            cin >> temp; // 从输入流中读取规则值存入temp
            R.insert(temp); // 将规则值插入集合R中，set会自动处理排序和去重
        } // 规则集R读取及预处理循环结束

        vector<long long> result; // 定义一个long long类型的向量result，用于按顺序存储最终输出的所有数值

        for (int r : R) { // 使用范围for循环遍历集合R中的每一个规则r（已排序且无重复）
            string r_str = to_string(r); // 将当前规则整数r转换为字符串r_str，以便进行子串包含检查
            vector<pair<int, long long>> matches; // 定义一个pair类型的向量matches，用于存储匹配成功的数据的索引和数值

            for (int i = 0; i < n; ++i) { // 遍历数据序列I中的每一个元素
                string i_str = to_string(I[i]); // 将当前数据I[i]转换为字符串i_str
                if (i_str.find(r_str) != string::npos) { // 检查规则字符串r_str是否是数据字符串i_str的子串
                    matches.push_back({i, I[i]}); // 如果包含，则将当前索引i和数据I[i]作为一个pair存入matches向量
                } // 子串检查结束
            } // 数据序列I的遍历结束

            if (!matches.empty()) { // 检查当前规则r是否有匹配到的数据（matches不为空）
                result.push_back(r); // 如果有匹配，首先将规则r本身添加到结果向量result中
                result.push_back(matches.size()); // 然后将匹配到的数据个数添加到结果向量result中
                for (auto& match : matches) { // 遍历所有匹配成功的记录
                    result.push_back(match.first); // 将匹配数据在I序列中的索引添加到结果向量result中
                    result.push_back(match.second); // 将匹配数据的值添加到结果向量result中
                } // 匹配记录的添加循环结束
            } // 当前规则r的处理逻辑结束
        } // 所有规则的遍历结束

        cout << result.size(); // 输出结果向量result的总大小，即题目要求的第一个整数k
        for (long long val : result) { // 遍历结果向量result中的每一个数值
            cout << " " << val; // 输出一个空格，紧接着输出当前数值val
        } // 结果向量的输出循环结束
        cout << endl; // 输出一个换行符，标志着当前测试用例输出的结束
    } // while循环结束，准备处理下一组输入（如果有）
    return 0; // 主函数返回0，表示程序正常执行结束
} // 主函数结束


