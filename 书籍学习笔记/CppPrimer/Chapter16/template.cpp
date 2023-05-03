#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template<typename T, int VAL>
T addValue(const T & x)
{
	return x + VAL;
}

int main()
{
	vector<int> vec{ 9,5,1,2,3,4 };

	transform(vec.begin(), vec.end(), vec.begin(), addValue<int, 5>);
	for (const auto& elem : vec)
	{
		cout << elem << " ";
	}
	cout << endl;

	return 0;
}
