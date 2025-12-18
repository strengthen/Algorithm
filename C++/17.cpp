#include <iostream> // 引入输入输出流库
#include <string>   // 引入字符串处理库
#include <vector>   // 引入向量库（虽然本题可以用流处理代替，但作为常用库保留）
#include <sstream>  // 引入字符串流库，用于分割字符串

using namespace std; // 使用标准命名空间

int main() { // 主函数入口
    string line; // 定义字符串变量用于存储输入的一整行
    while (getline(cin, line)) { // 循环读取每一行输入，直到输入结束
        stringstream ss(line); // 使用输入行初始化字符串流
        string token; // 定义字符串变量用于存储分割后的指令
        int x = 0, y = 0; // 初始化横坐标x和纵坐标y为0
        
        while (getline(ss, token, ';')) { // 以分号为分隔符读取每个指令
            if (token.empty()) continue; // 如果指令为空，跳过
            
            // 检查指令长度，合法的指令长度只能是2或3（如A1或A10）
            if (token.size() < 2 || token.size() > 3) continue;
            
            char direction = token[0]; // 获取指令的第一个字符作为方向
            // 检查方向字符是否合法（必须是A, D, W, S中的一个）
            if (direction != 'A' && direction != 'D' && direction != 'W' && direction != 'S') {
                continue; // 如果方向不合法，跳过该指令
            }
            
            string numStr = token.substr(1); // 获取指令剩余部分作为数字字符串
            bool isNum = true; // 定义标志位判断是否为数字
            for (char c : numStr) { // 遍历数字字符串的每一个字符
                if (!isdigit(c)) { // 如果字符不是数字
                    isNum = false; // 标记为非数字
                    break; // 跳出循环
                }
            }
            
            if (!isNum) continue; // 如果包含非数字字符，跳过该指令
            
            int step = stoi(numStr); // 将数字字符串转换为整数
            
            // 题目要求数字大于0且小于100（即1-99）
            // 实际上由于长度限制为3，且去掉了方向字符，剩余最多2位数字，最大99，所以必定小于100
            // 因此主要检查是否大于0
            if (step > 0) { 
                switch (direction) { // 根据方向更新坐标
                    case 'A': // 向左移动
                        x -= step; // 横坐标减去步长
                        break; // 结束分支
                    case 'D': // 向右移动
                        x += step; // 横坐标加上步长
                        break; // 结束分支
                    case 'W': // 向上移动
                        y += step; // 纵坐标加上步长
                        break; // 结束分支
                    case 'S': // 向下移动
                        y -= step; // 纵坐标减去步长
                        break; // 结束分支
                }
            }
        }
        cout << x << "," << y << endl; // 输出最终坐标，用逗号分隔
    }
    return 0; // 程序正常结束
}

