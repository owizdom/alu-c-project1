# Question 1: Sensor Monitoring System

## Deliverables

| # | Deliverable (from the assignment) | Where |
|---|---|---|
| 1 | Complete C source code | [Section 1](#1-complete-c-source-code), [`water_quality.c`](water_quality.c) |
| 2 | Sample output from one test run | [Section 2](#2-sample-output-from-one-test-run), [`sample_input.txt`](sample_input.txt), [`sample_output.txt`](sample_output.txt), [`more_test_runs.txt`](more_test_runs.txt) |
| 3 | Short technical explanation covering (a), (b), and (c) | [Section 3](#3-short-technical-explanation) |

## 1. Complete C source code

Source code: [`water_quality.c`](water_quality.c). To turn it into a program, use gcc, the C compiler: `gcc water_quality.c -o water_quality`.

Sample input: [`sample_input.txt`](sample_input.txt). Sample output: [`sample_output.txt`](sample_output.txt). Both files come from a real run. To run it again with the same input, use `./water_quality < sample_input.txt`. The `<` feeds the file in as if you typed it.

Turbidity is how cloudy the water is, measured in NTU. The program has three small functions besides `main()`:

- `temperature_deviation()` works out how far the temperature is from 25 C. The task says to use abs(). But abs() only works on whole numbers, and the temperature can be a decimal like 28.5. So the function uses an `if` instead: when the difference is negative, it makes it positive.
- `quality_index()` works out the index: 100 minus (deviation + turbidity / 2).
- `print_status()` prints Good, Warning or Critical, depending on the index.

## 2. Sample output from one test run

I compiled the program with `gcc water_quality.c -o water_quality`. There were no errors or warnings. Here is one run:

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

You can check this by hand. 28.5 is 3.5 away from 25. Half of 12 is 6. So the index is 100 - (3.5 + 6) = 90.5. That is 80 or more, so the status is Good.

I also tried other readings, to see every status:

| Temperature | Turbidity | Index | Status |
|---|---|---|---|
| 25 | 40 | 80.00 | Good |
| 25 | 80 | 60.00 | Warning |
| 25 | 82 | 59.00 | Critical |
| 10 | 50 | 60.00 | Warning |

The last row tests cold water. 10 C is 15 below 25. The program counts that as 15, not -15, which is correct.

## 3. Short technical explanation

### (a) Real-world application

C is often used to program small devices, such as a real water-quality monitor. A program that lives inside a device like this is called firmware. A real monitor could use a small chip such as the Arduino Uno's ATmega328P. That chip can store only 32 KB of program and 2 KB of working data. A C program is small enough to fit. C turns into small, fast machine code, which is the 0s and 1s the chip runs. It does not need an operating system, such as Windows, underneath it. It can switch the chip's pins, its electrical connections, on and off directly. And it runs at a steady, predictable speed. That matters when a sensor has to be read at the right moment.

### (b) Error analysis

#### Syntax error

A syntax error breaks the grammar rules of C. For example, I could forget the semicolon at the end of this line in `quality_index()`:

```c
penalty = turbidity / 2
```

The compiler (gcc) then stops and shows this message:

```
syn.c:27:25: error: expected ';' before 'index'
```

Here `syn.c` is a copy of the program with the `;` removed. `27:25` means line 27, character 25. gcc only notices the problem at the next word, `index`. This message comes from gcc on Linux. On a Mac the wording is a little different.

This is a syntax error because every statement in C must end with `;`. The compiler cannot understand the code, so it does not build the program at all.

#### Semantic error

A semantic error is code with correct grammar but the wrong meaning. For example, I could write the formula without the brackets:

```c
index = 100 - deviation + penalty;
```

This compiles with no errors and no warnings. But for 28.5 C and 12 NTU, the program prints `Quality index : 102.50` instead of `90.50`. C subtracts the deviation first, then adds the penalty. So dirty water raises the score instead of lowering it. The compiler cannot know what I meant, so it cannot catch this. Only testing the output against a hand calculation shows the mistake.

### (c) Compilation lifecycle

Turning the C file into a program takes four stages. I ran each stage on its own to see what goes in and what comes out. The options `-E`, `-S` and `-c` tell gcc to stop after the first, second and third stage.

#### 1. Preprocessing

- Command: `gcc -E water_quality.c -o water_quality.i`.
- Input: `water_quality.c`, which has 74 lines.
- Output: `water_quality.i`, which has 810 lines.
- What happens: the line `#include <stdio.h>` is replaced by the whole of `stdio.h`. That is a file that describes `printf`, `scanf` and other ready-made functions. The comments are removed, but `stdio.h` adds far more lines. So the file grows from 74 to 810 lines.

#### 2. Compilation

- Command: `gcc -S water_quality.i -o water_quality.s`.
- Input: `water_quality.i`.
- Output: `water_quality.s`, which has 229 lines of assembly code. Assembly is a text form of the processor's own instructions, one small step per line.
- What happens: the compiler checks the code for errors. Then it turns the C into assembly.

#### 3. Assembly

- Command: `gcc -c water_quality.s -o water_quality.o`.
- Input: `water_quality.s`.
- Output: `water_quality.o`, an object file. This is machine code that is not ready to run yet.
- What happens: the assembly code becomes machine code. My own functions are in this file. But `printf` and `scanf` are still missing. Their code is in the C library, which is ready-made code that comes with gcc.

#### 4. Linking

- Command: `gcc water_quality.o -o water_quality`.
- Input: `water_quality.o` and the C library.
- Output: `water_quality`, the finished program that you can run.
- What happens: the linker is the tool that joins the pieces. It adds the library code for `printf` and `scanf`. It also adds the code that runs before `main()` and calls it.

The line counts come from gcc on Linux. They can be a little different on another computer, because the header files and the assembly depend on the system.

In practice, the single command `gcc water_quality.c -o water_quality` runs all four stages at once.
