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

int AverageOf3Number(int Num1, int Num2, int Num3)
{
    int Average = 0;

    return Average /= Num1 + Num2 + Num3;
}

void PrintResults(int Total)
{
    cout << "\nAverage  of 3 Numbers = " << Total << endl;
}

int main()
{
    int Num1, Num2, Num3;
    ReadNumbers(Num1, Num2, Num3);
    PrintResults(AverageOf3Number(Num1, Num2, Num3));

}