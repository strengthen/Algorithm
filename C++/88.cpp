#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// 获取扑克牌的权重值，用于比较大小
// 3-9: 对应数字3-9
// 10: 10
// J: 11
// Q: 12
// K: 13
// A: 14
// 2: 15
// joker (小王): 16
// JOKER (大王): 17
int getPokerValue(string p) {
    if (p == "J") return 11;
    if (p == "Q") return 12;
    if (p == "K") return 13;
    if (p == "A") return 14;
    if (p == "2") return 15;
    if (p == "joker") return 16;
    if (p == "JOKER") return 17;
    if (p == "10") return 10;
    return p[0] - '0'; // 3-9
}

// 将手牌字符串分割成单张牌的vector
vector<string> split(string s) {
    vector<string> res;
    stringstream ss(s);
    string temp;
    while (ss >> temp) {
        res.push_back(temp);
    }
    return res;
}

int main() {
    string line;
    // 循环读取每一行输入
    while (getline(cin, line)) {
        // 找到连接符 '-' 的位置
        size_t dashPos = line.find('-');
        
        // 分割出两手牌的字符串
        string s1_str = line.substr(0, dashPos);
        string s2_str = line.substr(dashPos + 1);
        
        // 将两手牌分别解析为字符串数组
        vector<string> c1 = split(s1_str);
        vector<string> c2 = split(s2_str);
        
        // 判断是否为对王（对王是最大的牌）
        // 对王由 "joker" 和 "JOKER" 组成
        bool c1_is_jokers = (c1.size() == 2 && (c1[0] == "joker" || c1[0] == "JOKER") && (c1[1] == "joker" || c1[1] == "JOKER"));
        bool c2_is_jokers = (c2.size() == 2 && (c2[0] == "joker" || c2[0] == "JOKER") && (c2[1] == "joker" || c2[1] == "JOKER"));
        
        if (c1_is_jokers || c2_is_jokers) {
            // 如果有一方是对王，则对王最大
            if (c1_is_jokers) cout << s1_str << endl;
            else cout << s2_str << endl;
            continue;
        }
        
        // 判断是否为炸弹（4张牌）
        // 题目保证输入合法，所以4张牌的一定是炸弹
        bool c1_is_bomb = (c1.size() == 4);
        bool c2_is_bomb = (c2.size() == 4);
        
        // 如果两手牌都是炸弹，比较牌面大小
        if (c1_is_bomb && c2_is_bomb) {
            if (getPokerValue(c1[0]) > getPokerValue(c2[0])) {
                cout << s1_str << endl;
            } else {
                cout << s2_str << endl;
            }
            continue;
        }
        
        // 如果只有一手牌是炸弹，炸弹大
        if (c1_is_bomb) {
            cout << s1_str << endl;
            continue;
        }
        if (c2_is_bomb) {
            cout << s2_str << endl;
            continue;
        }
        
        // 如果都不是对王或炸弹，则必须牌型一致（张数相同）才能比较
        // 个子、对子、三个、顺子，只要张数相同，比较第一张牌的大小即可
        if (c1.size() == c2.size()) {
            if (getPokerValue(c1[0]) > getPokerValue(c2[0])) {
                cout << s1_str << endl;
            } else {
                cout << s2_str << endl;
            }
            continue;
        }
        
        // 无法比较的情况
        cout << "ERROR" << endl;
    }
    return 0;
}
