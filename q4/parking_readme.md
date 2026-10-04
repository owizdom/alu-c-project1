# Question 4: Arduino Smart Parking System

## Deliverables

| # | Deliverable (from the assignment) | Where |
|---|---|---|
| 1 | Tinkercad circuit design showing all components and connections | [Section 1](#1-tinkercad-circuit-design), [`images/circuit.jpg`](images/circuit.jpg), [live design on Tinkercad](https://www.tinkercad.com/things/af6CaRZ7KVX-smart-parking-system?sharecode=5jWkTN-CQHOvnFIWV-pHdCgkueqLRMvHqunsgteppko) |
| 2 | Block diagram showing the flow of data through the system | [Section 2](#2-block-diagram), [`images/block_diagram.png`](images/block_diagram.png) |
| 3 | Arduino source code used in the Tinkercad simulation | [Section 3](#3-arduino-source-code), [`parking.ino`](parking.ino) |
| 4 | At least two simulation test cases | [Section 4](#4-simulation-test-cases), five tests, two of them either side of 50 cm, screenshots in [`images/`](images) |
| 5 | Short explanation describing the role of each component, how sensor data is processed, how the Arduino controls the outputs | [Section 5](#5-short-explanation) |

## 1. Tinkercad circuit design

Live design on Tinkercad: <https://www.tinkercad.com/things/af6CaRZ7KVX-smart-parking-system?sharecode=5jWkTN-CQHOvnFIWV-pHdCgkueqLRMvHqunsgteppko>

![Tinkercad circuit: Smart Parking System](images/circuit.jpg)

The circuit is built on a small breadboard. That is a board with holes that connects parts without soldering, which means melting metal to join wires. The long rows along its top and bottom edges, called rails, carry power to every part. Black wires are GND (ground, 0 V). Red wires are 5V (power). Each signal wire has its own colour. Pins are the numbered sockets on the Arduino.

| Part | Connected to |
|---|---|
| HC-SR04 ultrasonic sensor | power (VCC) to 5V, trigger (TRIG) to pin 10, echo (ECHO) to pin 9, ground (GND) to GND |
| Green LED | pin 3 through a 220 ohm resistor, other leg to GND |
| Red LED | pin 4 through a 220 ohm resistor, other leg to GND |
| Piezo buzzer | + to pin 5, - to GND |
| Breadboard rails | Arduino 5V and GND |

## 2. Block diagram

![Block diagram](images/block_diagram.png)

First the Arduino sends a short signal, called a trigger pulse, to the sensor on pin 10. The sensor answers on pin 9, by telling how long the echo took to come back. The Arduino turns that time into a distance. It compares the distance with 50 cm. Then it switches the LEDs and the buzzer.

## 3. Arduino source code

Source code: [`parking.ino`](parking.ino). It's the exact code running in the Tinkercad simulation.

The cut-off point, or threshold, is 50 cm. Anything closer than 50 cm counts as a parked car. Anything further away counts as an empty space.

## 4. Simulation test cases

While the simulation runs, you can click the sensor and drag an object closer or further away. I ran five tests. During each test I kept the Serial Monitor open. That is a window that shows what the program prints. Tests 4 and 5 sit just on each side of 50 cm.

| Test | Tinkercad distance | Arduino printed | Green | Red | Buzzer |
|------------|------|----------|----|----|------|
| 1. No car | 171.9 cm | 169 cm, AVAILABLE | ON | OFF | OFF |
| 2. Car parked | 21.6 cm | 21 cm, OCCUPIED | OFF | ON | ON |
| 3. Car leaves | 110.8 cm | 109 cm, AVAILABLE | ON | OFF | OFF |
| 4. Just outside 50 cm | 55.3 cm | 54 cm, AVAILABLE | ON | OFF | OFF |
| 5. Just inside 50 cm | 45.4 cm | 44 cm, OCCUPIED | OFF | ON | ON |

Test 1: no car (171.9 cm). The green LED is on.

![Test 1](images/test1_far_171cm.jpg)

Test 2: car close (21.6 cm). The red LED is on and the buzzer sounds.

![Test 2](images/test2_near_21cm.jpg)

Test 3: the car leaves (110.8 cm). The green LED is back on.

![Test 3](images/test3_back_out_110cm.jpg)

Test 4: just outside 50 cm (55.3 cm). The green LED stays on.

![Test 4](images/test4_just_outside_55cm.jpg)

Test 5: just inside 50 cm (45.4 cm). The red LED is on and the buzzer sounds.

![Test 5](images/test5_just_inside_45cm.jpg)

The Serial Monitor shows a slightly smaller number than the distance Tinkercad shows above the sensor. One reason is that the code rounds the distance down to whole centimetres. Another is that it uses a rounded speed of sound. In these five tests, the difference never changed the result.

## 5. Short explanation

### Role of each component

- The HC-SR04 ultrasonic sensor sends out a sound too high for people to hear. It reports how long the echo takes to come back.
- The Arduino Uno runs the program. It starts the sensor, works out the distance and switches the outputs.
- The green LED shows the space is free.
- The red LED shows the space is taken.
- The piezo buzzer makes a sound while a car is in the space.
- The 220 ohm resistors limit how much electricity flows through the LEDs, so the LEDs do not burn out.
- The breadboard connects 5V and GND to all the parts.

### How the sensor data is processed

1. The Arduino turns the TRIG pin on for 10 microseconds. A microsecond is a millionth of a second. This makes the sensor send a sound pulse.
2. `pulseIn(echoPin, HIGH)` measures how long the ECHO pin stays HIGH, which means on (5 V). That is the time the sound takes to reach the car and come back.
3. Sound travels about 0.034 cm every microsecond. The sound goes to the car and back, so the time covers the distance twice. That is why the code divides by 2: `distance = duration * 0.034 / 2`.
4. The program prints the distance to the Serial Monitor.

### How the Arduino controls the outputs

One `if / else` makes the decision. If `distance < threshold` (50 cm), the red LED turns on and the green LED turns off. `tone(buzzer, 1000)` plays a steady high tone. Its pitch is 1000 Hz, which means 1000 vibrations a second. Otherwise, the green LED turns on and the red LED turns off. `noTone(buzzer)` stops the sound. After `delay(500)`, which waits half a second, the loop starts again. So the lights update about twice a second.
