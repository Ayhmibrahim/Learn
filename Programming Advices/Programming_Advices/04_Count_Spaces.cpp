// 04_Count_Spaces.cpp
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

int CountSpaces(string S1)
{
    short Counter = 0;

    for (short i = 0; i < S1.length(); i++)
    {
        if (S1[i] == ' ')
        {
            Counter++;
        }
    }

    return Counter;
}

int main()
{
    string S1 = ReadName();

    cout << "\n\nCounter Spaces is: " << CountSpaces(S1);

    return 0;
}