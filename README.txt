Name: AJIITESH GUPTA and SOHAIB KHADRI
CMPUT 274 Fa19

Assignment 2 Part 1: Encrypted Arduino Communication

-----------------------------------------------------------

Included Files:
 * encrypted_communication_part1.cpp
 * README
 * Makefile

Accessories:
 * Arduino Mega Board(s) (AMG)- We use 2 of them. One of them is the client, while the other one is the server.
 * 550 ohm resistor
 * Wires

Wiring Instructions:

ArduinoS: Server Arduino
ArduinoC: Client Arduino

Server: For the server arduino, connect pin 13 to the 5V pin with a 550 ohm resistor in series using a breadboard.
Client: For the client, simply connect pin 13 to any of the ground pins.
Connect the grounds of both arduinos together using any ground ports on the arduino since they are all connected. Then connect the TX3 pin of one arduino to the RX3 pin on the other arduino and vice versa so that you have Serial3 pins of each arduino connected together.

ArduinoS Pin 13 <--> 550 ohm Resistor <--> ArduinoS Pin 5V

ArduinoC Pin 13 <--> ArduinoC Ground Pin

ArduinoS Ground Pin <--> ArduinoC Ground Pin

ArduinoS Pin TX3 <--> ArduinoC Pin RX3
ArduinoS Pin RX3 <--> ArduinoC Pin TX3


Running Instructions:
1. Connect the Arduino to the PC using an A-B style USB cable. Ensure that the Arduino is using  the proper serial port (/dev/ttyACM0 or -ACM1).

2. In the  directory  containing the files encrypted_communication_part1.cpp, and a Makefile, use the following commands on 2 different computers We need to open two separate terminals and select 2 different ports by pressing "1" and then "2" on both the terminals. Type in "make upload-0 && serial-mon-0" in terminal 1 for the first Arduino and select "make upload-1 && serial-mon-1" in terminal 2 for the second Arduino.

4. On typing anything on the serial monitor, the exact thing gets copied on the other screen and that is the aim of this program: communicating between two Arduinos.

