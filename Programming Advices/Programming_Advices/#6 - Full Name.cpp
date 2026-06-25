#include <iostream>
using namespace std;

string ReadFirstName()
{
    string FirstName;
    cout << "Enter First Name: ";
    cin >> FirstName;
    return FirstName;
}

string ReadLastName()
{
    string LastName;
    cout << "Enter Last Name: ";
    cin >> LastName;
    return LastName;
}

string FullName(string FirstName, string LastName, bool Reverse = false)
{
    return Reverse
        ? LastName + " " + FirstName
        : FirstName + " " + LastName;
}

int main()
{
    string FirstName = ReadFirstName();
    string LastName = ReadLastName();

    cout << FullName(FirstName, LastName, true);

    return 0;
}