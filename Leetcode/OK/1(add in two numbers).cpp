/*
 * @Author: xu
 * @Date:   2023-03-29 10:29:43
 * @Last Modified by:
 * @Last Modified time: 2023-03-29 12:25:34
 * @Function:两数之和
 */
#include <iostream>
#include <vector>
using namespace std;
void swap(vector< int > &nums, int i, int j)
{
    int temp;
    temp = nums[i], nums[i] = nums[j], nums[j] = temp;
}
void quickSort(vector< int > &nums, int begin, int end)
{
    if (begin >= end)
        return;
    int b = begin, e = end;
    while (b < e)
    {
        while (nums[b] <= nums[e] && b < e)
        {
            e--;
        }
        if (b < e && nums[b] > nums[e])
        {
            swap(nums, b, e);
        }
        while (nums[e] <= nums[b] && b < e)
        {
            b++;
        }
        if (b < e && nums[b] > nums[e])
        {
            swap(nums, b, e);
        }
    }
    quickSort(nums, begin, b);
    quickSort(nums, b + 1, end);
}
int main(int argc, char const *argv[])
{
    vector< int > v = {1, 53, 2, 509, 21, 23, 5, -4, 65};
    vector< int > temp(v);
    int u = 26;
    quickSort(v, 0, v.size());
    int sum = v[0] + v[v.size() - 1];
    cout << sum << endl;
    int b = 0, e = v.size() - 1;
    for (auto x : v)
    {
        cout << x << " ";
    }
    cout << endl;
    while (u != sum && e != b)
    {
        if (sum > u)
            e--;
        else
            b++;
        sum = v[b] + v[e];
    }
    bool flag = false;
    int i1, i2;
    for (int i = 0; i < v.size(); i++)
    {
        if (temp[i] == v[b] || temp[i] == v[e] && flag)
        {
            i2 = i;
            break;
        }
        if (temp[i] == v[b] || temp[i] == v[e] && !flag)
        {
            i1 = i;
            flag = true;
        }
    }
    cout << b << " " << e << endl;
    return 0;
}
