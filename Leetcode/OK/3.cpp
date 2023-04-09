// 无重复字符的最长子串
#include "iostream"
#include "string"
#include "algorithm"
#include "vector"
#include "map"
#include "cstring"
using namespace std;
int lengthOfLongestSubstring(string s)
{
    map<char, uint16_t> pos;
    int16_t max_ = 0;
    int16_t head = 0;
    int16_t count = 0;
    for (uint16_t i = 0; i < s.size(); i++)
    {
        if (pos.find(s[i]) != pos.end())
        {
            max_ = max(count, max_);
            if (head <= pos[s[i]])
            {
                count = count - (pos[s[i]] - head);
                head = pos[s[i]] + 1;
            } else count++;
            pos[s[i]] = i;
        }
        else
        {
            pos[s[i]] = i;
            count++;
        }
    }
    max_ = max(count, max_);
    return max_;
}

int main()
{
    string pojo1 = "tmmzuxt";   // 3
    string pojo2 = "bbbbb";  // 1
    string pojo3 = "pwwkew"; // 3
    cout << lengthOfLongestSubstring(pojo1) << endl;
    // cout << lengthOfLongestSubstring(pojo2) << endl;
    // cout << lengthOfLongestSubstring(pojo3) << endl;
}