#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于处理字符串操作
#include <vector>   // 引入向量库

using namespace std; // 使用标准命名空间，避免每次调用标准库函数都要加 std::

int main() { // 主函数入口
    string keyStr; // 定义字符串变量 keyStr，用于存储密钥底串 s
    string textStr; // 定义字符串变量 textStr，用于存储待加密的明文 t

    // 使用 while 循环读取输入，cin 会跳过空白字符读取字符串
    // 题目要求输入两行，第一行为 s，第二行为 t
    while (cin >> keyStr >> textStr) { 
        string newAlphabet = ""; // 定义字符串 newAlphabet，用于构建加密用的新字母表
        bool isExist[26] = {false}; // 定义布尔数组 isExist，记录 'a'-'z' 是否已添加到新字母表中，初始化为 false

        // 第一步：根据密钥底串 keyStr 构建新字母表的前半部分
        // 遍历密钥字符串中的每一个字符
        for (int i = 0; i < keyStr.length(); i++) {
            char c = keyStr[i]; // 获取当前字符
            int index = c - 'a'; // 计算当前字符 c 对应的小写字母索引（0-25）
            // 题目保证输入仅由小写字母构成，所以直接判断是否已存在
            if (index >= 0 && index < 26 && !isExist[index]) { // 如果该字符是小写字母且尚未被添加到新字母表中
                newAlphabet += c; // 将该字符追加到新字母表末尾
                isExist[index] = true; // 将该字符标记为已存在
            }
        }

        // 第二步：将剩余未出现的字母按顺序补充到新字母表后
        for (char c = 'a'; c <= 'z'; ++c) { // 从 'a' 到 'z' 遍历所有小写字母
            int index = c - 'a'; // 计算当前字母对应的索引
            if (!isExist[index]) { // 如果该字母在之前的密钥串中未出现过
                newAlphabet += c; // 将该字母追加到新字母表末尾
                isExist[index] = true; // 标记为已存在
            }
        }

        // 第三步：根据新字母表对明文 textStr 进行加密
        string cipherText = ""; // 定义字符串 cipherText，用于存储加密后的密文
        // 遍历明文字符串中的每一个字符
        for (int i = 0; i < textStr.length(); i++) {
            char c = textStr[i]; // 获取当前明文字符
            // 明文字符 c 在标准字母表中的位置是 c - 'a'
            // 新字母表中对应位置的字符即为加密后的字符
            // 例如：明文 'a' 替换为 newAlphabet[0]，'b' 替换为 newAlphabet[1]
            if (c >= 'a' && c <= 'z') { // 确保是小写字母
                 cipherText += newAlphabet[c - 'a']; // 查找对照表替换字符并追加到密文串
            } else {
                 cipherText += c; // 如果是非小写字母（题目未涉及，防卫性编程），原样保留
            }
        }

        cout << cipherText << endl; // 输出最终生成的密文，并换行
    }

    return 0; // 程序正常结束，返回 0
}

