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

bool ReadRecommendation()
{
	char Choice;

	cout << "\nDo you have a recommendation? (y/n): ";
	cin >> Choice;

	return Choice == 'y' || Choice == 'Y';
}

bool CheckResult(bool HassRecommendation ,int Age, char HasDriveLicense)
{

	return HassRecommendation ? true : 
		(Age >= 21 &&
		(HasDriveLicense == 'y' || HasDriveLicense == 'Y'));

}

int main()
{
	short Age = ReadAge();
	char HasDriveLicense = ReadHasDriveLicense();
	bool HasRecommendation = ReadRecommendation();

	if (CheckResult(HasRecommendation,Age, HasDriveLicense))
		cout << "\nHired";
	else
		cout << "Rejected";


}