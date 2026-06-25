#include <iostream>
using namespace std;

int ReadMark()
{
    int Mark;
    cout << "\nEnter Mark: ";
    cin >> Mark;
    return Mark;
}

bool CheckMark(int Mark)
{
    return Mark >= 50 ? true : false;
}


int main()
{
    int Mark = ReadMark();

    CheckMark(Mark) ? cout << "\nPass" : cout << "\nFail";
}