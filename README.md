# C Project 1

This repository holds the four programs for Project 1: three C programs (Questions 1 to 3) and a smart parking indicator built with an Arduino in Tinkercad (Question 4). This README is the full write-up. It starts with Question 4, whose circuit and tests are the quickest to see at a glance, and then works through the C programs in order. Each question folder holds the code, a short answer file, and the input and output from a real run. The parking circuit can also be opened and run on Tinkercad at <https://www.tinkercad.com/things/af6CaRZ7KVX-smart-parking-system?sharecode=5jWkTN-CQHOvnFIWV-pHdCgkueqLRMvHqunsgteppko>.

## Repository layout

| Question | Code | Answers | Evidence |
|---|---|---|---|
| Q1 Sensor monitoring | [`q1/water_quality.c`](q1/water_quality.c) | [`q1/water_quality_readme.md`](q1/water_quality_readme.md) | [`q1/sample_input.txt`](q1/sample_input.txt), [`q1/sample_output.txt`](q1/sample_output.txt), [`q1/more_test_runs.txt`](q1/more_test_runs.txt) |
| Q2 Mobile money | [`q2/mobile_money.c`](q2/mobile_money.c) | [`q2/mobile_money_readme.md`](q2/mobile_money_readme.md) | [`q2/sample_input.txt`](q2/sample_input.txt), [`q2/sample_output.txt`](q2/sample_output.txt) |
| Q3 Delivery distances | [`q3/delivery.c`](q3/delivery.c) | [`q3/delivery_readme.md`](q3/delivery_readme.md) | [`q3/sample_input.txt`](q3/sample_input.txt), [`q3/sample_output.txt`](q3/sample_output.txt) |
| Q4 Smart parking | [`q4/parking.ino`](q4/parking.ino) | [`q4/parking_readme.md`](q4/parking_readme.md) | [`q4/images`](q4/images) (circuit, block diagram, five simulation tests) |

## How to compile and run

The three C programs need only a C compiler such as gcc:

```
gcc q1/water_quality.c -o water_quality && ./water_quality
gcc q2/mobile_money.c -o mobile_money && ./mobile_money
gcc q3/delivery.c -o delivery && ./delivery
```

To replay a sample run, feed its input file, for example `./delivery < q3/sample_input.txt`. The results match `sample_output.txt`, but the typed values are not shown when the input comes from a file.

For Question 4, open the Tinkercad link above, or paste `q4/parking.ino` into a Tinkercad circuit wired as described below, and start the simulation. Clicking the sensor lets you drag the object closer or further away.

## Question 4: Arduino Smart Parking System

The goal is a small indicator for one parking space: green when the space is free, red and a beep when a car is in it. An HC-SR04 ultrasonic sensor measures the distance to whatever is in front of it, an Arduino Uno decides whether that counts as a car, and two LEDs and a piezo buzzer show the result.

### 1. Tinkercad circuit design

![Tinkercad circuit: Smart Parking System](q4/images/circuit.jpg)

Everything sits on a small breadboard. Its rails are fed by the Arduino's 5V and GND pins, and the sensor takes its power from them. The sensor's TRIG and ECHO pins connect to Arduino pins 10 and 9. Each LED runs from its Arduino pin through a 220 ohm resistor and back to ground, with green on pin 3 and red on pin 4. The buzzer's positive leg goes to pin 5. In the picture, black wires are ground, red wires are 5V, and each signal has its own colour.

### 2. Block diagram

![Block diagram](q4/images/block_diagram.png)

The only signal sent back to the sensor is the trigger pulse from the Arduino. Everything else flows forward: the sensor returns the echo time, the Arduino turns it into a distance and compares it with the 50 cm threshold, and the result drives the LEDs and the buzzer.

### 3. Arduino source code

`setup()` sets the pin modes and starts the Serial Monitor, and `loop()` repeats the measure-and-decide cycle from the block diagram. I chose 50 cm as the threshold because a car in the space sits well inside it, while an empty space gives a much longer reading. The full sketch, exactly as it runs in Tinkercad, is [`q4/parking.ino`](q4/parking.ino).

### 4. Simulation test cases

To test the system, I ran the simulation and dragged the object in front of the sensor to different distances. For each position I checked the LEDs, the buzzer and the Serial Monitor. The first three tests cover a free space, a parked car and the car driving away. The last two sit either side of the threshold, at 55.3 cm and 45.4 cm, to show the outputs switching around 50 cm.

