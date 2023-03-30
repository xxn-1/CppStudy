/*
 * @Author: xu
 * @Date:   2023-03-30 13:46:36
 * @Last Modified by:
 * @Last Modified time: 2023-03-30 15:15:22
 * @Function: 表达式求值
 */
#include "iostream"
#include <cctype>
#include <stack>
#include <stdexcept>
#include <string>
using namespace std;
enum P
{
    ADD,
    SUB,
    MUL,
    DIV,
    BRA
};
void op(stack< double > &nums, stack< char > &punc, P tmp)
{
    if (tmp == BRA)
    {
        punc.pop();
        return;
    }
    double a = nums.top();
    nums.pop();
    double b = nums.top();
    nums.pop();
    punc.pop();
    switch (tmp)
    {
    case ADD:
    {
        nums.push(a + b);
        if (!punc.empty() && punc.top() == '(')
            punc.pop();
        break;
    }
    case SUB:
    {
        nums.push(b - a);
        if (!punc.empty() && punc.top() == '(')
            punc.pop();
        break;
    }
    case MUL:
    {
        nums.push(a * b);
        if (!punc.empty() && punc.top() == '(')
            punc.pop();
        break;
    }
    case DIV:
    {
        if (a == 0)
        {
            throw runtime_error("divide 0");
            return;
        }
        nums.push(b / a);
        if (!punc.empty() && punc.top() == '(')
            punc.pop();
        break;
    }
    }
}
double evaluation(string s)
{
    stack< double > nums;
    stack< char > punc;
    int neg = 1;
    bool flag = false;
    auto beg = s.begin();
    while (beg != s.end())
    {
        if (isblank(*beg))
        {
            beg++;
            continue;
        }
        if (isdigit(*beg))
        {
            int u = 0;
            while (beg != s.end() && isdigit(*beg))
            {
                u = u * 10 + (*beg - '0');
                beg++;
            }
            u *= neg;
            nums.push(u);
            if (!punc.empty() && punc.top() == '*')
            {
                op(nums, punc, MUL);
            } else if (!punc.empty() && punc.top() == '/')
            {
                try
                {
                    op(nums, punc, DIV);
                }
                catch (runtime_error e)
                {
                    cout << e.what() << endl;
                    return 0;
                }
            }
            flag = false, neg = 1;
        } else
        {
            switch (*beg)
            {
            case '(':
            {
                punc.push(*beg);
                break;
            }
            case ')':
            {
                char c = punc.top();
                switch (c)
                {
                case '+':
                {
                    op(nums, punc, ADD);
                    break;
                }
                case '-':
                {
                    op(nums, punc, SUB);
                    break;
                }
                case '*':
                {
                    op(nums, punc, MUL);
                    break;
                }
                case '/':
                {
                    try
                    {
                        op(nums, punc, DIV);
                    }
                    catch (runtime_error e)
                    {
                        cout << e.what() << endl;
                        return 0;
                    }
                    break;
                }
                default:
                {
                    op(nums, punc, BRA);
                    break;
                }
                }
                break;
            }
            default:
            {
                if (flag && *beg == '-')
                    neg = -1;
                else
                {
                    punc.push(*beg);
                }
                break;
            }
            }
            flag = true;
            beg++;
        }
    }
    while (!punc.empty())
    {
        if (punc.top() == '+')
            op(nums, punc, ADD);
        else
            op(nums, punc, SUB);
    }
    if (nums.size() == 1)
        return nums.top();
    else
    {
        return 0;
    }
}
int main(int argc, char const *argv[])
{
    string s;
    printf("请输入表达式!\n");
    while (getline(cin, s))
    {
        cout << "计算结果:" << evaluation(s) << endl;
        printf("请输入表达式!\n");
    }
    return 0;
}
