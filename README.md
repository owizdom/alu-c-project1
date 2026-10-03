# C Project 1

Four small programs for Project 1. Three are plain C and one is an Arduino sketch. The code stays at a beginner level on purpose. It uses only `stdio.h`, plain variables, simple loops and `if` statements.

## Files

| Question | File | What it does |
|---|---|---|
| Q1 | `q1/water_quality.c` | Reads two sensor values and prints a water-quality status. |
| Q2 | `q2/mobile_money.c` | Mobile-money menu. Rejects negative amounts and overdrafts. |
| Q3 | `q3/delivery.c` | Route totals, average, longest route and a recursive sum. |
| Q4 | `q4/parking.ino` | Smart parking indicator for Tinkercad. Red LED and buzzer under 50 cm, green LED otherwise. |

## Compile and run (Q1 to Q3)

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
| HC-SR04 VCC / GND | 5V / GND (through the breadboard rails) |
| HC-SR04 TRIG | pin 10 |
| HC-SR04 ECHO | pin 9 |
| Green LED (with 220 ohm resistor) | pin 3 |
| Red LED (with 220 ohm resistor) | pin 4 |
| Piezo buzzer | pin 5 |

Paste `q4/parking.ino` into the Tinkercad code editor in Text mode. Start the simulation and click the sensor. Drag the object closer than 50 cm and the red LED and buzzer turn on.

## Author

Wisdom Okechukwu
