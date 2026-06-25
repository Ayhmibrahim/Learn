// 05_To_Uppercase.cpp
// Auto generated file


// 04_Count_Spaces.cpp
// Auto generated file

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string ReadName()
{
    string Name;

    cout << "Please Enter your Name\n";
    getline(cin, Name);

    return Name;
}

string ChangeCharToUpperCase(string S1)
{
    for (int i = 0; i < S1.length(); i++)
    {
        S1[i] = toupper(S1[i]);
    }

    return S1;
}

int main()
{
    string S1 = ReadName();

    cout << "\n\nUpper Case Is: " << ChangeCharToUpperCase(S1);

    cout << "\n\n";
    return 0;
}