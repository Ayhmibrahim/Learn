#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance = 0.0;
    bool MarkForDelete = false;
};

struct stUser
{
    string Username;
    string Password;
    short Permissions = 0;
    bool MarkForDelete = false;

};

enum enPermissionsOptions { eFullAccess = -1, eShowClients = 1, eAddClients = 2, eDeleteClients = 4,
    eUpdateClients = 8, eFindClients = 16, eTransactions = 32,  enManageUsers = 64 };

void ShowMainMenue(stUser& CurrentUser);
void ShowTransactionsMenue(stUser& CurrentUser);
void ShowManageUserMenue(stUser& CurrentUser);
void Login();

vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}

string ConvertRecordUserToLine(stUser User, string Seperator = "#//#")
{
    string stUserRecord = "";

    stUserRecord += User.Username + Seperator;
    stUserRecord += User.Password + Seperator;
    stUserRecord += to_string(User.Permissions);

    return stUserRecord;
}

stUser ConvertLineUserToRecord(string Line, string Seperator = "#//#")
{

    stUser User;
    vector<string> vUserData;

    vUserData = SplitString(Line, Seperator);

    if (vUserData.size() >=3)
    {
        User.Username = vUserData[0];
        User.Password = vUserData[1];
        User.Permissions = stoi(vUserData[2]);
    }

    return User;

}

bool UserExistsByUserName(string UserName, string FileName)
{

    vector <stUser> vUser;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        stUser User;

        while (getline(MyFile, Line))
        {

            User = ConvertLineUserToRecord(Line);
            if (User.Username == UserName)
            {
                MyFile.close();
                return true;
            }


            vUser.push_back(User);
        }

        MyFile.close();

    }

    return false;


}

short ReadPermissionsToSet()
{
    short Permissions = 0;
    char Answer = 'y';

    cout << "Do you want to give full access? y/n?";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        return enPermissionsOptions::eFullAccess;

    cout << "\n\nDo you want to give access to:";

    cout << "\n\nShow Client List? y/n?";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permissions |= enPermissionsOptions::eShowClients;

    cout << "\nAdd New Client List? y/n?";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permissions |= enPermissionsOptions::eAddClients;

    cout << "\nDelete Client List? y/n?";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permissions |= enPermissionsOptions::eDeleteClients;


    cout << "\nUpdate Client List? y/n?";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permissions |= enPermissionsOptions::eUpdateClients;

    cout << "\nFind Client List? y/n?";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permissions |= enPermissionsOptions::eFindClients;

    cout << "\nTransactions? y/n?";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permissions |= enPermissionsOptions::eTransactions;

    cout << "\nManage Users? y/n?";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permissions |= enPermissionsOptions::enManageUsers;

    return Permissions;
}

bool CheckAccessPremissions(short UserPermissions, enPermissionsOptions Permission)
{
    return ((UserPermissions == -1) ? true : (UserPermissions & Permission) == Permission);
}

bool HasAccess(stUser User, enPermissionsOptions Permission)
{
    return CheckAccessPremissions(User.Permissions, Permission);
}

stUser ReadNewUser()
{
    stUser User;

    cout << "Enter Username: ";
    getline(cin >> ws, User.Username);

    while (UserExistsByUserName(User.Username, UsersFileName))
    {
        cout << "\nUser with [" << User.Username << "] already exists, Enter another Username? ";
        getline(cin >> ws, User.Username);
    }

    cout << "Enter Password: ";
    getline(cin >> ws, User.Password);

    User.Permissions = ReadPermissionsToSet();

    return User;
}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double


    return Client;

}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }


            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return false;


}

sClient ReadNewClient()
{
    sClient Client;

    cout << "Enter Account Number? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return vClients;

}

vector <stUser> LoadUsersDataFromFile(string FileName)
{

    vector <stUser> vUsers;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        stUser Users;

        while (getline(MyFile, Line))
        {

            Users = ConvertLineUserToRecord(Line);

            vUsers.push_back(Users);
        }

        MyFile.close();

    }

    return vUsers;

}

void PrintUserRecordLine(stUser User)
{
    cout << "| " << setw(20) << left << User.Username;
    cout << "| " << setw(15) << left << User.Password;
    cout << "| " << setw(10) << left << User.Permissions;
}

