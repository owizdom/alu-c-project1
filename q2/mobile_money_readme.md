# Question 2: Mobile Money Transaction System

## Deliverables

| # | Deliverable (from the assignment) | Where |
|---|---|---|
| 1 | Complete C source code | [Section 1](#1-complete-c-source-code), [`mobile_money.c`](mobile_money.c) |
| 2 | Sample input/output demonstrating at least three different menu operations, including one invalid transaction | [Section 2](#2-sample-inputoutput), [`sample_input.txt`](sample_input.txt), [`sample_output.txt`](sample_output.txt) |
| 3 | Brief explanation of how the program uses conditionals, loops, break, and continue | [Section 3](#3-how-the-program-uses-conditionals-loops-break-and-continue) |

## 1. Complete C source code

Source code: [`mobile_money.c`](mobile_money.c). Compile it with `gcc mobile_money.c -o mobile_money`.

Sample input: [`sample_input.txt`](sample_input.txt). Sample output: [`sample_output.txt`](sample_output.txt). Both come from a real run. Running `./mobile_money < sample_input.txt` gives the same results (the typed values just are not shown when the input comes from a file).

### Data types I used

Everything is an `int`, and here's why for each one:

- `balance` and `amount`: mobile money in RWF is handled in whole francs. Nobody sends 500.75 RWF, so I didn't need decimals.
- `deposit_count` and `withdrawal_count`: you can't have half a transaction, so whole numbers make sense. Both start at 0.
- `choice`: the menu option, 1 to 5.
- `result`: this holds what `scanf` gives back. It's 1 if it read a number, 0 if the user typed letters, and `EOF` if there's no more input at all.

## 2. Sample input/output

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

## 3. How the program uses conditionals, loops, break and continue

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
