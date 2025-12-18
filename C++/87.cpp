#include <iostream> // 引入输入输出流库
#include <string>   // 引入字符串库
#include <cctype>   // 引入字符处理库

using namespace std; // 使用标准命名空间

int main() {
    string password; // 定义字符串变量存储输入的密码
    while (cin >> password) { // 循环读取密码，直到输入结束
        int score = 0; // 初始化总分变量
        int len = password.length(); // 获取密码长度
        int lowerCount = 0; // 初始化小写字母计数器
        int upperCount = 0; // 初始化大写字母计数器
        int digitCount = 0; // 初始化数字计数器
        int symbolCount = 0; // 初始化符号计数器

        // 遍历密码字符串统计各类字符数量
        for (char c : password) { // 遍历每一个字符
            if (islower(c)) { // 如果是小写字母
                lowerCount++; // 小写字母计数加1
            } else if (isupper(c)) { // 如果是大写字母
                upperCount++; // 大写字母计数加1
            } else if (isdigit(c)) { // 如果是数字
                digitCount++; // 数字计数加1
            } else { // 其他情况视为符号（根据题目描述的ASCII范围，非字母数字即可视为符号）
                // 题目给出的符号ASCII范围涵盖了大部分非字母数字的可打印字符
                symbolCount++; // 符号计数加1
            }
        }

        // 一、密码长度评分
        if (len <= 4) { // 长度小于等于4
            score += 5; // 得5分
        } else if (len >= 5 && len <= 7) { // 长度在5到7之间
            score += 10; // 得10分
        } else if (len >= 8) { // 长度大于等于8
            score += 25; // 得25分
        }

        // 二、字母评分
        if (lowerCount > 0 && upperCount > 0) { // 大小写混合
            score += 20; // 得20分
        } else if (lowerCount > 0 || upperCount > 0) { // 全是小写或全是大写（即只有一种且有字母）
            score += 10; // 得10分
        } else { // 没有字母
            score += 0; // 得0分
        }

        // 三、数字评分
        if (digitCount == 1) { // 1个数字
            score += 10; // 得10分
        } else if (digitCount > 1) { // 大于1个数字
            score += 20; // 得20分
        } else { // 没有数字
            score += 0; // 得0分
        }

        // 四、符号评分
        if (symbolCount == 1) { // 1个符号
            score += 10; // 得10分
        } else if (symbolCount > 1) { // 大于1个符号
            score += 25; // 得25分
        } else { // 没有符号
            score += 0; // 得0分
        }

        // 五、奖励评分（只能选符合最多的那一种）
        if (lowerCount > 0 && upperCount > 0 && digitCount > 0 && symbolCount > 0) { // 大小写字母、数字和符号都有
            score += 5; // 奖励5分
        } else if ((lowerCount > 0 || upperCount > 0) && digitCount > 0 && symbolCount > 0) { // 字母、数字和符号都有
            score += 3; // 奖励3分
        } else if ((lowerCount > 0 || upperCount > 0) && digitCount > 0) { // 字母和数字都有
            score += 2; // 奖励2分
        }

        // 根据总分判定安全等级并输出
        if (score >= 90) { // 分数大于等于90
            cout << "VERY_SECURE" << endl; // 输出非常安全
        } else if (score >= 80) { // 分数大于等于80
            cout << "SECURE" << endl; // 输出安全
        } else if (score >= 70) { // 分数大于等于70
            cout << "VERY_STRONG" << endl; // 输出非常强
        } else if (score >= 60) { // 分数大于等于60
            cout << "STRONG" << endl; // 输出强
        } else if (score >= 50) { // 分数大于等于50
            cout << "AVERAGE" << endl; // 输出一般
        } else if (score >= 25) { // 分数大于等于25
            cout << "WEAK" << endl; // 输出弱
        } else { // 分数小于25
            cout << "VERY_WEAK" << endl; // 输出非常弱
        }
    }
    return 0; // 程序结束
}
