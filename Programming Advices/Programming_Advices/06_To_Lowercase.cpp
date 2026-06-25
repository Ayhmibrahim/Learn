// 06_To_Lowercase.cpp
// Auto generated file

#include <iostream>
#include <string>
using namespace std;

string ReadName()
{
    string Name;

    cout << "Please Enter your Name\n";
    getline(cin, Name);

    return Name;
}


string ChangeCharToLowerCase(string S1)
{

    for (int i = 0; i < S1.length(); i++)
    {
        S1[i] = tolower(S1[i]);
    }
    return S1;
}



int main()
{
    string S1 = ReadName();

    cout << "\n\nLower Case Is: " << ChangeCharToLowerCase(S1);

    cout << "\n\n";
    return 0;
}