void ShowAllUsersScreen()
{
    vector <stUser> vUser = LoadUsersDataFromFile(UsersFileName);

    cout << "\n\t\t\t\t\tUser List (" << vUser.size() << ") User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(20) << "User Name";
    cout << "| " << left << setw(15) << "Password";
    cout << "| " << left << setw(10) << "Permissions";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
 
    if (vUser.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (stUser& Users : vUser)
        {
            PrintUserRecordLine(Users);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

void PrintClientRecordLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void PrintClientRecordBalanceLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void ShowAllClientsScreen()
{
    stUser User;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

void ShowTotalBalances()
{

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;

            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;

}

void PrintUserCard(stUser User)
{
    cout << "\nThe following are the User details:\n";
    cout << "-----------------------------------";
    cout << "\nUsername    : " << User.Username;
    cout << "\nPassword    : " << User.Password;
    cout << "\nPermissions : " << User.Permissions;
    cout << "\n-----------------------------------\n";

}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";

}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{

    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;

}

bool FindUserByUserNameAndPassword(string Username,string Password, vector <stUser> vUser, stUser& User)
{

    for (stUser Users : vUser )
    {

        if (Users.Username == Username && Users.Password == Password)
        {
            User = Users;
            return true;
        }

    }
    return false;
}

bool FindUserByUsername(string Username , vector <stUser> vUsers, stUser& User)
{
    for (stUser U : vUsers)
    {
        if (U.Username == Username)
        {
            User = U;
            return true;
        }
    }

    return false;
}

stUser ChangeUserRecord(string Username)
{
    stUser User;

    User.Username = Username;
    
    cout << "Enter Password: ";
    getline(cin >> ws, User.Password);

    User.Permissions = ReadPermissionsToSet();

    return User;
}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}

bool MarkUserForDeleteByUsername(string Username, vector<stUser>& vUsers)
{

    for (stUser& U  : vUsers)
    {
        if (U.Username == Username)
        {
            U.MarkForDelete = true;
            return true;
        }
    }

    return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    for (sClient& C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }

    return false;

}

vector <stUser> SaveUsersDataToFile(string FileName, vector <stUser> vUsers)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    string DataLine;
    if (MyFile.is_open())
    {
        for (stUser U : vUsers)
        {
            if (U.MarkForDelete == false)
            {
                DataLine = ConvertRecordUserToLine(U);
                MyFile << DataLine << endl;
            }
        }
        
        MyFile.close();
    }

    return vUsers;
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vClients;

}

void AddDataLineToFile(string FileName, string  stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }

}

void AddNewUser()
{
    stUser User;
    User = ReadNewUser();
    AddDataLineToFile(UsersFileName, ConvertRecordUserToLine(User));
}

void AddNewUsers()
{
    char AddMore = 'Y';
    do
    {
        system("cls");
        cout << "Adding New User:\n\n";

        AddNewUser();
        cout << "\nUser Added Successfully, do you want to add more users? Y/N? ";

        cin >> AddMore;

       

    } while (toupper(AddMore) == 'Y');
}

void ShowAddNewUsersScreen()
{
    
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Users Screen";
    cout << "\n-----------------------------------\n";

    AddNewUsers();

}

void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        //system("cls");
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";


        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

bool DeleteUserByUsername(string Username, vector<stUser>& vUsers)
{
    stUser User;
    char Answer = 'n';

    if (FindUserByUsername(Username, vUsers, User))
    {
        PrintUserCard(User);

        cout << "\n\nAre you sure you want delete this User? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkUserForDeleteByUsername(Username, vUsers);
            SaveUsersDataToFile(UsersFileName, vUsers);

            vUsers = LoadUsersDataFromFile(UsersFileName);

            cout << "\n\nUser Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nUser with Username (" << Username << ") is Not Found!";
        return false;
    }

    return false;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            //Refresh Clients 
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }

    return false;
}

