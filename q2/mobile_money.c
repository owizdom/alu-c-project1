#include <stdio.h>

/* Throws away whatever is left on the input line (for example letters) */
void clear_input(void)
{
	int c;

	c = getchar();
	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
}

int main(void)
{
	int balance;
	int amount;
	int choice;
	int deposit_count;
	int withdrawal_count;
	int result;

	balance = 0;
	deposit_count = 0;
	withdrawal_count = 0;

	printf("===== MOBILE MONEY TRANSACTION SYSTEM =====\n");

	/* keep showing the menu until the agent chooses Exit */
	while (1)
	{
		printf("\n1. Deposit\n");
		printf("2. Withdraw\n");
		printf("3. Check Balance\n");
		printf("4. Transaction Summary\n");
		printf("5. Exit\n");
		printf("\nEnter choice: ");
		result = scanf("%d", &choice);

		/* no more input at all: stop the program */
		if (result == EOF)
		{
			printf("\nSystem terminated.\n");
			break;
		}

		/* the agent typed letters instead of a number */
		if (result != 1)
		{
			printf("Invalid input. Please enter a number.\n");
			clear_input();
			continue;
		}

		/* Exit: break leaves the while loop and the program ends */
		if (choice == 5)
		{
			printf("System terminated.\n");
			break;
		}

		/* a number that is not on the menu */
		if (choice < 1 || choice > 5)
		{
			printf("Invalid choice. Please enter a number from 1 to 5.\n");
			continue;
		}

		switch (choice)
		{
		case 1:
			printf("Enter deposit amount: ");
			result = scanf("%d", &amount);
			if (result != 1)
			{
				printf("Invalid input. Please enter a number.\n");
				clear_input();
				continue;
			}

			if (amount <= 0)
			{
				printf("Transaction rejected: Amount must be positive.\n");
			}
			else
			{
				balance = balance + amount;
				deposit_count = deposit_count + 1;
				printf("Deposit successful.\n");
				printf("Current balance: %d RWF\n", balance);
			}
			break;

		case 2:
			printf("Enter withdrawal amount: ");
			result = scanf("%d", &amount);
			if (result != 1)
			{
				printf("Invalid input. Please enter a number.\n");
				clear_input();
				continue;
			}

			if (amount <= 0)
			{
				printf("Transaction rejected: Amount must be positive.\n");
			}
			else if (amount > balance)
			{
				printf("Transaction rejected: Insufficient balance.\n");
			}
			else
			{
				balance = balance - amount;
				withdrawal_count = withdrawal_count + 1;
				printf("Withdrawal successful.\n");
				printf("Current balance: %d RWF\n", balance);
			}
			break;

		case 3:
			printf("Current balance: %d RWF\n", balance);
			break;

		case 4:
			printf("===== TRANSACTION SUMMARY =====\n");
			printf("Successful deposits: %d\n", deposit_count);
			printf("Successful withdrawals: %d\n", withdrawal_count);
			break;
		}
	}

	return 0;
}
