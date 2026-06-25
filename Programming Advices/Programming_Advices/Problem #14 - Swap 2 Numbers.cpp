#include <iostream>
using namespace std;


void ReadNumbers(int& Number1, int& Number2)
{
    cout << "========================\n";
    cout << "      Enter Numbers\n";
    cout << "========================\n\n";

    cout << "Enter First Number  : ";
    cin >> Number1;

    cout << "Enter Second Number : ";
    cin >> Number2;
}


void SwapNumbers(int& Number1, int& Number2)
{
    int Temp = Number1;
    Number1 = Number2;
    Number2 = Temp;
}


void PrintNumbers(int Number1, int Number2)
{
    cout << "\n========================\n";
    cout << "       After Swap\n";
    cout << "========================\n\n";

    cout << "First Number  : " << Number1 << endl;
    cout << "Second Number : " << Number2 << endl;
}


int main()
{
    int Number1, Number2;

    ReadNumbers(Number1, Number2);

    SwapNumbers(Number1, Number2);

    PrintNumbers(Number1, Number2);

    return 0;
}