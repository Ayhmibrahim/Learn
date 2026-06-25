#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const string ClientsFileName = "Clients.txt";

// ===================== STRUCT =====================

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance = 0.0;
    bool MarkForDelete = false;
};

// ===================== ENUM =====================

enum enATMOptions
{
    enQuickWithdraw = 1,
    enNormalWithdraw = 2,
    enDeposit = 3,
    enCheckBalance = 4,
    enLogout = 5
};

struct stClient CurrentClient;

// ===================== FORWARD DECLARATION =====================

void ATMMainMenueScreen(stClient& Client);

// ===================== STRING HELPERS =====================

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord;

    while ((pos = S1.find(Delim)) != string::npos)
    {
        sWord = S1.substr(0, pos);

        if (sWord != "")
            vString.push_back(sWord);

        S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
        vString.push_back(S1);

    return vString;
}

// ===================== FILE CONVERSION =====================

stClient ConvertLineClientToRecord(string Line, string Seperator = "#//#")
{
    stClient Client;
    vector<string> vClientData = SplitString(Line, Seperator);

    if (vClientData.size() >= 5)
    {
        Client.AccountNumber = vClientData[0];
        Client.PinCode = vClientData[1];
        Client.Name = vClientData[2];
        Client.Phone = vClientData[3];
        Client.AccountBalance = stod(vClientData[4]);
    }

    return Client;
}

string ConvertRecordToLine(stClient Client, string Seperator = "#//#")
{
    return Client.AccountNumber + Seperator +
        Client.PinCode + Seperator +
        Client.Name + Seperator +
        Client.Phone + Seperator +
        to_string(Client.AccountBalance);
}

// ===================== FILE HANDLING =====================

vector<stClient> LoadCleintsDataFromFile(string FileName)
{
    vector<stClient> vClients;
    fstream MyFile(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineClientToRecord(Line);
            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return vClients;
}

vector<stClient> SaveCleintDataToFile(string FileName, vector<stClient> vClients)
{
    fstream MyFile(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (stClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                MyFile << ConvertRecordToLine(C) << endl;
            }
        }

        MyFile.close();
    }

    return vClients;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFlile(FileName, ios::out | ios::app);

    if (MyFlile.is_open())
    {
        MyFlile << stDataLine << endl;
        MyFlile.close();
    }
}

// ===================== SEARCH =====================

bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode,
    vector<stClient>& vClients, stClient& Client)
{
    for (stClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
        {
            Client = C;
            return true;
        }
    }

    return false;
}

bool FindClientByAccountNumber(string AccountNumber,
    vector<stClient>& vClients,
    stClient& Client)
{
    return FindClientByAccountNumberAndPinCode(AccountNumber,
        CurrentClient.PinCode,
        vClients,
        Client);
}

// ===================== INPUT =====================

string ReadInput(string Message)
{
    string input;
    cout << Message;
    getline(cin >> ws, input);
    return input;
}

string ReadAccountNumber()
{
    return ReadInput("Enter Account Number? ");
}

string ReadPinCode()
{
    return ReadInput("Enter Pin? ");
}

short ReadInputOption(string Message)
{
    cout << Message;
    short Choice;
    cin >> Choice;
    return Choice;
}

short ReadQuickWithdrawOption()
{
    return ReadInputOption("Choose what to withdraw from [1] to [8] ? ");
}

short ReadAtmMainMenueOption()
{
    return ReadInputOption("Choose what do you want to do? [1 to 5]? ");
}

// ===================== ATM LOGIC =====================

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount,
    vector<stClient>& vClients)
{
    char Answer;

    cout << "\n\nAre you sure you want perform this transaction? y/n ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        for (stClient& C : vClients)
        {
            if (C.AccountNumber == CurrentClient.AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintDataToFile(ClientsFileName, vClients);

                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;
                return true;
            }
        }
    }

    return false;
}

// ===================== SCREENS =====================

