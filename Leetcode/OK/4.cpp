// 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。
// 算法的时间复杂度应该为 O(log (m+n)) 。
// 示例
// 输入：nums1 = [1,3], nums2 = [2]
// 输出：2.00000
// 解释：合并数组 = [1,2,3] ，中位数 2
// 示例 2：
// 输入：nums1 = [1,2], nums2 = [3,4]
// 输出：2.50000
// 解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5
// nums1.length == m
// nums2.length == n
// 0 <= m <= 1000
// 0 <= n <= 1000
// 1 <= m + n <= 2000
// -106 <= nums1[i], nums2[i] <= 106
#include <iostream>
#include <vector>

using namespace std;

void mergeDemo(int begin, int end, vector<int> &nums, vector<int> &res)
{
    if (begin >= end)
        return;

    int len = end - begin, mid = len / 2 + begin;

    int start1 = begin, end1 = mid;
    int start2 = mid + 1, end2 = end;
    mergeDemo(start1, end1, nums, res);
    mergeDemo(start2, end2, nums, res);
    int k = begin;

    while (start1 <= end1 && start2 <= end2)
    {

        res[k++] = nums[start1] < nums[start2] ? nums[start1++] : nums[start2++];
    }
    while (start1 <= end1)
        res[k++] = nums[start1++];
    while (start2 <= end2)
        res[k++] = nums[start2++];
    for (k = begin; k <= end; k++)
        nums[k] = res[k];
}
vector<int> mergeSort(vector<int> &nums1, vector<int> &nums2)
{
    vector<int> merge = nums1;
    merge.insert(merge.end(), nums2.begin(), nums2.end());
    int l = merge.size();
    vector<int> res;
    res.resize(2001);
    mergeDemo(0, l - 1, merge, res);
    return merge;
}
double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
// 排好序的
{
    if (nums1.empty() && nums2.empty())
        return 0;
    vector<int> res = mergeSort(nums1, nums2);
    int l = res.size();
    if (l & 1)
        return res[l / 2];
    else
        return (double)(res[l / 2] + res[l / 2 - 1]) / 2.00;
}

int main()
{
    // vector<int> v1{1, 3}, v2{2}; // 2
    // vector<int> v1{1, 3}, v2{2,4}; // 2.5
    // vector<int> v1{1, 3, 5}, v2{2,4}; // 2.5
    // vector<int> v1{1, 4}, v2{2, 3}; // 2.5
    vector<int> v1{2}, v2{3}; // 2.5

    // vector<int> v1{1, 3}, v2{2};
    cout << findMedianSortedArrays(v1, v2) << endl;
}
// (m+n)/2 = i,i+1; (m+n)/2 +1