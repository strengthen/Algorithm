#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <vector>   // 引入向量库，虽然本题可以用数组，但引入常用库是个好习惯

using namespace std; // 使用标准命名空间，方便直接使用cout, cin等

// 判断是否为闰年的函数
// 参数：year - 年份
// 返回值：如果是闰年返回true，否则返回false
bool isLeapYear(int year) {
    // 闰年规则：能被4整除但不能被100整除，或者能被400整除
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int main() { // 主函数，程序的入口点
    int year, month, day; // 定义整型变量，分别存储年、月、日
    
    // 使用while循环读取输入，虽然题目描述只说了一行输入，但处理多组输入更稳健
    // cin >> year >> month >> day 会跳过空白字符读取三个整数
    while (cin >> year >> month >> day) {
        // 定义一个数组存储平年每个月的天数
        // 为了方便通过月份索引（1-12），数组大小设为13，索引0的位置设为0或忽略
        int daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        // 判断当前年份是否为闰年
        if (isLeapYear(year)) {
            daysInMonth[2] = 29; // 如果是闰年，将2月（索引为2）的天数改为29天
        }
        
        int totalDays = 0; // 定义变量totalDays用于累计天数，初始化为0
        
        // 循环累加输入月份之前所有月份的天数
        // 例如：输入3月，则累加1月和2月的天数
        for (int i = 1; i < month; ++i) {
            totalDays += daysInMonth[i]; // 将第i月的天数加到totalDays中
        }
        
        totalDays += day; // 最后加上当前月份的日期天数
        
        cout << totalDays << endl; // 输出计算出的总天数，并换行
    }
    
    return 0; // 程序正常结束，返回0
}
