#include <iostream> // 引入输入输出流库
using namespace std; // 使用标准命名空间

int main() { // 主函数入口
    double h; // 声明一个双精度浮点数变量h，用于存储初始高度
    while (cin >> h) { // 循环读取输入的高度，直到没有输入为止
        double height = h; // 初始化当前高度为h
        double distance = h; // 初始化总路程为第一次下落的距离h
        
        // 循环4次，计算第1次落地后到第5次落地前的反弹和下落过程
        for (int i = 0; i < 4; ++i) { // 循环变量i从0到3
            height /= 2; // 每次反弹高度变为原来的一半
            distance += height * 2; // 总路程增加：反弹上去的距离 + 再次落下的距离（即当前高度的2倍）
        } // 循环结束

        cout << distance << endl; // 输出第5次落地时经历的总路程
        cout << height / 2 << endl; // 输出第5次反弹的高度（即第5次下落高度的一半）
    } // while循环结束
    return 0; // 程序正常结束返回0
} // main函数结束

