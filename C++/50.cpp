#include <iostream>  // 引入输入输出流库，用于控制台输入输出
#include <string>    // 引入字符串库，用于处理字符串
#include <stack>     // 引入栈容器，用于存储操作数和运算符
#include <unordered_map> // 引入哈希表，用于存储运算符优先级
#include <cctype>    // 引入字符处理库，用于isdigit等函数

using namespace std; // 使用标准命名空间

// 定义运算符计算的辅助函数
// 该函数从数字栈中弹出两个操作数，从符号栈中弹出一个运算符，进行计算，并将结果压回数字栈
void calculate(stack<int>& nums, stack<char>& ops) {
    // 检查栈是否为空，防止下溢（虽然题目保证合法，但为了健壮性）
    if (nums.size() < 2 || ops.empty()) return;

    // 栈顶元素是第二个操作数（右操作数）
    int b = nums.top(); 
    nums.pop(); // 弹出右操作数
    // 次栈顶元素是第一个操作数（左操作数）
    int a = nums.top(); 
    nums.pop(); // 弹出左操作数
    
    // 获取运算符
    char op = ops.top(); 
    ops.pop(); // 弹出运算符

    int res = 0; // 用于存储计算结果
    // 根据运算符进行相应的四则运算
    if (op == '+') res = a + b;      // 加法
    else if (op == '-') res = a - b; // 减法
    else if (op == '*') res = a * b; // 乘法
    else if (op == '/') res = a / b; // 除法
    
    // 将计算结果压入数字栈
    nums.push(res);
}

// 解决四则运算问题的主逻辑
void solve() {
    string s; // 用于存储输入的表达式字符串
    while (cin >> s) { // 循环读取输入，直到没有更多输入
        // 预处理字符串，统一括号格式并处理负号
        string formula = ""; // 存储处理后的表达式
        
        // 遍历输入字符串进行预处理
        for (int i = 0; i < s.size(); ++i) {
            // 将大括号和中括号统一替换为小括号
            if (s[i] == '{' || s[i] == '[') {
                formula += '(';
            } else if (s[i] == '}' || s[i] == ']') {
                formula += ')';
            } else if (s[i] == '-') {
                // 处理负号的情况：如果减号出现在开头，或者前一个字符是左括号，则代表负号
                // 在逻辑上相当于 0 - x，所以我们手动补一个 0
                if (i == 0 || s[i-1] == '(' || s[i-1] == '[' || s[i-1] == '{') {
                    formula += "0-"; // 补0
                } else {
                    formula += '-'; // 否则就是普通的减号
                }
            } else {
                formula += s[i]; // 其他字符（数字、+、*、/）直接复制
            }
        }

        // 定义两个栈：一个存数字，一个存运算符
        stack<int> nums; 
        stack<char> ops;

        // 定义运算符优先级
        unordered_map<char, int> priority;
        priority['+'] = 1;
        priority['-'] = 1;
        priority['*'] = 2;
        priority['/'] = 2;

        // 遍历预处理后的表达式
        for (int i = 0; i < formula.size(); ++i) {
            char c = formula[i]; // 当前字符

            if (isdigit(c)) { // 如果当前字符是数字
                int num = 0; // 用于构建多位数字
                int j = i;
                // 继续向后读取，直到不是数字为止
                while (j < formula.size() && isdigit(formula[j])) {
                    num = num * 10 + (formula[j] - '0'); // 将字符转换为整数并累加
                    j++;
                }
                nums.push(num); // 将解析出的完整数字压入数字栈
                i = j - 1; // 更新外层循环索引，因为j已经到了非数字位置，下一次循环会i++
            } else if (c == '(') { // 如果是左括号
                ops.push(c); // 直接压入符号栈
            } else if (c == ')') { // 如果是右括号
                // 不断计算，直到遇到匹配的左括号
                while (!ops.empty() && ops.top() != '(') {
                    calculate(nums, ops);
                }
                if (!ops.empty()) ops.pop(); // 弹出栈顶的左括号 '('
            } else { // 如果是运算符 (+, -, *, /)
                // 当符号栈不为空，且栈顶不是左括号，且当前运算符优先级 <= 栈顶运算符优先级时
                // 说明栈顶的运算需要先执行（左结合性或高优先级先行）
                while (!ops.empty() && ops.top() != '(' && priority[c] <= priority[ops.top()]) {
                    calculate(nums, ops); // 执行计算
                }
                ops.push(c); // 当前运算符入栈
            }
        }

        // 遍历结束后，如果符号栈中还有残留运算符，继续计算
        while (!ops.empty()) {
            calculate(nums, ops);
        }

        // 最终数字栈顶即为结果
        cout << nums.top() << endl; // 输出结果
    }
}

int main() {
    solve(); // 调用求解函数
    return 0; // 程序正常结束
}

