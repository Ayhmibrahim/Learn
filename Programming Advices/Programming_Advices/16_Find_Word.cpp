// 16_Find_Word.cpp
// Auto generated file

#include <iostream>
#include <string>
#include <vector>
using namespace std;

string  ReadString()
{
    string S1;
    cout << "Please Enter Your String?\n";
    getline(cin, S1);
    return S1;
}

vector <string> SplitString(string S1, string Delim)
{
    vector <string> vString;

    short pos = 0;
    string sWord;

    while ((pos = S1.find(Delim)) != std::string::npos) {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}

bool FindWord(string S1, string target )
{
    vector <string> vString = SplitString(S1," ");

    for (string& word : vString)
    {
        if (word == target)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    string S1 = ReadString();

    string target = "Ayham";

    cout << "\n\nDid you find the word?\n";

    if (FindWord(S1, target))
        cout << "Yes, I found it." << endl;

    else
        cout << "I couldn't find it" << endl;

}