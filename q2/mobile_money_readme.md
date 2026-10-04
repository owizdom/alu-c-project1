# Question 2: Mobile Money Transaction System

## Deliverables

| # | Deliverable (from the assignment) | Where |
|---|---|---|
| 1 | Complete C source code | [Section 1](#1-complete-c-source-code), [`mobile_money.c`](mobile_money.c) |
| 2 | Sample input/output demonstrating at least three different menu operations, including one invalid transaction | [Section 2](#2-sample-inputoutput), [`sample_input.txt`](sample_input.txt), [`sample_output.txt`](sample_output.txt) |
| 3 | Brief explanation of how the program uses conditionals, loops, break, and continue | [Section 3](#3-how-the-program-uses-conditionals-loops-break-and-continue) |

## 1. Complete C source code

Source code: [`mobile_money.c`](mobile_money.c). To turn it into a program, use gcc, the C compiler: `gcc mobile_money.c -o mobile_money`.

Sample input: [`sample_input.txt`](sample_input.txt). Sample output: [`sample_output.txt`](sample_output.txt). Both files come from a real run. To run it again with the same input, use `./mobile_money < sample_input.txt`. The `<` feeds the file in as if you typed it.

### Data types I used

Every variable is an `int`, which holds whole numbers:

- `balance` and `amount` hold money in Rwandan francs. People send whole francs, like 50000 RWF, so decimals are not needed.
- `deposit_count` and `withdrawal_count` count successful transactions. A count is always a whole number, and both start at 0.
- `choice` holds the number typed at the menu. A valid choice is 1 to 5.
- `result` holds the number that `scanf` gives back. `scanf` is the function that reads what the user types. It gives back 1 if the user typed a number. It is 0 if the user typed letters. It is `EOF`, which means "end of input", if there is nothing left to read.

## 2. Sample input/output

I compiled the program with `gcc mobile_money.c -o mobile_money`. There were no errors or warnings.

In this run I used all five menu options. I also tried four things that should fail:

- withdrawing more than the balance,
- a negative amount,
- a menu number that does not exist (9),
- typing letters (abc).

Amounts must be whole francs, like 50000. A decimal like 12.5 is not supported. The program keeps the 12, and the leftover .5 shows up as invalid input at the next menu.

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

## 3. How the program uses conditionals, loops, break and continue

The loop. The whole menu sits inside `while (1)` (line 31). The 1 means true, so this loop never stops on its own. Only a `break` gets out of it. So the agent, the person who runs the mobile-money shop, can do many transactions without restarting the program.

The `if` checks. First, a few `if` checks look at what the agent typed:

- `result == EOF` (line 42) means the input has ended.
- `result != 1` (line 49) catches letters.
- `choice == 5` (line 57) means Exit.
- `choice < 1 || choice > 5` (line 64) catches numbers that are not on the menu. Here `||` means or.

If the choice is valid, a `switch (choice)` (line 70) jumps to the right operation for options 1 to 4. Inside Deposit and Withdraw, an `if / else` turns down amounts of 0 or less. Withdraw also turns down any amount bigger than the balance. The balance only changes when every check passes.

`continue`. Some input is not a usable number at all. Examples are letters at the menu, a menu number that does not exist, or letters typed as an amount. In those cases (lines 53, 67, 79 and 102), `continue` skips the rest of the loop and jumps back to the top. So the menu shows up again, and nothing changes. A negative or too-large amount works differently. It prints its message, and the case's `break` then ends the `switch`. The loop then shows the menu again.

`break`. It is used in two ways:

1. Every `case` in the `switch` ends with `break` (lines 93, 120, 124 and 130). Without it, C would carry on into the next case's code too.
2. When the agent chooses 5, the program prints "System terminated." Then `break` (line 60) jumps out of the `while` loop, and the program ends. One more `break` (line 45) leaves the loop if the input runs out, for example after Ctrl+D, the keys that mean no more input. So the program can never get stuck.

Letters. If the agent types `abc`, `scanf` cannot read it as a number. `scanf` leaves the letters unread, so they are still there next time. So a small function, `clear_input()`, reads the rest of that line and throws it away. Without it, the next `scanf` would read the same `abc` again, and the menu would repeat forever.
