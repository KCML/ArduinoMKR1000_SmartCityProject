#ifndef _PMS_5003_H
#define _PMS_5003_H

#include <Wire.h>
#include <Arduino.h>

#define VERSION 0.2
#define Sense_PM        6
#define NUM_INCOME_BYTE 32
#define CHAR_PRELIM     0x42
#define NUM_DATA_BYTE   29
#define CHECK_BYTE      30
#define PM1_BYTE        10
#define PM25_BYTE       12
#define PM10_BYTE       14

class PMS5003 {
public:
	//void processData(int *PM1, int *PM25, int *PM10);
	void processDataOn(HardwareSerial &serial);
	int getPM1();
	int getPM25();
	int getPM10();
private:
	int pm1;
	int pm25;
	int pm10;
};
#endif