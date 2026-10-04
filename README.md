# C Project 1

Four small programs for Project 1. Three are plain C programs. One is an Arduino program, which Arduino calls a sketch.

## Files

| Question | File | What it does |
|---|---|---|
| Q1 | `q1/water_quality.c` | Reads two sensor values and prints a water-quality status. |
| Q2 | `q2/mobile_money.c` | Mobile-money menu. Refuses negative amounts and withdrawals bigger than the balance. |
| Q3 | `q3/delivery.c` | Route total, average and longest route. Also a sum done by a function that calls itself. |
| Q4 | `q4/parking.ino` | Smart parking light for Tinkercad, a free online circuit simulator. Red LED and buzzer under 50 cm, green LED otherwise. |

## Answers and evidence

Each question folder holds its code and its written answers (`<program>_readme.md`). It also holds the input and output of a real run, or screenshots for Q4.

| Question | Answers | Evidence |
|---|---|---|
| Q1 | [q1/water_quality_readme.md](q1/water_quality_readme.md) | [q1/sample_input.txt](q1/sample_input.txt), [q1/sample_output.txt](q1/sample_output.txt), plus four more runs in [q1/more_test_runs.txt](q1/more_test_runs.txt) |
| Q2 | [q2/mobile_money_readme.md](q2/mobile_money_readme.md) | [q2/sample_input.txt](q2/sample_input.txt), [q2/sample_output.txt](q2/sample_output.txt), a full menu session |
| Q3 | [q3/delivery_readme.md](q3/delivery_readme.md) | [q3/sample_input.txt](q3/sample_input.txt), [q3/sample_output.txt](q3/sample_output.txt), the example from the question |
| Q4 | [q4/parking_readme.md](q4/parking_readme.md) | [q4/images](q4/images), circuit, block diagram and five simulation tests |

## Compile and run (Q1 to Q3)

gcc is the C compiler. It turns a `.c` file into a program you can run.

```
gcc q1/water_quality.c -o water_quality
./water_quality

gcc q2/mobile_money.c -o mobile_money
./mobile_money

gcc q3/delivery.c -o delivery
./delivery
```

Example for Q3, using the numbers from the question:

```
Enter number of routes: 6
Enter distance 1: 12
...
Enter distance limit: 20

===== DELIVERY DISTANCE ANALYSIS =====

Total distance: 140 km
Average distance: 23.33 km
Longest route: 40 km
Routes above 20 km: 3

Recursive sum: 140 km
```

## Q4 wiring (Tinkercad)

| Part | Arduino Uno |
|---|---|
| HC-SR04 power (VCC) and ground (GND) | 5V and GND, through the long power strips on the breadboard |
| HC-SR04 TRIG, which tells the sensor to send a sound | pin 10 |
| HC-SR04 ECHO, which carries the sensor's answer | pin 9 |
| Green LED (with 220 ohm resistor) | pin 3 |
| Red LED (with 220 ohm resistor) | pin 4 |
| Piezo buzzer | pin 5 |

In Tinkercad, open the code editor and switch it from Blocks to Text. Paste in `q4/parking.ino`. Start the simulation and click the sensor. A small circle appears in front of it. Drag the circle closer than 50 cm, and the red LED and buzzer turn on.

## Author

Wisdom Okechukwu
