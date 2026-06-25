#include <iostream>
using namespace std;


class clsPerson
{
private:
    int _Age;
    string _FirstName;
    string _LastName;
    bool _ChackAge;

public:

    void setFirstName(string FirstName)
    {
        _FirstName = FirstName;
    }

    string FirstName()
    {
        return _FirstName;
    }

    void setLastName(string LastName)
    {
        _LastName = LastName;
    }

    string LastName()
    {
        return _LastName;
    }

    void setAgePerson(int Age)
    {
        _Age = Age;
    }

    int Age()
    {
        return _Age;
    }

    string FullName()
    {
        return _FirstName + " " + _LastName;
    }
};

int main() {


    clsPerson Person1;

    Person1.setFirstName("Ayhm");
    Person1.setLastName("Ibrahim");
    Person1.setAgePerson(15);

    if (Person1.Age() < 20)
    {
        cout << "My Dear " << Person1.FullName();
        cout << "\nYour Age is teen You can Enter";
    }
    else
    {
        cout << "My Dear " << Person1.FullName();
        cout << "\nYour Age is Old So You can't Enter";
    }
    return 0;
}