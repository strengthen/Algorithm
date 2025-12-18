#include <iostream> // 引入输入输出流头文件
#include <cmath> // 引入数学函数头文件
#include <numeric> // 引入数值算法头文件

using namespace std; // 使用标准命名空间

// 定义求最大公约数的函数，用于化简向量
long long get_gcd(long long a, long long b) {
    return b == 0 ? a : get_gcd(b, a % b); // 使用欧几里得算法递归计算最大公约数
}

int main() { // 主函数入口
    ios::sync_with_stdio(false); // 取消cin和stdin的同步，提高读取速度
    cin.tie(nullptr); // 解除cin和cout的绑定，避免不必要的刷新

    int n; // 定义整数变量n，表示需要击中的坐标数量
    long long h; // 定义长整型变量h，表示水面距离水底的直线距离
    
    if (cin >> n >> h) { // 从标准输入读取n和h，若读取成功则进入循环
        for (int i = 0; i < n; ++i) { // 循环n次，依次处理每一个坐标点
            long long x, y, z; // 定义长整型变量x, y, z存储目标的坐标
            cin >> x >> y >> z; // 读取当前目标的x, y, z坐标值
            
            // 根据光的全反射原理，从原点射向水面反射击中目标(x,y,z)
            // 等价于直接射向目标点关于水面(z=h平面)的对称点
            long long target_x = x; // 对称点的x坐标与原目标相同
            long long target_y = y; // 对称点的y坐标与原目标相同
            long long target_z = 2 * h - z; // 对称点的z坐标为水面高度的两倍减去原z坐标
            
            // 为了输出最简整数比的方向向量，需要计算三个分量的最大公约数
            long long common_divisor = get_gcd(abs(target_x), abs(target_y)); // 先计算x和y分量的最大公约数
            common_divisor = get_gcd(common_divisor, abs(target_z)); // 再将结果与z分量计算最大公约数
            
            // 输出化简后的方向向量，即各分量除以最大公约数
            cout << target_x / common_divisor << " " // 输出化简后的x分量
                 << target_y / common_divisor << " " // 输出化简后的y分量
                 << target_z / common_divisor << "\n"; // 输出化简后的z分量并换行
        }
    }
    
    return 0; // 返回0表示程序执行成功
}
