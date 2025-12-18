#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于使用string类型
using namespace std; // 使用标准命名空间std，避免每次调用标准库需加std::

int main() { // 主函数，程序的入口点
    string s; // 定义一个字符串变量s，用来存储输入的字符串
    
    // 使用while循环读取输入，cin >> s 会跳过空白字符读取字符串
    // 这样可以处理可能存在的多组输入情况
    while (cin >> s) { 
        int len = s.length(); // 获取输入字符串的长度
        
        // 使用for循环遍历字符串，步长为8，因为题目要求每8个字符一组
        for (int i = 0; i < len; i += 8) { 
            
            // 判断当前位置 i 加上 8 是否超过了字符串总长度
            if (i + 8 <= len) { 
                // 如果没有超过，说明可以直接截取8个字符
                // substr(i, 8) 表示从下标 i 开始截取 8 个字符
                cout << s.substr(i, 8) << endl; // 输出截取的子串并换行
            } else { 
                // 如果超过了，说明是最后一部分且不足8个字符
                // substr(i) 表示从下标 i 开始截取到字符串末尾
                string sub = s.substr(i); 
                cout << sub; // 先输出这部分原本的字符
                
                // 计算需要补充多少个 '0'，总共需要8个，减去现在的长度
                int need = 8 - sub.length(); 
                
                // 循环输出缺少的 '0'
                for (int j = 0; j < need; ++j) { 
                    cout << '0'; // 输出字符 '0'
                }
                cout << endl; // 补齐后换行
            }
        }
    }
    return 0; // 程序执行完毕，返回0表示成功
}
