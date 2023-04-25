/*
* @Author:
* @Date:   2023-04-25 10:47:22
* @Last Modified by:
* @Last Modified time: 2023-04-25 11:29:11
* @Function:
*/
#include <iostream>
#include <iterator>
#include <vector>
#include <type_traits>
#include <typeinfo>
using namespace std;


template <typename T> auto getElement(T start_,T end_)->typename remove_reference<decltype(*start_)>::type
{
    return *start_;
}
int main(int argc, char const *argv[])
{
    /* code */
    vector<int>v = {1,41,2,4};
    cout << getElement(v.begin(), v.end()) << endl;
    auto c = getElement(v.begin(), v.end());
    cout << typeid(c).name() << endl;
    int nums[3] = {3,42,2};
    cout << getElement(begin(nums), end(nums)) << endl;
    return 0;
}
