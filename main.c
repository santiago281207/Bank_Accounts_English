#define _CRT_SECURE_NO_WARNINGS
#define MAX 500
#define NAME 20
#define PASS_LENGTH 30

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>

struct BankAccount {
	char name[20];
	char pass[30];
	char contact[9];
	double balance;
};

void ResetBalances(struct BankAccount accounts[], int size);		//Set all balances to 0
void RemoveInvalid(char word[]);
void Menu(int accounts_created);    //Menu function
int BetweenAB(int n, int min, int max);     //Check a range of integers or chars
int Password_Strength(char* password);  //Check password strength 1-strong 0-weak
int NameCheck(struct BankAccount accounts[], char name[], int size);    //Check if name is valid or already assigned
int ContactVerification(char contact[]);      //Is contact valid?
int ContactConfirm(struct BankAccount accounts[], char number[], int account);
int IsInString(char string[], char value);      //Check if a character is in a string
int AccountFinder(struct BankAccount accounts[], char name[], int size);      //Find account with the name the user enters
int PasswordCheck(struct BankAccount accounts[], char pass[], int account);	//Check if password is correct
int AmountToSendValid(double balance, double amount_to_send);	//Check if amount to send is valid

int main()
{
	struct BankAccount Accounts[MAX];
	int password_change_counter = 0, contact_check = 0;	//Count how many password change attempts have happened
	int qty_accounts = 0, accounts_created = 0;
	int account_pos = 0;
	int send_amount_check, pass_change_check;	//Shows if amount to send is valid
	double amount_withdraw, amount_deposit;	//Deposit amounts
	double amount_send;
	int sender, recipient, passcheck;	//Send amount and account positions and correct password verification
	char sender_name[NAME], sender_pass[PASS_LENGTH], recipient_name[NAME];
	char menu_task = ' ';   //Menu choice
	char creator_task;    //Create accounts one by one or create several at once?
	char balance_account_name[NAME], balance_account_pass[PASS_LENGTH];  //Account name to check balance and password
	char change_account_name[NAME], change_account_pass[PASS_LENGTH], choice_maker = ' ', contact_confirm[10];	//Account name that will change password, decide to change to contact confirmation and if contact is correct
	system("color B");      //Change color to light blue

	ResetBalances(Accounts, MAX);

	while (1)    //Loop that runs the bank
	{
		Menu(accounts_created);

		do
		{
			scanf_s("%c", &menu_task, 1);
			getchar();
			if (BetweenAB(menu_task, '1', '7') == 0)
			{
				puts("Enter a valid option!");
			}
		} while (BetweenAB(menu_task, '1', '7') == 0);

		if (menu_task == '7')  //Check if chosen task is exit
		{
			printf("Exiting...\n");
			Sleep(1000);
			break;
		}

		switch (menu_task)    //Find which task was chosen
		{
		case '1':       //Add new accounts
			if (accounts_created >= MAX)
			{
				puts("Maximum number of accounts reached!");
				break;
			}
			puts("  === BANANA ACCOUNT CREATOR ===  ");
			puts("1. Serial account creator");  //Enter number of accounts
			puts("2. Single account creator (recommended)");  //Create only one account
			puts("3. Exit");


			do
			{
				scanf_s("%c", &creator_task, 1);
				getchar();

				if (BetweenAB(creator_task, '1', '3') == 0)
				{
					printf("Select a valid option.");
				}
			} while (BetweenAB(creator_task, '1', '3') == 0);
			if (creator_task == '3')
			{
				printf("Exiting...\n");
				Sleep(1000);
				break;
			}


			switch (creator_task)
			{
			case '1':   //Serial creator
				printf(" === SERIAL ACCOUNT CREATOR === \n");
				do
				{
					printf("Enter the number of accounts you want to create: ");
					scanf_s("%d", &qty_accounts);    //Number of accounts
					getchar();
					if (BetweenAB(qty_accounts, 1, MAX) == 0)
					{
						printf("Our servers only support up to %d accounts.\n", MAX);
					}
				} while (BetweenAB(qty_accounts, 1, MAX) == 0);


				for (; accounts_created < qty_accounts;) //Create accounts up to the desired number
				{
					do
					{
						printf("Enter the name of the owner of this account: ");
						fgets(Accounts[accounts_created].name, NAME, stdin);    //Read account name
						Accounts[accounts_created].name[strcspn(Accounts[accounts_created].name, "\n")] = '\0';     //Remove the "\n" from the name string

						if (NameCheck(Accounts, Accounts[accounts_created].name, accounts_created) == 0)    //Check if name is valid
						{
							printf("Invalid name!\n");
						}
					} while (NameCheck(Accounts, Accounts[accounts_created].name, accounts_created) == 0);    //Check if name is valid

					do
					{
						printf("Enter the password for the account (minimum 8 characters): ");
						fgets(Accounts[accounts_created].pass, PASS_LENGTH, stdin);
						Accounts[accounts_created].pass[strcspn(Accounts[accounts_created].pass, "\n")] = '\0';     //Remove the "\n" from the string

						if (Password_Strength(Accounts[accounts_created].pass) != 1)
						{
							printf("Password too weak!\nTry again.\n");
						}
					} while (Password_Strength(Accounts[accounts_created].pass) != 1);


					do
					{
						printf("Enter your contact number:+351");
						scanf_s("%s", Accounts[accounts_created].contact, 10);  //Read mobile number
						getchar();
						if (ContactVerification(Accounts[accounts_created].contact) == 0)   //Check if number is valid
						{
							printf("Invalid number!\n");
						}
					} while (ContactVerification(Accounts[accounts_created].contact) == 0);  //Check if contact number is valid

					printf("Account for %s created successfully!\n\n", Accounts[accounts_created].name);
					accounts_created++;
				}
				break;  //END OF SERIAL ACCOUNT CREATOR

			case '2':   //Single creator
				do
				{
					printf("Enter the name of the owner of this account: ");
					fgets(Accounts[accounts_created].name, NAME, stdin);    //Read account name
					Accounts[accounts_created].name[strcspn(Accounts[accounts_created].name, "\n")] = '\0';     //Remove the "\n" from the string

					if (NameCheck(Accounts, Accounts[accounts_created].name, accounts_created) == 0)    //Check if name is valid
					{
						printf("Invalid name!\n");
					}
				} while (NameCheck(Accounts, Accounts[accounts_created].name, accounts_created) == 0);    //Check if name is valid

				do
				{
					printf("Enter the password for the account (minimum 8 characters): ");
					fgets(Accounts[accounts_created].pass, PASS_LENGTH, stdin);
					Accounts[accounts_created].pass[strcspn(Accounts[accounts_created].pass, "\n")] = '\0';     //Remove the "\n" from the string

					if (Password_Strength(Accounts[accounts_created].pass) != 1)
					{
						printf("Password too weak!\nTry again.\n");
					}
				} while (Password_Strength(Accounts[accounts_created].pass) != 1);      //Check if password meets requirements

				do
				{
					printf("Enter your contact number:+351");
					scanf_s("%s", &Accounts[accounts_created].contact, 10);  //Read mobile number
					getchar();

					if (ContactVerification(Accounts[accounts_created].contact) == 0)   //Check if number is valid
					{
						printf("Invalid number!\n");
					}
				} while (ContactVerification(Accounts[accounts_created].contact) == 0);  //Check if contact number is valid

				printf("Account for %s created successfully!\n\n", Accounts[accounts_created].name);
				accounts_created++;

				break;      //END OF SINGLE CREATOR
			}
			break;

		case '2':       //Check balance - password required
			printf(" === BANANA CHECKER === \n");
			do
			{
				printf("Type quit to exit.\n");
				printf("Account name: ");
				fgets(balance_account_name, NAME, stdin);
				RemoveInvalid(balance_account_name);

				if (_stricmp(balance_account_name, "quit") == 0)
				{
					break;
				}
				else if (AccountFinder(Accounts, balance_account_name, accounts_created) == -1)
				{
					printf("Account does not exist. Try another name\n");
				}
			} while (AccountFinder(Accounts, balance_account_name, accounts_created) == -1);  //Repeat until account is found

			if (_stricmp(balance_account_name, "quit") == 0)
			{
				printf("Exiting...\n");
				Sleep(1000);
				break;
			}

			account_pos = AccountFinder(Accounts, balance_account_name, accounts_created);

			do
			{
				printf("Enter your password: ");
				fgets(balance_account_pass, PASS_LENGTH, stdin);
				RemoveInvalid(balance_account_pass);		//Remove the \n at the end of the string

				if (_stricmp(balance_account_pass, "quit") == 0)
				{
					break;
				}
				else if (PasswordCheck(Accounts, balance_account_pass, account_pos) == 0)		//If password is wrong
				{
					printf("Incorrect password. Try again.\n");
				}
			} while (PasswordCheck(Accounts, balance_account_pass, account_pos) == 0);		//Repeat until correct

			if (_stricmp(balance_account_pass, "quit") == 0)
			{
				printf("Exiting...\n");
				Sleep(1000);
				break;
			}
			else
			{
				printf("Your bananas: %.2lf\n\n", Accounts[account_pos].balance);
			}
			break;      //END CHECK BALANCE

		case '3':       //Withdraw money - password required
			printf(" === WITHDRAW BANANAS === \n");
			do
			{
				printf("\nType quit to exit.\n");
				printf("Account name: ");
				fgets(balance_account_name, NAME, stdin);
				RemoveInvalid(balance_account_name);	//Remove the \n from the end of the string

				if (_stricmp(balance_account_name, "quit") == 0)
				{
					break;
				}
				else if (AccountFinder(Accounts, balance_account_name, accounts_created) == -1)
				{
					printf("Account does not exist. Try another name\n");
				}
			} while (AccountFinder(Accounts, balance_account_name, accounts_created) == -1);  //Repeat until account is found

			if (_stricmp(balance_account_name, "quit") == 0)
			{
				printf("Exiting...\n");
				Sleep(1000);
				break;
			}

			account_pos = AccountFinder(Accounts, balance_account_name, accounts_created);

			do
			{
				printf("Enter your password: ");
				fgets(balance_account_pass, PASS_LENGTH, stdin);
				RemoveInvalid(balance_account_pass);		//Remove the \n from the end of the string

				if (_stricmp(balance_account_pass, "quit") == 0)
				{
					break;
				}
				else if (PasswordCheck(Accounts, balance_account_pass, account_pos) == 0)		//If password is wrong
				{
					printf("Incorrect password. Try again.\n");
				}
			} while (PasswordCheck(Accounts, balance_account_pass, account_pos) == 0);		//Repeat until correct

			if (_stricmp(balance_account_pass, "quit") == 0)	//Exiting task
			{
				printf("Exiting...\n");
				Sleep(1000);
				break;
			}

			if (Accounts[account_pos].balance <= 0)	//No balance to withdraw
			{
				printf("You don't have enough balance to withdraw any amount!\n");
				printf("Exiting...\n");
				Sleep(1000);
			}
			else
			{
				do
				{
					printf("Enter how much you want to withdraw: $");
					scanf("%lf", &amount_withdraw);
					if (amount_withdraw <= 0)
					{
						printf("Invalid amount!\n");
					}
					else if (amount_withdraw > Accounts[account_pos].balance)
					{
						printf("Insufficient balance.\n");
					}
					else
					{
						Accounts[account_pos].balance -= amount_withdraw;	//Reduce balance
						printf("%.2lf was withdrawn from your account!\n", amount_withdraw);
						printf("Current balance: %.2lf\n\n", Accounts[account_pos].balance);	//Show balance after withdrawal
						Sleep(2000);
					}
				} while (amount_withdraw <= 0);	//Repeat until reading a valid value
			}
			break;      //END WITHDRAW MONEY

		case '4':       //Deposit money - password required
			printf(" === DEPOSIT BANANAS === \n");
			do
			{
				printf("Type quit to exit.\n");
				printf("Account name: ");
				fgets(balance_account_name, NAME, stdin);
				RemoveInvalid(balance_account_name);	//Remove \n

				if (_stricmp(balance_account_name, "quit") == 0)	//Check if exiting task
				{
					break;
				}
				else if (AccountFinder(Accounts, balance_account_name, accounts_created) == -1)	//Check if account exists
				{
					printf("Account does not exist. Try another name");
				}
			} while (AccountFinder(Accounts, balance_account_name, accounts_created) == -1);  //Repeat until account is found

			if (_stricmp(balance_account_name, "quit") == 0)	//Exiting
			{
				printf("Exiting...\n\n");
				Sleep(1000);
				break;
			}

			account_pos = AccountFinder(Accounts, balance_account_name, accounts_created);	//Find account position

			do
			{
				printf("Enter your password: ");
				fgets(balance_account_pass, PASS_LENGTH, stdin);
				RemoveInvalid(balance_account_pass);		//Remove the \n at the end of the string

				if (_stricmp(balance_account_pass, "quit") == 0)	//Check if exiting task
				{
					break;
				}
				else if (PasswordCheck(Accounts, balance_account_pass, account_pos) == 0)		//If password is wrong
				{
					printf("Incorrect password. Try again.\n");
				}
			} while (PasswordCheck(Accounts, balance_account_pass, account_pos) == 0);		//Repeat until correct

			if (_stricmp(balance_account_pass, "quit") == 0)	//Exiting task
			{
				printf("Exiting...\n\n");
				Sleep(1000);
				break;
			}

			do
			{
				printf("Enter how much you want to deposit: $");
				scanf("%lf", &amount_deposit);
				if (amount_deposit <= 0)
				{
					printf("Invalid amount!\n");
				}
				else
				{
					Accounts[account_pos].balance += amount_deposit;		//Add deposit to balance
					printf("%.2lf was deposited to your account!\n", amount_deposit);
					printf("Current balance: %.2lf\n\n", Accounts[account_pos].balance);	//Show balance after deposit
					getchar();
					Sleep(1000);
				}
			} while (amount_deposit < 0);

			break;      //END DEPOSIT MONEY

		case '5':       //Money transfer - password required
			printf(" === BANANA TRANSFER === \n");
			puts("Type quit to exit.");
			do
			{
				printf("Sender name: ");
				fgets(sender_name, NAME, stdin);
				RemoveInvalid(sender_name);	//Remove "\n" from the end of the string

				sender = AccountFinder(Accounts, sender_name, accounts_created);
				if (_stricmp(sender_name, "quit") == 0)
				{
					break;
				}
				else if (sender == -1)	//Find account
				{
					puts("Account does not exist. Try again.");
				}
			} while (sender == -1);		//Repeat until account is found

			if (_stricmp(sender_name, "quit") == 0)	//Exit task
			{
				printf("Exiting...\n");
				Sleep(1000);
				break;
			}

			do
			{
				printf("Password: ");
				fgets(sender_pass, PASS_LENGTH, stdin);
				RemoveInvalid(sender_pass);	//Remove /n from string

				passcheck = PasswordCheck(Accounts, sender_pass, sender);	//Find sender's account

				if (_stricmp(sender_pass, "quit") == 0)	//Check if exiting task
				{
					printf("Exiting...\n\n");
					Sleep(1000);
					break;
				}
				else if (passcheck == 0)	//If password is incorrect
				{
					puts("Incorrect password!");
				}
			} while (passcheck == 0);	//Until password is correct

			if (_stricmp(sender_pass, "quit") == 0)	//Exit task
			{
				printf("Exiting...\n\n");
				Sleep(1000);
				break;
			}

			do
			{
				printf("Recipient name: ");
				fgets(recipient_name, NAME, stdin);
				RemoveInvalid(recipient_name);	//Remove \n from string

				recipient = AccountFinder(Accounts, recipient_name, accounts_created);	//Find recipient's account

				if (recipient == sender)
				{
					printf("You cannot transfer to yourself.\n");
					continue;
				}
				else if (_stricmp(recipient_name, "quit") == 0)	//Check if exiting task
				{
					break;
				}
				else if (recipient == -1)
				{
					printf("Account does not exist. Try again.\n");
				}
			} while (recipient == -1);

			if (_stricmp(recipient_name, "quit") == 0)
			{
				printf("Exiting...\n\n");
				Sleep(1000);
				break;
			}

			do
			{
				if (Accounts[sender].balance <= 0)	//Not enough balance
				{
					printf("You don't have enough money to make a transaction.\n");
					printf("Exiting...\n\n");
					Sleep(1000);
					break;
				}
				else
				{
					printf("Enter how much you want to send to %s: $", Accounts[recipient].name);
					scanf("%lf", &amount_send);
					send_amount_check = AmountToSendValid(Accounts[sender].balance, amount_send);

					if (send_amount_check == 0)
					{
						printf("Invalid amount!\n");
					}
					else if (send_amount_check == -1)
					{
						printf("Insufficient balance!\n");
					}
					else if (send_amount_check == 1)
					{
						printf("%.2lf was sent to %s.\n", amount_send, Accounts[recipient].name);
						Accounts[sender].balance -= amount_send;	//Remove sent amount from sender
						Accounts[recipient].balance += amount_send;	//Add sent amount to recipient
						printf("Current balance: %.2lf\n\n", Accounts[sender].balance);
					}
				}
			} while (send_amount_check == 0 || send_amount_check == -1);

			if (Accounts[sender].balance <= 0)	//Exit task
			{
				break;
			}

			printf("Exiting...\n\n");
			Sleep(1000);
			printf("\n\n");
			getchar();
			break;      //END MONEY TRANSFER

		case '6':       /*Change password - needs current password. If don't know it, ask for mobile contact*/
			printf(" === CHANGE PASSWORD === \n");
			printf("Type quit to exit.\n");
			do
			{
				printf("Account name: ");
				fgets(change_account_name, NAME, stdin);
				RemoveInvalid(change_account_name);		//Remove \n at the end of string

				account_pos = AccountFinder(Accounts, change_account_name, accounts_created);	//Find account position

				if (_stricmp(change_account_name, "quit") == 0)	//Exit task
				{
					break;
				}
				else if (account_pos == -1)	//Didn't find account
				{
					printf("Account does not exist. Try again.\n");
				}
			} while (account_pos == -1);	//Repeat until account is found

			if (_stricmp(change_account_name, "quit") == 0)	//Exit task
			{
				printf("Exiting...\n\n");
				Sleep(1000);
				break;
			}

			do
			{
				printf("Password: ");
				fgets(change_account_pass, PASS_LENGTH, stdin);
				RemoveInvalid(change_account_pass);	//Remove \n from string

				pass_change_check = PasswordCheck(Accounts, change_account_pass, account_pos);	//Check if password is correct

				if (_stricmp(change_account_pass, "quit") == 0)	//Exit task
				{
					break;
				}
				else if (pass_change_check == 0)
				{
					printf("Incorrect password. Try again.\n");
				}
				else if (pass_change_check == 1)
				{
					break;
				}
				password_change_counter++;

				if (password_change_counter % 3 == 0)
				{
					do
					{
						printf("Do you want to verify profile by contact number?\n[Y/N] ");
						scanf("%c", &choice_maker);	//Read choice
						getchar();
						if (toupper(choice_maker) == 'Y' || toupper(choice_maker) == 'N')	//Wants to change
						{
							break;
						}
						else		//Entered wrong decision
						{
							printf("Enter a valid decision [Y/N].\n");
						}
						if (toupper(choice_maker) == 'Y')
						{
							break;
						}
					} while (toupper(choice_maker) != 'Y' || toupper(choice_maker) != 'N');

					if (toupper(choice_maker) == 'Y')
					{
						break;
					}
					else if (toupper(choice_maker) == 'N')
					{
						continue;
					}
				}

			} while (pass_change_check == 0);



			if (_stricmp(change_account_pass, "quit") == 0)	//Exit task
			{
				printf("Exiting...\n");
				Sleep(1000);
				break;
			}
			else if (toupper(choice_maker) == 'Y')		//Verification by contact number
			{
				printf("Type quit to exit.\n");
				do
				{
					printf("Contact number:+351");
					fgets(contact_confirm, 10, stdin);
					RemoveInvalid(contact_confirm);	//Remove the \n at the end of string
					contact_check = ContactConfirm(Accounts, contact_confirm, account_pos);

					if (_stricmp(contact_confirm, "quit") == 0)
					{
						break;
					}
					else if (contact_check == 0)
					{
						printf("Wrong contact number. Try again.\n");
					}
				} while (contact_check == 0);		//While contact number fails

				if (_stricmp(contact_confirm, "quit") == 0)
				{
					printf("Exiting...\n");
					Sleep(1000);
				}
			}
			else if (pass_change_check == 1)	//Got password right
			{
				do
				{
					printf("New password (minimum 8 characters): ");
					fgets(Accounts[account_pos].pass, PASS_LENGTH, stdin);
					RemoveInvalid(Accounts[account_pos].pass);		//Remove \n from string

					if (Password_Strength(Accounts[account_pos].pass) != 1)
					{
						printf("Password too weak!\nTry again.\n");
					}
				} while (Password_Strength(Accounts[account_pos].pass) != 1);      //Check if password meets requirements
			}

			if (contact_check == 1)	//Got contact number right
			{
				do
				{
					getchar();
					printf("New password (minimum 8 characters): ");
					fgets(Accounts[account_pos].pass, PASS_LENGTH, stdin);
					RemoveInvalid(Accounts[account_pos].pass);		//Remove \n from string

					if (Password_Strength(Accounts[account_pos].pass) != 1)
					{
						printf("Password too weak!\nTry again.\n");
					}
				} while (Password_Strength(Accounts[account_pos].pass) != 1);      //Check if password meets requirements
			}

			printf("\n");
			password_change_counter = 0;
			break;      //END CHANGE PASSWORD
		}
	}
	return 0;
}

