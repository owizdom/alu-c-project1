# Question 3: Delivery Distance Analysis

## Deliverables

| # | Deliverable (from the assignment) | Where |
|---|---|---|
| 1 | Complete C source code | [Section 1](#1-complete-c-source-code), [`delivery.c`](delivery.c) |
| 2 | Sample input/output | [Section 2](#2-sample-inputoutput), [`sample_input.txt`](sample_input.txt), [`sample_output.txt`](sample_output.txt) |
| 3 | Brief explanation of how the program is divided into functions | [Section 3](#3-how-the-program-is-divided-into-functions) |
| 4 | Brief explanation of how the recursive function works, including its base case | [Section 4](#4-how-the-recursive-function-works-including-its-base-case) |
| 5 | State one advantage and one limitation of using recursion for this problem | [Section 5](#5-one-advantage-and-one-limitation-of-using-recursion) |

## 1. Complete C source code

Source code: [`delivery.c`](delivery.c). To turn it into a program, use gcc, the C compiler: `gcc delivery.c -o delivery`.

Sample input: [`sample_input.txt`](sample_input.txt). Sample output: [`sample_output.txt`](sample_output.txt). Both files come from a real run. To run it again with the same input, use `./delivery < sample_input.txt`. The `<` feeds the file in as if you typed it.

## 2. Sample input/output

I compiled the program with `gcc delivery.c -o delivery`. There were no errors or warnings. This run uses the example from the task.

```
$ ./delivery
Enter number of routes: 6
Enter distance 1: 12
Enter distance 2: 25
Enter distance 3: 18
Enter distance 4: 40
Enter distance 5: 15
Enter distance 6: 30
Enter distance limit: 20

===== DELIVERY DISTANCE ANALYSIS =====

Total distance: 140 km
Average distance: 23.33 km
Longest route: 40 km
Routes above 20 km: 3

Recursive sum: 140 km
```

You can check this by hand. 12 + 25 + 18 + 40 + 15 + 30 = 140, and 140 / 6 = 23.33. The longest route is 40 km. Three routes are over 20 km: 25, 40 and 30.

## 3. How the program is divided into functions

`main()` reads the input and prints the results. It also checks that the number of routes is between 1 and 100. Each calculation is in its own function. An array is a list of values stored together, and every function gets the array of distances and the number of routes. Each function gives back one answer:

| Function | What it gets | What it gives back | How it works |
|---|---|---|---|
| `total_distance` | `distances[]`, `count` | the total (`int`) | a `for` loop adds up every distance |
| `average_distance` | `distances[]`, `count` | the average (`float`) | calls `total_distance()` and divides by `count` |
| `longest_route` | `distances[]`, `count` | the longest (`int`) | starts with the first distance and keeps the biggest one it sees |
| `count_above_limit` | `distances[]`, `count`, `limit` | how many routes (`int`) | adds 1 for every distance bigger than `limit` |
| `recursive_sum` | `distances[]`, `count` | the total (`int`) | adds the distances by calling itself |

In the table, `int` means a whole number and `float` means a decimal. `distances[]` is the array of distances.

Some functions reuse others. `average_distance()` does not add the numbers again. It calls `total_distance()` (line 24) and uses its answer. So the adding code is written once and used in two places. Also, the limit is passed in as an input value, called a parameter. So `count_above_limit()` works for any limit, like 20 km or 30 km, without changing the code.

In `average_distance()` I wrote `(float)total / count`. The `(float)` turns the total into a decimal number before dividing. Without it, C would divide two whole numbers and drop the decimals. The program would print 23.00 instead of 23.33.

## 4. How the recursive function works, including its base case

A recursive function is a function that calls itself.

```c
int recursive_sum(int distances[], int count)
{
	if (count == 0)
	{
		return 0;
	}
	return distances[count - 1] + recursive_sum(distances, count - 1);
}
```

The sum of all the routes is the last route plus the sum of the routes before it. Arrays count from 0, so the last route is at position `count - 1`. The function uses that idea:

- Base case: when `count` is 0, there is nothing left to add. The function returns 0 and stops calling itself.
- Moving toward the base case: every call passes `count - 1`. So each call has one route fewer. The count must reach 0, so the function always stops.
- Returning the result: each call adds its own last distance to the answer it gets back. Then it returns that total to whoever called it.

Here are the calls for the example array. The array is left out of each call to save space.

```
recursive_sum(6) = 30 + recursive_sum(5)
recursive_sum(5) = 15 + recursive_sum(4)
recursive_sum(4) = 40 + recursive_sum(3)
recursive_sum(3) = 18 + recursive_sum(2)
recursive_sum(2) = 25 + recursive_sum(1)
recursive_sum(1) = 12 + recursive_sum(0)
recursive_sum(0) = 0                       <- base case
```

Then the answers come back up the chain: 12, 37, 55, 95, 110 and finally 140. The program prints `Recursive sum: 140 km`. That is the same as the loop's total, so the two methods agree.

## 5. One advantage and one limitation of using recursion

Advantage: the code is short and easy to read. It follows the same idea you would say out loud: "the last route plus the sum of the rest". There is no loop counter to keep track of.

Limitation: each call has to wait for the next call to finish. Every waiting call keeps a small block of memory on the stack. The stack is the part of memory C uses for function calls. Six routes need only seven calls, which is fine. But with a few hundred thousand routes, the program could run out of stack memory and crash. The `for` loop in `total_distance()` does not have this problem, because it uses the same small amount of memory for any number of routes. My program allows at most 100 routes, so recursion is safe here.
