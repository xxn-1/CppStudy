/*
 * @Author: xu
 * @Date:   2023-03-29 16:46:00
 * @Last Modified by:
 * @Last Modified time: 2023-03-29 17:29:54
 * @Function:两数相加
 */
#include <iostream>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
    int u = 0;
    ListNode head;
    ListNode *t = &head;
    while (l1 != nullptr || l2 != nullptr)
    {
        ListNode *tmp = new ListNode();
        if (l1 != nullptr && l2 != nullptr)
        {
            tmp->val = (l1->val + l2->val + u) % 10;
            u = (l1->val + l2->val + u) / 10;
            l1 = l1->next, l2 = l2->next;
            // cout << l1->val << " " << l2->val << endl;
        }
        else if (l1 != nullptr)
        {
            tmp->val = (l1->val + u) % 10;
            u = (l1->val + u) / 10;
            l1 = l1->next;
        }
        else
        {
            tmp->val = (l2->val + u) % 10;
            u = (l2->val + u) / 10;
            l2 = l2->next;
        }
        t->next = tmp;
        // cout<<"==";
        t = t->next;
    }
    if (u)
    {
        ListNode *tmp = new ListNode();
        tmp->val = u;
        t->next = tmp;
    }

    return head.next;
}
int main()
{
    // ListNode l1(2), l2(4), l3(3);
    // l1.next = &l2, l2.next = &l3, l3.next = nullptr;
    // ListNode l4(5), l5(6), l6(4);
    // l4.next = &l5, l5.next = &l6, l6.next = nullptr;
    // ListNode l1(0);
    // ListNode l4(0);
    ListNode l1(9), l2(9), l22(9), l222(9), l2222(9), l22222(9), l222222(9);
    l1.next = &l2, l2.next = &l22, l22.next = &l222, l222.next = &l2222, l2222.next = &l22222, l22222.next = &l222222;
    ListNode l4(9), l5(9), l6(9), l7(9);
    l4.next = &l5, l5.next = &l6, l6.next = &l7;
    ListNode *t = addTwoNumbers(&l1, &l4);

    do
    {
        cout << t->val << " ";
        t = t->next;
    } while (t);
    return 0;
}
