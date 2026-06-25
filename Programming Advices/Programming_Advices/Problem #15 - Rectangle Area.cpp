#include <iostream>
using namespace std;


void ReadRectangleDimensions(float& Width, float& Length)
{
    cout << "========================\n";
    cout << "   Rectangle Dimensions\n";
    cout << "========================\n\n";

    cout << "Enter Width  : ";
    cin >> Width;

    cout << "Enter Length : ";
    cin >> Length;
}


float CalculateRectangleArea(float Width, float Length)
{
    return Width * Length;
}


void PrintRectangleArea(float Area)
{
    cout << "\n========================\n";
    cout << "    Rectangle Area\n";
    cout << "========================\n\n";

    cout << "Area = " << Area << endl;
}


int main()
{
    float Width, Length;

    ReadRectangleDimensions(Width, Length);

    float Area = CalculateRectangleArea(Width, Length);

    PrintRectangleArea(Area);

    return 0;
}