| Test | Distance | Serial Monitor | Green | Red | Buzzer |
|---|---|---|---|---|---|
| 1. Free space | 171.9 cm | 169 cm, AVAILABLE | ON | OFF | OFF |
| 2. Car parked | 21.6 cm | 21 cm, OCCUPIED | OFF | ON | ON |
| 3. Car leaves | 110.8 cm | 109 cm, AVAILABLE | ON | OFF | OFF |
| 4. Just outside 50 cm | 55.3 cm | 54 cm, AVAILABLE | ON | OFF | OFF |
| 5. Just inside 50 cm | 45.4 cm | 44 cm, OCCUPIED | OFF | ON | ON |

| Test 1: 171.9 cm | Test 2: 21.6 cm | Test 3: 110.8 cm |
|---|---|---|
| ![Test 1](q4/images/test1_far_171cm.jpg) | ![Test 2](q4/images/test2_near_21cm.jpg) | ![Test 3](q4/images/test3_back_out_110cm.jpg) |

| Test 4: 55.3 cm | Test 5: 45.4 cm |
|---|---|
| ![Test 4](q4/images/test4_just_outside_55cm.jpg) | ![Test 5](q4/images/test5_just_inside_45cm.jpg) |

The Serial Monitor reads a little lower than Tinkercad's distance, by about 3 cm at most here. Part of the gap comes from the program working in whole centimetres with a rounded speed of sound, and the rest probably from how Tinkercad times the echo. In these five tests it never moves a reading across the threshold, but an object at about 50.5 cm could read 49 cm and count as occupied. The full screenshots, which also show the Serial Monitor, are in [`q4/images`](q4/images).

### 5. Short explanation

The HC-SR04 sends an ultrasonic pulse and reports how long the echo takes to return. The Arduino Uno runs the program, so it triggers the sensor, works out the distance and switches the outputs. The green LED tells a driver the space is free, the red LED says it is taken, and the buzzer sounds while a car is there. The 220 ohm resistors protect the LEDs by limiting their current, and the breadboard shares 5V and GND between the parts.

The sensor data goes through three steps. First the Arduino holds TRIG high for 10 microseconds, which makes the sensor send a pulse. Then `pulseIn(echoPin, HIGH)` measures how long ECHO stays high, which is the time the sound takes to reach the car and come back. Finally, because sound travels about 0.034 cm per microsecond and makes the trip twice, the program calculates `distance = duration * 0.034 / 2` and prints it.

The outputs are controlled by a single `if / else`. When `distance < threshold` (50 cm), the red LED turns on, the green LED turns off, and `tone(buzzer, 1000)` plays a continuous 1000 Hz tone. Otherwise the green LED turns on, the red one turns off, and `noTone(buzzer)` stops the tone. After `delay(500)` the loop runs again, so the lights update about twice a second as a car arrives or leaves.

## Question 1: Sensor Monitoring System

This program takes a temperature and a turbidity reading, turns them into a water-quality index and prints a short report. The index is 100 minus two penalties: how far the temperature is from 25 C, and half the turbidity. The index then decides whether the water is Good, Warning or Critical.

### 1. Complete C source code

The work is split across three small functions, so that `main()` only reads the input and prints the report. `temperature_deviation()` returns how far the temperature is from 25 C. The task describes this as abs(), but abs() only works on whole numbers, so the function uses an `if` to turn a negative difference positive. `quality_index()` applies the formula using that deviation, and `print_status()` prints the matching status. The full code is [`q1/water_quality.c`](q1/water_quality.c).

### 2. Sample output from one test run

Compiled with `gcc water_quality.c -o water_quality`, with no errors or warnings, a reading of 28.5 C and 12 NTU ([`q1/sample_input.txt`](q1/sample_input.txt)) gives:

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

This matches the calculation by hand. The deviation is 3.5 and the penalty is 6, so the index is 100 - 9.5 = 90.5, which is Good. I also ran the edges of each band. At 25 C, a turbidity of 40 gives exactly 80 (Good), 80 gives exactly 60 (Warning) and 82 gives 59 (Critical). A cold reading of 10 C with 50 NTU also gives 60, so 15 C too cold costs the same as 15 C too hot. Those runs are in [`q1/more_test_runs.txt`](q1/more_test_runs.txt).

### 3. Short technical explanation

#### (a) Real-world application

