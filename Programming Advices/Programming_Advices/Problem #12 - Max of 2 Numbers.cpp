#include <iostream>
using namespace std;

void ReadNumbers(int& Num1, int& Num2)
{
    cout << "Enter Num1: ";
    cin >> Num1;

    cout << "Enter Num2: ";
    cin >> Num2;
}

int MaxOf2Numbers(int Num1, int Num2)
{
    return (Num1 >= Num2) ? Num1 : Num2 ;
}

void PrintResults(int Max)
{
    cout << "\nMax of 2 Numbers = " << Max << endl;
}

int main()
{
    int Num1, Num2;

    ReadNumbers(Num1, Num2);

    PrintResults(MaxOf2Numbers(Num1, Num2));

    return 0;
}