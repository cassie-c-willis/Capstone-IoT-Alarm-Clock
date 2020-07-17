#include "ble1_spi.h"

void InitializeBLE1SPI() {
	SET_USCIA0_MISO_AS_AN_INPUT;
	SET_USCIA0_MOSI_AS_AN_OUTPUT;
	SET_SPI_SCK_AS_AN_OUTPUT;
	SPI_SCK_PORT &= 0;
}

void BLE1SPISendByte(unsigned char SendValue) {
	unsigned char sendLocal = SendValue;
	volatile int i;
	for (i = 7; i >= 0; i--) { //for each bit in sendLocal
		int currBit = (sendLocal >> i) & 0x01; //currbit is current bit
		if (currBit) {
			SET_MOSI;
		}
		else {
			RESET_MOSI;
		}
		sendLocal << i;
		//Toggle SCLK twice
		TOGGLE_SPI_SCK;
		TOGGLE_SPI_SCK;
	}

}

unsigned char BLE1SPIReceiveByte() {
	unsigned char received = 0x00;
	int i;

	for (i = 7; i >= 0; i--) { //for each bit in received
		received <<= 1; //Left shift by one
		received |= (MISO_VALUE); //OR with (P1IN | BIT1)

		//Toggle SCLK twice
		TOGGLE_SPI_SCK;
		TOGGLE_SPI_SCK;
	}

	return received;
}

