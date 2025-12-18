#include <iostream> // 引入输入输出流库
#include <algorithm> // 引入算法库，用于使用min函数

using namespace std; // 使用标准命名空间std

int main() { // 主程序的入口点
    int n, m; // 声明两个整型变量，n代表结算金额，m代表优惠券数量
    if (cin >> n >> m) { // 从标准输入读取n和m，并检查输入是否有效
        int min_pay = n; // 初始化最少支付金额为原价n，表示初始假设不使用优惠券
        for (int i = 0; i < m; ++i) { // 循环遍历每一张优惠券
            int a, b; // 声明两个整型变量，a代表满减门槛，b代表减免金额
            cin >> a >> b; // 读取当前优惠券的门槛a和减免金额b
            if (n >= a) { // 判断当前结算金额n是否达到优惠券的使用门槛a
                min_pay = min(min_pay, n - b); // 如果满足条件，更新最少支付金额，取当前最小值和使用优惠券后金额的较小者
            } // 结束if条件判断
        } // 结束for循环
        cout << min_pay << endl; // 输出最终计算出的最少支付金额
    } // 结束输入判断
    return 0; // 返回0，表示程序正常结束
} // 结束主函数
