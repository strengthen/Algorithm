#include <iostream> // 引入输入输出流库，用于控制台的输入和输出操作
#include <list>     // 引入列表容器库，std::list是一个双向链表
#include <algorithm> // 引入算法库，使用std::find函数来查找元素

using namespace std; // 使用标准命名空间，这样可以直接使用cout、cin等而不需要std::前缀

int main() { // 主函数的入口点，程序从这里开始执行
    int n; // 定义一个整型变量n，用来存储链表中节点的总个数
    if (cin >> n) { // 从标准输入读取节点总数n，如果读取成功则进入if块
        int head_val; // 定义一个整型变量head_val，用来存储头节点的值
        cin >> head_val; // 从标准输入读取头节点的值

        list<int> my_list; // 创建一个std::list<int>对象，名为my_list，作为我们的链表
        my_list.push_back(head_val); // 将头节点的值添加到链表的末尾（初始时也是开头）

        // 题目给出了n个节点，头节点已经读取，还剩下n-1个节点需要插入
        for (int i = 0; i < n - 1; ++i) { // 开始循环，执行n-1次插入操作
            int val_to_insert; // 定义变量val_to_insert，表示要插入的新节点的值（题目中的a）
            int val_after; // 定义变量val_after，表示新节点要插入到哪个值之后（题目中的b）
            cin >> val_to_insert >> val_after; // 从输入流中读取这两个值

            // 在链表中查找值为val_after的节点，find函数返回一个迭代器指向找到的元素
            auto it = find(my_list.begin(), my_list.end(), val_after);
            
            // 判断是否找到了目标节点（迭代器不等于my_list.end()表示找到了）
            if (it != my_list.end()) { 
                // std::list的insert方法是在给定迭代器指向的位置 *之前* 插入元素
                // 题目要求是在val_after *之后* 插入
                // 所以我们需要将迭代器it向后移动一位（++it）
                // 这样insert就会在原来的it的下一个位置之前（即原来的it之后）插入新值
                my_list.insert(++it, val_to_insert); 
            }
        }

        int val_to_delete; // 定义变量val_to_delete，表示最后需要删除的节点的值（题目中的k）
        cin >> val_to_delete; // 读取这个要删除的值

        // 使用std::list的remove成员函数
        // 它会删除链表中所有值等于val_to_delete的节点
        // 根据题目描述，链表中节点值互不相同，所以只会删除一个（如果存在）
        my_list.remove(val_to_delete); 

        // 接下来输出处理后的链表
        bool first = true; // 定义一个布尔标记first，用于控制输出格式（处理空格）
        for (auto it = my_list.begin(); it != my_list.end(); ++it) { // 使用迭代器遍历链表
            if (!first) { // 如果不是第一个输出的元素
                cout << " "; // 在元素之间输出一个空格
            }
            cout << *it; // 输出当前迭代器指向的节点的值
            first = false; // 将first标记设为false，后续元素前都会输出空格
        }
        cout << endl; // 所有元素输出完毕后，输出一个换行符
    }
    return 0; // 主函数返回0，表示程序正常结束
}

