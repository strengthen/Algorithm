#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于处理命令字符串
#include <vector>   // 引入向量库（虽然本解法主要用基本类型，但保留常用头文件）

using namespace std; // 使用标准命名空间，避免每次写std::

int main() { // 主函数，程序的入口点
    int n; // 定义整型变量n，表示歌曲总数
    
    // 使用while循环读取输入，因为题目可能包含多组测试数据
    while (cin >> n) { 
        string cmd; // 定义字符串变量cmd，用于存储操作命令序列
        cin >> cmd; // 读取命令字符串（例如 "UUUDD"）
        
        int current = 1; // 定义当前光标所在的歌曲位置，初始化为1
        int top = 1;     // 定义当前屏幕显示列表的第一首歌位置，初始化为1
        
        // 题目逻辑分两种情况：歌曲少于等于4首，和多于4首
        if (n <= 4) {
            // --- 情况一：歌曲总数 <= 4 ---
            // 此时不需要翻页，屏幕总是显示所有歌曲（1 到 n）
            
            for (char c : cmd) { // 遍历命令字符串中的每一个字符
                if (c == 'U') { // 如果是向上移动命令
                    if (current == 1) { // 如果当前在第一首
                        current = n; // 按Up跳到最后一首
                    } else { // 否则
                        current--; // 光标位置减1
                    }
                } else if (c == 'D') { // 如果是向下移动命令
                    if (current == n) { // 如果当前在最后一首
                        current = 1; // 按Down跳到第一首
                    } else { // 否则
                        current++; // 光标位置加1
                    }
                }
            }
            
            // 输出当前列表：显示 1 到 n 的所有歌曲
            for (int i = 1; i <= n; ++i) {
                cout << i << (i == n ? "" : " "); // 输出歌曲编号，最后一个编号后不带空格
            }
            cout << endl; // 换行
            cout << current << endl; // 输出当前选中的歌曲编号
            
        } else {
            // --- 情况二：歌曲总数 > 4 ---
            // 此时屏幕固定显示4首歌，需要维护窗口起始位置 top
            
            for (char c : cmd) { // 遍历命令字符串
                if (c == 'U') { // 如果是向上移动命令
                    if (current == 1) { // 特殊翻页：如果在第一首按Up
                        current = n; // 光标跳到最后一首
                        top = n - 3; // 屏幕显示最后一页（即 n-3, n-2, n-1, n）
                    } else if (current == top) { // 一般翻页：光标在当前页第一首按Up
                        current--; // 光标上移
                        top--; // 屏幕窗口向上滚动一行
                    } else { // 普通移动：光标不在当前页第一首
                        current--; // 仅光标上移，屏幕不翻页
                    }
                } else if (c == 'D') { // 如果是向下移动命令
                    if (current == n) { // 特殊翻页：如果在最后一首按Down
                        current = 1; // 光标跳到第一首
                        top = 1; // 屏幕显示第一页（1, 2, 3, 4）
                    } else if (current == top + 3) { // 一般翻页：光标在当前页最后一首按Down
                        current++; // 光标下移
                        top++; // 屏幕窗口向下滚动一行
                    } else { // 普通移动：光标不在当前页最后一首
                        current++; // 仅光标下移，屏幕不翻页
                    }
                }
            }
            
            // 输出当前列表：从 top 开始的4首歌
            for (int i = 0; i < 4; ++i) {
                cout << top + i << (i == 3 ? "" : " "); // 输出 top 到 top+3
            }
            cout << endl; // 换行
            cout << current << endl; // 输出当前选中的歌曲编号
        }
    }
    
    return 0; // 程序正常结束
}
