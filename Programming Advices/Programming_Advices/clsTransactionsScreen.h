#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"


class clsTransactionsScreen : protected clsScreen
{
private:

	enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3, eShowMainMenue = 4 };

	static short ReadTransactionsMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 4]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 4, "Enter Number between 1 to 4? ");
		return Choice;
	}

	static  void _GoBackToTransactionsMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Transactions Menue...\n";

		system("pause>0");
		ShowTransactionsMenue();
	}

	static void _ShowDepositScreen()
	{
		cout << "\nDeposit Screen Will be here...\n";

	}

	static void _ShowWithdrawScreen()
	{
		cout << "\nWithdraw Screen Will be here...\n";

	}

	static void _ShowTotalBalancesScreen()
	{
		cout << "\nTotal Balances Screen Will be here...\n";

	}

	static void _PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
	{
		switch (TransactionMenueOption)
		{
		case enTransactionsMenueOptions::eDeposit:
		{
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case enTransactionsMenueOptions::eWithdraw:
		{
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenue();
			break;
		}


		case enTransactionsMenueOptions::eShowTotalBalance:
		{
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenue();
			break;
		}


		case enTransactionsMenueOptions::eShowMainMenue:
		{
			//do nothing here the main screen will handle it :-) ;
		}
		}

	}

public:

	static void ShowTransactionsMenue()
	{
		system("cls");
		_DrawScreenHeader("\t  Transactions Screen");
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tTransactions Menue Screen\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		_PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
	} 
		
};  

