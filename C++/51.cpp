#include <iostream> // 引入输入输出流库，用于控制台输入输出
using namespace std; // 使用标准命名空间，方便直接使用cin, cout等

// 定义链表结点结构体
struct ListNode {
    int val; // 结点存储的整型数值
    ListNode* m_pNext; // 指向下一个结点的指针
    // 构造函数，初始化结点值，并将next指针置为空
    ListNode(int x) : val(x), m_pNext(nullptr) {}
};

int main() {
    int n; // 用于存储链表结点的个数
    // 使用while循环处理多组输入，只要能读取到n就继续执行
    while (cin >> n) {
        // 定义链表的头指针，初始为空
        ListNode* head = nullptr;
        // 定义链表的尾指针，用于尾插法构建链表，初始为空
        ListNode* tail = nullptr;
        
        // 循环n次，读取n个结点的值并构建链表
        for (int i = 0; i < n; ++i) {
            int val; // 临时变量存储输入的结点值
            cin >> val; // 读取结点值
            ListNode* newNode = new ListNode(val); // 创建新结点
            
            if (head == nullptr) {
                // 如果链表为空，新结点即为头结点
                head = newNode;
                tail = newNode; // 尾指针也指向该结点
            } else {
                // 如果链表不为空，将新结点接到尾结点后面
                tail->m_pNext = newNode;
                tail = newNode; // 更新尾指针指向新的尾结点
            }
        }
        
        int k; // 用于存储要求输出的倒数第k个结点的k值
        cin >> k; // 读取k值
        
        // 如果k非法（小于等于0）或者链表为空，直接进入下一轮循环（虽然题目保证k<=n，但做个防御性编程）
        if (k <= 0 || head == nullptr) {
            continue; 
        }

        // 使用双指针法查找倒数第k个结点
        ListNode* fast = head; // 快指针，初始指向头结点
        ListNode* slow = head; // 慢指针，初始指向头结点
        
        // 让快指针先移动k步
        while (k > 0 && fast != nullptr) {
            fast = fast->m_pNext; // 快指针向后移动一步
            k--; // 步数减一
        }
        
        // 如果快指针移动k步后已经超出链表范围（即k > n的情况，虽然题目保证k<=n），说明倒数第k个不存在
        // 这里根据题目逻辑，如果k=n，fast会变成nullptr，这是正常的
        // 此时slow还在head，正好是倒数第n个（即第1个）
        
        // 同时移动快慢指针，直到快指针指向链表末尾（nullptr）
        while (fast != nullptr) {
            fast = fast->m_pNext; // 快指针向后移动
            slow = slow->m_pNext; // 慢指针向后移动
        }
        
        // 此时slow指向的就是倒数第k个结点，输出其值
        if (slow != nullptr) {
            cout << slow->val << endl;
        }
        
        // 释放链表内存，防止内存泄漏
        ListNode* curr = head; // 当前指针指向头结点
        while (curr != nullptr) {
            ListNode* next = curr->m_pNext; // 保存下一个结点指针
            delete curr; // 删除当前结点
            curr = next; // 移动到下一个结点
        }
    }
    
    return 0; // 程序正常结束
}
