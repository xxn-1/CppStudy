/*
 * @Author: xu
 * @Date:   2023-03-29 16:46:00
 * @Last Modified by:
 * @Last Modified time: 2023-03-29 17:29:54
 * @Function:两数相加
 */
#include <iostream>
using namespace std;
bool m[101][101];
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
ListNode *l;
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
    int u = 0;
    ListNode *t = l;

    while (l1 != nullptr || l2 != nullptr)
    {
        ListNode *tmp;

        if (l1 != nullptr && l2 != nullptr)
        {
            tmp.val = (l1->val + l2->val + u) % 10;
            u = (l1->val + l2->val + u) / 10;
            l1 = l1->next, l2 = l2->next;
        } else if (l1 != nullptr)
        {
            tmp.val = (l1->val + u) % 10;
            u = (l1->val + u) / 10;
            l1 = l1->next;
        } else
        {
            tmp.val = (l2->val + u) % 10;
            u = (l2->val + u) / 10;
            l2 = l2->next;
        }
        cout<<"==";

        t->next = &tmp;

        t = t->next;

    }
    cout << "===" << endl;
    return l->next;
}
int main()
{
    ListNode l1(2), l2(4), l3(3);
    l1.next = &l2, l2.next = &l3, l3.next = nullptr;
    ListNode l4(5), l5(6), l6(4);
    l4.next = &l5, l5.next = &l6, l6.next = nullptr;
    ListNode *t = addTwoNumbers(&l1, &l4);
    do
    {
        cout << t->val << " ";
        t = t->next;
    }
    while (t);
    return 0;
}