bool UpdateUserByUsername(string Username, vector <stUser> vUsers)
{
    stUser User;
    char Answer = 'n';

    if (FindUserByUsername(Username,vUsers,User))
    {
        PrintUserCard(User);
        cout << "\n\nAre you sure you want update this User? y/n ? ";
        cin >> Answer;
        if (Answer == 'y'|| Answer =='Y')
        {
            for (stUser& U : vUsers)
            {
                if (U.Username == Username)
                {
                    U = ChangeUserRecord(U.Username);
                    break;

                }
            }

            SaveUsersDataToFile(UsersFileName,vUsers);
            return true;
        }

    }
    else
    {
        cout << "\nUser with Username (" << Username << ") is Not Found!";
        return false;
    }
    return false;

}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }

            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
    return false;

}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{
    char Answer = 'n';


    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

                return true;
            }

        }


        return false;
    }

    return false;
}

string ReadInput(string Message)
{
    string input = "";

    cout << Message;
    getline(cin >> ws, input); // ws لحل مشكلة buffer

    return input;
}

string ReadClientAccountNumber()
{
    return ReadInput("\nPlease enter AccountNumber? ");

}

string ReadUsername()
{
    return ReadInput("Enter Username? ");
}

string ReadPassword()
{
    return ReadInput("Enter Password? ");
}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);

}

void ShowDeleteUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete User Screen";
    cout << "\n-----------------------------------\n";

    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    string Username = ReadUsername();
    DeleteUserByUsername(Username, vUsers);

}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);

}

void ShowUpdateUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate User Screen";
    cout << "\n-----------------------------------\n";

    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    string Username = ReadUsername();
    UpdateUserByUsername(Username, vUsers);
}

void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();

}

void ShowFindUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind User Screen";
    cout << "\n-----------------------------------\n";


    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    stUser User;
    string Username = ReadUsername();
    if (FindUserByUsername(Username, vUsers, User))
        PrintUserCard(User);
    else
        cout << "\nClient with Account Number[" << Username << "] is not found!";

}
void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";


    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";

}

void ShowLogoutScreen()
{
    Login();

}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";


    sClient Client;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }


    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);

}

void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";



    sClient Client;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;

    //Validate that the amount does not exceeds the balance
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);

}

void ShowTotalBalancesScreen()
{

    ShowTotalBalances();

}

enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3, eShowMainMenue = 4 };

enum enMainMenueOptions { eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6, eManageUsers = 7, eLogout = 8 };

enum enUserManageOptions{ eListUsers = 1, eAddNewUser =2, eDeleteUser =3 , eUpdateUser = 4, eFindUser = 5, eShowMainMenues = 6 };

void GoBackToMainMenue(stUser& CurrentUser)
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue(CurrentUser);
}

void GoBackToTransactionsMenue(stUser& CurrentUser)
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    ShowTransactionsMenue(CurrentUser);

}

void GoBackToUsersMenue(stUser& CurrentUser)
{
    cout << "\n\nPress any key to go back to Users Menue...";
    system("pause>0");
    ShowManageUserMenue(CurrentUser);

}

short ReadInputOption(string Massage)
{
    cout << Massage;
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

short ReadMainMenueOption()
{
    return ReadInputOption("Choose what do you want to do? [1 to 8]? ");
}

short ReadManageUserMenueOption()
{
    return ReadInputOption("Choose what do you want to do? [1 to 6]? ");
}

short ReadTransactionsMenueOption()
{
    return ReadInputOption("Choose what do you want to do? [1 to 4]? ");
}

void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption,stUser& CurrentUser)
{
    switch (TransactionMenueOption)
    {
    case enTransactionsMenueOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue(CurrentUser);
        break;
    }

    case enTransactionsMenueOptions::eWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactionsMenue(CurrentUser);
        break;
    }


    case enTransactionsMenueOptions::eShowTotalBalance:
    {
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenue(CurrentUser);
        break;
    }


    case enTransactionsMenueOptions::eShowMainMenue:
    {

        ShowMainMenue(CurrentUser);

    }
    }

}

void ShowTransactionsMenue(stUser& CurrentUser)
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";
    PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption(), CurrentUser);
}

