// 11_Longest_Word.cpp
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

string PrintEachWord(string S1)
{
    string word = "";
    string MaxWord = "";
    int MaxLength;

    for (int i = 0; i < S1.length(); i++)
    {
        if (S1[i] != ' ')
        {
            word += S1[i];
        }
 
        else
        {
            if (word != "")
            {
                if (word.length() > MaxWord.length())
                {
                    MaxWord = word;
                }
                word = "";
            }
        }
    }

    if (word != "")
    {
        if (word.length() > MaxWord.length())
        {
            MaxWord = word;
        }
    }
 
    return MaxWord;
}



int main()
{

    string S1 = ReadString();


    cout << "\n\nLongest Word is:\n";
    cout << PrintEachWord(S1) << endl;

    return 0;

}