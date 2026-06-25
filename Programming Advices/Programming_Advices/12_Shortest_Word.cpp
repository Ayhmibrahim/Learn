// 12_Shortest_Word.cpp
// Auto generated file

#include <iostream>
#include <string>

using namespace std;

string ReadString()
{
    string S1;

    cout << "Please Enter your string\n";
    getline(cin, S1);

    return S1;
}

string PrintShortestWord(string S1)
{
    string word = "";
    string MinWord = "";
    int MinLength = 0;

    for (int i = 0; i < S1.length(); i++)
    {
        if (S1[i] != ' ')
        {
            word += S1[i];
        }

        else
        {
            if (word !="")
            {
                if (MinWord == "" || word.length() < MinWord.length())
                {
                    MinWord = word;
                }
                word = "";
            }
        }
    }

    if (word != "")
    {
        if (MinWord == "" || word.length() < MinWord.length())
        {
            MinWord = word;
        }
    }
    
    return MinWord;
}


int main()
{

    string S1 = ReadString();


    cout << "\n\nShortest Word is:\n";
    cout << PrintShortestWord(S1) << endl;

    return 0;
}