void AccessDenied(stUser& CurrentUser)
{
    system("cls");
    cout << "-------------------------------------------\n";
    cout << "Access Denied,\n";
    cout << "You dont Have Permission To Do this,\n";
    cout << "Please Contact Your Admin.\n";
    cout << "-------------------------------------------\n";

    GoBackToMainMenue(CurrentUser);
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption , stUser& CurrentUser)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:

        if (!HasAccess(CurrentUser, eShowClients))
        {
            AccessDenied(CurrentUser);
        }
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue(CurrentUser);
        break;

        
    case enMainMenueOptions::eAddNewClient:

        if (!HasAccess(CurrentUser,eAddClients))
        {
            AccessDenied(CurrentUser);
        }
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenue(CurrentUser);
        break;

 
    case enMainMenueOptions::eDeleteClient:

        if (!HasAccess(CurrentUser, eDeleteClients))
        {
            AccessDenied(CurrentUser);
        }
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue(CurrentUser);
        break;

     
    case enMainMenueOptions::eUpdateClient:

        if (!HasAccess(CurrentUser, eUpdateClients))
        {
            AccessDenied(CurrentUser);
        }
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue(CurrentUser);
        break;

    case enMainMenueOptions::eFindClient:
        if (!HasAccess(CurrentUser, eFindClients))
        {
            AccessDenied(CurrentUser);
            return;
        }
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue(CurrentUser);
        break;

    case enMainMenueOptions::eShowTransactionsMenue:
        if (!HasAccess(CurrentUser, eTransactions))
        {
            AccessDenied(CurrentUser);
        }
        system("cls");
        ShowTransactionsMenue(CurrentUser);
        break;

    case enMainMenueOptions::eManageUsers:
        if (!HasAccess(CurrentUser, enManageUsers))
        {
            AccessDenied(CurrentUser);
        }
        system("cls");
        ShowManageUserMenue(CurrentUser);
        break;

    case enMainMenueOptions::eLogout:
        system("cls");
        ShowLogoutScreen();
        break;
    }

}

void PerfromManageUserMenueOption(enUserManageOptions UserMenueOption, stUser& CurrentUser)
{
    switch (UserMenueOption)
    {
    case::eListUsers:
        system("cls");
        ShowAllUsersScreen();
        GoBackToUsersMenue(CurrentUser);
        break;

    case::eAddNewUser:
        system("cls");
        ShowAddNewUsersScreen();
        GoBackToUsersMenue(CurrentUser);
        break;

    case::eDeleteUser:
        system("cls");
        ShowDeleteUserScreen();
        GoBackToUsersMenue(CurrentUser);
        break;

    case::eUpdateUser:
        system("cls");
        ShowUpdateUserScreen();
        GoBackToUsersMenue(CurrentUser);
        break;

    case::eFindUser:
        system("cls");
        ShowFindUserScreen();
        GoBackToUsersMenue(CurrentUser);
        break;

    case::eShowMainMenues:
        ShowMainMenue(CurrentUser);

    }
}

void ShowMainMenue(stUser& CurrentUser)
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption(), CurrentUser);
}

void ShowManageUserMenue(stUser& CurrentUser)
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tManage User Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] List User.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menu.\n";
    cout << "===========================================\n";

    PerfromManageUserMenueOption((enUserManageOptions)ReadManageUserMenueOption(),CurrentUser);
}

bool CheckUsernameAndPassword(string Username, string Password, stUser& CurrentUser)
{
    vector<stUser> vUser = LoadUsersDataFromFile(UsersFileName);

    return FindUserByUserNameAndPassword(Username, Password, vUser, CurrentUser);
}

void Login()
{
    cout << "-----------------------------\n";
    cout <<"\tLogin Screen\n";
    cout << "-----------------------------\n";
            
    string Username, Password;
    stUser CurrentUser;

    while (true)
    {
        Username = ReadUsername();
        Password = ReadPassword();

        if (CheckUsernameAndPassword(Username, Password, CurrentUser))
        {
            cout << "\nLogin Successful!\n";
           ShowMainMenue(CurrentUser);
           break;
        }
        else
        {
            system("cls");

            cout << "-----------------------------\n";
            cout << "\tLogin Screen\n";
            cout << "-----------------------------\n";
        }
        cout << "Invalid Username/Password, try again...\n";
    }
}

int main()
{
    Login();
    system("pause>0");
    return 0;
}