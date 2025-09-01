#include <iostream>
using namespace std;

bool is_leap(int y)
{
	bool answer = false;

	if (y % 400 == 0)
		answer = true;

	else if (y % 4 == 0)
	{
		answer = true;

		if (y % 100 == 0)
			answer = false;
	}


	return answer;
}

int main()
{
	cout << boolalpha << is_leap(2000) << " " << is_leap(1900) << " " << is_leap(2024) << "\n"; // true false true
}