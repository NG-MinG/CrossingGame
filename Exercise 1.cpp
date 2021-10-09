#include <iostream>
#include "Exercise1_1.h"
#include "Exercise1_2.h"
using namespace std;

void main_menu()
{
	cout << "\n ________________________| MENU |________________________\n";
	cout << "|                                                        |\n";
	cout << "|     [0]. Exit                                          |\n";
	cout << "|     [1]. Exercise 1.1                                  |\n";
	cout << "|     [2]. Exercise 1.2                                  |\n";
	cout << "|________________________________________________________|\n";
}

void sub_menu1()
{
	cout << " ________________________________________________________\n";
	cout << "|                                                        |\n";
	cout << "|     [1]. Exercise 1.1                                  |\n";
	cout << "|________________________________________________________|\n";
}

void sub_menu2()
{
	cout << " ________________________________________________________\n";
	cout << "|                                                        |\n";
	cout << "|     [2]. Exercise 1.2                                  |\n";
	cout << "|________________________________________________________|\n";
}

int main()
{
	int choice = -1;
	main_menu();
	do
	{
		cout << "__________________________________________________________\n";
		cout << "\n  YOUR CHOICE: ";
		
		cin >> choice;
		switch (choice)
		{
			case 1:
				sub_menu1();
				cout << "\n";
				ex1();
				break;
			case 2:
				sub_menu2();
				cout << "\n";
				ex2();
				break;
			case 0:
				continue;
				break;
			default:
				cout << "\n  INVALID SELECTION, PLEASE CHOOSE AGAIN.\n";
				continue;
				break;
		}
		
		cout << "\n__________________________________________________________\n";
		cout << "\nPress 1 to continue or press 0 to exit: ";
		cin >> choice;

		cin.clear(); cin.ignore();
		
		system("cls");
		main_menu();

	} while (!cin.fail() && choice != 0);

	cout << "Thanks for using. Press any key to exit.\n";
	system("pause > nul");
	return 0;
}