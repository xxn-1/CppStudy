/*
 * @Author: xu
 * @Date:   2023-03-28 10:20:01
 * @Last Modified by: xu
 * @Last Modified time: 2023-03-28 13:05:24
 * @Function:
 */
#include "Sales_item.h"
using namespace std;
int main()
{
    Sales_item book1;
    Sales_item book2;
    cin >> book1 >> book2;
    cout << book1 << endl << book2 << endl;
    Sales_item book = book1 + book2;
    if (book1 == book2)
        cout << book << endl;

}
