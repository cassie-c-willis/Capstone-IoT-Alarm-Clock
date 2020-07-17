#include "led_spi.h"

void InitializeLEDSPI() {
	SET_USCIA0_MISO_AS_AN_INPUT1;
	SET_USCIA0_MOSI_AS_AN_OUTPUT1;
	SET_SPI_SCK_AS_AN_OUTPUT1;
	SPI_SCK_PORT1 &= 0;
}

void LEDSPISendByte(unsigned char SendValue) {
	unsigned char sendLocal = SendValue;
	volatile int i;
	for (i = 7; i >= 0; i--) { //for each bit in sendLocal
		int currBit = (sendLocal >> i) & 0x01; //currbit is current bit
		if (currBit) {
			SET_MOSI1;
		}
		else {
			RESET_MOSI1;
		}
		sendLocal << i;
		//Toggle SCLK twice
		TOGGLE_SPI_SCK1;
		TOGGLE_SPI_SCK1;
	}

}

unsigned char LEDSPIReceiveByte() {
	unsigned char received = 0x00;
	int i;

	for (i = 7; i >= 0; i--) { //for each bit in received
		received <<= 1; //Left shift by one
		received |= (MISO_VALUE1); //OR with (P1IN | BIT1)

		//Toggle SCLK twice
		TOGGLE_SPI_SCK1;
		TOGGLE_SPI_SCK1;
	}

	return received;
}

