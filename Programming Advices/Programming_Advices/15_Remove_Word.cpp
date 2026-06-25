// 15_Remove_Word.cpp
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

string RemoveWordsInString(string S1, string target)
{
    // نقسم الجملة إلى كلمات ونخزنها في vector
    vector<string> vWords = SplitString(S1, " ");

    // هذا المتغير سنبني فيه الجملة النهائية بعد الحذف
    string result = "";

    // نمشي على كل كلمة داخل الـ vector
    for (string& word : vWords)
    {
        // إذا الكلمة ليست هي الكلمة المطلوب حذفها
        if (word != target)
        {
            // نضيفها إلى النتيجة مع مسافة
            result += word + " ";
        }
        // إذا كانت هي target → نتجاهلها (لا نضيفها)
    }

    // حذف المسافة الزائدة في آخر الجملة
    if (!result.empty())
    {
        result = result.substr(0, result.length() - 1);
    }

    // إرجاع الجملة بعد حذف الكلمة
    return result;
}

int main()
{
    string S1 = ReadString();


    cout << "\n\nString after replacing  word:\n" << RemoveWordsInString(S1, "Laptop");

    system("pause>0");
}