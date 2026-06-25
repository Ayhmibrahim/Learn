#include <iostream>
#include <string>
using namespace std;

string ReadName()
{
    string Name;

    cout << "Please Enter your Name\n";
    cin.ignore();
    getline(cin, Name);

    return Name;
}



int main()
{
    string S1 = ReadName();

    cout << "\nYour String Length is: " << S1.length();

    return 0;
}