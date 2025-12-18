#include <iostream> // 引入输入输出流标准库
#include <bitset>   // 引入bitset标准库，用于处理二进制位

using namespace std; // 使用标准命名空间

int main() { // 主函数入口
    int n; // 声明一个整型变量n，用于存储输入的整数
    
    // 从标准输入读取整数n
    if (cin >> n) {
        // 创建一个32位的bitset对象b，并将整数n作为初始值
        // bitset<32> 表示一个包含32个二进制位的容器
        // 构造函数会自动将n转换为二进制形式存储
        bitset<32> b(n); 
        
        // 调用b.count()方法，该方法返回bitset中被设置为1的位的数量
        // 直接输出这个结果，即为n的二进制表示中1的个数
        cout << b.count() << endl; 
    }

    return 0; // 程序正常结束
}
