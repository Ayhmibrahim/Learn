// 03_First_And_Last_Char.cpp
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

void PrintFirstAndLastChar(string S1)
{

    if (S1.length()==0)
    {
        cout << "String Is empty\n";
    }
    else {
        cout << "\n\nFirst Char: " << S1[0] << endl;
        cout << "Last Char: " << S1[S1.length() - 1];
    }
    cout << "\n\n";
}

int main()
{
    string S1 = ReadName();

    PrintFirstAndLastChar(S1);

    return 0;
}