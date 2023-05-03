/*
 * @Author:
 * @Date:   2023-04-06 10:18:10
 * @Last Modified by:
 * @Last Modified time: 2023-04-06 10:33:38
 * @Function:
 */
#include <algorithm>
#include <iostream>
#include <istream>
#include <iterator>
#include <vector>
using namespace std;
int main(int argc, char const *argv[])
{
    istream_iterator< int > initer(cin), eof;
    vector< int > nums(initer, eof);
    cout << nums.size() << endl;
    ostream_iterator< int > out_iter(cout," ");
    copy(nums.begin(),nums.end(),out_iter);
    cout << endl;
    return 0;
}