C is widely used to program small embedded devices, such as the microcontroller inside a water-quality monitor. The Arduino Uno's chip, the ATmega328P, has only 32 KB of program memory and 2 KB of RAM. C suits this because it compiles to small, fast machine code with no interpreter or garbage collector. It also gives direct control over the hardware pins and timers, and its timing is predictable, which matters when a sensor has to be read at the right moment.

#### (b) Error analysis

A syntax error would be leaving out the semicolon at the end of this line in `quality_index()`:

```c
penalty = turbidity / 2
```

gcc refuses to compile it and reports `error: expected ';' before 'index'`. This is a syntax error because it breaks C's grammar: every statement must end with a semicolon, so the compiler cannot make sense of the code and no program is built.

A semantic error would be writing the formula without its brackets:

```c
index = 100 - deviation + penalty;
```

This compiles with no errors or warnings, but for 28.5 C and 12 NTU the program now prints 102.50 instead of 90.50. C subtracts the deviation first and then adds the penalty, so dirty water raises the score instead of lowering it. The grammar is fine but the meaning is wrong, which is what makes it a semantic error. The compiler cannot catch it; only checking the output against a hand calculation does.

#### (c) Compilation lifecycle

Turning `water_quality.c` into a program takes four stages. I ran each one separately to see what goes in and what comes out.

1. Preprocessing (`gcc -E`) takes `water_quality.c` (74 lines) and outputs `water_quality.i` (810 lines). The `#include <stdio.h>` line is replaced by the whole header file and the comments are removed, which is why the file grows so much.
2. Compilation (`gcc -S`) takes `water_quality.i` and outputs `water_quality.s`, 229 lines of assembly. This is where the code is checked for errors and translated into instructions for the processor.
3. Assembly (`gcc -c`) takes `water_quality.s` and outputs the object file `water_quality.o`, which is machine code. My own functions are in it, but `printf` and `scanf` are still missing.
4. Linking takes `water_quality.o` and the C library and outputs the executable `water_quality`. The linker adds the library code for `printf` and `scanf` and the start-up code, giving a program that can run.

Normally `gcc water_quality.c -o water_quality` runs all four stages in one go. The line counts are from my machine and can differ slightly on another system.

## Question 2: Mobile Money Transaction System

This is a menu-driven program for a mobile-money agent. It keeps a balance and two counters, and it loops through a menu of deposit, withdraw, balance, summary and exit until the agent chooses to leave. Every amount and menu choice is checked before anything changes.

### 1. Complete C source code

All the variables are `int`. The balance and the amounts are whole Rwandan francs, the two counters only ever hold whole numbers, and the menu choice is 1 to 5. One more variable, `result`, stores what `scanf` returns. That value is 1 for a number, 0 for letters and `EOF` when the input ends, which is how the program tells good input from bad. The full code is [`q2/mobile_money.c`](q2/mobile_money.c).

### 2. Sample input/output

The session below, compiled with `gcc mobile_money.c -o mobile_money`, uses all five options. It also includes four inputs that should fail: withdrawing more than the balance, a negative amount, menu number 9 and the letters `abc`. The program prints its menu before every choice. Here the menu is shown once to save space. The full session is in [`q2/sample_output.txt`](q2/sample_output.txt), and the input that produced it is in [`q2/sample_input.txt`](q2/sample_input.txt).

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

Enter choice: 2
Enter withdrawal amount: 70000
Transaction rejected: Insufficient balance.

Enter choice: 2
Enter withdrawal amount: -200
Transaction rejected: Amount must be positive.

Enter choice: 2
Enter withdrawal amount: 20000
Withdrawal successful.
Current balance: 30000 RWF

Enter choice: 3
Current balance: 30000 RWF

Enter choice: 9
Invalid choice. Please enter a number from 1 to 5.

Enter choice: abc
Invalid input. Please enter a number.

Enter choice: 4
===== TRANSACTION SUMMARY =====
Successful deposits: 1
Successful withdrawals: 1

