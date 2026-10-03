# Question 2: Mobile Money Transaction System

Source code: [`mobile_money.c`](mobile_money.c) (also shown in full at the end). Real sample runs: [`sample_output.txt`](sample_output.txt).

## Data types I used

Everything is an `int`, and here's why for each one:

- `balance` and `amount`: mobile money in RWF is handled in whole francs. Nobody sends 500.75 RWF, so I didn't need decimals.
- `deposit_count` and `withdrawal_count`: you can't have half a transaction, so whole numbers make sense. Both start at 0.
- `choice`: the menu option, 1 to 5.
- `result`: this holds what `scanf` gives back. It's 1 if it read a number, 0 if the user typed letters, and `EOF` if there's no more input at all.

## Sample input/output

I compiled it with `gcc mobile_money.c -o mobile_money` and got no errors or warnings.

In this run I used all five menu options. I also tried four things that should fail: withdrawing more than the balance, a negative amount, a menu number that doesn't exist (9), and typing letters (abc).

```
$ ./mobile_money
===== MOBILE MONEY TRANSACTION SYSTEM =====

1. Deposit
2. Withdraw
3. Check Balance
4. Transaction Summary
5. Exit

Enter choice: 1
Enter deposit amount: 50000
Deposit successful.
Current balance: 50000 RWF

1. Deposit
2. Withdraw
3. Check Balance
4. Transaction Summary
5. Exit

Enter choice: 2
Enter withdrawal amount: 70000
Transaction rejected: Insufficient balance.

1. Deposit
2. Withdraw
3. Check Balance
4. Transaction Summary
5. Exit

Enter choice: 2
Enter withdrawal amount: -200
Transaction rejected: Amount must be positive.

1. Deposit
2. Withdraw
3. Check Balance
4. Transaction Summary
5. Exit

Enter choice: 2
Enter withdrawal amount: 20000
Withdrawal successful.
Current balance: 30000 RWF

1. Deposit
2. Withdraw
3. Check Balance
4. Transaction Summary
5. Exit

Enter choice: 3
Current balance: 30000 RWF

1. Deposit
2. Withdraw
3. Check Balance
4. Transaction Summary
5. Exit

Enter choice: 9
Invalid choice. Please enter a number from 1 to 5.

1. Deposit
2. Withdraw
3. Check Balance
4. Transaction Summary
5. Exit

Enter choice: abc
Invalid input. Please enter a number.

1. Deposit
2. Withdraw
3. Check Balance
4. Transaction Summary
5. Exit

Enter choice: 4
===== TRANSACTION SUMMARY =====
Successful deposits: 1
Successful withdrawals: 1

1. Deposit
2. Withdraw
3. Check Balance
4. Transaction Summary
5. Exit

Enter choice: 5
System terminated.
```

## How the program uses conditionals, loops, break and continue

The loop. The whole menu sits inside `while (1)` (line 31). That means it just keeps going round, so the agent can do as many transactions as they want without restarting. The normal way out is picking 5.

The conditionals. Before doing anything, a few `if` checks look at what was typed:

- `result != 1` (line 49) catches letters.
- `choice == 5` (line 57) is Exit.
- `choice < 1 || choice > 5` (line 64) catches numbers that aren't on the menu.

If the choice is fine, a `switch (choice)` (line 70) jumps to the right operation for 1 to 4. Inside Deposit and Withdraw there's an `if / else` chain that turns down amounts of 0 or less (`amount <= 0`). For withdrawals it also turns down anything bigger than the balance (`amount > balance`). The balance only changes if every check passes.

`continue`. Whenever the input is bad (lines 53, 67, 79 and 102), `continue` skips the rest of the loop and goes straight back to the top. So the menu shows up again and nothing has changed.

`break`. I used it in two ways:

1. Every `case` in the `switch` ends with `break` (lines 93, 120, 124 and 130). This stops the code from running into the next case.
2. When the agent picks 5, the program prints "System terminated." and `break` (line 60) jumps out of the `while` loop, so the program ends. There's one more `break` (line 45) that also gets out of the loop if the input runs out completely, like when someone presses Ctrl+D. That way the program can never get stuck.

One small thing about letters. If the agent types `abc`, `scanf` can't read it as a number, and the letters stay sitting in the input. So I wrote a tiny function, `clear_input()`, that reads the rest of that line and throws it away. Without it, the next `scanf` would hit the same `abc` again, and the menu would print forever.

## Full source code

```c
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
```
