#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 将牌面字符串转换为对应的数值
int getCardValue(string card) {
    if (card == "A") return 1;
    if (card == "J") return 11;
    if (card == "Q") return 12;
    if (card == "K") return 13;
    if (card == "10") return 10;
    // 对于2-9，直接转换字符为数字
    return card[0] - '0';
}

// 执行两个数的运算，如果是非法运算（如除以0）返回特定错误码
int calculate(int a, int b, int op) {
    switch (op) {
        case 0: return a + b; // 加法
        case 1: return a - b; // 减法
        case 2: return a * b; // 乘法
        case 3: 
            if (b == 0) return -99999; // 防止除以0
            return a / b; // 整数除法
        default: return 0;
    }
}

// 根据操作符索引获取对应的字符
char getOpChar(int op) {
    if (op == 0) return '+';
    if (op == 1) return '-';
    if (op == 2) return '*';
    if (op == 3) return '/';
    return ' ';
}

int main() {
    vector<string> cards(4); // 存储输入的4张牌的字符串
    vector<int> nums(4);     // 存储4张牌对应的数值
    bool hasJoker = false;   // 标记是否包含大小王

    // 读取输入
    for (int i = 0; i < 4; ++i) {
        cin >> cards[i];
        // 检查是否包含大小王，题目要求包含大小王则输出ERROR
        if (cards[i] == "joker" || cards[i] == "JOKER") {
            hasJoker = true;
        }
    }

    // 如果输入包含大小王，直接输出ERROR并结束程序
    if (hasJoker) {
        cout << "ERROR" << endl;
        return 0;
    }

    // 将牌面字符串转换为数值
    for (int i = 0; i < 4; ++i) {
        nums[i] = getCardValue(cards[i]);
    }

    // 创建索引数组，用于全排列遍历所有可能的牌的顺序
    vector<int> p;
    p.push_back(0);
    p.push_back(1);
    p.push_back(2);
    p.push_back(3);

    // 使用do-while循环进行全排列
    do {
        // 枚举三个运算符位置的所有可能性
        // op取值 0-3，分别代表 + - * /
        for (int i = 0; i < 4; ++i) { // 第一个运算符
            for (int j = 0; j < 4; ++j) { // 第二个运算符
                for (int k = 0; k < 4; ++k) { // 第三个运算符
                    // 按照题目要求，运算顺序从左至右，不考虑优先级
                    // 相当于 ((a op1 b) op2 c) op3 d
                    int val1 = nums[p[0]];
                    int val2 = nums[p[1]];
                    int val3 = nums[p[2]];
                    int val4 = nums[p[3]];

                    // 第一步运算
                    int res1 = calculate(val1, val2, i);
                    if (res1 == -99999) continue; // 错误处理

                    // 第二步运算
                    int res2 = calculate(res1, val3, j);
                    if (res2 == -99999) continue;

                    // 第三步运算
                    int res3 = calculate(res2, val4, k);
                    if (res3 == -99999) continue;

                    // 如果最终结果为24，输出算式
                    if (res3 == 24) {
                        cout << cards[p[0]] << getOpChar(i) 
                             << cards[p[1]] << getOpChar(j) 
                             << cards[p[2]] << getOpChar(k) 
                             << cards[p[3]] << endl;
                        return 0; // 找到一个解后直接退出
                    }
                }
            }
        }
    } while (next_permutation(p.begin(), p.end())); // 生成下一个排列

    // 如果遍历所有情况都无法得到24，输出NONE
    cout << "NONE" << endl;

    return 0;
}
