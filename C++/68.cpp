#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <vector>   // 引入向量库，用于存储动态数组
#include <string>   // 引入字符串库，用于处理学生姓名
#include <algorithm> // 引入算法库，用于使用排序函数

using namespace std; // 使用标准命名空间

// 定义学生结构体，包含姓名和成绩
struct Student {
    string name; // 学生姓名
    int score;   // 学生成绩
};

// 比较函数：用于降序排序（从大到小）
// 返回true表示a应该排在b前面
bool compareDesc(const Student& a, const Student& b) {
    return a.score > b.score; // 如果a的成绩大于b的成绩，则a排在前面
}

// 比较函数：用于升序排序（从小到大）
// 返回true表示a应该排在b前面
bool compareAsc(const Student& a, const Student& b) {
    return a.score < b.score; // 如果a的成绩小于b的成绩，则a排在前面
}

int main() { // 主函数
    int n; // 定义变量n，用于存储学生人数
    
    // 循环读取输入，直到没有更多输入为止（兼容多组测试用例的情况）
    while (cin >> n) { 
        int op; // 定义变量op，用于存储排序方式（0为降序，1为升序）
        cin >> op; // 读取排序方式
        
        vector<Student> students(n); // 创建一个大小为n的Student向量，用于存储所有学生信息
        
        // 循环读取n个学生的姓名和成绩
        for (int i = 0; i < n; ++i) {
            cin >> students[i].name >> students[i].score; // 依次读取姓名和成绩并存入向量中
        }
        
        // 根据op的值选择排序方式
        // 题目要求“成绩相同的同学需要保持输入的先后顺序”，因此必须使用 stable_sort
        if (op == 0) { // 如果op为0，表示降序
            // 使用stable_sort进行稳定排序，传入降序比较函数
            stable_sort(students.begin(), students.end(), compareDesc);
        } else { // 如果op为1，表示升序
            // 使用stable_sort进行稳定排序，传入升序比较函数
            stable_sort(students.begin(), students.end(), compareAsc);
        }
        
        // 遍历排序后的学生列表并输出
        for (int i = 0; i < n; ++i) {
            // 输出姓名和成绩，中间用空格分隔，末尾换行
            cout << students[i].name << " " << students[i].score << endl;
        }
    }
    
    return 0; // 程序正常结束
}