Enter choice: 5
System terminated.
```

Each invalid input gets a clear message, and the balance only changes on the two successful transactions. Amounts have to be whole francs, so a decimal like 12.5 is not supported. The program keeps the 12 and treats the leftover .5 as invalid input at the next menu.

### 3. How the program uses conditionals, loops, break and continue

The whole menu runs inside a `while (1)` loop (line 31), so the agent can keep working without restarting. Inside it, the program first checks what `scanf` read: `result == EOF` means the input has ended (line 42), `result != 1` catches letters (line 49), `choice == 5` handles Exit (line 57), and `choice < 1 || choice > 5` catches numbers that are not on the menu (line 64). A valid choice then goes to a `switch` (line 70). Inside Deposit and Withdraw, an `if / else` rejects amounts of 0 or less and withdrawals larger than the balance.

`continue` sends the agent straight back to the menu when the input itself is unusable: letters at the menu (line 53), a number that is not on the menu (line 67), or letters typed as an amount (lines 79 and 102). It skips the rest of the loop body, so nothing changes. A rejected amount, such as a negative number or an overdraw, prints its message and leaves the `switch` through its normal `break`, which also brings the menu back. `break` is used in two ways. Each `case` in the switch ends with `break` (lines 93, 120, 124 and 130), so one operation never runs into the next. Choosing 5 prints "System terminated." and uses `break` (line 60) to leave the loop. A second `break` (line 45) leaves the loop if the input runs out, for example after Ctrl+D, so the program never gets stuck.

Letters need one extra step. When `scanf` cannot read a number, it leaves the letters waiting in the input, and every later `scanf` would trip over them forever. The small `clear_input()` function reads and throws away the rest of that line before `continue` returns to the menu.

## Question 3: Delivery Distance Analysis

This program stores the distances of up to 100 delivery routes in an `int` array. It reports the total, the average, the longest route and how many routes are over a chosen limit. It also adds the distances a second time with a recursive function, which acts as a check on the loop.

### 1. Complete C source code

The full code is [`q3/delivery.c`](q3/delivery.c). Section 3 below explains how it is divided into functions.

### 2. Sample input/output

This run uses the example from the task, six routes and a 20 km limit ([`q3/sample_input.txt`](q3/sample_input.txt)), compiled with `gcc delivery.c -o delivery`:

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

These match the expected results: 140 km in total, an average of 140 / 6 = 23.33 km, a longest route of 40 km, and three routes over 20 km (25, 40 and 30).

### 3. How the program is divided into functions

`main()` only handles input and output. It reads the routes, checks there are between 1 and 100 of them, and prints the results. Each calculation is a separate function that takes the array and the number of routes and returns a single value.

| Function | Returns | How it works |
|------------|--------|------------------------|
| `total_distance` | the total (`int`) | a `for` loop adds every distance |
| `average_distance` | the average (`float`) | calls `total_distance()` and divides by the count |
| `longest_route` | the longest (`int`) | keeps the biggest distance seen so far |
| `count_above_limit` | a count (`int`) | also takes the limit, and counts distances above it |
| `recursive_sum` | the total (`int`) | adds the distances by calling itself |

The functions reuse each other where it makes sense. `average_distance()` calls `total_distance()` (line 24) instead of adding the numbers again. `count_above_limit()` takes the limit as a parameter, so the same function works for 20 km, 30 km or any other limit. The average also turns the total into a `float` before dividing. Without that, C would do whole-number division and print 23.00 instead of 23.33.

### 4. How the recursive function works, including its base case

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

The idea is that the sum of all the routes is the last route plus the sum of the ones before it. The base case is `count == 0`. With no routes left there is nothing to add, so the function returns 0 and stops calling itself. Every other call passes `count - 1`, so each call works on one route fewer and the chain always reaches the base case. On the way back, each call adds its own distance to the result it receives and returns the total to its caller. For the example array the calls unfold like this:

```
recursive_sum(6) = 30 + recursive_sum(5)
recursive_sum(5) = 15 + recursive_sum(4)
recursive_sum(4) = 40 + recursive_sum(3)
recursive_sum(3) = 18 + recursive_sum(2)
recursive_sum(2) = 25 + recursive_sum(1)
recursive_sum(1) = 12 + recursive_sum(0)
recursive_sum(0) = 0                       <- base case
```

The results then come back up the chain as 12, 37, 55, 95, 110 and finally 140, the same total the loop produced.

### 5. One advantage and one limitation of using recursion

The advantage is clarity: the function mirrors the definition of the sum, with no loop counter to manage. The limitation is memory. Every call waits on the stack until the next one returns, so six routes need seven calls at the same time. That is no problem here, but with a few hundred thousand routes the program could run out of stack space and crash. The loop in `total_distance()` uses the same small amount of memory for any size. Since this program accepts at most 100 routes, recursion is safe for it.

## Author

Wisdom Okechukwu
