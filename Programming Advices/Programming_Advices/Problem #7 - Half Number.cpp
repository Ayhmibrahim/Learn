#include <iostream>
using namespace std;

int ReadNumber()
{
    int Number;
    cout << "\nEnter Number: ";
    cin >> Number;
    return Number;
}

int HalfNumber(int Number)
{
    return Number / 2;
}


int main()
{
   
    int Number = ReadNumber();

    cout << "\nHalf of " << Number << " is " << HalfNumber(Number) << endl;

}