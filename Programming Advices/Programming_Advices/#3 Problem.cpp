#include <iostream>

using namespace std;



int ReadNumber()
{
	int Number = 0;

	cout << "Enter Number: ";
	cin >> Number;
	return Number;
}

bool CheckNumber(int Number)
{
	return (Number % 2 == 0);
}

int main()
{

	int Number = ReadNumber();

	if (CheckNumber(Number))
	{
		cout << "\nThis Number is EVEN";
	}
	else
	{
		cout << "\nThis Number is ODD";
	}
	

}