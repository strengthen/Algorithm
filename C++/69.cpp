#include <iostream> // 引入输入输出流库，用于控制台的输入和输出
#include <vector>   // 引入向量容器库，用于存储矩阵数据

using namespace std; // 使用标准命名空间，方便直接使用标准库中的名称

int main() { // 主函数，程序的执行入口
    int x, y, z; // 定义三个整数变量，分别代表矩阵A的行数、矩阵A的列数(即矩阵B的行数)、矩阵B的列数

    // 从标准输入读取三个整数：x, y, z
    // 题目描述中分别各占一行，cin 会自动跳过空白字符读取
    while (cin >> x >> y >> z) { 
        // 使用二维向量 vector<vector<int>> 来存储矩阵A，大小为 x 行 y 列
        vector<vector<int>> A(x, vector<int>(y));
        
        // 嵌套循环读取矩阵A的元素
        for (int i = 0; i < x; ++i) { // 遍历矩阵A的每一行
            for (int j = 0; j < y; ++j) { // 遍历矩阵A的每一列
                cin >> A[i][j]; // 读取矩阵A第i行第j列的元素
            }
        }

        // 使用二维向量 vector<vector<int>> 来存储矩阵B，大小为 y 行 z 列
        vector<vector<int>> B(y, vector<int>(z));

        // 嵌套循环读取矩阵B的元素
        for (int i = 0; i < y; ++i) { // 遍历矩阵B的每一行
            for (int j = 0; j < z; ++j) { // 遍历矩阵B的每一列
                cin >> B[i][j]; // 读取矩阵B第i行第j列的元素
            }
        }

        // 定义结果矩阵C，大小为 x 行 z 列，并初始化所有元素为0
        // 结果矩阵C的行数等于A的行数，列数等于B的列数
        vector<vector<int>> C(x, vector<int>(z, 0));

        // 进行矩阵乘法运算
        // C[i][j] 的值等于 A的第i行 与 B的第j列 对应元素的乘积之和
        for (int i = 0; i < x; ++i) { // 遍历结果矩阵C的每一行（对应矩阵A的行）
            for (int j = 0; j < z; ++j) { // 遍历结果矩阵C的每一列（对应矩阵B的列）
                for (int k = 0; k < y; ++k) { // 遍历矩阵A的列（同时也是矩阵B的行），用于累加乘积
                    C[i][j] += A[i][k] * B[k][j]; // 累加 A[i][k] * B[k][j] 到 C[i][j]
                }
            }
        }

        // 输出计算得到的结果矩阵C
        for (int i = 0; i < x; ++i) { // 遍历结果矩阵C的每一行
            for (int j = 0; j < z; ++j) { // 遍历结果矩阵C的每一列
                cout << C[i][j]; // 输出当前元素
                if (j < z - 1) { // 如果不是该行的最后一个元素
                    cout << " "; // 输出一个空格作为分隔符
                }
            }
            cout << endl; // 每输出完一行后换行
        }
    }

    return 0; // 程序执行成功，返回0
}