void Menu(int accounts_created)
{
	puts(" === WELCOME TO THE BANANA BANK === ");
	puts("----------------------------------------");
	puts("|Select an option from below:          |");
	printf("|1. Add banana accounts(%d/%d)          |\n", accounts_created, MAX);   //1 Add account
	puts("|2. Check bananas                      |");   //2 Check balance
	puts("|3. Withdraw bananas                   |");   //3 Withdraw money
	puts("|4. Deposit bananas                    |");   //4 Deposit money
	puts("|5. Banana transfer                    |");   //5 Money transfer
	puts("|6. Change password                    |");   //6 Change password
	puts("|7. Exit                               |");   //7 Exit
	puts("----------------------------------------");
}

int BetweenAB(int n, int min, int max)
{
	return n >= min && n <= max;
}

int Password_Strength(char* password)
{
	/*This function will evaluate the strength of a password and if the password is valid.
	CRITERIA:
				Minimum 8 characters
				Uppercase letter
				Lowercase letter
				Numbers
				Special characters
				No spaces
				No easy repetitions
				No common passwords*/
	int i = 0;
	int upper_letters_count = 0, lower_letters_count = 0, special_count = 0, numbers_count = 0, total = 0;   //Character counters
	int length_check = 0;
	char lower_letters[] = { "abcdefghijklmnopqrstuvwxyz" };
	char upper_letters[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	char special[] = { "@!$_-#" };
	char numbers[] = { "0123456789" };
	size_t length = strlen(password);

	if (length < 8)
	{
		return 0;
	}
	else
	{
		for (i = 0; i < length; i++)
		{
			if (IsInString(lower_letters, password[i]) == 1) //Check if current character is lowercase
				lower_letters_count = 1;
			else if (IsInString(upper_letters, password[i]) == 1)   //Check if current character is uppercase
				upper_letters_count = 1;
			else if (IsInString(special, password[i]) == 1)     //Check if current character is special
				special_count = 1;
			else if (IsInString(numbers, password[i]) == 1)     //Check if current character is a number
				numbers_count = 1;
		}
		length_check = 1;
		total = numbers_count + special_count + upper_letters_count + lower_letters_count + length_check;       //Calculate how many rules it follows
	}
	if (total != 5)     //If it doesn't follow all rules
	{
		return 0;
	}
	return 1;
}

int NameCheck(struct BankAccount accounts[], char name[], int size)
{
	//Function checks if the name is already being used by another user

	int i = 0;

	for (i = 0; i < size; i++)
	{
		if (_stricmp(accounts[i].name, name) == 0)    //Check if entered name already exists in database case-insensitive
		{
			return 0;
		}
	}
	return 1;
}

int ContactVerification(char contact[])
{
	int i = 0;
	char nums[] = { "0123456789" };
	for (i = 0; contact[i] != '\0'; i++)
	{
		if (IsInString(nums, contact[i]) == 0)
		{
			return 0;
		}
	}

	return i == 9;
}

int IsInString(char string[], char value)
{
	size_t i = 0;

	for (i = 0; string[i] != '\0'; i++)
	{
		if (string[i] == value)
		{
			return 1;
		}
	}
	return 0;
}

int AccountFinder(struct BankAccount accounts[], char name[], int size)	//-1 if not found
{
	//Find user's name
	int i = 0;

	for (i = 0; i < size; i++)
	{
		if (strcmp(accounts[i].name, name) == 0)
		{
			return i;
		}
	}
	return -1;
}

int PasswordCheck(struct BankAccount accounts[], char pass[], int account)
{
	//Check if password is correct
	if (strcmp(accounts[account].pass, pass) == 0)
	{
		return 1;
	}
	return 0;
}

void RemoveInvalid(char word[])
{
	int i = 0;
	for (i = 0; word[i] != '\0'; i++)
	{
		if (word[i] == '\n')
		{
			word[i] = '\0';
		}
	}
}

int AmountToSendValid(double balance, double amount_to_send)
{
	// Checks if the amount of money to send is valid
	if (amount_to_send < 0)
	{
		return 0;    // If the amount is negative
	}
	else if (amount_to_send > balance)
	{
		return -1;   // If there's insufficient balance
	}
	else
	{
		return 1;    // If it's valid
	}
}

void ResetBalances(struct BankAccount accounts[], int size)
{
	int i = 0;
	for (i = 0; i < size; i++)
	{
		accounts[i].balance = 0;
	}
}

int ContactConfirm(struct BankAccount accounts[], char number[], int account)
{
	// Checks if the contact number is correct
	if (strcmp(accounts[account].contact, number) == 0)
	{
		return 1;
	}
	return 0;
}
