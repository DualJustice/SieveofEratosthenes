#include "Arduino.h"
#include "HardwareSerial.h"


static int *primeZeroArray;


int inputLoop() {
	int userInput = 0;

	while(true) {
		if(Serial.available() > 0) {
			userInput = Serial.parseInt();
			Serial.print("You input: ");
			Serial.println(userInput);
			break;
		}

		else {
			delay(100);
		}
	}

	return userInput;
}


int *arrayLoop(int maxValue) {
	int *buildArray = new int[maxValue];

	for(int i = 0; i < maxValue; i += 1) {
		buildArray[i] = i + 2;
	}

	for(int i = 0; i < maxValue - 1; i += 1) {
		int buildi = buildArray[i];

		if(buildi != 0) {
			for(int k = 1; k < maxValue; k += 1) {
				int convertToZero = buildi*k + i;

				if(convertToZero <= maxValue) {
					buildArray[convertToZero] = 0;
				}

				else {
					break;
				}
			}
		}
	}

	int *primeZeroArray = buildArray;

	primeZeroArray[maxValue - 1] = -1;

	return primeZeroArray;
}


void askMaxAndCreateArray() {
	Serial.println("Please input a positive integer >= 2.");

	while(true) {
		int maxValue = inputLoop();

		if(maxValue < 2) {
			Serial.println("Please make sure your input is >= 2.");
		}

		else {
			primeZeroArray = arrayLoop(maxValue);
			break;
		}
	}
}


void setup() {
	Serial.begin(9600);
	while(!Serial) {
		delay(250);
	}

	while(true) {
		askMaxAndCreateArray();

		int i = 0;
		int arrayBuffer = primeZeroArray[i];

		while(arrayBuffer != -1) {
			if(arrayBuffer != 0) {
				Serial.print(arrayBuffer);
				Serial.print(" ");
			}

			i += 1;
			arrayBuffer = primeZeroArray[i];
		}

	Serial.println();
	}
}


void loop() {

}