bool DrawQuick()
{
    short arr[8]{ 10,50,100,200,400,600,800,1000 };
    int Choose = ReadQuickWithdrawOption();

    if (Choose == 9)
        return false;

    if (Choose < 1 || Choose > 9)
    {
        cout << "Invalid Choice!\n";
        return false;
    }

    vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    double Amount = arr[Choose - 1];

    if (DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, -Amount, vClients))
    {
        CurrentClient.AccountBalance -= Amount;
        return true;
    }

    return false;
}

void NormalWithdrawScreen()
{
    cout << "\n===========================================\n";
    cout << "\tNormal Withdraw Screen";
    cout << "\n===========================================\n";

    vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    int Amount = 0;

    do
    {
        cout << "Enter amount multiple of 5's ? ";
        cin >> Amount;

        if (Amount <= 0 || Amount % 5 != 0)
            cout << "Amount must be multiple of 5\n";

    } while (Amount % 5 != 0);

    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber,
        Amount * -1,
        vClients);
}

void DepositScreen()
{
    cout << "\n===========================================\n";
    cout << "\tDeposit Screen";
    cout << "\n===========================================\n";

    vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    int Amount;

    cout << "Enter a positive Deposit Amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber,
        Amount,
        vClients);
}

void QuickWithdrawScreen()
{
    cout << "\n===========================================\n";
    cout << "\t\tQuick Withdraw";
    cout << "\n===========================================\n";

    cout << "\t[1] 20\t\t[2] 50\n";
    cout << "\t[3] 100\t\t[4] 200\n";
    cout << "\t[5] 400\t\t[6] 600\n";
    cout << "\t[7] 800\t\t[8] 1000\n";
    cout << "\t[9] Exit\n";

    cout << "\n===========================================\n";
    cout << "Your Balance is " << CurrentClient.AccountBalance << endl;

    DrawQuick();
}

void CheckBalanceScreen()
{
    cout << "\n===========================================\n";
    cout << "\tCheck Balance Screen";
    cout << "\n===========================================\n";

    cout << "Your Balance is " << CurrentClient.AccountBalance;
}

// ===================== NAVIGATION =====================

void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back...";
    system("pause>0");
    ATMMainMenueScreen(CurrentClient);
}

void PerfromAtmMainMenueOption(enATMOptions AtmMenueOption)
{
    switch (AtmMenueOption)
    {
    case enQuickWithdraw:
        system("cls");
        QuickWithdrawScreen();
        GoBackToTransactionsMenue();
        break;

    case enNormalWithdraw:
        system("cls");
        NormalWithdrawScreen();
        GoBackToTransactionsMenue();
        break;

    case enDeposit:
        system("cls");
        DepositScreen();
        GoBackToTransactionsMenue();
        break;

    case enCheckBalance:
        system("cls");
        CheckBalanceScreen();
        GoBackToTransactionsMenue();
        break;
    }
}

void ATMMainMenueScreen(stClient& Client)
{
    system("cls");

    cout << "\n===========================================\n";
    cout << "\tATM Main Menue Screen";
    cout << "\n===========================================\n";

    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";

    cout << "===========================================\n";

    PerfromAtmMainMenueOption((enATMOptions)ReadAtmMainMenueOption());
}

// ===================== LOGIN =====================

void Login()
{
    cout << "\n---------------------------\n";
    cout << "\tLogin Screen";
    cout << "\n---------------------------\n";

    vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    string AccountNumber = ReadAccountNumber();
    string Pin = ReadPinCode();

    while (true)
    {
        if (FindClientByAccountNumberAndPinCode(AccountNumber, Pin, vClients, CurrentClient))
        {
            cout << "\nLogin Successful!\n";
            ATMMainMenueScreen(CurrentClient);
            break;
        }
        else
        {
            system("cls");
            cout << "-----------------------------\n";
            cout << "\tLogin Screen\n";
            cout << "-----------------------------\n";
            cout << "Invalid Account Number/PinCode!\n";
        }
    }
}

// ===================== MAIN =====================

int main()
{
    Login();
    system("pause>0");
}