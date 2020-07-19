/*# ---------------------------------------------------
# Name : SOHAIB KHADRI and AJIITESH GUPTA
# ID: 1574054 and 1562557
# CMPUT 274 , Fall 2019
#
# Assignment 2 Part 1: Encrypted Arduino Communication
# ---------------------------------------------------
*/


//needed for all arduinos
#include <Arduino.h>


//initializing static key values given to us
uint32_t serverPublicKey = 7;
uint32_t serverPrivateKey = 27103;
uint32_t serverModulus = 95477;
uint32_t clientPublicKey = 11;
uint32_t clientPrivateKey = 38291;
uint32_t clientModulus = 84823;



void setup() {
	//needed for all arduino programs
	init();

	//initializing serial ports
	Serial.begin(9600);
	Serial3.begin(9600);

}

uint32_t mulmod(uint32_t a, uint32_t b, uint32_t m) {
     //Initialize variables used in function and mod m before calculations
    uint32_t res = b % m;
    uint32_t tres = 0;
    a = a % m;

    //multiplying by 2 and mod m for each bit
    for(int i = 0; i <= 31; i++) {
    	//checking if binary represention of a has a 1 in ith position. If so, add result to total result
        if (((a>>i) & 1) != 0) {

            tres = (tres % m) + (res % m);
        }

        res = (2*res) % m;
    
    }
    return (tres % m);
}

//powmod function given to us inclass
//computes the value x^pow mod m ("x to the power of pow" mod m)
uint32_t powmod(uint32_t x, uint32_t pow, uint32_t m) {

	uint32_t ans = 1;
	uint32_t pow_x = x;

	while (pow > 0) {
		if(pow&1 == 1) {	
			ans = mulmod(ans, pow_x, m);	
		}
	pow_x = mulmod(pow_x, pow_x, m);
	pow >>= 1;

	}
	return ans;

}

/** Writes an uint32_t to Serial3 , starting from the least - significant
* and finishing with the most significant byte .
*/
void uint32_to_serial3(uint32_t num) {
	Serial3.write((char)(num>>0));
	Serial3.write((char)(num>>8));
	Serial3.write((char)(num>>16));
	Serial3.write((char)(num>>24));
}

/** Reads an uint32_t from Serial3 , starting from the least - significant
* and finishing with the most significant byte .
*/
uint32_t uint32_from_serial3() {
	uint32_t num = 0;
	num=num|((uint32_t)Serial3.read())<<0;
	num=num|((uint32_t)Serial3.read())<<8;
	num=num|((uint32_t)Serial3.read())<<16;
	num=num|((uint32_t)Serial3.read())<<24;
	return num;
}



int main() {
	
	setup();

	//initializing variables for the two different arduinos if server or client
	uint32_t d;
	uint32_t n;
	uint32_t e;
	uint32_t m;

	//assigning values to server arduino
	if (digitalRead(13) == HIGH) {
		d = serverPrivateKey;
		n = serverModulus;
		e = clientPublicKey;
		m = clientModulus;
	
	//assigning variables to client arduino
	} else {
		d = clientPrivateKey;
		n = clientModulus;
		e = serverPublicKey;
		m = serverModulus;
	}

	
	//loop to check for sending or recieving characters from serial mon
	while (true) {
		
		//sending character
		if (Serial.available() > 0) {
			char input = Serial.read();
			uint32_t encrypted = powmod(input, e, m);
			Serial.print(input);
			uint32_to_serial3(encrypted);

			//if carraige return character sent, also send new line feed character
			if (input == '\r') {
				uint32_t encrypted = powmod('\n', e, m);
				Serial.print('\n');
				uint32_to_serial3(encrypted);
			}
		}

		//recieving character
		if (Serial3.available() >= 4) {
			uint32_t input = uint32_from_serial3();
			uint32_t decrypted = powmod(input, d, n);
			Serial.write(decrypted);

		}	
	}

	Serial.flush();
	return 0;
}