# Question 3: Delivery Distance Analysis

Source code: [`delivery.c`](delivery.c). Real sample runs: [`sample_output.txt`](sample_output.txt).

## Sample input/output

I compiled it with `gcc delivery.c -o delivery` and got no errors or warnings. This is the example from the question:

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

Checking it by hand: 12 + 25 + 18 + 40 + 15 + 30 = 140, and 140 / 6 = 23.33. The longest route is 40. The routes over 20 km are 25, 40 and 30, so that's 3.

## How I split the program into functions

`main()` reads the input, checks that the number of routes is between 1 and 100, and prints the results. All the actual calculating happens in separate functions. Each one gets the array and the number of routes, and gives back one answer:

| Function | What it gets | What it gives back | How it works |
|---|---|---|---|
| `total_distance` | `distances[]`, `count` | the total (`int`) | a `for` loop adds up every distance |
| `average_distance` | `distances[]`, `count` | the average (`float`) | calls `total_distance()` and divides by `count` |
| `longest_route` | `distances[]`, `count` | the longest (`int`) | starts with the first distance and keeps whichever is bigger as it goes |
| `count_above_limit` | `distances[]`, `count`, `limit` | how many routes (`int`) | adds 1 every time a distance is bigger than `limit` |
| `recursive_sum` | `distances[]`, `count` | the total (`int`) | adds the distances by calling itself |

For function reuse, `average_distance()` doesn't add the numbers up again. It just calls `total_distance()` (line 24) and uses that answer. So the adding code is written once and used in two places, in `main()` and inside `average_distance()`. Also, because the limit is passed in as a parameter, `count_above_limit()` works for any limit (20 km, 30 km, whatever) without touching the code.

In `average_distance()` I wrote `(float)total / count`. The `(float)` matters. Without it, C divides two whole numbers, cuts off the decimals, and prints 23.00 instead of 23.33.

## How the recursive function works

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

The idea is simple: the sum of all the routes is the last route plus the sum of all the routes before it.

- Base case: when `count` is 0 there's nothing left to add, so it returns 0 and stops calling itself.
- Getting closer to the base case: every call passes `count - 1`, so there's one route fewer each time. Eventually it has to hit 0, so it always stops.
- Returning the result: each call adds its last distance to whatever the smaller call returned, then passes that back up to the call before it.

Here's what happens with the example array:

```
recursive_sum(6) = 30 + recursive_sum(5)
recursive_sum(5) = 15 + recursive_sum(4)
recursive_sum(4) = 40 + recursive_sum(3)
recursive_sum(3) = 18 + recursive_sum(2)
recursive_sum(2) = 25 + recursive_sum(1)
recursive_sum(1) = 12 + recursive_sum(0)
recursive_sum(0) = 0                       <- base case
```

Then the answers come back up: 12, 37, 55, 95, 110 and finally 140. The program prints `Recursive sum: 140 km`, the same as the loop version, so the two methods agree.

## One advantage and one limitation

Advantage: the code is really short, and it reads just like the way you'd explain the problem out loud ("last route plus the sum of the rest"). There's no loop counter to keep track of.

Limitation: every call has to wait for the next one to finish, and each waiting call takes up a bit of memory on the stack. For 6 routes that's only 7 calls, so it's nothing. But with a huge array, like a million routes, the program would run out of stack memory and crash. The `for` loop in `total_distance()` doesn't have that problem, because it uses the same small amount of memory no matter how many routes there are. My program only allows up to 100 routes anyway, so it's safe here.
