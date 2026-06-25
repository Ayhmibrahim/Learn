#include <iostream>
#include <string>

using namespace std;

struct stEmployee
{
	string EmployeeID;
	string Password;
	string FullName;
	string Email;
	double Salary;
};

stEmployee ReadNewEmployee()
{
	stEmployee Employee;

	cout << "Enter EmployeeID? ";
	getline(cin, Employee.EmployeeID);

	cout << "Enter Password? ";
	getline(cin, Employee.Password);

	cout << "Enter FullName? ";
	getline(cin, Employee.FullName);

	cout << "Enter Email? ";
	getline(cin, Employee.Email);

	cout << "Enter Salary? ";
	cin >> Employee.Salary;

	return Employee;
}

string ConvertEmployeeToLine(stEmployee Employee, string Seperator = "#//#")
{
	string stEmployeeRecord = "";

	stEmployeeRecord += Employee.EmployeeID + Seperator;
	stEmployeeRecord += Employee.Password + Seperator;
	stEmployeeRecord += Employee.FullName + Seperator;
	stEmployeeRecord += Employee.Email + Seperator;
	stEmployeeRecord += to_string(Employee.Salary) + Seperator;

	return stEmployeeRecord;
}

int main()
{
	cout << "\nPlease Enter Employee Data: \n\n";

	stEmployee Employee;
	Employee = ReadNewEmployee();

	cout << "Employee Record for Saving is:\n"
		<< ConvertEmployeeToLine(Employee);

	system("pause>0");
	return 0;
}