#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <vector>   // 引入向量容器库，用于存储数独矩阵

using namespace std; // 使用标准命名空间，避免每次调用标准库都要加 std::

// 检查在数独棋盘的 (row, col) 位置填入数字 val 是否合法
bool isValid(const vector<vector<int>>& board, int row, int col, int val) {
    for (int i = 0; i < 9; ++i) { // 循环 0 到 8，用于检查行、列和宫格
        if (board[row][i] == val) return false; // 检查当前行是否已经包含该数字，如果包含则返回 false
        if (board[i][col] == val) return false; // 检查当前列是否已经包含该数字，如果包含则返回 false
        // 检查当前位置所在的 3x3 宫格是否已经包含该数字
        // 宫格的行起始位置为 3 * (row / 3)，列起始位置为 3 * (col / 3)
        // i / 3 产生 0, 0, 0, 1, 1, 1, 2, 2, 2 的偏移量
        // i % 3 产生 0, 1, 2, 0, 1, 2, 0, 1, 2 的偏移量
        if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == val) return false; // 如果宫格内有重复数字，返回 false
    }
    return true; // 如果行、列、宫格检查都通过，说明该数字在该位置合法，返回 true
}

// 使用回溯算法（深度优先搜索）求解数独
bool solveSudoku(vector<vector<int>>& board) {
    for (int i = 0; i < 9; ++i) { // 遍历数独的每一行
        for (int j = 0; j < 9; ++j) { // 遍历数独的每一列
            if (board[i][j] == 0) { // 如果当前位置是 0，表示这是一个空格，需要填入数字
                for (int k = 1; k <= 9; ++k) { // 尝试填入数字 1 到 9
                    if (isValid(board, i, j, k)) { // 检查填入数字 k 是否满足数独规则
                        board[i][j] = k; // 如果合法，先假设填入数字 k
                        if (solveSudoku(board)) return true; // 递归调用继续尝试填充下一个空格，如果后续都成功找到解，则返回 true
                        board[i][j] = 0; // 如果递归调用返回 false，说明当前填入 k 导致后续无解，回溯：将该位置重置为 0
                    }
                }
                return false; // 如果尝试了 1-9 所有数字都无法填入该空格，说明之前的步骤有误，返回 false 触发回溯
            }
        }
    }
    return true; // 如果所有位置都遍历完且没有返回 false，说明所有空格都已正确填满，返回 true
}

int main() {
    vector<vector<int>> board(9, vector<int>(9)); // 定义一个 9x9 的二维整数向量来存储数独矩阵

    // 从标准输入读取数独题目数据
    for (int i = 0; i < 9; ++i) { // 遍历 9 行
        for (int j = 0; j < 9; ++j) { // 遍历 9 列
            cin >> board[i][j]; // 读取输入的数字，0 代表空格
        }
    }

    solveSudoku(board); // 调用求解函数开始解数独

    // 将解出的数独矩阵输出到标准输出
    for (int i = 0; i < 9; ++i) { // 遍历 9 行
        for (int j = 0; j < 9; ++j) { // 遍历 9 列
            cout << board[i][j] << (j == 8 ? "" : " "); // 输出数字，每行数字之间用空格隔开，最后一个数字后不加空格
        }
        cout << endl; // 每行输出完毕后换行
    }

    return 0; // 程序执行成功，返回 0
}

