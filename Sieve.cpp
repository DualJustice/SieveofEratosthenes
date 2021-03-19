#include "Arduino.h"
#include "HardwareSerial.h"


static int *primeZeroArray;
static unsigned int primeArrayIndex;
static int arrayBuffer;


int inputLoop() {

	String inputString;

	while(true) {
		if(Serial.available() > 0) {
			inputString = Serial.readStringUntil('\n');
			Serial.print("You input: ");
			Serial.print(inputString);
			Serial.println();
			break;
		}

		else {
			delay(100);
		}
	}

	return inputString.toInt();
}


int *arrayLoop(int maxValue) {
	int *buildArray = new int[maxValue];
	int buildi = 0;
	int k = 0;
	int convertToZero = 0;

	for(int i = 0; i < maxValue; i += 1) {
		buildArray[i] = i + 2;
	}

	for(int i = 0; i < maxValue - 1; i += 1) {
		buildi = buildArray[i];

		if(buildi != 0) {
			for(k = 1; k < maxValue; k += 1) {
				convertToZero = buildi*k + i;

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
	int maxValue = 0;

	while(true) {
		maxValue = inputLoop();

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
}


void loop() {
	askMaxAndCreateArray();

	primeArrayIndex = 0;
	arrayBuffer = primeZeroArray[primeArrayIndex];

	while(arrayBuffer != -1) {
		if(arrayBuffer != 0) {
			Serial.print(arrayBuffer);
			Serial.print(" ");
		}

		primeArrayIndex += 1;
		arrayBuffer = primeZeroArray[primeArrayIndex];
	}

	Serial.println('\n');
}