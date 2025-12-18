#include <iostream> // 引入输入输出流库
#include <string>   // 引入字符串处理库
#include <vector>   // 引入向量容器库
#include <algorithm> // 引入算法库

using namespace std; // 使用标准命名空间

// 定义一个结构体来存储错误记录
struct ErrorRecord {
    string filename; // 文件名
    int lineNum;     // 行号
    int count;       // 错误计数
};

int main() {
    string filePath; // 用于存储输入的文件路径
    int lineNum;     // 用于存储输入的行号
    vector<ErrorRecord> records; // 存储所有不同的错误记录，按首次出现顺序排列

    // 循环读取输入，直到文件结束（EOF）
    // 题目描述输入包含文件路径和行号
    while (cin >> filePath >> lineNum) {
        // 1. 提取文件名
        // 查找文件路径中最后一个反斜杠 '\' 的位置
        // 注意：在C++中反斜杠需要转义，所以写成 '\\'
        size_t pos = filePath.rfind('\\');
        string filename;
        
        // 如果找到了反斜杠，截取其后的部分作为文件名
        if (pos != string::npos) {
            filename = filePath.substr(pos + 1);
        } else {
            // 如果没找到反斜杠，说明整个路径字符串就是文件名
            filename = filePath;
        }

        // 2. 处理文件名长度
        // 题目要求：至多保留文件名的最后 16 个字符
        if (filename.size() > 16) {
            // 使用 substr 截取从 (长度-16) 开始到末尾的子串
            filename = filename.substr(filename.size() - 16);
        }

        // 3. 检查记录是否已存在
        // 题目要求：相同的报错信息以第一次出现的时间为准
        bool exists = false; // 标记该记录是否已存在
        for (auto& record : records) {
            // 如果文件名和行号都相同，则视为同一条报错
            if (record.filename == filename && record.lineNum == lineNum) {
                record.count++; // 增加该记录的出现次数
                exists = true;  // 标记为已存在
                break;          // 找到后退出查找循环
            }
        }

        // 4. 如果记录不存在，则作为新记录添加到列表中
        if (!exists) {
            // 创建新记录实例
            ErrorRecord newRecord;
            newRecord.filename = filename;
            newRecord.lineNum = lineNum;
            newRecord.count = 1; // 初始计数为1
            records.push_back(newRecord); // 将新记录添加到向量末尾
        }
    }

    // 5. 输出最后8条记录
    // 题目要求：至多输出最后 8 条记录
    // 计算开始输出的索引位置
    int start = 0;
    if (records.size() > 8) {
        // 如果记录总数超过8条，则从倒数第8条开始输出
        start = records.size() - 8;
    }

    // 遍历并输出选定的记录范围
    for (int i = start; i < records.size(); ++i) {
        // 输出格式：文件名 行号 计数，中间用空格分隔
        cout << records[i].filename << " " << records[i].lineNum << " " << records[i].count << endl;
    }

    return 0; // 程序正常结束
}

