#include <iostream>

using namespace std;

void ReadArrayData(int Arr1[100], int& Length)
{
	cout << "How Many Number do you want to enter? 1 to 100?" << endl;
	cin >> Length;

	for (int i = 0; i < Length; i++)
	{
		cout << "Please enter Number " << i+1 << endl;
		cin >> Arr1[i];
	}
}

void PrintArrayData(int Arr1[100], int Length)
{
	for (int i = 0; i < Length; i++)
	{
		
		cout << "Number [" << i + 1 << "] : " << Arr1[i] << endl;

	}
}

int CalculateArraySum(int Arr1[100], int Length)
{
	int Sum = 0;

	for (int i = 0; i < Length; i++)
	{
		Sum += Arr1[i];
	}

	return Sum;
}

float CalculateArrayAverage(int Arr1[100], int Length)
{
	return (float)CalculateArraySum(Arr1, Length) / Length;
}
int main()
{

	int Array[100], Length = 0;
	ReadArrayData(Array, Length);
	PrintArrayData(Array, Length);

	cout << "\n*************************************\n";
	cout << "Sum = " << CalculateArraySum(Array, Length) << endl;
	cout << "Average = " << CalculateArrayAverage(Array, Length) << endl;
}