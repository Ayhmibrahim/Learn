#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


void PrintMatrix(int arr[3][3], short Rows, short Cols)
{
	for (short i = 0; i < Rows; i++)
	{
		for (short j = 0; j < Cols; j++)
		{
			cout << setw(3) << arr[i][j] << " ";
		}
		cout << "\n";
	}
}

int CheckNumberMax(int Matrix1[3][3] ,
	short Rows, short Cols)
{

	int Max = Matrix1[0][0];
	for (short i = 0; i < Rows; i++)
	{
		for (short j = 0; j < Cols; j++)
		{
			if (Matrix1[i][j] > Max)
				Max = Matrix1[i][j];
		}

	}

	return Max;
}

int CheckNumberMin(int Matrix1[3][3],
	short Rows, short Cols)
{

	int Min= Matrix1[0][0];
	for (short i = 0; i < Rows; i++)
	{
		for (short j = 0; j < Cols; j++)
		{
			if (Matrix1[i][j] < Min)
				Min = Matrix1[i][j];
		}

	}

	return Min;
}



int main()
{

	int Matrix1[3][3] = { {77,5,12},{22,20,1},{1,3,9} };
	cout << "\nMatrix1:\n";
	PrintMatrix(Matrix1, 3, 3);
	cout << "\nMinimum Number is: "<< CheckNumberMin(Matrix1, 3, 3)<<endl;
	cout << "\nMax Number is: "<< CheckNumberMax(Matrix1, 3, 3) << endl;
	
	system("pause>0");

}