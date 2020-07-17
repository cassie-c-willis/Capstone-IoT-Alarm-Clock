#include <msp430.h> 
#include "ble1_spi.h"
#include "led_spi.h"
#include "pin_io_setup.h"
#include <string.h>

/*
 * main.c
 */

void alarmSound(void);
void phoneInteract(void);
void parseData(unsigned char byteString[]);
void bedSensorInteract(void);
void ConfigureClockModule(void);
void alarmTimers(void);
void timeDelay(volatile unsigned int delay, volatile unsigned int resolution);

unsigned int alarmTimes[7];

struct Alarms{
	unsigned int time[13];
	unsigned char name[40];
	unsigned char weekday[3];
};

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	//Initialize Buzzer port pins
    BUZZER_OFF;
	SET_BUZZER_AS_OUTPUT;
	SET_LFXIN_AS_OUTPUT;
	InitializeBLE1SPI();
	InitializeLEDSPI();
	ConfigureClockModule();
	volatile unsigned int delay = 250;
	volatile unsigned int resolution = 185;
	unsigned int count;
	while(1) {
		for(count = 0; count < 60; count++) { //wait for 1 minute
			timeDelay(delay, resolution);
			timeDelay(delay, resolution);
			timeDelay(delay, resolution);
			timeDelay(delay, resolution);
		}
		count = 0;
		phoneInteract();
	}

	return 0;
}

void alarmTimers(void) {
	//set time between alarms
	const unsigned int firstAlarm = alarmTimes[0];
	const unsigned int secondAlarm = alarmTimes[1] - alarmTimes[0];
	const unsigned int thirdAlarm = alarmTimes[2] - alarmTimes[1];
	const unsigned int fourthAlarm = alarmTimes[3] - alarmTimes[2];
	const unsigned int fifthAlarm = alarmTimes[4] - alarmTimes[3];
	const unsigned int sixthAlarm = alarmTimes[5] - alarmTimes[4];
	const unsigned int seventhAlarm = alarmTimes[6] - alarmTimes[5];
	//play the alarms
//	_delay_cycles(firstAlarm);
//	alarmSound();
//	_delay_cycles(secondAlarm);
//	alarmSound();
//	_delay_cycles(thirdAlarm);
//	alarmSound();
//	_delay_cycles(fourthAlarm);
//	alarmSound();
//	_delay_cycles(fifthAlarm);
//	alarmSound();
//	_delay_cycles(sixthAlarm);
//	alarmSound();
//	_delay_cycles(seventhAlarm);
//	alarmSound();
}

void phoneInteract(void) {
	//SPI to the bluetooth connected to the phone
	//give me info, how x amount of info to give, x info requests
	BLE1SPISendByte(0xFF); //how many bytes do you have?
	unsigned int numBytes = BLE1SPIReceiveByte(); //I have this many bytes
	numBytes = numBytes << 8;
	numBytes |= (unsigned int) BLE1SPIReceiveByte();
	unsigned char byteString[numBytes];
	int i;
	for(i = 0; i < numBytes; i++) {
		byteString[i] = BLE1SPIReceiveByte();
	}
	parseData(byteString);
}

void parseData(unsigned char byteString[]) {
	unsigned char tempweekday[3];
	unsigned char temptime[13];
	unsigned char tempName[40];
	unsigned int j = 0;
	unsigned int i = 0;
	unsigned int k = 0;
	unsigned int m = 0;
	unsigned int begin = 0;
	unsigned int end = 0;
	struct Alarms alarms[(unsigned int)byteString[1]];
	for(i = 0; i < sizeof(byteString); i++) {
		if((byteString[i] == ';') && (byteString[i+1] != '!')) {
			j++; // alarms array index
			begin = i;
		}

		else if(byteString[i] == ',') {
			end = i;
			for (k = 0; begin < k < end; k++) {
				if(m == 0) tempweekday[k] = byteString[k];
				else if (m == 1) temptime[k] = byteString[k];
				else if (m == 2) { }
				else if (m == 3) {
					tempName[k] = byteString[k];
					m = 0;
				}
				m++;
				begin = end;
			}
			unsigned int y, z, w;
			for(y = 0; y < sizeof(tempweekday); y++) alarms[j].weekday[y] = tempweekday[y];
			for(z = 0; z < sizeof(temptime); z++) alarms[j].time[z] = temptime[z];
			for(w = 0; w < sizeof(tempName); w++) alarms[j].name[w] = tempName[w];
			memset(&tempweekday[0], 0, sizeof(tempweekday));
			memset(&tempName[0], 0, sizeof(tempName));
			memset(&temptime[0], 0, sizeof(temptime));

			alarmTimes[j] = alarms[j].time; //add time until alarm in array
		}

		else if (byteString[i] == '!' && byteString[i+2] == ';') {
			//snooze time and user name here
			int snoozeTime = byteString[i+1];
		}
		else {
			begin = i;
			unsigned char username[sizeof(byteString) - begin];
			unsigned int n = 0;
			for(n = 0; begin < n < sizeof(byteString); n++) {
				username[n] = byteString[i];
			}
		}
	}
	//alarmTimers();
}

void bedSensorInteract(void) {
	//use 1 pin on ble and 1 matching pin on MSP
	//if signal is 1, person on bed, else, person not on bed
	//if person on bed, start timer
	//if person on bed after timer expires, set off alarm
	int person = BED_PIN;
	if (person) {
		person = 0;
		_delay_cycles(60000000); //set timer for 1 min
		person = BED_PIN;
		if (person) {
			alarmSound(); //turn alarm on
		}
	}
}

void alarmSound(void) {
	//sound the alarm
	unsigned int timer = 1;
	while(1) {
		int snoozeOn = SNOOZE_PIN;
		int alarmOff = ALARM_PIN;

		if(snoozeOn) {
			BUZZER_OFF;
			_delay_cycles(60000000); //turn off alarm for 1 min
		}
		else if (alarmOff == 1) {
			BUZZER_OFF;
			_delay_cycles(60000000); //turn off alarm for 1 min
			bedSensorInteract();
			break;
		}
		else {
			while(timer) {
				BUZZER_ON;
				_delay_cycles(2000);
				BUZZER_OFF;
				_delay_cycles(2000);
				timer = 0;
			}
			_delay_cycles(500000);
			timer = 1;
		}
	}
}

void timeDelay(volatile unsigned int delay, volatile unsigned int resolution) {
	// Wait for approximately 1/4 second
	unsigned int i, j;

	for(i = 0; i < delay; i++) {
		for(j = 0; j < resolution; j++);
	}
}

void ConfigureClockModule(void)
{
    // Configure Digitally Controlled Oscillator (DCO) for 16 MHz using factory
    // calibrations.
	CSCTL0  = DCOFSEL_0;
	CSCTL1 = DCOFSEL_0;
}
