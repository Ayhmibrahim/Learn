// 10_Last_Word.cpp
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

string PrintLastWord(string S1)
{
    string word = "";
    string ResultWord;

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
                ResultWord = word;
                word = "";
            }
        }
    }

    if (word != "")
    {
        ResultWord = word;
    }
    return ResultWord;
}


int main()
{

    string S1 = ReadString();


    cout << "\n\nPrint First Word is:\n";
    cout << PrintLastWord(S1) << endl;


    return 0;

}