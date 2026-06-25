#include <iostream>
using namespace std;

void ReadNumbers(int& Num1, int& Num2, int& Num3)
{
    cout << "Enter Num1: ";
    cin >> Num1;

    cout << "Enter Num2: ";
    cin >> Num2;

    cout << "Enter Num3: ";
    cin >> Num3;
}

int MaxOf2Numbers(int Num1, int Num2, int Num3)
{
    return (Num1 >= Num2 && Num1 >= Num3) ? Num1 :
        (Num2 >= Num1 && Num2 >= Num3) ? Num2 :
        Num3;
}

void PrintResults(int Max)
{
    cout << "\nMax of 2 Numbers = " << Max << endl;
}

int main()
{
    int Num1, Num2,Num3;

    ReadNumbers(Num1, Num2, Num3);

    PrintResults(MaxOf2Numbers(Num1, Num2, Num3));

    return 0;
}