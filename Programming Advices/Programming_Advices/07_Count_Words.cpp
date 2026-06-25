// 07_Count_Words.cpp
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

int CountWords(string S1)
{
    short Counter = 0;

    bool insideWord = false;

    for (short i = 0; i < S1.length(); i++)
    {
        if (S1[i] != ' ')
        {
            if (insideWord == false)
            {
                if (isupper(S1[i]))
                {
                    Counter++;
                    insideWord = true;
                }
            }
        }
        else
        {
            insideWord = false;
        }
    }

    return Counter;
}

int main()
{
    string S1 = ReadName();

    cout << "\n\nCounter Words is: " << CountWords(S1);
    

    cout << "\n\n";
    return 0;
}