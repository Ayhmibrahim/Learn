#include <iostream>
using namespace std;


short ReadAge()
{
	short Number = 0;

	cout << "\nEnter your Age: ";
	cin >> Number;

	return Number;
}

char ReadHasDriveLicense()
{
	char HasDriveLicense;

	cout << "\nDo you have a driving license? (y/n): ";
	cin >> HasDriveLicense;

	return HasDriveLicense;
}

bool CheckResult(int Age , char HasDriveLicense)
{

	return Age >= 21 && (HasDriveLicense == 'y' || HasDriveLicense == 'Y');

}

int main()
{
	short Age = ReadAge();
	char HasDriveLicense = ReadHasDriveLicense();

	if (CheckResult(Age, HasDriveLicense))
		cout << "\nHired";
	else
		cout << "Rejected";
	

}