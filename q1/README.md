# Question 1: Sensor Monitoring System

## How the program is organised

Source code: [`water_quality.c`](water_quality.c) (also shown in full at the end). Real sample runs: [`sample_output.txt`](sample_output.txt).

Besides `main()`, I split the work into three small functions:

- `temperature_deviation()` works out how far the temperature is from 25 C. The question says abs(), but abs() only works on whole numbers, so I wrote my own with an `if`: if the answer is negative, I flip it to positive.
- `quality_index()` does the formula: 100 minus (deviation + turbidity / 2).
- `print_status()` looks at the index and prints Good, Warning or Critical.

## Sample output

I compiled it with `gcc water_quality.c -o water_quality` and got no errors or warnings. Here's one run:

```
$ ./water_quality
Enter temperature (C): 28.5
Enter turbidity (NTU): 12

===== WATER QUALITY REPORT =====
Temperature   : 28.50 C
Turbidity     : 12.00 NTU
Quality index : 90.50
Status        : Good
================================
```

Checking it by hand: 28.5 is 3.5 away from 25, and 12 / 2 is 6. So the index is 100 - (3.5 + 6) = 90.5. That's 80 or more, so it's Good.

I also tried a few other readings to make sure every status shows up:

| Temperature | Turbidity | Index | Status |
|---|---|---|---|
| 25 | 40 | 80.00 | Good |
| 25 | 80 | 60.00 | Warning |
| 25 | 82 | 59.00 | Critical |
| 10 | 50 | 60.00 | Warning |

The last row checks the cold side. 10 C is 15 below 25, and the program still counts that as a deviation of 15, not -15.

## (a) Real-world application

A good example is the firmware inside small devices like this water-quality monitor. These run on tiny chips. The Arduino Uno's chip, the ATmega328P, only has 32 KB of program memory and 2 KB of RAM. C works well here because it compiles into small, fast machine code and doesn't need anything heavy running in the background. It also lets you control the hardware pins and timers directly. And the timing is predictable, which matters when you need to read a sensor at the right moment.

## (b) Error analysis

### Syntax error

Say I forget the semicolon on this line in `quality_index()`:

```c
penalty = turbidity / 2
```

gcc refuses to compile and tells me:

```
syn.c:27:25: error: expected ';' before 'index'
```

That's a syntax error because I broke C's grammar rules. Every statement has to end with `;`. The compiler can't make sense of the code, so no program gets built at all.

### Semantic error

Now say I write the formula without the brackets:

```c
index = 100 - deviation + penalty;
```

This one compiles fine, with no errors and no warnings. But for 28.5 C and 12 NTU the program prints `Quality index : 102.50` instead of `90.50`. C does the subtraction first and then adds the penalty, so dirty water actually pushes the score up.

That's a semantic error. The grammar is fine, but the meaning is wrong. The compiler has no way of knowing what I meant, so the only way to catch it is to test the output against a calculation done by hand.

## (c) Compilation lifecycle

I ran each stage separately on my own file to see what goes in and what comes out.

**1. Preprocessing**

- Command: `gcc -E water_quality.c -o water_quality.i`
- Input: `water_quality.c` (74 lines)
- Output: `water_quality.i` (810 lines)
- What happens: `#include <stdio.h>` gets replaced with the whole header file, and the comments are removed. That's why 74 lines turn into 810.

**2. Compilation**

- Command: `gcc -S water_quality.i -o water_quality.s`
- Input: `water_quality.i`
- Output: `water_quality.s` (229 lines of assembly)
- What happens: the compiler checks the code for errors and translates the C into assembly instructions for the processor.

**3. Assembly**

- Command: `gcc -c water_quality.s -o water_quality.o`
- Input: `water_quality.s`
- Output: `water_quality.o` (object file)
- What happens: the assembly becomes binary machine code. My own functions are in there, but `printf` and `scanf` are still missing.

**4. Linking**

- Command: `gcc water_quality.o -o water_quality`
- Input: `water_quality.o` and the C library
- Output: `water_quality` (the executable)
- What happens: the linker joins my code with the library code for `printf` and `scanf`, adds the start-up code, and gives me a program I can run.

The line counts are from my machine. They can be a bit different on another computer, because the header files and assembly depend on the system.

Normally you just run `gcc water_quality.c -o water_quality` and it does all four stages in one go.

## Full source code

```c
#include <stdio.h>

/* Returns how far the temperature is from 25 C. The answer is never negative. */
float temperature_deviation(float temperature)
{
	float deviation;

	deviation = temperature - 25;

	/* this works like abs(): turn a negative number into a positive one */
	if (deviation < 0)
	{
		deviation = -deviation;
	}

	return deviation;
}

/* Calculates the water-quality index from the two sensor readings */
float quality_index(float temperature, float turbidity)
{
	float deviation;
	float penalty;
	float index;

	deviation = temperature_deviation(temperature);
	penalty = turbidity / 2;
	index = 100 - (deviation + penalty);

	return index;
}

/* Prints Good, Warning or Critical depending on the index */
void print_status(float index)
{
	if (index >= 80)
	{
		printf("Status        : Good\n");
	}
	else if (index >= 60)
	{
		printf("Status        : Warning\n");
	}
	else
	{
		printf("Status        : Critical\n");
	}
}

int main(void)
{
	float temperature;
	float turbidity;
	float index;

	/* read the two sensor values */
	printf("Enter temperature (C): ");
	scanf("%f", &temperature);
	printf("Enter turbidity (NTU): ");
	scanf("%f", &turbidity);

	/* calculate the index */
	index = quality_index(temperature, turbidity);

	/* print the report */
	printf("\n===== WATER QUALITY REPORT =====\n");
	printf("Temperature   : %.2f C\n", temperature);
	printf("Turbidity     : %.2f NTU\n", turbidity);
	printf("Quality index : %.2f\n", index);
	print_status(index);
	printf("================================\n");

	return 0;
}
```
